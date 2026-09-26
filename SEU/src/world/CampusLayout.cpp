#include "CampusLayout.h"
#include "../render/Primitives.h"
#include "Furniture.h"
#include <GL/glut.h>
#include <string>

namespace campus {
namespace {
using render::Color;
const Color driveway{.66f, .61f, .48f};
const Color gardenGreen{.15f, .46f, .18f};
const Color wall{.76f, .78f, .8f};
const Color roomBlue{.28f, .52f, .7f};
const Color roomPurple{.42f, .28f, .7f};
const Color roomGreen{.35f, .67f, .5f};
const Color roomPink{.68f, .45f, .7f};
const Color glass{.22f, .72f, .82f, .42f};
void label(const Rect& r, const char* name, bool labels) {
    if (labels) render::text3d({(r.minX + r.maxX) * .5f - .8f, floorY + .04f, (r.minZ + r.maxZ) * .5f}, name, {1, 1, 1});
}
void room(const Rect& r, Color floor, const char* name, bool labels, bool glassFront = false) {
    render::box({(r.minX + r.maxX) * .5f, floorY, (r.minZ + r.maxZ) * .5f}, {r.maxX-r.minX, .1f, r.maxZ-r.minZ}, floor);
    const float y = floorY + wallHeight * .5f;
    render::box({r.minX, y, (r.minZ+r.maxZ)*.5f}, {wallThickness, wallHeight, r.maxZ-r.minZ}, wall);
    render::box({r.maxX, y, (r.minZ+r.maxZ)*.5f}, {wallThickness, wallHeight, r.maxZ-r.minZ}, wall);
    render::box({(r.minX+r.maxX)*.5f, y, r.maxZ}, {r.maxX-r.minX, wallHeight, wallThickness}, wall);
    if (glassFront) render::glassPanel({(r.minX+r.maxX)*.5f, y, r.minZ}, {r.maxX-r.minX, wallHeight, .08f}, glass);
    else render::box({(r.minX+r.maxX)*.5f, y, r.minZ}, {r.maxX-r.minX, wallHeight, wallThickness}, wall);
    label(r, name, labels);
}
void tree(float x, float z) {
    render::cylinder({x, .9f, z}, .13f, 1.8f, {.35f, .2f, .1f});
    render::cylinder({x, 2.15f, z}, .9f, 1.5f, {.1f, .43f, .13f});
}
void gate(float x, const char* name) {
    render::box({x - .8f, 2.1f, .15f}, {.22f, 4.2f, .22f}, {.35f, .35f, .38f});
    render::box({x + .8f, 2.1f, .15f}, {.22f, 4.2f, .22f}, {.35f, .35f, .38f});
    render::box({x, 4.0f, .15f}, {1.8f, .22f, .22f}, {.72f, .72f, .76f});
    render::text3d({x - .65f, 4.35f, .15f}, name, {1, .85f, .2f});
}
void outline(const Rect& r) {
    const float y = floorY + .12f;
    glDisable(GL_LIGHTING); glColor3f(1, .12f, .1f); glBegin(GL_LINE_LOOP);
    glVertex3f(r.minX, y, r.minZ); glVertex3f(r.maxX, y, r.minZ); glVertex3f(r.maxX, y, r.maxZ); glVertex3f(r.minX, y, r.maxZ); glEnd(); glEnable(GL_LIGHTING);
}
void exteriorFacade(bool labels) {
    // SEU-inspired massing sits above the unchanged ground-floor footprint.
    render::box({-19.5f, 5.3f, 39.2f}, {7.5f, 8.2f, 1.2f}, {.58f, .22f, .14f});
    render::box({-7.0f, 5.1f, 39.25f}, {16, 7.8f, .9f}, {.74f, .76f, .77f});
    render::box({9.4f, 5.5f, 39.1f}, {6.0f, 8.6f, 1.4f}, {.8f, .81f, .8f});
    render::glassPanel({-6.5f, 5.0f, 38.65f}, {12.5f, 6.9f, .08f}, {.3f, .7f, .78f, .55f});
    render::glassPanel({4.0f, 5.0f, 38.62f}, {5.0f, 6.9f, .08f}, {.3f, .7f, .78f, .55f});
    for (int i = 0; i < 7; ++i) {
        render::box({9.4f, 2.2f + i * 1.0f, 38.35f}, {1.7f, .4f, .08f}, {.1f, .12f, .13f});
    }
    render::text3d({-1.2f, 7.2f, 38.55f}, "S E U", {1, 1, .96f});
    // A shallow colonnade makes the front approach readable from outside.
    for (float x = -10; x <= 10; x += 4) {
        render::cylinder({x, 2.1f, 10.05f}, .18f, 4.2f, {.78f, .79f, .8f});
    }
    if (labels) render::text3d({-3.0f, 4.45f, 10.0f}, "SOUTHEAST UNIVERSITY", {1, 1, 1});
}
}
void renderScene(bool showLabels, bool debugBounds) {
    render::plane({0, 0, 20}, {48, 0, 42}, {.22f, .27f, .25f});
    render::plane({0, .02f, 2.8f}, {34, 0, 5.2f}, gardenGreen);
    render::plane({0, .04f, 7.7f}, {48, 0, 4.2f}, driveway);
    render::plane({20, .04f, 24}, {8, 0, 34}, driveway);
    exteriorFacade(showLabels);
    gate(-19, "IN GATE"); gate(20, "OUT GATE");
    render::box({-22.4f, 1.1f, 7.9f}, {3, 2.2f, 2.6f}, {.45f, .24f, .2f});
    render::text3d({-23.5f, 2.4f, 7.8f}, "GUARD", {1, 1, 1});
    for (float x : {-13.f, -5.f, 4.f, 12.f}) tree(x, 2.8f);
    render::stairs({-5.5f, 0, 7.9f}, 7.5f, .15f, .34f, 8, {.63f, .64f, .67f});
    render::box({-1.75f, floorY + .2f, 14.8f}, {14.5f, .4f, .8f}, {.9f, .76f, .2f});
    render::text3d({-8, floorY + .5f, 14.8f}, "PUNCH GATE", {.15f, .1f, .05f});
    room({-24,-12,10,24}, roomBlue, "ADMIN", showLabels);
    room({-24,-17,24,28}, roomPink, "FEMALE", showLabels);
    room({-17,-12,24,28}, roomPink, "LIFT 4 / 3", showLabels);
    room({-24,-11,28,33}, roomPurple, "FACULTY", showLabels);
    room({-24,-21,33,36}, roomGreen, "FOOD 2", showLabels);
    room({-24,-21,36,40}, roomGreen, "FOOD 1", showLabels);
    room({-11,13,30,40}, roomPurple, "CAFETERIA", showLabels);
    room({9,13,37,40}, roomGreen, "FOOD 5", showLabels);
    room({13,16,35,40}, roomGreen, "FOOD 3", showLabels);
    room({13,16,30,35}, roomGreen, "FOOD 4", showLabels);
    room({1,4,25,30}, roomPink, "STAIR 3", showLabels);
    room({4,12,24,28}, roomPink, "LIFT 1 / 2", showLabels);
    room({12,16,24,28}, roomPink, "MALE", showLabels);
    room({7,11,20,24}, roomBlue, "BANK 2", showLabels);
    room({11,16,17,24}, roomGreen, "STATIONERY", showLabels);
    room({-1,16,13.5f,17}, roomBlue, "GAMING 1", showLabels, true);
    room({-1,16,10,13.5f}, roomBlue, "GAMING 2", showLabels, true);
    renderFurniture(showLabels);
    render::text3d({-23, floorY + .2f, 20}, "ADMISSION 1 / 2  BANK 1", {1, 1, 1});
    render::text3d({-23, floorY + .2f, 11}, "SECURITY", {1, 1, 1});
    if (debugBounds) {
        outline(building); outline(garden); outline(admin); outline(gaming);
    }
}
}
