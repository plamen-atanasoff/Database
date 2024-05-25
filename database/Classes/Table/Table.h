#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Columns/Column.h"

using String = std::string;
using PrimaryKeyColumn = std::vector<unsigned>;
using ColumnArray = std::vector<Column*>;

// name,
// nextRecordId,
// recordsId: size, elements,
// cols: size,
// col: type, name, values: size, elements

// currently primary key can only be one and it must be an unsigned int

class Table
{
public:
	Table() : Table("") {}
	Table(const String& name);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	void addRecord(const std::vector<String>& values);
	void addColumn(const Column& col);

	void writeToFile(std::ofstream& ofile) const;
	void readFromFile(std::ifstream& ifile);

	std::vector<int> getRecordsPositions(size_t colPos, const String& val) const;

	//void deleteRecord(int recordPos);
	void deleteRecords(const std::vector<int>& recordsPositions);

	void updateValues(int colPos, const std::vector<int>& recordsPositions, const String& newVal);

	void printTable() const;
	void printTableToFile(std::ostream& ofile) const;
	void printColumnInfo() const;
	void describeColumns() const;
	void printTableSelect(const std::vector<int>& recordsPositions) const;

	const char* getName() const;
private:
	static constexpr int MAX_NAME_LENGTH = 33;

	char name[MAX_NAME_LENGTH]{};
	unsigned nextRecordId = 0;
	PrimaryKeyColumn recordsId;
	ColumnArray cols;

	unsigned recordsPerPage = 2;

	void copyFrom(const Table& other);
	void free();

	void deleteRecordsFromRecordsId(const std::vector<int>& recordsPositions);
};