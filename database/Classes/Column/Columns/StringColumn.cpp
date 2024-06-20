#include "StringColumn.h"

StringColumn::StringColumn(const String& name) : TypeColumn<String>(name, ColumnType::STRING) {}

Column* StringColumn::clone() const
{
	return new StringColumn(*this);
}

void StringColumn::readFromFile(std::ifstream& ifile)
{
	assert(ifile.good());
	ifile.read(reinterpret_cast<char*>(&width), sizeof(width));

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	values.clear();
	values.reserve(size);
	size_t stringLen;
	String temp;
	bool hasValue;
	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&stringLen), sizeof(stringLen));
		temp.resize(stringLen);
		ifile.read(reinterpret_cast<char*>(&temp[0]), stringLen);
		ifile.read(reinterpret_cast<char*>(&hasValue), sizeof(hasValue));
		if (hasValue) {
			values.push_back(temp);
		}
		else {
			values.push_back(String());
		}
		setValues.add(!hasValue);
	}
}

void StringColumn::writeToFile(std::ofstream& ofile) const
{
	assert(ofile.good());
	int type = static_cast<int>(getType());
	ofile.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofile.write(getName(), MAX_NAME_LENGTH);
	ofile.write(reinterpret_cast<const char*>(&width), sizeof(width));

	size_t size = values.size();
	ofile.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; i++) {
		size_t stringLen = values[i].size();
		ofile.write(reinterpret_cast<const char*>(&stringLen), sizeof(stringLen));
		ofile.write(reinterpret_cast<const char*>(&values[i][0]), stringLen);
		bool flag = setValues.contains(i) ? true : false;
		ofile.write(reinterpret_cast<const char*>(&flag), sizeof(flag));
	}
}

String StringColumn::convertFromString(const String& value) const
{
	return value;
}

String StringColumn::convertToString(const String& value) const
{
	return value;
}

StringColumnCreator::StringColumnCreator() : ColumnCreator(ColumnType::STRING) {}

Column* StringColumnCreator::create(const std::vector<String>& args) const
{
	if (args.size() != 1) {
		throw std::exception("invalid arguments count");
	}

	return new StringColumn(args[0]);
}

Column* StringColumnCreator::create(const String& name) const
{
	return new StringColumn(name);
}

static StringColumnCreator __;
