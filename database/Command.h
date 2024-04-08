#pragma once

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;
using String = std::string;

enum class CommandType {
	CREATE,

	COMMANDS_COUNT
};

class Command {
private:
	CommandType name;
	StringVector args;

	Command(CommandType name, StringVector args);
public:
	static Command create(String line);

	CommandType getCommandName() const;
	const StringVector& getArgs() const;
};
