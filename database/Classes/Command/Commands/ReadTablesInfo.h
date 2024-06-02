#pragma once

#include "../Command.h"

using String = std::string;

class ReadTablesInfo : public Command {
public:
	ReadTablesInfo(const String& fileName, std::vector<StringPair>* tablesInfo);

	virtual void execute() const override;
private:
	String fileName;
	std::vector<StringPair>* tablesInfo = nullptr;
};