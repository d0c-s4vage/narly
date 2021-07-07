# narly
Automatically exported from code.google.com/p/narly

Author: d0c-s4vage\
Additionally Capabilities: @TheCyberBebop, Shadi Habbal (@Kerpanic)\
Tested on: Windows 10.0.19041.1052 (x86_64)

Updated for VS 2019 and incorporated total size, module rebase/potential to rebase, system file, and header.

Original work all goes to d0c-s4vage for an amazing tool!

<pre><code>0:004> !nmod /b \x00\x0a\x0d\x1a\x20
|Base   |Top     |Size    |Module              |Bad Characters |Rebase  |Potential    |SafeSEH |GS |ASLR |DEP |System File |Path
--------------------------------------------------------------------------------------------------------------------------------
00400000 0054d000 0014d000 DVDXPlayer           *BADCHARS                              OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\DVDXPlayer.EXE
02480000 024a9000 00029000 PowerManagementCtrl  *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\PowerManagementCtrl.dll
024e0000 0250c000 0002c000 FileAssocator        *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\FileAssocator.dll
02510000 02520000 00010000 QTMediaControl       *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\QTMediaControl.dll
02530000 02544000 00014000 RealMediaControl     *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\RealMediaControl.dll
02690000 026a4000 00014000 applog               *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\applog.dll
026c0000 026f0000 00030000 VideoWindow          *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\VideoWindow.dll
02930000 02946000 00016000 DibLibDll            *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\DibLibDll.dll
02950000 0297a000 0002a000 AudioProcess         *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\AudioProcess.dll
02990000 029dd000 0004d000 RecorderCtrl         *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\RecorderCtrl.dll
02b00000 02b8f000 0008f000 FileConverter        *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\FileConverter.dll
02ba0000 02bb4000 00014000 ProfileStore         *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\ProfileStore.DLL
02bd0000 02beb000 0001b000 mlutil               *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\mlutil.dll
02c50000 02cb8000 00068000 ProfileManager       *BADCHARS       *REBASED *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\ProfileManager.dll
10000000 10018000 00018000 SkinScrollBar                                 *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\SkinScrollBar.Dll
55d20000 55d4c000 0002c000 oledlg                                                      ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\oledlg.dll
55d50000 55dbd000 0006d000 WINSPOOL                                                    ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\WINSPOOL.DRV
55dc0000 55f5a000 0019a000 QUARTZ                                                      ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\QUARTZ.dll
567d0000 567e6000 00016000 asycfilt                                                    ON       /GS *ASLR *DEP True         C:\Windows\system32\asycfilt.dll
57610000 57629000 00019000 OLEPRO32                                                    ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\OLEPRO32.DLL
59210000 59238000 00028000 WINMM                                                       ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\WINMM.dll
60300000 603a4000 000a4000 Configuration                                               OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\Configuration.dll
61380000 61414000 00094000 TextShaping                                                 ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\TextShaping.dll
61600000 6169b000 0009b000 EPG                                                         OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\EPG.dll
64000000 6407a000 0007a000 MediaPlayerCtrl                                             OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\MediaPlayerCtrl.dll
64100000 64128000 00028000 NetReg                                                      OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\NetReg.dll
64a00000 64a06000 00006000 MSIMG32                                                     NO_SEH   /GS *ASLR *DEP True         C:\Windows\SYSTEM32\MSIMG32.dll
65b40000 65f9a000 0045a000 WININET                                                     ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\WININET.dll
668b0000 668e2000 00032000 iphlpapi                                                    ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\iphlpapi.dll
67000000 67010000 00010000 VersionInfo                                   *COULD_REBASE OFF                     False        C:\Program Files (x86)\Aviosoft\DVD X Player 5.5 Professional\VersionInfo.dll
67de0000 67ded000 0000d000 UMPDC                                                       ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\UMPDC.dll
67df0000 67e34000 00044000 powrprof                                                    ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\powrprof.dll
6b4d0000 6b4e8000 00018000 profapi                                                     ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\profapi.dll
723f0000 724cb000 000db000 wintypes                                                    ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\wintypes.dll
724d0000 724f9000 00029000 ntmarta                                                     ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\ntmarta.dll
72500000 7277e000 0027e000 CoreUIComponents                                            ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\CoreUIComponents.dll
72780000 7281b000 0009b000 CoreMessaging                                               ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\CoreMessaging.dll
72820000 728d9000 000b9000 textinputframework                                          ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\textinputframework.dll
72d20000 72f30000 00210000 COMCTL32                                                    ON       /GS *ASLR *DEP True         C:\Windows\WinSxS\x86_microsoft.windows.common-controls_6595b64144ccf1df_6.0.19041.844_none_11adecdf30011423\COMCTL32.dll
73d50000 74359000 00609000 windows_storage                                             ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\windows.storage.dll
74360000 744c9000 00169000 gdiplus                                                     ON       /GS *ASLR *DEP True         C:\Windows\WinSxS\x86_microsoft.windows.gdiplus_6595b64144ccf1df_1.1.19041.1023_none_d94e0b13e107593b\gdiplus.dll
749a0000 74a14000 00074000 uxtheme                                                     ON       /GS *ASLR *DEP True         C:\Windows\system32\uxtheme.dll
74a20000 74a44000 00024000 Wldp                                                        ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\Wldp.dll
75270000 75278000 00008000 VERSION                                                     ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\VERSION.dll
75280000 7528f000 0000f000 kernel_appcore                                              ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\kernel.appcore.dll
754d0000 75666000 00196000 USER32                                                      ON       /GS *ASLR *DEP True         C:\Windows\System32\USER32.dll
75670000 75760000 000f0000 KERNEL32                                                    ON       /GS *ASLR *DEP True         C:\Windows\System32\KERNEL32.DLL
75760000 75d13000 005b3000 SHELL32                                                     ON       /GS *ASLR *DEP True         C:\Windows\System32\SHELL32.dll
75d20000 75d43000 00023000 GDI32                                                       NO_SEH   /GS *ASLR *DEP True         C:\Windows\System32\GDI32.dll
75d50000 75f64000 00214000 KERNELBASE                                                  ON       /GS *ASLR *DEP True         C:\Windows\System32\KERNELBASE.dll
75f90000 76211000 00281000 combase                                                     ON       /GS *ASLR *DEP True         C:\Windows\System32\combase.dll
76220000 76303000 000e3000 ole32                                                       ON       /GS *ASLR *DEP True         C:\Windows\System32\ole32.dll
76310000 7634b000 0003b000 cfgmgr32                                                    ON       /GS *ASLR *DEP True         C:\Windows\System32\cfgmgr32.dll
764c0000 76556000 00096000 OLEAUT32                                                    ON       /GS *ASLR *DEP True         C:\Windows\System32\OLEAUT32.dll
76560000 765bf000 0005f000 bcryptPrimitives                                            ON       /GS *ASLR *DEP True         C:\Windows\System32\bcryptPrimitives.dll
765c0000 7666f000 000af000 comdlg32                                                    ON       /GS *ASLR *DEP True         C:\Windows\System32\comdlg32.dll
76670000 766b5000 00045000 SHLWAPI                                                     ON       /GS *ASLR *DEP True         C:\Windows\System32\SHLWAPI.dll
76710000 76735000 00025000 IMM32                                                       ON       /GS *ASLR *DEP True         C:\Windows\System32\IMM32.dll
767a0000 767fe000 0005e000 coml2                                                       ON       /GS *ASLR *DEP True         C:\Windows\System32\coml2.dll
76800000 76875000 00075000 sechost                                                     ON       /GS *ASLR *DEP True         C:\Windows\System32\sechost.dll
76880000 76954000 000d4000 MSCTF                                                       ON       /GS *ASLR *DEP True         C:\Windows\System32\MSCTF.dll
769d0000 76a90000 000c0000 RPCRT4                                                      ON       /GS *ASLR *DEP True         C:\Windows\System32\RPCRT4.dll
76aa0000 76b1a000 0007a000 ADVAPI32                                                    ON       /GS *ASLR *DEP True         C:\Windows\System32\ADVAPI32.dll
76b20000 76bfc000 000dc000 gdi32full                                                   ON       /GS *ASLR *DEP True         C:\Windows\System32\gdi32full.dll
76c00000 76c7b000 0007b000 msvcp_win                                                   ON       /GS *ASLR *DEP True         C:\Windows\System32\msvcp_win.dll
76c80000 76ce3000 00063000 WS2_32                                                      ON       /GS *ASLR *DEP True         C:\Windows\System32\WS2_32.dll
76cf0000 76d09000 00019000 bcrypt                                                      ON       /GS *ASLR *DEP True         C:\Windows\System32\bcrypt.dll
771e0000 771f8000 00018000 win32u                                                      NO_SEH   /GS *ASLR *DEP True         C:\Windows\System32\win32u.dll
77210000 77297000 00087000 shcore                                                      ON       /GS *ASLR *DEP True         C:\Windows\System32\shcore.dll
77320000 773df000 000bf000 msvcrt                                                      ON       /GS *ASLR *DEP True         C:\Windows\System32\msvcrt.dll
773e0000 77500000 00120000 ucrtbase                                                    ON       /GS *ASLR *DEP True         C:\Windows\System32\ucrtbase.dll
77510000 776b3000 001a3000 ntdll                                                       ON       /GS *ASLR *DEP True         C:\Windows\SYSTEM32\ntdll.dll

Unloaded modules:
66600000 66600000 UCM.DLL             
67000000 67010000 VersionInfo.dll     
67000000 67010000 VersionInfo.dll     

*DEP/*ASLR means that these modules are compatible with ASLR/DEP
*COULD_REBASE means that the module has the same base address of another loaded module
*REBASED means the module was rebased and the current base address differs from the original
*BADCHARS are *ONLY* checked agaisnt the most significant byte!</pre></code>
