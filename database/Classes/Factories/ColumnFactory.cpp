#include "ColumnFactory.h"

#include <stdexcept>

Column* getColumn(const std::string& name, ColumnType type) {
	switch (type) {
	case ColumnType::INT:
		return new IntColumn(name, type);
	}

	throw std::invalid_argument("type is invalid");
}