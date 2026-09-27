#pragma once
#include "MiniGame.h"
class RubiksCube final : public MiniGame {
public:
    void reset() override; void update(const Input&) override; void render(int, int) const override; const char* title() const override { return "RUBIK'S CUBE"; }
private: int face_[6][9]{}; int moves_ = 0; void turn(int face, bool inverse); bool solved() const;
};
