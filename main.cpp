#include <iostream>
#include "Triangles.hpp"
#include "Tuples.hpp"

int main()
{
	std::tuple<float, float, float> tup(14, 105, 106);

	std::cout << Utils::max_tuple_value(tup) << std::endl;
	return 0;
}