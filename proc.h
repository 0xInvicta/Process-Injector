#ifndef ProcInfo
#define ProcInfo

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>

/// <summary>
/// Lists all running processes
/// </summary>
/// <param name=""></param>
/// <returns></returns>
BOOL procList(void);

#endif
