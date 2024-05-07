#pragma once
#include <string>
#include "ColumnType.h"
#include "../Columns/IntColumn.h"

Column* getColumn(const std::string& name, ColumnType type);