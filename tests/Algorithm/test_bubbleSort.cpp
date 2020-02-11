//
// Created by tabis on 10/10/2019.
//

#include "BubbleSort.hpp"
#include "gmock/gmock.h"

TEST(BubbleSortTests, bubble_sort)
{
    std::vector<int> vec{1, 0, 32, 4, 4, 5, 2};

    // Bubble sorting the vector.
    Algorithm::bubble_sort(vec);

    ASSERT_THAT(vec, testing::ElementsAre(0, 1, 2, 4, 4, 5, 32));
}