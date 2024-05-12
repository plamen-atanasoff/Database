#pragma once

#include <string>

#include "ColumnType.h"
#include "../Columns/IntColumn.h"

using String = std::string;

Column* getColumn(const String& name, ColumnType type);