//
// Created by tabis on 09/10/2019.
//

#pragma once

#include "macro.hpp"

#include <exception>
#include <iostream>

namespace Maths {

    template<typename T>
    class Vector2 {

    public:
        /// \brief Ctor
        /// Construct the Vector2 class
        Vector2();
        /// \brief Ctor
        /// Construct the Vector2 class
        /// \param value : value of all fields
        Vector2(T value);
        /// \brief Ctor
        /// Construct the Vector2 class
        /// \param x : x field value
        /// \param y : y field value
        Vector2(T x, T y);
        /// \brief Dtor
        /// Destroy the Vector2 class
        ~Vector2() = default;

    private:
        T _x, _y;
    };
}