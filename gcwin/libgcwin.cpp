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

// find gcWin path
std::wstring FindGcWinPath() {
    WCHAR* localAppDataFolder; // local appdata variable

    if (SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &localAppDataFolder) != S_OK) 
        return std::wstring(); // find local appdata path

    // set gcWin path location
    std::wstring gcWinPath(localAppDataFolder); // gcwin path variable
    WCHAR fileNameBuffer[8]; // temporary string for file name
    size_t fileNameSize;
    mbstowcs_s(&fileNameSize, fileNameBuffer, "\\gcwin", 7); // c-string to WCHAR

    gcWinPath.append(fileNameBuffer); // append file name buffer

    return gcWinPath;
}

// parse gcWin file
int ParseGcWinFile(std::wstring gcWinPath, std::string commandName) {
    Command command = FindGcWinCommand(gcWinPath, commandName);

    // error checking
    if (command.error == 0 || command.error == -1)
        return command.error;

    // run commands
    for (std::string instruction : command.commands)
        system(instruction.c_str());

    return 1;
}

// edit gcWin file
int EditGcWinFile(std::wstring gcWinPath) {
    std::string notepadCommand = std::string("notepad ");
    notepadCommand += std::string(gcWinPath.begin(), gcWinPath.end());

    return system(notepadCommand.c_str());
}

// init gcWin file
bool CreateGcWinFile() {
    std::wstring filePath = FindGcWinPath(); // get file path

    // create empty file
    std::ifstream gcWinFile(filePath);

    // check file exists
    if (!gcWinFile.good()) {
        // close read mode
        gcWinFile.close();

        // open as write mode
        std::ofstream gcWinFile(filePath);
        gcWinFile << "";
        gcWinFile.close();

        return true;
    }

    gcWinFile.close();
    return false;
}

// reset gcWin file
void ResetGcWinFile(std::wstring gcWinPath) {
    std::ofstream gcWinFile;
    gcWinFile.open(gcWinPath.c_str(), std::ofstream::out | std::ofstream::trunc);
    gcWinFile.close();
}

// list gcWin commands
std::vector<std::string> ListGcWinCommands(std::wstring gcWinPath) {
    std::ifstream gcWinFile(gcWinPath); // open gcwin file as read mode
    bool inCommand = false;
    std::vector<std::string> commands; // commands vector

    if (gcWinFile.is_open()) {
        std::string gcWinLine; // current line

        // read file line-by-line
        while (std::getline(gcWinFile, gcWinLine)) {
            if (!inCommand && gcWinLine.back() == ':') {
                // command found
                inCommand = true;

                gcWinLine.pop_back();
                commands.push_back(gcWinLine);
            }
            else if (inCommand && gcWinLine == std::string()) inCommand = false; // command finished
        }
        gcWinFile.close(); // close file
    }

    return commands;
}

// dump gcWin file
std::string DumpGcWinFile(std::wstring gcWinPath) {
    std::ifstream gcWinFile(gcWinPath); // open as read mode
    std::string content = std::string(); // content variable
    
    // check file open
    if (gcWinFile.is_open()) {
        std::string gcWinLine; // current line

        // read file line-by-line
        while (std::getline(gcWinFile, gcWinLine)) {
            content += gcWinLine;
            content.push_back('\n');
        }

        gcWinFile.close(); // close file
        return content;
    }
    else {
        // close file
        gcWinFile.close();
        return std::string();
    }
}

// find gcWin command
Command FindGcWinCommand(std::wstring gcWinPath, std::string commandName) {
    std::ifstream gcWinFile(gcWinPath); // open gcwin file as read mode
    bool foundCommand = false;

    // add command struct
    Command command = Command{ commandName, {}, 1 };

    commandName += std::string(":"); // edit command name

    if (gcWinFile.is_open()) {
        std::string gcWinLine; // current line

        // read file line-by-line
        while (std::getline(gcWinFile, gcWinLine)) {
            if (!foundCommand && gcWinLine == commandName) foundCommand = true; // command found
            else if (foundCommand) {
                if (gcWinLine == std::string()) break; // finish loop
                else command.commands.push_back(gcWinLine); // append command
            }
        }
        gcWinFile.close(); // close file

        // check if command parsed
        if (!foundCommand) {
            command.error = 0;
            return command;
        }; 
    }
    else {
        command.error = -1;
        return command;
    };
    return command;
}