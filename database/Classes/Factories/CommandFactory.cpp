#include "CommandFactory.h"

#include <stdexcept>

CommandType getCommandTypeAsEnum(const String& type) {
	for (int i = 0; i < (int)CommandType::COMMANDS_COUNT; i++) {
		if (type == getCommandTypeAsString((CommandType)i)) {
			return (CommandType)i;
		}
	}

	throw std::exception("no such type available");
}

String getCommandTypeAsString(CommandType type) {
	switch (type)
	{
	case CommandType::SHOW_TABLES:
		return "showtables";
	case CommandType::CREATE_TABLE:
		return "create";
	case CommandType::ADD_COLUMN:
		return "addcolumn";
	case CommandType::ADD_RECORD:
		return "insert";
	case CommandType::SAVE_TABLE:
		return "save";
	case CommandType::READ_TABLE:
		return "read";
	case CommandType::DELETE_RECORDS:
		return "delete";
	case CommandType::PRINT_TABLE:
		return "print";
	case CommandType::IMPORT_TABLE:
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
		return "saveas";
	}

	throw std::invalid_argument("type is invalid");
}
