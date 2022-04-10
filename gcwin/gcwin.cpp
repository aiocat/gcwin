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
    } 
    else if (strcmp(command, "edit") == 0) EditGcWinFile(gcWinPath); // edit gcWin file
    else if (strcmp(command, "init") == 0) {
        // init gcWin file
        bool initResult = CreateGcWinFile();

        // check result
        if (initResult == true) {
            std::cout << "gcwin file created at ";
            std::wcout << gcWinPath << std::endl;
        }
        else std::cerr << "gcwin file already exists." << std::endl;
    }
    else if (strcmp(command, "reset") == 0) ResetGcWinFile(gcWinPath); // reset gcWin file
    else if (strcmp(command, "list") == 0) ListGcWinCommands(gcWinPath); // list gcWin commands
    else if (strcmp(command, "help") == 0) {
        std::cout << "help: To list all commands" << std::endl;
        std::cout << "run [command]: Execute a command" << std::endl;
        std::cout << "edit: Edit gcWin file with notepad" << std::endl;
        std::cout << "init: Create empty gcWin file" << std::endl;
        std::cout << "reset: Clear gcWin file" << std::endl;
    }
    else {
        std::cerr << "command not found." << std::endl;
    }

    return 0;
}