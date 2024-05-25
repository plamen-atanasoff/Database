#pragma once

#include <string>

using String = std::string;

enum class CommandType {
	SHOW_TABLES,
	CREATE_TABLE,
	ADD_COLUMN,
	ADD_RECORD,
	SAVE_TABLE,
	READ_TABLE,
	DELETE_RECORDS,
	PRINT_TABLE,
	IMPORT_TABLE,
	OPEN_TABLE,

	COMMANDS_COUNT
};

CommandType getCommandTypeAsEnum(const String& type);
String getCommandTypeAsString(CommandType type);
