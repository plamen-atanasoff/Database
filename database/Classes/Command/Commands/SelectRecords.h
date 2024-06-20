#pragma once

#include "../Command.h"

class SelectRecords : public Command {
public:
	SelectRecords(int colPos, const String& value, Table* table, unsigned recordsPerPage);

	virtual void execute() const;
	virtual Command* clone() const override;
private:
	int colPos;
	String value;
	Table* table = nullptr;
	const unsigned recordsPerPage;

	static constexpr const char* separator = " | ";

	void printColumnInfo() const;
};

class SelectRecordsCreator : public CommandCreator {
public:
	SelectRecordsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};