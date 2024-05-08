#pragma once

enum class CommandType {
	SHOWTABLES,
	CREATE,

	COMMANDS_COUNT
};

const char* getCommandName(CommandType commandName);
