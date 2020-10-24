#pragma once
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <iomanip>

//This memory class is straight outta https://www.youtube.com/watch?v=jutZzuvX8Qs 

class Memory
{
public:

	Memory();
	~Memory();
	HANDLE getHandle();

	template <class val>
	val readMem(uintptr_t addr)
	{
		val x; 
		ReadProcessMemory(handle, (LPBYTE*)addr, &x, sizeof(x), NULL);
		return x;
	}

	template <class val>
	val writeMem(uintptr_t addr, val x)
	{
		WriteProcessMemory(handle, (LPBYTE*)addr, &x, sizeof(x), NULL);
		return x;
	}

	uintptr_t getProcess(const wchar_t*);
	uintptr_t getModule(uintptr_t, const wchar_t*);

private:

	HANDLE handle;
};