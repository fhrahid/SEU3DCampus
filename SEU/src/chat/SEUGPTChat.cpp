#define WIN32_LEAN_AND_MEAN
#include "SEUGPTChat.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <windows.h>
#include <winhttp.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

namespace {
std::string trim(const std::string& value) {
    const std::size_t first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return {};
    const std::size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::wstring wide(const std::string& value) {
    return std::wstring(value.begin(), value.end());
}

void drawString(const std::string& value, int x, int y, render::Color color) {
    render::text2d(x, y, value.c_str(), color);
}

void drawWorldString(Vec3 position, const std::string& value, render::Color color) {
    glDisable(GL_LIGHTING);
    glColor3f(color.r, color.g, color.b);
    // The whole scene is mirrored at the view boundary.  Use a mirrored
    // monospaced stroke font locally so the terminal reads left-to-right in
    // world space and can be scaled to the physical monitor face.
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    // Slight horizontal compression keeps the terminal dense and readable
    // while preserving the comfortable vertical character height.
    glScalef(-.00027f, .00032f, .00032f);
    for (const unsigned char character : value) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, character);
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
}

SEUGPTChat::SEUGPTChat() {
    loadSettings();
    messages_.push_back({"assistant", "Hello! I am SEUGPT, the Southeast University digital campus assistant. How can I help you?"});
}

SEUGPTChat::~SEUGPTChat() {
    if (worker_.joinable()) worker_.join();
}

void SEUGPTChat::loadSettings() {
    std::vector<std::string> paths = {
        "seugpt_config.ini",
        "SEU/seugpt_config.ini",
        "../seugpt_config.ini",
        "../../seugpt_config.ini"
    };

    // Code::Blocks may set its working directory to the MinGW installation.
    // Resolve the project config from the executable directory as well:
    // SEU/bin/Debug/SEU.exe -> SEU/seugpt_config.ini.
    char modulePath[MAX_PATH]{};
    const DWORD moduleLength = GetModuleFileNameA(nullptr, modulePath, MAX_PATH);
    if (moduleLength > 0 && moduleLength < MAX_PATH) {
        std::string executablePath(modulePath, moduleLength);
        const std::size_t slash = executablePath.find_last_of("\\/");
        if (slash != std::string::npos) {
            const std::string executableDirectory = executablePath.substr(0, slash);
            paths.push_back(executableDirectory + "\\seugpt_config.ini");
            paths.push_back(executableDirectory + "\\..\\..\\seugpt_config.ini");
            paths.push_back(executableDirectory + "\\..\\..\\..\\seugpt_config.ini");
        }
    }

    std::ifstream file;
    for (const std::string& path : paths) {
        file.clear();
        file.open(path.c_str());
        if (file.is_open()) break;
    }

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty() || line.front() == '#' || line.front() == ';') continue;
            const std::size_t separator = line.find('=');
            if (separator == std::string::npos) continue;
            const std::string key = trim(line.substr(0, separator));
            const std::string value = trim(line.substr(separator + 1));
            if (key == "api_key") settings_.apiKey = value;
            else if (key == "model" && !value.empty()) settings_.model = value;
            else if (key == "endpoint" && !value.empty()) settings_.endpoint = value;
            else if (key == "system_prompt" && !value.empty()) settings_.systemPrompt = value;
        }
    }

    if (settings_.apiKey.empty()) {
        const char* openRouterKey = std::getenv("OPENROUTER_API_KEY");
        if (openRouterKey) settings_.apiKey = openRouterKey;
    }
    if (settings_.apiKey.empty()) {
        const char* environmentKey = std::getenv("OPENAI_API_KEY");
        if (environmentKey) settings_.apiKey = environmentKey;
    }

    // Make the common OpenRouter setup work even when only the key was
    // changed in the config file and the endpoint was left at the template
    // default.
    if (settings_.apiKey.rfind("sk-or-", 0) == 0 &&
        settings_.endpoint == "https://api.openai.com/v1/responses") {
        settings_.endpoint = "https://openrouter.ai/api/v1/responses";
    }
}

void SEUGPTChat::open() {
    loadSettings();
    active_ = true;
    cursorTime_ = 0.0f;
    errorText_.clear();
}

void SEUGPTChat::close() {
    active_ = false;
    inputText_.clear();
}

void SEUGPTChat::update(float dt) {
    cursorTime_ += dt;
    if (cursorTime_ > 2.0f) cursorTime_ = 0.0f;
    finishRequest();
}

