#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "../Columns/Column.h"

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
	Table(const std::string& name);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	void addRecord(const std::vector<std::string>& values);
	void addColumn(const Column& col);

	void writeToFile(std::ofstream& ofile) const;
	void readFromFile(std::ifstream& ifile);

	std::vector<int> getRecordsPositions(int colPos, const std::string& val) const;
	//void deleteRecord(int recordPos);
	void deleteRecords(std::vector<int> recordsPositions);
	void deleteRecordsFromRecordsId(std::vector<int> recordsPositions);

	void printTable() const;
	void printColumnInfo() const;

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
};