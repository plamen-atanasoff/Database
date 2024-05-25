#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> // TODO: ask is it's okay to use <stdlib.h>(to clear console), <iomanip>(to print table columns better),
// <limits>(to mark null for int and double), <sstream>(for splitting strings by ' ' easily) and <cassert>(for asserting certain invariants)

#include "Classes/Controller.h"

// TODO: check if everywhere dynamic memory is deleted!
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <crtdbg.h>
#include <assert.h>
#endif

using String = std::string;

int main()
{
	//size_t count = 3;
	//StringPair p1{"Table1", "table1.dat"};
	//StringPair p2{ "Table2", "table2.dat" };
	//StringPair p3{ "Table3", "table3.dat" };
	//std::ofstream ofile("tablesInfo.dat", std::ios::binary);
	//if (!ofile.is_open()) {
	//	return 1;
	//}
	//ofile.write(reinterpret_cast<const char*>(&count), sizeof(count));
	//ofile.write(reinterpret_cast<const char*>(&p1), sizeof(p1));
	//ofile.write(reinterpret_cast<const char*>(&p2), sizeof(p2));
	//ofile.write(reinterpret_cast<const char*>(&p3), sizeof(p3));
	//
	//ofile.close();
	{
		try
		{
			Controller c;
			String line;

			//c.execute(Command(CommandType::CREATE_TABLE, { "MyTable" }));
			//c.execute(Command(CommandType::ADD_COLUMN, { "Column1", "int"}));
			//c.execute(Command(CommandType::ADD_COLUMN, { "Column2", "int" }));
			//c.execute(Command(CommandType::ADD_RECORD, { "12", "33" }));
			//c.execute(Command(CommandType::ADD_RECORD, { "13", "34" }));
			//c.execute(Command(CommandType::SAVE_TABLE, {}));

			c.execute(Command(CommandType::READ_TABLE, { "MyTable.dat" }));
			c.execute(Command(CommandType::ADD_RECORD, { "11", "11" }));
			c.execute(Command(CommandType::ADD_COLUMN, { "Column3", "int" }));
			c.execute(Command(CommandType::ADD_RECORD, { "1", "2", "3"}));

			while (true)
			{
				std::cout << "Enter command: ";
				std::getline(std::cin, line);
				system("cls");

				if (line == "exit")
					break;

				// add exception for wrong command format in execute()
				try {
					Command command = Command::create(line);
					c.execute(command);
				}
				catch (const std::exception&) {
					std::cout << "Wrong command\n" << std::endl;
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
	
	_CrtDumpMemoryLeaks();
}
