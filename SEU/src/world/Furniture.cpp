#include "Furniture.h"
#include "../render/Primitives.h"
#include <initializer_list>
namespace campus {
namespace {
using render::Color;
void table(float x, float y, float z, float w, float d, Color top) {
    render::texturedBox({x, y + .8f, z}, {w, .12f, d}, top, 2);
    for (float sx : {-w * .38f, w * .38f}) for (float sz : {-d * .32f, d * .32f})
        render::box({x + sx, y + .4f, z + sz}, {.1f, .8f, .1f}, {.2f, .16f, .1f});
}
void chair(float x, float y, float z) {
    render::box({x, y + .45f, z}, {.55f, .1f, .55f}, {.45f, .22f, .1f});
    render::box({x, y + .85f, z + .22f}, {.55f, .75f, .1f}, {.45f, .22f, .1f});
}
void counter(float x, float z, float w) {
    render::box({x, 2.0f, z}, {w, 1.6f, .65f}, {.46f, .25f, .12f});
    render::box({x, 2.85f, z}, {w + .08f, .12f, .72f}, {.75f, .62f, .3f});
    chair(x - w * .3f, 1.2f, z - .7f);
}
void shelf(float x, float z, int levels) {
    render::box({x, 1.8f, z}, {.16f, 3.2f, 1.0f}, {.38f, .2f, .12f});
    for (int i = 0; i < levels; ++i) render::box({x, .5f + i * .55f, z}, {1.2f, .08f, 1.0f}, {.55f, .28f, .12f});
}
void lift(float x, float z) {
    render::box({x, 1.8f, z}, {1.9f, 3.6f, .2f}, {.18f, .22f, .25f});
    render::box({x - .42f, 1.8f, z - .13f}, {.78f, 2.7f, .06f}, {.68f, .73f, .76f});
    render::box({x + .42f, 1.8f, z - .13f}, {.78f, 2.7f, .06f}, {.68f, .73f, .76f});
    render::box({x, 3.35f, z - .19f}, {.42f, .2f, .05f}, {.1f, .85f, .35f});
}
void rails(float x, float z, float width) {
    for (int i = 0; i < 5; ++i) render::cylinder({x + i * width / 4, 1.0f + i * .15f, z}, .035f, .9f, {.65f, .66f, .7f});
}
}
void renderFurniture(bool labels) {
    // Admission and banks: counters, desks and seating communicate function.
    counter(-20, 11.5f, 4.4f); counter(-14, 18.5f, 2.7f);
    table(-20, 1.2f, 17, 2.8f, 1.2f, {.64f, .38f, .16f}); chair(-20, 1.2f, 15.9f);
    render::box({-20, 1.9f, 22.4f}, {2.8f, 1.8f, .5f}, {.55f, .3f, .15f});
    // Cafeteria and faculty seating.
    for (float x : {-7.f, 0.f, 7.f}) { table(x, 1.2f, 34, 2.4f, 1.2f, {.55f, .3f, .15f}); chair(x - 1.5f, 1.2f, 34); chair(x + 1.5f, 1.2f, 34); }
    table(-17, 1.2f, 30.2f, 3, 1.1f, {.3f, .22f, .15f}); chair(-18.2f, 1.2f, 30.2f);
    // Shops and stationery shelves.
    counter(-22, 34.3f, 2.2f); counter(-22, 37.3f, 2.2f); counter(11, 38.2f, 1.5f); counter(14.5f, 37.2f, 1.5f); counter(14.5f, 32.2f, 1.5f);
    shelf(12.2f, 20, 5); shelf(14.4f, 20, 5);
    // Lift doors and static staircase railings.
    lift(-19, 24.1f); lift(-14.5f, 24.1f); lift(6.2f, 24.1f); lift(10.2f, 24.1f);
    rails(1.2f, 25, 2.4f); rails(10.5f, 27.4f, 3.5f);
    // Gaming Room 1/2 hierarchical setup.
    table(4, 1.2f, 15.2f, 3.3f, 1.7f, {.08f, .28f, .08f});
    render::box({4, 2.05f, 15.2f}, {2.7f, .08f, 1.2f}, {.9f, .85f, .7f});
    table(10, 1.2f, 15.2f, 3.5f, 1.8f, {.08f, .1f, .12f});
    render::cylinder({10, 2.05f, 15.2f}, .6f, .08f, {.8f, .1f, .08f});
    table(5, 1.2f, 11.7f, 3.3f, 1.7f, {.18f, .1f, .05f});
    chair(3, 1.2f, 11.7f); chair(7, 1.2f, 11.7f);
    if (labels) {
        render::text3d({-22, 3.1f, 11.2f}, "ADMISSION", {1, 1, 1});
        render::text3d({-22, 3.1f, 34.5f}, "CAFETERIA", {1, 1, 1});
        render::text3d({2.5f, 3.1f, 15.2f}, "POOL / CARROM", {1, 1, 1});
    }
}
}