void SEUGPTChat::handleKey(unsigned char key) {
    if (!active_) return;

    if (key == 27) {
        close();
        return;
    }
    if (key == 13) {
        sendMessage();
        return;
    }
    if (key == 8) {
        if (!inputText_.empty()) inputText_.pop_back();
        return;
    }
    if (key >= 32 && key <= 126 && inputText_.size() < 480) {
        inputText_.push_back(static_cast<char>(key));
    }
}

void SEUGPTChat::handleSpecialKey(int key) {
    if (!active_) return;
    if (key == GLUT_KEY_UP || key == GLUT_KEY_PAGE_UP) {
        historyScroll_ += 4;
    } else if (key == GLUT_KEY_DOWN || key == GLUT_KEY_PAGE_DOWN) {
        historyScroll_ = std::max(0, historyScroll_ - 4);
    }
}

void SEUGPTChat::sendMessage() {
    if (waiting_) return;
    const std::string prompt = trim(inputText_);
    if (prompt.empty()) return;

    inputText_.clear();
    errorText_.clear();
    historyScroll_ = 0;
    messages_.push_back({"user", prompt});

    if (settings_.apiKey.empty()) {
        errorText_ = "No API key configured. Edit SEU/seugpt_config.ini or set OPENAI_API_KEY, then reopen SEUGPT.";
        messages_.push_back({"assistant", errorText_});
        return;
    }

    std::ostringstream payload;
    payload << "{\"model\":\"" << jsonEscape(settings_.model)
            << "\",\"instructions\":\"" << jsonEscape(settings_.systemPrompt)
            << "\",\"store\":false,\"input\":[";
    for (std::size_t i = 0; i < messages_.size(); ++i) {
        if (i != 0) payload << ',';
        payload << "{\"role\":\"" << jsonEscape(messages_[i].role)
                << "\",\"content\":\"" << jsonEscape(messages_[i].text) << "\"}";
    }
    payload << "]}";

    const Settings requestSettings = settings_;
    const std::string body = payload.str();
    waiting_ = true;
    if (worker_.joinable()) worker_.join();
    worker_ = std::thread([this, requestSettings, body]() {
        bool ok = false;
        const std::string response = request(requestSettings, body, ok);
        std::lock_guard<std::mutex> lock(resultMutex_);
        workerResult_ = response;
        resultSuccess_ = ok;
        resultReady_ = true;
    });
}

void SEUGPTChat::finishRequest() {
    std::string result;
    bool success = false;
    {
        std::lock_guard<std::mutex> lock(resultMutex_);
        if (!resultReady_) return;
        result = workerResult_;
        success = resultSuccess_;
        resultReady_ = false;
    }

    waiting_ = false;
    if (worker_.joinable()) worker_.join();
    if (success) {
        errorText_.clear();
        historyScroll_ = 0;
        messages_.push_back({"assistant", result.empty() ? "SEUGPT returned an empty response." : result});
    } else {
        errorText_ = result.empty() ? "SEUGPT could not reach the OpenAI API." : result;
        messages_.push_back({"assistant", errorText_});
    }
}

std::string SEUGPTChat::jsonEscape(const std::string& value) {
    std::string escaped;
    escaped.reserve(value.size() + 16);
    for (const unsigned char character : value) {
        switch (character) {
            case '"': escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default:
                if (character < 0x20) escaped += ' ';
                else escaped += static_cast<char>(character);
                break;
        }
    }
    return escaped;
}

std::string SEUGPTChat::extractOutputText(const std::string& json) {
    std::size_t typePosition = json.find("\"output_text\"");
    if (typePosition == std::string::npos) typePosition = 0;
    const std::size_t textKey = json.find("\"text\"", typePosition);
    if (textKey == std::string::npos) return {};
    const std::size_t colon = json.find(':', textKey);
    if (colon == std::string::npos) return {};
    const std::size_t quote = json.find('"', colon + 1);
    if (quote == std::string::npos) return {};

    std::string result;
    bool escaped = false;
    for (std::size_t i = quote + 1; i < json.size(); ++i) {
        const char character = json[i];
        if (escaped) {
            switch (character) {
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
                case '"': result += '"'; break;
                case '\\': result += '\\'; break;
                default: result += character; break;
            }
            escaped = false;
        } else if (character == '\\') {
            escaped = true;
        } else if (character == '"') {
            break;
        } else {
            result += character;
        }
    }
    return result;
}

