#include "Player.h"
#include "../core/Input.h"
#include "../physics/CollisionWorld.h"
#include <algorithm>
#include <cmath>

namespace { constexpr float pi = 3.1415926535f; }

float Player::floorHeight(float x, float y, float z) const {
    // 1. Floor 4: Executive Boardroom & Sky Garden Level (y >= 11.2f)
    if (y >= 11.2f) {
        if (x >= -24.0f && x <= 16.5f && z >= 9.5f && z <= 40.0f) {
            return 13.2f; // Solid Fourth Floor & Sky Terrace slab
        }
    }

    // 2. Floor 3: Grand Auditorium & Innovation Floor (y >= 7.2f)
    if (y >= 7.2f) {
        if (x >= -24.0f && x <= 16.5f && z >= 9.5f && z <= 40.0f) {
            // Central Atrium Void opening down to Ground Floor
            if (x > -7.0f && x < 7.0f && z > 18.0f && z < 24.0f) {
                return 1.2f;
            }
            return 9.2f; // Solid Third Floor slab
        }
    }

    // 3. Stair 3: Primary Grand Staircase to Second Floor (x in [1.4, 4.6], z in [24.4, 30.6])
    if (x >= 1.4f && x <= 4.6f && z >= 24.4f && z <= 30.6f && y < 7.0f) {
        const float t = std::max(0.0f, std::min(1.0f, (z - 24.5f) / 5.6f));
        return 1.2f + t * 4.0f; // Climbs smoothly from 1.2f up to 5.2f
    }

    // 4. Stair 2: Secondary Staircase to Second Floor (x in [9.5, 15.5], z in [26.5, 30.5])
    if (x >= 9.5f && x <= 15.5f && z >= 26.5f && z <= 30.5f && y < 7.0f) {
        const float t = std::max(0.0f, std::min(1.0f, (z - 26.5f) / 4.0f));
        return 1.2f + t * 4.0f; // Climbs from 1.2f up to 5.2f
    }

    // 5. Floor 2: Academic & Library Level (y >= 3.5f)
    if (y >= 3.5f) {
        if (x >= -24.0f && x <= 16.5f && z >= 9.5f && z <= 40.0f) {
            // Central Atrium Void (opening down to Ground Floor lobby)
            if (x > -7.0f && x < 7.0f && z > 18.0f && z < 24.0f) {
                return 1.2f;
            }
            // Stair 3 well opening down to Ground Floor
            if (x > 1.4f && x < 4.6f && z >= 24.0f && z <= 30.4f) {
                const float t = std::max(0.0f, std::min(1.0f, (z - 24.5f) / 5.6f));
                return 1.2f + t * 4.0f;
            }
            return 5.2f; // Solid Second Floor tile slab
        }
    }

    // 6. Stair 1: Front Entrance Ramp from outdoor street level
    if (x >= -12.0f && x <= 2.8f && z >= 8.17f && z <= 9.9f && y < 2.5f) {
        const int step = std::max(0, std::min(7, static_cast<int>((z - 8.17f) / .21f)));
        return .15f * (step + 1);
    }

    // 7. Ground Floor Interior (Floor 1)
    if (z >= 9.9f && x >= -24.0f && x <= 23.5f && z <= 40.0f) {
        return 1.2f;
    }

    // 8. Outside Ground Level
    return 0.0f;
}

void Player::reset() {
    position = {-1.8f, 0, 6.3f};
    yaw = 90.0f;
    pitch = 0.0f;
    verticalVelocity = 0.0f;
    grounded = true;
    seated = false;
    state = State::Idle;
}

void Player::look(float dx, float dy) {
    yaw += dx;
    pitch = std::max(-85.0f, std::min(85.0f, pitch - dy));
}

void Player::update(const Input& input, float dt, const CollisionWorld& world) {
    if (seated) { state = State::Sit; return; }

    Vec3 forward{std::cos(yaw * pi / 180), 0, std::sin(yaw * pi / 180)};
    // World +X is the reference plan's right side. Rendering mirrors the
    // world for the first-person view, so this vector becomes screen-right.
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

    if (moving) {
        move = move * (1.0f / length);
        position = world.move(position, move * (speed * dt), .34f);
    }

    const float targetFloor = floorHeight(position.x, position.y, position.z);

    if (input.pressed(' ') && grounded) {
        verticalVelocity = 5.2f;
        grounded = false;
        state = State::Jump;
    }

    if (!grounded) {
        verticalVelocity -= 13.0f * dt;
        position.y += verticalVelocity * dt;
        if (position.y <= targetFloor) {
            position.y = targetFloor;
            verticalVelocity = 0;
            grounded = true;
        }
    } else {
        if (targetFloor > position.y) {
            position.y = targetFloor;
        } else if (position.y - targetFloor > 0.65f) {
            grounded = false; // Stepped off an edge or balcony
        } else {
            position.y = targetFloor;
        }
    }

    const bool onStair1 = position.x >= -12.0f && position.x <= 2.8f && position.z >= 8.17f && position.z <= 9.9f && position.y < 2.0f;
    const bool onStair3 = position.x >= 1.5f && position.x <= 4.5f && position.z >= 24.4f && position.z <= 30.2f;
    const bool onStair2 = position.x >= 9.5f && position.x <= 15.5f && position.z >= 26.5f && position.z <= 30.5f;
    const bool onStairs = onStair1 || onStair3 || onStair2;

    if (!grounded) state = verticalVelocity > 0 ? State::Jump : State::Fall;
    else if (moving && onStairs) state = State::Stair;
    else if (moving) state = running ? State::Run : State::Walk;
    else state = State::Idle;
}

Vec3 Player::eyePosition() const {
    const float h = seated ? 1.1f : eyeHeight_;  // Lower view when seated
    return {position.x, position.y + h, position.z};
}

const char* Player::stateName() const {
    if (seated) return "SIT";
    const int fl = position.y >= 11.2f ? 4 : (position.y >= 7.2f ? 3 : (position.y >= 3.5f ? 2 : 1));
    switch (state) {
        case State::Walk:
            if (fl == 4) return "FLOOR 4 [SKY TERRACE] - WALK";
            if (fl == 3) return "FLOOR 3 [AUDITORIUM] - WALK";
            if (fl == 2) return "FLOOR 2 [LIBRARY] - WALK";
            return "FLOOR 1 [GROUND] - WALK";
        case State::Run:
            if (fl == 4) return "FLOOR 4 [SKY TERRACE] - RUN";
            if (fl == 3) return "FLOOR 3 [AUDITORIUM] - RUN";
            if (fl == 2) return "FLOOR 2 [LIBRARY] - RUN";
            return "FLOOR 1 [GROUND] - RUN";
        case State::Jump:
            if (fl == 4) return "FLOOR 4 - JUMP";
            if (fl == 3) return "FLOOR 3 - JUMP";
            if (fl == 2) return "FLOOR 2 - JUMP";
            return "JUMP";
        case State::Fall: return "FALL";
        case State::Stair: return "STAIR CLIMB";
        case State::Sit: return "SIT";
        default:
            if (fl == 4) return "FLOOR 4 [SKY TERRACE] - IDLE";
            if (fl == 3) return "FLOOR 3 [AUDITORIUM] - IDLE";
            if (fl == 2) return "FLOOR 2 [LIBRARY] - IDLE";
            return "FLOOR 1 [GROUND] - IDLE";
    }
}
