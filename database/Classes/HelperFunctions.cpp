#include "HelperFunctions.h"

#include "Optional/Optional.hpp"

std::vector<int> getRecordsPositions(const Column* col, const String& value)
{
	std::vector<int> res;
	Optional<int> v;
	if (value != "NULL") {
		v.setValue(std::stoi(value));
	}

	// only int for now
	//std::vector<Optional<int> >& values = col->getValues();
	/*size_t n = values.size();*/
	/*for (int i = 0; i < n; i++) {
		if (values[i].hasValue() && values[i].getValue() == v.getValue()) {
			res.push_back(i);
		}
	}*/

	return res;
}
