#include "CollisionWorld.h"
#include "../render/Primitives.h"
#include <GL/gl.h>
#include <algorithm>

CollisionWorld::CollisionWorld() {
    auto wall = [this](float minX, float maxX, float minZ, float maxZ, float minY = 0.0f, float maxY = 5.0f) {
        solids_.push_back({minX, maxX, minZ, maxZ, minY, maxY});
    };

    // Full-height building exterior envelope (spans Ground through Floor 2 and Roof)
    wall(-24.3f, -23.8f, 9.5f, 40.0f, 0.0f, 25.0f);
    wall(16.2f, 16.7f, 9.5f, 40.0f, 0.0f, 25.0f);
    wall(-24.0f, 16.5f, 39.7f, 40.3f, 0.0f, 25.0f);

    // Ground Floor: South frontage
    // Admission 1 and Gaming suite are closed along the south facade;
    // Stair 1 remains open between x = -12.0f and x = 2.5f as the entrance.
    wall(-24.0f, -12.0f, 9.2f, 9.8f, 0.0f, 5.0f);
    wall(2.5f, 16.5f, 9.2f, 9.8f, 0.0f, 5.0f);

    // Ground Floor: Admission Office 1 Corridor Wall (x = -11.5m)
    // Grand entrance gate at z in [10.6, 13.0] is 100% OPEN (width 2.4m)
    wall(-11.8f, -11.3f, 9.5f, 10.6f, 0.0f, 5.0f);  // South sidelight partition
    wall(-11.8f, -11.3f, 13.0f, 14.0f, 0.0f, 5.0f); // North sidelight partition

    // Ground Floor: Divider Wall between Admission 1 and Admission 2/Bank 1 (z = 14.0m)
    // Internal connecting double door at x in [-19.6, -17.4] is 100% OPEN (width 2.2m)
    wall(-24.0f, -19.6f, 13.8f, 14.2f, 0.0f, 5.0f);
    wall(-17.4f, -11.3f, 13.8f, 14.2f, 0.0f, 5.0f);

    // Ground Floor: Divider Wall between Admission 2 and Bank 1 (x = -16.2m)
    wall(-16.4f, -16.0f, 14.0f, 21.6f, 0.0f, 5.0f);

    // Ground Floor: Bank 1 Corridor Wall (x = -11.5m)
    // Bank 1 entrance door at z in [15.2, 17.4] is 100% OPEN (width 2.2m)
    wall(-11.8f, -11.3f, 14.0f, 15.2f, 0.0f, 5.0f);
    wall(-11.8f, -11.3f, 17.4f, 21.6f, 0.0f, 5.0f);

    // Ground Floor: Infirmary & Female Washroom (x in [-24.0, -20.8])
    // The corridor in front of the female lifts (x in [-20.8, -10.2], z in [21.6, 25.0]) is 100% OPEN with zero extra blockers!
    wall(-24.0f, -20.8f, 21.4f, 21.8f, 0.0f, 5.0f); // Infirmary south divider with Admission 2
    wall(-21.0f, -20.6f, 21.6f, 28.2f, 0.0f, 5.0f); // Flush East wall of Infirmary & Female Washroom at x = -20.8m

    // Ground Floor: Gaming suite perimeter and internal divider
    // West glass wall moved to x = 3.6m to create a wide, open corridor beside the gaming room
    wall(3.5f, 3.9f, 9.5f, 16.2f, 0.0f, 5.0f);
    wall(16.3f, 16.8f, 9.5f, 16.2f, 0.0f, 5.0f);
    // Grand double entrance opening: x in [7.6, 11.2] is 100% open (width 3.6m)
    wall(3.5f, 7.6f, 16.0f, 16.4f, 0.0f, 5.0f);
    wall(11.2f, 16.6f, 16.0f, 16.4f, 0.0f, 5.0f);
    // Double internal divider door opening: x in [8.0, 10.8] is 100% open (width 2.8m)
    wall(3.5f, 8.0f, 12.6f, 13.0f, 0.0f, 5.0f);
    wall(10.8f, 16.6f, 12.6f, 13.0f, 0.0f, 5.0f);

    // Ground Floor: Bank 2 (x in [7.4, 12.0], z in [18.2, 22.2])
    // Clean 2.0-meter wide cross-corridor beside Gaming Room north wall
    wall(7.2f, 7.6f, 18.2f, 22.2f, 0.0f, 5.0f);   // Bank 2 West wall
    wall(7.4f, 9.0f, 18.0f, 18.4f, 0.0f, 5.0f);   // Bank 2 South front left
    wall(10.4f, 12.0f, 18.0f, 18.4f, 0.0f, 5.0f);  // Bank 2 South front right
    wall(7.4f, 12.0f, 22.0f, 22.4f, 0.0f, 5.0f);  // Bank 2 North back

    // Ground Floor: SEU University Stationery & Bookstore (x in [12.0, 16.6], z in [18.2, 22.2])
    // Grand entrance door at x in [13.1, 15.3] is 100% open (width 2.2m)
    wall(12.0f, 13.1f, 18.0f, 18.4f, 0.0f, 5.0f);   // Left storefront display window
    wall(15.3f, 16.6f, 18.0f, 18.4f, 0.0f, 5.0f);   // Right storefront display window
    wall(12.0f, 16.6f, 22.0f, 22.4f, 0.0f, 5.0f);   // North wall
    wall(11.8f, 12.2f, 18.2f, 22.2f, 0.0f, 5.0f);   // West partition with Bank 2
    wall(13.9f, 15.7f, 18.8f, 19.4f, 0.0f, 5.0f);   // Checkout counter

    // Ground Floor: Cafeteria Enclosure & Grand Entrance (x in [-10.2, 10.2], z in [29.8, 40.0])
    // Grand double entrance opening at x in [-1.8, 1.8] is 100% OPEN with zero obstruction
    wall(-10.2f, -1.8f, 29.6f, 30.0f, 0.0f, 5.0f);  // Left storefront facade
    wall(4.7f, 10.2f, 29.6f, 30.0f, 0.0f, 5.0f);   // Right storefront facade (East of Stair 3, Stairwell 100% OPEN)

    // Ground Floor: Teacher & Faculty Lounge corridor frontage (x = -10.2m)
    // Grand entrance double doors at z in [29.4, 31.8] are 100% OPEN for seamless entry
    wall(-10.4f, -10.0f, 28.2f, 29.4f, 0.0f, 5.0f); // South corner wall segment
    wall(-10.4f, -10.0f, 31.8f, 33.6f, 0.0f, 5.0f); // North window wall segment
    wall(-10.4f, -10.0f, 36.6f, 40.0f, 0.0f, 5.0f); // West wall segment beside Shop 1
    wall(10.0f, 10.4f, 29.8f, 31.5f, 0.0f, 5.0f);  // East wall segment
    wall(10.0f, 10.4f, 35.0f, 38.0f, 0.0f, 5.0f);  // East wall segment

    // Ground Floor: Dedicated Food Shops 1 to 5 Serving Counters
    wall(-21.9f, -20.6f, 33.6f, 40.0f, 0.0f, 5.0f); // Shops 1 & 2 counters facing East
    wall(13.6f, 14.8f, 31.5f, 39.0f, 0.0f, 5.0f);   // Shops 3 & 4 counters facing West
    wall(10.2f, 14.0f, 38.0f, 39.2f, 0.0f, 5.0f);   // Shop 5 counter facing South

    // Multi-Floor Elevator Shafts & Boardable 3D Cabins (minY = 0.0f, maxY = 20.0f)
    // West Core: Lift 3 (closed door at z = 25.0) and Lift 4 (open boardable cabin at x = -13.5m)
    wall(-18.5f, -15.3f, 24.8f, 25.1f, 0.0f, 20.0f); // West Lift 3 closed front door
    wall(-18.5f, -12.2f, 26.7f, 27.2f, 0.0f, 20.0f); // West Core rear mirror wall
    wall(-18.5f, -18.2f, 25.0f, 26.8f, 0.0f, 20.0f); // West outer cabin wall
    wall(-12.4f, -12.1f, 25.0f, 26.8f, 0.0f, 20.0f); // East outer cabin wall
    wall(-15.4f, -15.2f, 25.0f, 26.8f, 0.0f, 20.0f); // Internal divider between West lifts

    // East Core: Lift 1 (closed door at z = 25.2) and Lift 2 (open boardable cabin at x = 10.6m)
    wall(5.4f, 8.6f, 25.0f, 25.3f, 0.0f, 20.0f);     // East Lift 1 closed front door
    wall(5.4f, 11.8f, 26.9f, 27.4f, 0.0f, 20.0f);    // East Core rear mirror wall
    wall(5.35f, 5.65f, 25.2f, 27.0f, 0.0f, 20.0f);   // West outer cabin wall
    wall(11.7f, 12.0f, 25.2f, 27.0f, 0.0f, 20.0f);   // East outer cabin wall
    wall(8.5f, 8.7f, 25.2f, 27.0f, 0.0f, 20.0f);     // Internal divider between East lifts

    // Second Floor (minY = 5.0f, maxY = 9.0f):
    // South facade / sky terrace perimeter railing
    wall(-10.0f, 5.0f, 9.3f, 9.7f, 5.0f, 6.5f);
    wall(-24.0f, -10.0f, 9.3f, 9.7f, 5.0f, 9.5f);
    wall(5.0f, 16.5f, 9.3f, 9.7f, 5.0f, 9.5f);

    // Second Floor: Central atrium safety balustrades (overlooking ground floor lobby)
    wall(-7.0f, 7.0f, 13.8f, 14.2f, 5.0f, 6.4f); // South atrium rail
    wall(-7.0f, 1.3f, 23.8f, 24.2f, 5.0f, 6.4f); // North atrium rail (left of Stair 3)
    wall(4.7f, 7.0f, 23.8f, 24.2f, 5.0f, 6.4f);  // North atrium rail (right of Stair 3)
    wall(-7.2f, -6.8f, 14.0f, 24.0f, 5.0f, 6.4f); // West atrium rail
    wall(6.8f, 7.2f, 14.0f, 24.0f, 5.0f, 6.4f);  // East atrium rail

    // Second Floor: Stair 3 side railings (clear 3.0m stairwell opening at x in [1.5, 4.5])
    wall(1.1f, 1.5f, 24.0f, 30.6f, 5.0f, 6.4f);
    wall(4.5f, 4.9f, 24.0f, 30.6f, 5.0f, 6.4f);

    // Second Floor: Major room partitions
    wall(-12.3f, -11.8f, 14.0f, 23.0f, 5.0f, 9.5f); // CSE Lab corridor wall
    wall(-12.3f, -11.8f, 28.0f, 38.0f, 5.0f, 9.5f); // Library corridor wall
    wall(4.8f, 5.2f, 14.0f, 21.0f, 5.0f, 9.5f);     // Classroom 201 corridor wall

    // Third Floor (minY = 9.0f, maxY = 13.0f): Central atrium safety balustrades
    wall(-7.0f, 7.0f, 13.8f, 14.2f, 9.0f, 10.4f);
    wall(-7.0f, 7.0f, 23.8f, 24.2f, 9.0f, 10.4f);
    wall(-7.2f, -6.8f, 14.0f, 24.0f, 9.0f, 10.4f);
    wall(6.8f, 7.2f, 14.0f, 24.0f, 9.0f, 10.4f);
    wall(-12.3f, -11.8f, 14.0f, 23.0f, 9.0f, 13.2f); // Robotics Lab wall
    wall(-12.3f, -11.8f, 26.0f, 38.0f, 9.0f, 13.2f); // Auditorium wall

    // Fourth Floor (minY = 13.0f, maxY = 17.5f): Central atrium & Sky Garden balustrades
    wall(-7.0f, 7.0f, 13.8f, 14.2f, 13.0f, 14.4f);
    wall(-7.0f, 7.0f, 23.8f, 24.2f, 13.0f, 14.4f);
    wall(-7.2f, -6.8f, 14.0f, 24.0f, 13.0f, 14.4f);
    wall(6.8f, 7.2f, 14.0f, 24.0f, 13.0f, 14.4f);
    wall(-10.0f, 16.5f, 9.3f, 9.7f, 13.0f, 14.5f);  // South Sky Garden perimeter railing
    wall(16.0f, 16.6f, 9.5f, 38.0f, 13.0f, 14.5f);  // East Sky Garden perimeter railing
}

