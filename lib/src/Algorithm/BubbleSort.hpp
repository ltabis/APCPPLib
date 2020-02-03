
#pragma once

#include <algorithm>

/// \namespace Algorithm.
/// \brief Algorithm namespace.
namespace Algorithm
{
    namespace
    {
        template<typename T>
        bool is_sorted(const std::vector<T> &data)
        {
            if (!data.size())
                return true;
        
            // Getting the first element.
            T tmp = data.at(0);
        
            // Iterating through the vector
            for (auto &element : data)
            {

                // If the last element is greater than the next, not sorted.
                if (tmp > element)
                    return false;

                tmp = element;
            }
            return true;
        }
    }

    template<typename T>
    void bubble_sort(std::vector<T> &data)
    {
        while (!is_sorted(data))
        {
            for (std::size_t it = 0; it < data.size(); ++it)
            {
                if (it != data.size() - 1 && data[it] > data[it + 1])
                {
                    T tmp = data.at(it);

                    data[it] = data[it + 1];
                    data[it + 1] = tmp;
                }
            }
        }
    }
}