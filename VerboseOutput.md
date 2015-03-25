Most people never run this, but it might be useful to some. The verbose output to the !nmod function outputs exactly why it gets the results it did. An example is shown below (using the narly\_tester binaries from the download page). Also note that /debug will do the same thing:

```

0:000:x86> !nmod /verbose

inspecting module 0: dll_seh_dep

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -is NOT ASLR compatible

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have /GS without it
00110000 0011c000 dll_seh_dep          /SafeSEH OFF           *DEP dll_seh_dep.dll

inspecting module 1: narly_tester

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00009a70
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: 012d9b40
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: 00000003
    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0
      -has SafeSEH

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00009a70
    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): 012db400
    Security cookie value: 35f01243
    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0
      -has /GS
012d0000 012e0000 narly_tester         /SafeSEH ON  /GS *ASLR *DEP C:\Users\testing\Downloads\narly_tester\narly_tester.exe

inspecting module 2: dll_safeseh_gs

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00007818
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: 100078e0
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: 00000003
    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0
      -has SafeSEH

  Checking for NX_COMPAT flag
    IMAGE_DLLCHARACTERISTICS_NX_COMPAT in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -is NOT DEP compatible

  Checking for DYNAMIC_BASE flag
    IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -is NOT ASLR compatible

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00007818
    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): 10009000
    Security cookie value: 35f1fb6f
    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0
      -has /GS
10000000 1000d000 dll_safeseh_gs       /SafeSEH ON  /GS            dll_safeseh_gs.dll

inspecting module 3: dll_all

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00007820
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: 70e578e0
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: 00000003
    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0
      -has SafeSEH

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00007820
    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): 70e59000
    Security cookie value: 35f1f8a7
    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0
      -has /GS
70e50000 70e5d000 dll_all              /SafeSEH ON  /GS *ASLR *DEP dll_all.dll

inspecting module 4: dll_seh_aslr

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY

  Checking for NX_COMPAT flag
    IMAGE_DLLCHARACTERISTICS_NX_COMPAT in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -is NOT DEP compatible

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have /GS without it
74ec0000 74ecc000 dll_seh_aslr         /SafeSEH OFF     *ASLR      dll_seh_aslr.dll

inspecting module 5: wow64win

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have /GS without it
74ed0000 74f2c000 wow64win             /SafeSEH OFF     *ASLR *DEP C:\Windows\SYSTEM32\wow64win.dll

inspecting module 6: wow64

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have /GS without it
74f30000 74f6f000 wow64                /SafeSEH OFF     *ASLR *DEP C:\Windows\SYSTEM32\wow64.dll

inspecting module 7: wow64cpu

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have /GS without it
74f80000 74f88000 wow64cpu             /SafeSEH OFF     *ASLR *DEP C:\Windows\SYSTEM32\wow64cpu.dll

inspecting module 8: KERNEL32

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00083108
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: 75693150
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: 00000003
    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0
      -has SafeSEH

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00083108
    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): 756f03ac
    Security cookie value: 35f728dd
    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0
      -has /GS
75610000 75720000 KERNEL32             /SafeSEH ON  /GS *ASLR *DEP KERNEL32.dll

inspecting module 9: KERNELBASE

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 000069b8
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: 759a6a30
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: 00000003
    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0
      -has SafeSEH

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 000069b8
    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): 759e0230
    Security cookie value: 35f728ae
    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0
      -has /GS
759a0000 759e6000 KERNELBASE           /SafeSEH ON  /GS *ASLR *DEP KERNELBASE.dll

inspecting module 10: ntdll

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have SafeSEH without an IMAGE_LOAD_CONFIG_DIRECTORY

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00000000
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress was 0
      -can't have /GS without it
776f0000 77899000 ntdll                /SafeSEH OFF     *ASLR *DEP C:\Windows\SYSTEM32\ntdll.dll

inspecting module 11: ntdll_778d0000

  Checking for NO_SEH flag
    IMAGE_DLLCHARACTERISTICS_NO_SEH in IMAGE_OPTIONAL_HEADER.DllCharacteristics is not present
      -has at least SEH

  Checking for /SafeSEH
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00072140
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerTable: 77942188
    IMAGE_LOAD_CONFIG_DIRECTORY.SEHandlerCount: 00000008
    module has an IMAGE_LOAD_CONFIG_DIRECTORY and the SEHandlerCount > 0
      -has SafeSEH

  Checking for NX_COMPAT flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_NX_COMPAT
      -is DEP compatible!

  Checking for DYNAMIC_BASE flag
    IMAGE_OPTIONAL_HEADER.DllCharacteristics has IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
      -is ASLR compatible!

  Checking for /GS
    IMAGE_OPTIONAL_HEADER.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress: 00072140
    IMAGE_LOAD_CONFIG_DIRECTORY.SecurityCookie (is an address): 779d2088
    Security cookie value: 76d70903
    module has an IMAGE_LOAD_CONFIG_DIRECTORY, SecurityCookie != 0, and the value != 0
      -has /GS
778d0000 77a50000 ntdll_778d0000       /SafeSEH ON  /GS *ASLR *DEP ntdll.dll

*DEP/*ASLR means that these modules are compatible with ASLR/DEP
```