bool CollisionWorld::overlaps(const Aabb& box, float x, float y, float z, float radius, float height) const {
    if (y + height < box.minY || y > box.maxY) return false;
    return x + radius > box.minX && x - radius < box.maxX && z + radius > box.minZ && z - radius < box.maxZ;
}

Vec3 CollisionWorld::move(Vec3 position, Vec3 delta, float radius) const {
    const float playerHeight = 1.8f;
    Vec3 result = position;
    auto liftDoorBlocks = [this, radius, playerHeight, delta, &result](float baseY, float minX, float maxX, float frontZ) {
        if (liftDoorsOpen_ && liftFloor_ == static_cast<int>((baseY - 1.2f) / 4.0f) + 1) return false;
        const Aabb door{minX, maxX, frontZ - .14f, frontZ + .14f, baseY, baseY + 3.0f};
        if (!overlaps(door, result.x, result.y, result.z, radius, playerHeight)) return false;
        if (std::abs(delta.z) > 1e-5f) {
            result.z = delta.z > 0 ? door.minZ - radius : door.maxZ + radius;
        }
        return true;
    };
    if (std::abs(delta.x) > 1e-5f) {
        result.x += delta.x;
        for (const Aabb& box : solids_) if (overlaps(box, result.x, result.y, result.z, radius, playerHeight)) {
            if (delta.x > 0) result.x = box.minX - radius; else result.x = box.maxX + radius;
        }
    }
    if (std::abs(delta.z) > 1e-5f) {
        result.z += delta.z;
        for (const Aabb& box : solids_) if (overlaps(box, result.x, result.y, result.z, radius, playerHeight)) {
            if (delta.z > 0) result.z = box.minZ - radius; else result.z = box.maxZ + radius;
        }
    }
    // Boardable Lift 4 / Lift 2 landing doors are dynamic. Closed doors
    // prevent entering the shaft; only the car's current open landing is free.
    for (int floor = 1; floor <= 4; ++floor) {
        const float baseY = 1.2f + (floor - 1) * 4.0f;
        liftDoorBlocks(baseY, -14.65f, -12.35f, 25.0f);
        liftDoorBlocks(baseY, 9.45f, 11.75f, 25.2f);
    }
    result.x = std::max(-23.8f, std::min(16.5f, result.x));
    result.z = std::max(.2f, std::min(39.8f, result.z));
    return result;
}

void CollisionWorld::setLiftState(int floor, bool doorsOpen) {
    liftFloor_ = std::max(1, std::min(4, floor));
    liftDoorsOpen_ = doorsOpen;
}

void CollisionWorld::debugDraw() const {
    glDisable(GL_LIGHTING); glColor3f(1, .1f, .1f);
    for (const Aabb& box : solids_) {
        const float drawY = box.minY + 0.1f;
        glBegin(GL_LINE_LOOP);
        glVertex3f(box.minX, drawY, box.minZ);
        glVertex3f(box.maxX, drawY, box.minZ);
        glVertex3f(box.maxX, drawY, box.maxZ);
        glVertex3f(box.minX, drawY, box.maxZ);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}
