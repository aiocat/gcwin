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

#include "libgcwin.h"

int main(int argc, char** argv)
{
    if (argc < 2) std::cerr << "can't find command name" << std::endl; // check argument count

    std::string commandName = std::string(argv[1]); // get first argument
    std::wstring gcWinPath = FindGcWinPath(); // find gcwin path

    ParseGcWinFile(gcWinPath, commandName); // parse file
}