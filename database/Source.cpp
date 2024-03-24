#include <iostream>
#include <string>
#include <stdlib.h> // TODO: ask is it's okay to use <stdlib.h>(to clear console), <iomanip>(to print table columns better),
// <limits>(to mark null for int and double) and <sstram>(for splitting strings by ' ' easily)

#include "Controller.h"

// TODO: check if everywhere dynamic memory is deleted !
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <assert.h>
#endif

using String = std::string;

int main()
{
	{
		Controller c;
		String line;
		Command command;

		while (true)
		{
			try
			{
				std::cout << "Enter command: ";
				std::getline(std::cin, line);
				system("cls");

				if (line == "exit")
					break;
				
				command = Command::create(line);
				c.execute(command);
			}
			catch (std::exception& err)
			{
				std::cout << err.what() << std::endl;
			}
			catch (...)
			{
				std::cout << "catched unknown exception" << std::endl;
			}
		}
	}
	_CrtDumpMemoryLeaks();
}
