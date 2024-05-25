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
	DESCRIBE_COLUMNS,
	EXPORT_TABLE,
	UPDATE_RECORDS,
	SELECT_RECORDS,
	SAVE_TABLE_TO_FILE,

	COMMANDS_COUNT
};

CommandType getCommandTypeAsEnum(const String& type);
String getCommandTypeAsString(CommandType type);
