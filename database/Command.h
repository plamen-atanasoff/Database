#pragma once

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;
using String = std::string;

class Command {
private:
	CommandName name;
	StringVector args;

	Command(CommandName name, StringVector args);
public:
	Command() = default;
	static Command create(String line);

	CommandName getCommandName() const;
	const StringVector& getArgs() const;
};

enum class CommandName {
	CREATE,

	COMMANDS_COUNT
};