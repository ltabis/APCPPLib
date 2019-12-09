//
// Created by tabis on 09/10/2019.
//

#include "Vector2.hpp"

template<typename T> Maths::Vector2<T>::Vector2() : _x(0), _y(0) {}

template<typename T> Maths::Vector2<T>::Vector2(T value) : _x(value), _y(value) {}

template<typename T> Maths::Vector2<T>::Vector2(T x, T y) : _x(x), _y(y) {}

template<typename T> T Maths::Vector2<T>::x() const
{
    return _x;
}

template<typename T> T Maths::Vector2<T>::y() const
{
    return _y;
}

template<typename T> void Maths::Vector2<T>::setX(T value)
{
    _x = value;
}

template<typename T> void Maths::Vector2<T>::setY(T value)
{
    _y = value;
}