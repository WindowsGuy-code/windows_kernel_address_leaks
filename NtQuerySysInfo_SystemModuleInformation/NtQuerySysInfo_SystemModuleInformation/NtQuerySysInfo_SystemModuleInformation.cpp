// NtQuerySysInfo_SystemModuleInformation.cpp : Attempts to use the NtQuerySystemInformation to find the base addresses if loaded modules.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

#define MAXIMUM_FILENAME_LENGTH 255 

typedef struct SYSTEM_MODULE {
	ULONG                Reserved1;
	ULONG                Reserved2;
#ifdef _WIN64
	ULONG				Reserved3;
#endif
	PVOID                ImageBaseAddress;
	ULONG                ImageSize;
	ULONG                Flags;
	WORD                 Id;
	WORD                 Rank;
	WORD                 w018;
	WORD                 NameOffset;
	CHAR                 Name[MAXIMUM_FILENAME_LENGTH];
}SYSTEM_MODULE, *PSYSTEM_MODULE;

typedef struct SYSTEM_MODULE_INFORMATION {
	ULONG                ModulesCount;
	SYSTEM_MODULE        Modules[1];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemModuleInformation = 11
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI *PNtQuerySystemInformation)(
	 SYSTEM_INFORMATION_CLASS SystemInformationClass,
	 PVOID SystemInformation,
	 ULONG SystemInformationLength,
     PULONG ReturnLength
	);

int main()
{
	HMODULE ntdll = GetModuleHandle(TEXT("ntdll"));
	PNtQuerySystemInformation query = (PNtQuerySystemInformation)GetProcAddress(ntdll, "NtQuerySystemInformation");
	if (query == NULL) {
		printf("GetProcAddress() failed.\n");
        cin.get();
		return 1;
	}
	ULONG len = 0;
	query(SystemModuleInformation, NULL, 0, &len);

	HGLOBAL hBuff = GlobalAlloc(GMEM_ZEROINIT, len);
    PSYSTEM_MODULE_INFORMATION pModuleInfo = (PSYSTEM_MODULE_INFORMATION)GlobalLock(hBuff);
	if (pModuleInfo == NULL) {
		printf("Could not allocate memory for module info.\n");
        cin.get();
		return 1;
	}
	NTSTATUS status = query(SystemModuleInformation, pModuleInfo, len, &len);

	if (status != (NTSTATUS)0x0) {
		printf("NtQuerySystemInformation failed with error code 0x%X\n", status);
        cin.get();
		return 1;
	}
	for (unsigned int i = 0; i < pModuleInfo->ModulesCount; i++) {
		PVOID kernelImageBase = pModuleInfo->Modules[i].ImageBaseAddress;
		PCHAR kernelImage = (PCHAR)pModuleInfo->Modules[i].Name;
		printf("Mod name %s ", kernelImage);
#ifdef _WIN64
		printf("Base Addr 0x%llx\r\n", kernelImageBase);
#else
		printf("Base Addr 0x%X\r\n", kernelImageBase);
#endif
	}
    cin.get();
    GlobalUnlock(hBuff);
    GlobalFree(hBuff);
    return 0;
}
