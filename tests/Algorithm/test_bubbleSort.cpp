//
// Created by tabis on 10/10/2019.
//

#include "BubbleSort.hpp"
#include "gmock/gmock.h"

TEST(BubbleSortTests, bubble_sort)
{
    std::vector<int> vec0;
    std::vector<int> vec1{1, 0, 32, 4, 4, 5, 2};
    std::vector<float> vec2{.02f, 11.100f, 5.59f, .10f, .00001f, .3445f, 11.100f, 411344.12222f};
    std::vector<double> vec3{.02f, 11.100f, 5.59f, .10f, .00001f, .3445f, 11.100f, 411344.12222f};

    // Bubble sorting the vector.
    Algorithm::bubble_sort(vec0);
    Algorithm::bubble_sort(vec1);
    Algorithm::bubble_sort(vec2);
    Algorithm::bubble_sort(vec3);

    ASSERT_THAT(vec0, testing::ElementsAre());
    ASSERT_THAT(vec1, testing::ElementsAre(0, 1, 2, 4, 4, 5, 32));
    ASSERT_THAT(vec2, testing::ElementsAre(.00001f, .02f, .10f, .3445f, 5.59f, 11.100f, 11.100f, 411344.12222f));
    ASSERT_THAT(vec3, testing::ElementsAre(.00001f, .02f, .10f, .3445f, 5.59f, 11.100f, 11.100f, 411344.12222f));
}

TEST(BubbleSortTests, less_sort)
{
    std::vector<int> vec1{1, 0, 32, 4, 4, 5, 2};
    std::vector<float> vec2{.02f, 11.100f, 5.59f, .10f, .00001f, .3445f, 11.100f, 411344.12222f};
    std::vector<double> vec3{.02f, 11.100f, 5.59f, .10f, .00001f, .3445f, 11.100f, 411344.12222f};

    // Bubble sorting vectors.
    Algorithm::less_sort(vec1);
    Algorithm::less_sort(vec2);
    Algorithm::less_sort(vec3);

    ASSERT_THAT(vec1, testing::ElementsAre(0, 1, 2, 4, 4, 5, 32));
    ASSERT_THAT(vec2, testing::ElementsAre(.00001f, .02f, .10f, .3445f, 5.59f, 11.100f, 11.100f, 411344.12222f));
    ASSERT_THAT(vec3, testing::ElementsAre(.00001f, .02f, .10f, .3445f, 5.59f, 11.100f, 11.100f, 411344.12222f));
}