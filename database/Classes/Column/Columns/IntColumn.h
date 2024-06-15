#pragma once

#include "../TypeColumn.hpp"

class IntColumn : public TypeColumn<int> {
public:
	IntColumn(const String& name, ColumnType type);

	virtual Column* clone() const override;

	virtual String getValue(size_t pos) const override;
private:
	virtual int convert(const String& value) const;
};

class IntColumnCreator : public ColumnCreator {
public:
	IntColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name, ColumnType type) const override;
};