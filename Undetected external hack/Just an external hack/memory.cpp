#include "memory.hpp"

Memory::Memory()
{
    handle = NULL;
}

Memory::~Memory()
{
    CloseHandle(handle);
}

HANDLE Memory::getHandle()
{
    return handle;
}

uintptr_t Memory::getProcess(const wchar_t* proc)
{
    HANDLE hProcessId = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    uintptr_t process = NULL;
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);

    do
    {
        if (!_wcsicmp(pEntry.szExeFile, proc))
        {
            process = pEntry.th32ProcessID;
            CloseHandle(hProcessId);
            handle = OpenProcess(PROCESS_ALL_ACCESS, false, process);
        }

    } while (Process32Next(hProcessId, &pEntry));
    return process;
}

uintptr_t Memory::getModule(uintptr_t procId, const wchar_t* modName)
{
    HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);

    do
    {
        if (!_wcsicmp(mEntry.szModule, modName))
        {
            CloseHandle(hModule);
            return (uintptr_t)mEntry.hModule;
        }
    } while (Module32Next(hModule, &mEntry));
    return 0;
}