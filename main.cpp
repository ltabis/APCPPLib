#include <iostream>
#include "Logger.hpp"
#include "Breakpoint.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

int main()
{
	Maths::Vector2<float> vector2(9.5f, 105.2f);
	Maths::Vector3<int> vector3(9, 105, 10);

	std::cout << vector2 << std::endl;
	std::cout << vector3 << std::endl;
	return 0;
}
