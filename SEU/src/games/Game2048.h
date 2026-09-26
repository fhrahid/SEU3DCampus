#pragma once
#include "MiniGame.h"
class Game2048 final : public MiniGame {
public:
    void reset() override; void update(const Input&) override; void render(int, int) const override; const char* title() const override { return "2048"; }
private: int tiles_[4][4]{}; int score_ = 0; bool won_ = false, over_ = false; void spawn(); bool move(int dx, int dz); bool hasMoves() const;
};
