#include "Ludo.h"
#include "../render/Primitives.h"
void Ludo::reset() { for (int& token : tokens_) token = -1; turn_ = dice_ = 0; winner_ = -1; }
void Ludo::update(const Input&) {}
void Ludo::render(int, int) const { render::text2d(55, 90, title(), {1,1,1}); render::text2d(55, 140, "Phase 12 game implementation pending", {1,1,1}); }
void Ludo::roll() {}
