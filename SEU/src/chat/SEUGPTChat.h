#pragma once

#include "../render/Primitives.h"
#include <string>
#include <thread>
#include <mutex>
#include <vector>

class SEUGPTChat {
public:
    SEUGPTChat();
    ~SEUGPTChat();

    bool active() const { return active_; }
    void open();
    void close();
    void update(float dt);
    void handleKey(unsigned char key);
    void handleSpecialKey(int key);
    void render(int width, int height) const;
    void renderWorld() const;

private:
    struct Message {
        std::string role;
        std::string text;
    };

    struct Settings {
        std::string apiKey;
        std::string model = "gpt-6-astra";
        std::string endpoint = "https://api.openai.com/v1/responses";
        std::string systemPrompt =
            "You are SEUGPT, the helpful digital campus assistant for Southeast University "
            "in Dhaka, Bangladesh. Be concise, friendly, accurate, and useful to students, "
            "teachers, visitors, and admission applicants. If you do not know a campus-specific "
            "detail, say so instead of inventing it.";
    };

    Settings settings_;
    std::vector<Message> messages_;
    std::string inputText_;
    std::string errorText_;
    bool active_ = false;
    bool waiting_ = false;
    float cursorTime_ = 0.0f;
    int historyScroll_ = 0;

    std::thread worker_;
    mutable std::mutex resultMutex_;
    bool resultReady_ = false;
    bool resultSuccess_ = false;
    std::string workerResult_;

    void loadSettings();
    void sendMessage();
    void finishRequest();
    static std::string request(const Settings& settings, const std::string& payload, bool& ok);
    static std::string jsonEscape(const std::string& value);
    static std::string extractOutputText(const std::string& json);
    static std::string extractErrorText(const std::string& json);
    static void drawRect(int x, int y, int width, int height, float r, float g, float b, float a = 1.0f);
    static void drawWrapped(const std::string& value, int x, int y, int maxChars, int maxLines,
                            render::Color color, int lineHeight = 21);
};
