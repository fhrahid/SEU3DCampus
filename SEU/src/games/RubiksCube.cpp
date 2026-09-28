#include "RubiksCube.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdio>
#include <random>
namespace { std::mt19937 rng(std::random_device{}()); }
void RubiksCube::reset() { for(int f=0;f<6;++f)for(int i=0;i<9;++i)face_[f][i]=f; moves_=0; }
void RubiksCube::turn(int face, bool inverse) {
    const auto rotFace = [this](int f) {
        int old[9]; for(int i=0;i<9;++i) old[i]=face_[f][i];
        for(int r=0;r<3;++r) for(int c=0;c<3;++c) face_[f][c*3+(2-r)]=old[r*3+c];
    };
    const auto cycle4 = [this](int f0, int i0, int i1, int i2,
                               int f1, int j0, int j1, int j2,
                               int f2, int k0, int k1, int k2,
                               int f3, int l0, int l1, int l2) {
        int t0 = face_[f3][l0], t1 = face_[f3][l1], t2 = face_[f3][l2];
        face_[f3][l0] = face_[f2][k0]; face_[f3][l1] = face_[f2][k1]; face_[f3][l2] = face_[f2][k2];
        face_[f2][k0] = face_[f1][j0]; face_[f2][k1] = face_[f1][j1]; face_[f2][k2] = face_[f1][j2];
        face_[f1][j0] = face_[f0][i0]; face_[f1][j1] = face_[f0][i1]; face_[f1][j2] = face_[f0][i2];
        face_[f0][i0] = t0;            face_[f0][i1] = t1;            face_[f0][i2] = t2;
    };
    const auto sideTurn = [&](int f) {
        rotFace(f);
        switch(f) {
            // 0: U, 1: D, 2: L, 3: R, 4: F, 5: B
            case 0: cycle4(5,0,1,2,  3,0,1,2,  4,0,1,2,  2,0,1,2); break;
            case 1: cycle4(4,6,7,8,  3,6,7,8,  5,6,7,8,  2,6,7,8); break;
            case 2: cycle4(0,0,3,6,  4,0,3,6,  1,0,3,6,  5,8,5,2); break;
            case 3: cycle4(0,2,5,8,  5,6,3,0,  1,2,5,8,  4,2,5,8); break;
            case 4: cycle4(0,6,7,8,  3,0,3,6,  1,2,1,0,  2,8,5,2); break;
            case 5: cycle4(0,2,1,0,  2,0,3,6,  1,6,7,8,  3,8,5,2); break;
        }
    };
    const int count = inverse ? 3 : 1;
    for (int c = 0; c < count; ++c) sideTurn(face);
    ++moves_;
}
bool RubiksCube::solved() const { for(int f=0;f<6;++f)for(int i=0;i<9;++i)if(face_[f][i]!=f)return false; return true; }
void RubiksCube::update(const Input& input) {
    if(input.pressed('n')){reset();return;}
    if(input.pressed('x')){
        std::uniform_int_distribution<int> face(0, 5);
        std::uniform_int_distribution<int> direction(0, 1);
        for(int i=0;i<12;++i) turn(face(rng), direction(rng));
        return;
    }
    const bool inverse=input.held('i');
    const char keys[]={'u','d','l','r','f','b'};
    for(int f=0;f<6;++f)if(input.pressed(static_cast<unsigned char>(keys[f])))turn(f,inverse);
}
void RubiksCube::render(int, int) const {
    const float colors[6][3]={{1,1,1},{1,1,0},{1,0,0},{1,.5f,0},{0,0.6f,0},{0,.2f,1}};
    render::text2d(55,65,"RUBIK'S CUBE",{1,.85f,.25f}); render::text2d(55,100,"U D L R F B turn | hold I inverse | X scramble | N reset | Esc menu",{1,1,1});
    // Standard unfolded cross net:
    // Row 0: U (f=0)
    // Row 1: L (f=2), F (f=4), R (f=3), B (f=5)
    // Row 2: D (f=1)
    const int ox[6]={145,145,55,235,145,325}, oy[6]={145,325,235,235,235,235};
    for(int f=0;f<6;++f)for(int i=0;i<9;++i){int x=ox[f]+(i%3)*28,y=oy[f]+(i/3)*28;glDisable(GL_LIGHTING);glColor3fv(colors[face_[f][i]]);glBegin(GL_QUADS);glVertex2i(x,y);glVertex2i(x+24,y);glVertex2i(x+24,y+24);glVertex2i(x,y+24);glEnd();glEnable(GL_LIGHTING);}
    char status[80]; std::snprintf(status,sizeof status,"Moves: %d   %s",moves_,solved()?"SOLVED":"Scramble or turn a face"); render::text2d(55,440,status,{1,1,1});
}
