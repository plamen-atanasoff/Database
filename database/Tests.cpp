#include "Tests.h"

#include "Classes/Controller.h"

const char* Tests::FILE_PATH = "tablesInfo.dat";
Controller& Tests::controller = Controller::getInstance();

void Tests::scenario1()
{
	controller.loadDatabase(FILE_PATH);

	createTable3Bigger();
	controller.executeCommand("print");

	controller.closeDatabase();
}

void Tests::test1() {
	controller.loadDatabase(FILE_PATH);
	controller.closeDatabase();
}

void Tests::test2() {
	controller.loadDatabase(FILE_PATH);

	controller.executeCommand("create TestTable");

	controller.executeCommand("addcolumn Col1 int");
	controller.executeCommand("insert 12");

	controller.executeCommand("addcolumn Col2 double");
	controller.executeCommand("insert 34 5.67");

	controller.executeCommand("addcolumn Col3 string");
	controller.executeCommand("insert 56 10.567 Name");

	controller.executeCommand("print");

	controller.closeDatabase();
}

void Tests::test3()
{
	controller.loadDatabase(FILE_PATH);

	createTable1();

	controller.executeCommand("saveas TestTable.dat");

	controller.closeDatabase();

	controller.loadDatabase(FILE_PATH);

	controller.executeCommand("read TestTable.dat");

	controller.executeCommand("print");

	controller.closeDatabase();
}

void Tests::test4()
{
	controller.loadDatabase(FILE_PATH);

	createTable1();

	controller.executeCommand("export TestTable.txt");

	controller.closeDatabase();
}

void Tests::test5()
{
	controller.loadDatabase(FILE_PATH);

	createTable1();

	controller.executeCommand("describe");

	controller.closeDatabase();
}

void Tests::test6()
{
	controller.loadDatabase(FILE_PATH);

	createTable1Bigger();
	controller.executeCommand("addcolumn Col4 string");

	controller.executeCommand("update 3 NULL 4 Other");

	controller.executeCommand("print");

	controller.closeDatabase();
}

void Tests::test7()
{
	controller.loadDatabase(FILE_PATH);

	createTable1Bigger();

	controller.executeCommand("delete 3 NULL");

	controller.executeCommand("print");

	controller.closeDatabase();
}

void Tests::test8()
{
	controller.loadDatabase(FILE_PATH);

	createTable1Bigger();
	controller.executeCommand("saveas TestTableBigger1.dat");
	controller.executeCommand("import TestTableBigger1.dat");
	
	createTable2();
	controller.executeCommand("saveas TestTable2.dat");
	controller.executeCommand("import TestTable2.dat");
	
	createTable3();
	controller.executeCommand("saveas TestTable3.dat");
	controller.executeCommand("import TestTable3.dat");

	controller.executeCommand("showtables");

	controller.closeDatabase();
	controller.loadDatabase(FILE_PATH);
	
	controller.executeCommand("showtables");

	controller.closeDatabase();
}

void Tests::test9()
{
	controller.loadDatabase(FILE_PATH);

	controller.executeCommand("showtables");

	createTable3();
	controller.executeCommand("saveas TestTable3.dat");

	controller.executeCommand("create Temp");

	controller.executeCommand("open TestTable3");
	controller.executeCommand("print");

	controller.executeCommand("addcolumn Weight double");
	controller.executeCommand("insert Stefan Kazakov Svishtov 47 3.69 89.5");

	controller.executeCommand("save");

	controller.closeDatabase();
	controller.loadDatabase(FILE_PATH);

	controller.executeCommand("open TestTable3");
	controller.executeCommand("print");

	controller.closeDatabase();
}


void Tests::test10()
{
	controller.loadDatabase(FILE_PATH);

	createTable1Bigger();
	controller.executeCommand("print");

	controller.executeCommand("select 3 NULL");

	controller.closeDatabase();
}

void Tests::test11()
{
	controller.loadDatabase(FILE_PATH);

	createTable1Bigger();
	controller.executeCommand("print");

	controller.executeCommand("select_onto ResultTable [3, 2, 1, 2] 3 NULL");
	controller.executeCommand("print");

	controller.closeDatabase();
}

