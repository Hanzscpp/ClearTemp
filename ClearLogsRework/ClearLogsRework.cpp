#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <locale.h>
#include <Windows.h>

int main() {
    //title for the cmd
    system("title Temporary Files / Logs Cleaner\n");

    //color changer (background and text)
    system("color 0C");

    std::cout << "{+} - WARNING: This will not compromise you computer, it will only delete TEMPORARY files that will not be used more. \n";
    system("pause");


    std::cout << "\n{+} -- By pressing another key this progam will delete the following folders: Temp, %temp% and Prefetch.\n";
    system("pause");

    std::cout << "\n{+} --- Deleting files\n";

    auto deleteFiles = [](const std::wstring& directory) {
        std::wstring path = directory + L"*.*"; //path to the directory
        WIN32_FIND_DATA fileData;
        HANDLE fileHandle = FindFirstFile(path.c_str(), &fileData);

        if (fileHandle != INVALID_HANDLE_VALUE) {
            do {
                if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    std::wstring filename = fileData.cFileName;
                    std::wstring filepath = directory + filename;
                    std::wcout << "Deleting file: " << filepath << std::endl;
                    DeleteFile(filepath.c_str()); //delete the files
                }
            } while (FindNextFile(fileHandle, &fileData));
            FindClose(fileHandle);
        }
    };

    //delete files in Temp directory
    deleteFiles(L"C:\\Windows\\Temp\\");

    //delete files in %temp% directory
    WCHAR tempPath[MAX_PATH];
    DWORD result = GetTempPathW(MAX_PATH, tempPath);
    if (result > 0 && result < MAX_PATH) {
        std::wstring tempDir(tempPath);
        deleteFiles(tempDir);
    }

    //delete files in Prefetch directory
    deleteFiles(L"C:\\Windows\\Prefetch\\");

    std::cout << "\n{+} ---- Done, now you can close and have fun :3\n";

    system("pause");
    return 0;
}
    
   