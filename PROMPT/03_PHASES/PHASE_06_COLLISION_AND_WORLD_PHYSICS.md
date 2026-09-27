# PHASE 06 — Collision, Boundaries and Robust Navigation

## Objective
Make the university behave like a physical space.

## Implement
- AABB or suitable simple colliders for walls/solid furniture,
- separate trigger volumes from solid colliders,
- broad-phase organization if collider count is large,
- sliding response along walls,
- prevention of wall tunneling at run speed,
- floors and stair collision,
- bounds to prevent leaving the intended site,
- safe spawn/reset point,
- collider debug view.

## Collision Categories
At minimum:
- WALL
- FLOOR
- STAIR
- FURNITURE_SOLID
- GLASS_SOLID
- INTERACTION_TRIGGER
- GAME_TRIGGER

## Required Tests
- sprint directly into walls,
- move diagonally along corners,
- jump beside walls,
- go up/down Stair 1 repeatedly,
- enter/exit doors,
- walk around tables/chairs,
- test low FPS / large delta safeguards.

## Acceptance Gate
The player cannot normally pass through walls, glass partitions or solid furniture and can still traverse every intended route.
