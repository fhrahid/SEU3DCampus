#include "Ludo.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdio>
#include <random>
#include <string>
namespace { std::mt19937 rng(12); }
void Ludo::reset() { for(int& token:tokens_)token=-1; turn_=0; dice_=0; winner_=-1; }
void Ludo::roll() { if(dice_||winner_>=0)return; std::uniform_int_distribution<int>d(1,6); dice_=d(rng); }
void Ludo::update(const Input& input) {
    if(input.pressed('n')){reset();return;} if(winner_>=0)return;
    if (turn_ == 1) { if (input.pressed('n')) reset(); return; }
    if(!dice_ && (input.pressed(' ')||input.pressed('r'))) {roll();return;}
    if(dice_){for(int i=0;i<4;++i)if(input.pressed(static_cast<unsigned char>('1'+i))){ if(tokens_[i]<0){if(dice_==6)tokens_[i]=0;}else if(tokens_[i]+dice_<=20)tokens_[i]+=dice_; dice_=0; if(tokens_[0]>=20&&tokens_[1]>=20&&tokens_[2]>=20&&tokens_[3]>=20)winner_=0; else { turn_=1; cpuTurn(); } break; }}
}
void Ludo::cpuTurn() {
    std::uniform_int_distribution<int>d(1,6); const int rollValue=d(rng); int chosen=-1;
    for(int i=4;i<8;++i) if(tokens_[i]>=0 && tokens_[i]+rollValue<=20){chosen=i;break;}
    if(chosen<0 && rollValue==6) for(int i=4;i<8;++i) if(tokens_[i]<0){chosen=i;break;}
    if(chosen>=0){if(tokens_[chosen]<0)tokens_[chosen]=0;else tokens_[chosen]+=rollValue;}
    if(tokens_[4]>=20&&tokens_[5]>=20&&tokens_[6]>=20&&tokens_[7]>=20) winner_=1; else turn_=0;
}
void Ludo::render(int, int) const {
    char text[100]; render::text2d(55,65,"LUDO",{1,.85f,.25f}); render::text2d(55,100,"Space/R roll | 1-4 choose token | N new game | Esc menu",{1,1,1});
    glDisable(GL_LIGHTING); glColor3f(.15f,.45f,.2f); glBegin(GL_QUADS);glVertex2i(55,145);glVertex2i(455,145);glVertex2i(455,345);glVertex2i(55,345);glEnd(); glColor3f(1,1,1);glBegin(GL_LINE_LOOP);glVertex2i(75,165);glVertex2i(435,165);glVertex2i(435,325);glVertex2i(75,325);glEnd();glEnable(GL_LIGHTING);
    for(int i=0;i<8;++i){int x=95+(i%4)*90,y=i<4?285:215; if(tokens_[i]>=0)y-=std::min(tokens_[i],20)*2; render::text2d(x,y,"●",i<4?render::Color{.9f,.2f,.2f}:render::Color{.2f,.5f,1});}
    std::snprintf(text,sizeof text,"Turn: %s  Dice: %s",turn_?"CPU":"Player",dice_?std::to_string(dice_).c_str():"-"); render::text2d(55,405,text,{1,1,1});
    if(winner_==0)render::text2d(55,450,"PLAYER WINS - N to replay",{1,.8f,.2f}); else if(winner_==1)render::text2d(55,450,"CPU WINS - N to replay",{1,.5f,.2f}); else if(dice_)render::text2d(55,450,"Choose a legal token (a six launches a token)",{1,1,1});
}
