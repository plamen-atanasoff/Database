#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "ColumnType.h"

using String = std::string;

class Column {
public:
	Column(const String& name, ColumnType type, size_t width) : type(type) {
		strcpy_s(this->name, name.c_str());
		if (width <= MAX_COLUMN_WIDTH) {
			this->width = width;
		}
	}
	virtual ~Column() = default;
	virtual Column* clone() const = 0;

	virtual bool hasValue(size_t pos) const = 0;
	virtual String getValue(size_t pos) const = 0;

	virtual void addValue(const String& val) = 0;
	virtual void changeValue(size_t pos, const String& newVal) = 0;
	virtual void deleteValue(size_t pos) = 0;

	virtual void printValueAt(size_t pos) const = 0;
	virtual void printValueAtToStream(size_t pos, std::ostream& ofile) const = 0;

	virtual void writeToFile(std::ofstream& ofile) const = 0;
	virtual void readFromFile(std::ifstream& ifile) = 0;

	virtual void deleteRecords(const std::vector<size_t>& recordsPositions) = 0;
	virtual void updateValues(const std::vector<size_t>& recordsPositions, const String& newVal) = 0;

	virtual void initializeValues(size_t recordsCount) = 0;
	virtual void deleteRecords() = 0;

	ColumnType getType() const { return type; }
	const char* getName() const { return name; }
	size_t getWidth() const { return width; }
	virtual size_t getSize() const = 0;

	static constexpr int MAX_NAME_LENGTH = 33;
	static constexpr int MAX_COLUMN_WIDTH = 16;
protected:
	ColumnType type;
	char name[MAX_NAME_LENGTH]{};
	size_t width = 8;
};

class ColumnCreator {
public:
	ColumnCreator(ColumnType type);
	virtual ~ColumnCreator() = default;

	virtual Column* create(const std::vector<String>&args) const = 0;
	virtual Column* create(const String& name) const = 0;

	ColumnType getColumnType() const;
private:
	ColumnType type;
};