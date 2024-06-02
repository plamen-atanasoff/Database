#include "IntColumn.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>

IntColumn::IntColumn(const String& name, ColumnType type) : Column(name, type, name.size()) {}

void IntColumn::addValue(const String& val)
{
	if (val == "NULL") {
		values.push_back(Optional<int>());
	} 
	else {
		values.push_back(Optional<int>(std::stoi(val)));
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
		values[pos] = Optional<int>();
	}
	else {
		values[pos] = Optional<int>(std::stoi(newVal));
	}
}

void IntColumn::printValueAt(size_t pos) const
{
	printValueAtToStream(pos, std::cout);
}

void IntColumn::printValueAtToStream(size_t pos, std::ostream& os) const
{
	os << std::setw(width) << std::left;

	if (values[pos].hasValue()) {
		os << values[pos].getValue();
	}
	else {
		os << "NULL";
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
	//ofile.write(reinterpret_cast<const char*>(values.data()), sizeof(Optional<int>) * size);
	for (size_t i = 0; i < size; i++) {
		ofile.write(reinterpret_cast<const char*>(&values[i].getValue()), sizeof(int));
		bool res = values[i].hasValue();
		ofile.write(reinterpret_cast<const char*>(&res), sizeof(bool));
	}
}

void IntColumn::readFromFile(std::ifstream& ifile)
{
	assert(ifile.good());
	// move to base class
	ifile.read(reinterpret_cast<char*>(&width), sizeof(width));

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	values.clear();
	values.reserve(size);
	//ifile.read(reinterpret_cast<char*>(values.data()), sizeof(Optional<int>) * size);
	int temp;
	bool hasValue;
	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		ifile.read(reinterpret_cast<char*>(&hasValue), sizeof(hasValue));
		if (hasValue) {
			values.push_back({ temp });
		}
		else {
			values.push_back({});
		}
	}
}

std::vector<int> IntColumn::getRecordsPositions(const String& val) const
{
	std::vector<int> res;
	Optional<int> v;
	if (val != "NULL") {
		v.setValue(std::stoi(val));
	}

	for (int i = 0; i < values.size(); i++) {
		if (values[i].hasValue() && values[i].getValue() == v.getValue()) {
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
		values.push_back(Optional<int>());
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