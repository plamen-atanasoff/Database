#include "IntColumn.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>

IntColumn::IntColumn(const String& name, ColumnType type) : Column(name, type, name.size()) {}

void IntColumn::addValue(const String& val)
{
	if (val == "NULL") {
		values.push_back(NULL_VALUE);
	} 
	else {
		values.push_back(std::stoi(val));
		if (val.size() < 16 && val.size() > width) {
			width = val.size();
		}
	}
}

void IntColumn::deleteValue(size_t pos)
{
	assert(pos < values.size());

	values.erase(values.begin() + pos);
}

void IntColumn::changeValue(size_t pos, const String& newVal)
{
	if (newVal == "NULL") {
		values[pos] = NULL_VALUE;
	}
	else {
		values[pos] = std::stoi(newVal);
	}
}

//void IntColumn::printValues() const
//{
//	for (int i = 0; i < values.size(); i++) {
//		if (values[i] == NULL_VALUE) {
//			std::cout << "NULL";
//		}
//		else {
//			std::cout << values[i];
//		}
//		std::cout << " ";
//	}
//	std::cout << std::endl;
//}

void IntColumn::printValueAt(size_t pos) const
{
	std::cout << std::setw(width) << std::left;

	if (values[pos] == NULL_VALUE) {
		std::cout << "NULL";
	}
	else {
		std::cout << values[pos];
	}
}

void IntColumn::printValueAtToFile(size_t pos, std::ostream& ofile) const
{
	ofile << std::setw(width) << std::left;

	if (values[pos] == NULL_VALUE) {
		ofile << "NULL";
	}
	else {
		ofile << values[pos];
	}
}

void IntColumn::writeToFile(std::ofstream& ofile) const
{
	assert(ofile.good());
	// move to base class
	int type = static_cast<int>(getType());
	ofile.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofile.write(getName(), MAX_NAME_LENGTH);
	ofile.write(reinterpret_cast<const char*>(&width), sizeof(width));

	size_t size = values.size();
	ofile.write(reinterpret_cast<const char*>(&size), sizeof(size));
	ofile.write(reinterpret_cast<const char*>(values.data()), sizeof(int) * size);
}

void IntColumn::readFromFile(std::ifstream& ifile)
{
	assert(ifile.good());
	// move to base class
	ifile.read(reinterpret_cast<char*>(&width), sizeof(width));

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	values.clear();
	values.resize(size);
	ifile.read(reinterpret_cast<char*>(values.data()), sizeof(int) * size);
}

std::vector<int> IntColumn::getRecordsPositions(const String& val) const
{
	std::vector<int> res;
	int v;
	if (val == "NULL") {
		v = NULL_VALUE;
	}
	else {
		v = std::stoi(val);
	}

	for (int i = 0; i < values.size(); i++) {
		if (values[i] == v) {
			res.push_back(i);
		}
	}

	return res;
}

void IntColumn::deleteRecords(const std::vector<int>& recordsPositions)
{
	assert(recordsPositions.size() <= values.size());
	// ptr is pointer to the current record to be removed,
	// i is pointer to the current valid pos,
	// j is pointer to the current value in values
	size_t i = 0, j = 0;
	for (size_t ptr = 0; ptr < recordsPositions.size(); j++) {
		assert(recordsPositions[ptr] < values.size());

		if (recordsPositions[ptr] == j) {
			ptr++;
		}
		else {
			values[i] = values[j];
			i++;
		}
	}
	for (; j < values.size(); j++, i++) {
		values[i] = values[j];
	}

	values.resize(i);
}

void IntColumn::updateValues(const std::vector<int>& recordsPositions, const String& newVal)
{
	// make validations
	for (int pos : recordsPositions) {
		changeValue(pos, newVal);
	}
}

void IntColumn::initializeValues(size_t recordsCount)
{
	values.reserve(recordsCount);
	for (int i = 1; i <= recordsCount; i++) {
		values.push_back(NULL_VALUE);
	}
}

Column* IntColumn::clone() const
{
	return new IntColumn(*this);
}

IntColumnCreator::IntColumnCreator(): ColumnCreator(ColumnType::INT) {}

Column* IntColumnCreator::create(const std::vector<String>& args) const
{
	return new IntColumn(args[0], getColumnTypeAsEnum(args[1]));
}

Column* IntColumnCreator::create(const String& name, ColumnType type) const
{
	return new IntColumn(name, type);
}

static IntColumnCreator __;