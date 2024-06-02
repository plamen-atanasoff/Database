#pragma once

#include "Command.h"
#include "../Controller.h"

#include <string>
#include <vector>

using String = std::string;

class CommandFactory
{
public:
	static CommandFactory& getFactory();
	void addCreator(const CommandCreator& creator);

	Command* createCommand(const String& input, Database& database) const;
private:
	static constexpr size_t MAX_SIZE = static_cast<size_t>(CommandType::COMMANDS_COUNT);
	static constexpr char DELIMITER = ' ';
	const CommandCreator* creators[MAX_SIZE] {};
	size_t size = 0;

	CommandFactory() = default;
	~CommandFactory() = default;
	CommandFactory(const CommandFactory&) = delete;
	CommandFactory& operator=(const CommandFactory&) = delete;

	const CommandCreator* getCreator(CommandType type) const;
};

std::vector<String> splitString(const String& str, char delimiter);