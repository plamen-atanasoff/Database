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
	}

	throw std::invalid_argument("type is invalid");
}
