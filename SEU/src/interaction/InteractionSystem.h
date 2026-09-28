#pragma once
#include "../render/Camera.h"
#include <string>

class Input;
class Player;

class InteractionSystem {
public:
    enum class Kind { Chair, GameStation, Shop, Lift, Chatbot };
    struct Trigger {
        Vec3 position;
        float radius;
        Kind kind;
        const char* name;
        int gameIndex = -1;
        const char* notification = nullptr;
        float seatYaw = 0.0f;        // Direction player faces when seated
    };

    void update(const Input& input, Player& player, float dt = 0.016f);
    const char* prompt() const { return prompt_.c_str(); }
    bool gameRequested() const { return gameRequested_; }
    int requestedGame() const { return requestedGame_; }
    void clearGameRequest() { gameRequested_ = false; }
    bool chatRequested() const { return chatRequested_; }
    void clearChatRequest() { chatRequested_ = false; }

    bool hasNotification() const { return notifyTimer_ > 0.0f; }
    const char* notification() const { return notification_.c_str(); }

private:
    const Trigger* current_ = nullptr;
    std::string prompt_;
    std::string notification_;
    float notifyTimer_ = 0.0f;
    float sitCooldown_ = 0.0f;       // Prevents immediate re-sit after standing
    bool gameRequested_ = false;
    int requestedGame_ = -1;
    bool chatRequested_ = false;
};