std::string SEUGPTChat::extractErrorText(const std::string& json) {
    const std::size_t errorPosition = json.find("\"error\"");
    const std::size_t searchFrom = errorPosition == std::string::npos ? 0 : errorPosition;
    const std::size_t messageKey = json.find("\"message\"", searchFrom);
    if (messageKey == std::string::npos) return {};
    const std::size_t colon = json.find(':', messageKey);
    const std::size_t quote = colon == std::string::npos ? std::string::npos : json.find('"', colon + 1);
    if (quote == std::string::npos) return {};
    const std::size_t end = json.find('"', quote + 1);
    if (end == std::string::npos) return {};
    return json.substr(quote + 1, end - quote - 1);
}

std::string SEUGPTChat::request(const Settings& settings, const std::string& payload, bool& ok) {
    ok = false;
    const std::wstring endpoint = wide(settings.endpoint);
    URL_COMPONENTS components{};
    components.dwStructSize = sizeof(components);
    wchar_t hostBuffer[256]{};
    wchar_t pathBuffer[2048]{};
    components.lpszHostName = hostBuffer;
    components.dwHostNameLength = static_cast<DWORD>(sizeof(hostBuffer) / sizeof(hostBuffer[0]));
    components.lpszUrlPath = pathBuffer;
    components.dwUrlPathLength = static_cast<DWORD>(sizeof(pathBuffer) / sizeof(pathBuffer[0]));
    if (!WinHttpCrackUrl(endpoint.c_str(), 0, 0, &components)) {
        return "Invalid SEUGPT endpoint in seugpt_config.ini.";
    }

    const bool secure = components.nScheme == INTERNET_SCHEME_HTTPS;
    const std::wstring host(hostBuffer, components.dwHostNameLength);
    const std::wstring path = components.dwUrlPathLength == 0
        ? std::wstring(L"/")
        : std::wstring(pathBuffer, components.dwUrlPathLength);
    HINTERNET session = WinHttpOpen(L"SEUGPT/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!session) return "Could not initialize Windows HTTP networking.";
    WinHttpSetTimeouts(session, 5000, 5000, 15000, 15000);

    HINTERNET connection = WinHttpConnect(session, host.c_str(), components.nPort, 0);
    if (!connection) {
        WinHttpCloseHandle(session);
        return "Could not connect to the SEUGPT API endpoint.";
    }
    HINTERNET requestHandle = WinHttpOpenRequest(connection, L"POST", path.c_str(), nullptr,
                                                 WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES,
                                                 secure ? WINHTTP_FLAG_SECURE : 0);
    if (!requestHandle) {
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);
        return "Could not create the SEUGPT API request.";
    }

    const std::wstring headers = L"Content-Type: application/json\r\nAuthorization: Bearer " + wide(settings.apiKey);
    const BOOL sent = WinHttpSendRequest(requestHandle, headers.c_str(), static_cast<DWORD>(headers.size()),
                                         const_cast<char*>(payload.data()), static_cast<DWORD>(payload.size()),
                                         static_cast<DWORD>(payload.size()), 0);
    if (!sent || !WinHttpReceiveResponse(requestHandle, nullptr)) {
        WinHttpCloseHandle(requestHandle);
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);
        return "The SEUGPT request failed before receiving a response.";
    }

    DWORD status = 0;
    DWORD statusSize = sizeof(status);
    WinHttpQueryHeaders(requestHandle, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                        WINHTTP_HEADER_NAME_BY_INDEX, &status, &statusSize, WINHTTP_NO_HEADER_INDEX);
    std::string response;
    DWORD available = 0;
    while (WinHttpQueryDataAvailable(requestHandle, &available) && available > 0) {
        std::string chunk(available, '\0');
        DWORD received = 0;
        if (!WinHttpReadData(requestHandle, &chunk[0], available, &received)) break;
        response.append(chunk.data(), received);
    }

    WinHttpCloseHandle(requestHandle);
    WinHttpCloseHandle(connection);
    WinHttpCloseHandle(session);

    if (status < 200 || status >= 300) {
        const std::string apiError = extractErrorText(response);
        if (apiError.find("No endpoints") != std::string::npos ||
            apiError.find("no endpoints") != std::string::npos) {
            return "OpenRouter has no active endpoint for model '" + settings.model + "'. Set model=openrouter/free or choose an available model in seugpt_config.ini.";
        }
        return apiError.empty() ? "SEUGPT API returned HTTP status " + std::to_string(status) + "." : apiError;
    }
    const std::string text = extractOutputText(response);
    if (text.empty()) return "SEUGPT returned a response that could not be read.";
    ok = true;
    return text;
}

