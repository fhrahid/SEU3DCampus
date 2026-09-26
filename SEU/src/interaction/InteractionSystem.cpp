#include "InteractionSystem.h"
#include "../core/Input.h"
#include "../player/Player.h"
#include <cmath>
namespace {
const InteractionSystem::Trigger triggers[] = {
    {{-20, 0, 15.9f}, 2.0f, InteractionSystem::Kind::Chair, "Admission chair"},
    {{-20, 0, 16.0f}, 2.0f, InteractionSystem::Kind::Chair, "Admission desk"},
    {{-7, 0, 34}, 2.2f, InteractionSystem::Kind::Chair, "Cafeteria table"},
    {{4, 0, 15.2f}, 2.0f, InteractionSystem::Kind::GameStation, "Gaming Room 1"},
    {{5, 0, 11.7f}, 2.0f, InteractionSystem::Kind::GameStation, "Gaming Room 2"}
};
}
void InteractionSystem::update(const Input& input, Player& player) {
    current_ = nullptr; prompt_ = "";
    if (player.seated) {
        prompt_ = "E: stand";
        if (input.pressed('e')) player.seated = false;
        if (player.seated) { player.state = Player::State::Sit; return; }
    }
    float nearest = 1e9f;
    for (const auto& trigger : triggers) {
        const float dx = player.position.x - trigger.position.x;
        const float dz = player.position.z - trigger.position.z;
        const float distance = std::sqrt(dx * dx + dz * dz);
        if (distance < trigger.radius && distance < nearest) { nearest = distance; current_ = &trigger; }
    }
    if (!current_) return;
    prompt_ = current_->kind == Kind::Chair ? "E: sit on " : "E: enter ";
    if (input.pressed('e')) {
        if (current_->kind == Kind::Chair) { player.seated = true; player.state = Player::State::Sit; }
        else gameRequested_ = true;
    }
}
