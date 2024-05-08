#include "CommandFactory.h"
#include <stdexcept>

const char* getCommandName(CommandType commandName) {
	switch (commandName)
	{
	case CommandType::CREATE:
		return "create";
	case CommandType::SHOWTABLES:
		return "showtables";
	}

	throw std::invalid_argument("no such command available");
}
