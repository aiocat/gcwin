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
        std::cerr << "can't find local appdata." << std::endl; // find local appdata path

    // set gcWin path location
    std::wstring gcWinPath(localAppDataFolder); // gcwin path variable
    WCHAR fileNameBuffer[8]; // temporary string for file name
    size_t fileNameSize;
    mbstowcs_s(&fileNameSize, fileNameBuffer, "\\gcwin", 7); // c-string to WCHAR

    gcWinPath.append(fileNameBuffer); // append file name buffer

    return gcWinPath;
}

// parse gcWin file
void ParseGcWinFile(std::wstring gcWinPath, std::string commandName) {
    std::ifstream gcWinFile(gcWinPath); // open gcwin file as read mode
    bool foundCommand = false;
    commandName += std::string(":"); // edit command name

    if (gcWinFile.is_open()) {
        std::string gcWinLine; // current line

        // read file line-by-line
        while (std::getline(gcWinFile, gcWinLine)) {
            if (!foundCommand && gcWinLine == commandName) foundCommand = true; // command found
            else if (foundCommand) {
                if (gcWinLine == std::string()) break; // finish loop
                else system(gcWinLine.c_str()); // run command
            }
        }
        gcWinFile.close(); // close file
        if (!foundCommand) 
            std::cerr << "command not found." << std::endl; // check if command parsed
    }
    else std::cerr << "can't open gcwin file." << std::endl;
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