#include "ColumnType.h"
#include <stdexcept>

ColumnType getColumnTypeAsEnum(const std::string& type) {
    for (int i = 0; i < (int)ColumnType::COLUMN_TYPES_COUNT; i++) {
        if (type == getColumnTypeAsString((ColumnType)i)) {
            return (ColumnType)i;
        }
    }

    throw std::exception("no such type available");
}

std::string getColumnTypeAsString(ColumnType type) {
	switch (type)
	{
	case ColumnType::INT:
		return "int";
	}

	throw std::invalid_argument("no such type available");
}