void SEUGPTChat::drawRect(int x, int y, int width, int height, float r, float g, float b, float a) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor4f(r, g, b, a);
    glBegin(GL_QUADS);
    glVertex2i(x, y); glVertex2i(x + width, y);
    glVertex2i(x + width, y + height); glVertex2i(x, y + height);
    glEnd();
}

void SEUGPTChat::drawWrapped(const std::string& value, int x, int y, int maxChars, int maxLines,
                             render::Color color, int lineHeight) {
    std::string line;
    int lineCount = 0;
    auto emit = [&]() {
        if (lineCount >= maxLines) return;
        drawString(line, x, y + lineCount * lineHeight, color);
        ++lineCount;
        line.clear();
    };

    for (const char character : value) {
        if (character == '\n' || static_cast<int>(line.size()) >= maxChars) emit();
        if (lineCount >= maxLines) break;
        if (character != '\n') line.push_back(character);
    }
    if (lineCount < maxLines && !line.empty()) emit();
}

void SEUGPTChat::render(int width, int height) const {
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // A compact monochrome monitor terminal: the campus remains visible
    // behind it, while the black screen stays readable from a distance.
    drawRect(0, 0, width, height, .0f, .0f, .0f, .45f);
    const int monitorW = std::min(980, std::max(620, width - 150));
    const int monitorH = std::min(600, std::max(410, height - 90));
    const int monitorX = (width - monitorW) / 2;
    const int monitorY = (height - monitorH) / 2;
    drawRect(monitorX - 14, monitorY - 14, monitorW + 28, monitorH + 28, .18f, .19f, .20f, 1.0f);
    drawRect(monitorX - 5, monitorY - 5, monitorW + 10, monitorH + 10, .72f, .73f, .74f, 1.0f);
    drawRect(monitorX, monitorY, monitorW, monitorH, .0f, .0f, .0f, 1.0f);

    const int screenX = monitorX + 24;
    const int screenY = monitorY + 22;
    const int screenW = monitorW - 48;
    const int screenH = monitorH - 76;
    drawRect(screenX, screenY, screenW, screenH, .015f, .015f, .015f, 1.0f);
    drawRect(screenX, screenY, screenW, 34, .10f, .10f, .10f, 1.0f);
    drawString("SEUGPT // SOUTHEAST UNIVERSITY TERMINAL", screenX + 14, screenY + 23, {.96f, .96f, .96f});
    drawString(settings_.apiKey.empty() ? "OFFLINE" : (waiting_ ? "PROCESSING" : "READY"),
               screenX + screenW - 118, screenY + 23, {.78f, .78f, .78f});

    const int inputH = 54;
    const int historyX = screenX + 18;
    const int historyY = screenY + 48;
    const int historyBottom = screenY + screenH - inputH - 14;
    const int lineHeight = 18;
    const int maxChars = std::max(48, (screenW - 36) / 10);
    std::vector<std::string> terminalLines;

    // Build one wrapped command-line history, then draw only the final lines.
    // This keeps every new message visible instead of letting old bubbles push
    // the latest response below the monitor.
    auto appendMessage = [&](const Message& message) {
        const std::string prefix = message.role == "user" ? "> " : "SEUGPT> ";
        std::string line = prefix;
        for (const char character : message.text) {
            if (character == '\n' || static_cast<int>(line.size()) >= maxChars) {
                terminalLines.push_back(line);
                line = std::string(prefix.size(), ' ');
            }
            if (character != '\n') line.push_back(character);
        }
        if (line.size() > prefix.size() || message.text.empty()) terminalLines.push_back(line);
    };
    for (const Message& message : messages_) appendMessage(message);
    if (waiting_) terminalLines.push_back("SEUGPT> [thinking...]");

    const int visibleLines = std::max(3, (historyBottom - historyY) / lineHeight);
    const int firstLine = terminalLines.size() > static_cast<std::size_t>(visibleLines)
        ? static_cast<int>(terminalLines.size()) - visibleLines : 0;
    int y = historyY + lineHeight;
    for (int index = firstLine; index < static_cast<int>(terminalLines.size()); ++index) {
        drawString(terminalLines[static_cast<std::size_t>(index)], historyX, y, {.93f, .93f, .93f});
        y += lineHeight;
    }

    drawRect(screenX, historyBottom, screenW, inputH, .08f, .08f, .08f, 1.0f);
    const std::string status = settings_.apiKey.empty()
        ? "CONFIGURE API KEY"
        : (waiting_ ? "WAITING FOR RESPONSE" : "ENTER SEND | ESC CLOSE");
    drawString(status, historyX, historyBottom + 19, {.72f, .72f, .72f});

    std::string composer = inputText_;
    const int composerChars = std::max(30, (screenW - 70) / 10);
    if (static_cast<int>(composer.size()) > composerChars) {
        composer = "..." + composer.substr(composer.size() - static_cast<std::size_t>(composerChars - 3));
    }
    if (composer.empty() && !waiting_) composer = "type a message";
    if (!waiting_ && cursorTime_ < 1.0f) composer += "_";
    drawString("> " + composer, historyX, historyBottom + 43,
               inputText_.empty() && !waiting_ ? render::Color{.52f, .52f, .52f} : render::Color{1, 1, 1});
    drawString("SEUGPT", monitorX + monitorW / 2 - 34, monitorY + monitorH + 24, {.08f, .08f, .08f});

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW);
}

