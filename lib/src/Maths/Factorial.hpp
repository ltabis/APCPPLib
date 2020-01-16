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
    template<size_t T>
    size_t factorial()
    {
        // Do we need to compute the next number n-1 ?
        if constexpr(T != 1)
            return T * factorial<T - 1>();

        return T;
    }
}