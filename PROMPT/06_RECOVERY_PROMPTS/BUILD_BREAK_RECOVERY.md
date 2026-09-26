# Build Break Recovery Prompt

Stop adding features.

Inspect the latest working state and current compile/link errors.
Preserve all previously passing phase requirements.
Make the smallest possible patch to restore a clean build and current phase acceptance criteria.

Do not rewrite unrelated modules.

After fixing:
- compile,
- rerun the current phase tests,
- list exactly what changed,
- stop.
