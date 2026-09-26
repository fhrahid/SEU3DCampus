#include "GameManager.h"
#include "../core/Input.h"
#include "../render/Primitives.h"
#include <GL/glut.h>
#include <cstdio>
#include <algorithm>

void GameManager::enter(int initialGame) {
    active_ = true;
    game_ = initialGame;
    if (game_ == 0) ttt_.reset();
    else if (game_ == 1) rps_.reset();
    else if (game_ == 2) game2048_.reset();
    else if (game_ == 3) cube_.reset();
    else if (game_ == 4) ludo_.reset();
}

void GameManager::update(const Input& input) {
    if (!active_) return;

    if (input.pressed(27)) { // Esc key
        if (game_ == -1) {
            active_ = false; // Step away from the screen back to campus
        } else {
            game_ = -1; // Return to screen master menu
        }
        return;
    }

    if (game_ == -1) {
        if (input.pressed('1')) { ttt_.reset(); game_ = 0; }
        else if (input.pressed('2')) { rps_.reset(); game_ = 1; }
        else if (input.pressed('3')) { game2048_.reset(); game_ = 2; }
        else if (input.pressed('4')) { cube_.reset(); game_ = 3; }
        else if (input.pressed('5')) { ludo_.reset(); game_ = 4; }
        return;
    }

    switch (game_) {
        case 0: ttt_.update(input); break;
        case 1: rps_.update(input); break;
        case 2: game2048_.update(input); break;
        case 3: cube_.update(input); break;
        case 4: ludo_.update(input); break;
    }
}

