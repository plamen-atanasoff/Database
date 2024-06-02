#pragma once

#include <string>

using String = std::string;

enum class CommandType {
	READ_TABLE,
	PRINT_TABLE,
	ADD_COLUMN,

	COMMAND_TYPES_COUNT
};

CommandType getCommandTypeAsEnum(const String& type);
String getCommandTypeAsString(CommandType type);
