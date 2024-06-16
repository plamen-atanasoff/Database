#pragma once

#include "../TypeColumn.hpp"

using String = std::string;

class StringColumn : public TypeColumn<String> {
public:
	StringColumn(const String& name);

	virtual Column* clone() const override;
private:
	virtual String convert(const String& value) const;
};

class StringColumnCreator : public ColumnCreator {
public:
	StringColumnCreator();
	virtual Column* create(const std::vector<String>& args) const override;
	virtual Column* create(const String& name) const override;
};