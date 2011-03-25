// narly.h
// N for gnarly!

#ifndef _NARLY_H
#define _NARLY_H

#include <windows.h>
#include <wdbgexts.h>
#include <dbgeng.h>
#include <vector>
#include <ios>
#include <iostream>
#include <sstream>

bool g_DebugMode = false;
PDEBUG_SYMBOLS3 g_DebugSymbols;
PDEBUG_CONTROL4 g_DebugControl;
PDEBUG_DATA_SPACES3 g_DebugDataSpaces;
PDEBUG_CLIENT4 g_DebugClient;
WINDBG_EXTENSION_APIS ExtensionApis;

extern "C" HRESULT ExtQuery(PDEBUG_CLIENT4 Client);
void ExtRelease(void);
ULONG64 resolveFunctionByName(char *funcName);

#define DEBUG(...) if(g_DebugMode) { dprintf(__VA_ARGS__); }
#define INIT_API() HRESULT Status; if ((Status = ExtQuery(Client)) != S_OK) return Status;
#define EXT_RELEASE(Unk) ((Unk) != NULL ? ((Unk)->Release(), (Unk) = NULL) : NULL)

EXT_API_VERSION g_ExtApiVersion = {1,1,EXT_API_VERSION_NUMBER,0} ;

namespace ModuleUtils {

	bool hasSEH(ULONG moduleIndex) {
		IMAGE_NT_HEADERS64 moduleHeaders;
		ULONG64 moduleBase;
		g_DebugSymbols->GetModuleByIndex(moduleIndex, &moduleBase);
		g_DebugDataSpaces->ReadImageNtHeaders(moduleBase, &moduleHeaders);
		
		DEBUG("\n  Checking for NO_SEH flag\n");

		if(moduleHeaders.OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NO_SEH) {
			DEBUG("    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NO_SEH\n");
			DEBUG("      -does not have SEH!\n");
			return false;
		} else {
			DEBUG("    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present\n");
			DEBUG("      -has at least SEH\n");
			return true;
		}
	};

	bool isDynBaseCompat(ULONG moduleIndex) {
		IMAGE_NT_HEADERS64 moduleHeaders;
		ULONG64 moduleBase;
		g_DebugSymbols->GetModuleByIndex(moduleIndex, &moduleBase);
		g_DebugDataSpaces->ReadImageNtHeaders(moduleBase, &moduleHeaders);
		
		DEBUG("\n  Checking for DYNAMIC_BASE flag\n");

		if(moduleHeaders.OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) {
			DEBUG("    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE\n");
			DEBUG("      -is ASLR compatible!\n");
			return true;
		} else {
			DEBUG("    IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present\n");
			DEBUG("      -is NOT ASLR compatible\n");
			return false;
		}
	};

	bool isNXCompat(ULONG moduleIndex) {
		IMAGE_NT_HEADERS64 moduleHeaders;
		ULONG64 moduleBase;
		g_DebugSymbols->GetModuleByIndex(moduleIndex, &moduleBase);
		g_DebugDataSpaces->ReadImageNtHeaders(moduleBase, &moduleHeaders);
		
		DEBUG("\n  Checking for NX_COMPAT flag\n");

		if(moduleHeaders.OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_NX_COMPAT) {
			DEBUG("    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT\n");
			DEBUG("      -is DEP compatible!\n");
			return true;
		} else {
			DEBUG("    IMAGE_DLLCHARACTERISTICS_NX_COMPAT in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present\n");
			DEBUG("      -is NOT DEP compatible\n");
			return false;
		}
	};

	bool hasSafeSEH(ULONG moduleIndex) {
		IMAGE_LOAD_CONFIG_DIRECTORY32 moduleConfig;
		IMAGE_NT_HEADERS64 moduleHeaders;
		DWORD loadConfigSize;
		ULONG bytesRead=0;
		ULONG64 moduleBase=0, loadConfigVA=0;
		g_DebugSymbols->GetModuleByIndex(moduleIndex, &moduleBase);
		g_DebugDataSpaces->ReadImageNtHeaders(moduleBase, &moduleHeaders);
		loadConfigVA = moduleHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress;
		loadConfigSize = moduleHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size;

		DEBUG("\n  Checking for /SafeSEH\n");

		DEBUG("    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: %08x\n", (DWORD)loadConfigVA);

		if(loadConfigVA == 0) {
			DEBUG("    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0\n");
			DEBUG("      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY\n");
			return false;
		}

		g_DebugDataSpaces->ReadVirtual(moduleBase+loadConfigVA, (PVOID)&moduleConfig,
									   sizeof(moduleConfig), &bytesRead);

		DEBUG("    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: %08x\n", (DWORD)moduleConfig.SEHandlerTable);
		DEBUG("    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: %08x\n", (DWORD)moduleConfig.SEHandlerCount);

		if(moduleConfig.SEHandlerCount == 0) {
			DEBUG("    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount was 0\n");
			DEBUG("      -no registered handles == no SafeSEH\n");
			return false;
		}

		DEBUG("    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0\n");
		DEBUG("      -has SafeSEH\n");

		return true;
	};

	bool hasGS(ULONG moduleIndex) {
		IMAGE_NT_HEADERS64 moduleHeaders;
		IMAGE_LOAD_CONFIG_DIRECTORY32 moduleConfig;
		DWORD loadConfigSize=0, securityCookieAddr=0, securityCookieVal=0;
		ULONG bytesRead=0;
		ULONG64 moduleBase=0, loadConfigVA=0;
		g_DebugSymbols->GetModuleByIndex(moduleIndex, &moduleBase);
		g_DebugDataSpaces->ReadImageNtHeaders(moduleBase, &moduleHeaders);
		loadConfigVA = moduleHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress;

		DEBUG("\n  Checking for /GS\n");

		DEBUG("    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: %08x\n", (DWORD)loadConfigVA);

		if(loadConfigVA == 0) {
			DEBUG("    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0\n");
			DEBUG("      -can't have /GS without it\n");
			return false;
		}

		g_DebugDataSpaces->ReadVirtual(moduleBase+loadConfigVA, (PVOID)&moduleConfig,
									   sizeof(moduleConfig), &bytesRead);

		DEBUG("    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): %08x\n", moduleConfig.SecurityCookie);

		// read the actual value of the security cookie
		if(moduleConfig.SecurityCookie == 0) {
			DEBUG("    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie was 0\n");
			DEBUG("      -pointer to securitiy cookie == 0 (no /GS)\n");
			return false;
		}

		g_DebugDataSpaces->ReadVirtual(moduleConfig.SecurityCookie, (PVOID)&securityCookieVal,
									   sizeof(DWORD), &bytesRead);

		DEBUG("    Security cookie value: %08x\n", securityCookieVal);

		if(securityCookieVal == 0) {
			DEBUG("    Security cookie value was 0\n");
			DEBUG("      -essentially makes /GS be turned off\n");
			return false;
		}

		DEBUG("    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0\n");
		DEBUG("      -has /GS\n");

		return true;
	};
}

#endif // #define _NARLY_H