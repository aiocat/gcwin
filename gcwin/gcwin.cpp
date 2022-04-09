#include "libgcwin.h"

int main()
{
    std::wstring gcWinPath = FindGcWinPath();
    std::wcout << gcWinPath << std::endl;
}