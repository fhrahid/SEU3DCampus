#include "CollisionWorld.h"
#include "../render/Primitives.h"
#include <GL/gl.h>
#include <algorithm>
CollisionWorld::CollisionWorld() {
    auto wall = [this](float minX, float maxX, float minZ, float maxZ) { solids_.push_back({minX, maxX, minZ, maxZ}); };
    // Site perimeter, with a deliberate south opening at Stair 1.
    wall(-24, -5.5f, 9.7f, 10.2f); wall(2.0f, 16, 9.7f, 10.2f);
    wall(-24.3f, -23.8f, 10, 40); wall(15.7f, 16.3f, 10, 40); wall(-24, 16, 39.7f, 40.3f);
    // Room partitions and glass fronts. Door gaps remain open in the central circulation.
    wall(-12.3f, -11.8f, 10, 13.4f); wall(-12.3f, -11.8f, 16.2f, 24);
    wall(2.0f, 2.4f, 25, 30); wall(3.8f, 4.2f, 24, 27.3f);
    wall(6.9f, 7.3f, 20, 24); wall(10.8f, 11.2f, 20, 24);
    wall(-1.3f, 16.3f, 16.7f, 17.2f); wall(-1.3f, 16.3f, 13.2f, 13.8f);
    wall(15.7f, 16.3f, 10, 17); wall(-1.3f, -.8f, 10, 13.8f);
}
bool CollisionWorld::overlaps(const Aabb& box, float x, float z, float radius) const {
    return x + radius > box.minX && x - radius < box.maxX && z + radius > box.minZ && z - radius < box.maxZ;
}
Vec3 CollisionWorld::move(Vec3 position, Vec3 delta, float radius) const {
    Vec3 result = position;
    result.x += delta.x;
    for (const Aabb& box : solids_) if (overlaps(box, result.x, result.z, radius)) {
        if (delta.x > 0) result.x = box.minX - radius; else if (delta.x < 0) result.x = box.maxX + radius;
    }
    result.z += delta.z;
    for (const Aabb& box : solids_) if (overlaps(box, result.x, result.z, radius)) {
        if (delta.z > 0) result.z = box.minZ - radius; else if (delta.z < 0) result.z = box.maxZ + radius;
    }
    result.x = std::max(-23.5f, std::min(15.5f, result.x));
    result.z = std::max(.2f, std::min(39.3f, result.z));
    return result;
}
void CollisionWorld::debugDraw() const {
    glDisable(GL_LIGHTING); glColor3f(1, .1f, .1f);
    for (const Aabb& box : solids_) {
        glBegin(GL_LINE_LOOP); glVertex3f(box.minX, 1.3f, box.minZ); glVertex3f(box.maxX, 1.3f, box.minZ); glVertex3f(box.maxX, 1.3f, box.maxZ); glVertex3f(box.minX, 1.3f, box.maxZ); glEnd();
    }
    glEnable(GL_LIGHTING);
}
