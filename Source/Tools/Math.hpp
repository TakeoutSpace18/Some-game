#pragma once
#include "Constants.hpp"

template <typename T>
T toRad(T degrees) {
    return degrees * Constants::pi / 180;
}

template <typename T>
T toDeg(T radians) {
    return (radians * 180) / Constants::pi;
}
