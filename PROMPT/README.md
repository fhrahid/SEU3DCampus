# SEU 3D GLUT — AI Agent Ready Pack

This pack is structured so a coding AI agent can execute the Southeast University 3D GLUT project safely, one validated phase at a time.

## READ ORDER — DO NOT CHANGE

The AI agent must read these files in this exact order:

1. `00_START_HERE/AI_ENTRYPOINT.md`
2. `01_AGENT_INSTRUCTIONS/MASTER_AGENT_PROMPT.md`
3. `01_AGENT_INSTRUCTIONS/AGENT_RULES_AND_CHECKPOINTS.md`
4. `01_AGENT_INSTRUCTIONS/PROJECT_ARCHITECTURE_GUIDE.md`
5. `02_REFERENCE_LOCK/REFERENCE_PRIORITY.md`
6. `04_REQUIREMENTS/COURSE_REQUIREMENTS_MAPPING.md`
7. `04_REQUIREMENTS/FINAL_FEATURE_CHECKLIST.md`
8. Then execute only the requested file from `03_PHASES/`

## Critical Rule

Never execute multiple implementation phases at once.

For every phase:
- inspect current repo,
- read relevant references,
- implement only that phase,
- compile,
- test,
- update project status,
- report PASS / PARTIAL / BLOCKED,
- stop.

Do not continue automatically.

## Source of Truth

Architectural information must come from:
`08_ORIGINAL_REFERENCES/`

Priority:
1. `location.md`
2. top-view/floor-plan reference image
3. exterior SEU image
4. old coding prompt
5. neutral placeholder if genuinely unknown

Unsupported architectural invention is not allowed.

## Required Final Capabilities

### Campus
- recognizable Southeast University exterior
- gates, garden, driveways, stairs, rooms, lifts, punch gate
- readable ground-floor navigation
- furniture and interior materials

### Player
- walk
- run
- jump
- gravity
- stairs
- collision
- sit / stand
- interact

### Gaming Room
- Ludo
- Rubik's Cube
- 2048
- Tic-Tac-Toe
- Rock Paper Scissors

### Mandatory Graphics Course Requirements
- translation
- rotation
- scaling
- complex objects
- continuous rotating object
- interior-to-exterior viewing element
- 2+ light sources
- ambient/diffuse/specular materials
- object coordinate transforms
- viewing coordinate transforms
- textures
- algorithmic games

## Working Files the Agent Must Maintain

In the actual coding repository, the agent must create/update:

- `PROJECT_STATUS.md`
- `BUILD_INSTRUCTIONS.md`
- `CONTROLS.md`
- `QA_REPORT.md`
- `docs/REFERENCE_INTERPRETATION.md`
- `docs/LAYOUT_COORDINATES.md`
- `docs/GRAPHICS_REQUIREMENTS.md`
- `docs/LUDO_RULES.md`
- `FINAL_DEMO_SCRIPT.md`

Templates are available in `05_PROJECT_DOCS_TEMPLATES/`.

## Do Not

- do not dump the project into one `main.cpp`
- do not rewrite working modules without need
- do not continue with compile errors
- do not mark a feature PASS unless it is demonstrable in the running program
- do not silently invent campus geometry
- do not let mini-game input control the player at the same time
