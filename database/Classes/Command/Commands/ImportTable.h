#pragma once

#include "../Command.h"

class ImportTable : public Command {
public:
	ImportTable(const String& fileName, std::vector<StringPair>& tables, Table* table, const String& tablesFileName);
	virtual void execute() const override;
	virtual Command* clone() const override;
private:
	String fileName;
	std::vector<StringPair>& tables;
	Table* table = nullptr;
	String tablesFileName;

	bool fileNameExists() const;
};

class ImportTableCreator : public CommandCreator {
public:
	ImportTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};