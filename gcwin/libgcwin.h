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

std::wstring FindGcWinPath(); // find gcWin path
void ParseGcWinFile(std::wstring gcwinPath, std::string commandName); // parse gcWin file
void EditGcWinFile(std::wstring gcwinPath); // edit gcwin file