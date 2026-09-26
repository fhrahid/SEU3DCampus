#pragma once
#include "Input.h"
#include "../render/Camera.h"
#include "../world/CampusLayout.h"
#include "../player/Player.h"
#include "../physics/CollisionWorld.h"
#include "../interaction/InteractionSystem.h"
#include "../games/GameManager.h"
class App {
public:
    static App& instance();
    int run(int argc, char** argv);
private:
    Input input_;
    Player player_;
    CollisionWorld collisionWorld_;
    InteractionSystem interaction_;
    GameManager games_;
    Camera camera_;
    int width_ = 1280, height_ = 720, lastTimeMs_ = 0;
    bool debug_ = true, demo_ = false, topDown_ = false, labels_ = true, mouseCaptured_ = false, ignoreMouseWarp_ = false;
    Vec3 demoPosition_{0, 1, 4};
    float demoAngle_ = 0, demoScale_ = 1;
    App() = default;
    void update(float dt);
    void display();
    void reshape(int width, int height);
    void mouseMove(int x, int y);
    void setupLighting();
    static void displayCallback();
    static void reshapeCallback(int width, int height);
    static void timerCallback(int value);
    static void keyDownCallback(unsigned char key, int, int);
    static void keyUpCallback(unsigned char key, int, int);
    static void specialDownCallback(int key, int, int);
    static void specialUpCallback(int key, int, int);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
};
