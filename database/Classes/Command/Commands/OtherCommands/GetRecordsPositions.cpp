#include "GetRecordsPositions.h"

std::vector<size_t> GetRecordsPositions::execute(const Column* col, const String& value)
{
	std::vector<size_t> res;

	size_t n = col->getSize();

	if (value == "NULL") {
		for (size_t i = 0; i < n; i++) {
			if (!col->hasValue(i)) {
				res.push_back(i);
			}
		}
	}
	else {
		for (size_t i = 0; i < n; i++) {
			if (col->hasValue(i) && col->getValue(i) == value) {
				res.push_back(i);
			}
		}
	}

	return res;
}
