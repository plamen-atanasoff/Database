#pragma once

#include <string>

enum class CommandType {
	SHOW_TABLES,
	CREATE_TABLE,
	ADD_COLUMN,
	ADD_RECORD,
	SAVE_TABLE,
	READ_TABLE,

	COMMANDS_COUNT
};

CommandType getCommandTypeAsEnum(const std::string& type);
const char* getCommandTypeAsString(CommandType type);
