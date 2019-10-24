#include <vector>
#include "Logger.hpp"

int main()
{
    Debug::Logger log;

    log.generateDebugMessage(Debug::INFO, "no errors", "main");
	return 0;
}
