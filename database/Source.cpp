#include "Classes/Column/ColumnFactory.h"
#include "Classes/Column/ColumnType.h"
#include "Classes/Set/Set.h"
#include "Classes/Command/Command.h"
#include "Classes/Command/Commands/SaveTableAs.h"
#include "Classes/Command/Commands/ReadIntoTable.h"

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

int main() {
#if 0
	Table t;
	Column* col1 = ColumnFactory::getFactory().createColumn("Col1", ColumnType::INT);
	Column* col2 = ColumnFactory::getFactory().createColumn("Col2", ColumnType::INT);
	Column* col3 = ColumnFactory::getFactory().createColumn("Col3", ColumnType::INT);
	t.addColumn(*col1);
	t.addColumn(*col2);

	t.addRecord({ "1", "2" });
	t.addRecord({ "3", "4" });

	t.addColumn(*col3);
	t.addRecord({ "5", "6", "7" });

	Command* c1 = new SaveTableAs("testTable.dat", &t);
	c1->execute();

	delete col1;
	delete col2;
	delete col3;
	delete c1;
#endif
#if 0
	Table t;

	Command* c1 = new ReadIntoTable("testTable.dat", &t);
	c1->execute();

	t.printTable();

	delete c1;
#endif
}

#if 0
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
	//ofile.close();
	{
		try
		{
			Controller c;
			String line;

			//c.execute(Command(CommandType::CREATE_TABLE, { "test1" }));
			//c.execute(Command(CommandType::ADD_COLUMN, { "Column1", "int"}));
			//c.execute(Command(CommandType::ADD_COLUMN, { "Column2", "int" }));
			//c.execute(Command(CommandType::ADD_RECORD, { "12", "33" }));
			//c.execute(Command(CommandType::ADD_RECORD, { "13", "34" }));
			//c.execute(Command(CommandType::SAVE_TABLE, {}));

			//c.execute(Command(CommandType::READ_TABLE, { "test1.dat" }));
			//c.execute(Command(CommandType::ADD_RECORD, { "11", "11" }));
			//c.execute(Command(CommandType::ADD_COLUMN, { "Column3", "int" }));
			//c.execute(Command(CommandType::ADD_RECORD, { "1", "2", "3"}));

			//c.executeCommand("read newT.dat");
			//c.executeCommand("insert 12 44");
			//c.executeCommand("insert 12 45");
			//c.executeCommand("insert 4 33");
			//c.executeCommand("insert 12 46");

			//c.executeCommand("select_onto resTable [2, 1, 1] 1 12");

			// test ShowTables
			//c.executeCommand("showtables");

			// test OpenTable
			//c.executeCommand("open ");

			// test ImportTable
			//c.executeCommand("import newT.dat");

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
	
	_CrtDumpMemoryLeaks();
}
#endif