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
	dprintf("\n");
	dprintf("Available commands:\n"
			"\n"
			"    !nmod     - display /SafeSEH, /GS, DEP, and ASLR info for\n"
			"                all loaded modules\n"
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

	if(strstr(args, "help") || strstr(args, "/?")) {
		dprintf("Summary:\n"
				"\n"
				"    !nmod lists all of the loaded and unloaded modules, displaying\n"
				"    info on /SafeSEH, NO_SEH, /GS, and ASLR and DEP compatibility\n"
				"\n"
				"Usage:  !nmod [/v /help]\n"
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

	BOOL unloadedModulesPrinted = false;
	ULONG i=0, numModulesLoaded=0, numModulesUnloaded=0, currModuleNameSize=0,
		  currImageNameSize=0, currLoadedImageNameSize=0;
	ULONG64 currModuleBase=0;
	IMAGE_NT_HEADERS64 currModuleHeaders;
	CHAR currModuleName[1024]; memset(currModuleName, 0, sizeof(currModuleName));
	CHAR currImageName[1024]; memset(currModuleName, 0, sizeof(currImageName));
	CHAR currLoadedImageName[1024]; memset(currLoadedImageName, 0, sizeof(currLoadedImageName));

	g_DebugSymbols->GetNumberModules(&numModulesLoaded, &numModulesUnloaded);

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
		} else {
			dprintf("%08x %08x %-20s %-12s %-3s %-5s %-4s %s\n",
							(DWORD)currModuleBase,
							(DWORD)currModuleBase+currModuleHeaders.OptionalHeader.SizeOfImage,
							currModuleName,
							(ModuleUtils::hasSEH(i) ? (ModuleUtils::hasSafeSEH(i) ? "/SafeSEH ON" : "/SafeSEH OFF") : "NO_SEH"),
							(ModuleUtils::hasGS(i) ? "/GS" : ""),
							(ModuleUtils::isDynBaseCompat(i) ? "*ASLR" : ""),
							(ModuleUtils::isNXCompat(i) ? "*DEP" : ""),
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

    ExtRelease();
	return S_OK;
}

LPEXT_API_VERSION WDBGAPI ExtensionApiVersion (void)
{
	return &g_ExtApiVersion;
}