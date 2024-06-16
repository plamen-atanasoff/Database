#pragma once

#include <string>

using String = std::string;

enum class ColumnType {
	INT,
	DOUBLE,
	STRING,

	COLUMN_TYPES_COUNT
};

ColumnType getColumnTypeAsEnum(const String& type);
String getColumnTypeAsString(ColumnType type);