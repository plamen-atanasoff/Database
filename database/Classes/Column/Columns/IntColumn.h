#pragma once

#include <vector>

#include "../Column.h"
#include "../../Optional/Optional.hpp"

class IntColumn : public Column {
public:
	IntColumn(const String& name, ColumnType type);

	virtual void addValue(const String& val) override;
	virtual void deleteValue(size_t pos) override;
	virtual void changeValue(size_t pos, const String& newVal) override;

	virtual void printValueAt(size_t pos) const override;
	virtual void printValueAtToStream(size_t pos, std::ostream& ofile) const override;

	virtual void writeToFile(std::ofstream& ofile) const override;
	virtual void readFromFile(std::ifstream& ifile) override;

	virtual std::vector<int> getRecordsPositions(const String& val) const override;
	virtual void deleteRecords(const std::vector<int>& recordsPositions) override;
	virtual void updateValues(const std::vector<int>& recordsPositions, const String& newVal) override;

	virtual void initializeValues(size_t recordsCount) override;

	virtual Column* clone() const override;

	virtual String getValue(size_t pos) const override;

	virtual void deleteRecords() override;
private:
	std::vector<Optional<int> > values;
};

class IntColumnCreator : public ColumnCreator {
public:
	IntColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name, ColumnType type) const override;
};