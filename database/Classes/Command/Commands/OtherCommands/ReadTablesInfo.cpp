#include "ReadTablesInfo.h"

void ReadTablesInfo::execute(const String& fileName, std::vector<StringPair>* tablesInfo)
{
	std::ifstream ifile(fileName, std::ios::in | std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	size_t size = 0;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));

	StringPair temp;
	tablesInfo->reserve(size);
	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		tablesInfo->push_back(temp);
	}

	ifile.close();
}
