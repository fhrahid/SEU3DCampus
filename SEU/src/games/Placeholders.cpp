#include "RubiksCube.h"
#include "Ludo.h"
#include "../render/Primitives.h"
void RubiksCube::reset() { for (int f = 0; f < 6; ++f) for (int& cell : face_[f]) cell = f; moves_ = 0; }
void RubiksCube::update(const Input&) {}
void RubiksCube::render(int, int) const { render::text2d(55, 90, title(), {1,1,1}); render::text2d(55, 140, "Phase 11 game implementation pending", {1,1,1}); }
void RubiksCube::turn(int, bool) {} bool RubiksCube::solved() const { return true; }
void Ludo::reset() { for (int& token : tokens_) token = -1; turn_ = dice_ = 0; winner_ = -1; }
void Ludo::update(const Input&) {}
void Ludo::render(int, int) const { render::text2d(55, 90, title(), {1,1,1}); render::text2d(55, 140, "Phase 12 game implementation pending", {1,1,1}); }
void Ludo::roll() {}
