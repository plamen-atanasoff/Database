#pragma once

#include "../TypeColumn.hpp"

class DoubleColumn : public TypeColumn<double> {
public:
	DoubleColumn(const String& name, ColumnType type);

	virtual Column* clone() const override;

	virtual String getValue(size_t pos) const override;
private:
	virtual double convert(const String& value) const;
};

class DoubleColumnCreator : public ColumnCreator {
public:
	DoubleColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name, ColumnType type) const override;
};