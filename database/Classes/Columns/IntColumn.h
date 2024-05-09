#pragma once
#include "Column.h"
#include <vector>

class IntColumn : public Column {
public:
	IntColumn(const std::string& name, ColumnType type);

	virtual void addValue(const std::string& val) override;
	virtual void removeValue(int pos) override;
	virtual void changeValue(int pos, const std::string& newVal) override;

	virtual void printValues() const override;

	virtual void writeToFile(std::ofstream& ofile) const override;
	virtual void readFromFile(std::ifstream& ifile) override;

	virtual std::vector<int> getRecordsPositions(const std::string& val) const override;
	virtual void deleteValue(int valPos) override;

	virtual Column* clone() const override;
private:
	std::vector<int> values;

	static constexpr int NULL_VALUE = INT_MIN;
};