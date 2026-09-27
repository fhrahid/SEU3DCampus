# Project Architecture Guide

## Why this matters

The campus, player controller and five mini-games are already enough moving parts. Putting all of them in `main.cpp` is not simplicity; it is delayed punishment.

## Suggested Modules

### Core
Own GLUT lifecycle, input, timing and global app state.

### Render
Own camera, projection, materials, lighting, primitives and text.

### World
Own SEU geometry and scene data only.

### Player
Own movement state and player-facing behavior.

### Physics
Own colliders, grounding, stair handling and collision resolution.

### Interaction
Own prompts, activation and seat/game triggers.

### Games
Each mini-game owns its rules and rendering while implementing the same lifecycle:
- enter
- update
- render
- input
- reset
- exit

## Suggested Main Loop

```text
input collection
    -> app state routing
        -> campus/player update OR active mini-game update
    -> collision/interaction
    -> render world
    -> render active UI/game
    -> swap buffers
```

## App States

Recommended:
- CAMPUS
- MINIGAME
- PAUSED

Player states:
- IDLE
- WALK
- RUN
- JUMP
- FALL
- SIT
- INTERACT

Keep app state and player locomotion state separate.


## Graphics Coursework Modules

Add or retain modules equivalent to:

```text
render/
  Transform.*
  Materials.*
  Lighting.*
  TextureManager.*
  PrimitiveRenderer.*

world/
  ComplexObjects.*
  AnimatedObjects.*
```

`Transform` should support model transformations.
`Camera` should own viewing transformations.
`Lighting` should configure at least two sources.
`Materials` should centralize ambient/diffuse/specular/shininess.
`TextureManager` should centralize texture loading/binding.
`AnimatedObjects` should update continuous rotations using delta time.
