// narly.cpp
// N for gnarly!

#include "narly.h"
#include "tokenizer.h"

using namespace std;

extern "C" HRESULT ExtQuery(PDEBUG_CLIENT4 Client) {
	g_DebugMode = false;
	g_DebugClient = Client;

	if(DebugCreate(__uuidof(IDebugSymbols3),(void **)&g_DebugSymbols) != S_OK) {
        ExtRelease();
		return S_FALSE;
    }
	if(DebugCreate(__uuidof(IDebugDataSpaces3),(void **)&g_DebugDataSpaces) != S_OK) {
        ExtRelease();
		return S_FALSE;
    }
	if(g_DebugClient->QueryInterface(__uuidof(IDebugControl4), (void **)&g_DebugControl) != S_OK) {
        ExtRelease();
		return S_FALSE;
	}

    return S_OK;
}

void ExtRelease(void) {
	IUnknown **unknowns[] = {(IUnknown **) &g_DebugSymbols,
							 (IUnknown **) &g_DebugControl,
							 (IUnknown **) &g_DebugDataSpaces};
	UINT i;
	UINT numUnknowns = sizeof(unknowns) / sizeof(IUnknown *);

	for(i = 0; i < numUnknowns; i++) {
		(*unknowns[i])->Release();
		*unknowns[i] = NULL;
	}

	// reset options to default settings for rerun
	g_BadCharacters = false;
	g_DebugMode = false;
	ModuleUtils::DeleteModNodes();
}

// The entry point for the extension
extern "C" HRESULT CALLBACK DebugExtensionInitialize(PULONG Version, PULONG Flags) {
	PDEBUG_CLIENT debugClient;
	PDEBUG_CONTROL debugControl;
	if(DebugCreate(__uuidof(IDebugClient),(void **)&debugClient) != S_OK) {
        return S_FALSE;
    }
    if(debugClient->QueryInterface(__uuidof(IDebugControl),(void **)&debugControl) == S_OK) {
        ExtensionApis.nSize = sizeof(ExtensionApis);
		debugControl->GetWindbgExtensionApis64((PWINDBG_EXTENSION_APIS64) &ExtensionApis);
        debugControl->Release();
    }
	debugClient->Release();

	dprintf("\n");
	dprintf("      __s|I}*!{a.                        ._s,aan2*a\n");
	dprintf("     _wY1+~-    )S,                     .ae\"~=:...:X\n");
	dprintf("   .vXl+:.       -4c                   <2+=|==::..:d\n");
	dprintf("   vvi=;..        -?o,                =2=+==:::...=d\n");
	dprintf("  )nv=:.            )5,              .2=--.......-=d\n");
	dprintf("  ue+::              -*s             <c .        .=d\n");
	dprintf("  m>==::..     ._,     <s,           )c           :d\n");
	dprintf("  #==viii|===; {Xs=,    -{s          )c         ..:d\n");
	dprintf("  Z;{nnonnvvii;v(-{%%=.    ~s,        )e:====||iiv%%=d\n");
	dprintf("  X={oooonvvIl;3;  -{%%,    -*>       )2<onnnnvnnnn>d\n");
	dprintf("  X=)vvvvIliii:3;    -!s.   :)s.     )e<oonvlllllIid\n");
	dprintf("  X=<lllliii|=:n;      -1c.  +|1,    )z<nvii||+|+|vX\n");
	dprintf("  S=<lli|||=:: n;        \"nc  -s%%;   )c=ovl|++==+=vo\n");
	dprintf("  X=<i||+=; . .n`          \"1>.-{%%i. )c<Xnnli||++=vn\n");
	dprintf("  X=iii>==-.  :o`            \"1,:+iI,)c:Sonnvli||=v(\n");
	dprintf("  X>{ii+;:-  .u(               \"o,-{Iw(:nvvvllii=v2\n");
	dprintf("  S=i||;:. .=u(                 -!o,+I(:iiillii|ie`\n");
	dprintf("  2>v|==__su?`                    -?o,-:==||iisv\"\n");
	dprintf("  {nvnI!\"\"~                         -!sasvv}\"\"`\n");
	dprintf("\n");
	dprintf("             by Nephi Johnson (d0c_s4vage)\n");
	dprintf("                      N for gnarly!\n");
	dprintf("            Addtional Capabilities Added by\n");
	dprintf("               @TheCyberBebop, @Kerpanic\n");
	dprintf("\n");
	dprintf("Available commands:\n"
			"\n"
			"    !nmod     - display Bad Characters, REBASE, /SafeSEH, /GS,\n"
		    "                DEP, and ASLR info for all loaded modules\n"
			"\n");

    return S_OK;
}

