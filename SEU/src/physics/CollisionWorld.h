#pragma once
#include "../render/Camera.h"
#include <vector>
struct Aabb { float minX, maxX, minZ, maxZ; };
class CollisionWorld {
public:
    CollisionWorld();
    Vec3 move(Vec3 position, Vec3 delta, float radius) const;
    void debugDraw() const;
private:
    std::vector<Aabb> solids_;
    bool overlaps(const Aabb& box, float x, float z, float radius) const;
};
