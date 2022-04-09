#pragma once
#include <string>
#include <shlobj.h>
#include <iostream>
#include <fstream>

std::wstring FindGcWinPath(); // find gcWin path
void ParseGcWinFile(std::wstring gcwinPath, std::string commandName); // parse gcWin file 