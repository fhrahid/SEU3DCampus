#include "TicTacToe.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdio>
void TicTacToe::reset() { for (int& cell : board_) cell = 0; cursor_ = 0; turn_ = 1; result_ = 0; }
int TicTacToe::winner() const {
    const int lines[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for (const auto& line : lines) if (board_[line[0]] && board_[line[0]] == board_[line[1]] && board_[line[1]] == board_[line[2]]) return board_[line[0]];
    for (int cell : board_) if (!cell) return 0;
    return 3;
}
void TicTacToe::update(const Input& input) {
    if (input.pressed('n')) { reset(); return; }
    if (result_) return;
    // Arrow or WASD keys navigate cursor; 1-9 directly jumps to cell.
    if ((input.specialPressed(GLUT_KEY_LEFT) || input.pressed('a')) && cursor_ % 3) --cursor_;
    if ((input.specialPressed(GLUT_KEY_RIGHT) || input.pressed('d')) && cursor_ % 3 < 2) ++cursor_;
    if ((input.specialPressed(GLUT_KEY_UP) || input.pressed('w')) && cursor_ >= 3) cursor_ -= 3;
    if ((input.specialPressed(GLUT_KEY_DOWN) || input.pressed('s')) && cursor_ < 6) cursor_ += 3;
    for (int i = 0; i < 9; ++i) if (input.pressed(static_cast<unsigned char>('1' + i))) cursor_ = i;
    if (input.pressed(' ') || input.pressed(13)) {
        if (!board_[cursor_]) { board_[cursor_] = turn_; result_ = winner(); if (!result_) turn_ = 3 - turn_; }
    }
}
void TicTacToe::render(int, int) const {
    render::text2d(55, 75, "TIC-TAC-TOE", {1,.85f,.25f});
    render::text2d(55, 110, "Two players: WASD/arrows or 1-9 select, Space/Enter place, N new, Esc menu", {1,1,1});
    glDisable(GL_LIGHTING); glColor3f(.8f,.85f,.9f);
    glBegin(GL_LINES);
    for (int i=1;i<3;++i) { glVertex2i(55+i*90,150); glVertex2i(55+i*90,420); glVertex2i(55,150+i*90); glVertex2i(325,150+i*90); }
    glEnd(); glEnable(GL_LIGHTING);
    for (int i=0;i<9;++i) {
        const int x=55+(i%3)*90, y=150+(i/3)*90;
        if (i==cursor_) { glDisable(GL_LIGHTING); glColor3f(1,.75f,.2f); glBegin(GL_LINE_LOOP); glVertex2i(x+4,y+4); glVertex2i(x+86,y+4); glVertex2i(x+86,y+86); glVertex2i(x+4,y+86); glEnd(); glEnable(GL_LIGHTING); }
        if (board_[i]) render::text2d(x+38,y+52,board_[i]==1?"X":"O", {1,1,1});
    }
    char status[80];
    if (result_==3) std::snprintf(status,sizeof status,"DRAW - N to replay");
    else if (result_) std::snprintf(status,sizeof status,"PLAYER %d WINS - N to replay",result_);
    else std::snprintf(status,sizeof status,"PLAYER %d TURN",turn_);
    render::text2d(55,470,status,{1,1,1});
}
