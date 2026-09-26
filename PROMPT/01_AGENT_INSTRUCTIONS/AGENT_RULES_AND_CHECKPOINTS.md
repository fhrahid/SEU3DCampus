# AI Agent Rules and Checkpoints

1. Compile after every meaningful batch of changes.
2. Never proceed with unresolved compiler errors.
3. Preserve known-working controls.
4. Preserve the reference-defined floor plan.
5. Add one system at a time.
6. Use debug toggles for colliders and layout.
7. Record every assumption not explicitly present in the references.
8. Do not claim a feature is complete until it can be exercised in the running program.
9. Mini-game rule logic should be testable independently of rendering where possible.
10. At the end of each phase, update `PROJECT_STATUS.md` and stop.

## Mandatory Phase Report Format

```text
PHASE:
STATUS: PASS / PARTIAL / BLOCKED

IMPLEMENTED:
- ...

FILES CHANGED:
- ...

TESTS RUN:
- ...

KNOWN ISSUES:
- ...

ACCEPTANCE GATE:
- item: PASS/FAIL

NEXT SAFE STEP:
- ...
```
