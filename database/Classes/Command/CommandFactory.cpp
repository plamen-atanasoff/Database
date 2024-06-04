#include "CommandFactory.h"

#include <cassert>
#include <sstream>
#include <string>

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
	size_t typeEnd = input.find_first_of(DELIMITER);
	String mInput = input.substr(typeEnd + 1);

	const CommandCreator* creator = getCreator(getCommandTypeAsEnum(input.substr(0, typeEnd)));

	std::vector<String> tokens;
	if (creator->getCommandType() == CommandType::SELECT_ONTO) {
		size_t startArrInd = mInput.find_first_of('[');
		size_t endArrInd = mInput.find_first_of(']');

		tokens = splitString(mInput.substr(0, startArrInd - 1), DELIMITER);
		tokens.insert(tokens.end(), mInput.substr(startArrInd + 1, endArrInd - startArrInd - 1));
		std::vector<String> temp = splitString(mInput.substr(endArrInd + 2), DELIMITER);
		tokens.insert(tokens.end(), temp.begin(), temp.end());
	}
	else {
		tokens = splitString(mInput, DELIMITER);
	}

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
