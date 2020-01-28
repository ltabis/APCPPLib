//
// Created by tabis on 28/01/2020.
//

#pragma once

#include <string>
#include <vector>

namespace Utils
{

    /// \brief A function that parses a string separating words.
    /// \param input : the string that we want to parse.
    /// \return A vector of string containing each words.
    std::vector<std::string> stringToWordVector(const std::string &input)
    {
        std::vector<std::string> split;
        std::size_t idx = 0;

        // Skipping first non-word characters.
        for (; !input.empty() && input[idx] <= ' '; ++idx);

        // Getting input arguments.
        for (std::size_t start = idx; input[idx]; ++idx)
        {
            for (; input[idx] > ' '; ++idx);

            // Getting a word.
            auto tmp = input.substr(start, idx - start);

            // Pushing it back to our vector.
            split.push_back(tmp);

            // Skipping non-word characters.
            for (; input[idx] && input[idx] <= ' '; ++idx);
            start = idx--;
        }

        return split;
    }

}