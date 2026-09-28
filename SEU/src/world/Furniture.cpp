#include "Furniture.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <initializer_list>
#include <cstdio>
#include <cmath>
#include <algorithm>

namespace campus {
namespace {
using render::Color;

const Color woodTop{.58f, .34f, .16f};
const Color woodDark{.24f, .15f, .08f};
const Color legSteel{.22f, .24f, .26f};
const Color chromeColor{.86f, .88f, .92f};
const Color cushionColor{.38f, .22f, .12f};
const Color sofaLeather{.32f, .16f, .10f};
float liftPresentationFloor = 4.0f;
float liftPresentationDoor = 0.0f;

enum class NpcActivity { Desk, Read, Teach, Serve, Eat, Game, Lab, Present, Talk, Cashier };

// Wall-mounted split AC unit. The front grille is deliberately visible from
// the room so every enclosed room reads as conditioned indoor space.
void airConditioner(float x, float y, float z, bool onXWall = true) {
    const Color casing{.86f, .88f, .90f};
    const Color vent{.18f, .22f, .26f};
    glPushMatrix();
    glTranslatef(x, y + 3.18f, z);
    if (onXWall) glRotatef(90.0f, 0, 1, 0);
    render::box({0, 0, 0}, {1.35f, .34f, .20f}, casing);
    render::box({0, -.02f, -.115f}, {1.05f, .16f, .025f}, vent);
    for (float gx = -.42f; gx <= .42f; gx += .14f)
        render::box({gx, -.02f, -.135f}, {.025f, .10f, .012f}, {.58f, .65f, .70f});
    render::box({.53f, .06f, -.14f}, {.08f, .035f, .018f}, {.15f, .85f, .38f});
    glPopMatrix();
}

void npc(float x, float y, float z, float yaw, NpcActivity activity, Color shirt) {
    const Color skin{.82f, .61f, .45f};
    const Color trousers{.16f, .19f, .24f};
    const Color hair{.08f, .055f, .04f};
    // Use the world position as a stable seed so every NPC has a different
    // rhythm, even when two characters share the same activity.
    const float seconds = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) * .001f;
    const float seed = std::fabs(x * 1.37f + y * .73f + z * 2.11f);
    const float cycle = seconds * (.72f + std::fmod(seed, .58f)) + seed;
    const float motion = std::sin(cycle);
    const float alternate = std::sin(cycle * 1.71f + 1.2f);
    const float pulse = .5f + .5f * motion;
    const float bob = .008f * std::sin(cycle * .63f);

    glPushMatrix();
    glTranslatef(x, y + bob, z);
    glRotatef(yaw, 0, 1, 0);

    // Compact low-poly person: legs and torso have a small idle shift so the
    // scene never feels like it contains frozen mannequins.
    render::box({-.13f + .012f * alternate, .38f, 0}, {.18f, .70f, .20f}, trousers);
    render::box({ .13f - .012f * alternate, .38f, 0}, {.18f, .70f, .20f}, trousers);
    render::box({0, 1.08f, 0}, {.46f, .68f, .28f}, shirt);

    // The head follows the current task: readers look down, presenters look
    // toward the room, and conversational NPCs subtly look side to side.
    float headTilt = -2.0f * motion;
    if (activity == NpcActivity::Read || activity == NpcActivity::Desk ||
        activity == NpcActivity::Cashier || activity == NpcActivity::Lab)
        headTilt -= 5.0f;
    if (activity == NpcActivity::Teach || activity == NpcActivity::Present)
        headTilt += 3.0f;
    glPushMatrix();
    glTranslatef(0, 1.58f, 0);
    glRotatef(headTilt, 1, 0, 0);
    glRotatef(2.5f * alternate, 0, 1, 0);
    render::box({0, 0, 0}, {.27f, .28f, .27f}, skin);
    render::box({0, .18f, 0}, {.29f, .12f, .29f}, hair);
    glPopMatrix();

    // Arms are animated around the shoulders. Different activities use this
    // same lightweight primitive with different gestures and timing.
    auto arm = [&](float side, float pitch, float roll, float reach) {
        glPushMatrix();
        glTranslatef(side * .25f, 1.31f, 0);
        glRotatef(roll, 0, 0, 1);
        glRotatef(pitch, 1, 0, 0);
        render::box({0, -.20f, reach}, {.10f, .40f, .10f}, skin);
        glPopMatrix();
    };

