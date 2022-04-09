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
    if (argc < 2) std::cerr << "invalid command, type \"help\" to list all commands." << std::endl; // check argument count

    char* command = argv[1]; // get first argument
    std::wstring gcWinPath = FindGcWinPath(); // find gcwin path

    if (strcmp(command, "run") == 0) {
        // run command
        if (argc < 3) std::cerr << "can't find command name." << std::endl; // check argument count

        std::string commandName = std::string(argv[2]); // get command name
        ParseGcWinFile(gcWinPath, commandName); // parse file
    } else if (strcmp(command, "edit") == 0) {
        // edit gcWin file
        EditGcWinFile(gcWinPath);
    }
}