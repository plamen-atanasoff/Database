#pragma once

#include <string>

using String = std::string;

enum class CommandType {
	READ_TABLE,
	PRINT_TABLE,
	ADD_COLUMN,
	CREATE_TABLE,
	SAVE_TABLE,
	ADD_RECORD,

	COMMAND_TYPES_COUNT
};

CommandType getCommandTypeAsEnum(const String& type);
String getCommandTypeAsString(CommandType type);
