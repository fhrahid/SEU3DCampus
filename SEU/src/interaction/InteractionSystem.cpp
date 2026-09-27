#include "InteractionSystem.h"
#include "../core/Input.h"
#include "../player/Player.h"
#include <cmath>

namespace {
const InteractionSystem::Trigger triggers[] = {
    // Ground Floor: Admission & Cafeteria Lounges
    {{-15.1f, 1.2f, 11.8f}, 2.2f, InteractionSystem::Kind::Chair, "Admission consultation visitor chair", -1, nullptr, 0.0f},
    {{-17.1f, 1.2f, 11.8f}, 2.2f, InteractionSystem::Kind::Chair, "Admission officer desk", -1, nullptr, 180.0f},
    {{-20.7f, 1.2f, 11.2f}, 2.5f, InteractionSystem::Kind::Chair, "Guardian waiting chair", -1, nullptr, 90.0f},
    {{-7.0f,  1.2f, 34.0f}, 2.5f, InteractionSystem::Kind::Chair, "Cafeteria lounge table", -1, nullptr, 270.0f},

    // Ground Floor: Food Shops 1 to 5 (Around Cafeteria)
    {{-20.8f, 1.2f, 38.3f}, 2.4f, InteractionSystem::Kind::Shop, "Food Shop 1: SEU Deli & Burgers", -1,
     "[DELI & BURGERS] Ordered Fresh Angus Beef Burger & Golden Crispy Fries! ($6.00)"},
    {{-20.8f, 1.2f, 35.1f}, 2.4f, InteractionSystem::Kind::Shop, "Food Shop 2: Pizza & Hot Rolls", -1,
     "[PIZZA & ROLLS] Ordered Hot Pepperoni Pizza Slice & Spicy Chicken Roll! ($5.50)"},
    {{13.8f,  1.2f, 37.5f}, 2.4f, InteractionSystem::Kind::Shop, "Food Shop 3: Bakery & Espresso Cafe", -1,
     "[BAKERY & CAFE] Ordered Double Espresso & Warm Butter Croissant! ($4.50)"},
    {{13.8f,  1.2f, 33.25f}, 2.4f, InteractionSystem::Kind::Shop, "Food Shop 4: Fresh Juice Bar & Smoothies", -1,
     "[JUICE BAR] Ordered Fresh Tropical Mango Smoothie & Fruit Bowl! ($3.50)"},
    {{12.1f,  1.2f, 38.0f}, 2.4f, InteractionSystem::Kind::Shop, "Food Shop 5: Asian Noodle Bowl & Rice", -1,
     "[ASIAN NOODLE BOWL] Ordered Spicy Chicken Chowmein & Egg Fried Rice! ($7.50)"},

    // Ground Floor: SEU University Stationery & Bookstore
    {{14.8f,  1.2f, 19.1f}, 2.3f, InteractionSystem::Kind::Shop, "SEU Bookstore & Stationery Checkout", -1,
     "[SEU BOOKSTORE] Purchased Engineering Textbooks, Spiral Notebooks & Casio Calculator!"},
    {{12.6f,  1.2f, 21.6f}, 2.2f, InteractionSystem::Kind::Shop, "Commercial Xerox Print & Photocopy Station", -1,
     "[XEROX STATION] Printed 10 double-sided lecture note handouts!"},

    // Ground Floor: Dedicated Wall-Mounted Gaming Room Screens (Play All Games on Screen)
    {{5.8f,   1.2f, 13.4f}, 2.2f, InteractionSystem::Kind::GameStation, "Gaming Room Screen 1 (All Games)", -1, nullptr},
    {{13.7f,  1.2f, 12.2f}, 2.2f, InteractionSystem::Kind::GameStation, "Gaming Room Screen 2 (All Games)", -1, nullptr},

    // Ground Floor: Gaming Room 1 (Tournaments & Sports Stations on Screen)
    {{5.4f,   1.2f, 14.8f}, 2.0f, InteractionSystem::Kind::GameStation, "2048 Arcade on Screen", 2, nullptr},
    {{8.6f,   1.2f, 14.8f}, 2.2f, InteractionSystem::Kind::GameStation, "Rock Paper Scissors on Screen", 1, nullptr},
    {{13.8f,  1.2f, 14.8f}, 2.2f, InteractionSystem::Kind::GameStation, "8-Ball Pool / Screen", -1, nullptr},

    // Ground Floor: Gaming Room 2 (Lounge & Board Game Stations on Screen)
    {{5.4f,   1.2f, 11.2f}, 2.0f, InteractionSystem::Kind::Chair,       "Gaming Lounge sofa", -1, nullptr, 0.0f},
    {{8.2f,   1.2f, 11.2f}, 2.0f, InteractionSystem::Kind::GameStation, "Tic-Tac-Toe on Screen", 0, nullptr},
    {{11.0f,  1.2f, 11.2f}, 2.0f, InteractionSystem::Kind::GameStation, "Rubik's Cube on Screen", 3, nullptr},
    {{13.8f,  1.2f, 11.2f}, 2.0f, InteractionSystem::Kind::GameStation, "Ludo Championship on Screen", 4, nullptr},

    // Multi-Floor Elevators (Boarding Cabins & Car Operating Panels)
    {{-13.5f, 1.2f, 25.8f}, 2.2f, InteractionSystem::Kind::Lift, "West Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{10.6f,  1.2f, 26.0f}, 2.2f, InteractionSystem::Kind::Lift, "East Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{-13.5f, 5.2f, 25.8f}, 2.2f, InteractionSystem::Kind::Lift, "West Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{10.6f,  5.2f, 26.0f}, 2.2f, InteractionSystem::Kind::Lift, "East Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{-13.5f, 9.2f, 25.8f}, 2.2f, InteractionSystem::Kind::Lift, "West Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{10.6f,  9.2f, 26.0f}, 2.2f, InteractionSystem::Kind::Lift, "East Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{-13.5f, 13.2f, 25.8f}, 2.2f, InteractionSystem::Kind::Lift, "West Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},
    {{10.6f,  13.2f, 26.0f}, 2.2f, InteractionSystem::Kind::Lift, "East Elevator Cabin [Press 1, 2, 3, 4]", -1,
     "[ELEVATOR] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)"},

    // Multi-Floor Highlights (Library, Auditorium, Boardroom)
    {{-17.5f, 5.2f, 32.5f}, 2.5f, InteractionSystem::Kind::Chair, "Library study station", -1, nullptr, 90.0f},
    {{-17.5f, 9.2f, 32.5f}, 2.5f, InteractionSystem::Kind::Chair, "Auditorium executive seating", -1, nullptr, 90.0f},
    {{-17.5f, 13.2f, 32.5f}, 2.5f, InteractionSystem::Kind::Chair, "Executive Boardroom chair", -1, nullptr, 90.0f}
};
}

void InteractionSystem::update(const Input& input, Player& player, float dt) {
    if (notifyTimer_ > 0.0f) {
        notifyTimer_ -= dt;
        if (notifyTimer_ <= 0.0f) {
            notifyTimer_ = 0.0f;
            notification_.clear();
        }
    }

    // Decrement sit cooldown (prevents instant re-sit after standing)
    if (sitCooldown_ > 0.0f) {
        sitCooldown_ -= dt;
        if (sitCooldown_ < 0.0f) sitCooldown_ = 0.0f;
    }

    current_ = nullptr;
    prompt_.clear();

    // --- SEATED STATE: player is locked in chair ---
    if (player.seated) {
        prompt_ = "E: stand up";
        if (input.pressed('e')) {
            player.seated = false;
            player.state = Player::State::Idle;
            sitCooldown_ = 0.6f;  // 0.6s before player can sit again
            notification_ = "Stood up";
            notifyTimer_ = 1.5f;
        }
        if (player.seated) { player.state = Player::State::Sit; return; }
    }

    // --- Find nearest trigger ---
    float nearest = 1e9f;
    for (const auto& trigger : triggers) {
        if (std::abs(player.position.y - trigger.position.y) > 2.2f) continue;
        const float dx = player.position.x - trigger.position.x;
        const float dz = player.position.z - trigger.position.z;
        const float distance = std::sqrt(dx * dx + dz * dz);
        if (distance < trigger.radius && distance < nearest) {
            nearest = distance;
            current_ = &trigger;
        }
    }

    if (!current_) return;

    if (current_->kind == Kind::Chair) {
        if (sitCooldown_ <= 0.0f) {
            prompt_ = "E: sit on " + std::string(current_->name);
        }
    } else if (current_->kind == Kind::GameStation) {
        prompt_ = "E: play on " + std::string(current_->name);
    } else if (current_->kind == Kind::Shop) {
        prompt_ = "E: order/buy from " + std::string(current_->name);
    } else if (current_->kind == Kind::Lift) {
        prompt_ = "E / 1-4: ride " + std::string(current_->name);
    }

    if (input.pressed('e')) {
        if (current_->kind == Kind::Chair && sitCooldown_ <= 0.0f) {
            // Snap player onto chair position for proper sit
            player.position = current_->position;
            player.yaw = current_->seatYaw;
            player.pitch = 0.0f;
            player.verticalVelocity = 0.0f;
            player.grounded = true;
            player.seated = true;
            player.state = Player::State::Sit;
            notification_ = std::string("Seated on ") + current_->name;
            notifyTimer_ = 2.5f;
        } else if (current_->kind == Kind::GameStation) {
            gameRequested_ = true;
            requestedGame_ = current_->gameIndex;
        } else if (current_->kind == Kind::Shop || current_->kind == Kind::Lift) {
            if (current_->notification) {
                notification_ = current_->notification;
            } else {
                notification_ = std::string("Interacted with ") + current_->name;
            }
            notifyTimer_ = 4.5f;
        }
    }
}
