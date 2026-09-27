#pragma once
#include "MiniGame.h"
#include <string>
class Ludo final : public MiniGame {
public:
    void reset() override; void update(const Input&) override; void render(int, int) const override; const char* title() const override { return "LUDO"; }
private:
    int tokens_[8]{-1,-1,-1,-1,-1,-1,-1,-1};
    int turn_ = 0, dice_ = 0, winner_ = -1;
    std::string statusMsg_;
    void roll();
    void cpuTurn();
};
