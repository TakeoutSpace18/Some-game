#pragma once

constexpr float PI = 3.14159265f;

template <typename T>
T toRad(T degrees) {
    return degrees * PI / 180;
}

template <typename T>
T toDeg(T radians) {
    return (radians * 180) / PI;
}
