#include "IntColumn.h"
#include <string>
#include <iostream>
#include <iomanip>

IntColumn::IntColumn(const std::string& name, ColumnType type) : Column(name, type) 
{}

void IntColumn::addValue(const std::string& val)
{
	// add validation
	if (val == "NULL") {
		values.push_back(NULL_VALUE);
	} 
	else {
		values.push_back(std::stoi(val));
	}
}

void IntColumn::removeValue(int pos)
{
	// add validation
	values.erase(values.begin() + pos);
}

void IntColumn::changeValue(int pos, const std::string& newVal)
{
	// add validation
	if (newVal == "NULL") {
		values[pos] = NULL_VALUE;
	}
	else {
		values[pos] = std::stoi(newVal);
	}
}

void IntColumn::printValues() const
{
	for (int i = 0; i < values.size(); i++) {
		if (values[i] == NULL_VALUE) {
			std::cout << "NULL";
		}
		else {
			std::cout << values[i];
		}
		std::cout << " ";
	}
	std::cout << std::endl;
}

void IntColumn::printValueAt(size_t pos) const
{
	std::cout << std::setw(8) << std::left;
	if (values[pos] == NULL_VALUE) {
		std::cout << "NULL";
	}
	else {
		std::cout << values[pos];
	}
}

void IntColumn::writeToFile(std::ofstream& ofile) const
{
	//check if file is valid
	// move to base class
	int type = static_cast<int>(getType());
	ofile.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofile.write(getName(), MAX_NAME_LENGTH);

	size_t size = values.size();
	ofile.write(reinterpret_cast<const char*>(&size), sizeof(size));
	ofile.write(reinterpret_cast<const char*>(values.data()), sizeof(int) * size);
}

void IntColumn::readFromFile(std::ifstream& ifile)
{
	//check if file is valid

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	values.clear();
	values.resize(size);
	ifile.read(reinterpret_cast<char*>(values.data()), sizeof(int) * size);
}

std::vector<int> IntColumn::getRecordsPositions(const std::string& val) const
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

void IntColumn::deleteValue(int valPos)
{
	values.erase(values.begin() + valPos);
}

void IntColumn::deleteRecords(const std::vector<int>& recordsPositions)
{
	// ptr is pointer to the curr record to be removed, i is pointer to the new valid pos, j is pointer to the curr value in values
	size_t i = 0, j = 0;
	for (size_t ptr = 0; ptr < recordsPositions.size(); j++) {
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
