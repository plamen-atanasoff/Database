#pragma once

#include "../Command.h"

class WriteTableInfo : public Command {
public:
	WriteTableInfo(const StringPair& tableInfo, const String& tablesFileName);
	virtual void execute() const override;
private:
	const StringPair& tableInfo;
	String tablesFileName;
};
