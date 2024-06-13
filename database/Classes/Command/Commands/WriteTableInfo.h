#pragma once

#include "../Command.h"

class WriteTableInfo : public Command {
public:
	WriteTableInfo(const StringPair& tableInfo, const String& tablesFileName, size_t tablesCount);
	virtual void execute() const override;
private:
	const StringPair& tableInfo;
	String tablesFileName;
	mutable size_t tablesCount;
};
