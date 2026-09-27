#pragma once
#include "Camera.h"
namespace render {
struct Color { float r, g, b, a = 1; };
void material(Color diffuse, float specular = .18f, float shininess = 24);
void box(Vec3 center, Vec3 size, Color color);
void texturedBox(Vec3 center, Vec3 size, Color color, int textureType);
void plane(Vec3 center, Vec3 size, Color color);
void cylinder(Vec3 center, float radius, float height, Color color);
void stairs(Vec3 foot, float width, float rise, float depth, int count, Color color);
void glassPanel(Vec3 center, Vec3 size, Color color);
void grid(float halfExtent, float spacing);
void axes(float length);
void text2d(int x, int y, const char* value, Color color);
void text3d(Vec3 at, const char* value, Color color);
}
