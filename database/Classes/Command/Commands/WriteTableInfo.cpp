#include "WriteTableInfo.h"

WriteTableInfo::WriteTableInfo(const StringPair& tableInfo, const String& tablesFileName, size_t tablesCount)
	: tableInfo(tableInfo), tablesFileName(tablesFileName), tablesCount(tablesCount) {}

void WriteTableInfo::execute() const
{
	std::fstream file(tablesFileName, std::ios::out | std::ios::app | std::ios::binary);
	if (!file.is_open()) {
		throw std::exception("file could not be opened");
	}

	tablesCount++;
	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(&tablesCount), sizeof(tablesCount));
	file.seekp(0, std::ios::end);
	file.write(reinterpret_cast<const char*>(&tableInfo), sizeof(tableInfo));

	file.close();
}
