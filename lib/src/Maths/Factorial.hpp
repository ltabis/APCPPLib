//
// Created by tabis on 09/10/2019.
//

#pragma once

#include <cstddef>

/// \namespace Maths.
/// \brief math namespace.
namespace Maths
{
    /// \brief Compute the factorial of an operand.
    /// \return the factorial of the operand.
    template<size_t N>
    struct Factorial
    {
        enum {Value = N * Factorial<N - 1>::Value};
    };

    /// \brief Stop compilation-time factorial computing.
    /// \return always one.
    template<>
    struct Factorial<1>
    {
        enum {Value = 1};
    };

    /// \brief Compute the factorial of an operand.
    /// \return the factorial of the operand.
    template<size_t T>
    size_t factorial()
    {
        // Do we need to compute the next number n - 1 ?
        if constexpr(T != 1)
            return T * factorial<T - 1>();

        return T;
    }

    /// \brief Compute the factorial of an operand.
    /// \param operand : the number to compute the factorial from.
    /// \return the factorial of the operand.
    template<typename T>
    T factorial(T operand)
    {
        // Do we need to compute the next number operand - 1 ?
        if (operand != 1)
            return operand * factorial<T>(operand - 1);

        return operand;
    }
}