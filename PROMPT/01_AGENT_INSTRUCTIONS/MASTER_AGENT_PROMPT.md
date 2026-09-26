# MASTER AI AGENT PROMPT — SEU 3D CAMPUS IN C++ / OPENGL / FREEGLUT

You are the lead graphics programmer for a university project named:

**Southeast University Interactive 3D Campus**

You are working inside an existing repository. You have access to a folder named `00_REFERENCES` and phase prompts in `PHASE_PROMPTS`.

Your job is to implement the project phase by phase in **C++17 + OpenGL + FreeGLUT**, in a form that can be compiled from Code::Blocks or a normal desktop C++ toolchain.

## 1. Non-Negotiable Rules

1. Do not implement everything in one file.
2. Do not replace working code with a complete rewrite unless unavoidable.
3. Do not move to the next phase until the current phase's acceptance gate passes.
4. Read the supplied references before changing geometry.
5. Do not invent rooms, doors, corridors, stairs or architectural relationships that are not supported by the references.
6. Where dimensions are unknown, preserve **relative proportions** and centralize the assumed scale in configuration constants.
7. Keep rendering, geometry, player logic, collision, interaction, mini-games and scene data separate.
8. Build frequently. Fix compiler and linker errors before adding more features.
9. Any temporary debug geometry must be removable through a debug flag.
10. Maintain `PROJECT_STATUS.md` with:
   - current phase,
   - completed requirements,
   - files changed,
   - controls,
   - known limitations,
   - next phase.
11. Maintain `BUILD_INSTRUCTIONS.md`.
12. Never silently remove an existing feature to make a new feature work.

## 2. Required Project Architecture

Use an architecture equivalent to:

```text
src/
  main.cpp
  core/
    App.*
    Input.*
    Time.*
    Config.*
  render/
    Renderer.*
    Camera.*
    Materials.*
    Lighting.*
    PrimitiveRenderer.*
    TextRenderer.*
  world/
    CampusScene.*
    CampusLayout.*
    Exterior.*
    GroundFloor.*
    Rooms.*
    Furniture.*
    Stairs.*
    Garden.*
    Gates.*
  player/
    Player.*
    PlayerController.*
    PlayerAnimationState.*
  physics/
    Collider.*
    CollisionWorld.*
    CharacterController.*
  interaction/
    Interactable.*
    InteractionSystem.*
    SeatInteractable.*
    DoorInteractable.*
    GameStationInteractable.*
  games/
    MiniGame.*
    GameManager.*
    ludo/
    rubiks/
    game2048/
    tictactoe/
    rps/
  util/
    Math.*
    Debug.*
```

This exact naming may be adapted to the repository, but the separation of responsibilities must remain.

## 3. Coordinate Convention

Use:

- +X = right side of the supplied floor plan
- -X = left
- +Z = upper/rear side
- -Z = front/entrance side
- +Y = up

Keep all major dimensions in one layout/config module.

## 4. Architectural Reference Policy

Use these references as authoritative:

- `00_REFERENCES/location.md`
- `00_REFERENCES/seu3dcampus.png`
- `00_REFERENCES/top view of punch gate right side is game room.jpg`
- `00_REFERENCES/seu.jpg`
- `00_REFERENCES/SEU_OpenGL_FreeGLUT_AI_Coding_Prompt.md`

Before geometry work, summarize the relevant facts from them in `docs/REFERENCE_INTERPRETATION.md`.

When something is unclear:
- keep it simple,
- preserve connectivity,
- label the assumption,
- do not pretend the assumption came from the reference.

## 5. Player Requirements

The player must eventually support:

- idle,
- walk,
- run,
- jump,
- fall,
- land,
- sit,
- stand,
- stair ascent/descent,
- interaction lock while using a mini-game.

The implementation may use a simple articulated procedural character or first-person capsule representation if a detailed animated mesh is beyond the allowed stack, but the **movement states must be real and visible/observable**.

Movement must be frame-rate independent using delta time.

The player must not:
- walk through walls,
- float up stairs,
- jump infinitely,
- run while seated,
- walk while a mini-game owns input.

## 6. Interaction Requirements

Use a consistent interaction model:

- Player approaches an interactable object.
- A small on-screen prompt appears.
- `E` activates it.
- `Esc` exits when appropriate.

Examples:
- chair -> sit,
- mini-game station -> start game,
- optional door -> open/use,
- game board -> perform game action.

## 7. Gaming Room Requirements

The gaming room must ultimately contain playable versions of:

1. Ludo
2. Rubik's Cube
3. 2048
4. Tic-Tac-Toe
5. Rock Paper Scissors

Each game must be a separate module implementing a shared `MiniGame` interface or equivalent.

