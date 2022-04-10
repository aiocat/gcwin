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

constexpr int FG_GREEN = 10; // green foreground
constexpr int FG_RED = 12; // red foreground
constexpr int FG_WHITE = 15; // white foreground

HANDLE handleConsole; // console handler

int HandleError(const char* message); // handle error and exit 

int main(int argc, char** argv)
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handleConsole, FG_WHITE);

    if (argc < 2) return HandleError("invalid command, type \"help\" to list all commands."); // check argument count

    char* command = argv[1]; // get first argument
    std::wstring gcWinPath = FindGcWinPath(); // find gcwin path

    // error checking
    if (gcWinPath == std::wstring()) return HandleError("unknown error while finding file path.");

    if (strcmp(command, "run") == 0) {
        // run command
        if (argc < 3) return HandleError("can't find gcWin command name."); // check argument count

        std::string commandName = std::string(argv[2]); // get command name
        int result = ParseGcWinFile(gcWinPath, commandName); // parse file

        // handle errors
        if (result == 0) return HandleError("gcWin command not found.");
        else if (result == -1) return HandleError("can't open gcWin file.");
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
        else return HandleError("gcWin file already exists.");
    }
    else if (strcmp(command, "reset") == 0) ResetGcWinFile(gcWinPath); // reset gcWin file
    else if (strcmp(command, "list") == 0) {
        // list gcWin commands
        std::vector<std::string> commands = ListGcWinCommands(gcWinPath);

        // error checking
        if (commands == std::vector<std::string>()) return HandleError("can't find any gcWin command.");

        // write commands
        for (std::string command : commands)
            std::cout << command << std::endl;
    }
    else if (strcmp(command, "dump") == 0) {
        // dump gcWin file
        std::string content = DumpGcWinFile(gcWinPath);

        // error checking
        if (content == std::string()) return HandleError("unknown error while reading gcWin file.");

        std::cout << content << std::endl;
    }
    else if (strcmp(command, "help") == 0) {
        std::cout << "help: To list all commands" << std::endl;
        std::cout << "run [command]: Execute a command" << std::endl;
        std::cout << "edit: Edit gcWin file with notepad" << std::endl;
        std::cout << "init: Create empty gcWin file" << std::endl;
        std::cout << "reset: Clear gcWin file" << std::endl;
        std::cout << "list: List all avaible gcWin commands" << std::endl;
        std::cout << "dump: Output gcWin file content" << std::endl;
    }
    else if (strcmp(command, "find") == 0) {
        // run command
        if (argc < 3) std::cerr << "can't find command name." << std::endl; // check argument count

        std::string commandName = std::string(argv[2]); // get command name

        Command command = FindGcWinCommand(gcWinPath, commandName);

        if (command.error == 0) return HandleError("gcWin command not found.");
        else if (command.error == -1) return HandleError("can't open gcWin file.");

        // print command
        SetConsoleTextAttribute(handleConsole, FG_GREEN | FOREGROUND_INTENSITY);
        std::cout << command.name << std::endl;
        SetConsoleTextAttribute(handleConsole, FG_WHITE);

        for (std::string instruction : command.commands)
            std::cout << "  " << instruction << std::endl;
    }
    else return HandleError("command not found.");

    return 0;
}

// handle error and exit
int HandleError(const char* message) {
    SetConsoleTextAttribute(handleConsole, FG_RED | FOREGROUND_INTENSITY);
    std::cerr << message << std::endl;
    SetConsoleTextAttribute(handleConsole, FG_WHITE);

    return -1;
}