    if (activity == NpcActivity::Read) {
        arm(-1, -48.0f + 9.0f * motion, -10.0f, .13f);
        arm( 1, -48.0f - 9.0f * motion,  10.0f, .13f);
        glPushMatrix();
        glTranslatef(0, 1.10f + .025f * alternate, .30f);
        glRotatef(5.0f * motion, 1, 0, 0);
        render::box({0, 0, 0}, {.42f, .30f, .04f}, {.88f, .78f, .28f});
        glPopMatrix();
    } else if (activity == NpcActivity::Teach || activity == NpcActivity::Present) {
        arm(-1, -22.0f + 12.0f * alternate, -14.0f, .08f);
        arm(1, -36.0f + 18.0f * motion, 12.0f, .12f);
        glPushMatrix();
        glTranslatef(.34f, 1.15f + .03f * motion, .10f);
        glRotatef(25.0f * alternate, 0, 1, 0);
        render::box({0, 0, 0}, {.05f, .05f, .62f}, {.82f, .72f, .28f});
        glPopMatrix();
    } else if (activity == NpcActivity::Game) {
        arm(-1, -34.0f + 7.0f * motion, -8.0f, .16f);
        arm( 1, -34.0f - 7.0f * motion,  8.0f, .16f);
        glPushMatrix();
        glTranslatef(0, 1.03f + .018f * alternate, .30f);
        glRotatef(3.0f * motion, 0, 1, 0);
        render::box({0, 0, 0}, {.38f, .08f, .16f}, {.12f, .15f, .18f});
        render::box({-.12f, .07f, .30f - .30f}, {.05f, .10f, .05f},
                    pulse > .5f ? Color{.95f, .16f, .12f} : Color{.48f, .08f, .06f});
        render::box({ .12f, .07f, .30f - .30f}, {.05f, .10f, .05f},
                    pulse <= .5f ? Color{.16f, .42f, .95f} : Color{.08f, .22f, .55f});
        glPopMatrix();
    } else if (activity == NpcActivity::Lab) {
        arm(-1, -30.0f + 18.0f * motion, -16.0f, .14f);
        arm( 1, -48.0f - 12.0f * motion,  15.0f, .14f);
        glPushMatrix();
        glTranslatef(.27f + .04f * motion, 1.02f + .02f * alternate, .18f);
        render::box({0, 0, 0}, {.22f, .18f, .16f}, {.18f, .55f, .78f});
        render::box({0, .12f, 0}, {.12f, .02f, .08f},
                    pulse > .45f ? Color{.2f, .95f, .45f} : Color{.06f, .34f, .16f});
        glPopMatrix();
    } else if (activity == NpcActivity::Serve || activity == NpcActivity::Cashier) {
        const float reachMotion = .05f * motion;
        arm(-1, -42.0f + 15.0f * motion, -12.0f, .18f + reachMotion);
        arm( 1, -42.0f - 15.0f * motion,  12.0f, .18f - reachMotion);
        glPushMatrix();
        glTranslatef(0, 1.05f + .02f * alternate, .30f + .035f * motion);
        render::box({0, 0, 0}, {.30f, .12f, .22f}, {.12f, .14f, .16f});
        glPopMatrix();
    } else if (activity == NpcActivity::Eat) {
        const float bite = std::max(0.0f, motion);
        arm(-1, -18.0f - 62.0f * bite, -12.0f, .12f + .12f * bite);
        arm( 1, -18.0f - 28.0f * (1.0f - bite),  12.0f, .12f);
        render::box({0, 1.12f + .20f * bite, .28f - .10f * bite},
                    {.08f, .08f, .08f}, {.92f, .65f, .18f});
    } else if (activity == NpcActivity::Talk) {
        arm(-1, -35.0f + 28.0f * motion, -20.0f, .12f);
        arm( 1, -35.0f - 28.0f * motion,  20.0f, .12f);
        render::box({-.28f, 1.08f + .08f * motion, .18f}, {.08f, .08f, .08f}, skin);
        render::box({ .28f, 1.08f - .08f * motion, .18f}, {.08f, .08f, .08f}, skin);
    } else {
        // Desk workers alternate between typing and checking the monitor.
        arm(-1, -35.0f + 14.0f * motion, -12.0f, .16f);
        arm( 1, -35.0f - 14.0f * motion,  12.0f, .16f);
        render::box({0, 1.08f, .25f}, {.18f, .08f, .12f}, {.12f, .15f, .18f});
    }
    glPopMatrix();
}

// Directional chair with 4 legs, cushioned seat, and backrest oriented by yaw
void chair(float x, float y, float z, float yawDegrees = 0.0f) {
    glPushMatrix();
    glTranslatef(x, y, z);
    if (yawDegrees != 0.0f) glRotatef(yawDegrees, 0, 1, 0);

    // 4 legs
    render::box({-.18f, .22f, -.18f}, {.04f, .44f, .04f}, legSteel);
    render::box({ .18f, .22f, -.18f}, {.04f, .44f, .04f}, legSteel);
    render::box({-.18f, .22f,  .18f}, {.04f, .44f, .04f}, legSteel);
    render::box({ .18f, .22f,  .18f}, {.04f, .44f, .04f}, legSteel);

    // Ergonomic seat cushion (center at y=0.45)
    render::box({0, .45f, 0}, {.48f, .06f, .48f}, cushionColor);

    // Backrest supports & backrest panel (at -Z when yaw=0, facing +Z)
    render::box({-.16f, .70f, -.21f}, {.035f, .48f, .035f}, legSteel);
    render::box({ .16f, .70f, -.21f}, {.035f, .48f, .035f}, legSteel);
    render::box({0, .75f, -.22f}, {.46f, .26f, .05f}, cushionColor);

    glPopMatrix();
}

// Square dining table set with 4 properly oriented chairs
void diningTableSet(float x, float y, float z, float w = 1.4f, float d = 1.4f) {
    // Table top
    render::texturedBox({x, y + .80f, z}, {w, .08f, d}, woodTop, 2);
    // Table frame & 4 legs
    const float hx = w * .42f, hz = d * .42f;
    render::box({x - hx, y + .38f, z - hz}, {.08f, .76f, .08f}, woodDark);
    render::box({x + hx, y + .38f, z - hz}, {.08f, .76f, .08f}, woodDark);
    render::box({x - hx, y + .38f, z + hz}, {.08f, .76f, .08f}, woodDark);
    render::box({x + hx, y + .38f, z + hz}, {.08f, .76f, .08f}, woodDark);

    // Centerpiece napkin / table number holder
    render::box({x, y + .88f, z}, {.14f, .08f, .14f}, chromeColor);

    // 4 neatly positioned chairs facing the table
    chair(x, y, z + d * .64f, 180.0f); // North chair faces South
    chair(x, y, z - d * .64f, 0.0f);   // South chair faces North
    chair(x + w * .64f, y, z, -90.0f); // East chair faces West
    chair(x - w * .64f, y, z, 90.0f);  // West chair faces East
}

// Round lounge table set with 4 symmetrical armchairs
void roundTableSet(float x, float y, float z, float radius = 0.72f) {
    // Circular table top and central pedestal
    render::cylinder({x, y + .80f, z}, radius, .08f, woodTop);
    render::cylinder({x, y + .38f, z}, .12f, .76f, chromeColor);
    render::cylinder({x, y + .04f, z}, .42f, .06f, legSteel);

    // Center floral/vase decor
    render::cylinder({x, y + .92f, z}, .10f, .16f, {.18f, .62f, .38f});

    // 4 chairs facing the center
    const float dist = radius + .36f;
    chair(x, y, z + dist, 180.0f);
    chair(x, y, z - dist, 0.0f);
    chair(x + dist, y, z, -90.0f);
    chair(x - dist, y, z, 90.0f);
}

// Professional administrative / consultation desk with staff chair and visitor chairs
void officeDesk(float x, float y, float z, float w = 1.9f, float d = 0.9f) {
    // Desk top
    render::texturedBox({x, y + .80f, z}, {w, .08f, d}, woodTop, 2);
    // Modesty front panel
    render::box({x, y + .40f, z - d * .45f}, {w * .92f, .65f, .04f}, woodDark);
    // Side drawer pedestals
    render::box({x - w * .40f, y + .38f, z}, {.36f, .76f, d * .88f}, woodDark);
    render::box({x + w * .40f, y + .38f, z}, {.36f, .76f, d * .88f}, woodDark);

    // Desktop computer / monitor and keyboard
    render::box({x, y + 1.15f, z - .15f}, {.52f, .32f, .04f}, {.12f, .14f, .16f});
    render::box({x, y + .90f, z - .15f}, {.12f, .18f, .12f}, chromeColor);
    render::box({x, y + .85f, z + .15f}, {.40f, .02f, .16f}, {.22f, .24f, .26f});

    // Executive staff chair behind desk (facing +Z toward visitor)
    chair(x, y, z - d * .75f, 0.0f);

    // Two visitor chairs in front of desk (facing -Z toward staff)
    chair(x - w * .28f, y, z + d * .75f, 180.0f);
    chair(x + w * .28f, y, z + d * .75f, 180.0f);
}

// Dedicated computer workstation for the Admission Room 2 digital assistant.
// The screen is intentionally angled toward the visitor side so it reads as a
// real usable terminal in first-person view rather than a floating monitor.
void seuGptDesk(float x, float y, float z) {
    render::texturedBox({x, y + .80f, z}, {1.65f, .08f, .82f}, woodTop, 2);
    render::box({x - .64f, y + .38f, z}, {.10f, .76f, .68f}, woodDark);
    render::box({x + .64f, y + .38f, z}, {.10f, .76f, .68f}, woodDark);

    // Monitor housing, luminous screen, and center stand.
    render::box({x, y + 1.22f, z + .14f}, {1.38f, .70f, .06f}, {.07f, .09f, .12f});
    render::box({x, y + 1.22f, z + .175f}, {1.20f, .56f, .018f}, {.035f, .12f, .16f});
    render::box({x, y + .98f, z + .12f}, {.12f, .18f, .08f}, legSteel);
    render::box({x, y + .90f, z + .12f}, {.42f, .025f, .22f}, legSteel);

    // Keyboard, mouse, and a small green status lamp.
    render::box({x, y + .89f, z + .18f}, {.52f, .025f, .20f}, {.18f, .20f, .23f});
    render::box({x + .35f, y + .90f, z + .18f}, {.08f, .035f, .11f}, {.82f, .84f, .88f});
    render::box({x + .52f, y + 1.22f, z + .21f}, {.08f, .035f, .018f}, {.20f, .95f, .45f});
    // The scene is mirrored at the view boundary, so raster text begins from
    // the +X side to appear on the visual left side of the monitor.
    render::text3d({x + .24f, y + 1.24f, z + .21f}, "SEUGPT", {.25f, .95f, .55f});

    // Visitor-side chair faces the workstation and leaves a clear approach.
    chair(x, y, z + .76f, 180.0f);
}

// Long service/teller counter with transaction window and chair
void serviceCounter(float x, float y, float z, float w = 2.8f) {
    render::box({x, y + .60f, z}, {w, 1.20f, .65f}, {.36f, .22f, .14f});
    render::box({x, y + 1.22f, z}, {w + .08f, .08f, .72f}, {.78f, .65f, .42f});
    // Staff chair behind counter
    chair(x, y, z - .75f, 0.0f);
}

// Money counting machine with hopper, keypad, and LED count screen
void moneyCounter(float x, float y, float z) {
    render::box({x, y + .16f, z}, {.42f, .32f, .36f}, {.15f, .17f, .20f});
    render::box({x, y + .32f, z - .08f}, {.36f, .12f, .18f}, {.25f, .27f, .30f}); // Cash hopper
    render::box({x, y + .24f, z + .185f}, {.22f, .10f, .02f}, {.08f, .85f, .35f}); // Green LED readout
}

// Comfortable modern sofa with armrests and cushions
void sofa(float x, float y, float z, float w = 2.6f, float d = 0.85f, float yaw = 0.0f) {
    glPushMatrix();
    glTranslatef(x, y, z);
    if (yaw != 0.0f) glRotatef(yaw, 0, 1, 0);

    // Base & seat cushion
    render::box({0, .32f, 0}, {w, .44f, d}, sofaLeather);
    // Backrest
    render::box({0, .68f, -d * .42f}, {w, .52f, .18f}, sofaLeather);
    // Left & right armrests
    render::box({-w * .46f, .55f, 0}, {.16f, .42f, d}, sofaLeather);
    render::box({ w * .46f, .55f, 0}, {.16f, .42f, d}, sofaLeather);

    glPopMatrix();
}

// Bookshelf with books
void bookshelf(float x, float y, float z, int shelves = 5) {
    render::box({x, y + 1.6f, z}, {.22f, 3.2f, 1.4f}, {.35f, .20f, .12f});
    for (int i = 0; i < shelves; ++i) {
        const float sy = y + .4f + i * .65f;
        render::box({x, sy, z}, {1.35f, .06f, .45f}, {.48f, .28f, .16f});
        // Books on shelf
        for (float bz = z - .55f; bz <= z + .55f; bz += .18f) {
            const Color bookCol = ((int)(bz * 10) % 2 == 0) ? Color{.2f, .4f, .75f} : Color{.75f, .25f, .18f};
            render::box({x, sy + .22f, bz}, {.18f, .38f, .14f}, bookCol);
        }
    }
}



// Authentic Architectural Elevator Portal & Illuminated 3D Cabin
void lift(float x, float y, float z, int floorNum = 1, float doorOpenAmount = 0.0f, bool carPresent = true, bool drawPortal = true) {
    const Color chromeCol{.85f, .88f, .92f};
    const Color steelDark{.22f, .24f, .27f};
    const Color steelBrushed{.72f, .75f, .80f};
    const Color potLightCol{1.0f, .96f, .85f};
    const Color glassCol{.25f, .75f, .90f, .45f};

    // =========================================================================
    // 1. ELEVATOR SHAFT & INTERIOR 3D CABIN (Extends 1.7m deep into +Z)
    // =========================================================================
    if (carPresent) {
    // Cabin Floor (Dark polished granite tile)
    render::box({x, y + .02f, z + .85f}, {2.24f, .04f, 1.70f}, {.15f, .16f, .18f});

    // Cabin Ceiling & 4 Recessed Warm LED Pot Lights
    render::box({x, y + 3.18f, z + .85f}, {2.24f, .06f, 1.70f}, steelBrushed);
    for (float dx : {-.55f, .55f}) {
        for (float dz : {-.45f, .45f}) {
            render::box({x + dx, y + 3.15f, z + .85f + dz}, {.24f, .02f, .24f}, potLightCol);
            render::box({x + dx, y + 3.14f, z + .85f + dz}, {.28f, .01f, .28f}, {.40f, .42f, .46f}); // Bezel
        }
    }

    // Cabin Side Walls (Brushed stainless steel with architectural vertical reveals)
    render::box({x - 1.11f, y + 1.60f, z + .85f}, {.04f, 3.16f, 1.70f}, steelBrushed);
    render::box({x + 1.11f, y + 1.60f, z + .85f}, {.04f, 3.16f, 1.70f}, steelBrushed);

    // Cabin Rear Wall & Full-Height Polished Elevator Mirror
    render::box({x, y + 1.60f, z + 1.70f}, {2.24f, 3.16f, .04f}, steelDark);
    render::box({x, y + 1.60f, z + 1.67f}, {2.08f, 2.90f, .02f}, {.90f, .94f, .98f}); // Mirror reflection

    // Interior Chrome Tubular Safety Handrails
    render::cylinder({x, y + .95f, z + 1.60f}, .025f, 2.05f, chromeCol); // Back wall rail
    render::box({x - .95f, y + .95f, z + 1.63f}, {.04f, .04f, .07f}, chromeCol);
    render::box({x + .95f, y + .95f, z + 1.63f}, {.04f, .04f, .07f}, chromeCol);

    // Interior Car Operating Panel (COP) on right side wall
    const float copX = x + 1.08f;
    render::box({copX, y + 1.55f, z + .55f}, {.025f, 1.60f, .28f}, {.20f, .22f, .25f});
    // Internal floor buttons [4], [3], [2], [1]
    const Color btnLit{.20f, .85f, 1.0f};
    const Color btnOff{.75f, .78f, .82f};
    render::box({copX - .015f, y + 1.95f, z + .50f}, {.01f, .07f, .07f}, floorNum == 4 ? btnLit : btnOff);
    render::box({copX - .015f, y + 1.95f, z + .60f}, {.01f, .07f, .07f}, floorNum == 3 ? btnLit : btnOff);
    render::box({copX - .015f, y + 1.82f, z + .50f}, {.01f, .07f, .07f}, floorNum == 2 ? btnLit : btnOff);
    render::box({copX - .015f, y + 1.82f, z + .60f}, {.01f, .07f, .07f}, floorNum == 1 ? btnLit : btnOff);
    // Interior digital LED readout
    render::box({copX - .015f, y + 2.15f, z + .55f}, {.01f, .12f, .22f}, {.08f, .10f, .14f});
    char inFlText[16]; std::snprintf(inFlText, sizeof(inFlText), "FL %d", floorNum);
    render::text3d({copX - .025f, y + 2.12f, z + .50f}, inFlText, {.15f, .95f, .40f});
    }

    // =========================================================================
    // 2. EXTERIOR ELEVATOR PORTAL, ARCHITRAVE & SILL
    // =========================================================================
    // Outer Stainless Steel Portal Architrave
    if (drawPortal) {
        render::box({x - 1.18f, y + 1.65f, z}, {.18f, 3.30f, .24f}, steelBrushed); // Left jamb
        render::box({x + 1.18f, y + 1.65f, z}, {.18f, 3.30f, .24f}, steelBrushed); // Right jamb
        render::box({x, y + 3.15f, z}, {2.54f, .30f, .24f}, steelBrushed);         // Header lintel
        render::box({x, y + .02f, z - .08f}, {2.36f, .04f, .22f}, {.42f, .45f, .48f}); // Grooved sill plate

    // Lintel Brand Plate ("OTIS / SCHINDLER 1600kg 21P")
        render::box({x, y + 3.08f, z - .122f}, {.72f, .08f, .01f}, {.15f, .17f, .20f});
        render::text3d({x - .32f, y + 3.05f, z - .135f}, "SEU LIFT - 1600kg", {.85f, .90f, .98f});
    }

    // =========================================================================
    // 3. DUAL TELESCOPING SLIDING DOORS (OPEN OR CLOSED WITH OBSERVATION PANELS)
    // =========================================================================
    const float dh = 2.85f;
    const float dy = y + .04f + dh * .5f;
    const float dz = z - .10f;

    if (doorOpenAmount > .01f) {
        // Telescoping leaves slide progressively into the jamb pockets.
        const float slide = .55f + .55f * std::min(1.0f, doorOpenAmount);
        render::box({x - slide, dy, dz}, {.94f, dh, .04f}, steelBrushed);
        render::box({x - slide, y + .22f, dz - .01f}, {.90f, .36f, .02f}, chromeCol);
        render::box({x + slide, dy, dz}, {.94f, dh, .04f}, steelBrushed);
        render::box({x + slide, y + .22f, dz - .01f}, {.90f, .36f, .02f}, chromeCol);
        if (doorOpenAmount > .98f)
            render::box({x, y + .025f, dz}, {1.84f, .03f, .16f}, {.82f, .72f, .35f});
    } else {
        // Closed doors with observation glass panels
        const float dw = .94f;
        // Left stainless steel door leaf with kick-plate
        render::box({x - .55f, dy, dz}, {dw, dh, .04f}, steelBrushed);
        render::box({x - .55f, y + .22f, dz - .01f}, {dw - .04f, .36f, .02f}, chromeCol);
        // Right stainless steel door leaf with kick-plate
        render::box({x + .55f, dy, dz}, {dw, dh, .04f}, steelBrushed);
        render::box({x + .55f, y + .22f, dz - .01f}, {dw - .04f, .36f, .02f}, chromeCol);

        // Center vertical safety rubber bumper seal
        render::box({x, dy, dz}, {.04f, dh, .05f}, {.10f, .11f, .12f});

        // Vertical Observation Glass Panels in each door (view into lit interior cabin)
        render::glassPanel({x - .38f, dy + .20f, dz}, {.18f, 1.65f, .02f}, glassCol);
        render::box({x - .38f, dy + .20f, dz}, {.20f, 1.67f, .03f}, chromeCol);
        render::glassPanel({x + .38f, dy + .20f, dz}, {.18f, 1.65f, .02f}, glassCol);
        render::box({x + .38f, dy + .20f, dz}, {.20f, 1.67f, .03f}, chromeCol);
    }

    // =========================================================================
    // 4. EXTERIOR HALL LANTERN DISPLAY & CALL STATION
    // =========================================================================
    // High-Contrast Digital LED Indicator Screen above doors
    render::box({x, y + 3.42f, z - .13f}, {.78f, .28f, .05f}, {.08f, .10f, .14f});
    render::box({x, y + 3.42f, z - .11f}, {.82f, .32f, .03f}, steelBrushed); // Chrome bezel
    char flText[16]; std::snprintf(flText, sizeof(flText), "FL %d", floorNum);
    render::text3d({x - .20f, y + 3.35f, z - .17f}, flText, {.15f, .95f, .40f}); // Glowing emerald green
    render::text3d({x + .14f, y + 3.35f, z - .17f}, floorNum == 4 ? "v" : (floorNum == 1 ? "^" : "^v"), {.20f, .85f, 1.0f});

    // Exterior Dual Call Station Button Panel on side door jamb
    render::box({x + 1.28f, y + 1.50f, z - .10f}, {.22f, .65f, .04f}, {.16f, .18f, .22f});
    render::box({x + 1.28f, y + 1.50f, z - .08f}, {.24f, .67f, .02f}, steelBrushed);
    // Illuminated tactile call buttons with cyan halos
    render::cylinder({x + 1.28f, y + 1.65f, z - .13f}, .035f, .03f, {.20f, .85f, 1.0f}); // Up button
    render::cylinder({x + 1.28f, y + 1.35f, z - .13f}, .035f, .03f, {.20f, .85f, 1.0f}); // Down button

    // Directory Plaque beside the elevator bank
    render::box({x - 1.55f, y + 1.70f, z - .10f}, {.42f, 1.20f, .03f}, {.14f, .16f, .20f});
    render::box({x - 1.55f, y + 1.70f, z - .08f}, {.44f, 1.22f, .02f}, steelBrushed);
    render::text3d({x - 1.72f, y + 2.15f, z - .12f}, "FL 4: SKY",    {.85f, .88f, .95f});
    render::text3d({x - 1.72f, y + 1.88f, z - .12f}, "FL 3: AUD",    {.85f, .88f, .95f});
    render::text3d({x - 1.72f, y + 1.61f, z - .12f}, "FL 2: LIB",    {.85f, .88f, .95f});
    render::text3d({x - 1.72f, y + 1.34f, z - .12f}, "FL 1: LOBBY",  {.85f, .88f, .95f});
}

} // anonymous namespace

