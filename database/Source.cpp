#include <iostream>
#include <string>
#include <stdlib.h>

#include "Classes/Controller.h"
#include "Tests.h"

// TODO: check if everywhere dynamic memory is deleted!
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <assert.h>
#endif

constexpr const char* TABLES_FILE = "tablesInfo.dat";

using String = std::string;

bool commandIsLoad(const String& line) {
	size_t commandEnd = line.find_first_of(' ');
	return line.substr(0, commandEnd) == "load";
}

int main()
{
#if 1
	{
		try
		{
			Controller& c = Controller::getInstance();
			String line;

			while (true)
			{
				std::cout << "Enter command: ";
				std::getline(std::cin, line);
				system("cls");

				if (line == "exit") {
					break;
				}
				else if (commandIsLoad(line)) {
					size_t commandEnd = line.find_first_of(' ');
					String databaseFileName = line.substr(commandEnd + 1);
					c.loadDatabase(databaseFileName);
				}
				else {
					try {
						c.executeCommand(line);
					}
					catch (const std::exception& e) {
						std::cout << "Wrong command\n" << e.what() << std::endl << std::endl;
					}
				}
			}
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
