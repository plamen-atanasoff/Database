#include "WriteTableInfo.h"

void WriteTableInfo::execute(const StringPair& tableInfo, const String& tablesFileName, size_t tablesCount)
{
	std::fstream file(tablesFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		file.open(tablesFileName, std::ios::out | std::ios::binary);
		file.close();

		file.open(tablesFileName, std::ios::in | std::ios::out | std::ios::binary);
		if (!file.is_open()) {
			throw std::exception("file could not be opened");
		}
	}

	tablesCount++;
	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(&tablesCount), sizeof(tablesCount));
	file.seekp(0, std::ios::end);
	file.write(reinterpret_cast<const char*>(&tableInfo), sizeof(tableInfo));

	file.close();
}
