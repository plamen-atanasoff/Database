#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Column/Column.h"
#include "../Column/Columns/IntColumn.h"

using String = std::string;
using ColumnArray = std::vector<Column*>;

class Table
{
public:
	Table() : Table(DEFAULT_NAME) {}
	Table(const char* name);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	void addRecord(const std::vector<String>& values);
	void addColumn(const Column& col);

	void writeToFile(std::ofstream& ofile) const;
	void readFromFile(std::ifstream& ifile);

	void deleteRecords(const std::vector<size_t>& recordsPositions);
	void updateValues(size_t colPos, const std::vector<size_t>& recordsPositions, const String& newVal);

	const char* getName() const;
	size_t getRecordsCount() const;
	const Column* getColumn(size_t pos) const;
	size_t getColumnsSize() const;

	std::vector<String> getRecordValues(size_t recPos, const std::vector<int>& colsPos) const;
private:
	static constexpr int MAX_NAME_LENGTH = 33;
	static constexpr const char* DEFAULT_NAME = "NoName";
	static constexpr const char* INVALID_INDEX_MESSAGE = "invalid index";
	static constexpr const char* INVALID_ARGUMENTS_COUNT_MESSAGE = "invalid arguments count";
	static constexpr const char* IS_EMPTY_MESSAGE = "name cannot be empty";
	static constexpr const char* IS_TOO_LONG_MESSAGE = "name length must be less than ";

	char name[MAX_NAME_LENGTH]{};
	size_t recordsCount = 0;
	ColumnArray cols;

	void copyFrom(const Table& other);
	void free();
};
