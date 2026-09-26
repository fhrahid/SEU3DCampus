#pragma once
#include "MiniGame.h"
class RockPaperScissors final : public MiniGame {
public:
    void reset() override; void update(const Input&) override; void render(int, int) const override; const char* title() const override { return "ROCK PAPER SCISSORS"; }
private: int player_ = 0, cpu_ = 0, result_ = 0, playerScore_ = 0, cpuScore_ = 0;
};
