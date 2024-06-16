#pragma once

#include "../TypeColumn.hpp"

class DoubleColumn : public TypeColumn<double> {
public:
	DoubleColumn(const String& name);

	virtual Column* clone() const override;
private:
	virtual double convert(const String& value) const;
};

class DoubleColumnCreator : public ColumnCreator {
public:
	DoubleColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name) const override;
};