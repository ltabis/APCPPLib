#include <vector>
#include "Exception.hpp"

void func()
{
    throw Log::Exception("Malloc buffer invalid", "func");
}

int main()
{
    try {
        func();
    } catch (Log::Exception &except) {
        except.debugErrorMessage();
    }
	return 0;
}