void SEUGPTChat::renderWorld() const {
    // Coordinates match the physical SEUGPT monitor in Furniture.cpp. The
    // front face points toward +Z, where the visitor chair is located.
    const float screenX = -22.35f;
    const float screenY = 1.2f + 1.22f;
    const float screenZ = 19.0f + .186f;
    const float halfWidth = .60f;
    const float halfHeight = .28f;

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(.005f, .005f, .005f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(screenX - halfWidth, screenY - halfHeight, screenZ);
    glVertex3f(screenX + halfWidth, screenY - halfHeight, screenZ);
    glVertex3f(screenX + halfWidth, screenY + halfHeight, screenZ);
    glVertex3f(screenX - halfWidth, screenY + halfHeight, screenZ);
    glEnd();

    glColor3f(.65f, .65f, .65f);
    glBegin(GL_LINES);
    glVertex3f(screenX - halfWidth, screenY + .13f, screenZ + .002f);
    glVertex3f(screenX + halfWidth, screenY + .13f, screenZ + .002f);
    glEnd();

    std::vector<std::string> lines;
    // 38 horizontally tightened characters fill the usable width of the
    // 1.20m screen with a small, realistic bezel margin.
    const int maxChars = 38;
    auto appendMessage = [&](const Message& message) {
        const std::string prefix = message.role == "user" ? "> " : "AI> ";
        std::string line = prefix;
        for (const char character : message.text) {
            if (character == '\n' || static_cast<int>(line.size()) >= maxChars) {
                lines.push_back(line);
                line = std::string(prefix.size(), ' ');
            }
            if (character != '\n') line.push_back(character);
        }
        if (line.size() > prefix.size() || message.text.empty()) lines.push_back(line);
    };
    for (const Message& message : messages_) appendMessage(message);
    if (waiting_) lines.push_back("AI> thinking...");

    // Use the full monitor face: eight history rows plus a separate composer
    // row. Older rows remain available through the existing scroll controls.
    const int visibleLines = 8;
    const int lastLineStart = lines.size() > static_cast<std::size_t>(visibleLines)
        ? static_cast<int>(lines.size()) - visibleLines : 0;
    const int firstLine = std::max(0, lastLineStart - historyScroll_);
    const float lineHeight = .043f;
    float textY = screenY + .105f;
    for (int index = firstLine; index < static_cast<int>(lines.size()); ++index) {
        drawWorldString({screenX + .54f, textY, screenZ + .006f},
                        lines[static_cast<std::size_t>(index)], {.92f, .92f, .92f});
        textY -= lineHeight;
    }

    const std::string input = waiting_ ? "AI> ..." : (inputText_.empty() ? "> _" : "> " + inputText_);
    std::string visibleInput = input;
    if (visibleInput.size() > 38) visibleInput = visibleInput.substr(0, 38);
    drawWorldString({screenX + .54f, screenY - .245f, screenZ + .006f}, visibleInput,
                    {.98f, .98f, .98f});
    drawWorldString({screenX + .54f, screenY + .205f, screenZ + .006f},
                    "SEUGPT // SEU TERMINAL",
                    {1.0f, 1.0f, 1.0f});

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
