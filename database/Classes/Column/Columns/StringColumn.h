#pragma once

#include "../TypeColumn.hpp"

using String = std::string;

class StringColumn : public TypeColumn<String> {
public:
	StringColumn(const String& name);

	virtual Column* clone() const override;

	virtual void readFromFile(std::ifstream& ifile) override;
	virtual void writeToFile(std::ofstream& ofile) const override;
private:
	virtual String convertFromString(const String& value) const;
	virtual String convertToString(const String& value) const;
};

class StringColumnCreator : public ColumnCreator {
public:
	StringColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name) const override;
};