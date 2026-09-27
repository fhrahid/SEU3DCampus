# AI ENTRYPOINT

You are working on a C++17 + OpenGL + FreeGLUT project that recreates Southeast University as an interactive 3D campus.

Before writing code:

1. Read `../01_AGENT_INSTRUCTIONS/MASTER_AGENT_PROMPT.md`
2. Read `../01_AGENT_INSTRUCTIONS/AGENT_RULES_AND_CHECKPOINTS.md`
3. Read `../01_AGENT_INSTRUCTIONS/PROJECT_ARCHITECTURE_GUIDE.md`
4. Read `../02_REFERENCE_LOCK/REFERENCE_PRIORITY.md`
5. Read `../04_REQUIREMENTS/COURSE_REQUIREMENTS_MAPPING.md`
6. Read `../04_REQUIREMENTS/FINAL_FEATURE_CHECKLIST.md`

Then execute **only one requested phase** from `../03_PHASES/`.

## Phase Completion Contract

For the current phase:

1. Inspect repo.
2. Inspect `PROJECT_STATUS.md` if present.
3. Read only relevant references.
4. Implement requested work.
5. Build.
6. Fix compile/link/runtime blockers introduced by this phase.
7. Run phase acceptance tests.
8. Update `PROJECT_STATUS.md`.
9. Return a phase report.
10. STOP.

Never self-start the next phase.

## Required Phase Report

```text
PHASE:
STATUS: PASS / PARTIAL / BLOCKED

IMPLEMENTED:
- ...

FILES CHANGED:
- ...

BUILD:
- PASS/FAIL

TESTS:
- ...

ACCEPTANCE GATE:
- requirement: PASS/FAIL

KNOWN ISSUES:
- ...

NEXT SAFE STEP:
- ...
```
