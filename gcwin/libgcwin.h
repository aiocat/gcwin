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
#include <string>
#include <shlobj.h>
#include <iostream>
#include <fstream>

std::wstring FindGcWinPath(); // find gcWin path
void ParseGcWinFile(std::wstring gcwinPath, std::string commandName); // parse gcWin file 