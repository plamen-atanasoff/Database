#include "CommandType.h"

#include <stdexcept>

CommandType getCommandTypeAsEnum(const String& type) {
	for (int i = 0; i < (int)CommandType::COMMAND_TYPES_COUNT; i++) {
		if (type == getCommandTypeAsString((CommandType)i)) {
			return (CommandType)i;
		}
	}

	throw std::exception("no such type available");
}

String getCommandTypeAsString(CommandType type) {
	switch (type)
	{
	/*case CommandType::SHOW_TABLES:
		return "showtables";*/
	case CommandType::CREATE_TABLE: // creates a new empty table with the given name
		return "create"; // create <tableName>
	case CommandType::ADD_COLUMN:
		return "addcolumn"; // addcolumn {tableName} <columnName> <columnType>
	case CommandType::ADD_RECORD:
		return "insert"; // insert {tableName} <column1> ... <columnN>
	case CommandType::SAVE_TABLE:
		return "save"; // save {tableName}
	case CommandType::READ_TABLE: // reads the table from the given file
		return "read"; // read <fileName>
	/*case CommandType::DELETE_RECORDS:
		return "delete";*/
	case CommandType::PRINT_TABLE:
		return "print"; // print {tableName}
	/*case CommandType::IMPORT_TABLE:
		return "import";
	case CommandType::OPEN_TABLE:
		return "open";
	case CommandType::DESCRIBE_COLUMNS:
		return "describe";
	case CommandType::EXPORT_TABLE:
		return "export";
	case CommandType::UPDATE_RECORDS:
		return "update";
	case CommandType::SELECT_RECORDS:
		return "select";
	case CommandType::SAVE_TABLE_TO_FILE:
		return "saveas";*/
	case CommandType::SELECT_ONTO:
		return "select_onto";
	}

	throw std::invalid_argument("type is invalid");
}
