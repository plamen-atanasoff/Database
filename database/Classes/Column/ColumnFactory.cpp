#include "ColumnFactory.h"

#include <cassert>
#include <sstream>

ColumnFactory& ColumnFactory::getFactory()
{
	static ColumnFactory factory;
	return factory;
}

void ColumnFactory::addCreator(const ColumnCreator& creator)
{
	assert(size < MAX_SIZE);
	creators[size++] = &creator;
}

// move this from ColumnFactory to another file
std::vector<String> splitString(const String& input, char delimiter);

Column* ColumnFactory::createColumn(const String& name, ColumnType type) const
{
	const ColumnCreator* creator = getCreator(type);

	if (creator) {
		return creator->create(name);
	}
	else {
		return nullptr;
	}
}

Column* ColumnFactory::readColumnFromStream(std::istream& is)
{
	assert(is.good());

	char name[33]; // remove magic number, set same as Column MAX_SIZE_NAME
	int type;

	is.read(reinterpret_cast<char*>(&type), sizeof(type));
	is.read(reinterpret_cast<char*>(name), 33); // remove magic number, set same as Column MAX_SIZE_NAME

	ColumnType cType = static_cast<ColumnType>(type);

	const ColumnCreator* creator = getCreator(cType);

	return creator->create(name);
}

const ColumnCreator* ColumnFactory::getCreator(ColumnType type) const
{
	for (size_t i = 0; i < size; i++) {
		if (type == creators[i]->getColumnType()) {
			return creators[i];
		}
	}

	return nullptr;
}