void GameManager::render(int width, int height) const {
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glDisable(GL_DEPTH_TEST); glDisable(GL_LIGHTING);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1. Semi-transparent dark cinematic room dimmer (keeps 3D gaming room visible in background!)
    glColor4f(.02f, .03f, .05f, .70f);
    glBegin(GL_QUADS);
    glVertex2i(0, 0); glVertex2i(width, 0); glVertex2i(width, height); glVertex2i(0, height);
    glEnd();

    // 2. Calculate Monitor Dimensions & Centering
    const int monW = std::min(780, width - 40);
    const int monH = std::min(580, height - 50);
    const int monX = (width - monW) / 2;
    const int monY = std::max(10, (height - monH) / 2 - 10);
    const int cx = monX + monW / 2;

    // 3. Monitor Desktop Stand & Pedestal
    // Neck
    glColor3f(.22f, .25f, .30f);
    glBegin(GL_QUADS);
    glVertex2i(cx - 36, monY + monH);
    glVertex2i(cx + 36, monY + monH);
    glVertex2i(cx + 46, monY + monH + 26);
    glVertex2i(cx - 46, monY + monH + 26);
    glEnd();
    // Neck metallic spine highlight
    glColor3f(.42f, .46f, .54f);
    glBegin(GL_LINES);
    glVertex2i(cx, monY + monH); glVertex2i(cx, monY + monH + 26);
    glEnd();

    // Heavy trapezoidal desktop base plate
    glColor3f(.14f, .16f, .20f);
    glBegin(GL_QUADS);
    glVertex2i(cx - 130, monY + monH + 24);
    glVertex2i(cx + 130, monY + monH + 24);
    glVertex2i(cx + 142, monY + monH + 34);
    glVertex2i(cx - 142, monY + monH + 34);
    glEnd();
    glColor3f(.32f, .36f, .42f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(cx - 130, monY + monH + 24);
    glVertex2i(cx + 130, monY + monH + 24);
    glVertex2i(cx + 142, monY + monH + 34);
    glVertex2i(cx - 142, monY + monH + 34);
    glEnd();

    // 4. Outer RGB Ambient Halo (Cyan / Neon Blue backlight reflection)
    glColor4f(.10f, .50f, .92f, .20f);
    glBegin(GL_QUADS);
    glVertex2i(monX - 10, monY - 10);
    glVertex2i(monX + monW + 10, monY - 10);
    glVertex2i(monX + monW + 10, monY + monH + 10);
    glVertex2i(monX - 10, monY + monH + 10);
    glEnd();

    // 5. Monitor Chassis & Beveled Frame
    glColor3f(.10f, .12f, .16f); // Dark titanium housing
    glBegin(GL_QUADS);
    glVertex2i(monX, monY);
    glVertex2i(monX + monW, monY);
    glVertex2i(monX + monW, monY + monH);
    glVertex2i(monX, monY + monH);
    glEnd();

    // Outer border chamfer
    glColor3f(.25f, .28f, .34f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(monX, monY);
    glVertex2i(monX + monW, monY);
    glVertex2i(monX + monW, monY + monH);
    glVertex2i(monX, monY + monH);
    glEnd();

    // Inner bezel step
    glColor3f(.15f, .17f, .21f);
    glBegin(GL_QUADS);
    glVertex2i(monX + 8, monY + 8);
    glVertex2i(monX + monW - 8, monY + 8);
    glVertex2i(monX + monW - 8, monY + monH - 8);
    glVertex2i(monX + 8, monY + monH - 8);
    glEnd();

    // 6. Active Screen Surface
    const int scrX = monX + 22;
    const int scrY = monY + 20;
    const int scrW = monW - 44;
    const int scrH = monH - 52;

    // Deep OLED screen panel
    glColor3f(.022f, .032f, .050f);
    glBegin(GL_QUADS);
    glVertex2i(scrX, scrY);
    glVertex2i(scrX + scrW, scrY);
    glVertex2i(scrX + scrW, scrY + scrH);
    glVertex2i(scrX, scrY + scrH);
    glEnd();

    // Inner glowing cyan bezel trim
    glColor3f(.14f, .38f, .55f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(scrX, scrY);
    glVertex2i(scrX + scrW, scrY);
    glVertex2i(scrX + scrW, scrY + scrH);
    glVertex2i(scrX, scrY + scrH);
    glEnd();

    // CRT / Display subtle horizontal scanlines
    glColor4f(0.0f, 0.0f, 0.0f, .09f);
    glBegin(GL_LINES);
    for (int y = scrY + 2; y < scrY + scrH; y += 4) {
        glVertex2i(scrX, y); glVertex2i(scrX + scrW, y);
    }
    glEnd();

    // 7. Bottom Bezel: Brand Plate, Speaker Slots & Power LED
    const int bezY = monY + monH - 22;
    render::text2d(cx - 105, bezY + 12, "SEU ESPORTS DISPLAY 240Hz", {.65f, .70f, .78f});

    // Pulsing green power LED on right of bezel
    glColor3f(.12f, .95f, .38f);
    glBegin(GL_QUADS);
    glVertex2i(monX + monW - 32, bezY + 4);
    glVertex2i(monX + monW - 24, bezY + 4);
    glVertex2i(monX + monW - 24, bezY + 12);
    glVertex2i(monX + monW - 32, bezY + 12);
    glEnd();

    // Stereo speaker grilles on left of bezel
    glColor3f(.06f, .07f, .09f);
    glBegin(GL_LINES);
    for (int sx = monX + 24; sx <= monX + 80; sx += 6) {
        glVertex2i(sx, bezY + 4); glVertex2i(sx, bezY + 12);
    }
    glEnd();

    // 8. Top On-Screen Display (OSD) Status Bar inside the screen
    glColor3f(.06f, .09f, .15f);
    glBegin(GL_QUADS);
    glVertex2i(scrX + 1, scrY + 1);
    glVertex2i(scrX + scrW - 1, scrY + 1);
    glVertex2i(scrX + scrW - 1, scrY + 32);
    glVertex2i(scrX + 1, scrY + 32);
    glEnd();

    glColor3f(.15f, .45f, .65f);
    glBegin(GL_LINES);
    glVertex2i(scrX, scrY + 33);
    glVertex2i(scrX + scrW, scrY + 33);
    glEnd();

    render::text2d(scrX + 12, scrY + 22, "SEU SCREEN", {1.0f, .82f, .22f});

    // Channel tabs in OSD bar
    const char* tabs[5] = {"1:TTT", "2:RPS", "3:2048", "4:Cube", "5:Ludo"};
    for (int t = 0; t < 5; ++t) {
        const int tabX = scrX + 135 + t * 86;
        const bool activeTab = (game_ == t);
        if (activeTab) {
            glColor3f(.12f, .48f, .78f);
            glBegin(GL_QUADS);
            glVertex2i(tabX - 4, scrY + 6);
            glVertex2i(tabX + 76, scrY + 6);
            glVertex2i(tabX + 76, scrY + 28);
            glVertex2i(tabX - 4, scrY + 28);
            glEnd();
        }
        render::text2d(tabX, scrY + 22, tabs[t], activeTab ? render::Color{1, 1, 1} : render::Color{.55f, .62f, .72f});
    }

    render::text2d(scrX + scrW - 130, scrY + 22, "ESC: Menu/Exit", {.82f, .85f, .90f});

    // 9. Display Content (Menu vs Active Game)
    if (game_ == -1) {
        // High-tech Screen Main Menu
        render::text2d(scrX + 35, scrY + 68, "SEU ESPORTS & GAMING ARENA - INTERACTIVE SCREEN", {1.0f, .85f, .25f});
        render::text2d(scrX + 35, scrY + 98, "SELECT A GAME TO PLAY DIRECTLY ON THIS SCREEN:", {.75f, .85f, .95f});

        struct GameCard { const char* key; const char* title; const char* desc; render::Color col; };
        const GameCard cards[5] = {
            {"1", "TIC-TAC-TOE",       "Classic 2-Player Strategy Board (WASD/1-9 select, Space place)", {.25f, .92f, 1.0f}},
            {"2", "ROCK PAPER SCISS",  "Fast Reflex Match vs Autonomous AI Challenger (1/2/3 select)",      {.95f, .55f, .25f}},
            {"3", "2048 ARCADE",       "Tile Sliding Puzzle: Merge 2048 block (WASD/Arrows slide)",         {.35f, .95f, .45f}},
            {"4", "RUBIK'S CUBE",      "3D Unfolded Net Cube Simulator (U/D/L/R/F/B turn, X scramble)",     {1.0f, .85f, .25f}},
            {"5", "LUDO CHAMPIONSHIP", "4-Token Board Game vs Computer (Space roll, 1-4 token move)",      {.95f, .35f, .45f}}
        };

        for (int i = 0; i < 5; ++i) {
            const int cardY = scrY + 120 + i * 56;
            // Card background
            glColor3f(.06f, .09f, .15f);
            glBegin(GL_QUADS);
            glVertex2i(scrX + 35, cardY);
            glVertex2i(scrX + scrW - 35, cardY);
            glVertex2i(scrX + scrW - 35, cardY + 48);
            glVertex2i(scrX + 35, cardY + 48);
            glEnd();

            // Border highlight
            glColor3f(cards[i].col.r * .5f, cards[i].col.g * .5f, cards[i].col.b * .5f);
            glBegin(GL_LINE_LOOP);
            glVertex2i(scrX + 35, cardY);
            glVertex2i(scrX + scrW - 35, cardY);
            glVertex2i(scrX + scrW - 35, cardY + 48);
            glVertex2i(scrX + 35, cardY + 48);
            glEnd();

            // Key badge
            glColor3f(cards[i].col.r, cards[i].col.g, cards[i].col.b);
            glBegin(GL_QUADS);
            glVertex2i(scrX + 45, cardY + 7);
            glVertex2i(scrX + 80, cardY + 7);
            glVertex2i(scrX + 80, cardY + 41);
            glVertex2i(scrX + 45, cardY + 41);
            glEnd();

            render::text2d(scrX + 57, cardY + 29, cards[i].key, {0, 0, 0});
            render::text2d(scrX + 95, cardY + 24, cards[i].title, cards[i].col);
            render::text2d(scrX + 95, cardY + 41, cards[i].desc, {.78f, .80f, .85f});
        }

        render::text2d(scrX + 35, scrY + scrH - 18, "PRESS 1, 2, 3, 4, OR 5 TO PLAY | ESC TO STEP AWAY FROM SCREEN", {.85f, .88f, .95f});
    } else {
        // Frame active game perfectly inside screen display area
        const int gameOffsetX = scrX + (scrW - 530) / 2 - 55;
        const int gameOffsetY = scrY + 38 - 65;

        glPushMatrix();
        glTranslatef(gameOffsetX, gameOffsetY, 0);

        switch (game_) {
            case 0: ttt_.render(scrW, scrH); break;
            case 1: rps_.render(scrW, scrH); break;
            case 2: game2048_.render(scrW, scrH); break;
            case 3: cube_.render(scrW, scrH); break;
            case 4: ludo_.render(scrW, scrH); break;
        }

        glPopMatrix();

        // Screen bottom navigation hint
        render::text2d(scrX + 20, scrY + scrH - 14, "[ESC] Return to Screen Menu  |  [N] New Game  |  [1-5] Quick Switch Channel", {.70f, .75f, .82f});
    }

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
