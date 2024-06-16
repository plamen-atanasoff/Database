#include "ColumnType.h"

#include <stdexcept>

ColumnType getColumnTypeAsEnum(const String& type) {
    for (int i = 0; i < (int)ColumnType::COLUMN_TYPES_COUNT; i++) {
        if (type == getColumnTypeAsString((ColumnType)i)) {
            return (ColumnType)i;
        }
    }

    throw std::exception("no such type available");
}

String getColumnTypeAsString(ColumnType type) {
	switch (type)
	{
	case ColumnType::INT:
		return "int";
	case ColumnType::DOUBLE:
		return "double";
	case ColumnType::STRING:
		return "string";
	}

	throw std::invalid_argument("type is invalid");
}
