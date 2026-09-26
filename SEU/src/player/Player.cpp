#include "Player.h"
#include "../core/Input.h"
#include "../physics/CollisionWorld.h"
#include <algorithm>
#include <cmath>
namespace { constexpr float pi = 3.1415926535f; }
float Player::stairHeight(float x, float z) const {
    if (x < -5.5f || x > 2.0f || z < 7.9f || z > 10.65f) return z >= 10.65f ? 1.2f : 0.0f;
    const int step = std::max(0, std::min(7, static_cast<int>((z - 7.9f) / .34f)));
    return .15f * (step + 1);
}
void Player::look(float dx, float dy) {
    yaw += dx; pitch = std::max(-85.0f, std::min(85.0f, pitch - dy));
}
void Player::update(const Input& input, float dt, const CollisionWorld& world) {
    if (seated) { state = State::Sit; return; }
    Vec3 forward{std::cos(yaw * pi / 180), 0, std::sin(yaw * pi / 180)};
    Vec3 right{std::cos((yaw - 90) * pi / 180), 0, std::sin((yaw - 90) * pi / 180)};
    Vec3 move{};
    if (input.held('w')) move = move + forward;
    if (input.held('s')) move = move - forward;
    if (input.held('d')) move = move + right;
    if (input.held('a')) move = move - right;
    const float length = std::sqrt(move.x * move.x + move.z * move.z);
    const bool moving = length > .001f;
    const bool running = input.held(16) || input.held('r');
    const float speed = running ? runSpeed_ : walkSpeed_;
    if (moving) { move = move * (1.0f / length); position = world.move(position, move * (speed * dt), .34f); }
    const float targetFloor = stairHeight(position.x, position.z);
    if (input.pressed(' ') && grounded) { verticalVelocity = 5.2f; grounded = false; state = State::Jump; }
    if (!grounded) {
        verticalVelocity -= 13.0f * dt;
        position.y += verticalVelocity * dt;
        if (position.y <= targetFloor) { position.y = targetFloor; verticalVelocity = 0; grounded = true; }
    } else {
        position.y = targetFloor;
        if (std::fabs(targetFloor - position.y) > .01f) state = State::Stair;
    }
    if (!grounded) state = verticalVelocity > 0 ? State::Jump : State::Fall;
    else if (moving && position.z >= 7.9f && position.z <= 10.7f) state = State::Stair;
    else if (moving) state = running ? State::Run : State::Walk;
    else state = State::Idle;
}
Vec3 Player::eyePosition() const { return {position.x, position.y + eyeHeight_, position.z}; }
const char* Player::stateName() const {
    switch (state) { case State::Walk: return "WALK"; case State::Run: return "RUN"; case State::Jump: return "JUMP"; case State::Fall: return "FALL"; case State::Stair: return "STAIR"; case State::Sit: return "SIT"; default: return "IDLE"; }
}
