//
// Created by tabis on 09/10/2019.
//

#include "Vector2.hpp"

template<typename T> Maths::Vector2<T>::Vector2() : _x(0), _y(0), _z(0) {}

template<typename T> Maths::Vector2<T>::Vector2(T value) : _x(value), _y(value), _z(value) {}

template<typename T> Maths::Vector2<T>::Vector2(T x, T y) : _x(x), _y(y), _z(z) {}