#include "Game2048.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <algorithm>
#include <cstdio>
#include <random>
namespace { std::mt19937 rng(2048); }
void Game2048::reset() { for (auto& row : tiles_) for (int& cell : row) cell=0; score_=0; won_=over_=false; spawn(); spawn(); }
void Game2048::spawn() {
    int empty[16], n=0; for(int z=0;z<4;++z) for(int x=0;x<4;++x) if(!tiles_[z][x]) empty[n++]=z*4+x;
    if (!n) return;
    std::uniform_int_distribution<int> pick(0,n-1);
    std::uniform_int_distribution<int> value(0,9);
    int p=empty[pick(rng)];
    tiles_[p/4][p%4]=value(rng)?2:4;
}
bool Game2048::move(int dx, int dz) {
    bool changed=false;
    for(int line=0;line<4;++line) {
        int values[4]{}, count=0;
        for(int i=0;i<4;++i){ int x=dx? (dx>0?3-i:i):line; int z=dz? (dz>0?3-i:i):line; int v=tiles_[z][x]; if(v) values[count++]=v; }
        int out[4]{}, at=0;
        for(int i=0;i<count;++i){ if(i+1<count && values[i]==values[i+1]){out[at++]=values[i]*2; score_+=values[i]*2; ++i;} else out[at++]=values[i]; }
        for(int i=0;i<4;++i){ int x=dx?(dx>0?3-i:i):line; int z=dz?(dz>0?3-i:i):line; if(tiles_[z][x]!=out[i]) changed=true; tiles_[z][x]=out[i]; }
    }
    if(changed){ spawn(); for(auto& row:tiles_)for(int v:row)if(v>=2048)won_=true; over_=!hasMoves(); }
    return changed;
}
bool Game2048::hasMoves() const { for(int z=0;z<4;++z)for(int x=0;x<4;++x){if(!tiles_[z][x])return true; if(x<3&&tiles_[z][x]==tiles_[z][x+1])return true; if(z<3&&tiles_[z][x]==tiles_[z+1][x])return true;} return false; }
void Game2048::update(const Input& input) {
    if(input.pressed('n')){reset();return;} if(won_||over_) return;
    if(input.pressed('a')||input.specialPressed(GLUT_KEY_LEFT))move(-1,0); else if(input.pressed('d')||input.specialPressed(GLUT_KEY_RIGHT))move(1,0); else if(input.pressed('w')||input.specialPressed(GLUT_KEY_UP))move(0,-1); else if(input.pressed('s')||input.specialPressed(GLUT_KEY_DOWN))move(0,1);
}
void Game2048::render(int, int) const {
    char line[80]; render::text2d(55,75,title(),{1,.85f,.25f}); render::text2d(55,110,"Arrows/WASD move | N new game | Esc menu",{1,1,1}); std::snprintf(line,sizeof line,"Score: %d",score_); render::text2d(55,145,line,{1,1,1});
    for(int z=0;z<4;++z)for(int x=0;x<4;++x){ int px=55+x*78, py=175+z*78; glDisable(GL_LIGHTING); glColor3f(.2f+.06f*std::min(10,tiles_[z][x]),.25f,.32f); glBegin(GL_QUADS); glVertex2i(px,py);glVertex2i(px+70,py);glVertex2i(px+70,py+70);glVertex2i(px,py+70);glEnd(); glEnable(GL_LIGHTING); if(tiles_[z][x]){std::snprintf(line,sizeof line,"%d",tiles_[z][x]);render::text2d(px+25,py+42,line,{1,1,1});} }
    if(won_)render::text2d(55,510,"2048 reached! N to replay",{1,.8f,.2f}); else if(over_)render::text2d(55,510,"GAME OVER - N to replay",{1,.3f,.3f});
}