void Tests::createTable1()
{
	controller.executeCommand("create TestTable1");
	controller.executeCommand("addcolumn Col1 int");
	controller.executeCommand("insert 12");
	controller.executeCommand("addcolumn Col2 double");
	controller.executeCommand("insert 34 5.67");
	controller.executeCommand("addcolumn Col3 string");
	controller.executeCommand("insert 56 10.567 Name");
}

void Tests::createTable1Bigger()
{
	createTable1();
	controller.executeCommand("insert 89 60.567 NULL");
	controller.executeCommand("insert 45 104.5 Age");
	controller.executeCommand("insert 234 170.567 City");
	controller.executeCommand("insert 101 20.7 NULL");
}

void Tests::createTable2()
{
	controller.executeCommand("create TestTable2");
	controller.executeCommand("addcolumn Name string");
	controller.executeCommand("addcolumn Age int");
	controller.executeCommand("addcolumn Weight double");
	controller.executeCommand("insert Plamen 23 76.5");
	controller.executeCommand("insert Alex 20 82.45");
	controller.executeCommand("insert Geri 21 55.567");
	controller.executeCommand("insert Pesho 33 80");
	controller.executeCommand("insert Tony 77 103.5");
}

void Tests::createTable3()
{
	controller.executeCommand("create TestTable3");
	controller.executeCommand("addcolumn FirstName string");
	controller.executeCommand("addcolumn LastName string");
	controller.executeCommand("addcolumn City string");
	controller.executeCommand("addcolumn Age int");
	controller.executeCommand("addcolumn Grade double");

	controller.executeCommand("insert Peter Brown Sofia 33 5.58");
	controller.executeCommand("insert Alex Dimitrov Burgas 27 4.58");
	controller.executeCommand("insert Someone Else Silistra 45 3.23");
	controller.executeCommand("insert Petq Georgieva Pleven 17 6");
	controller.executeCommand("insert Stoqn Petkov Plovdiv 99 5.45");
}

void Tests::createTable3Bigger() {
	createTable3();

	controller.executeCommand("insert John Smith NewYork 24 3.5");
	controller.executeCommand("insert Jane Doe LosAngeles 22 4.0");
	controller.executeCommand("insert Michael Johnson Chicago 30 2.8");
	controller.executeCommand("insert Emily Brown Houston 28 3.7");
	controller.executeCommand("insert David Jones Phoenix 21 4.2");
	controller.executeCommand("insert Sarah Garcia Philadelphia 26 3.9");
	controller.executeCommand("insert Robert Miller SanAntonio 23 4.5");
	controller.executeCommand("insert Jessica Davis SanDiego 29 3.3");
	controller.executeCommand("insert Daniel Martinez Dallas 25 3.8");
	controller.executeCommand("insert Laura Rodriguez SanJose 27 4.1");
	controller.executeCommand("insert James Wilson Austin 31 2.9");
	controller.executeCommand("insert Linda Martinez Jacksonville 32 4.6");
	controller.executeCommand("insert Thomas Anderson SanFrancisco 22 3.2");
	controller.executeCommand("insert Barbara Thomas Columbus 24 4.0");
	controller.executeCommand("insert Paul Hernandez FortWorth 26 3.4");
	controller.executeCommand("insert Nancy Lopez Charlotte 28 3.6");
	controller.executeCommand("insert Mark Harris Detroit 30 3.1");
	controller.executeCommand("insert Lisa Clark ElPaso 21 4.3");
	controller.executeCommand("insert Steven Lewis Denver 27 3.5");
	controller.executeCommand("insert Karen Walker Seattle 25 3.7");
	controller.executeCommand("insert Kevin Hall Boston 29 4.2");
	controller.executeCommand("insert Mary Allen Washington 32 3.0");
	controller.executeCommand("insert Richard Young Memphis 28 3.8");
	controller.executeCommand("insert Patricia King Nashville 24 4.1");
	controller.executeCommand("insert Christopher Wright Portland 26 3.9");
}