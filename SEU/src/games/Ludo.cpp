#include "Ludo.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdio>
#include <random>
#include <string>
namespace { std::mt19937 rng(12); }
void Ludo::reset() {
    for(int& token:tokens_) token=-1;
    turn_=0; dice_=0; winner_=-1;
    statusMsg_ = "Space/R to roll dice";
}
void Ludo::roll() {
    if(dice_||winner_>=0) return;
    std::uniform_int_distribution<int> d(1,6);
    dice_ = d(rng);
    bool legal = false;
    for(int i=0; i<4; ++i) legal = legal || (tokens_[i] < 0 ? dice_ == 6 : tokens_[i] + dice_ <= 20);
    if (!legal) {
        statusMsg_ = "Player rolled " + std::to_string(dice_) + " (no legal move) - Space to pass to CPU";
    } else {
        statusMsg_ = "Player rolled " + std::to_string(dice_) + " - Press 1-4 to choose token";
    }
}
void Ludo::update(const Input& input) {
    if (input.pressed('n')) { reset(); return; }
    if (winner_ >= 0) return;
    if (turn_ == 1) return;
    if (!dice_ && (input.pressed(' ') || input.pressed('r') || input.pressed(13))) {
        roll();
        return;
    }
    if (dice_) {
        bool legal = false;
        for (int i=0; i<4; ++i) legal = legal || (tokens_[i] < 0 ? dice_ == 6 : tokens_[i] + dice_ <= 20);
        if (!legal) {
            if (input.pressed(' ') || input.pressed('r') || input.pressed(13)) {
                dice_ = 0;
                turn_ = 1;
                cpuTurn();
            }
            return;
        }
        for (int i=0; i<4; ++i) {
            if (input.pressed(static_cast<unsigned char>('1' + i))) {
                bool moved = false;
                if (tokens_[i] < 0 && dice_ == 6) { tokens_[i] = 0; moved = true; }
                else if (tokens_[i] >= 0 && tokens_[i] + dice_ <= 20) { tokens_[i] += dice_; moved = true; }
                if (moved) {
                    dice_ = 0;
                    if (tokens_[0]>=20 && tokens_[1]>=20 && tokens_[2]>=20 && tokens_[3]>=20) {
                        winner_ = 0;
                        statusMsg_ = "PLAYER WINS - N to replay";
                    } else {
                        turn_ = 1;
                        cpuTurn();
                    }
                    break;
                }
            }
        }
    }
}
void Ludo::cpuTurn() {
    std::uniform_int_distribution<int> d(1,6);
    const int rollValue = d(rng);
    int chosen = -1;
    for (int i=4; i<8; ++i) if (tokens_[i]>=0 && tokens_[i]+rollValue<=20) { chosen = i; break; }
    if (chosen < 0 && rollValue == 6) {
        for (int i=4; i<8; ++i) if (tokens_[i] < 0) { chosen = i; break; }
    }
    if (chosen >= 0) {
        if (tokens_[chosen] < 0) tokens_[chosen] = 0;
        else tokens_[chosen] += rollValue;
    }
    if (tokens_[4]>=20 && tokens_[5]>=20 && tokens_[6]>=20 && tokens_[7]>=20) {
        winner_ = 1;
        statusMsg_ = "CPU WINS - N to replay";
    } else {
        turn_ = 0;
        char buf[128];
        if (chosen >= 0) {
            std::snprintf(buf, sizeof buf, "CPU rolled %d and moved Token %d. Your turn - Space to roll", rollValue, chosen - 3);
        } else {
            std::snprintf(buf, sizeof buf, "CPU rolled %d (no move). Your turn - Space to roll", rollValue);
        }
        statusMsg_ = buf;
    }
}
void Ludo::render(int, int) const {
    char text[100];
    render::text2d(55, 65, "LUDO", {1, .85f, .25f});
    render::text2d(55, 100, "Space/R roll | 1-4 choose token | N new game | Esc menu", {1, 1, 1});

    // Outer board frame
    glDisable(GL_LIGHTING);
    glColor3f(.12f, .38f, .18f);
    glBegin(GL_QUADS);
    glVertex2i(55, 140); glVertex2i(555, 140); glVertex2i(555, 360); glVertex2i(55, 360);
    glEnd();

    // Player Red Yard on left
    glColor3f(.7f, .18f, .18f);
    glBegin(GL_QUADS);
    glVertex2i(70, 155); glVertex2i(190, 155); glVertex2i(190, 345); glVertex2i(70, 345);
    glEnd();

    // CPU Blue Yard on right
    glColor3f(.18f, .35f, .75f);
    glBegin(GL_QUADS);
    glVertex2i(420, 155); glVertex2i(540, 155); glVertex2i(540, 345); glVertex2i(420, 345);
    glEnd();

    // Central track background
    glColor3f(.22f, .26f, .30f);
    glBegin(GL_QUADS);
    glVertex2i(195, 155); glVertex2i(415, 155); glVertex2i(415, 345); glVertex2i(195, 345);
    glEnd();

    // White borders
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP); glVertex2i(70, 155); glVertex2i(190, 155); glVertex2i(190, 345); glVertex2i(70, 345); glEnd();
    glBegin(GL_LINE_LOOP); glVertex2i(420, 155); glVertex2i(540, 155); glVertex2i(540, 345); glVertex2i(420, 345); glEnd();
    glBegin(GL_LINE_LOOP); glVertex2i(195, 155); glVertex2i(415, 155); glVertex2i(415, 345); glVertex2i(195, 345); glEnd();
    glEnable(GL_LIGHTING);

    render::text2d(85, 175, "Player Yard", {1, 1, 1});
    render::text2d(440, 175, "CPU Yard", {1, 1, 1});
    render::text2d(260, 175, "Track (0-20)", {.9f, .9f, .9f});

    // Draw tokens with state labels
    for (int i = 0; i < 4; ++i) {
        char buf[32];
        if (tokens_[i] < 0) {
            std::snprintf(buf, sizeof buf, "%d: [Yard]", i + 1);
            render::text2d(80, 210 + i * 32, buf, {1, .7f, .7f});
        } else if (tokens_[i] >= 20) {
            std::snprintf(buf, sizeof buf, "%d: [GOAL]", i + 1);
            render::text2d(340, 205 + i * 22, buf, {1, .9f, .2f});
        } else {
            std::snprintf(buf, sizeof buf, "%d: %d/20", i + 1, tokens_[i]);
            const int tx = 205 + static_cast<int>(tokens_[i] * 5.2f);
            render::text2d(tx, 205 + i * 22, buf, {1, .4f, .4f});
        }
    }

    for (int i = 4; i < 8; ++i) {
        char buf[32];
        if (tokens_[i] < 0) {
            std::snprintf(buf, sizeof buf, "%d: [Yard]", i - 3);
            render::text2d(435, 210 + (i - 4) * 32, buf, {.7f, .85f, 1});
        } else if (tokens_[i] >= 20) {
            std::snprintf(buf, sizeof buf, "C%d: [GOAL]", i - 3);
            render::text2d(205, 275 + (i - 4) * 16, buf, {1, .9f, .2f});
        } else {
            std::snprintf(buf, sizeof buf, "C%d: %d/20", i - 3, tokens_[i]);
            const int tx = 350 - static_cast<int>(tokens_[i] * 5.2f);
            render::text2d(tx, 275 + (i - 4) * 16, buf, {.4f, .7f, 1});
        }
    }

    std::snprintf(text, sizeof text, "Turn: %s   Dice: %s", turn_ ? "CPU" : "Player", dice_ ? std::to_string(dice_).c_str() : "-");
    render::text2d(55, 395, text, {1, 1, 1});

    const char* displayMsg = statusMsg_.empty() ? (winner_ == 0 ? "PLAYER WINS - N to replay" : winner_ == 1 ? "CPU WINS - N to replay" : "Space to roll") : statusMsg_.c_str();
    render::text2d(55, 435, displayMsg, winner_ >= 0 ? render::Color{1, .85f, .2f} : render::Color{1, 1, 1});
}
