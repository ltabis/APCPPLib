/**
 *  @file     lib/src/Algorithm/BubbleSort.hpp
 *  @author   tabis on the 2020-02-14
 *  @date     2020-02-14
 * 
 *  project: APCPPLib
 * 
 */

#pragma once

#include <algorithm>

/// @namespace Algorithm.
/// @brief Algorithm namespace.
namespace Algorithm
{
    // Equivalent to static C functions : invisible to other files.
    namespace
    {
        /** 
         * @brief checks wether the list passed as parameter is in order.
         * @return a bool set to true if the container is sorted, false otherwise.
         * @param data : the list to check.
         */
        template<typename T>
        bool is_sorted(const std::vector<T> &data)
        {
            if (data.empty())
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

    /** 
     * @brief A realy basic bubble sort algorithm sorting a list by ascending order.
     * @param data : the list to sort.
     */
    template<typename T>
    void bubble_sort(std::vector<T> &data)
    {
        while (!is_sorted(data))
        {
            for (std::size_t it = 0; it < data.size(); ++it)
            {
                if (it != data.size() - 1 && data[it] > data[it + 1])
                {
                    // To be replaced by a swap method of some sort.
                    T tmp = data.at(it);

                    data[it] = data[it + 1];
                    data[it + 1] = tmp;
                }
            }
        }
    }

    /** 
     * @brief Sort the list passed as parameter by ascending order using the less std method.
     * @return a bool set to true if the container is sorted, false otherwise.
     * @param data : the list to check.
     */
    template<typename T>
    void less_sort(std::vector<T> &data)
    {
        std::sort(data.begin(), data.end(), std::less<T>());
    }
}