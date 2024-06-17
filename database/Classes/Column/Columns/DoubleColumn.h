#pragma once

#include "../TypeColumn.hpp"

class DoubleColumn : public TypeColumn<double> {
public:
	DoubleColumn(const String& name);

	virtual Column* clone() const override;
private:
	virtual double convertFromString(const String& value) const override;
	virtual String convertToString(const double& value) const override;
};

class DoubleColumnCreator : public ColumnCreator {
public:
	DoubleColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name) const override;
};