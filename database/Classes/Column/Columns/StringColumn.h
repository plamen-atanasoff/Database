#pragma once

#include "../TypeColumn.hpp"

using String = std::string;

class StringColumn : public TypeColumn<String> {
public:
	StringColumn(const String& name, ColumnType type);

	virtual Column* clone() const override;

	virtual String getValue(size_t pos) const override;
private:
	virtual String convert(const String& value) const;
};

class StringColumnCreator : public ColumnCreator {
public:
	StringColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name, ColumnType type) const override;
};