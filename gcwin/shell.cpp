/*
 * GcWin - Global command manager for Windows
 *
 * https://github.com/aiocat/gcwin
 *
 * Licensed under MIT License
 *
 * For more information, please check:
 * https://github.com/aiocat/gcwin/blob/main/LICENSE
 *
 * Copyright (C) 2022, aiocat <aiocat@protonmail.com>
 *
 */

#include "shell.h"

// convert string to lptstr
LPTSTR ToLPTSTR(std::string command) {
	std::wstring wideCommand = std::wstring(command.begin(), command.end());
	const wchar_t* commandAsWchar = wideCommand.c_str();

	return _tcsdup(commandAsWchar);
}

// convert wstring to lptstr
LPTSTR ToLPTSTR(std::wstring command) {
	const wchar_t* commandAsWchar = command.c_str();
	return _tcsdup(commandAsWchar);
}

// create new shell process
void CreateShellProcess(LPTSTR command) {
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;

    if (CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
}