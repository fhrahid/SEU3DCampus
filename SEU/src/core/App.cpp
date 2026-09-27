#include "App.h"
#include "Config.h"
#include "../render/Primitives.h"
#include "../render/TextureManager.h"
#include <GL/glut.h>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>

namespace {
// Stylized 3D Player Avatar drawn in third-person / drone view
void drawPlayerAvatar(const Vec3& pos, float yaw, bool seated) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(yaw - 90.0f, 0, 1, 0);

    const render::Color skin{.92f, .78f, .68f};
    const render::Color shirt{.18f, .38f, .68f};
    const render::Color pants{.22f, .24f, .28f};
    const render::Color hair{.12f, .10f, .08f};
    const render::Color backpack{.78f, .25f, .12f};
    const render::Color shoes{.10f, .10f, .12f};

    if (seated) {
        render::box({0, .45f, .12f}, {.42f, .55f, .24f}, shirt);
        render::box({0, .45f, -.04f}, {.32f, .42f, .12f}, backpack);
        render::box({0, .88f, .12f}, {.22f, .24f, .22f}, skin);
        render::box({0, 1.02f, .12f}, {.24f, .10f, .24f}, hair);
        render::box({-.12f, .38f, .32f}, {.16f, .16f, .42f}, pants);
        render::box({ .12f, .38f, .32f}, {.16f, .16f, .42f}, pants);
        render::box({-.12f, .16f, .52f}, {.16f, .32f, .16f}, pants);
        render::box({ .12f, .16f, .52f}, {.16f, .32f, .16f}, pants);
        render::box({-.12f, .04f, .56f}, {.18f, .08f, .24f}, shoes);
        render::box({ .12f, .04f, .56f}, {.18f, .08f, .24f}, shoes);
    } else {
        render::box({-.13f, .08f, .04f}, {.18f, .14f, .28f}, shoes);
        render::box({ .13f, .08f, .04f}, {.18f, .14f, .28f}, shoes);
        render::box({-.13f, .48f, 0}, {.18f, .70f, .20f}, pants);
        render::box({ .13f, .48f, 0}, {.18f, .70f, .20f}, pants);
        render::box({0, 1.10f, 0}, {.44f, .65f, .26f}, shirt);
        render::box({0, 1.12f, -.18f}, {.34f, .46f, .15f}, backpack);
        render::box({0, 1.58f, 0}, {.24f, .26f, .24f}, skin);
        render::box({0, 1.74f, 0}, {.26f, .12f, .26f}, hair);
    }
    glPopMatrix();
}
} // anonymous namespace

App& App::instance() { static App app; return app; }

int App::run(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width_, height_);
    glutCreateWindow("Southeast University 3D Campus");
    glEnable(GL_DEPTH_TEST); glEnable(GL_NORMALIZE); glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
    glClearColor(.84f, .87f, .90f, 1.0f);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    const GLfloat overcastSkyColor[4] = {.84f, .87f, .90f, 1.0f};
    glFogfv(GL_FOG_COLOR, overcastSkyColor);
    glFogf(GL_FOG_START, 70.0f);
    glFogf(GL_FOG_END, 140.0f);
    TextureManager::instance().initialize();
    glutDisplayFunc(displayCallback); glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyDownCallback); glutKeyboardUpFunc(keyUpCallback);
    glutSpecialFunc(specialDownCallback); glutSpecialUpFunc(specialUpCallback);
    glutMouseFunc(mouseCallback); glutPassiveMotionFunc(motionCallback); glutMotionFunc(motionCallback);
    lastTimeMs_ = glutGet(GLUT_ELAPSED_TIME); glutTimerFunc(16, timerCallback, 0);
    glutMainLoop(); return EXIT_SUCCESS;
}

