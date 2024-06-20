#include <iostream>

#include "Classes/Controller.h"
#include "Tests.h"

// TODO: check if everywhere dynamic memory is deleted!
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <assert.h>
#endif

int main()
{
#if 0
	{
		Tests::scenario1();
	}
#endif
#if 1
	{
		try
		{
			Controller& c = Controller::getInstance();
			c.run();
		}
		catch (std::exception& err)
		{
			std::cout << err.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Catched unknown exception" << std::endl;
		}
	}
#endif
	_CrtDumpMemoryLeaks();
}
