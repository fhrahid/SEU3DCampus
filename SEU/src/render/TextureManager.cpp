#include "TextureManager.h"
#include <GL/glut.h>
TextureManager& TextureManager::instance() { static TextureManager manager; return manager; }
void TextureManager::initialize() {
    if (initialized_) return;
    glGenTextures(4, textures_);
    for (int t=0;t<4;++t) {
        unsigned char pixels[8*8*3];
        for(int y=0;y<8;++y)for(int x=0;x<8;++x){const bool checker=((x+y)&1)!=0; int i=(y*8+x)*3; unsigned char a=0;
            if (t == 0) a = checker ? 218 : 246;          // white ceramic floor tiles
            else if (t == 1) a = checker ? 226 : 246;     // white wall/concrete finish
            else if (t == 2) a = checker ? 74 : 128;      // warm wood
            else a = checker ? 38 : 78;                   // dark sign backing
            pixels[i]=a; pixels[i+1]=static_cast<unsigned char>(t < 2 ? a : a*.8f); pixels[i+2]=static_cast<unsigned char>(t < 2 ? a : a*.55f);}
        glBindTexture(GL_TEXTURE_2D,textures_[t]); glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,8,8,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
    }
    glBindTexture(GL_TEXTURE_2D,0); initialized_=true;
}
void TextureManager::bind(Type type) const { glBindTexture(GL_TEXTURE_2D,textures_[static_cast<int>(type)]); }
