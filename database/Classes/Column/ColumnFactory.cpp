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

	char name[Column::MAX_NAME_LENGTH];
	int type;

	is.read(reinterpret_cast<char*>(&type), sizeof(type));
	is.read(reinterpret_cast<char*>(name), Column::MAX_NAME_LENGTH);

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
