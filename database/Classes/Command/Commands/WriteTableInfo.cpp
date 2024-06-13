#include "WriteTableInfo.h"

WriteTableInfo::WriteTableInfo(const StringPair& tableInfo, const String& tablesFileName) 
	: tableInfo(tableInfo), tablesFileName(tablesFileName) {}

void WriteTableInfo::execute() const
{
	std::fstream file(tablesFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		throw std::exception("file could not be opened");
	}

	size_t count;
	file.read(reinterpret_cast<char*>(&count), sizeof(count));
	count++;
	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(&count), sizeof(count));
	file.seekp(0, std::ios::end);
	file.write(reinterpret_cast<const char*>(&tableInfo), sizeof(tableInfo));

	file.close();
}
