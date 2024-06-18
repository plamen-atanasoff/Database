#include "GetFileName.h"

String GetFileName::execute(const String& tableName, const std::vector<StringPair>& tables)
{
	size_t n = tables.size();
	for (size_t i = 0; i < n; i++) {
		if (tableName == tables[i].tableName) {
			return tables[i].fileName;
		}
	}

	return "";
}
