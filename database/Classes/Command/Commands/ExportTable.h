#pragma once

#include "../Command.h"

class ExportTable : public Command {
public:
	ExportTable(const String& filePath, Table* table);

	virtual void execute() const;
private:
	String filePath;
	Table* table = nullptr;
};

class ExportTableCreator : public CommandCreator {
public:
	ExportTableCreator();
	virtual Command* create(const std::vector<String>& args, Database& database) const override;
};