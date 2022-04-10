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
#include <iostream>
#include <fstream>
#include <shlobj.h>
#include <vector>

std::wstring FindGcWinPath(); // find gcWin path
int ParseGcWinFile(std::wstring gcWinPath, std::string commandName); // parse gcWin file
int EditGcWinFile(std::wstring gcWinPath); // edit gcWin file
bool CreateGcWinFile(); // init gcWin file
void ResetGcWinFile(std::wstring gcWinPath); // reset gcWin file
std::vector<std::string> ListGcWinCommands(std::wstring gcWinPath); // list gcWin commands