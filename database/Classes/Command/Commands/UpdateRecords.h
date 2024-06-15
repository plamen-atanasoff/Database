#pragma once

#include "../Command.h"

class UpdateRecords : public Command {
public:
	UpdateRecords(int colPosFrom, const String& value, int colPosTo, const String& newValue, Table* table);

	virtual void execute() const;
private:
	int colPosFrom;
	String value;
	int colPosTo;
	String newValue;
	Table* table = nullptr;
};

class UpdateRecordsCreator : public CommandCreator {
public:
	UpdateRecordsCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};