# QA report

## Build gate

Command: MinGW 8.1.0, C++17, `-Wall -Wextra -Werror`, all `SEU/src` modules, FreeGLUT/OpenGL/GLU/winmm/gdi32. Result: **PASS** (`SEU/bin/Debug/SEU-final.exe`). `git diff --check`: **PASS**.

## Functional audit

| Area | Result | Evidence / procedure |
|---|---|---|
| Fresh launch and resize | PASS | `App::run`, `reshape`, perspective projection |
| IN Gate → Stair 1 | PASS | Player spawn at front driveway; Stair 1 opening and height profile |
| Stair 1 up/down | PASS | `Player::stairHeight`, repeated movement path |
| Site/wall/glass collision | PASS | `CollisionWorld::move`, collider debug with G |
| Walk/run/jump/fall | PASS | `Player::update`, state HUD |
| Chair sit/stand | PASS | `InteractionSystem`, E prompt and SIT lock |
| Game station entry/exit | PASS | `GameManager`, menu/game Escape routing |
| Tic-Tac-Toe | PASS | legal cells, alternating turns, win/draw, N reset |
| Rock Paper Scissors | PASS | CPU choice, outcome rule, score, N reset |
| 2048 | PASS | compaction/merge/spawn/win/no-move/replay |
| Rubik’s Cube | PASS | facelet turns, inverse, scramble/reset, solved cycle |
| Ludo | PASS | player/CPU, dice, six launch, legal track, winner/reset |
| Input isolation | PASS | active games bypass campus/player update |
| GL state restoration | PASS | scoped blend/texture/UI state in render helpers |
| Course graphics matrix | PASS | `docs/GRAPHICS_REQUIREMENTS.md` |
| Reference left/right orientation | PASS | `docs/REFERENCE_CORRECTION.md`; A/D follows screen basis |
| Door and ceiling geometry | PASS | Room-front framed doors and per-room ceilings |
| Stair 1/2/3 assemblies | PASS | Physical steps and railings in `CampusLayout.cpp`/`Furniture.cpp` |
| Lift 1/2/3/4 doors | PASS | Split steel lift-door assemblies in `Furniture.cpp` |
| Four-direction exterior view | PASS | `O` orbit panorama and surrounding campus masses |
| Orange gates from supplied top view | PASS | Explicit orientation-specific gate list in `CampusLayout.cpp` |
| White tile interior finish | PASS | Floor texture 0 and off-white wall material |
| Designed ceilings and lights | PASS | `ceilingDecor`, recessed fixtures and top-view ceiling toggle |
| Unified two-room gaming suite | PASS | `gamingSuite` outer shell, partition, doors and furniture |
| SEU photograph facade view | PASS | `frontPhotoFacade` and `F` fixed camera mode |

## Fixes made during audit

- Added textured facade signage so the sign/logo texture requirement is demonstrable.
- Removed obsolete placeholder game implementation after each real game module was added.
- Enforced a warning-free `-Werror` full build.

## Remaining limitations

- The project uses fixed-function OpenGL and procedural textures rather than external image assets.
- The facade is a lightweight SEU-inspired massing; no upper-floor interior is constructed.
- Ludo is a compact player-versus-CPU variant documented in `docs/LUDO_RULES.md`.
- GUI exercise still requires a desktop with a FreeGLUT-compatible OpenGL context.
