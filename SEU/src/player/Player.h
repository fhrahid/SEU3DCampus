#pragma once
#include "../render/Camera.h"
class Input;
class CollisionWorld;
class Player {
public:
    enum class State { Idle, Walk, Run, Jump, Fall, Stair, Sit };
    Vec3 position{-1.8f, 0, 6.3f};
    float yaw = 90, pitch = 0;
    float verticalVelocity = 0;
    bool grounded = true;
    State state = State::Idle;
    bool seated = false;
    void update(const Input& input, float dt, const CollisionWorld& world);
    void look(float dx, float dy);
    Vec3 eyePosition() const;
    const char* stateName() const;
private:
    float walkSpeed_ = 3.2f;
    float runSpeed_ = 6.0f;
    float eyeHeight_ = 1.7f;
    float stairHeight(float x, float z) const;
};
