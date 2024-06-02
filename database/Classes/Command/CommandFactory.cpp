#include "CommandFactory.h"

#include <cassert>
#include <sstream>

CommandFactory& CommandFactory::getFactory()
{
	static CommandFactory factory;
	return factory;
}

void CommandFactory::addCreator(const CommandCreator& creator)
{
	assert(size < MAX_SIZE);
	creators[size++] = &creator;
}

Command* CommandFactory::createCommand(const String& input, Database& database) const
{
	std::vector<String> tokens = splitString(input, DELIMITER);
	const CommandCreator* creator = getCreator(getCommandTypeAsEnum(tokens[0]));
	tokens.erase(tokens.begin());

	if (creator) {
		return creator->create(tokens, database);
	}
	else {
		return nullptr;
	}
}

const CommandCreator* CommandFactory::getCreator(CommandType type) const
{
	for (size_t i = 0; i < size; i++) {
		if (type == creators[i]->getCommandType()) {
			return creators[i];
		}
	}

	return nullptr;
}

std::vector<String> splitString(const String& str, char delimiter)
{
	std::vector<String> tokens;
	std::stringstream ss(str);
	String token;

	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}