void App::update(float dt) {
    if (games_.active()) { games_.update(input_); input_.endFrame(); return; }
    rotationAngle_ += 55.0f * dt;

    if (elevatorNotifyTimer_ > 0.0f) {
        elevatorNotifyTimer_ = std::max(0.0f, elevatorNotifyTimer_ - dt);
        if (elevatorNotifyTimer_ == 0.0f) elevatorNotification_.clear();
    }

    if (input_.pressed(27)) { std::exit(EXIT_SUCCESS); }
    if (input_.pressed('g')) debug_ = !debug_;
    if (input_.pressed('n')) nightMode_ = !nightMode_;
    if (input_.pressed('t')) demo_ = !demo_;
    if (input_.pressed('v')) { topDown_ = !topDown_; panorama_ = false; facadeView_ = false; }
    if (input_.pressed('l')) labels_ = !labels_;
    if (input_.pressed('o')) { panorama_ = !panorama_; facadeView_ = false; topDown_ = false; }
    if (input_.pressed('f')) { facadeView_ = !facadeView_; panorama_ = false; topDown_ = false; }
    if (input_.pressed('\t')) { droneChase_ = !droneChase_; }

    if (input_.pressed('0') && !demo_) {
        player_.reset();
        dronePos_ = {0.0f, 18.0f, -14.0f};
        droneYaw_ = 90.0f;
        dronePitch_ = -16.0f;
    }

    // Elevator floor transformation buttons: 1, 2, 3, 4
    if (!demo_) {
        if (input_.pressed('1')) handleElevator(1);
        else if (input_.pressed('2')) handleElevator(2);
        else if (input_.pressed('3')) handleElevator(3);
        else if (input_.pressed('4')) handleElevator(4);
    }

    if (input_.pressed('m')) {
        mouseCaptured_ = !mouseCaptured_;
        glutSetCursor(mouseCaptured_ ? GLUT_CURSOR_NONE : GLUT_CURSOR_INHERIT);
        if (mouseCaptured_) { ignoreMouseWarp_ = true; glutWarpPointer(width_ / 2, height_ / 2); }
    }

    const float speed = (input_.held(16) ? config::fastCameraSpeed : config::cameraSpeed) * dt;
    if (demo_) {
        if (input_.specialHeld(GLUT_KEY_LEFT)) demoPosition_.x -= speed;
        if (input_.specialHeld(GLUT_KEY_RIGHT)) demoPosition_.x += speed;
        if (input_.specialHeld(GLUT_KEY_UP)) demoPosition_.z += speed;
        if (input_.specialHeld(GLUT_KEY_DOWN)) demoPosition_.z -= speed;
        if (input_.held('q')) demoAngle_ += 75 * dt;
        if (input_.held('e')) demoAngle_ -= 75 * dt;
        if (input_.held('+') || input_.held('=')) demoScale_ = std::min(3.0f, demoScale_ + dt);
        if (input_.held('-')) demoScale_ = std::max(.25f, demoScale_ - dt);
    } else if (panorama_) {
        // DRONE MODE: Interactive Flight Controller & Playable Chase Drone
        if (droneChase_) {
            // Playable 3rd-Person Chase Drone: user moves player character
            player_.update(input_, dt, collisionWorld_);
            interaction_.update(input_, player_);
            if (interaction_.gameRequested()) { games_.enter(interaction_.requestedGame()); interaction_.clearGameRequest(); }

            // Chase camera orbit controls
            if (input_.specialHeld(GLUT_KEY_LEFT)) chaseYaw_ -= 65.0f * dt;
            if (input_.specialHeld(GLUT_KEY_RIGHT)) chaseYaw_ += 65.0f * dt;
            if (input_.specialHeld(GLUT_KEY_UP)) chasePitch_ = std::min(45.0f, chasePitch_ + 45.0f * dt);
            if (input_.specialHeld(GLUT_KEY_DOWN)) chasePitch_ = std::max(-75.0f, chasePitch_ - 45.0f * dt);
            if (input_.held('[')) chaseHeight_ = std::max(2.0f, chaseHeight_ - 8.0f * dt);
            if (input_.held(']')) chaseHeight_ = std::min(25.0f, chaseHeight_ + 8.0f * dt);
            if (input_.held('-')) chaseDistance_ = std::min(35.0f, chaseDistance_ + 10.0f * dt);
            if (input_.held('+') || input_.held('=')) chaseDistance_ = std::max(4.0f, chaseDistance_ - 10.0f * dt);
        } else {
            // Free Drone Flight: user directly pilots the drone anywhere in 3D
            const bool turbo = input_.held(16) || input_.held('r');
            const float curSpeed = (turbo ? droneSpeed_ * 2.2f : droneSpeed_) * dt;
            const float radYaw = droneYaw_ * 0.0174532925f;
            const float radPitch = dronePitch_ * 0.0174532925f;

            Vec3 fwd{
                std::cos(radYaw) * std::cos(radPitch),
                std::sin(radPitch),
                std::sin(radYaw) * std::cos(radPitch)
            };
            Vec3 rgt{
                std::cos((droneYaw_ - 90.0f) * 0.0174532925f),
                0.0f,
                std::sin((droneYaw_ - 90.0f) * 0.0174532925f)
            };

            if (input_.held('w')) dronePos_ = dronePos_ + fwd * curSpeed;
            if (input_.held('s')) dronePos_ = dronePos_ - fwd * curSpeed;
            if (input_.held('d')) dronePos_ = dronePos_ + rgt * curSpeed;
            if (input_.held('a')) dronePos_ = dronePos_ - rgt * curSpeed;
            if (input_.held(' ') || input_.held('e')) dronePos_.y += curSpeed;
            if (input_.held('c') || input_.held('q')) dronePos_.y = std::max(1.0f, dronePos_.y - curSpeed);

            if (input_.held('[')) dronePos_.y = std::max(1.0f, dronePos_.y - curSpeed * 1.5f);
            if (input_.held(']')) dronePos_.y = std::min(75.0f, dronePos_.y + curSpeed * 1.5f);

            // Arrow keys rotate camera
            if (input_.specialHeld(GLUT_KEY_LEFT)) droneYaw_ -= 65.0f * dt;
            if (input_.specialHeld(GLUT_KEY_RIGHT)) droneYaw_ += 65.0f * dt;
            if (input_.specialHeld(GLUT_KEY_UP)) dronePitch_ = std::min(85.0f, dronePitch_ + 55.0f * dt);
            if (input_.specialHeld(GLUT_KEY_DOWN)) dronePitch_ = std::max(-85.0f, dronePitch_ - 55.0f * dt);
        }
    } else {
        // Standard First-Person Mode
        player_.update(input_, dt, collisionWorld_);
        interaction_.update(input_, player_, dt);
        if (interaction_.gameRequested()) { games_.enter(interaction_.requestedGame()); interaction_.clearGameRequest(); }
    }
    input_.endFrame();
}

