#pragma once
#include "Input.h"
#include "../render/Camera.h"
#include "../world/CampusLayout.h"
#include "../player/Player.h"
#include "../physics/CollisionWorld.h"
#include "../interaction/InteractionSystem.h"
#include "../games/GameManager.h"
#include "../chat/SEUGPTChat.h"

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
    SEUGPTChat chat_;
    Camera camera_;
    int width_ = 1280, height_ = 720, lastTimeMs_ = 0;
    bool debug_ = false, demo_ = false, topDown_ = false, labels_ = true, panorama_ = false, facadeView_ = false, mouseCaptured_ = false, ignoreMouseWarp_ = false;
    bool nightMode_ = false;
    Vec3 demoPosition_{0, 1, 4};
    float demoAngle_ = 0, demoScale_ = 1;
    float rotationAngle_ = 0, orbitAngle_ = 0;

    // Drone Mode State
    bool droneChase_ = false;
    Vec3 dronePos_{0.0f, 18.0f, -14.0f};
    float droneYaw_ = 90.0f, dronePitch_ = -16.0f;
    float droneSpeed_ = 14.0f;
    float chaseDistance_ = 10.0f, chaseHeight_ = 4.5f, chaseYaw_ = 90.0f, chasePitch_ = -18.0f;

    // Elevator / Lift System
    enum class LiftPhase { Idle, Opening, Open, Closing, Traveling };
    bool inLiftArea(const Vec3& pos) const;
    bool inLiftCabin(const Vec3& pos) const;
    int floorAtPlayer() const;
    void handleElevator(int floor);
    void updateLift(float dt);
    void syncLiftWorld();
    float floorY(int floor) const;
    std::string elevatorNotification_;
    float elevatorNotifyTimer_ = 0.0f;
    LiftPhase liftPhase_ = LiftPhase::Idle;
    float liftFloorPosition_ = 4.0f;
    float liftDoorAmount_ = 0.0f;
    float liftPhaseTimer_ = 0.0f;
    int liftTargetFloor_ = 4;
    bool liftRiding_ = false;

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
