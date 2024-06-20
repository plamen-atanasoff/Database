#include <iostream>

#include "Classes/Controller.h"
#include "Tests.h"

namespace {
	constexpr const char* UNKNOWN_EXCEPTION_MESSAGE = "Catched unknown exception";
}

int main()
{
#if 0
	Tests::scenario1();
#endif
#if 1
	try
	{
		Controller& c = Controller::getInstance();
		c.run();
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (...)
	{
		std::cout << UNKNOWN_EXCEPTION_MESSAGE << std::endl;
	}
#endif
}
