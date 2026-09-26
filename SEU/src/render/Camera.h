#pragma once
struct Vec3 {
    float x = 0, y = 0, z = 0;
    Vec3 operator+(Vec3 v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator-(Vec3 v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
};
class Camera {
public:
    Vec3 position{0, 2, -7};
    float yaw = 90, pitch = 0;
    Vec3 forward() const;
    Vec3 right() const;
    void look(float dx, float dy);
    void applyView() const;
};
