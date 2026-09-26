#include "Camera.h"
#include <GL/glu.h>
#include <algorithm>
#include <cmath>
namespace { constexpr float radians = .017453292519943295f; }
Vec3 Camera::forward() const {
    const float y = yaw * radians, p = pitch * radians;
    return {std::cos(p) * std::cos(y), std::sin(p), std::cos(p) * std::sin(y)};
}
Vec3 Camera::right() const {
    const float y = (yaw - 90) * radians;
    return {std::cos(y), 0, std::sin(y)};
}
void Camera::look(float dx, float dy) {
    yaw += dx;
    pitch = std::max(-85.0f, std::min(85.0f, pitch - dy));
}
void Camera::applyView() const {
    const Vec3 target = position + forward();
    gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z, 0, 1, 0);
}
