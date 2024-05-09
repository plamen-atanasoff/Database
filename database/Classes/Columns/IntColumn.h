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

	virtual void saveToFile(std::ofstream& ofile) const override;
	virtual Column* clone() const override;
private:
	std::vector<int> values;

	static constexpr int NULL_VALUE = INT_MIN;
};