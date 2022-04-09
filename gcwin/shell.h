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

#pragma once
#include <windows.h>
#include <string>
#include <tchar.h>
#include <processthreadsapi.h>
#include <shlobj.h>

LPTSTR ToLPTSTR(std::string command); // convert string to lptstr
LPTSTR ToLPTSTR(std::wstring command); // convert wstring to lptstr
void CreateShellProcess(LPTSTR command); // create new shell process