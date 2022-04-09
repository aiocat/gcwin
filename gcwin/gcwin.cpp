
#include <iostream>
#include <Windows.h>
#include <string.h>
#include <shlobj.h>

constexpr int fg_red = 12;
constexpr int fg_white = 15;

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // handle console output
    SetConsoleTextAttribute(hConsole, fg_white); // set text to white


    WCHAR *localAppDataFolder; // local appdata variable

    // find local appdata path
    if (SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &localAppDataFolder) != S_OK) {
        SetConsoleTextAttribute(hConsole, fg_red); // set text to red
        std::cerr << "can't find local appdata" << std::endl;
    }

    // set gcWin path location
    std::wstring gcWinPath(localAppDataFolder); // gcwin path variable
    WCHAR fileNameBuffer[8]; // temporary string for file name
    size_t size; 
    mbstowcs_s(&size, fileNameBuffer, "\\gcwin", 7); // c-string to WCHAR

    gcWinPath.append(fileNameBuffer); // append file name buffer

    std::wcout << gcWinPath << std::endl;
}