#pragma once
#include "TicTacToe.h"
#include "RockPaperScissors.h"
#include "Game2048.h"
#include "RubiksCube.h"
#include "Ludo.h"
class GameManager {
public:
    bool active() const { return active_; }
    bool playing() const { return game_ != -1; }
    void enter();
    void update(const Input& input);
    void render(int width, int height) const;
private:
    bool active_ = false; int game_ = -1;
    TicTacToe ttt_; RockPaperScissors rps_; Game2048 game2048_; RubiksCube cube_; Ludo ludo_;
};
