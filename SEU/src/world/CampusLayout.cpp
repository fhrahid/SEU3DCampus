#include "CampusLayout.h"
#include "../render/Primitives.h"
#include "Furniture.h"
#include <GL/glut.h>
#include <initializer_list>
#include <cstring>
#include <algorithm>

namespace campus {
namespace {
using render::Color;

// =============================================================================
// CANONICAL SEU 6-TONE COLOR PALETTE CONSTANTS
// =============================================================================
// Tone 1: Terracotta / Rust Orange: Left tower cladding, admin walls, handrails & gates
const Color terracotta{.72f, .30f, .15f};
const Color terracottaGroove{.50f, .18f, .08f};
const Color terracottaCap{.42f, .15f, .07f};
const Color rustOrange{.90f, .42f, .08f};
const Color roomOrange{.55f, .18f, .12f};

// Tone 2: Concrete Gray / Off-White: Right concrete tower, floor slabs, pilotis, walls
const Color concreteGray{.76f, .78f, .80f};
const Color concreteSlab{.84f, .85f, .87f};
const Color concreteOffWhite{.88f, .89f, .91f};
const Color structuralPilotis{.86f, .88f, .90f};
const Color wall{.55f, .18f, .12f};
const Color roomWhite{.55f, .18f, .12f};
const Color tileFloor{.92f, .93f, .95f};
const Color surroundingConcrete{.74f, .76f, .78f};

// Tone 3: Reflective Steel Blue & Cyan: Central atrium curtain wall & right high-rise
const Color curtainGlass{.22f, .65f, .78f, .55f};
const Color reflectiveSteelBlue{.24f, .54f, .68f};
const Color highRiseGlass{.22f, .60f, .75f, .65f};
const Color glass{.20f, .74f, .85f, .38f};
const Color chrome{.88f, .90f, .94f};
const Color roomSteel{.55f, .18f, .12f};

// Tone 4: Deep Forest & Olive Green: Lush tree canopies and ground foliage
const Color deepForestGreen{.11f, .32f, .13f};
const Color oliveGreen{.22f, .44f, .16f};
const Color gardenGreen{.14f, .38f, .16f};
const Color hedgeGreen{.12f, .34f, .14f};
const Color roomGreen{.55f, .18f, .12f};

// Tone 6: Earthy Brown & Dark Charcoal: Paved ground, driveways, rooftops, roads
const Color earthyBrownPaved{.56f, .50f, .40f};
const Color earthyBrownRooftop{.46f, .38f, .30f};
const Color darkCharcoalRooftop{.20f, .22f, .25f};
const Color darkCharcoalAsphalt{.22f, .23f, .25f};
const Color darkCharcoalMullion{.16f, .18f, .21f};
const Color darkCharcoalFrame{.16f, .18f, .21f};
const Color driveway = earthyBrownPaved;

bool showCeilings = true;

void label(const Rect& r, const char* name, bool labels, float y = floorY) {
    if (labels) render::text3d({(r.minX + r.maxX) * .5f - .8f, y + .04f, (r.minZ + r.maxZ) * .5f}, name, {1, 1, 1});
}

// State-of-the-Art Architectural Glass Door System
// Inspired by modern commercial & institutional frameless/slim-profile glass entrances
void architecturalGlassDoor(float x, float z, float width, const char* name, bool isDouble = false, float baseFloor = floorY, bool isOpen = true) {
    const Color frameCol{.16f, .18f, .22f};     // Dark bronze / matte graphite anodized aluminum
    const Color chromeCol{.88f, .90f, .94f};    // Brushed stainless steel / chrome
    const Color glassCol{.20f, .78f, .88f, .38f}; // High-clarity tempered glass with cyan refraction
    const Color frostedCol{.92f, .95f, .98f, .75f}; // Semi-opaque frosted safety manifestation decal
    const Color edgeCol{.14f, .55f, .65f, .75f};   // Polished beveled glass edge profile

    const float halfW = width * 0.5f;

    // 1. Structural Anodized Aluminum Perimeter Frame
    render::box({x - halfW, baseFloor + wallHeight * 0.5f, z}, {.07f, wallHeight, .12f}, frameCol);
    render::box({x + halfW, baseFloor + wallHeight * 0.5f, z}, {.07f, wallHeight, .12f}, frameCol);
    render::box({x, baseFloor + 2.70f, z}, {width, .07f, .12f}, frameCol); // Door header transom bar
    render::box({x, baseFloor + wallHeight - .035f, z}, {width, .07f, .12f}, frameCol); // Ceiling channel
    render::box({x, baseFloor + .015f, z}, {width, .03f, .16f}, {.72f, .75f, .80f});   // Floor threshold

    // 2. Upper Stationary Glass Transom Panel (fills header to ceiling)
    const float transomH = wallHeight - 2.80f;
    render::glassPanel({x, baseFloor + 2.735f + transomH * 0.5f, z}, {width - .08f, transomH, .03f}, glassCol);

    // 3. Floating Edge-Lit Acrylic & Aluminum Room Plaque
    if (name) {
        const int tlen = static_cast<int>(std::strlen(name));
        const float signW = std::max(1.15f, std::min(width * 0.90f, 0.13f * tlen + 0.45f));
        // Backplate housing
        render::box({x, baseFloor + 3.02f, z}, {signW, .26f, .05f}, {.12f, .14f, .18f});
        render::box({x, baseFloor + 3.02f, z}, {signW - .04f, .20f, .06f}, {.18f, .22f, .28f});
        // Standoff mounting pins through transom glass
        render::cylinder({x - signW * .44f, baseFloor + 3.02f, z}, .018f, .08f, chromeCol);
        render::cylinder({x + signW * .44f, baseFloor + 3.02f, z}, .018f, .08f, chromeCol);
        // Glowing illuminated typography
        const float textOffset = tlen * 0.052f;
        render::text3d({x - textOffset, baseFloor + 2.95f, z + .04f}, name, {1.0f, .92f, .42f});
        render::text3d({x - textOffset, baseFloor + 2.95f, z - .04f}, name, {1.0f, .92f, .42f});
    }

    // 4. Door Leaf / Leaves Geometry
    const float lh = 2.62f; // Door leaf height
    const float ly = baseFloor + 1.35f;

    if (!isDouble) {
        // --- SINGLE ARCHITECTURAL GLASS DOOR ---
        const float lw = width - 0.10f;
        const float pivotX = x - halfW + .04f;
        const float latchX = x + halfW - .04f;

        // Stainless Steel Patch Fittings (Corner Pivot Clamps)
        render::box({pivotX + .10f, baseFloor + 2.62f, z}, {.18f, .07f, .045f}, chromeCol);
        render::box({pivotX + .10f, baseFloor + .08f, z}, {.18f, .07f, .045f}, chromeCol);
        // Concealed floor spring closer cover plate in threshold
        render::box({pivotX + .10f, baseFloor + .02f, z}, {.24f, .015f, .10f}, chromeCol);
        // Bottom patch lock fitting
        render::box({latchX - .09f, baseFloor + .08f, z}, {.14f, .06f, .042f}, chromeCol);

        // Tempered Glass Door Leaf
        render::glassPanel({x, ly, z}, {lw, lh, .025f}, glassCol);
        // Polished beveled edge profile
        render::box({x, baseFloor + 2.65f, z}, {lw, .02f, .028f}, edgeCol);
        render::box({x, baseFloor + .05f, z}, {lw, .02f, .028f}, edgeCol);
        render::box({x - lw * .5f, ly, z}, {.02f, lh, .028f}, edgeCol);
        render::box({x + lw * .5f, ly, z}, {.02f, lh, .028f}, edgeCol);

        // Frosted Safety Manifestation Decal Bands
        // Eye-level band (y = 1.45m)
        render::glassPanel({x, baseFloor + 1.45f, z}, {lw - .04f, .14f, .028f}, frostedCol);
        render::box({x, baseFloor + 1.48f, z + .016f}, {lw - .08f, .018f, .005f}, {.18f, .28f, .38f});
        // Waist-level band (y = 0.95m)
        render::glassPanel({x, baseFloor + .95f, z}, {lw - .04f, .07f, .028f}, frostedCol);

        // Long Tubular Stainless Steel Push/Pull Handles (Dual-sided)
        const float hx = latchX - .14f;
        render::cylinder({hx, baseFloor + 1.525f, z + .05f}, .022f, 1.35f, chromeCol);
        render::cylinder({hx, baseFloor + 1.525f, z - .05f}, .022f, 1.35f, chromeCol);
        render::box({hx, baseFloor + .95f, z}, {.04f, .04f, .12f}, chromeCol);
        render::box({hx, baseFloor + 2.10f, z}, {.04f, .04f, .12f}, chromeCol);
    } else {
        // --- DOUBLE ARCHITECTURAL GLASS DOORS ---
        const float lw = (width - 0.14f) * 0.5f; // Each leaf width
        if (isOpen) {
            // Welcoming open double doors swung inward (+Z into the room)
            const float pivotLX = x - halfW + .08f;
            const float pivotRX = x + halfW - .08f;
            const float lz = z + lw * 0.45f;

            // Left Leaf swung inward
            render::glassPanel({pivotLX, ly, lz}, {.025f, lh, lw}, glassCol);
            render::box({pivotLX, baseFloor + 2.65f, lz}, {.028f, .02f, lw}, edgeCol);
            render::box({pivotLX, baseFloor + .05f, lz}, {.028f, .02f, lw}, edgeCol);
            render::glassPanel({pivotLX, baseFloor + 1.45f, lz}, {.028f, .14f, lw - .04f}, frostedCol);
            render::box({pivotLX, baseFloor + 2.62f, z + .08f}, {.045f, .07f, .16f}, chromeCol);
            render::box({pivotLX, baseFloor + .08f, z + .08f}, {.045f, .07f, .16f}, chromeCol);
            render::cylinder({pivotLX + .05f, baseFloor + 1.525f, z + lw * .78f}, .022f, 1.35f, chromeCol);
            render::cylinder({pivotLX - .05f, baseFloor + 1.525f, z + lw * .78f}, .022f, 1.35f, chromeCol);

            // Right Leaf swung inward
            render::glassPanel({pivotRX, ly, lz}, {.025f, lh, lw}, glassCol);
            render::box({pivotRX, baseFloor + 2.65f, lz}, {.028f, .02f, lw}, edgeCol);
            render::box({pivotRX, baseFloor + .05f, lz}, {.028f, .02f, lw}, edgeCol);
            render::glassPanel({pivotRX, baseFloor + 1.45f, lz}, {.028f, .14f, lw - .04f}, frostedCol);
            render::box({pivotRX, baseFloor + 2.62f, z + .08f}, {.045f, .07f, .16f}, chromeCol);
            render::box({pivotRX, baseFloor + .08f, z + .08f}, {.045f, .07f, .16f}, chromeCol);
            render::cylinder({pivotRX - .05f, baseFloor + 1.525f, z + lw * .78f}, .022f, 1.35f, chromeCol);
            render::cylinder({pivotRX + .05f, baseFloor + 1.525f, z + lw * .78f}, .022f, 1.35f, chromeCol);
        } else {
            const float lx = x - lw * 0.5f - 0.01f;
            const float rx = x + lw * 0.5f + 0.01f;

            // Left Leaf Hardware & Glass
            render::box({x - halfW + .12f, baseFloor + 2.62f, z}, {.18f, .07f, .045f}, chromeCol);
            render::box({x - halfW + .12f, baseFloor + .08f, z}, {.18f, .07f, .045f}, chromeCol);
            render::box({x - halfW + .12f, baseFloor + .02f, z}, {.24f, .015f, .10f}, chromeCol);
            render::box({x - .05f, baseFloor + .08f, z}, {.12f, .06f, .042f}, chromeCol);
            render::glassPanel({lx, ly, z}, {lw, lh, .025f}, glassCol);
            render::box({lx, baseFloor + 2.65f, z}, {lw, .02f, .028f}, edgeCol);
            render::box({lx, baseFloor + .05f, z}, {lw, .02f, .028f}, edgeCol);
            render::box({lx - lw * .5f, ly, z}, {.02f, lh, .028f}, edgeCol);
            render::box({lx + lw * .5f, ly, z}, {.02f, lh, .028f}, edgeCol);
            render::glassPanel({lx, baseFloor + 1.45f, z}, {lw - .04f, .14f, .028f}, frostedCol);
            render::glassPanel({lx, baseFloor + .95f, z}, {lw - .04f, .07f, .028f}, frostedCol);

            // Left Leaf Handle (near center meeting edge)
            const float lhx = lx + lw * .5f - .12f;
            render::cylinder({lhx, baseFloor + 1.525f, z + .05f}, .022f, 1.35f, chromeCol);
            render::cylinder({lhx, baseFloor + 1.525f, z - .05f}, .022f, 1.35f, chromeCol);
            render::box({lhx, baseFloor + .95f, z}, {.04f, .04f, .12f}, chromeCol);
            render::box({lhx, baseFloor + 2.10f, z}, {.04f, .04f, .12f}, chromeCol);

            // Right Leaf Hardware & Glass
            render::box({x + halfW - .12f, baseFloor + 2.62f, z}, {.18f, .07f, .045f}, chromeCol);
            render::box({x + halfW - .12f, baseFloor + .08f, z}, {.18f, .07f, .045f}, chromeCol);
            render::box({x + halfW - .12f, baseFloor + .02f, z}, {.24f, .015f, .10f}, chromeCol);
            render::box({x + .05f, baseFloor + .08f, z}, {.12f, .06f, .042f}, chromeCol);
            render::glassPanel({rx, ly, z}, {lw, lh, .025f}, glassCol);
            render::box({rx, baseFloor + 2.65f, z}, {lw, .02f, .028f}, edgeCol);
            render::box({rx, baseFloor + .05f, z}, {lw, .02f, .028f}, edgeCol);
            render::box({rx - lw * .5f, ly, z}, {.02f, lh, .028f}, edgeCol);
            render::box({rx + lw * .5f, ly, z}, {.02f, lh, .028f}, edgeCol);
            render::glassPanel({rx, baseFloor + 1.45f, z}, {lw - .04f, .14f, .028f}, frostedCol);
            render::glassPanel({rx, baseFloor + .95f, z}, {lw - .04f, .07f, .028f}, frostedCol);

            // Right Leaf Handle (near center meeting edge)
            const float rhx = rx - lw * .5f + .12f;
            render::cylinder({rhx, baseFloor + 1.525f, z + .05f}, .022f, 1.35f, chromeCol);
            render::cylinder({rhx, baseFloor + 1.525f, z - .05f}, .022f, 1.35f, chromeCol);
            render::box({rhx, baseFloor + .95f, z}, {.04f, .04f, .12f}, chromeCol);
            render::box({rhx, baseFloor + 2.10f, z}, {.04f, .04f, .12f}, chromeCol);

            // Center meeting weatherseal
            render::box({x, ly, z}, {.018f, lh, .026f}, {.85f, .88f, .92f});
        }
    }
}

// Architectural Glass Door in the Y-Z plane (depth along Z, normal along X)
void architecturalGlassDoorZ(float x, float z, float depthZ, const char* name, bool isDouble = false, float baseFloor = floorY, bool isOpen = true) {
    const Color frameCol{.16f, .18f, .22f};     // Dark bronze / matte graphite anodized aluminum
    const Color chromeCol{.88f, .90f, .94f};    // Brushed stainless steel / chrome
    const Color glassCol{.20f, .78f, .88f, .38f}; // High-clarity tempered glass with cyan refraction
    const Color frostedCol{.92f, .95f, .98f, .75f}; // Semi-opaque frosted safety manifestation decal
    const Color edgeCol{.14f, .55f, .65f, .75f};   // Polished beveled glass edge profile

    const float halfD = depthZ * 0.5f;

    // 1. Structural Anodized Aluminum Perimeter Frame
    render::box({x, baseFloor + wallHeight * 0.5f, z - halfD}, {.12f, wallHeight, .07f}, frameCol);
    render::box({x, baseFloor + wallHeight * 0.5f, z + halfD}, {.12f, wallHeight, .07f}, frameCol);
    render::box({x, baseFloor + 2.70f, z}, {.12f, .07f, depthZ}, frameCol); // Header transom bar
    render::box({x, baseFloor + wallHeight - .035f, z}, {.12f, .07f, depthZ}, frameCol); // Ceiling channel
    render::box({x, baseFloor + .015f, z}, {.18f, .03f, depthZ}, {.78f, .75f, .80f});   // Floor threshold

    // 2. Upper Stationary Glass Transom Panel
    const float transomH = wallHeight - 2.80f;
    render::glassPanel({x, baseFloor + 2.735f + transomH * 0.5f, z}, {.03f, transomH, depthZ - .08f}, glassCol);

    // 3. Floating Edge-Lit Acrylic & Aluminum Room Plaque
    if (name) {
        const int tlen = static_cast<int>(std::strlen(name));
        const float signW = std::max(1.15f, std::min(depthZ * 0.90f, 0.13f * tlen + 0.45f));
        render::box({x, baseFloor + 3.02f, z}, {.05f, .26f, signW}, {.12f, .14f, .18f});
        render::box({x, baseFloor + 3.02f, z}, {.06f, .20f, signW - .04f}, {.18f, .22f, .28f});
        render::cylinder({x, baseFloor + 3.02f, z - signW * .44f}, .018f, .08f, chromeCol);
        render::cylinder({x, baseFloor + 3.02f, z + signW * .44f}, .018f, .08f, chromeCol);
        const float textOffset = tlen * 0.052f;
        render::text3d({x + .04f, baseFloor + 2.95f, z - textOffset}, name, {1.0f, .92f, .42f});
        render::text3d({x - .04f, baseFloor + 2.95f, z - textOffset}, name, {1.0f, .92f, .42f});
    }

    // 4. Door Leaves along Z
    const float lh = 2.62f;
    const float ly = baseFloor + 1.35f;

    if (!isDouble) {
        const float lw = depthZ - 0.10f;
        if (isOpen) {
            render::glassPanel({x - .28f, ly, z - halfD + lw * .45f}, {.50f, lh, .025f}, glassCol);
            render::cylinder({x - .48f, baseFloor + 1.525f, z - halfD + lw * .45f}, .022f, 1.35f, chromeCol);
        } else {
            render::glassPanel({x, ly, z}, {.025f, lh, lw}, glassCol);
            render::cylinder({x + .05f, baseFloor + 1.525f, z + halfD - .14f}, .022f, 1.35f, chromeCol);
            render::cylinder({x - .05f, baseFloor + 1.525f, z + halfD - .14f}, .022f, 1.35f, chromeCol);
        }
    } else {
        const float lw = (depthZ - 0.14f) * 0.5f;
        if (isOpen) {
            // Welcoming open double doors swung inward into the office (-X)
            // South leaf swung inward
            render::glassPanel({x - .28f, ly, z - halfD + lw * .45f}, {.52f, lh, .025f}, glassCol);
            render::glassPanel({x - .28f, baseFloor + 1.45f, z - halfD + lw * .45f}, {.48f, .14f, .028f}, frostedCol);
            render::box({x - .28f, baseFloor + 2.65f, z - halfD + lw * .45f}, {.52f, .02f, .028f}, edgeCol);
            render::box({x - .28f, baseFloor + .05f, z - halfD + lw * .45f}, {.52f, .02f, .028f}, edgeCol);
            render::box({x, baseFloor + 2.62f, z - halfD + .08f}, {.045f, .07f, .16f}, chromeCol);
            render::box({x, baseFloor + .08f, z - halfD + .08f}, {.045f, .07f, .16f}, chromeCol);
            render::cylinder({x - .48f, baseFloor + 1.525f, z - halfD + lw * .45f}, .022f, 1.35f, chromeCol);

            // North leaf swung inward
            render::glassPanel({x - .28f, ly, z + halfD - lw * .45f}, {.52f, lh, .025f}, glassCol);
            render::glassPanel({x - .28f, baseFloor + 1.45f, z + halfD - lw * .45f}, {.48f, .14f, .028f}, frostedCol);
            render::box({x - .28f, baseFloor + 2.65f, z + halfD - lw * .45f}, {.52f, .02f, .028f}, edgeCol);
            render::box({x - .28f, baseFloor + .05f, z + halfD - lw * .45f}, {.52f, .02f, .028f}, edgeCol);
            render::box({x, baseFloor + 2.62f, z + halfD - .08f}, {.045f, .07f, .16f}, chromeCol);
            render::box({x, baseFloor + .08f, z + halfD - .08f}, {.045f, .07f, .16f}, chromeCol);
            render::cylinder({x - .48f, baseFloor + 1.525f, z + halfD - lw * .45f}, .022f, 1.35f, chromeCol);
        } else {
            const float lz = z - lw * 0.5f - 0.01f;
            const float rz = z + lw * 0.5f + 0.01f;
            render::glassPanel({x, ly, lz}, {.025f, lh, lw}, glassCol);
            render::glassPanel({x, ly, rz}, {.025f, lh, lw}, glassCol);
            render::glassPanel({x, baseFloor + 1.45f, lz}, {.028f, .14f, lw - .04f}, frostedCol);
            render::glassPanel({x, baseFloor + 1.45f, rz}, {.028f, .14f, lw - .04f}, frostedCol);
            render::cylinder({x + .05f, baseFloor + 1.525f, z - .12f}, .022f, 1.35f, chromeCol);
            render::cylinder({x - .05f, baseFloor + 1.525f, z - .12f}, .022f, 1.35f, chromeCol);
            render::cylinder({x + .05f, baseFloor + 1.525f, z + .12f}, .022f, 1.35f, chromeCol);
            render::cylinder({x - .05f, baseFloor + 1.525f, z + .12f}, .022f, 1.35f, chromeCol);
        }
    }
}


void ceilingDecor(const Rect& r, float baseFloor = floorY) {
    const float cx = (r.minX + r.maxX) * .5f;
    const float cz = (r.minZ + r.maxZ) * .5f;
    const float y = baseFloor + wallHeight;
    render::texturedBox({cx, y, cz}, {r.maxX-r.minX, .12f, r.maxZ-r.minZ}, {.95f,.96f,.98f}, 1);
    render::box({cx, y + .08f, r.minZ + .16f}, {r.maxX-r.minX, .12f, .12f}, {.78f,.8f,.84f});
    render::box({cx, y + .08f, r.maxZ - .16f}, {r.maxX-r.minX, .12f, .12f}, {.78f,.8f,.84f});
    render::box({r.minX + .16f, y + .08f, cz}, {.12f, .12f, r.maxZ-r.minZ}, {.78f,.8f,.84f});
    render::box({r.maxX - .16f, y + .08f, cz}, {.12f, .12f, r.maxZ-r.minZ}, {.78f,.8f,.84f});
    const float lightY = y - .08f;
    for (float x = r.minX + (r.maxX-r.minX)*.3f; x < r.maxX; x += (r.maxX-r.minX)*.4f)
        for (float z = r.minZ + (r.maxZ-r.minZ)*.3f; z < r.maxZ; z += (r.maxZ-r.minZ)*.4f)
            render::box({x, lightY, z}, {.34f, .06f, .18f}, {1.0f, .88f, .52f});
}

void room(const Rect& r, Color roomColor, const char* name, bool labels, bool glassFront = true, bool frontDoor = true, float baseFloor = floorY) {
    render::texturedBox({(r.minX + r.maxX) * .5f, baseFloor, (r.minZ + r.maxZ) * .5f}, {r.maxX-r.minX, .1f, r.maxZ-r.minZ}, tileFloor, 0);
    const float y = baseFloor + wallHeight * .5f;
    render::texturedBox({r.minX, y, (r.minZ+r.maxZ)*.5f}, {wallThickness, wallHeight, r.maxZ-r.minZ}, roomColor, 4);
    render::texturedBox({r.maxX, y, (r.minZ+r.maxZ)*.5f}, {wallThickness, wallHeight, r.maxZ-r.minZ}, roomColor, 4);
    render::texturedBox({(r.minX+r.maxX)*.5f, y, r.maxZ}, {r.maxX-r.minX, wallHeight, wallThickness}, roomColor, 4);
    const float center = (r.minX + r.maxX) * .5f;
    const float doorHalf = .95f; // 1.9m wide entrance opening
    if (glassFront) {
        render::glassPanel({(r.minX + center - doorHalf) * .5f, y, r.minZ}, {center - doorHalf - r.minX, wallHeight, .08f}, glass);
        render::glassPanel({(center + doorHalf + r.maxX) * .5f, y, r.minZ}, {r.maxX - center - doorHalf, wallHeight, .08f}, glass);
    } else {
        render::texturedBox({(r.minX + center - doorHalf) * .5f, y, r.minZ}, {center - doorHalf - r.minX, wallHeight, wallThickness}, roomColor, 4);
        render::texturedBox({(center + doorHalf + r.maxX) * .5f, y, r.minZ}, {r.maxX - center - doorHalf, wallHeight, wallThickness}, roomColor, 4);
    }
    if (frontDoor) architecturalGlassDoor(center, r.minZ, 1.9f, name, glassFront, baseFloor);
    if (showCeilings) ceilingDecor(r, baseFloor);
    label(r, name, labels, baseFloor);
}

void gamingSuite(bool labels) {
    const Rect outer{3.6f, 16.6f, 9.5f, 16.2f};
    const float y = floorY + wallHeight * .5f;
    const Color frameCol{.16f, .18f, .22f};
    const Color frostedCol{.92f, .95f, .98f, .75f};

    // Floor tile
    render::texturedBox({10.1f, floorY, 12.85f}, {13.0f, .1f, 6.7f}, tileFloor, 0);

    // --- WEST GLASS WALL (x = 3.6m, z in [9.5, 16.2]) ---
    // Moved to x = 3.6m to create a generous 15-meter wide main corridor/lobby
    render::glassPanel({3.6f, y, 12.85f}, {.08f, wallHeight, 6.7f}, glass);
    render::box({3.6f, floorY + .04f, 12.85f}, {.12f, .08f, 6.7f}, frameCol); // Floor channel
    render::box({3.6f, floorY + wallHeight - .04f, 12.85f}, {.12f, .08f, 6.7f}, frameCol); // Ceiling channel
    render::glassPanel({3.6f, floorY + 1.45f, 12.85f}, {.09f, .14f, 6.6f}, frostedCol); // Manifestation line

    // --- EAST GLASS WALL (x = 16.6m, z in [9.5, 16.2]) ---
    render::glassPanel({16.6f, y, 12.85f}, {.08f, wallHeight, 6.7f}, glass);
    render::box({16.6f, floorY + .04f, 12.85f}, {.12f, .08f, 6.7f}, frameCol);
    render::box({16.6f, floorY + wallHeight - .04f, 12.85f}, {.12f, .08f, 6.7f}, frameCol);
    render::glassPanel({16.6f, floorY + 1.45f, 12.85f}, {.09f, .14f, 6.6f}, frostedCol);

    // --- SOUTH GLASS WALL (z = 9.5m, x in [3.6, 16.6]) ---
    render::glassPanel({10.1f, y, 9.5f}, {13.0f, wallHeight, .08f}, glass);
    render::box({10.1f, floorY + .04f, 9.5f}, {13.0f, .08f, .12f}, frameCol);
    render::box({10.1f, floorY + wallHeight - .04f, 9.5f}, {13.0f, .08f, .12f}, frameCol);
    render::glassPanel({10.1f, floorY + 1.45f, 9.5f}, {12.9f, .14f, .09f}, frostedCol);

    // --- NORTH GLASS WALL & GRAND DOUBLE ENTRANCE (z = 16.2m) ---
    // Opening is centered at x = 9.4m, width 3.6m (from 7.6m to 11.2m)
    // Left glass pane (x in [3.6, 7.6], width 4.0m, center 5.6m)
    render::glassPanel({5.6f, y, 16.2f}, {4.0f, wallHeight, .08f}, glass);
    render::box({5.6f, floorY + .04f, 16.2f}, {4.0f, .08f, .12f}, frameCol);
    render::box({5.6f, floorY + wallHeight - .04f, 16.2f}, {4.0f, .08f, .12f}, frameCol);
    render::glassPanel({5.6f, floorY + 1.45f, 16.2f}, {3.9f, .14f, .09f}, frostedCol);

    // Right glass pane (x in [11.2, 16.6], width 5.4m, center 13.9m)
    render::glassPanel({13.9f, y, 16.2f}, {5.4f, wallHeight, .08f}, glass);
    render::box({13.9f, floorY + .04f, 16.2f}, {5.4f, .08f, .12f}, frameCol);
    render::box({13.9f, floorY + wallHeight - .04f, 16.2f}, {5.4f, .08f, .12f}, frameCol);
    render::glassPanel({13.9f, floorY + 1.45f, 16.2f}, {5.3f, .14f, .09f}, frostedCol);

    // Grand Double Glass Door at Gaming Entry (Width: 3.6m, welcoming open inward)
    architecturalGlassDoor(9.4f, 16.2f, 3.6f, "GAMING & RECREATION", true, floorY, true);

    // --- INTERNAL DIVIDER WALL & ARCHITECTURAL GLASS DOOR (z = 12.8m) ---
    // Opening is centered at x = 9.4m, width 2.8m (from 8.0m to 10.8m)
    // Left solid divider wall: x in [3.6, 8.0] -> width 4.4m, center 5.8m
    render::box({5.8f, y, 12.8f}, {4.4f, wallHeight, .22f}, wall);
    // Right solid divider wall: x in [10.8, 16.6] -> width 5.8m, center 13.7m
    render::box({13.7f, y, 12.8f}, {5.8f, wallHeight, .22f}, wall);

    // Double Architectural Glass Door to Gaming Room 2 (Width: 2.8m, open inward)
    architecturalGlassDoor(9.4f, 12.8f, 2.8f, "GAMING ROOM 2", true, floorY, true);

    if (showCeilings) ceilingDecor(outer, floorY);
    if (labels) {
        render::text3d({4.5f, floorY + .04f, 14.5f}, "GAMING ROOM 1", {1, 1, 1});
        render::text3d({4.5f, floorY + .04f, 11.2f}, "GAMING ROOM 2", {1, 1, 1});
    }
}

void tree(float x, float z) {
    // Solid wood bark trunk (Tone 6: Earthy Brown / Charcoal)
    render::cylinder({x, .9f, z}, .15f, 1.8f, {.32f, .20f, .12f});
    // Lower broad lush canopy (Tone 4: Deep Forest Green)
    render::cylinder({x, 2.15f, z}, 1.15f, 1.5f, deepForestGreen);
    // Upper cresting foliage dome (Tone 4: Olive Green)
    render::cylinder({x, 3.10f, z}, .82f, 1.3f, oliveGreen);
    // Interlocking foliage volume
    render::box({x, 2.35f, z}, {1.65f, .85f, 1.65f}, {.13f, .36f, .14f});
}

void gate(float x, const char* name) {
    render::box({x - .8f, 2.1f, .15f}, {.22f, 4.2f, .22f}, darkCharcoalFrame);
    render::box({x + .8f, 2.1f, .15f}, {.22f, 4.2f, .22f}, darkCharcoalFrame);
    render::box({x, 4.0f, .15f}, {1.8f, .22f, .22f}, rustOrange);
    render::text3d({x - .65f, 4.35f, .15f}, name, {1, .92f, .30f});
}

void outline(const Rect& r) {
    const float y = floorY + .12f;
    glDisable(GL_LIGHTING); glColor3f(1, .12f, .1f); glBegin(GL_LINE_LOOP);
    glVertex3f(r.minX, y, r.minZ); glVertex3f(r.maxX, y, r.minZ); glVertex3f(r.maxX, y, r.maxZ); glVertex3f(r.minX, y, r.maxZ); glEnd(); glEnable(GL_LIGHTING);
}

// 3D Illuminated Rooftop Letters spelling "S E U"
void rooftopLettersSEU(float cx, float cy, float cz) {
    const Color goldLetter{1.0f, .92f, .35f};
    const Color letterBack = darkCharcoalFrame;

    // Letter 'S' around x = cx - 2.2f
    const float sx = cx - 2.2f;
    render::box({sx, cy + .75f, cz}, {1.2f, .22f, .35f}, goldLetter);
    render::box({sx - .48f, cy + .45f, cz}, {.24f, .40f, .35f}, goldLetter);
    render::box({sx, cy + .15f, cz}, {1.2f, .22f, .35f}, goldLetter);
    render::box({sx + .48f, cy - .15f, cz}, {.24f, .40f, .35f}, goldLetter);
    render::box({sx, cy - .45f, cz}, {1.2f, .22f, .35f}, goldLetter);
    render::box({sx, cy - .65f, cz}, {1.4f, .18f, .45f}, letterBack);

    // Letter 'E' around x = cx
    const float ex = cx;
    render::box({ex - .48f, cy + .15f, cz}, {.24f, 1.40f, .35f}, goldLetter);
    render::box({ex + .12f, cy + .75f, cz}, {1.0f, .22f, .35f}, goldLetter);
    render::box({ex + .05f, cy + .15f, cz}, {.85f, .20f, .35f}, goldLetter);
    render::box({ex + .12f, cy - .45f, cz}, {1.0f, .22f, .35f}, goldLetter);
    render::box({ex, cy - .65f, cz}, {1.4f, .18f, .45f}, letterBack);

    // Letter 'U' around x = cx + 2.2f
    const float ux = cx + 2.2f;
    render::box({ux - .48f, cy + .20f, cz}, {.24f, 1.30f, .35f}, goldLetter);
    render::box({ux + .48f, cy + .20f, cz}, {.24f, 1.30f, .35f}, goldLetter);
    render::box({ux, cy - .45f, cz}, {1.2f, .22f, .35f}, goldLetter);
    render::box({ux, cy - .65f, cz}, {1.4f, .18f, .45f}, letterBack);
}

// Complete Full Building Exterior Facade
void fullBuildingArchitecture(bool labels) {
    // 1. LEFT VERTICAL TOWER (Terracotta Cladding, Height: 22m, Bilingual Signage)
    const float towerX = -19.5f, towerZ = 9.2f;
    render::texturedBox({towerX, 11.0f, towerZ}, {7.2f, 22.0f, 3.2f}, terracotta, 1);
    for (float vx : {-22.5f, -20.5f, -18.5f, -16.5f}) {
        render::box({vx, 11.0f, towerZ - 1.62f}, {.14f, 21.6f, .10f}, terracottaGroove);
    }
    render::box({towerX, 22.1f, towerZ}, {7.5f, .6f, 3.5f}, terracottaCap);

    // Bilingual Signage Plaques on Front Face of Terracotta Tower
    render::box({towerX, 17.5f, towerZ - 1.65f}, {6.5f, 1.15f, .12f}, darkCharcoalFrame);
    render::text3d({towerX - 2.85f, 17.35f, towerZ - 1.74f}, "SOUTHEAST UNIVERSITY", {1, 1, 1});

    render::box({towerX, 15.8f, towerZ - 1.65f}, {6.5f, 1.15f, .12f}, darkCharcoalFrame);
    render::text3d({towerX - 2.85f, 15.65f, towerZ - 1.74f}, "SOUTHEAST UNIVERSITY (SEU)", {.98f, .88f, .25f});

    render::box({towerX, 14.1f, towerZ - 1.65f}, {6.5f, 1.00f, .12f}, darkCharcoalFrame);
    render::text3d({towerX - 2.85f, 13.95f, towerZ - 1.74f}, "CAMPUS MAIN BUILDING", {.85f, .90f, .95f});

    // 2. CENTRAL ATRIUM & GLAZED VOLUME (4-Story Multi-Tier Grid & Recessed Balconies)
    const float atriumCx = -7.15f, atriumW = 17.3f;
    render::box({atriumCx, 5.2f, 8.85f}, {atriumW, .45f, .65f}, concreteSlab);
    render::box({atriumCx, 9.2f, 8.85f}, {atriumW, .45f, .65f}, concreteSlab);
    render::box({atriumCx, 13.2f, 8.85f}, {atriumW, .45f, .65f}, concreteSlab);
    render::box({atriumCx, 17.5f, 8.85f}, {atriumW, .55f, .75f}, concreteSlab);

    render::glassPanel({atriumCx, 3.2f, 8.78f}, {atriumW - .2f, 3.6f, .08f}, curtainGlass);
    render::glassPanel({atriumCx, 7.2f, 8.78f}, {atriumW - .2f, 3.6f, .08f}, curtainGlass);
    render::glassPanel({atriumCx, 11.2f, 8.78f}, {atriumW - .2f, 3.6f, .08f}, curtainGlass);
    render::glassPanel({atriumCx, 15.3f, 8.78f}, {atriumW - .2f, 3.8f, .08f}, curtainGlass);

    for (float mx = -15.0f; mx <= .8f; mx += 1.6f) {
        render::box({mx, 10.3f, 8.70f}, {.08f, 14.2f, .08f}, darkCharcoalMullion);
    }
    for (float ty : {3.2f, 7.2f, 11.2f, 15.3f}) {
        render::box({atriumCx, ty, 8.69f}, {atriumW, .06f, .08f}, darkCharcoalMullion);
    }

    // 3. RIGHT VERTICAL CORE / PYLON (Brutalist Concrete, Matrix Punctures, 3D "SEU")
    const float pylonCx = 4.5f, pylonW = 6.0f, pylonZ = 9.1f;
    render::box({pylonCx, 10.5f, pylonZ}, {pylonW, 21.0f, 2.8f}, concreteGray);
    for (int row = 0; row < 12; ++row) {
        for (int col = 0; col < 3; ++col) {
            const float px = 2.6f + col * 1.9f;
            const float py = 3.6f + row * 1.35f;
            render::box({px, py, pylonZ - 1.42f}, {.65f, .65f, .12f}, darkCharcoalMullion);
        }
    }
    render::box({pylonCx, 21.2f, pylonZ}, {6.4f, .45f, 3.2f}, concreteOffWhite);
    rooftopLettersSEU(pylonCx, 22.4f, pylonZ - .4f);

    // 4. RIGHT HIGH-RISE WING (East Wing facade: x in [7.5, 16.5])
    render::box({12.0f, 9.0f, 9.25f}, {8.8f, 18.0f, 2.2f}, concreteGray);
    render::glassPanel({12.0f, 8.5f, 8.68f}, {8.2f, 15.5f, .08f}, curtainGlass);
    for (float mx = 8.2f; mx <= 15.8f; mx += 1.8f) {
        render::box({mx, 8.5f, 8.60f}, {.08f, 15.5f, .08f}, darkCharcoalMullion);
    }

    // 5. GROUND & BASE LEVEL: PILOTIS COLONNADE & ENTRANCE APPROACH
    for (float px = -14.0f; px <= 14.0f; px += 3.5f) {
        render::cylinder({px, 2.5f, 8.35f}, .22f, 5.0f, structuralPilotis);
    }

    // Rear exterior facade wall (North side: z = 40.0f)
    render::box({-4.0f, 9.5f, 40.2f}, {40.5f, 19.0f, .45f}, concreteGray);
    // West exterior facade wall (x = -24.0f)
    render::box({-24.2f, 9.5f, 24.5f}, {.45f, 19.0f, 31.0f}, terracotta);
    // East exterior facade wall (x = 16.5f)
    render::box({16.7f, 9.5f, 24.5f}, {.45f, 19.0f, 31.0f}, concreteGray);

    // Rooftop slab & skylight atrium vault (y = 17.5f)
    if (showCeilings) {
        render::box({-4.0f, 17.5f, 24.5f}, {40.5f, .4f, 31.0f}, concreteSlab);
        render::glassPanel({-7.0f, 17.75f, 24.0f}, {14.0f, .10f, 14.0f}, curtainGlass);
    }

    if (labels) {
        render::text3d({-4.5f, 5.8f, 8.50f}, "SOUTHEAST UNIVERSITY", {1, 1, 1});
    }
}

// Second Floor Construction (Floor Level: y = 5.2f, Height: 4.0m to y = 9.2f)
void secondFloorStructure(bool labels) {
    // 1. Ceramic tile floor slabs across the Second Floor
    render::texturedBox({-15.5f, floor2Y, 25.0f}, {17.0f, .12f, 30.5f}, tileFloor, 0);
    render::texturedBox({11.8f, floor2Y, 25.0f}, {9.6f, .12f, 30.5f}, tileFloor, 0);
    // Slabs around Stair 3 well opening (leaving x in [1.3, 4.7], z in [24.0, 30.6] clear)
    render::texturedBox({-2.85f, floor2Y, 34.0f}, {8.3f, .12f, 12.0f}, tileFloor, 0); // West slab: x in [-7.0, 1.3]
    render::texturedBox({5.85f, floor2Y, 34.0f}, {2.3f, .12f, 12.0f}, tileFloor, 0);  // East slab: x in [4.7, 7.0]
    render::texturedBox({3.0f, floor2Y, 35.3f}, {3.4f, .12f, 9.4f}, tileFloor, 0);   // North landing: x in [1.3, 4.7], z in [30.6, 40.0]
    render::texturedBox({-2.5f, floor2Y, 11.5f}, {15.0f, .12f, 4.0f}, tileFloor, 0);

    // 2. Central Atrium Void (Guarded by polished safety glass balustrades with chrome railings)
    const Color glassRail{.24f, .72f, .84f, .45f};

    // South Atrium Railing (z = 14.0f)
    render::glassPanel({0.0f, floor2Y + .55f, 14.0f}, {14.0f, 1.05f, .06f}, glassRail);
    render::box({0.0f, floor2Y + 1.10f, 14.0f}, {14.0f, .06f, .08f}, chrome);
    render::box({0.0f, floor2Y + .04f, 14.0f}, {14.0f, .08f, .10f}, darkCharcoalMullion);

    // North Atrium Railing (z = 24.0f) split to leave Stair 3 open
    render::glassPanel({-2.85f, floor2Y + .55f, 24.0f}, {8.3f, 1.05f, .06f}, glassRail);
    render::box({-2.85f, floor2Y + 1.10f, 24.0f}, {8.3f, .06f, .08f}, chrome);
    render::box({-2.85f, floor2Y + .04f, 24.0f}, {8.3f, .08f, .10f}, darkCharcoalMullion);

    render::glassPanel({5.85f, floor2Y + .55f, 24.0f}, {2.3f, 1.05f, .06f}, glassRail);
    render::box({5.85f, floor2Y + 1.10f, 24.0f}, {2.3f, .06f, .08f}, chrome);
    render::box({5.85f, floor2Y + .04f, 24.0f}, {2.3f, .08f, .10f}, darkCharcoalMullion);

    // West Atrium Railing (x = -7.0f)
    render::glassPanel({-7.0f, floor2Y + .55f, 19.0f}, {.06f, 1.05f, 10.0f}, glassRail);
    render::box({-7.0f, floor2Y + 1.10f, 19.0f}, {.08f, .06f, 10.0f}, chrome);
    render::box({-7.0f, floor2Y + .04f, 19.0f}, {.10f, .08f, 10.0f}, darkCharcoalMullion);

    // East Atrium Railing (x = 7.0f)
    render::glassPanel({7.0f, floor2Y + .55f, 19.0f}, {.06f, 1.05f, 10.0f}, glassRail);
    render::box({7.0f, floor2Y + 1.10f, 19.0f}, {.08f, .06f, 10.0f}, chrome);
    render::box({7.0f, floor2Y + .04f, 19.0f}, {.10f, .08f, 10.0f}, darkCharcoalMullion);

    // 3. Stair 3 Safety Balustrades on Second Floor (flanking stairwell, leaving landing at z = 30.6m open)
    render::glassPanel({1.3f, floor2Y + .55f, 27.3f}, {.06f, 1.05f, 6.6f}, glassRail);
    render::box({1.3f, floor2Y + 1.10f, 27.3f}, {.08f, .06f, 6.6f}, chrome);
    render::box({1.3f, floor2Y + .04f, 27.3f}, {.10f, .08f, 6.6f}, darkCharcoalMullion);

    render::glassPanel({4.7f, floor2Y + .55f, 27.3f}, {.06f, 1.05f, 6.6f}, glassRail);
    render::box({4.7f, floor2Y + 1.10f, 27.3f}, {.08f, .06f, 6.6f}, chrome);
    render::box({4.7f, floor2Y + .04f, 27.3f}, {.10f, .08f, 6.6f}, darkCharcoalMullion);

    // 4. Sky Terrace South Perimeter Railing
    render::glassPanel({-2.5f, floor2Y + .55f, 9.5f}, {15.0f, 1.05f, .06f}, glassRail);
    render::box({-2.5f, floor2Y + 1.10f, 9.5f}, {15.0f, .06f, .08f}, chrome);

    // 5. Second Floor Rooms (All with grand double architectural glass doors)
    room({-24.0f, -11.5f, 28.2f, 40.0f}, roomWhite, "CENTRAL LIBRARY", labels, true, true, floor2Y);
    room({-24.0f, -11.5f, 14.0f, 24.6f}, {.82f, .88f, .94f}, "CSE & AI RESEARCH LAB", labels, true, true, floor2Y);
    room({5.0f, 16.5f, 14.0f, 22.0f}, roomWhite, "SMART CLASSROOM 201", labels, true, true, floor2Y);
    room({-24.0f, -11.5f, 9.5f, 14.0f}, roomOrange, "DEAN'S OFFICE", labels, true, true, floor2Y);

    if (showCeilings) {
        ceilingDecor({-24.0f, 16.5f, 9.5f, 40.0f}, floor2Y);
    }
}

// Third Floor Construction (Floor Level: y = 9.2f, Height: 4.0m to y = 13.2f)
void thirdFloorStructure(bool labels) {
    // 1. Ceramic tile floor slabs across the Third Floor
    render::texturedBox({-15.5f, floor3Y, 25.0f}, {17.0f, .12f, 30.5f}, tileFloor, 0);
    render::texturedBox({11.8f, floor3Y, 25.0f}, {9.6f, .12f, 30.5f}, tileFloor, 0);
    render::texturedBox({0.0f, floor3Y, 34.0f}, {14.0f, .12f, 12.0f}, tileFloor, 0);
    render::texturedBox({-2.5f, floor3Y, 11.5f}, {15.0f, .12f, 4.0f}, tileFloor, 0);

    // Stair 2 continues from Floor 3 to the Floor 4 executive level.
    render::stairs({6.8f, floor3Y, 28.2f}, 2.4f, .25f, .25f, 16, concreteGray);
    if (labels) render::text3d({5.5f, floor3Y + .5f, 27.8f}, "STAIR 2 -> FLOOR 4", {1, .90f, .25f});

    // 2. Central Atrium Void Balustrades (Guarded by polished safety glass balustrades with chrome railings)
    const Color glassRail{.24f, .72f, .84f, .45f};

    // South Atrium Railing (z = 14.0f)
    render::glassPanel({0.0f, floor3Y + .55f, 14.0f}, {14.0f, 1.05f, .06f}, glassRail);
    render::box({0.0f, floor3Y + 1.10f, 14.0f}, {14.0f, .06f, .08f}, chrome);
    render::box({0.0f, floor3Y + .04f, 14.0f}, {14.0f, .08f, .10f}, darkCharcoalMullion);

    // North Atrium Railing (z = 24.0f)
    render::glassPanel({0.0f, floor3Y + .55f, 24.0f}, {14.0f, 1.05f, .06f}, glassRail);
    render::box({0.0f, floor3Y + 1.10f, 24.0f}, {14.0f, .06f, .08f}, chrome);
    render::box({0.0f, floor3Y + .04f, 24.0f}, {14.0f, .08f, .10f}, darkCharcoalMullion);

    // West Atrium Railing (x = -7.0f)
    render::glassPanel({-7.0f, floor3Y + .55f, 19.0f}, {.06f, 1.05f, 10.0f}, glassRail);
    render::box({-7.0f, floor3Y + 1.10f, 19.0f}, {.08f, .06f, 10.0f}, chrome);
    render::box({-7.0f, floor3Y + .04f, 19.0f}, {.10f, .08f, 10.0f}, darkCharcoalMullion);

    // East Atrium Railing (x = 7.0f)
    render::glassPanel({7.0f, floor3Y + .55f, 19.0f}, {.06f, 1.05f, 10.0f}, glassRail);
    render::box({7.0f, floor3Y + 1.10f, 19.0f}, {.08f, .06f, 10.0f}, chrome);
    render::box({7.0f, floor3Y + .04f, 19.0f}, {.10f, .08f, 10.0f}, darkCharcoalMullion);

    // 3. Third Floor Rooms
    room({-24.0f, -11.5f, 26.0f, 40.0f}, roomWhite, "GRAND AUDITORIUM", labels, true, true, floor3Y);
    room({-24.0f, -11.5f, 14.0f, 23.5f}, {.84f, .88f, .94f}, "ROBOTICS & INNOVATION LAB", labels, true, true, floor3Y);
    room({5.0f, 16.5f, 14.0f, 22.0f}, roomWhite, "CONFERENCE SUITE", labels, true, true, floor3Y);
    room({-24.0f, -11.5f, 9.5f, 14.0f}, roomOrange, "CHAIRMAN SUITE", labels, true, true, floor3Y);

    if (showCeilings) {
        ceilingDecor({-24.0f, 16.5f, 9.5f, 40.0f}, floor3Y);
    }
}

// Fourth Floor Construction (Floor Level: y = 13.2f, Height: 4.0m to y = 17.2f)
void fourthFloorStructure(bool labels) {
    // 1. Floor Slabs & Sky Terrace
    render::texturedBox({-15.5f, floor4Y, 25.0f}, {17.0f, .12f, 30.5f}, tileFloor, 0);
    render::texturedBox({11.8f, floor4Y, 25.0f}, {9.6f, .12f, 30.5f}, tileFloor, 0);
    render::texturedBox({0.0f, floor4Y, 34.0f}, {14.0f, .12f, 12.0f}, tileFloor, 0);
    render::texturedBox({-2.5f, floor4Y, 11.5f}, {15.0f, .12f, 4.0f}, tileFloor, 0);

    // 2. Central Atrium Void Balustrades
    const Color glassRail{.24f, .72f, .84f, .45f};

    render::glassPanel({0.0f, floor4Y + .55f, 14.0f}, {14.0f, 1.05f, .06f}, glassRail);
    render::box({0.0f, floor4Y + 1.10f, 14.0f}, {14.0f, .06f, .08f}, chrome);
    render::box({0.0f, floor4Y + .04f, 14.0f}, {14.0f, .08f, .10f}, darkCharcoalMullion);

    render::glassPanel({0.0f, floor4Y + .55f, 24.0f}, {14.0f, 1.05f, .06f}, glassRail);
    render::box({0.0f, floor4Y + 1.10f, 24.0f}, {14.0f, .06f, .08f}, chrome);
    render::box({0.0f, floor4Y + .04f, 24.0f}, {14.0f, .08f, .10f}, darkCharcoalMullion);

    render::glassPanel({-7.0f, floor4Y + .55f, 19.0f}, {.06f, 1.05f, 10.0f}, glassRail);
    render::box({-7.0f, floor4Y + 1.10f, 19.0f}, {.08f, .06f, 10.0f}, chrome);
    render::box({-7.0f, floor4Y + .04f, 19.0f}, {.10f, .08f, 10.0f}, darkCharcoalMullion);

    render::glassPanel({7.0f, floor4Y + .55f, 19.0f}, {.06f, 1.05f, 10.0f}, glassRail);
    render::box({7.0f, floor4Y + 1.10f, 19.0f}, {.08f, .06f, 10.0f}, chrome);
    render::box({7.0f, floor4Y + .04f, 19.0f}, {.10f, .08f, 10.0f}, darkCharcoalMullion);

    // 3. Panoramic Outdoor Sky Terrace Perimeter Railing (South & East)
    render::glassPanel({2.0f, floor4Y + .55f, 9.5f}, {29.0f, 1.05f, .06f}, glassRail);
    render::box({2.0f, floor4Y + 1.10f, 9.5f}, {29.0f, .06f, .08f}, chrome);
    render::glassPanel({16.5f, floor4Y + .55f, 24.5f}, {.06f, 1.05f, 30.0f}, glassRail);
    render::box({16.5f, floor4Y + 1.10f, 24.5f}, {.08f, .06f, 30.0f}, chrome);

    // 4. Fourth Floor Executive Rooms
    room({-24.0f, -11.5f, 26.0f, 40.0f}, roomWhite, "EXECUTIVE BOARDROOM", labels, true, true, floor4Y);
    room({-24.0f, -11.5f, 14.0f, 23.5f}, roomOrange, "CHANCELLOR SUITE", labels, true, true, floor4Y);

    if (showCeilings) {
        ceilingDecor({-24.0f, -11.5f, 9.5f, 40.0f}, floor4Y);
    }
}

void surroundingCampus() {
    // 1. LARGE MODERN HIGH-RISE IN THE RIGHT BACKGROUND
    // Prominent multi-story commercial high-rise tower rising 34m tall
    // Facade featuring reflective steel blue & cyan glass curtain walls and concrete spandrels
    const float hrX = 33.0f, hrZ = 19.0f;
    const float hrW = 12.0f, hrD = 24.0f, hrH = 34.0f;
    // Core concrete structure
    render::box({hrX, hrH * 0.5f, hrZ}, {hrW, hrH, hrD}, concreteGray);
    // Reflective Steel Blue spandrel base facing campus (-X face)
    render::box({hrX - hrW * 0.5f - 0.05f, hrH * 0.5f, hrZ}, {0.10f, hrH - 2.0f, hrD - 1.5f}, reflectiveSteelBlue);
    // Reflective cyan glass curtain panels
    render::glassPanel({hrX - hrW * 0.5f - 0.12f, hrH * 0.5f, hrZ}, {0.12f, hrH - 2.8f, hrD - 2.0f}, highRiseGlass);
    // Concrete floor bands every 3.8m on high-rise
    for (float fy = 4.0f; fy <= hrH - 2.0f; fy += 3.8f) {
        render::box({hrX - hrW * 0.5f - 0.16f, fy, hrZ}, {0.20f, 0.40f, hrD - 1.2f}, concreteSlab);
    }
    // Vertical dark charcoal mullion fins
    for (float mz = hrZ - hrD * 0.42f; mz <= hrZ + hrD * 0.42f; mz += 3.4f) {
        render::box({hrX - hrW * 0.5f - 0.18f, hrH * 0.5f, mz}, {0.22f, hrH - 1.8f, 0.15f}, darkCharcoalMullion);
    }
    // Rooftop mechanical penthouse & communication spire
    render::box({hrX, hrH + 1.2f, hrZ}, {hrW * 0.6f, 2.4f, hrD * 0.5f}, darkCharcoalRooftop);
    render::cylinder({hrX, hrH + 4.2f, hrZ}, 0.14f, 4.4f, chrome);

    // 2. ADJACENT SMALLER STRUCTURES (Left & Rear Campus Periphery)
    // Left adjacent structure (x = -32.0f)
    render::box({-32.0f, 4.0f, 21.0f}, {8.0f, 8.0f, 32.0f}, surroundingConcrete);
    // Earthy brown & dark charcoal rooftop surfaces and parapets
    render::box({-32.0f, 8.1f, 21.0f}, {7.8f, 0.20f, 31.8f}, darkCharcoalRooftop);
    render::box({-32.0f, 8.35f, 21.0f}, {8.2f, 0.35f, 32.2f}, earthyBrownRooftop);
    render::box({-32.0f, 9.2f, 15.0f}, {3.5f, 1.4f, 4.5f}, darkCharcoalRooftop);
    render::box({-32.0f, 9.2f, 27.0f}, {3.5f, 1.4f, 4.5f}, earthyBrownRooftop);

    // Rear adjacent structure (z = 49.0f)
    render::box({0.0f, 3.5f, 49.0f}, {48.0f, 7.0f, 8.0f}, surroundingConcrete);
    render::box({0.0f, 7.1f, 49.0f}, {47.8f, 0.20f, 7.8f}, darkCharcoalRooftop);
    render::box({0.0f, 7.35f, 49.0f}, {48.2f, 0.35f, 8.2f}, earthyBrownRooftop);

    // South perimeter wall & roadside curb
    render::box({0.0f, 1.8f, -9.0f}, {48.0f, 3.6f, 1.2f}, surroundingConcrete);
    render::box({0.0f, 3.7f, -9.0f}, {48.2f, 0.25f, 1.4f}, darkCharcoalRooftop);
}

// Dedicated Grand Architectural Cafeteria & Dining Commons
void cafeteriaCommons(bool /*showLabels*/) {
    const float y = floorY + wallHeight * .5f;
    const Color frameCol{.16f, .18f, .22f};
    const Color frostedCol{.92f, .95f, .98f, .75f};

    // 1. Ceramic tile floor slab
    render::texturedBox({0.0f, floorY, 34.9f}, {20.4f, .1f, 10.2f}, tileFloor, 0);

    // 2. North Exterior Wall with Daylight Glazed Windows (z = 40.0m)
    render::box({0.0f, y, 40.0f}, {20.4f, wallHeight, wallThickness}, roomWhite);
    for (float wx = -7.5f; wx <= 7.5f; wx += 3.75f) {
        render::glassPanel({wx, floorY + 2.4f, 39.95f}, {2.8f, 1.8f, .06f}, glass);
        render::box({wx, floorY + 2.4f, 39.95f}, {2.84f, 1.84f, .02f}, frameCol);
    }

    // 3. West Wall with Connecting Portals to Food Shops 1-2 & Teacher Lounge (x = -10.2m)
    render::box({-10.2f, y, 38.3f}, {wallThickness, wallHeight, 3.4f}, roomWhite); // z in [36.6, 40.0]
    render::box({-10.2f, floorY + 3.1f, 35.1f}, {wallThickness, .60f, 3.0f}, roomWhite); // Header over passage

    // 4. East Wall with Connecting Portals to Food Shops 3-5 (x = 10.2m)
    render::box({10.2f, y, 30.65f}, {wallThickness, wallHeight, 1.7f}, roomWhite); // z in [29.8, 31.5]
    render::box({10.2f, y, 36.5f}, {wallThickness, wallHeight, 3.0f}, roomWhite);  // z in [35.0, 38.0]
    render::box({10.2f, floorY + 3.1f, 33.25f}, {wallThickness, .60f, 3.5f}, roomWhite); // Header over Shop 4
    render::box({10.2f, floorY + 3.1f, 39.0f}, {wallThickness, .60f, 2.0f}, roomWhite);  // Header over Shop 5

    // 5. South Architectural Entrance Facade (z = 29.8m)
    // Left Storefront Glazing: x in [-10.2, -1.8] (width 8.4m)
    render::box({-9.4f, y, 29.8f}, {1.6f, wallHeight, wallThickness}, roomWhite); // Solid corner pier
    render::glassPanel({-5.2f, y, 29.8f}, {6.8f, wallHeight, .08f}, glass);
    render::box({-5.2f, floorY + .04f, 29.8f}, {6.8f, .08f, .12f}, frameCol);
    render::box({-5.2f, floorY + wallHeight - .04f, 29.8f}, {6.8f, .08f, .12f}, frameCol);
    render::glassPanel({-5.2f, floorY + 1.45f, 29.8f}, {6.7f, .14f, .09f}, frostedCol);
    render::box({-5.2f, floorY + 1.48f, 29.816f}, {6.6f, .018f, .005f}, {.18f, .28f, .38f});
    for (float mx = -7.5f; mx <= -2.5f; mx += 1.7f) {
        render::box({mx, y, 29.8f}, {.07f, wallHeight, .12f}, frameCol);
    }

    // Right Storefront Glazing: East of Stair 3 (x in [4.7, 10.2], width 5.5m)
    // Leaving x in [1.5, 4.7] completely open so Stair 3 is 100% visible between upper and lower floors!
    render::glassPanel({6.65f, y, 29.8f}, {3.9f, wallHeight, .08f}, glass);
    render::box({6.65f, floorY + .04f, 29.8f}, {3.9f, .08f, .12f}, frameCol);
    render::box({6.65f, floorY + wallHeight - .04f, 29.8f}, {3.9f, .08f, .12f}, frameCol);
    render::glassPanel({6.65f, floorY + 1.45f, 29.8f}, {3.8f, .14f, .09f}, frostedCol);
    render::box({6.65f, floorY + 1.48f, 29.816f}, {3.7f, .018f, .005f}, {.18f, .28f, .38f});
    for (float mx = 5.2f; mx <= 8.2f; mx += 1.5f) {
        render::box({mx, y, 29.8f}, {.07f, wallHeight, .12f}, frameCol);
    }
    render::box({9.4f, y, 29.8f}, {1.6f, wallHeight, wallThickness}, roomWhite); // Solid corner pier

    // 6. Grand Double Architectural Glass Door (Width 3.6m centered at x = 0.0f, z = 29.8m, open inward)
    architecturalGlassDoor(0.0f, 29.8f, 3.6f, "SEU CENTRAL CAFETERIA", true, floorY, true);

    // Overhead Terracotta Architectural Signage Portal
    render::box({0.0f, floorY + 3.15f, 29.8f}, {4.4f, .55f, .28f}, rustOrange);
    render::box({0.0f, floorY + 3.15f, 29.74f}, {4.2f, .45f, .04f}, {.15f, .18f, .22f});
    render::text3d({-1.85f, floorY + 3.10f, 29.70f}, "SEU CENTRAL CAFETERIA", {1.0f, .90f, .25f});
    render::text3d({-1.70f, floorY + 2.82f, 29.70f}, "CAMPUS DINING COMMONS", {.92f, .95f, .98f});

    if (showCeilings) ceilingDecor({-10.2f, 10.2f, 29.8f, 40.0f}, floorY);
}

} // anonymous namespace

void renderScene(bool showLabels, bool debugBounds, bool ceilings) {
    showCeilings = ceilings;

    // Ground & Landscape Planes
    // 1. Dark Charcoal Asphalt Site Base & Road Infrastructure
    render::plane({0, 0, 20}, {64, 0, 56}, darkCharcoalAsphalt);
    // Concrete Gray road curbs
    render::box({0, .06f, .3f}, {48, .12f, .22f}, concreteGray);
    render::box({0, .06f, 5.2f}, {48, .12f, .22f}, concreteGray);

    // 2. Foreground Garden Lawn (Deep Forest & Olive Green Foliage)
    render::plane({0, .02f, 2.75f}, {34, 0, 4.7f}, gardenGreen);
    render::box({-16.5f, .25f, 2.75f}, {.4f, .48f, 4.7f}, hedgeGreen);
    render::box({16.5f, .25f, 2.75f}, {.4f, .48f, 4.7f}, hedgeGreen);

    // 3. Paved Ground & Driveways (Earthy Brown Paving)
    render::plane({0, .04f, 7.6f}, {48, 0, 4.0f}, earthyBrownPaved);
    render::plane({20, .04f, 24}, {8, 0, 34}, earthyBrownPaved);

    surroundingCampus();
    fullBuildingArchitecture(showLabels);

    // Site Gates
    gate(-18.75f, "IN GATE");
    gate(20.2f, "OUT GATE");

    // Guard Room (Concrete Off-White walls with Earthy Brown & Dark Charcoal Roof)
    render::box({-22.4f, 1.1f, 7.9f}, {3, 2.2f, 2.6f}, concreteOffWhite);
    render::box({-22.4f, 2.25f, 7.9f}, {3.2f, .20f, 2.8f}, darkCharcoalRooftop);
    render::box({-22.4f, 2.40f, 7.9f}, {2.8f, .15f, 2.4f}, earthyBrownRooftop);
    render::box({-22.4f, 1.0f, 6.55f}, {.8f, 1.8f, .10f}, darkCharcoalFrame);
    render::text3d({-23.5f, 2.65f, 7.8f}, "GUARD", {1, 1, 1});

    // Trees in front garden
    for (float x : {-13.f, -5.f, 4.f, 12.f}) tree(x, 2.8f);

    // =========================================================================
    // STAIR 1 (Entrance Ramp from Outdoor Street Level to Ground Floor)
    // =========================================================================
    render::stairs({-4.5f, 0, 8.17f}, 14.5f, .15f, .21f, 8, concreteGray);
    for (float x : {-11.25f, 2.25f}) {
        render::box({x, 1.75f, 9.0f}, {.09f, .09f, 1.9f}, rustOrange);
        for (float z : {8.25f, 8.7f, 9.15f, 9.65f}) render::box({x, .95f + (z-8.17f)*.15f, z}, {.12f, 1.5f, .12f}, rustOrange);
    }

    // Professional Optical Security Turnstiles at Main Entrance Checkpoint (z = 11.5m)
    // Sleek stainless steel pedestals with glowing RFID card-access panels and wide open lanes
    for (float tx : {-8.5f, -6.5f, -4.5f, -2.5f, -0.5f}) {
        render::box({tx, floorY + .50f, 11.5f}, {.24f, 1.00f, 1.10f}, {.22f, .24f, .28f});
        render::box({tx, floorY + 1.01f, 11.5f}, {.26f, .04f, 1.12f}, {.85f, .88f, .92f}); // Stainless steel top
        render::box({tx, floorY + 1.03f, 11.25f}, {.12f, .01f, .16f}, {.18f, .85f, 1.0f});  // Illuminated card reader
    }
    if (showLabels) render::text3d({-7.5f, floorY + 1.35f, 11.5f}, "SEU SECURITY CHECKPOINT - CARD ACCESS", {.18f, .85f, 1.0f});

    // Continuous Ground Floor Ceramic Tile
    render::texturedBox({-4, floorY - .02f, 25}, {40, .08f, 30}, tileFloor, 0);

    // =========================================================================
    // GROUND FLOOR ROOMS
    // =========================================================================
    const float yWall = floorY + wallHeight * .5f;

    // =========================================================================
    // ADMISSION OFFICE 1 (x in [-24.0, -11.5], z in [9.5, 14.0])
    // Grand East Architectural Entrance Gate facing the Main Ground Lobby Corridor
    // =========================================================================
    render::texturedBox({-17.75f, floorY, 11.75f}, {12.5f, .1f, 4.5f}, tileFloor, 0);
    // West exterior building wall
    render::box({-24.0f, yWall, 11.75f}, {wallThickness, wallHeight, 4.5f}, roomOrange);
    // South exterior building facade wall
    render::box({-17.75f, yWall, 9.5f}, {12.5f, wallHeight, wallThickness}, roomOrange);
    // Exterior view window on south wall looking outside
    render::glassPanel({-17.75f, floorY + 2.0f, 9.5f}, {9.5f, 1.6f, .08f}, glass);
    render::box({-17.75f, floorY + 1.15f, 9.5f}, {9.6f, .08f, .12f}, darkCharcoalFrame);
    render::box({-17.75f, floorY + 2.85f, 9.5f}, {9.6f, .08f, .12f}, darkCharcoalFrame);

    // North partition wall at z = 14.0m (dividing Admission 1 from Admission 2 & Bank 1)
    render::box({-21.8f, yWall, 14.0f}, {4.4f, wallHeight, wallThickness}, roomOrange);
    render::box({-14.45f, yWall, 14.0f}, {5.9f, wallHeight, wallThickness}, roomOrange);
    // Internal connecting double glass door into Admission Office 2 (x = -18.5m, width 2.2m)
    architecturalGlassDoor(-18.5f, 14.0f, 2.2f, "ADMISSION 2 EXECUTIVE", true, floorY);

    // East Corridor Wall at x = -11.5m (facing the Main Ground Lobby):
    // South glass sidelight (z in [9.5, 10.6])
    render::glassPanel({-11.5f, yWall, 10.05f}, {.08f, wallHeight, 1.1f}, glass);
    render::box({-11.5f, floorY + .04f, 10.05f}, {.14f, .08f, 1.1f}, darkCharcoalFrame);
    render::box({-11.5f, floorY + wallHeight - .04f, 10.05f}, {.14f, .08f, 1.1f}, darkCharcoalFrame);
    render::box({-11.5f, yWall, 9.5f}, {.16f, wallHeight, .16f}, rustOrange); // Corner pillar

    // North glass sidelight (z in [13.0, 14.0])
    render::glassPanel({-11.5f, yWall, 13.5f}, {.08f, wallHeight, 1.0f}, glass);
    render::box({-11.5f, floorY + .04f, 13.5f}, {.14f, .08f, 1.0f}, darkCharcoalFrame);
    render::box({-11.5f, floorY + wallHeight - .04f, 13.5f}, {.14f, .08f, 1.0f}, darkCharcoalFrame);
    render::box({-11.5f, yWall, 14.0f}, {.16f, wallHeight, .16f}, rustOrange); // Corner pillar

    // Grand Entrance Gate at x = -11.5m, z in [10.6, 13.0] (width 2.4m)
    architecturalGlassDoorZ(-11.5f, 11.8f, 2.4f, "ADMISSION OFFICE 1", true, floorY, true);

    // Overhead Grand Illuminated Portal Architrave & Welcome Fascia
    render::box({-11.5f, floorY + 3.15f, 11.8f}, {.26f, .55f, 2.8f}, rustOrange);
    render::box({-11.5f, floorY + 3.45f, 11.8f}, {.28f, .06f, 2.85f}, darkCharcoalFrame);
    render::box({-11.5f, floorY + 2.85f, 11.8f}, {.28f, .06f, 2.85f}, darkCharcoalFrame);
    render::text3d({-11.35f, floorY + 3.25f, 10.7f}, "ADMISSION OFFICE 1", {1.0f, .95f, .30f});
    render::text3d({-11.35f, floorY + 2.98f, 10.8f}, "SOUTHEAST UNIVERSITY", {1, 1, 1});
    render::text3d({-11.35f, floorY + 2.70f, 11.1f}, "INQUIRE & ENROLL", {.20f, .90f, 1.0f});
    render::text3d({-11.65f, floorY + 3.25f, 10.7f}, "ADMISSION OFFICE 1", {1.0f, .95f, .30f});
    render::text3d({-11.65f, floorY + 2.98f, 10.8f}, "SOUTHEAST UNIVERSITY", {1, 1, 1});

    ceilingDecor({-24.0f, -11.5f, 9.5f, 14.0f}, floorY);
    if (showLabels) label({-24.0f, -11.5f, 9.5f, 14.0f}, "ADMISSION OFFICE 1", true, floorY);

    // =========================================================================
    // ADMISSION OFFICE 2 (x in [-24.0, -16.2], z in [14.0, 21.6]) - EXECUTIVE SUITE
    // =========================================================================
    render::texturedBox({-20.1f, floorY, 17.8f}, {7.8f, .1f, 7.6f}, tileFloor, 0);
    render::box({-24.0f, yWall, 17.8f}, {wallThickness, wallHeight, 7.6f}, roomOrange); // West
    render::box({-20.1f, yWall, 21.6f}, {7.8f, wallHeight, wallThickness}, roomOrange); // North
    render::box({-16.2f, yWall, 17.8f}, {wallThickness, wallHeight, 7.6f}, roomOrange); // East divider with Bank 1
    ceilingDecor({-24.0f, -16.2f, 14.0f, 21.6f}, floorY);
    if (showLabels) label({-24.0f, -16.2f, 14.0f, 21.6f}, "ADMISSION OFFICE 2", true, floorY);

    // =========================================================================
    // BANK 1 (x in [-16.2, -11.5], z in [14.0, 21.6]) - SEU CAMPUS BANK
    // =========================================================================
    render::texturedBox({-13.85f, floorY, 17.8f}, {4.7f, .1f, 7.6f}, tileFloor, 0);
    render::box({-13.85f, yWall, 21.6f}, {4.7f, wallHeight, wallThickness}, roomOrange); // North
    // East wall along corridor (x = -11.5m)
    render::box({-11.5f, yWall, 14.6f}, {wallThickness, wallHeight, 1.2f}, roomOrange);
    architecturalGlassDoorZ(-11.5f, 16.3f, 2.2f, "SEU CAMPUS BANK", true, floorY, true);
    render::glassPanel({-11.5f, yWall, 19.5f}, {.08f, wallHeight, 4.2f}, glass);
    render::box({-11.5f, floorY + .04f, 19.5f}, {.14f, .08f, 4.2f}, darkCharcoalFrame);
    render::box({-11.5f, floorY + wallHeight - .04f, 19.5f}, {.14f, .08f, 4.2f}, darkCharcoalFrame);
    render::text3d({-11.35f, floorY + 3.1f, 15.4f}, "SEU CAMPUS BANK", {1, .92f, .30f});
    ceilingDecor({-16.2f, -11.5f, 14.0f, 21.6f}, floorY);
    if (showLabels) label({-16.2f, -11.5f, 14.0f, 21.6f}, "BANK 1", true, floorY);
    room({-24.0f, -20.8f, 21.6f, 24.6f}, {.78f, .86f, .90f}, "INFIRMARY", showLabels);
    room({-24.0f, -20.8f, 24.6f, 28.2f}, roomWhite, "FEMALE WASHROOM", showLabels);

    // West Elevator Core (Lifts 3 & 4) Shaft Enclosure
    // Approach in front of West lifts (x in [-20.8, -10.2], z in [21.6, 25.0]) is wide, open, and free of blockers
    render::box({-20.8f, floorY + wallHeight * .5f, 26.6f}, {wallThickness, wallHeight, 3.2f}, roomSteel); // West
    render::box({-10.2f, floorY + wallHeight * .5f, 26.6f}, {wallThickness, wallHeight, 3.2f}, roomSteel); // East
    render::box({-15.5f, floorY + wallHeight * .5f, 28.2f}, {10.6f, wallHeight, wallThickness}, roomSteel); // North back
    render::box({-15.5f, floorY + 3.0f, 25.0f}, {10.6f, .60f, wallThickness}, roomSteel);                   // Header over lobby
    if (showLabels) render::text3d({-17.5f, floorY + 3.1f, 24.8f}, "LIFT CORE 2 [LIFT 3 / LIFT 4]", {1, .9f, .25f});

    // =========================================================================
    // TEACHER & FACULTY LOUNGE (Ground Floor: x in [-24.0, -10.2], z in [28.2, 33.6])
    // Grand East entrance facing the main corridor leading directly to the Cafeteria
    // =========================================================================
    render::texturedBox({-17.1f, floorY, 30.9f}, {13.8f, .1f, 5.4f}, tileFloor, 0);
    render::box({-24.0f, yWall, 30.9f}, {wallThickness, wallHeight, 5.4f}, roomWhite);  // West exterior
    render::box({-17.1f, yWall, 33.6f}, {13.8f, wallHeight, wallThickness}, roomWhite); // North divider with Food Shop 2
    render::box({-17.1f, yWall, 28.2f}, {13.8f, wallHeight, wallThickness}, roomWhite); // South divider behind Lifts

    // East Corridor Frontage (x = -10.2m): Highly visible from the corridor and cafeteria
    render::box({-10.2f, yWall, 28.8f}, {wallThickness, wallHeight, 1.2f}, roomWhite);   // South corner partition
    architecturalGlassDoorZ(-10.2f, 30.6f, 2.4f, "TEACHER & FACULTY LOUNGE", true, floorY, true);

    // Overhead Terracotta Architectural Signage Portal
    render::box({-10.2f, floorY + 3.15f, 30.6f}, {.28f, .55f, 2.8f}, rustOrange);
    render::box({-10.14f, floorY + 3.15f, 30.6f}, {.04f, .45f, 2.7f}, {.15f, .18f, .22f});
    render::text3d({-10.10f, floorY + 3.10f, 29.5f}, "TEACHER & FACULTY LOUNGE", {1.0f, .90f, .25f});
    render::text3d({-10.10f, floorY + 2.82f, 29.5f}, "SOUTHEAST UNIVERSITY - STAFF ONLY", {.92f, .95f, .98f});

    // Clear viewing glass sidelights looking into the Teacher Lounge
    render::glassPanel({-10.2f, yWall, 32.7f}, {.08f, wallHeight, 1.8f}, glass);
    render::box({-10.2f, floorY + .04f, 32.7f}, {.12f, .08f, 1.8f}, darkCharcoalFrame);
    render::box({-10.2f, floorY + wallHeight - .04f, 32.7f}, {.12f, .08f, 1.8f}, darkCharcoalFrame);

    if (showCeilings) ceilingDecor({-24.0f, -10.2f, 28.2f, 33.6f}, floorY);
    if (showLabels) render::text3d({-18.0f, floorY + 3.1f, 30.9f}, "FACULTY LOUNGE", {1, 1, 1});

    // =========================================================================
    // DEDICATED OPEN-FRONT FOOD SHOPS 1 TO 5 (AROUND CAFETERIA)
    // =========================================================================

    // --- FOOD SHOP 1 (x in [-24, -20.8], z in [36.6, 40.0]) - SEU DELI & BURGERS ---
    render::box({-24.0f, yWall, 38.3f}, {wallThickness, wallHeight, 3.4f}, roomGreen); // Back West
    render::box({-22.4f, yWall, 40.0f}, {3.2f, wallHeight, wallThickness}, roomGreen); // North
    render::box({-22.4f, yWall, 36.6f}, {3.2f, wallHeight, wallThickness}, roomGreen); // South divider
    // Front Counter & Serving Window facing East into Cafeteria (x = -20.8m)
    render::box({-20.8f, floorY + .45f, 38.3f}, {.22f, .90f, 3.4f}, {.28f, .30f, .34f});
    render::box({-20.8f, floorY + .92f, 38.3f}, {.40f, .06f, 3.5f}, {.78f, .80f, .84f});
    render::box({-20.8f, floorY + 2.85f, 38.3f}, {.24f, .70f, 3.4f}, {.85f, .22f, .15f}); // Crimson canopy
    render::text3d({-20.65f, floorY + 2.85f, 37.0f}, "SHOP 1: SEU DELI & BURGERS", {1.0f, .90f, .25f});

    // --- FOOD SHOP 2 (x in [-24, -20.8], z in [33.6, 36.6]) - PIZZA & HOT ROLLS ---
    render::box({-24.0f, yWall, 35.1f}, {wallThickness, wallHeight, 3.0f}, roomGreen); // Back West
    render::box({-22.4f, yWall, 33.6f}, {3.2f, wallHeight, wallThickness}, roomGreen); // South wall
    // Front Counter & Serving Window facing East into Cafeteria (x = -20.8m)
    render::box({-20.8f, floorY + .45f, 35.1f}, {.22f, .90f, 3.0f}, {.28f, .30f, .34f});
    render::box({-20.8f, floorY + .92f, 35.1f}, {.40f, .06f, 3.1f}, {.78f, .80f, .84f});
    render::box({-20.8f, floorY + 2.85f, 35.1f}, {.24f, .70f, 3.0f}, {.92f, .48f, .12f}); // Orange canopy
    render::text3d({-20.65f, floorY + 2.85f, 34.0f}, "SHOP 2: PIZZA & HOT ROLLS", {1.0f, .92f, .30f});

    // --- CAFETERIA CENTRAL COMMONS ---
    cafeteriaCommons(showLabels);

    // --- FOOD SHOP 5 (x in [10.2, 14.0], z in [38.0, 40.0]) - ASIAN NOODLE BOWL ---
    render::box({12.1f, yWall, 40.0f}, {3.8f, wallHeight, wallThickness}, roomGreen); // North
    render::box({14.0f, yWall, 39.0f}, {wallThickness, wallHeight, 2.0f}, roomGreen); // East
    render::box({10.2f, yWall, 39.0f}, {wallThickness, wallHeight, 2.0f}, roomGreen); // West
    // Front Counter facing South into Cafeteria (z = 38.0m)
    render::box({12.1f, floorY + .45f, 38.0f}, {3.8f, .90f, .22f}, {.28f, .30f, .34f});
    render::box({12.1f, floorY + .92f, 38.0f}, {3.9f, .06f, .40f}, {.78f, .80f, .84f});
    render::box({12.1f, floorY + 2.85f, 38.0f}, {3.8f, .70f, .24f}, {.95f, .68f, .15f}); // Amber gold canopy
    render::text3d({10.5f, floorY + 2.85f, 37.85f}, "SHOP 5: ASIAN NOODLE BOWL", {1.0f, .90f, .25f});

    // --- FOOD SHOP 3 (x in [13.8, 16.6], z in [36.0, 39.0]) - BAKERY & CAFE ---
    render::box({16.6f, yWall, 37.5f}, {wallThickness, wallHeight, 3.0f}, roomGreen); // Back East
    render::box({15.2f, yWall, 39.0f}, {2.8f, wallHeight, wallThickness}, roomGreen); // North
    render::box({15.2f, yWall, 36.0f}, {2.8f, wallHeight, wallThickness}, roomGreen); // South divider
    // Front Counter facing West into Cafeteria (x = 13.8m)
    render::box({13.8f, floorY + .45f, 37.5f}, {.22f, .90f, 3.0f}, {.28f, .30f, .34f});
    render::box({13.8f, floorY + .92f, 37.5f}, {.40f, .06f, 3.1f}, {.78f, .80f, .84f});
    render::box({13.8f, floorY + 2.85f, 37.5f}, {.24f, .70f, 3.0f}, {.42f, .26f, .16f}); // Mocha canopy
    render::text3d({13.65f, floorY + 2.85f, 36.5f}, "SHOP 3: BAKERY & CAFE", {1.0f, .90f, .35f});

    // --- FOOD SHOP 4 (x in [13.8, 16.6], z in [31.5, 35.0]) - FRESH JUICE BAR ---
    render::box({16.6f, yWall, 33.25f}, {wallThickness, wallHeight, 3.5f}, roomGreen); // Back East
    render::box({15.2f, yWall, 35.0f}, {2.8f, wallHeight, wallThickness}, roomGreen); // North
    render::box({15.2f, yWall, 31.5f}, {2.8f, wallHeight, wallThickness}, roomGreen); // South
    // Front Counter facing West into Cafeteria (x = 13.8m)
    render::box({13.8f, floorY + .45f, 33.25f}, {.22f, .90f, 3.5f}, {.28f, .30f, .34f});
    render::box({13.8f, floorY + .92f, 33.25f}, {.40f, .06f, 3.6f}, {.78f, .80f, .84f});
    render::box({13.8f, floorY + 2.85f, 33.25f}, {.24f, .70f, 3.5f}, {.18f, .72f, .32f}); // Lime green canopy
    render::text3d({13.65f, floorY + 2.85f, 32.2f}, "SHOP 4: FRESH JUICE BAR", {.20f, 1.0f, .45f});

    // =========================================================================
    // STAIR 3: Grand 16-Step Staircase Leading to SECOND FLOOR
    // =========================================================================
    render::stairs({3.0f, floorY, 24.5f}, 2.5f, .25f, .35f, 16, concreteGray);
    for (float sx : {1.65f, 4.35f}) {
        render::box({sx, floorY + 2.1f + 2.0f, 27.3f}, {.08f, .08f, 5.8f}, rustOrange);
        for (int step = 0; step < 16; step += 3) {
            const float sz = 24.5f + step * .35f;
            const float sy = floorY + step * .25f;
            render::box({sx, sy + .55f, sz}, {.06f, 1.10f, .06f}, rustOrange);
        }
    }
    if (showLabels) render::text3d({1.8f, floorY + .5f, 24.2f}, "STAIR 3 -> FLOOR 2", {1, .90f, .25f});

    // East Elevator Core (Lifts 1 & 2) Shaft Enclosure
    render::box({5.15f, floorY + wallHeight * .5f, 26.65f}, {wallThickness, wallHeight, 2.9f}, roomSteel); // West
    render::box({13.25f, floorY + wallHeight * .5f, 26.65f}, {wallThickness, wallHeight, 2.9f}, roomSteel); // East
    render::box({9.20f, floorY + wallHeight * .5f, 28.1f}, {8.1f, wallHeight, wallThickness}, roomSteel);   // North back
    render::box({9.20f, floorY + 3.0f, 25.2f}, {8.1f, .60f, wallThickness}, roomSteel);                     // Header over lobby
    if (showLabels) render::text3d({7.2f, floorY + 3.1f, 25.0f}, "LIFT CORE 1 [LIFT 1 / LIFT 2]", {1, .9f, .25f});

    // =========================================================================
    // STAIR 2: Secondary 16-Step Staircase to SECOND FLOOR
    // =========================================================================
    render::stairs({6.8f, floorY, 28.2f}, 2.4f, .25f, .25f, 16, concreteGray);
    if (showLabels) render::text3d({5.5f, floorY + .5f, 27.8f}, "STAIR 2 -> FLOOR 2", {1, .90f, .25f});

    room({13.4f,16.6f,25.0f,28.1f}, roomWhite, "MALE WASHROOM", showLabels);
    room({7.4f,12.0f,18.2f,22.2f}, roomOrange, "BANK 2", showLabels, true);

    // =========================================================================
    // SEU UNIVERSITY STATIONERY & BOOKSTORE (x in [12.0, 16.6], z in [18.2, 22.2])
    // =========================================================================
    render::texturedBox({14.3f, floorY, 20.2f}, {4.6f, .1f, 4.0f}, tileFloor, 0);
    render::box({14.3f, yWall, 22.2f}, {4.6f, wallHeight, wallThickness}, roomWhite); // North
    render::box({16.6f, yWall, 20.2f}, {wallThickness, wallHeight, 4.0f}, roomWhite); // East
    render::box({12.0f, yWall, 20.2f}, {wallThickness, wallHeight, 4.0f}, roomOrange); // West divider with Bank 2

    // Storefront on z = 18.2m (facing wide cross-corridor):
    // Left display window (x in [12.0, 13.1]):
    render::glassPanel({12.55f, yWall, 18.2f}, {1.10f, wallHeight, .08f}, glass);
    render::box({12.55f, floorY + .04f, 18.2f}, {1.10f, .08f, .12f}, darkCharcoalFrame);
    // Right display window (x in [15.3, 16.6]):
    render::glassPanel({15.95f, yWall, 18.2f}, {1.30f, wallHeight, .08f}, glass);
    render::box({15.95f, floorY + .04f, 18.2f}, {1.30f, .08f, .12f}, darkCharcoalFrame);
    // Central Grand Double Glass Door (x = 14.2m, width 2.2m, open inward)
    architecturalGlassDoor(14.2f, 18.2f, 2.2f, "STATIONERY & BOOKS", true, floorY, true);

    // Overhead Storefront Illuminated Fascia Banner:
    render::box({14.3f, floorY + 2.95f, 18.16f}, {4.6f, .55f, .12f}, {.12f, .22f, .48f});
    render::box({14.3f, floorY + 2.95f, 18.18f}, {4.4f, .45f, .02f}, {.15f, .18f, .24f});
    render::text3d({12.3f, floorY + 2.90f, 18.12f}, "SEU UNIVERSITY STATIONERY & BOOKSTORE", {1.0f, .85f, .25f});

    // Gaming Suite with architectural glass walls and glass doors
    gamingSuite(showLabels);

    if (showCeilings) ceilingDecor({-11, 9, 17, 30});

    // =========================================================================
    // MULTI-FLOOR ARCHITECTURE: FLOORS 2, 3, AND 4
    // =========================================================================
    secondFloorStructure(showLabels);
    thirdFloorStructure(showLabels);
    fourthFloorStructure(showLabels);

    // Furnishings across Ground Floor and Upper Floors
    renderFurniture(showLabels);

    if (debugBounds) {
        outline(building); outline(garden); outline(admin); outline(gaming);
    }
}

} // namespace campus
