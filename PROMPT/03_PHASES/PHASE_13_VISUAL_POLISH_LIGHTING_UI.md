# PHASE 13 — Lighting, UI and Visual Polish

## Objective
Make the project presentation-ready without destabilizing gameplay.

## Implement
- balanced ambient + directional/point lighting,
- readable interior lighting,
- glass transparency with controlled draw order,
- improved materials,
- clean campus signage,
- interaction prompt UI,
- controls/help overlay,
- game titles/status UI,
- optional simple sky gradient/background,
- subtle shadows only if feasible without heavy complexity,
- optional day-like exterior lighting.

## Avoid
- excessive particle effects,
- huge texture dependencies,
- effects that reduce readability,
- changes to locked room coordinates.

## Acceptance Gate
All major areas remain readable, frame rate is stable, transparency behaves acceptably and UI clearly communicates controls.


## Mandatory Lighting, Materials, Textures and Continuous Rotation

### Two or More Light Sources
Use at least two enabled light sources at the same time.

Recommended implementation:
1. exterior sun/directional-like light,
2. interior point/spot-like light.

If fixed-function OpenGL is used, configure separate `GL_LIGHT0`, `GL_LIGHT1`, etc.

### Material Properties
For important material categories configure:
- ambient,
- diffuse,
- specular,
- shininess.

Create reusable material presets for examples such as:
- concrete,
- painted wall,
- wood,
- metal,
- plastic,
- glass,
- vegetation.

### Textures
Implement reusable texture loading/creation and texture coordinates.
Apply textures to at least several appropriate surfaces, including:
- wood furniture,
- wall/concrete/brick surface,
- floor/tile surface,
- sign/logo/picture or similar surface.

Texture state must not leak onto unrelated objects.

### Continuous Rotating Object
Add at least one continuously rotating scene object.
Preferred example:
- a ceiling fan in an interior room,
or another SEU-appropriate object.

Requirements:
- update angle using `deltaTime`,
- rotation continues while campus state is active,
- object is visually complex enough to demonstrate rotation clearly.

### Acceptance Gate Additions
- at least two lights are visibly active,
- ambient/diffuse/specular material properties are configured,
- textured surfaces are visible,
- rotating object continues smoothly at different frame rates,
- exterior remains visible through the required window/glass element.
