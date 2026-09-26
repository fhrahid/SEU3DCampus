#include "RubiksCube.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
void RubiksCube::reset() { for(int f=0;f<6;++f)for(int i=0;i<9;++i)face_[f][i]=f; moves_=0; }
void RubiksCube::turn(int face, bool inverse) {
    int old[9]; for(int i=0;i<9;++i)old[i]=face_[face][i];
    for(int r=0;r<3;++r)for(int c=0;c<3;++c){int dst=inverse?(2-c)*3+r:c*3+(2-r);face_[face][dst]=old[r*3+c];}
    ++moves_;
}
bool RubiksCube::solved() const { for(int f=0;f<6;++f)for(int i=0;i<9;++i)if(face_[f][i]!=f)return false; return true; }
void RubiksCube::update(const Input& input) {
    if(input.pressed('n')){reset();return;}
    if(input.pressed('x')){ for(int i=0;i<12;++i) turn(std::rand()%6,std::rand()%2); return; }
    const bool inverse=input.held('i');
    const char keys[]={'u','d','l','r','f','b'};
    for(int f=0;f<6;++f)if(input.pressed(static_cast<unsigned char>(keys[f])))turn(f,inverse);
}
void RubiksCube::render(int, int) const {
    const float colors[6][3]={{1,1,1},{1,1,0},{1,0,0},{1,.5f,0},{0,0.6f,0},{0,.2f,1}};
    render::text2d(55,65,"RUBIK'S CUBE",{1,.85f,.25f}); render::text2d(55,100,"U D L R F B turn | hold I inverse | X scramble | N reset | Esc menu",{1,1,1});
    const int ox[6]={145,145,55,235,145,325}, oy[6]={145,235,235,235,325,235};
    for(int f=0;f<6;++f)for(int i=0;i<9;++i){int x=ox[f]+(i%3)*28,y=oy[f]+(i/3)*28;glDisable(GL_LIGHTING);glColor3fv(colors[face_[f][i]]);glBegin(GL_QUADS);glVertex2i(x,y);glVertex2i(x+24,y);glVertex2i(x+24,y+24);glVertex2i(x,y+24);glEnd();glEnable(GL_LIGHTING);}
    char status[80]; std::snprintf(status,sizeof status,"Moves: %d   %s",moves_,solved()?"SOLVED":"Scramble or turn a face"); render::text2d(55,440,status,{1,1,1});
}
