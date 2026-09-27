# Reference Priority and Interpretation Rules

Use files in `../08_ORIGINAL_REFERENCES/`.

## Priority

1. `location.md`
   - room relationships
   - entrance sequence
   - named areas
   - spatial facts

2. Ground-floor / top-view reference image
   - adjacency
   - relative placement
   - circulation
   - left/right orientation

3. SEU exterior image
   - facade character
   - materials
   - glazing
   - massing cues

4. Existing OpenGL/FreeGLUT prompt
   - implementation ideas only
   - never override factual layout information

## Unknown Information

If a dimension, object or architectural fact is not supplied:
- use a simple neutral approximation,
- centralize the assumption in config/layout constants,
- document it as an assumption,
- do not claim it is accurate.

## Coordinates

Use:
- +X = right on plan
- -X = left
- +Z = rear/top of plan
- -Z = front/entrance
- +Y = up