void setLiftPresentation(float floorPosition, float doorOpenAmount) {
    liftPresentationFloor = std::max(1.0f, std::min(4.0f, floorPosition));
    liftPresentationDoor = std::max(0.0f, std::min(1.0f, doorOpenAmount));
}

void renderFurniture(bool labels) {
    const float gY = 1.2f;  // Ground Floor Y
    const float f2Y = 5.2f; // Second Floor Y

    // =========================================================================
    // 1. ADMISSION OFFICE 1 (Ground Floor: x in [-24, -11.5], z in [9.5, 14.0])
    // Required sequence: Outer glass door -> Inner glass door -> Front admission desk
    // -> Left side: multiple guardian waiting chairs -> Door -> Locked washroom
    // =========================================================================
    // Inner Vestibule Glass Portal (at x = -13.2m, creating the outer->inner door sequence)
    render::box({-13.2f, gY + 1.45f, 10.7f}, {.10f, 2.90f, .07f}, {.16f, .18f, .22f});
    render::box({-13.2f, gY + 1.45f, 12.9f}, {.10f, 2.90f, .07f}, {.16f, .18f, .22f});
    render::box({-13.2f, gY + 2.85f, 11.8f}, {.10f, .08f, 2.2f}, {.16f, .18f, .22f});
    render::box({-13.2f, gY + .015f, 11.8f}, {.14f, .03f, 2.2f}, {.78f, .75f, .80f});
    // Inner door leaves swung open into office
    render::glassPanel({-13.45f, gY + 1.35f, 11.1f}, {.48f, 2.62f, .025f}, {.20f, .78f, .88f, .38f});
    render::glassPanel({-13.45f, gY + 1.35f, 12.5f}, {.48f, 2.62f, .025f}, {.20f, .78f, .88f, .38f});
    render::cylinder({-13.65f, gY + 1.50f, 11.1f}, .022f, 1.30f, chromeColor);
    render::cylinder({-13.65f, gY + 1.50f, 12.5f}, .022f, 1.30f, chromeColor);

    // Front Admission Consultation Desk directly in front of entry facing East (+X)
    render::texturedBox({-16.2f, gY + .80f, 11.8f}, {.95f, .08f, 2.2f}, woodTop, 2);
    render::box({-15.75f, gY + .40f, 11.8f}, {.04f, .65f, 2.1f}, woodDark); // Front modesty panel
    render::box({-16.2f, gY + .38f, 10.95f}, {.88f, .76f, .36f}, woodDark); // Side drawers
    render::box({-16.2f, gY + .38f, 12.65f}, {.88f, .76f, .36f}, woodDark);
    // Dual desktop computer workstations
    render::box({-16.35f, gY + 1.15f, 11.35f}, {.04f, .32f, .52f}, {.12f, .14f, .16f});
    render::box({-16.35f, gY + .90f, 11.35f}, {.12f, .18f, .12f}, chromeColor);
    render::box({-16.05f, gY + .85f, 11.35f}, {.16f, .02f, .40f}, {.22f, .24f, .26f});
    render::box({-16.35f, gY + 1.15f, 12.25f}, {.04f, .32f, .52f}, {.12f, .14f, .16f});
    render::box({-16.35f, gY + .90f, 12.25f}, {.12f, .18f, .12f}, chromeColor);
    render::box({-16.05f, gY + .85f, 12.25f}, {.16f, .02f, .40f}, {.22f, .24f, .26f});
    // University Prospectus Brochure stands
    render::box({-15.9f, gY + .92f, 11.8f}, {.18f, .16f, .28f}, {.18f, .45f, .85f});

    // Executive staff chairs behind desk facing East (+X) toward entry.
    // chair() faces +Z at yaw 0, so +90 degrees turns it toward +X.
    chair(-17.1f, gY, 11.35f, 90.0f);
    chair(-17.1f, gY, 12.25f, 90.0f);

    // Two visitor consultation chairs in front of desk facing West (-X) toward staff.
    chair(-15.1f, gY, 11.35f, -90.0f);
    chair(-15.1f, gY, 12.25f, -90.0f);
    airConditioner(-23.82f, gY, 12.2f, true);
    // Keep the admission officer in the staff position behind the desk,
    // clear of the monitor and keyboard on the visitor-facing side.
    npc(-17.1f, gY, 11.35f, 90.0f, NpcActivity::Desk, {.18f, .38f, .72f});

    // Left guardian waiting area: 2 parallel rows of 4 cushioned chairs
    // Row 1 (z = 10.4m)
    render::box({-20.7f, gY + .18f, 10.4f}, {3.4f, .06f, .10f}, legSteel);
    for (float cx : {-22.2f, -21.2f, -20.2f, -19.2f}) chair(cx, gY, 10.4f, 0.0f);
    // Row 2 (z = 11.8m)
    render::box({-20.7f, gY + .18f, 11.8f}, {3.4f, .06f, .10f}, legSteel);
    for (float cx : {-22.2f, -21.2f, -20.2f, -19.2f}) chair(cx, gY, 11.8f, 0.0f);

    // Central magazine & prospectus table
    render::texturedBox({-20.7f, gY + .45f, 12.9f}, {2.0f, .06f, .70f}, woodTop, 2);
    render::box({-20.7f, gY + .22f, 12.9f}, {1.8f, .44f, .55f}, woodDark);

    // University water cooler dispenser
    render::box({-23.2f, gY + .55f, 10.2f}, {.40f, 1.10f, .40f}, {.90f, .92f, .94f});
    render::cylinder({-23.2f, gY + 1.30f, 10.2f}, .14f, .38f, {.20f, .75f, .95f, .6f});

    // Locked washroom door & interior fixture (Northwest corner)
    render::box({-22.5f, gY + 1.45f, 13.92f}, {1.20f, 2.90f, .08f}, {.16f, .18f, .22f});
    render::box({-22.5f, gY + 1.30f, 13.92f}, {1.05f, 2.60f, .04f}, {.78f, .55f, .30f});
    render::cylinder({-22.15f, gY + 1.10f, 13.88f}, .025f, .08f, chromeColor);
    render::box({-22.5f, gY + 2.85f, 13.88f}, {1.20f, .22f, .04f}, {.14f, .17f, .22f});
    render::text3d({-23.0f, gY + 2.80f, 13.82f}, "LOCKED WASHROOM", {1, .85f, .2f});
    render::box({-22.5f, gY + .45f, 14.4f}, {.55f, .55f, .55f}, {.92f, .92f, .94f});

    // =========================================================================
    // 2. ADMISSION OFFICE 2 (Ground Floor: x in [-24, -16.2], z in [14.0, 21.6])
    // Administrative workspace: multiple desks, office chairs, executive sofa
    // =========================================================================
    officeDesk(-21.2f, gY, 16.5f, 1.9f, .85f);
    officeDesk(-18.5f, gY, 19.4f, 1.9f, .85f);
    seuGptDesk(-22.35f, gY, 19.0f);
    sofa(-20.2f, gY, 14.6f, 2.7f, .80f, 0.0f);
    // Coffee table in front of sofa
    render::box({-20.2f, gY + .35f, 15.35f}, {1.5f, .30f, .60f}, woodTop);
    airConditioner(-23.82f, gY, 18.4f, true);
    // officeDesk() places its staff chair behind the desk at z - d*.75.
    npc(-21.2f, gY, 15.86f, 0.0f, NpcActivity::Desk, {.24f, .52f, .32f});
    npc(-18.5f, gY, 18.76f, 0.0f, NpcActivity::Talk, {.68f, .28f, .22f});

    // =========================================================================
    // 3. BANK 1 (Ground Floor: x in [-16.2, -11.5], z in [14.0, 21.6])
    // Front desk, chair, money counting machine
    // =========================================================================
    serviceCounter(-14.0f, gY, 18.5f, 2.6f);
    chair(-14.0f, gY, 17.2f, 0.0f); // Customer chair
    moneyCounter(-14.8f, gY + 1.22f, 18.5f);
    airConditioner(-16.05f, gY, 20.5f, true);
    // Staff position is behind the counter, beside its dedicated chair.
    npc(-14.0f, gY, 17.65f, 0.0f, NpcActivity::Cashier, {.12f, .42f, .72f});

    // =========================================================================
    // 4. BANK 2 (Ground Floor: x in [7.4, 12.0], z in [17.8, 22.0])
    // Front desk, chair, money counting machine
    // =========================================================================
    serviceCounter(9.7f, gY, 19.8f, 2.5f);
    chair(9.7f, gY, 18.5f, 0.0f); // Customer chair
    moneyCounter(10.4f, gY + 1.22f, 19.8f);
    airConditioner(11.82f, gY, 20.6f, true);
    npc(9.7f, gY, 19.00f, 0.0f, NpcActivity::Cashier, {.72f, .32f, .16f});

    // =========================================================================
    // 5. CAFETERIA (Ground Floor: x in [-10.2, 10.2], z in [29.8, 40.0])
    // 15 square tables in a clean, functional dining arrangement with chairs
    // 3 rows of 5 tables properly spaced with comfortable walking aisles
    // =========================================================================
    const float cafZ[3] = {32.0f, 35.2f, 38.4f};
    const float cafX[5] = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f};
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 5; ++c) {
            diningTableSet(cafX[c], gY, cafZ[r], 1.35f, 1.35f);
        }
    }
    airConditioner(0.0f, gY, 39.65f, false);
    npc(-4.0f, gY, 36.10f, 180.0f, NpcActivity::Eat, {.20f, .48f, .78f});
    npc(4.0f, gY, 39.30f, 180.0f, NpcActivity::Talk, {.78f, .28f, .18f});
    npc(0.0f, gY, 31.10f, 0.0f, NpcActivity::Eat, {.24f, .68f, .38f});

    // =========================================================================
    // 6. FACULTY LOUNGE (Ground Floor: x in [-24, -9.8], z in [28.2, 33.6])
    // 5 round tables with chairs around them for conversational sitting
    // =========================================================================
    roundTableSet(-21.0f, gY, 29.8f, 0.75f);
    roundTableSet(-16.8f, gY, 29.8f, 0.75f);
    roundTableSet(-12.6f, gY, 29.8f, 0.75f);
    roundTableSet(-18.9f, gY, 32.2f, 0.75f);
    roundTableSet(-14.7f, gY, 32.2f, 0.75f);
    airConditioner(-10.05f, gY, 30.8f, true);
    npc(-18.9f, gY, 33.35f, 180.0f, NpcActivity::Talk, {.48f, .26f, .18f});
    npc(-14.7f, gY, 31.05f, 0.0f, NpcActivity::Talk, {.18f, .34f, .62f});

    // =========================================================================
    // 7. FOOD SHOPS 1-5 (FULLY STOCKED SERVICE COUNTERS, FOOD WARMERS & DRINKS)
    // =========================================================================
    const Color foodBurger{.48f, .28f, .14f};
    const Color foodFries{.96f, .82f, .18f};
    const Color foodChicken{.82f, .38f, .12f};
    const Color foodPizza{.94f, .55f, .15f};
    const Color foodDonut{.88f, .45f, .55f};
    const Color foodCroissant{.85f, .65f, .25f};
    const Color foodRice{.95f, .90f, .65f};
    const Color foodNoodle{.88f, .70f, .22f};
    const Color glassCase{.20f, .78f, .90f, .40f};

    // --- FOOD SHOP 1: SEU DELI & BURGERS (x in [-24, -20.8], z in [36.6, 40.0]) ---
    // Service counter facing East into Cafeteria
    render::box({-21.6f, gY + .55f, 38.3f}, {.65f, 1.10f, 3.0f}, {.28f, .30f, .34f});
    render::box({-21.6f, gY + 1.12f, 38.3f}, {.72f, .06f, 3.1f}, {.85f, .88f, .92f}); // Granite top
    chair(-22.6f, gY, 38.3f, -90.0f); // Staff chair facing East

    // POS Cashier Register Terminal
    render::box({-21.6f, gY + 1.25f, 37.3f}, {.32f, .22f, .30f}, {.15f, .17f, .20f});
    render::box({-21.55f, gY + 1.35f, 37.3f}, {.02f, .16f, .22f}, {.18f, .85f, 1.0f}); // POS screen

    // Heated Glass Food Warmer Showcase (Burgers, Crispy Chicken & Fries)
    render::box({-21.6f, gY + 1.20f, 38.7f}, {.55f, .08f, 1.8f}, {.25f, .26f, .28f});
    render::glassPanel({-21.6f, gY + 1.45f, 38.7f}, {.50f, .42f, 1.7f}, glassCase);
    // Burgers (Buns with lettuce and patties)
    for (float bz : {38.1f, 38.4f, 38.7f}) {
        render::cylinder({-21.6f, gY + 1.28f, bz}, .12f, .10f, foodBurger);
        render::cylinder({-21.6f, gY + 1.32f, bz}, .13f, .02f, {.15f, .75f, .20f}); // Lettuce
        render::cylinder({-21.6f, gY + 1.34f, bz}, .12f, .06f, foodBurger);        // Top bun
    }
    // French fries box & fried chicken
    render::box({-21.6f, gY + 1.32f, 39.1f}, {.18f, .22f, .14f}, {.85f, .15f, .15f});
    render::box({-21.6f, gY + 1.44f, 39.1f}, {.16f, .08f, .12f}, foodFries);
    render::cylinder({-21.6f, gY + 1.30f, 39.4f}, .10f, .18f, foodChicken);

    // Overhead Menu Board
    render::text3d({-21.0f, gY + 2.45f, 37.0f}, "BURGER $4.00 | CHICKEN $4.50 | FRIES $2.00", {1, 1, 1});
    airConditioner(-23.82f, gY, 38.3f, true);
    npc(-22.85f, gY, 38.3f, 90.0f, NpcActivity::Serve, {.72f, .20f, .12f});

    // Commercial Upright Beverage Cooler on Back Wall
    render::box({-23.5f, gY + 1.05f, 38.8f}, {.55f, 2.10f, .95f}, {.18f, .20f, .24f});
    render::glassPanel({-23.2f, gY + 1.05f, 38.8f}, {.02f, 1.95f, .85f}, glassCase);
    // Soda cans on shelves (Red Coke, Green Sprite, Blue Pepsi)
    for (float cy : {gY + .55f, gY + 1.05f, gY + 1.55f}) {
        render::cylinder({-23.4f, cy, 38.55f}, .04f, .12f, {.85f, .12f, .12f});
        render::cylinder({-23.4f, cy, 38.75f}, .04f, .12f, {.15f, .75f, .25f});
        render::cylinder({-23.4f, cy, 38.95f}, .04f, .12f, {.15f, .35f, .85f});
    }

    // Kitchen Prep Table & Condiment Pumps
    render::box({-23.5f, gY + .50f, 37.2f}, {.55f, 1.00f, 1.2f}, legSteel);
    render::cylinder({-21.6f, gY + 1.22f, 37.8f}, .04f, .12f, {.85f, .12f, .12f}); // Ketchup pump
    render::cylinder({-21.6f, gY + 1.22f, 37.9f}, .04f, .12f, {.95f, .85f, .15f}); // Mustard pump

    // --- FOOD SHOP 2: PIZZA & HOT ROLLS (x in [-24, -20.8], z in [33.6, 36.6]) ---
    render::box({-21.6f, gY + .55f, 35.1f}, {.65f, 1.10f, 2.7f}, {.28f, .30f, .34f});
    render::box({-21.6f, gY + 1.12f, 35.1f}, {.72f, .06f, 2.8f}, {.85f, .88f, .92f});
    chair(-22.6f, gY, 35.1f, -90.0f);

    // POS Register
    render::box({-21.6f, gY + 1.25f, 34.2f}, {.32f, .22f, .30f}, {.15f, .17f, .20f});
    render::box({-21.55f, gY + 1.35f, 34.2f}, {.02f, .16f, .22f}, {.18f, .85f, 1.0f});

    // Hot Pizza & Baked Goods Showcase
    render::box({-21.6f, gY + 1.20f, 35.3f}, {.55f, .08f, 1.5f}, {.25f, .26f, .28f});
    render::glassPanel({-21.6f, gY + 1.45f, 35.3f}, {.50f, .42f, 1.4f}, glassCase);
    // Pizza pan & slices
    render::cylinder({-21.6f, gY + 1.26f, 34.9f}, .22f, .03f, foodPizza);
    render::box({-21.6f, gY + 1.28f, 35.4f}, {.18f, .06f, .18f}, foodCroissant); // Golden patties
    render::cylinder({-21.6f, gY + 1.28f, 35.7f}, .08f, .14f, foodChicken);   // Hot chicken roll

    // Overhead Menu Board
    render::text3d({-21.0f, gY + 2.45f, 34.0f}, "PIZZA SLICE $3 | SPICY ROLL $2.50 | SAMOSA $2", {1, 1, 1});
    airConditioner(-23.82f, gY, 35.0f, true);
    npc(-22.85f, gY, 35.1f, 90.0f, NpcActivity::Serve, {.82f, .25f, .12f});

    // Microwave & Pizza Box Stack
    render::box({-23.5f, gY + .95f, 35.6f}, {.45f, .32f, .55f}, {.75f, .78f, .82f}); // Microwave
    render::box({-23.5f, gY + .85f, 34.4f}, {.45f, .30f, .45f}, {.85f, .75f, .60f}); // Pizza boxes

    // --- FOOD SHOP 3: BAKERY & CAFE (x in [13.8, 16.6], z in [36.0, 39.0]) ---
    render::box({14.4f, gY + .55f, 37.5f}, {.65f, 1.10f, 2.7f}, {.28f, .30f, .34f});
    render::box({14.4f, gY + 1.12f, 37.5f}, {.72f, .06f, 2.8f}, {.85f, .88f, .92f});
    chair(15.4f, gY, 37.5f, 90.0f);

    // POS Register
    render::box({14.4f, gY + 1.25f, 38.3f}, {.32f, .22f, .30f}, {.15f, .17f, .20f});
    render::box({14.35f, gY + 1.35f, 38.3f}, {.02f, .16f, .22f}, {.18f, .85f, 1.0f});

    // Multi-Tier Bakery Glass Showcase (Donuts, Croissants & Muffins)
    render::box({14.4f, gY + 1.20f, 37.1f}, {.55f, .08f, 1.5f}, {.25f, .26f, .28f});
    render::glassPanel({14.4f, gY + 1.45f, 37.1f}, {.50f, .42f, 1.4f}, glassCase);
    render::cylinder({14.4f, gY + 1.28f, 36.6f}, .10f, .05f, foodDonut);     // Glazed donut
    render::cylinder({14.4f, gY + 1.28f, 36.9f}, .10f, .08f, foodBurger);    // Chocolate muffin
    render::box({14.4f, gY + 1.28f, 37.3f}, {.14f, .08f, .22f}, foodCroissant); // Butter croissant

    // Commercial Espresso Coffee Machine with Steam Wands
    render::box({14.4f, gY + 1.35f, 37.8f}, {.40f, .40f, .35f}, {.75f, .78f, .82f});
    render::cylinder({14.25f, gY + 1.25f, 37.8f}, .03f, .08f, chromeColor); // Coffee cup

    // Overhead Menu Board
    render::text3d({14.2f, gY + 2.45f, 36.3f}, "ESPRESSO $2 | CAPPUCCINO $3 | CROISSANT $2.5", {1, 1, 1});
    airConditioner(16.35f, gY, 37.5f, true);
    npc(15.65f, gY, 37.5f, -90.0f, NpcActivity::Serve, {.42f, .22f, .12f});

    // --- FOOD SHOP 4: FRESH JUICE BAR (x in [13.8, 16.6], z in [31.5, 35.0]) ---
    render::box({14.4f, gY + .55f, 33.25f}, {.65f, 1.10f, 3.2f}, {.28f, .30f, .34f});
    render::box({14.4f, gY + 1.12f, 33.25f}, {.72f, .06f, 3.3f}, {.85f, .88f, .92f});
    chair(15.4f, gY, 33.25f, 90.0f);

    // POS Register
    render::box({14.4f, gY + 1.25f, 34.3f}, {.32f, .22f, .30f}, {.15f, .17f, .20f});
    render::box({14.35f, gY + 1.35f, 34.3f}, {.02f, .16f, .22f}, {.18f, .85f, 1.0f});

    // Fresh Fruit Display & Smoothie Blenders
    render::box({14.4f, gY + 1.20f, 32.7f}, {.55f, .08f, 1.8f}, {.25f, .26f, .28f});
    render::glassPanel({14.4f, gY + 1.45f, 32.7f}, {.50f, .42f, 1.7f}, glassCase);
    // Fresh fruit bowls (Orange, Green Apple, Watermelon)
    render::cylinder({14.4f, gY + 1.28f, 32.1f}, .12f, .08f, {.95f, .55f, .12f});
    render::cylinder({14.4f, gY + 1.28f, 32.4f}, .12f, .08f, {.25f, .85f, .25f});
    render::cylinder({14.4f, gY + 1.28f, 32.7f}, .14f, .06f, {.85f, .15f, .22f});
    // Two high-speed commercial juice blenders
    render::cylinder({14.4f, gY + 1.35f, 33.2f}, .08f, .26f, {.20f, .85f, 1.0f});
    render::cylinder({14.4f, gY + 1.35f, 33.5f}, .08f, .26f, {.95f, .75f, .18f});

    // Overhead Menu Board
    render::text3d({14.2f, gY + 2.45f, 32.0f}, "MANGO JUICE $3 | SMOOTHIE $3.50 | FRUIT BOWL $3", {1, 1, 1});
    airConditioner(16.35f, gY, 33.25f, true);
    npc(15.65f, gY, 33.25f, -90.0f, NpcActivity::Serve, {.18f, .62f, .30f});

    // --- FOOD SHOP 5: ASIAN NOODLE BOWL (x in [10.2, 14.0], z in [38.0, 40.0]) ---
    render::box({12.1f, gY + .55f, 38.6f}, {3.4f, 1.10f, .65f}, {.28f, .30f, .34f});
    render::box({12.1f, gY + 1.12f, 38.6f}, {3.5f, .06f, .72f}, {.85f, .88f, .92f});
    chair(12.1f, gY, 39.4f, 180.0f);

    // POS Register
    render::box({10.9f, gY + 1.25f, 38.6f}, {.30f, .22f, .32f}, {.15f, .17f, .20f});
    render::box({10.9f, gY + 1.35f, 38.55f}, {.22f, .16f, .02f}, {.18f, .85f, 1.0f});

    // Heated Bain-Marie Buffet Warmer Counter (Fried Rice & Noodles)
    render::box({12.8f, gY + 1.20f, 38.6f}, {2.0f, .08f, .55f}, {.75f, .78f, .82f});
    render::glassPanel({12.8f, gY + 1.45f, 38.6f}, {1.9f, .42f, .50f}, glassCase);
    render::box({12.1f, gY + 1.26f, 38.6f}, {.48f, .04f, .36f}, foodRice);
    render::box({12.7f, gY + 1.26f, 38.6f}, {.48f, .04f, .36f}, foodNoodle);
    render::box({13.3f, gY + 1.26f, 38.6f}, {.48f, .04f, .36f}, foodChicken);

    // Commercial Rice Cooker on Back Counter
    render::cylinder({12.8f, gY + 1.05f, 39.6f}, .18f, .28f, {.85f, .88f, .92f});

    // Overhead Menu Board
    render::text3d({10.6f, gY + 2.45f, 38.4f}, "FRIED RICE $3.50 | CHOWMEIN $4 | DUMPLINGS $3", {1, 1, 1});
    airConditioner(13.8f, gY, 39.65f, false);
    npc(12.1f, gY, 39.45f, 180.0f, NpcActivity::Serve, {.78f, .48f, .12f});

    // =========================================================================
    // 8. SEU UNIVERSITY STATIONERY & BOOKSTORE (x in [12.0, 16.6], z in [16.5, 22.0])
    // Comprehensive bookstore: 4 full bookcases, central gondola with notebook stacks,
    // pen carousels, glass calculator showcase, photocopy center & checkout desk
    // =========================================================================
    // 4 Perimeter and Central Bookcases packed with Academic Textbooks
    bookshelf(16.2f, gY, 18.2f, 5); // CS & Math Textbooks
    bookshelf(16.2f, gY, 20.4f, 5); // Engineering & Science
    bookshelf(13.8f, gY, 21.6f, 5); // Business & Architecture
    bookshelf(15.5f, gY, 21.6f, 5); // Literature & Reference Manuals

    // Central Island Stationery Gondola Display (Notebook Stacks & Paper Reams)
    render::box({14.3f, gY + .45f, 19.4f}, {2.2f, .90f, .85f}, woodDark);
    render::box({14.3f, gY + .92f, 19.4f}, {2.3f, .05f, .90f}, woodTop);
    // Stacks of University Spiral Notebooks (Blue, Red, Green, Gold)
    for (float nx : {13.5f, 13.9f, 14.3f, 14.7f, 15.1f}) {
        const Color nCol = (nx < 14.0f) ? Color{.2f, .45f, .85f} : (nx < 14.5f ? Color{.85f, .22f, .18f} : Color{.18f, .75f, .32f});
        render::box({nx, gY + 1.02f, 19.2f}, {.24f, .15f, .32f}, nCol);
        render::box({nx, gY + 1.02f, 19.6f}, {.24f, .15f, .32f}, {.95f, .95f, .98f}); // A4 Paper reams
    }

    // Glass Showcase Display Counter (Scientific Calculators, USBs & Drawing Sets)
    render::box({12.8f, gY + .45f, 19.2f}, {.65f, .90f, 1.4f}, woodDark);
    render::glassPanel({12.8f, gY + 1.15f, 19.2f}, {.60f, .50f, 1.3f}, glassCase);
    render::box({12.8f, gY + .98f, 18.8f}, {.18f, .03f, .26f}, {.15f, .16f, .18f}); // Casio Calculator
    render::box({12.8f, gY + .98f, 19.2f}, {.16f, .02f, .22f}, {.25f, .55f, .85f}); // Compass box
    render::box({12.8f, gY + .98f, 19.6f}, {.14f, .03f, .18f}, {.85f, .85f, .20f}); // USB drives

    // Rotating Pen & Marker Carousel Displays
    render::cylinder({12.8f, gY + 1.15f, 20.2f}, .12f, .35f, {.85f, .15f, .18f}); // Red/blue pens
    render::cylinder({12.8f, gY + 1.15f, 20.6f}, .12f, .35f, {.15f, .75f, .25f}); // Highlighters

    // High-Volume Commercial Photocopier & Multi-Function Printing Center
    const float copX2 = 12.6f;
    const float copZ2 = 21.2f;
    render::box({copX2, gY + .58f, copZ2}, {.85f, 1.16f, 1.05f}, {.20f, .22f, .26f}); // Photocopier chassis
    render::box({copX2, gY + 1.18f, copZ2}, {.75f, .04f, .95f}, {.78f, .80f, .85f});  // Scanner platen glass
    render::box({copX2, gY + 1.30f, copZ2}, {.70f, .14f, .90f}, {.28f, .30f, .34f});  // Top document feeder
    render::box({copX2 + .35f, gY + 1.32f, copZ2 - .30f}, {.18f, .14f, .03f}, {.15f, .95f, .45f}); // Touchscreen
    render::box({copX2 - .45f, gY + .85f, copZ2}, {.22f, .04f, .55f}, {.35f, .38f, .42f}); // Output paper tray
    render::box({copX2 - .45f, gY + .92f, copZ2}, {.20f, .10f, .45f}, {1.0f, 1.0f, 1.0f}); // Printed document stack

    // Bookstore Checkout & POS Counter (facing wide cross-corridor at z = 18.2m)
    render::box({14.8f, gY + .55f, 19.1f}, {1.8f, 1.10f, .65f}, {.35f, .20f, .12f});
    render::box({14.8f, gY + 1.12f, 19.1f}, {1.9f, .06f, .72f}, {.78f, .65f, .42f});
    chair(14.8f, gY, 19.8f, 180.0f); // Cashier chair
    // Cash Register POS & Barcode Scanner
    render::box({14.4f, gY + 1.25f, 19.1f}, {.30f, .20f, .28f}, {.15f, .17f, .20f});
    render::box({14.4f, gY + 1.34f, 19.05f}, {.22f, .15f, .02f}, {.18f, .85f, 1.0f});

    // Bookstore Department Overhead Directional Labels
    render::text3d({16.0f, gY + 2.5f, 19.2f}, "TEXTBOOKS", {.95f, .90f, .25f});
    render::text3d({16.0f, gY + 2.5f, 20.6f}, "ENGINEERING", {.95f, .90f, .25f});
    render::text3d({13.2f, gY + 2.5f, 21.8f}, "REFERENCE", {.95f, .90f, .25f});
    render::text3d({12.3f, gY + 2.2f, 21.2f}, "XEROX PRINT", {.20f, .95f, .45f});
    airConditioner(16.35f, gY, 20.4f, true);
    npc(14.8f, gY, 20.10f, 180.0f, NpcActivity::Cashier, {.18f, .30f, .68f});
    npc(13.6f, gY, 20.8f, 0.0f, NpcActivity::Read, {.68f, .24f, .18f});

    // =========================================================================
    // 9. GAMING ROOM 1 & GAMING ROOM 2 (Ground Floor: x in [3.6, 16.6], z in [9.5, 16.2])
    // All outside walls are transparent glass.
    // Room 1 (Outer): Carrom table, Table Tennis, 8-Ball Pool table
    // Room 2 (Inner): Sitting area, Carrom, Chess, Rubik's cube, Ludo
    // =========================================================================
    // --- GAMING ROOM 1 ---
    // 1. Grand 85-Inch Esports Tournament Gaming Display Screen (Mounted on divider wall at x = 5.8m, z = 12.92m)
    render::box({5.8f, gY + 2.1f, 12.92f}, {3.4f, 1.9f, .08f}, {.10f, .12f, .16f}); // Titanium chassis
    render::box({5.8f, gY + 2.1f, 12.90f}, {3.48f, 1.98f, .04f}, {.10f, .55f, .95f, .45f}); // Cyan RGB halo
    render::box({5.8f, gY + 2.1f, 12.96f}, {3.22f, 1.72f, .02f}, {.025f, .035f, .055f}); // OLED active display
    render::box({5.8f, gY + 1.05f, 12.96f}, {2.8f, .15f, .14f}, {.14f, .16f, .19f}); // Soundbar
    render::text3d({4.3f, gY + 2.75f, 12.99f}, "SEU ESPORTS ARENA - GAMING SCREEN", {.25f, .92f, 1.0f});
    render::text3d({4.3f, gY + 2.40f, 12.99f}, "PLAY 5 ARCADE GAMES ON THIS SCREEN:", {1, 1, 1});
    render::text3d({4.3f, gY + 2.05f, 12.99f}, "[1] TTT  [2] RPS  [3] 2048  [4] CUBE  [5] LUDO", {.95f, .82f, .25f});
    render::text3d({4.3f, gY + 1.60f, 12.99f}, ">> PRESS 'E' TO PLAY ON SCREEN <<", {.20f, .96f, .45f});
    airConditioner(16.35f, gY, 14.7f, true);
    npc(9.4f, gY, 16.10f, 180.0f, NpcActivity::Game, {.18f, .48f, .78f});

    // Arcade Console Desk with Joysticks & Illuminated Buttons
    render::box({5.8f, gY + .45f, 13.40f}, {2.6f, .90f, .50f}, {.14f, .16f, .20f});
    render::box({5.8f, gY + .91f, 13.40f}, {2.5f, .04f, .46f}, {.08f, .10f, .14f});
    render::cylinder({5.2f, gY + .98f, 13.40f}, .02f, .10f, {.85f, .15f, .12f});
    render::cylinder({6.4f, gY + .98f, 13.40f}, .02f, .10f, {.15f, .45f, .85f});

    // Table 1: Official Tournament Carrom Board & Arcade Station
    render::box({5.8f, gY + .75f, 14.8f}, {1.35f, .08f, 1.35f}, {.15f, .12f, .08f});
    render::box({5.8f, gY + .80f, 14.8f}, {1.20f, .04f, 1.20f}, {.95f, .90f, .78f});
    chair(5.8f, gY, 15.6f, 180.0f); chair(5.8f, gY, 14.0f, 0.0f);
    chair(6.6f, gY, 14.8f, -90.0f); chair(5.0f, gY, 14.8f, 90.0f);
    render::box({5.0f, gY + 1.12f, 14.8f}, {.38f, .28f, .05f}, {.12f, .14f, .18f});
    render::text3d({4.85f, gY + 1.12f, 14.76f}, "2048 SCREEN", {.15f, .85f, 1.0f});

    // Table 2: Table Tennis Table & Match Score Screen
    render::box({9.4f, gY + .76f, 14.8f}, {3.0f, .08f, 1.5f}, {.12f, .48f, .28f});
    render::box({9.4f, gY + .81f, 14.8f}, {2.95f, .01f, .04f}, {1, 1, 1});
    render::box({9.4f, gY + .92f, 14.8f}, {.04f, .24f, 1.60f}, {.85f, .88f, .92f});
    render::cylinder({8.6f, gY + .82f, 14.5f}, .10f, .02f, {.85f, .15f, .12f});
    render::cylinder({10.2f, gY + .82f, 15.1f}, .10f, .02f, {.15f, .15f, .18f});
    render::box({7.8f, gY + 1.12f, 14.8f}, {.38f, .28f, .05f}, {.12f, .14f, .18f});
    render::text3d({7.65f, gY + 1.12f, 14.76f}, "RPS SCREEN", {.20f, .95f, .45f});

    // Table 3: 8-Ball Pool Table
    render::box({13.8f, gY + .78f, 14.8f}, {2.8f, .12f, 1.5f}, {.24f, .14f, .08f});
    render::box({13.8f, gY + .85f, 14.8f}, {2.5f, .04f, 1.2f}, {.12f, .55f, .25f});
    render::box({13.8f, gY + .38f, 14.8f}, {.25f, .76f, .25f}, woodDark);
    render::box({16.3f, gY + 1.6f, 14.8f}, {.06f, 1.6f, .8f}, woodDark);

    // --- GAMING ROOM 2 ---
    // 2. Wall-Mounted Gaming Lounge Screen (Mounted on divider wall at x = 13.7m, z = 12.68m)
    render::box({13.7f, gY + 2.1f, 12.68f}, {3.2f, 1.8f, .08f}, {.10f, .12f, .16f});
    render::box({13.7f, gY + 2.1f, 12.70f}, {3.28f, 1.88f, .04f}, {.95f, .45f, .15f, .45f});
    render::box({13.7f, gY + 2.1f, 12.64f}, {3.04f, 1.64f, .02f}, {.025f, .035f, .055f});
    render::box({13.7f, gY + 1.10f, 12.65f}, {2.6f, .14f, .12f}, {.14f, .16f, .19f});
    render::text3d({12.2f, gY + 2.70f, 12.61f}, "SEU GAMING LOUNGE SCREEN", {.95f, .82f, .25f});
    render::text3d({12.2f, gY + 2.35f, 12.61f}, "CHESS / LUDO / 2048 / RUBIK'S / RPS", {1, 1, 1});
    render::text3d({12.2f, gY + 1.80f, 12.61f}, ">> PRESS 'E' TO PLAY ON SCREEN <<", {.20f, .96f, .45f});
    airConditioner(16.35f, gY, 11.0f, true);
    npc(11.0f, gY, 10.15f, 0.0f, NpcActivity::Game, {.78f, .20f, .18f});

    // Lounge Sitting Area
    sofa(5.4f, gY, 11.2f, 2.2f, .80f, 90.0f);
    render::box({6.3f, gY + .35f, 11.2f}, {.8f, .30f, .8f}, woodTop);

    // Chess Table with Checkered Board, 2 Chairs & Match Display Screen
    render::box({8.2f, gY + .75f, 11.2f}, {1.1f, .08f, 1.1f}, woodDark);
    render::box({8.2f, gY + .80f, 11.2f}, {.85f, .03f, .85f}, {.95f, .90f, .78f});
    chair(8.2f, gY, 11.9f, 180.0f); chair(8.2f, gY, 10.5f, 0.0f);
    render::box({8.2f, gY + .95f, 10.58f}, {.26f, .18f, .04f}, {.12f, .14f, .18f});
    render::text3d({8.1f, gY + .95f, 10.54f}, "TTT SCREEN", {.95f, .85f, .25f});

    // Rubik's Cube Display Table & Match Screen
    render::box({11.0f, gY + .75f, 11.2f}, {.9f, .08f, .9f}, legSteel);
    render::box({11.0f, gY + .98f, 11.2f}, {.36f, .36f, .36f}, {.18f, .45f, .85f});
    render::box({11.0f, gY + .95f, 10.58f}, {.26f, .18f, .04f}, {.12f, .14f, .18f});
    render::text3d({10.9f, gY + .95f, 10.54f}, "CUBE SCREEN", {.15f, .85f, 1.0f});

    // Ludo Board Table, Chairs & Match Screen
    render::box({13.8f, gY + .75f, 11.2f}, {1.2f, .08f, 1.2f}, woodTop);
    render::box({13.8f, gY + .80f, 11.2f}, {.95f, .03f, .95f}, {.95f, .85f, .25f});
    chair(13.8f, gY, 12.0f, 180.0f); chair(13.8f, gY, 10.4f, 0.0f);
    render::box({13.8f, gY + .95f, 10.58f}, {.26f, .18f, .04f}, {.12f, .14f, .18f});
    render::text3d({13.7f, gY + .95f, 10.54f}, "LUDO SCREEN", {.95f, .35f, .45f});

    // =========================================================================
    // 10. LIFTS AND WASHROOM FIXTURES (FLOORS 1, 2, 3, AND 4)
    // =========================================================================
    const float f3Y = 9.2f;  // Third Floor Y
    const float f4Y = 13.2f; // Fourth Floor Y

    // Lifts across all 4 floors
    for (float flY : {gY, f2Y, f3Y, f4Y}) {
        const int flNum = flY == gY ? 1 : (flY == f2Y ? 2 : (flY == f3Y ? 3 : 4));
        const bool carAtLanding = std::abs(liftPresentationFloor - flNum) < .06f;
        const float doorsAtLanding = carAtLanding ? liftPresentationDoor : 0.0f;
        // Every landing keeps a visible closed portal. Only the selected car
        // gets a cabin interior; this prevents four cabins appearing at once.
        lift(-17.2f, flY, 25.0f, flNum, false, false, true);
        lift(-13.5f, flY, 25.0f, flNum, doorsAtLanding, false, true);
        lift(6.6f,   flY, 25.2f, flNum, false, false, true);
        lift(10.6f,  flY, 25.2f, flNum, doorsAtLanding, false, true);
        render::text3d({-15.35f, flY + 3.85f, 24.8f}, "LIFT [PRESS 1, 2, 3, 4]", {.88f, .92f, 1.0f});
        render::text3d({8.6f,    flY + 3.85f, 25.0f}, "LIFT [PRESS 1, 2, 3, 4]", {.88f, .92f, 1.0f});
    }

    // The car itself moves between landings while the landing portals stay
    // fixed. Both boardable cars are presented together for a coherent bank.
    const float carY = gY + (liftPresentationFloor - 1.0f) * 4.0f;
    const int carFloor = static_cast<int>(liftPresentationFloor + .5f);
    lift(-13.5f, carY, 25.0f, carFloor, liftPresentationDoor, true, false);
    lift(10.6f,  carY, 25.2f, carFloor, liftPresentationDoor, true, false);

    // Ground Floor Washrooms
    for (float x : {-22.5f, -21.6f}) render::box({x, gY + .45f, 26.2f}, {.55f, .55f, .55f}, {.92f, .92f, .94f});
    for (float x : {14.3f, 15.4f})  render::box({x, gY + .45f, 26.2f}, {.55f, .55f, .55f}, {.92f, .92f, .94f});
    airConditioner(-20.95f, gY, 27.5f, true);
    airConditioner(16.35f, gY, 27.0f, true);

    // =========================================================================
    // 11. SECOND FLOOR FURNISHINGS (Floor Level: y = 5.2f)
    // Library, CSE & AI Lab, Classroom 201, Dean's Office, Sky Terrace
    // =========================================================================
    // --- CENTRAL LIBRARY (Floor 2: x in [-24, -11.5], z in [28.2, 40.0]) ---
    bookshelf(-23.4f, f2Y, 32.0f, 5);
    bookshelf(-23.4f, f2Y, 35.5f, 5);
    bookshelf(-23.4f, f2Y, 38.5f, 5);
    diningTableSet(-17.5f, f2Y, 32.5f, 2.0f, 1.2f);
    diningTableSet(-17.5f, f2Y, 36.5f, 2.0f, 1.2f);
    render::cylinder({-17.5f, f2Y + .95f, 32.5f}, .06f, .25f, chromeColor);
    render::cylinder({-17.5f, f2Y + .95f, 36.5f}, .06f, .25f, chromeColor);
    airConditioner(-11.65f, f2Y, 36.0f, true);
    npc(-17.5f, f2Y, 33.35f, 180.0f, NpcActivity::Read, {.18f, .38f, .72f});
    npc(-17.5f, f2Y, 37.35f, 180.0f, NpcActivity::Read, {.68f, .24f, .18f});

    // --- CSE & AI LAB (Floor 2: x in [-24, -11.5], z in [14.0, 24.6]) ---
    for (float x : {-21.5f, -19.0f, -16.5f}) {
        render::texturedBox({x, f2Y + .80f, 17.0f}, {1.8f, .08f, .9f}, woodTop, 2);
        render::box({x, f2Y + 1.15f, 16.8f}, {.52f, .32f, .04f}, {.12f, .14f, .16f});
        render::box({x, f2Y + .85f, 17.2f}, {.40f, .02f, .16f}, {.22f, .24f, .26f});
        chair(x, f2Y, 17.8f, 180.0f);
    }
    for (float x : {-21.5f, -19.0f, -16.5f}) {
        render::texturedBox({x, f2Y + .80f, 21.5f}, {1.8f, .08f, .9f}, woodTop, 2);
        render::box({x, f2Y + 1.15f, 21.3f}, {.52f, .32f, .04f}, {.12f, .14f, .16f});
        render::box({x, f2Y + .85f, 21.7f}, {.40f, .02f, .16f}, {.22f, .24f, .26f});
        chair(x, f2Y, 22.3f, 180.0f);
    }
    render::box({-23.2f, f2Y + 1.5f, 15.0f}, {.65f, 2.6f, .9f}, {.12f, .14f, .16f});
    render::box({-22.85f, f2Y + 1.8f, 15.0f}, {.02f, .08f, .14f}, {.1f, .85f, .35f});
    airConditioner(-11.65f, f2Y, 20.0f, true);
    npc(-19.0f, f2Y, 18.25f, 180.0f, NpcActivity::Lab, {.18f, .58f, .78f});

    // --- CLASSROOM 201 (Floor 2: x in [5.0, 16.5], z in [14.0, 22.0]) ---
    render::box({10.5f, f2Y + .65f, 15.0f}, {.95f, 1.25f, .65f}, woodDark);
    render::box({10.5f, f2Y + 2.0f, 14.1f}, {4.5f, 1.6f, .04f}, {.96f, .96f, .98f});
    for (float z : {17.2f, 19.2f, 21.0f}) {
        for (float x : {7.5f, 10.5f, 13.5f}) {
            render::texturedBox({x, f2Y + .75f, z}, {1.4f, .06f, .65f}, woodTop, 2);
            chair(x, f2Y, z + .52f, 180.0f);
        }
    }
    airConditioner(16.25f, f2Y, 18.0f, true);
    npc(10.5f, f2Y, 16.10f, 0.0f, NpcActivity::Teach, {.72f, .25f, .16f});
    npc(7.5f, f2Y, 18.15f, 180.0f, NpcActivity::Read, {.20f, .46f, .78f});

    // --- DEAN'S OFFICE (Floor 2: x in [-24, -11.5], z in [9.5, 14.0]) ---
    officeDesk(-17.0f, f2Y, 11.4f, 2.4f, 1.0f);
    sofa(-21.5f, f2Y, 11.4f, 2.6f, .85f, 90.0f);
    render::box({-20.0f, f2Y + .35f, 11.4f}, {1.2f, .30f, .70f}, woodTop);
    airConditioner(-11.65f, f2Y, 12.0f, true);
    npc(-17.0f, f2Y, 10.65f, 0.0f, NpcActivity::Desk, {.42f, .22f, .58f});

    // --- SKY TERRACE BALCONY (Floor 2: x in [-10.0, 5.0], z in [9.5, 13.5]) ---
    roundTableSet(-7.0f, f2Y, 11.5f, 0.70f);
    roundTableSet(-2.5f, f2Y, 11.5f, 0.70f);
    roundTableSet( 2.0f, f2Y, 11.5f, 0.70f);
    npc(-7.0f, f2Y, 12.60f, 180.0f, NpcActivity::Talk, {.18f, .55f, .30f});

    // =========================================================================
    // 12. THIRD FLOOR FURNISHINGS (Floor Level: y = 9.2f)
    // Grand Auditorium, Robotics Lab, Faculty Conference Suite, Chairman Suite
    // =========================================================================
    // --- GRAND AUDITORIUM (Floor 3: x in [-24, -11.5], z in [26.0, 40.0]) ---
    // Raised stage and presentation screen
    render::box({-17.75f, f3Y + .45f, 37.5f}, {10.5f, .90f, 3.5f}, woodDark);
    render::box({-17.75f, f3Y + 2.5f, 39.8f}, {7.5f, 2.2f, .06f}, {.95f, .96f, .98f});
    render::box({-17.75f, f3Y + 1.25f, 36.5f}, {.9f, 1.2f, .6f}, woodTop); // Lecture podium
    // 3 Rows of auditorium audience chairs
    for (float az : {33.5f, 30.5f, 27.5f}) {
        for (float ax : {-21.5f, -19.0f, -16.5f, -14.0f}) {
            chair(ax, f3Y, az, 0.0f); // Facing stage
        }
    }
    airConditioner(-11.65f, f3Y, 36.0f, true);
    npc(-17.75f, f3Y, 37.15f, 180.0f, NpcActivity::Present, {.72f, .25f, .16f});

    // --- ROBOTICS & INNOVATION LAB (Floor 3: x in [-24, -11.5], z in [14.0, 23.5]) ---
    render::texturedBox({-17.75f, f3Y + .80f, 18.5f}, {4.5f, .08f, 2.0f}, woodTop, 2);
    render::box({-17.75f, f3Y + 1.15f, 18.5f}, {.8f, .55f, .6f}, {.20f, .55f, .85f}); // Robotics assembly unit
    chair(-19.5f, f3Y, 19.8f, 0.0f);
    chair(-16.0f, f3Y, 19.8f, 0.0f);
    airConditioner(-11.65f, f3Y, 20.0f, true);
    npc(-17.75f, f3Y, 20.35f, 180.0f, NpcActivity::Lab, {.18f, .50f, .72f});

    // --- FACULTY CONFERENCE SUITE (Floor 3: x in [5.0, 16.5], z in [14.0, 22.0]) ---
    render::box({10.5f, f3Y + .80f, 18.0f}, {4.8f, .08f, 1.8f}, woodDark);
    for (float cx : {8.5f, 10.5f, 12.5f}) {
        chair(cx, f3Y, 19.2f, 180.0f);
        chair(cx, f3Y, 16.8f, 0.0f);
    }
    chair(13.5f, f3Y, 18.0f, -90.0f);
    chair(7.5f,  f3Y, 18.0f, 90.0f);
    airConditioner(16.25f, f3Y, 18.0f, true);
    npc(14.0f, f3Y, 18.0f, -90.0f, NpcActivity::Talk, {.62f, .26f, .18f});

    // --- CHAIRMAN SUITE (Floor 3: x in [-24, -11.5], z in [9.5, 14.0]) ---
    officeDesk(-17.0f, f3Y, 11.4f, 2.4f, 1.0f);
    sofa(-21.5f, f3Y, 11.4f, 2.6f, .85f, 90.0f);
    airConditioner(-11.65f, f3Y, 12.0f, true);
    npc(-17.0f, f3Y, 10.65f, 0.0f, NpcActivity::Desk, {.22f, .42f, .68f});

    // =========================================================================
    // 13. FOURTH FLOOR FURNISHINGS (Floor Level: y = 13.2f)
    // Executive Boardroom, Chancellor Suite, Rooftop Sky Garden Lounge
    // =========================================================================
    // --- EXECUTIVE BOARDROOM (Floor 4: x in [-24, -11.5], z in [26.0, 40.0]) ---
    render::box({-17.75f, f4Y + .80f, 33.0f}, {5.6f, .08f, 2.2f}, woodDark);
    for (float cx : {-20.0f, -18.5f, -17.0f, -15.5f}) {
        chair(cx, f4Y, 34.4f, 180.0f);
        chair(cx, f4Y, 31.6f, 0.0f);
    }
    render::box({-17.75f, f4Y + 2.5f, 39.8f}, {6.5f, 2.0f, .06f}, {.95f, .96f, .98f});
    airConditioner(-11.65f, f4Y, 36.0f, true);
    npc(-17.75f, f4Y, 35.05f, 180.0f, NpcActivity::Talk, {.18f, .34f, .62f});

    // --- CHANCELLOR SUITE (Floor 4: x in [-24, -11.5], z in [14.0, 23.5]) ---
    officeDesk(-17.0f, f4Y, 18.5f, 2.6f, 1.1f);
    sofa(-21.0f, f4Y, 18.5f, 2.8f, .90f, 90.0f);
    airConditioner(-11.65f, f4Y, 20.0f, true);
    npc(-17.0f, f4Y, 17.68f, 0.0f, NpcActivity::Desk, {.62f, .24f, .18f});

    // --- ROOFTOP SKY GARDEN LOUNGE (Floor 4: x in [2.0, 16.0], z in [11.0, 35.0]) ---
    roundTableSet(6.5f,  f4Y, 16.0f, 0.75f);
    roundTableSet(12.5f, f4Y, 16.0f, 0.75f);
    roundTableSet(6.5f,  f4Y, 30.0f, 0.75f);
    roundTableSet(12.5f, f4Y, 30.0f, 0.75f);
    // Sky Garden Planters with Lush Greenery
    render::box({9.5f, f4Y + .35f, 23.0f}, {4.0f, .65f, 1.2f}, {.42f, .32f, .22f});
    render::cylinder({9.5f, f4Y + .95f, 23.0f}, .85f, .85f, {.15f, .46f, .18f});
    npc(6.5f, f4Y, 17.15f, 180.0f, NpcActivity::Talk, {.20f, .48f, .75f});
    npc(12.5f, f4Y, 28.85f, 0.0f, NpcActivity::Read, {.72f, .28f, .18f});

    // =========================================================================
    // ROOM IDENTIFICATION LABELS
    // =========================================================================
    if (labels) {
        render::text3d({-22.0f, gY + 3.1f, 11.2f}, "ADMISSION 1", {1, 1, 1});
        render::text3d({-22.0f, gY + 3.1f, 16.5f}, "ADMISSION 2", {1, 1, 1});
        render::text3d({-15.5f, gY + 3.1f, 18.5f}, "BANK 1", {1, 1, 1});
        render::text3d({8.2f,  gY + 3.1f, 20.2f}, "BANK 2", {1, 1, 1});
        render::text3d({-18.0f, gY + 3.1f, 31.0f}, "FACULTY LOUNGE", {1, 1, 1});
        render::text3d({7.5f,   gY + 3.1f, 15.0f}, "GAMING 1: CARROM / TT / POOL", {1, 1, 1});
        render::text3d({7.5f,   gY + 3.1f, 11.4f}, "GAMING 2: CHESS / CUBE / LUDO", {1, 1, 1});

        // Second Floor Labels
        render::text3d({-19.0f, f2Y + 3.1f, 34.0f}, "CENTRAL LIBRARY", {1, 1, 1});
        render::text3d({-19.0f, f2Y + 3.1f, 19.0f}, "CSE & AI LAB", {1, 1, 1});
        render::text3d({10.5f,  f2Y + 3.1f, 18.0f}, "CLASSROOM 201", {1, 1, 1});
        render::text3d({-18.0f, f2Y + 3.1f, 11.4f}, "DEAN'S OFFICE", {1, 1, 1});
        render::text3d({-3.0f,  f2Y + 3.1f, 11.5f}, "SKY TERRACE", {1, 1, 1});

        // Third Floor Labels
        render::text3d({-19.0f, f3Y + 3.1f, 34.0f}, "GRAND AUDITORIUM", {1, 1, 1});
        render::text3d({-19.0f, f3Y + 3.1f, 19.0f}, "ROBOTICS LAB", {1, 1, 1});
        render::text3d({10.5f,  f3Y + 3.1f, 18.0f}, "CONFERENCE SUITE", {1, 1, 1});
        render::text3d({-18.0f, f3Y + 3.1f, 11.4f}, "CHAIRMAN SUITE", {1, 1, 1});

        // Fourth Floor Labels
        render::text3d({-19.0f, f4Y + 3.1f, 34.0f}, "EXECUTIVE BOARDROOM", {1, 1, 1});
        render::text3d({-19.0f, f4Y + 3.1f, 19.0f}, "CHANCELLOR SUITE", {1, 1, 1});
        render::text3d({9.5f,   f4Y + 3.1f, 23.0f}, "ROOFTOP SKY GARDEN", {1, 1, 1});
    }
}

} // namespace campus
