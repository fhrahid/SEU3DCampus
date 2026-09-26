#pragma once
#include "../render/Camera.h"
class Input;
class Player;
class InteractionSystem {
public:
    enum class Kind { Chair, GameStation };
    struct Trigger { Vec3 position; float radius; Kind kind; const char* name; };
    void update(const Input& input, Player& player);
    const char* prompt() const { return prompt_; }
    bool gameRequested() const { return gameRequested_; }
    void clearGameRequest() { gameRequested_ = false; }
private:
    const Trigger* current_ = nullptr;
    const char* prompt_ = "";
    bool gameRequested_ = false;
};
