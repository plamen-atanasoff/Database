#pragma once

#include <string>
#include <vector>

#include "Column.h"

using String = std::string;

class ColumnFactory {
public:
	static ColumnFactory& getFactory();
	void addCreator(const ColumnCreator& creator);

	Column* createColumn(const String& name, ColumnType type) const;
	Column* readColumnFromStream(std::istream& is);
private:
	static constexpr size_t MAX_SIZE = static_cast<size_t>(ColumnType::COLUMN_TYPES_COUNT);
	static constexpr char DELIMITER = ' ';
	const ColumnCreator* creators[MAX_SIZE]{};
	size_t size = 0;

	ColumnFactory() = default;
	~ColumnFactory() = default;
	ColumnFactory(const ColumnFactory&) = delete;
	ColumnFactory& operator=(const ColumnFactory&) = delete;

	const ColumnCreator* getCreator(ColumnType type) const;
};
