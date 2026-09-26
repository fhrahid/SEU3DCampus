#include "Primitives.h"
#include <GL/glut.h>
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
    for (int i = 0; i < count; ++i) {
        const float h = rise * (i + 1);
        box({foot.x, foot.y + h * .5f, foot.z + depth * (i + .5f)}, {width, h, depth}, color);
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
