#pragma once
#include "../render/Camera.h"
#include <vector>
struct Aabb {
    float minX, maxX, minZ, maxZ;
    float minY = 0.0f, maxY = 30.0f;
};
class CollisionWorld {
public:
    CollisionWorld();
    Vec3 move(Vec3 position, Vec3 delta, float radius) const;
    void setLiftState(int floor, bool doorsOpen);
    void debugDraw() const;
private:
    std::vector<Aabb> solids_;
    int liftFloor_ = 4;
    bool liftDoorsOpen_ = false;
    bool overlaps(const Aabb& box, float x, float y, float z, float radius, float height = 1.8f) const;
};
