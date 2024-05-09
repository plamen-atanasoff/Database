#pragma once

#include <string>

enum class ColumnType {
	INT,

	COLUMN_TYPES_COUNT
};

ColumnType getColumnTypeAsEnum(const std::string& type);
std::string getColumnTypeAsString(ColumnType type);