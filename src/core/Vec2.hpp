#pragma once
#include <cmath>
#include <ostream>

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2() = default;
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    Vec2 operator/(float s) const { return {x / s, y / s}; }

    float length() const { return std::sqrt(x*x + y*y); }
    Vec2 normalized() const { float l = length(); return l > 0 ? (*this)/l : Vec2(); }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    return os << "(" << v.x << "," << v.y << ")";
}
