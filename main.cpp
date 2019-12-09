#include <iostream>
#include "Logger.hpp"
#include "Breakpoint.hpp"
#include "Vector2.hpp"

int main()
{
	Maths::Vector2<float> vector(9.5f, 105.2f);

	std::cout << vector << std::endl;
	return 0;
}
