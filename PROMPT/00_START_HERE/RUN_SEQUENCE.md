# Exact Copy-Paste Sequence for Your Coding AI

Give the AI agent the following in this order:

1. `01_MASTER_AGENT_PROMPT.md`
2. Tell it: **"Execute PHASE 00 only. Stop after its acceptance gate and phase report."**
3. Give `PHASE_00_REPOSITORY_AUDIT_AND_REFERENCE_LOCK.md`
4. Review its phase report.
5. If PASS, give Phase 01.
6. Continue one phase at a time.
7. Never tell it "finish the entire project now."

## Recovery Prompt if the Agent Starts Breaking Working Code

Paste:

> Stop adding features. Inspect the latest working state and current compile errors. Preserve all previously passing phase requirements. Make the smallest possible patch to restore a clean build and the current phase acceptance criteria. Do not rewrite unrelated modules. After the fix, compile and report exactly what changed.

## Recovery Prompt if Architecture Drifts From the Supplied Plan

Paste:

> Stop visual polishing. Compare the current campus geometry against `00_REFERENCES/location.md` and the supplied top-view image. List every adjacency, room placement, entrance, stair, gate, driveway or garden mismatch. Correct the blockout/layout first without adding unsupported architecture. Keep already-correct modules untouched. Re-run the current phase acceptance gate.

## Recovery Prompt if Player Movement Breaks

Paste:

> Disable unrelated feature work. Inspect player state, delta-time integration, gravity, grounded detection and collision resolution. Reproduce the movement bug using a minimal test route, patch the smallest responsible subsystem, then test walk, run, jump, wall sliding and Stair 1 ascent/descent before continuing.


## Additional Mandatory Course Phase

After `PHASE_13_VISUAL_POLISH_LIGHTING_UI.md`, run:

`PHASE_13A_COURSE_GRAPHICS_REQUIREMENTS_AUDIT.md`

Do not proceed to Phase 14 until every course requirement in its matrix is marked PASS.
