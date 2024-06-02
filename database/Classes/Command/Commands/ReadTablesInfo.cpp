#include "ReadTablesInfo.h"

ReadTablesInfo::ReadTablesInfo(const String& fileName, std::vector<StringPair>* tablesInfo) : fileName(fileName), tablesInfo(tablesInfo) {}

void ReadTablesInfo::execute() const
{
	std::ifstream ifile(fileName, std::ios::binary);
	if (!ifile.is_open()) {
		return;
	}

	size_t size;
	ifile.read(reinterpret_cast<char*>(&size), sizeof(size));

	StringPair temp;
	tablesInfo->reserve(size);
	for (size_t i = 0; i < size; i++) {
		ifile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		tablesInfo->push_back(temp);
	}

	ifile.close();
}
