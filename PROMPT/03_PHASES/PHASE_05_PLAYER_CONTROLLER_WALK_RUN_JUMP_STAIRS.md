# PHASE 05 — Real Player Movement: Walk, Run, Jump and Stairs

## Objective
Replace debug free-flight movement with a grounded human-style character controller.

## Required Controls
- W/S = forward/back
- A/D = strafe
- mouse = look
- Shift = run
- Space = jump
- E = interaction key, reserved now for later phases
- R = optional unstuck/reset

## Required States
- Idle
- Walking
- Running
- Jumping
- Falling
- Landing
- Stair movement

## Physics
Implement:
- player radius/capsule approximation,
- eye height,
- gravity,
- grounded test,
- jump only when grounded,
- separate walk/run speed,
- delta-time movement,
- maximum step/stair handling,
- slope/stair-friendly movement,
- floor snapping with safe tolerance.

## Stair 1
Player must smoothly:
- approach from driveway,
- climb Stair 1,
- transition to ground floor,
- walk back down,
- return outside.

No teleporting between exterior and interior.

## Animation / Visual Feedback
If third-person body is used:
- simple procedural leg/arm swing while walking,
- faster cycle while running,
- jump pose,
- idle pose.

If first-person is used:
- subtle camera bob for walk,
- faster but controlled bob for run,
- jump/fall camera motion.
Do not induce motion sickness with extreme bobbing.

## Acceptance Gate
Test at multiple frame rates. Player must walk, run and jump consistently without flying, double-jumping, falling through floors or getting stuck on Stair 1.
