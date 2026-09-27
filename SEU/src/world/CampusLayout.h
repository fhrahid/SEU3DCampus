#pragma once
#include "../render/Camera.h"
namespace campus {
struct Rect { float minX, maxX, minZ, maxZ; };
constexpr float floorY = 1.2f;
constexpr float floor1Y = 1.2f;
constexpr float floor2Y = 5.2f;
constexpr float floor3Y = 9.2f;
constexpr float floor4Y = 13.2f;
constexpr float wallHeight = 4.0f;
constexpr float wallThickness = .28f;
constexpr Rect site{-24, 24, 0, 40};
constexpr Rect garden{-16.5f, 15.5f, .5f, 5};
constexpr Rect building{-24, 16.5f, 9.5f, 40};
constexpr Rect admin{-24, -11.5f, 9.5f, 24.5f};
constexpr Rect gaming{3.6f, 16.6f, 9.5f, 16.2f};
void renderScene(bool showLabels, bool debugBounds, bool showCeilings = true);
}
