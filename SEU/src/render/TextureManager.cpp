#include "TextureManager.h"
#include <GL/glut.h>
TextureManager& TextureManager::instance() { static TextureManager manager; return manager; }
void TextureManager::initialize() {
    if (initialized_) return;
    glGenTextures(5, textures_);
    for (int t=0;t<5;++t) {
        unsigned char pixels[8*8*3];
        for(int y=0;y<8;++y)for(int x=0;x<8;++x){
            const int i=(y*8+x)*3;
            if (t == 0) {
                // Subtle white marble: broad tile variation plus fine veins.
                const bool grout = x == 0 || y == 0;
                const bool vein = ((x * 3 + y * 5) % 11) == 0 || ((x + y * 2) % 13) == 0;
                const unsigned char a = grout ? 168 : (vein ? 190 : static_cast<unsigned char>(232 + ((x * 7 + y * 3) % 18)));
                pixels[i]=a; pixels[i+1]=static_cast<unsigned char>(a + (a < 210 ? 4 : 0)); pixels[i+2]=static_cast<unsigned char>(a + (a < 210 ? 7 : 0));
            } else if (t == 1) {
                const unsigned char a = ((x+y)&1) ? 226 : 246;
                pixels[i]=a; pixels[i+1]=a; pixels[i+2]=a;
            } else if (t == 2) {
                const unsigned char a = ((x+y)&1) ? 74 : 128;
                pixels[i]=a; pixels[i+1]=static_cast<unsigned char>(a*.8f); pixels[i+2]=static_cast<unsigned char>(a*.55f);
            } else if (t == 3) {
                const unsigned char a = ((x+y)&1) ? 38 : 78;
                pixels[i]=a; pixels[i+1]=static_cast<unsigned char>(a*.8f); pixels[i+2]=static_cast<unsigned char>(a*.55f);
            } else {
                // Repeating running-bond red brick with dark mortar lines.
                const bool mortar = (y == 0 || y == 4 || x == ((y < 4) ? 0 : 4));
                pixels[i] = mortar ? 45 : 174;
                pixels[i+1] = mortar ? 22 : 58;
                pixels[i+2] = mortar ? 18 : 42;
            }
        }
        glBindTexture(GL_TEXTURE_2D,textures_[t]); glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,8,8,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
    }
    glBindTexture(GL_TEXTURE_2D,0); initialized_=true;
}
void TextureManager::bind(Type type) const { glBindTexture(GL_TEXTURE_2D,textures_[static_cast<int>(type)]); }