void App::setupLighting() {
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    if (nightMode_) {
        // --- NIGHT MODE: Atmospheric moonlit campus with warm interior glow ---

        // Deep indigo-blue ambient — enough to see silhouettes outdoors
        const GLfloat ambient[] = {.08f, .09f, .16f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

        // Cool silver-blue moonlight from high elevation (directional)
        const GLfloat moon[] = {.18f, .22f, .38f, 1.0f};
        const GLfloat moonSpec[] = {.10f, .14f, .22f, 1.0f};
        const GLfloat moonDir[] = {-0.3f, 2.0f, -0.5f, 0};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, moon);
        glLightfv(GL_LIGHT0, GL_SPECULAR, moonSpec);
        glLightfv(GL_LIGHT0, GL_POSITION, moonDir);

        // Primary warm interior light — lobby/atrium central ceiling chandelier
        const GLfloat lobbyWarm[] = {1.40f, 1.08f, .72f, 1.0f};
        const GLfloat lobbySpec[] = {.90f, .70f, .45f, 1.0f};
        const GLfloat lobbyPos[] = {0, 7.0f, 21, 1};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lobbyWarm);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lobbySpec);
        glLightfv(GL_LIGHT1, GL_POSITION, lobbyPos);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.4f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.012f);

        // Secondary warm light — cafeteria/dining area overhead
        const GLfloat cafeWarm[] = {1.25f, .92f, .62f, 1.0f};
        const GLfloat cafeSpec[] = {.70f, .55f, .35f, 1.0f};
        const GLfloat cafePos[] = {-3.0f, 5.5f, 35, 1};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, cafeWarm);
        glLightfv(GL_LIGHT2, GL_SPECULAR, cafeSpec);
        glLightfv(GL_LIGHT2, GL_POSITION, cafePos);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.5f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.015f);

        // Tertiary corridor accent light — gaming room / hallway warm spill
        const GLfloat hallWarm[] = {1.0f, .82f, .58f, 1.0f};
        const GLfloat hallPos[] = {8.0f, 4.5f, 13, 1};
        glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, hallWarm);
        glLightfv(GL_LIGHT3, GL_SPECULAR, hallWarm);
        glLightfv(GL_LIGHT3, GL_POSITION, hallPos);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.6f);
        glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.02f);
    } else {
        // --- DAY MODE: Bright, crisp sunlit campus ---

        // Warm ambient fill — soft sky contribution
        const GLfloat ambient[] = {.48f, .50f, .56f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

        // Primary sun: warm golden-white from high angle
        const GLfloat sun[] = {.92f, .90f, .82f, 1.0f};
        const GLfloat sunSpec[] = {.95f, .92f, .85f, 1.0f};
        const GLfloat sunDir[] = {-0.5f, 2.0f, -0.7f, 0};
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sun);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpec);
        glLightfv(GL_LIGHT0, GL_POSITION, sunDir);

        // Secondary fill light — sky bounce from opposite angle
        const GLfloat sky[] = {.42f, .48f, .60f, 1.0f};
        const GLfloat skyDir[] = {0.6f, 1.2f, 0.8f, 0};
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, sky);
        glLightfv(GL_LIGHT1, GL_SPECULAR, sky);
        glLightfv(GL_LIGHT1, GL_POSITION, skyDir);

        // Interior fill light — warm overhead in lobby
        const GLfloat interior[] = {.72f, .60f, .42f, 1.0f};
        const GLfloat intPos[] = {0, 6.0f, 20, 1};
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, interior);
        glLightfv(GL_LIGHT2, GL_SPECULAR, interior);
        glLightfv(GL_LIGHT2, GL_POSITION, intPos);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.6f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01f);

        glDisable(GL_LIGHT3);
    }
}

