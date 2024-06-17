#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Column/Column.h"
#include "../Column/Columns/IntColumn.h"

using String = std::string;
using PrimaryKeyColumn = std::vector<unsigned>;
using ColumnArray = std::vector<Column*>;

// name,
// nextRecordId,
// recordsId: size, elements,
// cols: size,
// col: type, name, values: size, elements

class Table
{
public:
	Table() : Table(DEFAULT_NAME) {}
	Table(const String& name);
	Table(const Table& other);
	Table& operator=(const Table& other);
	~Table();

	void addRecord(const std::vector<String>& values);
	void addColumn(const Column& col);

	void writeToFile(std::ofstream& ofile) const;
	void readFromFile(std::ifstream& ifile);

	void deleteRecords(const std::vector<size_t>& recordsPositions);
	void updateValues(int colPos, const std::vector<size_t>& recordsPositions, const String& newVal);

	const char* getName() const;
	const PrimaryKeyColumn& getRecordsId() const;
	const Column* getColumn(size_t pos) const;
	size_t getColumnsSize() const;

	std::vector<String> getRecordValues(size_t recPos, const std::vector<int>& colsPos) const;
private:
	static constexpr int MAX_NAME_LENGTH = 33;
	static constexpr const char* DEFAULT_NAME = "NoName";

	char name[MAX_NAME_LENGTH]{};
	unsigned nextRecordId = 0;
	PrimaryKeyColumn recordsId;
	ColumnArray cols;

	void copyFrom(const Table& other);
	void free();

	void deleteRecordsFromRecordsId(const std::vector<size_t>& recordsPositions);
};
