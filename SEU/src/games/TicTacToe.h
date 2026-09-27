#pragma once
#include "MiniGame.h"
class TicTacToe final : public MiniGame {
public:
    void reset() override; void update(const Input&) override; void render(int, int) const override; const char* title() const override { return "TIC-TAC-TOE"; }
private:
    int board_[9]{}; int cursor_ = 0; int turn_ = 1; int result_ = 0;
    int winner() const;
};