extern "C" HRESULT CALLBACK DebugExtensionUninitialize(void) {
	if(g_DebugClient) {
		g_DebugClient->Release();
		g_DebugClient = NULL;
	}

    return S_OK;
}

/*
 * !narlymod - Lists all informatino about all loaded modules.  The current
 * implementation lists /SafeSEH, /GS, NO_SEH, and ASLR and DEP info/compatiblities
 * 
 */
HRESULT CALLBACK nmod(PDEBUG_CLIENT4 Client, PCSTR args) {
    INIT_API();

	if(strstr(args, "/debug") || strstr(args, "/v") || strstr(args, "/verbose")) {
		g_DebugMode = true;
	}

	CHAR badChars[1025] = { 0 };

	if (strstr(args, "/b ")) {
		CHAR testInput[3] = { 0 };
		PCSTR token = "\\x";
		size_t inputLen = 0;

		DEBUG("\n  Parsing Bad Characters input\n");

		// verify the input legnth is not greater then our buffer
		inputLen = strcspn(args + 3, " ");
		if (1025 <= inputLen) {
			dprintf("[-] Max Bad character input is 256 bad charcters!\n");

			ExtRelease();
			return S_OK;
		}

		// copy badchars string
		strncpy_s(badChars,
			sizeof(badChars) / sizeof(badChars[0]),
			args + 3, // skip "\b "
			inputLen
		);

		DEBUG("    Bad Characters input: %s\n", badChars);
		DEBUG("    Length of input: %d\n", inputLen);

		// verify input format -- E.g. \x90\x22\x0a -- *MUST* have \x followed by *TWO* digits
		for (size_t i = 0; i < strlen(badChars); i += 4) {
			strncpy_s(testInput,
				sizeof(testInput) / sizeof(testInput[0]),
				badChars + i,
				(sizeof(testInput) / sizeof(testInput[0])) - 1
			);

			DEBUG("    Verifing input format (\\x): %s\n", testInput);

			// catch missing "\x" or final hex values not being two digits
			if (0 != strcmp(testInput, token) || 4 > strlen(badChars + i)) {
				dprintf("[-] Bad character input error -- verify format! (e.g. /b \\x0a\\x0d\\x22)\n");

				ExtRelease();
				return S_OK;
			}
		}

		g_BadCharacters = true;
	}

	if(strstr(args, "help") || strstr(args, "/?")) {
		dprintf("Summary:\n"
				"\n"
				"    !nmod lists all of the loaded and unloaded modules, displaying\n"
				"    info on Bad Characters, REBASE, /SafeSEH, NO_SEH, /GS, and\n"
			    "    ASLR and DEP compatibility\n"
				"\n"
				"Usage:  !nmod [/b [hex_values] /v /help]\n"
				"\n"
			    "    /b     - Check most significant byte for bad characters\n"
			    "    /b \\x00\\x0a\\x0d\n"
			    "\n"
				"    /debug -  Display verbose output\n"
				"    /verbose\n"
				"    /v\n"
				"\n"
				"    help   -  Who knows what this might do.  I wouldn't try it if\n"
				"    /?        I were you though.\n");
		ExtRelease();
		return S_OK;
	}

	bool isSystem = false;
	extern ModuleUtils::PREBASE myBase; // module node
	BOOL unloadedModulesPrinted = false;
	ULONG i=0, numModulesLoaded=0, numModulesUnloaded=0, currModuleNameSize=0,
		  currImageNameSize=0, currLoadedImageNameSize=0;
	ULONG64 currModuleBase=0;
	IMAGE_NT_HEADERS64 currModuleHeaders;
	CHAR currModuleName[1024]; memset(currModuleName, 0, sizeof(currModuleName));
	CHAR currImageName[1024]; memset(currModuleName, 0, sizeof(currImageName));
	CHAR currLoadedImageName[1024]; memset(currLoadedImageName, 0, sizeof(currLoadedImageName));

	g_DebugSymbols->GetNumberModules(&numModulesLoaded, &numModulesUnloaded);

	while (g_DebugSymbols->GetModuleByIndex(i, &currModuleBase) == S_OK) {
		g_DebugDataSpaces->ReadImageNtHeaders(currModuleBase, &currModuleHeaders);
		g_DebugSymbols->GetModuleNames(i, currModuleBase, currImageName, sizeof(currImageName) - 1,
			&currImageNameSize, currModuleName, sizeof(currModuleName) - 1,
			&currModuleNameSize, currLoadedImageName, sizeof(currLoadedImageName) - 1,
			&currLoadedImageNameSize);

		DEBUG("\ninspecting module %d: %s\n", i, (strlen(currModuleName) == 0 ? currImageName : currModuleName));

		ModuleUtils::insertModNode(
			(DWORD)currModuleHeaders.OptionalHeader.ImageBase, 
			currModuleName
		);

		currModuleBase = 0;
		memset(&currModuleHeaders, 0, sizeof(currModuleHeaders));
		memset(currModuleName, 0, sizeof(currModuleName));
		memset(currImageName, 0, sizeof(currImageName));
		memset(currLoadedImageName, 0, sizeof(currLoadedImageName));
		i++;
	}

	ModuleUtils::VerifyModBase();
	i = 0;

	dprintf("%-8s|%-8s|%-8s|%-20s|%-15s|%-8s|%-13s|%-8s|%-3s|%-5s|%-4s|%-12s|%s\n",
		"|Base",
		"Top",
		"Size",
		"Module",
		"Bad Characters",
		"Rebase",
		"Potential",
		"SafeSEH",
		"GS",
		"ASLR",
		"DEP",
		"System File",
		"Path");
	dprintf("-----------------------------------------------------------------");
	dprintf("---------------------------------------------------------------\n");

	while(g_DebugSymbols->GetModuleByIndex(i, &currModuleBase) == S_OK) {
		g_DebugSymbols->GetModuleNames(i, currModuleBase, currImageName, sizeof(currImageName)-1,
									   &currImageNameSize, currModuleName, sizeof(currModuleName)-1,
									   &currModuleNameSize, currLoadedImageName, sizeof(currLoadedImageName)-1,
									   &currLoadedImageNameSize);

		g_DebugDataSpaces->ReadImageNtHeaders(currModuleBase, &currModuleHeaders);
		
		DEBUG("\ninspecting module %d: %s\n", i, (strlen(currModuleName)==0? currImageName : currModuleName));

		// unloaded module
		if(strlen(currModuleName) == 0) {
			if(!unloadedModulesPrinted) {
				dprintf("\nUnloaded modules:\n");
				unloadedModulesPrinted = true;
			}
			dprintf("%08x %08x %-20s\n", (DWORD)currModuleBase,
										 (DWORD)currModuleBase+currModuleHeaders.OptionalHeader.SizeOfImage,
										  currImageName);
		} else { // will generate a false negative when the path is not included with system modules
			if (strstr(currImageName, "Windows\\System32") ||
				strstr(currImageName, "Windows\\system32") ||
				strstr(currImageName, "Windows\\SYSTEM32") ||
				strstr(currImageName, "Windows\\SysWOW64") ||
				strstr(currImageName, "Windows\\WinSxS")) {

				isSystem = true;
			}
			else {
				isSystem = false;
			}

			dprintf("%08x %08x %08x %-20s %-15s %-8s %-13s %-8s %-3s %-5s %-4s %-12s %s\n",
				(DWORD)currModuleBase,
				(DWORD)currModuleBase + currModuleHeaders.OptionalHeader.SizeOfImage,
				(DWORD)currModuleHeaders.OptionalHeader.SizeOfImage,
				currModuleName,
				g_BadCharacters ? ModuleUtils::checkBadChars(badChars, (DWORD)currModuleBase) : "NOT_CHECKED",
				(ModuleUtils::isReBase(i, (DWORD)currModuleBase) ? "*REBASED" : ""),
				(ModuleUtils::PrintRebase(currModuleName) ? "*COULD_REBASE" : ""),
				(ModuleUtils::hasSEH(i) ? (ModuleUtils::hasSafeSEH(i) ? "ON" : "OFF") : "NO_SEH"),
				(ModuleUtils::hasGS(i) ? "/GS" : ""),
				(ModuleUtils::isDynBaseCompat(i) ? "*ASLR" : ""),
				(ModuleUtils::isNXCompat(i) ? "*DEP" : ""),
				isSystem ? "True" : "False",
				currImageName);
		}

		currModuleBase = 0;
		memset(&currModuleHeaders, 0, sizeof(currModuleHeaders));
		memset(currModuleName, 0, sizeof(currModuleName));
		memset(currImageName, 0, sizeof(currImageName));
		memset(currLoadedImageName, 0, sizeof(currLoadedImageName));
		i++;
	}

	dprintf("\n*DEP/*ASLR means that these modules are compatible with ASLR/DEP\n");
	dprintf("*COULD_REBASE means that the module has the same base address of another loaded module\n");
	dprintf("*REBASED means the module was rebased and the current base address differs from the original\n");
	dprintf("*BADCHARS are *ONLY* checked agaisnt the most significant byte!\n");

    ExtRelease();
	return S_OK;
}

LPEXT_API_VERSION WDBGAPI ExtensionApiVersion (void)
{
	return &g_ExtApiVersion;
}