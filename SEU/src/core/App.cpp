#include "App.h"
#include "Config.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <algorithm>
#include <cstdlib>
App& App::instance() { static App app; return app; }
int App::run(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width_, height_);
    glutCreateWindow("Southeast University 3D Campus");
    glEnable(GL_DEPTH_TEST); glEnable(GL_NORMALIZE); glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
    glClearColor(.13f, .19f, .27f, 1);
    glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyDownCallback); glutKeyboardUpFunc(keyUpCallback);
    glutSpecialFunc(specialDownCallback); glutSpecialUpFunc(specialUpCallback);
    glutMouseFunc(mouseCallback); glutPassiveMotionFunc(motionCallback); glutMotionFunc(motionCallback);
    lastTimeMs_ = glutGet(GLUT_ELAPSED_TIME); glutTimerFunc(16, timerCallback, 0);
    glutMainLoop(); return EXIT_SUCCESS;
}
void App::update(float dt) {
    if (input_.pressed(27)) { std::exit(EXIT_SUCCESS); }
    if (input_.pressed('g')) debug_ = !debug_;
    if (input_.pressed('t')) demo_ = !demo_;
    if (input_.pressed('m')) {
        mouseCaptured_ = !mouseCaptured_;
        glutSetCursor(mouseCaptured_ ? GLUT_CURSOR_NONE : GLUT_CURSOR_INHERIT);
        if (mouseCaptured_) { ignoreMouseWarp_ = true; glutWarpPointer(width_ / 2, height_ / 2); }
    }
    const float speed = (input_.held(16) ? config::fastCameraSpeed : config::cameraSpeed) * dt;
    if (demo_) {
        if (input_.specialHeld(GLUT_KEY_LEFT)) demoPosition_.x -= speed;
        if (input_.specialHeld(GLUT_KEY_RIGHT)) demoPosition_.x += speed;
        if (input_.specialHeld(GLUT_KEY_UP)) demoPosition_.z += speed;
        if (input_.specialHeld(GLUT_KEY_DOWN)) demoPosition_.z -= speed;
        if (input_.held('q')) demoAngle_ += 75 * dt;
        if (input_.held('e')) demoAngle_ -= 75 * dt;
        if (input_.held('+') || input_.held('=')) demoScale_ = std::min(3.0f, demoScale_ + dt);
        if (input_.held('-')) demoScale_ = std::max(.25f, demoScale_ - dt);
    } else {
        Vec3 forward = camera_.forward(); forward.y = 0;
        const Vec3 right = camera_.right();
        if (input_.held('w')) camera_.position = camera_.position + forward * speed;
        if (input_.held('s')) camera_.position = camera_.position - forward * speed;
        if (input_.held('d')) camera_.position = camera_.position + right * speed;
        if (input_.held('a')) camera_.position = camera_.position - right * speed;
        if (input_.held(' ')) camera_.position.y += speed;
        if (input_.held('c')) camera_.position.y -= speed;
    }
    input_.endFrame();
}
void App::setupLighting() {
    const GLfloat ambient[] = {.22f, .24f, .27f, 1};
    const GLfloat sun[] = {.88f, .85f, .78f, 1};
    const GLfloat direction[] = {-1, 2, -1, 0};
    glEnable(GL_LIGHTING); glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun); glLightfv(GL_LIGHT0, GL_SPECULAR, sun); glLightfv(GL_LIGHT0, GL_POSITION, direction);
}
void App::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity(); camera_.applyView(); setupLighting();
    render::plane({0, -.03f, 0}, {32, 0, 32}, {.26f, .3f, .34f});
    if (debug_) { render::grid(16, 1); render::axes(3); }
    glPushMatrix(); glTranslatef(demoPosition_.x, demoPosition_.y, demoPosition_.z); glRotatef(demoAngle_, 0, 1, 0); glScalef(demoScale_, demoScale_, demoScale_);
    render::box({0, 0, 0}, {1.3f, 1.3f, 1.3f}, {.88f, .48f, .19f});
    render::cylinder({0, .85f, 0}, .23f, .4f, {.32f, .8f, .92f}); glPopMatrix();
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, width_, height_, 0);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    render::text2d(16, 28, demo_ ? "TRANSFORM: arrows move, Q/E rotate, +/- scale, T exit" : "FREE CAMERA: WASD move, Space/C vertical, M mouse, G grid, T transform", {1, 1, 1});
    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glutSwapBuffers();
}
void App::reshape(int width, int height) {
    width_ = std::max(1, width); height_ = std::max(1, height); glViewport(0, 0, width_, height_);
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(config::fov, static_cast<double>(width_) / height_, config::nearPlane, config::farPlane); glMatrixMode(GL_MODELVIEW);
}
void App::mouseMove(int x, int y) {
    if (!mouseCaptured_ || demo_) return;
    const int cx = width_ / 2, cy = height_ / 2;
    if (ignoreMouseWarp_) { ignoreMouseWarp_ = false; return; }
    if (x == cx && y == cy) return;
    camera_.look((x - cx) * config::mouseSensitivity, (y - cy) * config::mouseSensitivity); ignoreMouseWarp_ = true; glutWarpPointer(cx, cy);
}
void App::displayCallback() { instance().display(); }
void App::reshapeCallback(int w, int h) { instance().reshape(w, h); }
void App::timerCallback(int) { App& app = instance(); const int now = glutGet(GLUT_ELAPSED_TIME); const float dt = std::min(config::maxFrameStep, std::max(0, now - app.lastTimeMs_) * .001f); app.lastTimeMs_ = now; app.update(dt); glutPostRedisplay(); glutTimerFunc(16, timerCallback, 0); }
void App::keyDownCallback(unsigned char k, int, int) { instance().input_.keyDown(k); }
void App::keyUpCallback(unsigned char k, int, int) { instance().input_.keyUp(k); }
void App::specialDownCallback(int k, int, int) { instance().input_.specialDown(k); }
void App::specialUpCallback(int k, int, int) { instance().input_.specialUp(k); }
void App::mouseCallback(int button, int state, int, int) { if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !instance().mouseCaptured_) { instance().mouseCaptured_ = true; glutSetCursor(GLUT_CURSOR_NONE); instance().ignoreMouseWarp_ = true; glutWarpPointer(instance().width_ / 2, instance().height_ / 2); } }
void App::motionCallback(int x, int y) { instance().mouseMove(x, y); }