void App::display() {
    if (nightMode_) {
        glClearColor(.02f, .02f, .06f, 1.0f);
        const GLfloat nightFog[4] = {.02f, .02f, .06f, 1.0f};
        glFogfv(GL_FOG_COLOR, nightFog);
        glFogf(GL_FOG_START, 35.0f);
        glFogf(GL_FOG_END, 100.0f);
    } else {
        glClearColor(.78f, .85f, .94f, 1.0f);
        const GLfloat daySky[4] = {.78f, .85f, .94f, 1.0f};
        glFogfv(GL_FOG_COLOR, daySky);
        glFogf(GL_FOG_START, 75.0f);
        glFogf(GL_FOG_END, 150.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();

    if (facadeView_) {
        gluLookAt(0, 7.0f, -31.0f, 0, 5.5f, 9.0f, 0, 1, 0);
    } else if (panorama_) {
        if (droneChase_) {
            const Vec3 tgt = player_.eyePosition();
            const float ry = chaseYaw_ * 0.0174532925f;
            const float rp = chasePitch_ * 0.0174532925f;
            const Vec3 camPos = tgt + Vec3{
                -std::cos(ry) * std::cos(rp) * chaseDistance_,
                chaseHeight_ - std::sin(rp) * chaseDistance_,
                -std::sin(ry) * std::cos(rp) * chaseDistance_
            };
            gluLookAt(-camPos.x, camPos.y, camPos.z, -tgt.x, tgt.y, tgt.z, 0, 1, 0);
        } else {
            const float ry = droneYaw_ * 0.0174532925f;
            const float rp = dronePitch_ * 0.0174532925f;
            const Vec3 fwd{
                std::cos(ry) * std::cos(rp),
                std::sin(rp),
                std::sin(ry) * std::cos(rp)
            };
            const Vec3 tgt = dronePos_ + fwd;
            gluLookAt(-dronePos_.x, dronePos_.y, dronePos_.z, -tgt.x, tgt.y, tgt.z, 0, 1, 0);
        }
    } else if (topDown_) {
        gluLookAt(0, 52, 20, 0, 0, 20, 0, 0, 1);
    } else {
        camera_.position = player_.eyePosition();
        camera_.position.x = -camera_.position.x;
        camera_.yaw = 180.0f - player_.yaw;
        camera_.pitch = player_.pitch;
        camera_.applyView();
    }

    setupLighting();

    // The plan is authored from above with its right side on +X. A forward
    // first-person view naturally presents that axis reversed on screen, so
    // mirror the complete rendered world once at the view boundary.
    glPushMatrix();
    glDisable(GL_CULL_FACE);
    glScalef(-1, 1, 1);

    campus::renderScene(labels_, debug_, !topDown_);

    // Render 3D player avatar when viewing from drone or external camera
    if (panorama_ || facadeView_ || topDown_) {
        drawPlayerAvatar(player_.position, player_.yaw, player_.seated);
    }

    glPushMatrix(); glTranslatef(-7, 3.2f, 34); glRotatef(rotationAngle_, 0, 1, 0);
    render::box({0,0,0},{3.0f,.08f,.22f},{.9f,.75f,.18f}); render::box({0,0,0},{.22f,.08f,3.0f},{.9f,.75f,.18f}); glPopMatrix();

    if (debug_) { render::grid(24, 2); render::axes(3); }
    if (debug_) collisionWorld_.debugDraw();

    glPushMatrix(); glTranslatef(demoPosition_.x, demoPosition_.y, demoPosition_.z); glRotatef(demoAngle_, 0, 1, 0); glScalef(demoScale_, demoScale_, demoScale_);
    render::box({0, 0, 0}, {1.3f, 1.3f, 1.3f}, {.88f, .48f, .19f});
    render::cylinder({0, .85f, 0}, .23f, .4f, {.32f, .8f, .92f}); glPopMatrix();

    glEnable(GL_CULL_FACE);
    glPopMatrix();

    // 2D Text Overlay
    glDisable(GL_FOG);
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, width_, height_, 0);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

    if (demo_) {
        render::text2d(16, 28, "TRANSFORM: arrows move, Q/E rotate, +/- scale, T exit", {1, 1, 1});
    } else if (panorama_) {
        if (droneChase_) {
            render::text2d(16, 28, "DRONE CHASE [PLAYABLE]: WASD move | Space jump | 1-4 lift | Shift run | E interact | Mouse orbit | [/] height | TAB fly | O exit", {1, 1, 1});
        } else {
            render::text2d(16, 28, "DRONE FREE FLIGHT: WASD fly | E/Space up | Q/C down | 1-4 floors | Shift turbo | Mouse look | [/] height | TAB chase | O exit", {1, 1, 1});
        }
        char telemetry[160];
        const float dAlt = droneChase_ ? (player_.position.y + chaseHeight_) : dronePos_.y;
        const float dx = droneChase_ ? player_.position.x : dronePos_.x;
        const float dy = droneChase_ ? player_.position.y : dronePos_.y;
        const float dz = droneChase_ ? player_.position.z : dronePos_.z;
        const float dYaw = droneChase_ ? chaseYaw_ : droneYaw_;
        const float dPitch = droneChase_ ? chasePitch_ : dronePitch_;
        std::snprintf(telemetry, sizeof(telemetry), "DRONE ALT: %.1fm | POS: (%.1f, %.1f, %.1f) | CAM: Yaw %.0f Pitch %.0f | PLAYER: %s",
            dAlt, dx, dy, dz, dYaw, dPitch, player_.stateName());
        render::text2d(16, 52, telemetry, {.25f, .92f, 1.0f});
        render::text2d(16, 28, "WASD move | R/Shift run | Space jump | 1-4 lift floors | N Day/Night | 0 reset | F facade | O drone | V top | L labels | G bounds", {1, 1, 1});
        char statusText[128];
        std::snprintf(statusText, sizeof(statusText), "%s | TIME: %s",
            player_.stateName(),
            nightMode_ ? "NIGHT [CAMPUS LIGHTS ON]" : "DAY [SUNLIGHT]");
        render::text2d(16, 52, statusText, nightMode_ ? render::Color{.35f, .85f, 1.0f} : render::Color{1, .85f, .25f});
    }

    int hudY = 76;
    const bool nearLift = inLiftArea(player_.position);
    if (!demo_ && nearLift) {
        render::text2d(16, hudY, "[ELEVATOR LIFT] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)", {.20f, .96f, .45f});
        hudY += 24;
    }
    if (elevatorNotifyTimer_ > 0.0f && !elevatorNotification_.empty()) {
        render::text2d(16, hudY, elevatorNotification_.c_str(), {.12f, .88f, 1.0f});
        hudY += 24;
    }
    if (!demo_ && interaction_.prompt()[0] != '\0') {
        render::text2d(16, hudY, interaction_.prompt(), {1, 1, 1});
        hudY += 24;
    }
    if (!demo_ && interaction_.hasNotification()) {
        render::text2d(16, hudY, interaction_.notification(), {.25f, .92f, 1.0f});
        hudY += 24;
    }

    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW);
    if (games_.active()) games_.render(width_, height_);
    glEnable(GL_FOG);
    glutSwapBuffers();
}

