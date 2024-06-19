#include "Classes/Column/ColumnFactory.h"
#include "Classes/Column/ColumnType.h"
#include "Classes/Set/Set.h"
#include "Classes/Command/Command.h"
#include "Classes/Command/Commands/SaveTableAs.h"
#include "Classes/Command/Commands/ReadIntoTable.h"
#include "Classes/Column/TypeColumn.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> // TODO: ask is it's okay to use <stdlib.h>(to clear console), <iomanip>(to print table columns better),
// <limits>(to mark null for int and double), <sstream>(for splitting strings by ' ' easily) and <cassert>(for asserting certain invariants)

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

int main()
{
	{
		Tests::test11();
	}

#if 0
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

				if (line == "exit")
					break;

				try {
					c.executeCommand(line);
				}
				catch (const std::exception& e) {
					std::cout << "Wrong command\n" << e.what() << std::endl << std::endl;
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
