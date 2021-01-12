#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include "cmd.h"
#include "getch.h"
#include "string_utils.h"

unsigned int History_Index = 0;
std::vector<const char *> History;

bool HistoryInit = false;

char *HistoryFile;
std::fstream file;

void SaveHistory() {
/*	if (!HistoryInit)
		return;

	file.clear();
	file.seekg(0);*/
}

void InitHistory(const char *Name) {
	if (HistoryInit)
		return;

	HistoryInit = true;

	const char *HOME = getenv("HOME");
	HistoryFile = merge_str(HOME, Name);

	file.open(HistoryFile);

	if (!file.is_open()) {
		return;
	}

	std::string Line;
	while (std::getline(file, Line)) {
		if (Line[0] == '\n')
			continue;

		size_t len = Line.size();
		char *C_Line = (char *)malloc(len);
		strncpy(C_Line, Line.c_str(), len);
		History.push_back(C_Line);

		History_Index++;
	}
}

const char *GetShellLine(const char *prompt) {
	std::string Buffer = "";
	History_Index = History.size();

	// The Current Char
	int ch = 0;

	// To Keep Track Of The Character After An ESC
	bool EscPressed = false;
	bool MoveReady = false;

	size_t Prompt_Size = strlen(prompt);
	size_t Buffer_Index = 0;

	auto PrintShell = [&] {
		std::cout << prompt << Buffer;
	};

	auto ClearLine = [&] {
		std::cout << '\r';

		for (size_t i = 0; i < Buffer.size() + Prompt_Size; i++) {
			std::cout << ' ';
		}

		std::cout << '\r';
	};

	PrintShell();
	while ((ch = getch()) != '\n') {
		if (EscPressed) {
			if (MoveReady) {
				if (ch == 'A') {
					if (History_Index < 1) {
						write(1, "", 1);
						continue;
					}

					ClearLine();
					Buffer = History[--History_Index];
					PrintShell();
					continue;
				}
				else if (ch == 'B') {
					if (History_Index + 1 >= History.size()) {
						ClearLine();
						Buffer = "";
						PrintShell();

						write(1, "", 1);
						History_Index = History.size();
						continue;
					}

					ClearLine();
					Buffer = History[++History_Index];
					PrintShell();
					continue;
				}


				else if (ch == 'C') {
					write(1, "[C", 3);
					continue;
				}

				else if (ch == 'D') {
					write(1, "[D", 3);
					continue;
				}
			}

			if (ch == '[') {
				MoveReady = true;
				continue;
			}
		}

		EscPressed = false;
		MoveReady = false;

		if (ch == '') {
			
		}
		else if (ch == 27) { // \e or ESC
			EscPressed = true;
			continue;
		}
		else if (ch == 127) {
			if (Buffer.size() <= 0) {
				write(1, "", 1);
				continue;
			}

			ClearLine();
			Buffer.erase(Buffer.end() - 1);
			PrintShell();

			Buffer_Index--;
			continue;
		}

		Buffer += (char)ch;
		Buffer_Index++;
		std::cout << (char)ch;
	}

	std::cout << std::endl;

	size_t len = Buffer.size();

	char *Line = (char*)malloc(len + 1);
	memset(Line, 0x00, len + 1);
	strncpy(Line, Buffer.c_str(), len);

	History.push_back(Line);

	return Line;
}
