#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


BOOL procList(void) {
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Check if able to get first proccess if Error is Spawned exit [return(FALSE)].
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return(FALSE);
    }

    do
    {
        _tprintf(TEXT("\nPID:\033[31m%d\033[0m: [\033[36m%s\033[0m]"), pe32.th32ProcessID, pe32.szExeFile);


    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(TRUE);
}