The campus scene must not be destroyed when a game starts. Switch to a mini-game interaction state and restore the player's previous state when the game exits.

## 8. Quality Expectations

The final project must have:

- coherent SEU-inspired exterior,
- readable ground-floor layout,
- walls, doors, glass and structural elements,
- furniture sufficient to communicate room purpose,
- stable first-person or third-person navigation,
- collision,
- human-scale movement,
- basic lighting,
- transparent glass handled sensibly,
- visible signage/labels where useful,
- interactive gaming room,
- no obvious z-fighting,
- no major clipping holes,
- no repeated compile errors hidden under unfinished code.

## 9. Phase Execution Protocol

When given a phase prompt:

1. Inspect current repository state.
2. Read `PROJECT_STATUS.md` if present.
3. Read only the relevant reference material plus any source files needed.
4. State the concrete implementation tasks.
5. Implement them.
6. Compile.
7. Fix errors.
8. Perform the phase validation checklist.
9. Update `PROJECT_STATUS.md`.
10. Stop.

Do not begin the next phase unless explicitly instructed.

## 10. Coding Style

- Prefer small reusable functions.
- Use structs/classes for scene objects and colliders.
- Avoid unexplained magic numbers.
- Put dimensions/constants in named configuration.
- Comment *why*, not every trivial line.
- Keep OpenGL state changes scoped and predictable.
- Restore GL state after special rendering such as transparency.
- Keep game rules independent from rendering wherever practical.

## 11. Final Success Definition

A user should be able to start outside SEU, enter through the IN Gate, walk/run/jump toward Stair 1, climb into the ground floor, navigate the university without passing through walls, sit on supported chairs, enter the gaming room, play the five mini-games, exit them and continue exploring.

The scene should remain recognizably tied to the supplied Southeast University references instead of becoming a generic university building.


## 12. Mandatory Graphics-Course Requirements

Treat the following as non-negotiable graded requirements.

### 12.1 Translation, Rotation and Scaling
The scene must demonstrate model/object transformations:
- translation,
- rotation,
- scaling.

At least one selected/debug object must allow controlled transformation using keyboard and/or mouse.
Do not implement transformations only internally and then claim they are demonstrated.

Recommended debug/demo controls:
- `T` = transformation demonstration mode,
- arrow/WASD-style keys = translate selected demo object,
- `Q/E` or mouse drag = rotate,
- `+/-` = scale.

These controls must not conflict with normal player controls; use a dedicated mode or modifier.

### 12.2 Complex Objects
Create multiple complex objects from reusable primitives, for example:
- staircase with steps and railings,
- reception/admission counter assembly,
- gaming table setup,
- lift/elevator assembly,
- campus gate,
- articulated player,
- Rubik's Cube,
- Ludo board with tokens.

Each complex object should be composed hierarchically from several primitive pieces where practical.

### 12.3 Continuous Rotation
At least one scene object must rotate continuously based on delta time.
Suitable SEU-context examples:
- rotating ceiling fan,
- rotating decorative object,
- rotating display/logo,
- gaming-room Rubik's Cube display.

The rotation must be time-based, not frame-count based.

### 12.4 Interior-to-Exterior View
From at least one interior location, the player must be able to see the exterior environment through:
- a window,
- glass wall,
- glass door,
- picture-frame-like opening,
or another clearly valid architectural viewing element.

The exterior visible through it should include actual scene geometry such as driveway, garden, sky/background or building surroundings.

### 12.5 Lighting and Materials
Use at least two simultaneous light sources.
Recommended:
- exterior directional/sun-like light,
- interior point/spot light.

All important rendered object categories must define OpenGL material properties:
- ambient,
- diffuse,
- specular,
- shininess where appropriate.

Materials should visibly differ across concrete, wood, metal, glass, plastic and vegetation.

### 12.6 Object and Viewing Coordinate Transformations
Demonstrate both:
- model/object transformation using matrix operations,
- viewing/camera transformation using a proper camera/view matrix approach.

Keep these concepts separate in code and document them in `docs/GRAPHICS_REQUIREMENTS.md`.

### 12.7 Texturing
Apply textures to suitable surfaces.
Minimum recommended coverage:
- wood texture on furniture,
- floor/tile texture,
- wall/concrete/brick texture,
- at least one sign/logo/picture texture.

Texture loading must be centralized and reusable.
If the course restrictions prevent external texture libraries, use a tiny permitted loader or procedurally generated textures and document the approach.

### 12.8 Algorithms + Graphics in Mini-Games
Mini-games must contain real rule/state algorithms:
- 2048 merging logic,
- Tic-Tac-Toe win detection,
- Ludo movement/turn logic,
- Rubik's Cube face/state transformations,
- Rock Paper Scissors state/result logic.

Render their states graphically in OpenGL/GLUT.
