#pragma once

#include <iomanip>
#include <cassert>

#include "Column.h"
#include "../Set/Set.h"

template <typename Type>
class TypeColumn : public Column {
public:
	TypeColumn(const String& name, ColumnType type);

	virtual bool hasValue(size_t pos) const override;
	virtual String getValue(size_t pos) const override;

	virtual void addValue(const String& val) override;
	virtual void changeValue(size_t pos, const String& newVal) override;
	virtual void deleteValue(size_t pos) override;

	virtual void printValueAt(size_t pos) const override;
	virtual void printValueAtToStream(size_t pos, std::ostream& os) const override;

	virtual void readFromFile(std::ifstream& ifile) override;
	virtual void writeToFile(std::ofstream& ofile) const override;

	virtual void deleteRecords(const std::vector<size_t>& recordsPositions) override;
	virtual void updateValues(const std::vector<size_t>& recordsPositions, const String& newVal) override;

	virtual void initializeValues(size_t recordsCount) override;
	virtual void deleteRecords() override;

	virtual size_t getSize() const override { return values.size(); }

	void addValueType(const Type& val);
protected:
	std::vector<Type> values;
	Set setValues;

	virtual Type convertFromString(const String& value) const = 0;
	virtual String convertToString(const Type& value) const = 0;
};

template<typename Type>
TypeColumn<Type>::TypeColumn(const String& name, ColumnType type) : Column(name, type, name.size()) {}

template<typename Type>
bool TypeColumn<Type>::hasValue(size_t pos) const
{
	if (pos >= values.size()) {
		throw std::exception("invalid argument");
	}

	return setValues.contains(pos);
}

template<typename Type>
String TypeColumn<Type>::getValue(size_t pos) const
{
	if (pos >= values.size()) {
		throw std::exception("invalid argument");
	}

	return setValues.contains(pos) ? convertToString(values[pos]) : "NULL";
}


template<typename Type>
void TypeColumn<Type>::deleteValue(size_t pos)
{
	if (pos >= values.size()) {
		throw std::exception("invalid argument");
	}

	values.erase(values.begin() + pos);
}

template<typename Type>
void TypeColumn<Type>::addValue(const String& val)
{
	if (val == "NULL") {
		values.push_back(Type());
		setValues.add(true);
	}
	else {
		addValueType(convertFromString(val));
		if (val.size() < 16 && val.size() > width) {
			width = val.size();
		}
	}
}

template<typename Type>
void TypeColumn<Type>::initializeValues(size_t recordsCount)
{
	values.reserve(recordsCount);
	values.resize(recordsCount);

	for (size_t i = 1; i <= recordsCount; i++) {
		setValues.add(true);
	}
}

template<typename Type>
void TypeColumn<Type>::changeValue(size_t pos, const String& newVal)
{
	if (newVal == "NULL") {
		if (setValues.contains(pos)) {
			setValues.flip(pos);
		}
	}
	else {
		values[pos] = convertFromString(newVal);
		if (!setValues.contains(pos)) {
			setValues.flip(pos);
		}
	}
}

template<typename Type>
void TypeColumn<Type>::printValueAt(size_t pos) const
{
	printValueAtToStream(pos, std::cout);
}

template<typename Type>
void TypeColumn<Type>::printValueAtToStream(size_t pos, std::ostream& os) const
{
	os << std::setw(width) << std::left;

	if (setValues.contains(pos)) {
		os << values[pos];
	}
	else {
		os << "NULL";
	}
}

template<typename Type>
void TypeColumn<Type>::readFromFile(std::ifstream& ifile)
{
	assert(ifile.good());
	ifile.read(reinterpret_cast<char*>(&width), sizeof(width));

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));
	values.clear();
	values.reserve(size);
	Type temp;
	bool hasValue;
	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		ifile.read(reinterpret_cast<char*>(&hasValue), sizeof(hasValue));
		if (hasValue) {
			values.push_back(temp);
		}
		else {
			values.push_back(Type());
		}
		setValues.add(!hasValue);
	}
}

template<typename Type>
void TypeColumn<Type>::writeToFile(std::ofstream& ofile) const
{
	assert(ofile.good());
	int type = static_cast<int>(getType());
	ofile.write(reinterpret_cast<const char*>(&type), sizeof(type));
	ofile.write(getName(), MAX_NAME_LENGTH);
	ofile.write(reinterpret_cast<const char*>(&width), sizeof(width));

	size_t size = values.size();
	ofile.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; i++) {
		ofile.write(reinterpret_cast<const char*>(&values[i]), sizeof(values[i]));
		bool flag = setValues.contains(i) ? true : false;
		ofile.write(reinterpret_cast<const char*>(&flag), sizeof(flag));
	}
}

template<typename Type>
void TypeColumn<Type>::deleteRecords(const std::vector<size_t>& recordsPositions)
{
	assert(recordsPositions.size() <= values.size());
	// ptr is pointer to the current index in recordsPositions,
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
			if ((setValues.contains(j) && !setValues.contains(i)) || (!setValues.contains(j) && setValues.contains(i))) {
				setValues.flip(i);
			}
			i++;
		}
	}
	for (; j < values.size(); j++, i++) {
		values[i] = values[j];
		if ((setValues.contains(j) && !setValues.contains(i)) || (!setValues.contains(j) && setValues.contains(i))) {
			setValues.flip(i);
		}
	}

	values.resize(i);
}

template<typename Type>
void TypeColumn<Type>::updateValues(const std::vector<size_t>& recordsPositions, const String& newVal)
{
	for (size_t pos : recordsPositions) {
		assert(pos < values.size());
		changeValue(pos, newVal);
	}
}

template<typename Type>
void TypeColumn<Type>::deleteRecords()
{
	values.clear();
	setValues.clear();
}

template<typename Type>
void TypeColumn<Type>::addValueType(const Type& val)
{
	values.push_back(val);
	setValues.add(false);
}
