#pragma once

#include "Classes/Controller.h"

class Tests {
public:
	static void test1();
	static void test2();
	static void test3();
	static void test4();
	static void test5();
	static void test6();
	static void test7();
	static void test8();
	static void test9();
private:
	static const char* FILE_PATH;
	static Controller& controller;

	static void createTable1();
	static void createTableBigger1();
	static void createTable2();
	static void createTable3();
};