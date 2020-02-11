//
// Created by tabis on 10/10/2019.
//

#include "BubbleSort.hpp"
#include <gtest/gtest.h>

TEST(BubbleSortTests, bubble_sort)
{
    std::vector<int> vec{1, 0, 32, 4, 4, 5, 2};
    ASSERT_THAT(Algorithm::bubble_sort(vec));
}