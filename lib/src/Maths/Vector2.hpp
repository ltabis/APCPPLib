//
// Created by tabis on 09/10/2019.
//

#pragma once

#include <iostream>


/// \namespace Maths
/// \brief math namespace
namespace Maths {

    /// \class Vector2
    /// \brief Vector class that stores two coordinates
    template<typename T>
    struct Vector2 {
        /// \brief Ctor
        /// Construct the Vector2 class
        Vector2() : x(0), y(0) {}
        /// \brief Ctor
        /// Construct the Vector2 class
        /// \param value : value of all fields
        Vector2(T value) : x(value), y(value) {}
        /// \brief Ctor
        /// Construct the Vector2 class
        /// \param xx : x field value
        /// \param yy : y field value
        Vector2(T xx, T yy) : x(xx), y(yy) {}
        /// \brief Dtor
        /// Destroy the Vector2 class
        ~Vector2() = default;

        T x, y;
    };
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Maths::Vector2<T> &vector)
{ 
    os << "2D <" << vector.x << ", " << vector.y << ">"; 
    return os; 
}