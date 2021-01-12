#pragma once

void InitHistory(const char *Name);
const char *GetShellLine(const char *Prompt);

#include <vector>
#include <fstream>

#include "ShellPromptSettings.h"

class ShellInput {
public:
	ShellInput(const ShellPromptSettings& settings);
	ShellInput();
	~ShellInput();

	void InitHistory(const char *File);
	void SaveHistory();

	const char *GetLine();
private:
	std::fstream m_HistoryFile;
	std::vector<const char *> m_HistoryBuffer;
	size_t m_HistoryIndex;

	std::string m_LineBuffer;
	char *m_Prompt;
};
