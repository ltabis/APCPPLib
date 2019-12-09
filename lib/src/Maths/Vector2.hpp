//
// Created by tabis on 09/10/2019.
//

#pragma once

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

        /// \brief X getter
        /// \return the value of the x field.
        T x() const;
        /// \brief Y getter
        /// \return the value of the y field.
        T y() const;

        /// \brief X setter
        /// \param value : the new value of the x field.
        void setX(T value);
        /// \brief Y setter
        /// \param value : the new value of the y field.
        void setY(T value);

    private:
        T _x, _y;
    };
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Maths::Vector2<T> &vector)
{ 
    os << "2D <" << vector.x() << ", " << vector.y() << ">"; 
    return os; 
}