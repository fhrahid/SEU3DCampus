#include "GameManager.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdio>
void GameManager::enter() { active_ = true; game_ = -1; }
void GameManager::update(const Input& input) {
    if (!active_) return;
    if (input.pressed(27)) { if (game_ == -1) active_ = false; else game_ = -1; return; }
    if (game_ == -1) {
        if (input.pressed('1')) { ttt_.reset(); game_ = 0; }
        else if (input.pressed('2')) { rps_.reset(); game_ = 1; }
        else if (input.pressed('3')) { game2048_.reset(); game_ = 2; }
        else if (input.pressed('4')) { cube_.reset(); game_ = 3; }
        else if (input.pressed('5')) { ludo_.reset(); game_ = 4; }
        return;
    }
    switch (game_) { case 0: ttt_.update(input); break; case 1: rps_.update(input); break; case 2: game2048_.update(input); break; case 3: cube_.update(input); break; case 4: ludo_.update(input); break; }
}
void GameManager::render(int width, int height) const {
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glDisable(GL_DEPTH_TEST); glDisable(GL_LIGHTING);
    glColor4f(.035f, .05f, .08f, .96f); glBegin(GL_QUADS); glVertex2i(0,0); glVertex2i(width,0); glVertex2i(width,height); glVertex2i(0,height); glEnd();
    if (game_ == -1) {
        render::text2d(55, 90, "GAMING ROOM", {1, .8f, .2f});
        render::text2d(55, 145, "1 Tic-Tac-Toe", {1,1,1}); render::text2d(55, 180, "2 Rock Paper Scissors", {1,1,1}); render::text2d(55, 215, "3 2048", {1,1,1}); render::text2d(55, 250, "4 Rubik's Cube", {1,1,1}); render::text2d(55, 285, "5 Ludo", {1,1,1}); render::text2d(55, height - 45, "Esc: return to campus", {.8f,.8f,.8f});
    } else switch (game_) { case 0: ttt_.render(width, height); break; case 1: rps_.render(width, height); break; case 2: game2048_.render(width, height); break; case 3: cube_.render(width, height); break; case 4: ludo_.render(width, height); break; }
    glEnable(GL_LIGHTING); glEnable(GL_DEPTH_TEST); glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW);
}
