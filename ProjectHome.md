This windbg extension is intended to be able to:

  * list /SafeSEH, /GS, DEP, and ASLR info about all loaded modules
  * search for ROP gadgets
  * other misc utils

**Currently, only listing info about loaded modules is implemented**.  Go to the downloads section to get the most recently compiled extension and pdb. If you need to get to the older/deprecated downloads, search for deprecated downloads on the [downloads page](http://code.google.com/p/narly/downloads/list?can=4). For those of you who might download and use this extension, it would be worth it to check back every now and then for a new release, as a lot is currently in the works (or you could ping me directly).  Also, if you find a bug with this extension, please let me know.

Example:

To "install", download one of the zips from the [download page](http://code.google.com/p/narly/downloads/list), extract narly.dll, and copy it in to the `winext` folder for windbg.  The path to the `winext` folder usually looks something like this

```
C:\Program Files\Debugging Tools for Windows (x86)\winext
```

After you do that, you can `.load narly` to load the extension into windbg (output below). To some people, the `/verbose` or `/debug` option to `!nmod` might be useful (see the VerboseOutput wiki page).

(**NOTE - problems related to [issue #1](http://code.google.com/p/narly/issues/detail?id=1) have been fixed)**

```
0:018> .load narly

      __s|I}*!{a.                        ._s,aan2*a
     _wY1+~-    )S,                     .ae"~=:...:X
   .vXl+:.       -4c                   <2+=|==::..:d
   vvi=;..        -?o,                =2=+==:::...=d
  )nv=:.            )5,              .2=--.......-=d
  ue+::              -*s             <c .        .=d
  m>==::..     ._,     <s,           )c           :d
  #==viii|===; {Xs=,    -{s          )c         ..:d
  Z;{nnonnvvii;v(-{%=.    ~s,        )e:====||iiv%=d
  X={oooonvvIl;3;  -{%,    -*>       )2<onnnnvnnnn>d
  X=)vvvvIliii:3;    -!s.   :)s.     )e<oonvlllllIid
  X=<lllliii|=:n;      -1c.  +|1,    )z<nvii||+|+|vX
  S=<lli|||=:: n;        "nc  -s%;   )c=ovl|++==+=vo
  X=<i||+=; . .n`          "1>.-{%i. )c<Xnnli||++=vn
  X=iii>==-.  :o`            "1,:+iI,)c:Sonnvli||=v(
  X>{ii+;:-  .u(               "o,-{Iw(:nvvvllii=v2
  S=i||;:. .=u(                 -!o,+I(:iiillii|ie`
  2>v|==__su?`                    -?o,-:==||iisv"
  {nvnI!""~                         -!sasvv}""`

             by Nephi Johnson (d0c_s4vage)
                      N for gnarly!

Available commands:

    !nmod     - display /SafeSEH, /GS, DEP, and ASLR info for
                all loaded modules

0:018> !nmod /help
Summary:

    !nmod lists all of the loaded and unloaded modules, displaying
    info on /SafeSEH, NO_SEH, /GS, and ASLR and DEP compatibility

Usage:  !nmod [/v /help]

    /debug -  Display verbose output
    /verbose
    /v

    help   -  Who knows what this might do.  I wouldn't try it if
    /?        I were you though.
0:018> !nmod
00400000 0049c000 IEXPLORE             /SafeSEH ON  /GS *ASLR      C:\Program Files\Internet Explorer\IEXPLORE.EXE
010c0000 010c9000 Normaliz             /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\Normaliz.dll
022d0000 022f9000 msls31               /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\msls31.dll
1b000000 1b00c000 ImgUtil              /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\ImgUtil.dll
1b060000 1b06e000 pngfilt              /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\pngfilt.dll
20000000 202c5000 xpsp2res             NO_SEH                      C:\WINDOWS\system32\xpsp2res.dll
3cea0000 3d450000 mshtml               /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\mshtml.dll
3d930000 3da16000 WININET              /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\WININET.dll
3dfd0000 3e1b8000 iertutil             /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\iertutil.dll
3e1c0000 3ec54000 IEFRAME              /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\IEFRAME.dll
42070000 4209f000 iepeers              /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\iepeers.dll
439b0000 439f0000 ieproxy              /SafeSEH ON  /GS *ASLR *DEP C:\Program Files\Internet Explorer\ieproxy.dll
451f0000 451f6000 xpshims              /SafeSEH ON  /GS *ASLR *DEP C:\Program Files\Internet Explorer\xpshims.dll
5ad70000 5ada8000 uxtheme              /SafeSEH ON  /GS            C:\WINDOWS\system32\uxtheme.dll
5b860000 5b8b4000 NETAPI32             /SafeSEH ON  /GS            C:\WINDOWS\system32\NETAPI32.dll
5d090000 5d127000 comctl32_5d090000    /SafeSEH ON  /GS            C:\WINDOWS\system32\comctl32.dll
606b0000 607bd000 ESENT                /SafeSEH ON  /GS            C:\WINDOWS\system32\ESENT.dll
63380000 63434000 jscript              /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\System32\jscript.dll
662b0000 66308000 hnetcfg              /SafeSEH ON  /GS            C:\WINDOWS\system32\hnetcfg.dll
6d440000 6d44c000 jp2ssv               /SafeSEH ON  /GS            C:\Program Files\Java\jre6\bin\jp2ssv.dll
6dae0000 6daf2000 jqs_plugin           /SafeSEH ON  /GS            C:\Program Files\Java\jre6\lib\deploy\jqs\ie\jqs_plugin.dll
71a50000 71a8f000 mswsock              /SafeSEH ON  /GS            C:\WINDOWS\System32\mswsock.dll
71a90000 71a98000 wshtcpip             /SafeSEH ON  /GS            C:\WINDOWS\System32\wshtcpip.dll
71aa0000 71aa8000 WS2HELP              /SafeSEH ON  /GS            C:\WINDOWS\system32\WS2HELP.dll
71ab0000 71ac7000 ws2_32               /SafeSEH ON  /GS            C:\WINDOWS\system32\ws2_32.dll
71bf0000 71c03000 SAMLIB               /SafeSEH ON  /GS            C:\WINDOWS\system32\SAMLIB.dll
71d40000 71d5c000 actxprxy             NO_SEH                      C:\WINDOWS\system32\actxprxy.dll
722b0000 722b5000 sensapi              NO_SEH                      C:\WINDOWS\system32\sensapi.dll
73000000 73026000 WINSPOOL             /SafeSEH ON  /GS            C:\WINDOWS\system32\WINSPOOL.DRV
73030000 73040000 WZCSAPI              /SafeSEH ON  /GS            C:\WINDOWS\system32\WZCSAPI.DLL
746f0000 7471a000 msimtf               NO_SEH                      C:\WINDOWS\System32\msimtf.dll
74720000 7476b000 MSCTF                /SafeSEH ON  /GS            C:\WINDOWS\system32\MSCTF.dll
755c0000 755ee000 msctfime             /SafeSEH ON  /GS            C:\WINDOWS\system32\msctfime.ime
75cf0000 75d81000 MLANG                /SafeSEH ON  /GS            C:\WINDOWS\system32\MLANG.dll
75e90000 75f40000 SXS                  /SafeSEH ON  /GS            C:\WINDOWS\system32\SXS.DLL
76360000 76370000 WINSTA               /SafeSEH ON  /GS            C:\WINDOWS\system32\WINSTA.dll
76380000 76385000 msimg32              NO_SEH                      C:\WINDOWS\system32\msimg32.dll
76390000 763ad000 IMM32                /SafeSEH ON  /GS            C:\WINDOWS\system32\IMM32.DLL
763b0000 763f9000 comdlg32             /SafeSEH ON  /GS            C:\WINDOWS\system32\comdlg32.dll
76400000 765a6000 netshell             /SafeSEH ON  /GS            C:\WINDOWS\system32\netshell.dll
769c0000 76a73000 USERENV              /SafeSEH ON  /GS            C:\WINDOWS\system32\USERENV.dll
76b20000 76b31000 ATL                  NO_SEH                      C:\WINDOWS\system32\ATL.DLL
76b40000 76b6d000 WINMM                /SafeSEH ON  /GS            C:\WINDOWS\system32\WINMM.dll
76bf0000 76bfb000 PSAPI                /SafeSEH ON  /GS            C:\WINDOWS\system32\PSAPI.DLL
76c00000 76c2e000 credui               /SafeSEH ON  /GS            C:\WINDOWS\system32\credui.dll
76d30000 76d34000 WMI                  NO_SEH                      C:\WINDOWS\system32\WMI.dll
76d40000 76d58000 MPRAPI               /SafeSEH ON  /GS            C:\WINDOWS\system32\MPRAPI.dll
76d60000 76d79000 iphlpapi             /SafeSEH ON  /GS            C:\WINDOWS\system32\iphlpapi.dll
76d80000 76d9e000 DHCPCSVC             /SafeSEH ON  /GS            C:\WINDOWS\system32\DHCPCSVC.DLL
76e10000 76e35000 adsldpc              /SafeSEH ON  /GS            C:\WINDOWS\system32\adsldpc.dll
76e80000 76e8e000 rtutils              /SafeSEH ON  /GS            C:\WINDOWS\system32\rtutils.dll
76e90000 76ea2000 rasman               /SafeSEH ON  /GS            C:\WINDOWS\system32\rasman.dll
76eb0000 76edf000 TAPI32               /SafeSEH ON  /GS            C:\WINDOWS\system32\TAPI32.dll
76ee0000 76f1c000 RASAPI32             /SafeSEH ON  /GS            C:\WINDOWS\system32\RASAPI32.dll
76f20000 76f47000 DNSAPI               /SafeSEH ON  /GS            C:\WINDOWS\system32\DNSAPI.dll
76f50000 76f58000 WTSAPI32             NO_SEH                      C:\WINDOWS\system32\WTSAPI32.dll
76f60000 76f8c000 WLDAP32              /SafeSEH ON  /GS            C:\WINDOWS\system32\WLDAP32.dll
76fc0000 76fc6000 rasadhlp             NO_SEH                      C:\WINDOWS\system32\rasadhlp.dll
76fd0000 7704f000 CLBCATQ              /SafeSEH ON  /GS            C:\WINDOWS\system32\CLBCATQ.DLL
77050000 77115000 COMRes               NO_SEH                      C:\WINDOWS\system32\COMRes.dll
77120000 771ac000 OLEAUT32             /SafeSEH ON  /GS            C:\WINDOWS\system32\OLEAUT32.dll
773d0000 774d2000 comctl32             /SafeSEH ON  /GS            C:\WINDOWS\WinSxS\x86_Microsoft.Windows.Common-Controls_6595b64144ccf1df_6.0.2600.2180_x-ww_a84f1ff9\comctl32.dll
774e0000 7761c000 ole32                /SafeSEH ON  /GS            C:\WINDOWS\system32\ole32.dll
77620000 7768e000 WZCSvc               /SafeSEH ON  /GS            C:\WINDOWS\system32\WZCSvc.DLL
77920000 77a13000 SETUPAPI             /SafeSEH ON  /GS            C:\WINDOWS\system32\SETUPAPI.dll
77a80000 77b14000 CRYPT32              /SafeSEH ON  /GS            C:\WINDOWS\system32\CRYPT32.dll
77b20000 77b32000 MSASN1               NO_SEH                      C:\WINDOWS\system32\MSASN1.dll
77b40000 77b62000 appHelp              /SafeSEH ON  /GS            C:\WINDOWS\system32\appHelp.dll
77c00000 77c08000 VERSION              /SafeSEH ON  /GS            C:\WINDOWS\system32\VERSION.dll
77c10000 77c68000 msvcrt               /SafeSEH ON  /GS            C:\WINDOWS\system32\msvcrt.dll
77c70000 77c93000 msv1_0               /SafeSEH ON  /GS            C:\WINDOWS\system32\msv1_0.dll
77cc0000 77cf2000 ACTIVEDS             /SafeSEH ON  /GS            C:\WINDOWS\system32\ACTIVEDS.dll
77d00000 77d33000 netman               /SafeSEH ON  /GS            C:\WINDOWS\system32\netman.dll
77d40000 77dd0000 USER32               /SafeSEH ON  /GS            C:\WINDOWS\system32\USER32.dll
77dd0000 77e6b000 ADVAPI32             /SafeSEH ON  /GS            C:\WINDOWS\system32\ADVAPI32.dll
77e70000 77f01000 RPCRT4               /SafeSEH ON  /GS            C:\WINDOWS\system32\RPCRT4.dll
77f10000 77f56000 GDI32                /SafeSEH ON  /GS            C:\WINDOWS\system32\GDI32.dll
77f60000 77fd6000 SHLWAPI              /SafeSEH ON  /GS            C:\WINDOWS\system32\SHLWAPI.dll
77fe0000 77ff1000 Secur32              /SafeSEH ON  /GS            C:\WINDOWS\system32\Secur32.dll
78130000 78263000 urlmon               /SafeSEH ON  /GS *ASLR *DEP C:\WINDOWS\system32\urlmon.dll
7c340000 7c396000 MSVCR71              /SafeSEH ON  /GS            C:\Program Files\Java\jre6\bin\MSVCR71.dll
7c800000 7c8f4000 kernel32             /SafeSEH ON  /GS            C:\WINDOWS\system32\kernel32.dll
7c900000 7c9b0000 ntdll                /SafeSEH ON                 C:\WINDOWS\system32\ntdll.dll
7c9c0000 7d1d4000 SHELL32              /SafeSEH ON  /GS            C:\WINDOWS\system32\SHELL32.dll

Unloaded modules:
6cd00000 6cd00000 sqmapi.dll          

*DEP/*ASLR means that these modules are compatible with ASLR/DEP
```

This is only made for Win32 systems.  I would be shocked if it worked on 64-bit Windows systems.

Many thanks to those who have helped me with issues and testing while making this, especially `Chris Rohlf` and `_sinn3r`.