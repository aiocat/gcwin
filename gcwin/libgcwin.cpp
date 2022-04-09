#include "libgcwin.h"

// find gcWin path
std::wstring FindGcWinPath() {
    WCHAR* localAppDataFolder; // local appdata variable

    // find local appdata path
    if (SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &localAppDataFolder) != S_OK) {
        std::cerr << "can't find local appdata" << std::endl;
    }

    // set gcWin path location
    std::wstring gcWinPath(localAppDataFolder); // gcwin path variable
    WCHAR fileNameBuffer[8]; // temporary string for file name
    size_t size;
    mbstowcs_s(&size, fileNameBuffer, "\\gcwin", 7); // c-string to WCHAR

    gcWinPath.append(fileNameBuffer); // append file name buffer

    return gcWinPath;
}