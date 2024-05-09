#include "IntColumn.h"
#include <string>
#include <iostream>

IntColumn::IntColumn(const std::string& name, ColumnType type) : Column(name, type) 
{}

void IntColumn::addValue(const std::string& val)
{
	// add validation
	values.push_back(std::stoi(val));
}

void IntColumn::removeValue(int pos)
{
	// add validation
	values.erase(values.begin() + pos);
}

void IntColumn::changeValue(int pos, const std::string& newVal)
{
	// add validation
	values[pos] = std::stoi(newVal);
}

void IntColumn::printValues() const
{
	for (int i = 0; i < values.size(); i++) {
		std::cout << values[i] << " ";
	}
	std::cout << std::endl;
}

void IntColumn::saveToFile(std::ofstream& ofile) const
{
	// move to base class
	ColumnType type = getType();
	ofile.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofile.write(getName(), MAX_NAME_LENGTH);

	size_t size = values.size();
	ofile.write(reinterpret_cast<const char*>(&size), sizeof(size));
	ofile.write(reinterpret_cast<const char*>(values.data()), sizeof(int) * size);
}

Column* IntColumn::clone() const
{
	return new IntColumn(*this);
}
