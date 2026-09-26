#pragma once
#include "../render/Camera.h"
namespace campus {
struct Rect { float minX, maxX, minZ, maxZ; };
constexpr float floorY = 1.2f;
constexpr float wallHeight = 3.6f;
constexpr float wallThickness = .28f;
constexpr Rect site{-24, 24, 0, 40};
constexpr Rect garden{-16.5f, 15.5f, .5f, 5};
constexpr Rect building{-24, 16, 10, 40};
constexpr Rect admin{-24, -12, 10, 24};
constexpr Rect gaming{-1, 16, 10, 17};
void renderScene(bool showLabels, bool debugBounds, bool showCeilings = true);
}