void App::reshape(int width, int height) {
    width_ = std::max(1, width); height_ = std::max(1, height); glViewport(0, 0, width_, height_);
    glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(config::fov, static_cast<double>(width_) / height_, config::nearPlane, config::farPlane); glMatrixMode(GL_MODELVIEW);
}

void App::mouseMove(int x, int y) {
    if (!mouseCaptured_ || demo_) return;
    const int cx = width_ / 2, cy = height_ / 2;
    if (ignoreMouseWarp_) { ignoreMouseWarp_ = false; return; }
    if (x == cx && y == cy) return;

    const float dx = -(x - cx) * config::mouseSensitivity;
    const float dy = (y - cy) * config::mouseSensitivity;

    if (panorama_) {
        if (droneChase_) {
            chaseYaw_ += dx;
            chasePitch_ = std::max(-75.0f, std::min(45.0f, chasePitch_ - dy));
        } else {
            droneYaw_ += dx;
            dronePitch_ = std::max(-85.0f, std::min(85.0f, dronePitch_ - dy));
        }
    } else {
        player_.look(dx, dy);
    }

    ignoreMouseWarp_ = true;
    glutWarpPointer(cx, cy);
}

void App::displayCallback() { instance().display(); }
void App::reshapeCallback(int w, int h) { instance().reshape(w, h); }
void App::timerCallback(int) {
    App& app = instance();
    const int now = glutGet(GLUT_ELAPSED_TIME);
    const float dt = std::min(config::maxFrameStep, std::max(0, now - app.lastTimeMs_) * .001f);
    app.lastTimeMs_ = now;
    app.update(dt);
    glutPostRedisplay();
    glutTimerFunc(16, timerCallback, 0);
}
void App::keyDownCallback(unsigned char k, int, int) { instance().input_.keyDown(k); }
void App::keyUpCallback(unsigned char k, int, int) { instance().input_.keyUp(k); }
void App::specialDownCallback(int k, int, int) { instance().input_.specialDown(k); }
void App::specialUpCallback(int k, int, int) { instance().input_.specialUp(k); }
void App::mouseCallback(int button, int state, int, int) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !instance().mouseCaptured_) {
        instance().mouseCaptured_ = true;
        glutSetCursor(GLUT_CURSOR_NONE);
        instance().ignoreMouseWarp_ = true;
        glutWarpPointer(instance().width_ / 2, instance().height_ / 2);
    }
}
void App::motionCallback(int x, int y) { instance().mouseMove(x, y); }

