#include "Primitives.h"
#include <GL/glut.h>
#include "TextureManager.h"
namespace render {
void material(Color c, float specular, float shininess) {
    const GLfloat ambient[] = {c.r * .28f, c.g * .28f, c.b * .28f, c.a};
    const GLfloat diffuse[] = {c.r, c.g, c.b, c.a};
    const GLfloat shine[] = {specular, specular, specular, c.a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, shine);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColor4f(c.r, c.g, c.b, c.a);
}
void box(Vec3 center, Vec3 size, Color color) {
    material(color);
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glScalef(size.x, size.y, size.z);
    glutSolidCube(1);
    glPopMatrix();
}
void texturedBox(Vec3 center, Vec3 size, Color color, int textureType) {
    material(color); glEnable(GL_TEXTURE_2D); TextureManager::instance().bind(static_cast<TextureManager::Type>(textureType));
    glPushMatrix(); glTranslatef(center.x,center.y,center.z); glScalef(size.x,size.y,size.z);
    const float v[8][3]={{-.5f,-.5f,-.5f},{.5f,-.5f,-.5f},{.5f,.5f,-.5f},{-.5f,.5f,-.5f},{-.5f,-.5f,.5f},{.5f,-.5f,.5f},{.5f,.5f,.5f},{-.5f,.5f,.5f}};
    const int faces[6][4]={{0,1,2,3},{4,7,6,5},{0,4,5,1},{3,2,6,7},{1,5,6,2},{0,3,7,4}};
    glBegin(GL_QUADS); for(const auto& face:faces) { glTexCoord2f(0,0);glVertex3fv(v[face[0]]);glTexCoord2f(1,0);glVertex3fv(v[face[1]]);glTexCoord2f(1,1);glVertex3fv(v[face[2]]);glTexCoord2f(0,1);glVertex3fv(v[face[3]]); } glEnd();
    glPopMatrix(); glBindTexture(GL_TEXTURE_2D,0); glDisable(GL_TEXTURE_2D);
}
void plane(Vec3 center, Vec3 size, Color color) { box(center, {size.x, .02f, size.z}, color); }
void cylinder(Vec3 center, float radius, float height, Color color) {
    material(color);
    glPushMatrix();
    glTranslatef(center.x, center.y - height * .5f, center.z);
    glRotatef(-90, 1, 0, 0);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, 16, 1);
    gluDisk(quad, 0, radius, 16, 1);
    glTranslatef(0, 0, height);
    gluDisk(quad, 0, radius, 16, 1);
    gluDeleteQuadric(quad);
    glPopMatrix();
}
void stairs(Vec3 foot, float width, float rise, float depth, int count, Color color) {
    const Color treadCol{.92f, .94f, .96f};      // Polished marble/granite stair tread top
    const Color nosingCol{.85f, .42f, .12f};     // High-visibility safety nosing edge strip (SEU terracotta)
    const Color stringerCol{.28f, .30f, .34f};   // Steel/concrete architectural side carriage stringers

    const float totalH = rise * count;
    const float totalD = depth * count;
    const float midY = foot.y + totalH * 0.5f;
    const float midZ = foot.z + totalD * 0.5f;
    const float stringerW = 0.08f;
    const float halfW = width * 0.5f;

    // Structural carriage stringer beams along the staircase sides
    box({foot.x - halfW - stringerW * 0.5f, midY, midZ}, {stringerW, totalH * 0.45f, totalD}, stringerCol);
    box({foot.x + halfW + stringerW * 0.5f, midY, midZ}, {stringerW, totalH * 0.45f, totalD}, stringerCol);

    for (int i = 0; i < count; ++i) {
        const float topY = foot.y + rise * (i + 1);
        const float z = foot.z + depth * (i + 0.5f);
        const float h = rise * (i + 1);

        // Solid riser base block
        box({foot.x, foot.y + h * 0.5f, z}, {width, h, depth}, color);

        // Polished architectural step tread slab on top (slightly overhanging)
        box({foot.x, topY + 0.015f, z}, {width + 0.04f, 0.03f, depth + 0.03f}, treadCol);

        // High-contrast safety nosing strip on the leading edge of tread
        box({foot.x, topY + 0.02f, z - depth * 0.5f + 0.01f}, {width + 0.04f, 0.022f, 0.025f}, nosingCol);
    }
}
void glassPanel(Vec3 center, Vec3 size, Color color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    box(center, size, color);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}
void grid(float halfExtent, float spacing) {
    glDisable(GL_LIGHTING);
    glColor3f(.35f, .4f, .45f);
    glBegin(GL_LINES);
    for (float v = -halfExtent; v <= halfExtent; v += spacing) {
        glVertex3f(v, .005f, -halfExtent); glVertex3f(v, .005f, halfExtent);
        glVertex3f(-halfExtent, .005f, v); glVertex3f(halfExtent, .005f, v);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}
void axes(float length) {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, .2f, .2f); glVertex3f(0, 0, 0); glVertex3f(length, 0, 0);
    glColor3f(.2f, 1, .2f); glVertex3f(0, 0, 0); glVertex3f(0, length, 0);
    glColor3f(.2f, .4f, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, length);
    glEnd();
    glEnable(GL_LIGHTING);
}
void text3d(Vec3 at, const char* value, Color color) {
    glDisable(GL_LIGHTING);
    glColor3f(color.r, color.g, color.b);
    glRasterPos3f(at.x, at.y, at.z);
    while (*value) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *value++);
    glEnable(GL_LIGHTING);
}
void text2d(int x, int y, const char* value, Color color) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(color.r, color.g, color.b);
    glRasterPos2i(x, y);
    while (*value) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *value++);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
}
