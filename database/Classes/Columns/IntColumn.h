#pragma once

#include <vector>

#include "Column.h"

class IntColumn : public Column {
public:
	IntColumn(const String& name, ColumnType type);

	virtual void addValue(const String& val) override;
	virtual void deleteValue(size_t pos) override;
	virtual void changeValue(size_t pos, const String& newVal) override;

	//virtual void printValues() const override;
	virtual void printValueAt(size_t pos) const override;

	virtual void writeToFile(std::ofstream& ofile) const override;
	virtual void readFromFile(std::ifstream& ifile) override;

	virtual std::vector<int> getRecordsPositions(const String& val) const override;
	virtual void deleteRecords(const std::vector<int>& recordsPositions) override;

	virtual void initializeValues(size_t recordsCount) override;

	virtual Column* clone() const override;
private:
	std::vector<int> values;

	static constexpr int NULL_VALUE = INT_MIN;
};