bool App::inLiftArea(const Vec3& pos) const {
    const bool inWestLift = (pos.x >= -20.5f && pos.x <= -10.5f && pos.z >= 21.5f && pos.z <= 27.5f);
    const bool inEastLift = (pos.x >= 4.5f && pos.x <= 13.0f && pos.z >= 21.5f && pos.z <= 27.5f);
    return inWestLift || inEastLift;
}

void App::handleElevator(int floor) {
    if (floor < 1 || floor > 4) return;

    float targetY = 1.2f;
    const char* floorTitle = "FLOOR 1: GROUND LOBBY & GAMING SUITE";
    if (floor == 1) {
        targetY = 1.2f;
        floorTitle = "FLOOR 1: GROUND LOBBY & GAMING SUITE";
    } else if (floor == 2) {
        targetY = 5.2f;
        floorTitle = "FLOOR 2: ACADEMIC LIBRARY & FACULTY SUITES";
    } else if (floor == 3) {
        targetY = 9.2f;
        floorTitle = "FLOOR 3: GRAND AUDITORIUM & INNOVATION LAB";
    } else if (floor == 4) {
        targetY = 13.2f;
        floorTitle = "FLOOR 4: EXECUTIVE BOARDROOM & SKY TERRACE";
    }

    const bool nearWest = std::abs(player_.position.x - (-15.35f)) <= std::abs(player_.position.x - 8.6f);
    float targetX = nearWest ? -15.35f : 8.6f;
    float targetZ = nearWest ? 24.0f : 24.2f;

    // If player is already within a lift area, preserve their relative X & Z coordinates inside the cabin
    if (inLiftArea(player_.position)) {
        targetX = player_.position.x;
        targetZ = player_.position.z;
    }

    player_.position = {targetX, targetY, targetZ};
    player_.verticalVelocity = 0.0f;
    player_.grounded = true;
    player_.seated = false;
    player_.yaw = 270.0f; // Face outward into the floor lobby (-Z direction)
    player_.pitch = 0.0f;

    // In free drone flight, move drone to view destination floor
    if (panorama_ && !droneChase_) {
        dronePos_ = {targetX, targetY + 3.0f, targetZ - 7.0f};
        droneYaw_ = 90.0f;
        dronePitch_ = -10.0f;
    }

    elevatorNotification_ = std::string("[LIFT ARRIVAL] TRANSFORMED TO ") + floorTitle;
    elevatorNotifyTimer_ = 4.5f;
}
