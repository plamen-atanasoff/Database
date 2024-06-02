#pragma once

#include <string>

using String = std::string;

enum class CommandType {
	READ_TABLE,
	PRINT_TABLE,

	COMMANDS_COUNT
};

CommandType getCommandTypeAsEnum(const String& type);
String getCommandTypeAsString(CommandType type);
