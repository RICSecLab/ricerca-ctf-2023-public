### Step1: メモリの調査

memory.rawをvolatility3で解析
まずはwinfows.infoでメモリの情報を確認する。
```
> py.exe .\vol.py -f C:\temp\memory.raw windows.info
Volatility 3 Framework 2.4.2
Progress:  100.00               PDB scanning finished
Variable        Value

Kernel Base     0xf80648600000
DTB     0x1ae000
Symbols file:///C:/tools/volatility3-develop/volatility3/symbols/windows/ntkrnlmp.pdb/797E613DB16DB6C0E57795A0CB03F471-1.json.xz
Is64Bit True
IsPAE   False
layer_name      0 WindowsIntel32e
memory_layer    1 FileLayer
KdVersionBlock  0xf806492099b8
Major/Minor     15.22621
MachineType     34404
KeNumberProcessors      4
SystemTime      2023-04-18 08:45:26
NtSystemRoot    C:\Windows
NtProductType   NtProductWinNt
NtMajorVersion  10
NtMinorVersion  0
PE MajorOperatingSystemVersion  10
PE MinorOperatingSystemVersion  0
PE Machine      34404
PE TimeDateStamp        Tue Aug 10 18:00:02 1982
```

pstreeで動作しているプロセスを確認する。
explorer.exeの下にcmd.exeから実行されたpowershell.exeが存在する。
```
> py.exe .\vol.py -f C:\temp\memory.raw windows.pstree
Volatility 3 Framework 2.4.2
Progress:  100.00               PDB scanning finished
PID     PPID    ImageFileName   Offset(V)       Threads Handles SessionId       Wow64   CreateTime      ExitTime

4       0       System  0xd385716fa040  167     -       N/A     False   2023-04-18 08:36:15.000000      N/A
* 104   4       Registry        0xd3857187d080  4       -       N/A     False   2023-04-18 08:36:12.000000      N/A
* 1988  4       MemCompression  0xd38571736040  22      -       N/A     False   2023-04-18 08:36:19.000000      N/A
* 436   4       smss.exe        0xd38574654040  2       -       N/A     False   2023-04-18 08:36:15.000000      N/A
576     568     csrss.exe       0xd385764b2080  10      -       0       False   2023-04-18 08:36:17.000000      N/A
648     568     wininit.exe     0xd385766e5080  2       -       0       False   2023-04-18 08:36:17.000000      N/A
* 792   648     services.exe    0xd385767381c0  10      -       0       False   2023-04-18 08:36:18.000000      N/A
** 7180 792     svchost.exe     0xd38579c57080  7       -       0       False   2023-04-18 08:38:29.000000      N/A
** 1552 792     svchost.exe     0xd38576a7d080  11      -       0       False   2023-04-18 08:36:18.000000      N/A
** 2576 792     svchost.exe     0xd38576f840c0  4       -       0       False   2023-04-18 08:36:19.000000      N/A
** 2096 792     svchost.exe     0xd385717d9080  6       -       0       False   2023-04-18 08:36:19.000000      N/A
** 3640 792     svchost.exe     0xd385779750c0  11      -       1       False   2023-04-18 08:36:24.000000      N/A
** 2104 792     svchost.exe     0xd385791b3080  9       -       0       False   2023-04-18 08:38:29.000000      N/A
*** 7552        2104    MoUsoCoreWorke  0xd3857ad87080  13      -       0       False   2023-04-18 08:44:36.000000     N/A
** 7224 792     svchost.exe     0xd38579fcc080  2       -       1       False   2023-04-18 08:38:29.000000      N/A
** 2108 792     svchost.exe     0xd38579ee7080  1       -       0       False   2023-04-18 08:38:28.000000      N/A
** 1088 792     svchost.exe     0xd38576980080  3       -       0       False   2023-04-18 08:36:18.000000      N/A
** 2116 792     svchost.exe     0xd38576b72080  2       -       0       False   2023-04-18 08:36:19.000000      N/A
** 2124 792     svchost.exe     0xd38576b49080  8       -       0       False   2023-04-18 08:36:19.000000      N/A
** 4692 792     svchost.exe     0xd38577de7080  18      -       1       False   2023-04-18 08:36:25.000000      N/A
** 2132 792     svchost.exe     0xd3857a2ac0c0  8       -       0       False   2023-04-18 08:38:26.000000      N/A
** 3668 792     svchost.exe     0xd3857ad7e080  3       -       0       False   2023-04-18 08:43:27.000000      N/A
** 6756 792     svchost.exe     0xd38579591080  3       -       0       False   2023-04-18 08:40:12.000000      N/A
** 4204 792     svchost.exe     0xd38577c9a0c0  26      -       0       False   2023-04-18 08:36:24.000000      N/A
** 1140 792     svchost.exe     0xd38576c020c0  2       -       0       False   2023-04-18 08:36:18.000000      N/A
** 2164 792     svchost.exe     0xd38576bb7080  5       -       0       False   2023-04-18 08:36:19.000000      N/A
** 1148 792     svchost.exe     0xd38576a020c0  3       -       0       False   2023-04-18 08:36:18.000000      N/A
** 640  792     svchost.exe     0xd38576910080  6       -       0       False   2023-04-18 08:36:18.000000      N/A
*** 668 640     csrss.exe       0xd385766f1140  14      -       1       False   2023-04-18 08:36:17.000000      N/A
*** 748 640     winlogon.exe    0xd38576750080  3       -       1       False   2023-04-18 08:36:17.000000      N/A
**** 952        748     fontdrvhost.ex  0xd385768630c0  5       -       1       False   2023-04-18 08:36:18.000000     N/A
**** 4344       748     userinit.exe    0xd38577cc1080  0       -       1       False   2023-04-18 08:36:24.000000     2023-04-18 08:36:54.000000
***** 4384      4344    explorer.exe    0xd38577cd9080  71      -       1       False   2023-04-18 08:36:24.000000     N/A
****** 5472     4384    OneDrive.exe    0xd38579656080  22      -       1       False   2023-04-18 08:36:45.000000     N/A
****** 2468     4384    VBoxTray.exe    0xd3857998a080  13      -       1       False   2023-04-18 08:36:44.000000     N/A
****** 4484     4384    SecurityHealth  0xd3857997e080  2       -       1       False   2023-04-18 08:36:43.000000     N/A
****** 2788     4384    cmd.exe 0xd385741eb140  2       -       1       False   2023-04-18 08:37:55.000000      N/A
******* 5536    2788    winpmem_mini_x  0xd3857af020c0  3       -       1       False   2023-04-18 08:45:12.000000     N/A
******* 2900    2788    conhost.exe     0xd385741ed140  4       -       1       False   2023-04-18 08:37:55.000000     N/A
****** 4688     4384    regedit.exe     0xd38571e42140  3       -       1       False   2023-04-18 08:39:38.000000     N/A
****** 6772     4384    cmd.exe 0xd3857ae980c0  2       -       1       False   2023-04-18 08:44:16.000000      N/A
******* 1460    6772    conhost.exe     0xd38579426080  6       -       1       False   2023-04-18 08:44:16.000000     N/A
******* 2068    6772    powershell.exe  0xd3857a35e080  20      -       1       False   2023-04-01 08:44:54.000000     N/A
**** 724        748     LogonUI.exe     0xd3857698d1c0  0       -       1       False   2023-04-18 08:36:18.000000     2023-04-18 08:36:31.000000
**** 1028       748     dwm.exe 0xd3857694c080  18      -       1       False   2023-04-18 08:36:18.000000      N/A
** 3712 792     svchost.exe     0xd385778ee080  6       -       1       False   2023-04-18 08:36:24.000000      N/A
** 6276 792     SgrmBroker.exe  0xd385791a60c0  7       -       0       False   2023-04-18 08:38:28.000000      N/A
** 1160 792     svchost.exe     0xd385716f3080  3       -       0       False   2023-04-18 08:36:19.000000      N/A
** 2192 792     SecurityHealth  0xd3857764c080  11      -       0       False   2023-04-18 08:36:43.000000      N/A
** 1684 792     svchost.exe     0xd38576b410c0  6       -       0       False   2023-04-18 08:36:19.000000      N/A
** 2712 792     spoolsv.exe     0xd385771570c0  7       -       0       False   2023-04-18 08:36:19.000000      N/A
** 1176 792     svchost.exe     0xd3857a365080  1       -       0       False   2023-04-18 08:38:28.000000      N/A
** 3760 792     svchost.exe     0xd385778ef080  4       -       1       False   2023-04-18 08:36:24.000000      N/A
** 6336 792     svchost.exe     0xd38579f6e080  5       -       0       False   2023-04-18 08:40:12.000000      N/A
** 2248 792     wlms.exe        0xd385771aa080  2       -       0       False   2023-04-18 08:36:20.000000      N/A
** 6344 792     svchost.exe     0xd3857919e080  0       -       0       False   2023-04-18 08:36:48.000000      2023-04-18 08:42:00.000000
** 2764 792     svchost.exe     0xd385772020c0  13      -       0       False   2023-04-18 08:36:19.000000      N/A
** 1236 792     svchost.exe     0xd38576a0a080  3       -       0       False   2023-04-18 08:36:18.000000      N/A
** 5332 792     svchost.exe     0xd38577f19080  5       -       1       False   2023-04-18 08:36:28.000000      N/A
** 6868 792     svchost.exe     0xd385766ef0c0  2       -       0       False   2023-04-18 08:40:12.000000      N/A
** 1244 792     svchost.exe     0xd38576a0d080  6       -       0       False   2023-04-18 08:36:18.000000      N/A
** 2268 792     svchost.exe     0xd38576dc50c0  6       -       0       False   2023-04-18 08:36:19.000000      N/A
** 1760 792     VBoxService.ex  0xd385717d0080  11      -       0       False   2023-04-18 08:36:19.000000      N/A
** 1252 792     svchost.exe     0xd38576a0b080  18      -       0       False   2023-04-18 08:36:18.000000      N/A
*** 5028        1252    OneDriveStanda  0xd385791af080  7       -       1       False   2023-04-18 08:44:36.000000     N/A
*** 3920        1252    MicrosoftEdgeU  0xd385779d6080  5       -       0       True    2023-04-18 08:36:24.000000     N/A
*** 2640        1252    OneDriveStanda  0xd38579741080  12      -       1       False   2023-04-18 08:44:36.000000     N/A
*** 3896        1252    taskhostw.exe   0xd385779de080  8       -       1       False   2023-04-18 08:36:24.000000     N/A
*** 6712        1252    taskhostw.exe   0xd385777cc0c0  5       -       1       False   2023-04-18 08:37:27.000000     N/A
** 2792 792     svchost.exe     0xd385772790c0  5       -       0       False   2023-04-18 08:36:19.000000      N/A
** 1804 792     svchost.exe     0xd385717c0080  11      -       0       False   2023-04-18 08:36:19.000000      N/A
** 3852 792     svchost.exe     0xd3857ade3080  8       -       0       False   2023-04-18 08:44:36.000000      N/A
** 6924 792     sppsvc.exe      0xd38574144080  10      -       0       False   2023-04-18 08:44:37.000000      N/A
** 2332 792     svchost.exe     0xd385771b9080  18      -       0       False   2023-04-18 08:36:20.000000      N/A
** 3872 792     svchost.exe     0xd385779e20c0  8       -       0       False   2023-04-18 08:36:24.000000      N/A
** 1824 792     svchost.exe     0xd385794e10c0  10      -       0       False   2023-04-18 08:38:26.000000      N/A
** 4900 792     svchost.exe     0xd385779e7080  3       -       0       False   2023-04-18 08:36:26.000000      N/A
*** 7056        4900    consent.exe     0xd385799ac140  0       -       1       False   2023-04-18 08:37:53.000000     2023-04-18 08:37:55.000000
*** 7456        4900    consent.exe     0xd38571e44140  0       -       1       False   2023-04-18 08:39:36.000000     2023-04-18 08:39:38.000000
*** 7604        4900    consent.exe     0xd385796cd140  0       -       1       False   2023-04-18 08:40:19.000000     2023-04-18 08:40:21.000000
** 6948 792     uhssvc.exe      0xd3857a35c080  3       -       0       False   2023-04-18 08:38:28.000000      N/A
** 1840 792     svchost.exe     0xd385717ad080  9       -       0       False   2023-04-18 08:36:19.000000      N/A
** 7984 792     svchost.exe     0xd3857ad970c0  6       -       0       False   2023-04-18 08:40:47.000000      N/A
** 1336 792     svchost.exe     0xd38576c93080  5       -       0       False   2023-04-18 08:36:18.000000      N/A
** 3384 792     svchost.exe     0xd3857758b080  1       -       0       False   2023-04-18 08:36:20.000000      N/A
** 2876 792     svchost.exe     0xd385771020c0  3       -       0       False   2023-04-18 08:36:20.000000      N/A
** 4412 792     svchost.exe     0xd38577cd8080  8       -       0       False   2023-04-18 08:36:24.000000      N/A
** 2376 792     svchost.exe     0xd385771dc080  10      -       0       False   2023-04-18 08:36:20.000000      N/A
** 1892 792     svchost.exe     0xd385717a3080  7       -       0       False   2023-04-18 08:36:19.000000      N/A
** 2916 792     svchost.exe     0xd385773790c0  7       -       0       False   2023-04-18 08:36:20.000000      N/A
** 1900 792     svchost.exe     0xd385717a0080  5       -       0       False   2023-04-18 08:36:19.000000      N/A
** 2412 792     svchost.exe     0xd38576e7a080  3       -       0       False   2023-04-18 08:36:19.000000      N/A
*** 5464        2412    ctfmon.exe      0xd3857971b080  12      -       1       False   2023-04-18 08:36:31.000000     N/A
** 2924 792     svchost.exe     0xd385773680c0  17      -       0       False   2023-04-18 08:36:20.000000      N/A
*** 3500        2924    AggregatorHost  0xd38577583080  1       -       0       False   2023-04-18 08:36:20.000000     N/A
** 4972 792     SearchIndexer.  0xd3857794b080  27      -       0       False   2023-04-18 08:36:26.000000      N/A
** 3952 792     svchost.exe     0xd3857767b0c0  7       -       0       False   2023-04-18 08:36:23.000000      N/A
** 5488 792     svchost.exe     0xd3857a9c4080  5       -       0       False   2023-04-18 08:41:37.000000      N/A
** 1908 792     svchost.exe     0xd3857179e080  3       -       0       False   2023-04-18 08:36:19.000000      N/A
** 7540 792     svchost.exe     0xd385797360c0  4       -       1       False   2023-04-18 08:40:11.000000      N/A
** 2936 792     svchost.exe     0xd38577311080  6       -       0       False   2023-04-18 08:36:20.000000      N/A
** 2944 792     svchost.exe     0xd38577032080  16      -       0       False   2023-04-18 08:36:20.000000      N/A
** 1420 792     svchost.exe     0xd38576cbf080  10      -       0       False   2023-04-18 08:36:18.000000      N/A
*** 3396        1420    sihost.exe      0xd38577962080  15      -       1       False   2023-04-18 08:36:24.000000     N/A
** 1428 792     svchost.exe     0xd38576c7f080  1       -       0       False   2023-04-18 08:36:18.000000      N/A
** 2964 792     svchost.exe     0xd38577064080  6       -       0       False   2023-04-18 08:36:20.000000      N/A
** 932  792     svchost.exe     0xd38576832080  26      -       0       False   2023-04-18 08:36:18.000000      N/A
*** 5368        932     WmiPrvSE.exe    0xd38579fc5080  11      -       0       False   2023-04-18 08:43:26.000000     N/A
*** 7048        932     RuntimeBroker.  0xd3857919d080  6       -       1       False   2023-04-18 08:37:44.000000     N/A
*** 3596        932     OpenConsole.ex  0xd3857624d080  13      -       1       False   2023-04-18 08:44:16.000000     N/A
*** 4112        932     SearchHost.exe  0xd38577f1b080  68      -       1       False   2023-04-18 08:36:27.000000     N/A
*** 5264        932     RuntimeBroker.  0xd38577f16080  13      -       1       False   2023-04-18 08:36:28.000000     N/A
*** 3856        932     WmiPrvSE.exe    0xd3857a36c0c0  6       -       0       False   2023-04-18 08:40:28.000000     N/A
*** 2324        932     smartscreen.ex  0xd38579982080  3       -       1       False   2023-04-18 08:36:43.000000     N/A
*** 6804        932     WindowsTermina  0xd38579cdc080  0       -       1       False   2023-04-18 08:36:53.000000     2023-04-18 08:36:55.000000
*** 7572        932     SecHealthUI.ex  0xd38579e72140  0       -       1       False   2023-04-18 08:40:11.000000     2023-04-18 08:40:26.000000
*** 7316        932     SystemSettings  0xd38579c66080  19      -       1       False   2023-04-18 08:40:29.000000     N/A
**** 2424       7316    SystemSettings  0xd385795860c0  0       -       1       False   2023-04-18 08:40:43.000000     2023-04-18 08:40:46.000000
**** 8032       7316    SystemSettings  0xd3857a61a080  0       -       1       False   2023-04-18 08:44:52.000000     2023-04-01 08:44:52.000000
**** 4396       7316    SystemSettings  0xd3857a6190c0  0       -       1       False   2023-04-18 08:43:28.000000     2023-04-01 08:43:29.000000
**** 3552       7316    SystemSettings  0xd3857972b080  0       -       1       False   2023-04-18 08:44:28.000000     2023-04-01 08:44:29.000000
*** 7576        932     ApplicationFra  0xd38579e650c0  14      -       1       False   2023-04-18 08:40:11.000000     N/A
*** 6816        932     WindowsTermina  0xd3857a2c7080  0       -       1       False   2023-04-18 08:38:02.000000     2023-04-18 08:38:55.000000
*** 6968        932     WindowsTermina  0xd385791950c0  0       -       1       False   2023-04-18 08:36:54.000000     2023-04-18 08:36:55.000000
*** 5176        932     RuntimeBroker.  0xd38577f17080  2       -       1       False   2023-04-18 08:36:28.000000     N/A
*** 5568        932     dllhost.exe     0xd38577f14080  11      -       1       False   2023-04-18 08:36:29.000000     N/A
*** 6208        932     RuntimeBroker.  0xd385764c20c0  11      -       1       False   2023-04-18 08:44:23.000000     N/A
*** 4820        932     ShellExperienc  0xd3857417d080  17      -       1       False   2023-04-18 08:44:23.000000     N/A
*** 4572        932     Widgets.exe     0xd38577f18080  15      -       1       False   2023-04-18 08:36:28.000000     N/A
**** 3020       4572    msedgewebview2  0xd3857a9640c0  27      -       1       False   2023-04-18 08:41:34.000000     N/A
***** 5924      3020    msedgewebview2  0xd385741990c0  7       -       1       False   2023-04-18 08:41:35.000000     N/A
***** 4100      3020    msedgewebview2  0xd3857419c100  13      -       1       False   2023-04-18 08:41:36.000000     N/A
***** 1640      3020    msedgewebview2  0xd3857a966080  15      -       1       False   2023-04-18 08:41:36.000000     N/A
***** 2384      3020    msedgewebview2  0xd3857ad84080  6       -       1       False   2023-04-18 08:41:35.000000     N/A
***** 7764      3020    msedgewebview2  0xd385741b7080  9       -       1       False   2023-04-18 08:41:35.000000     N/A
*** 6624        932     WindowsTermina  0xd38579e6d080  0       -       1       False   2023-04-18 08:36:52.000000     2023-04-18 08:36:54.000000
*** 4196        932     dllhost.exe     0xd385796d1140  6       -       1       False   2023-04-18 08:39:16.000000     N/A
*** 8164        932     WindowsTermina  0xd385791a1080  0       -       1       False   2023-04-18 08:42:33.000000     2023-04-18 08:44:12.000000
*** 7276        932     WindowsTermina  0xd3857ac14080  21      -       1       False   2023-04-18 08:44:16.000000     N/A
*** 4088        932     StartMenuExper  0xd38577f1a080  13      -       1       False   2023-04-18 08:36:27.000000     N/A
*** 7164        932     WindowsTermina  0xd385796af080  0       -       1       False   2023-04-18 08:37:44.000000     2023-04-18 08:42:29.000000
** 1472 792     svchost.exe     0xd38576a1f080  6       -       0       False   2023-04-18 08:36:18.000000      N/A
** 452  792     svchost.exe     0xd385716e2080  6       -       0       False   2023-04-18 08:36:19.000000      N/A
** 5060 792     svchost.exe     0xd38577cdc080  5       -       0       False   2023-04-18 08:36:27.000000      N/A
** 4036 792     svchost.exe     0xd3857919b100  4       -       0       False   2023-04-18 08:36:56.000000      N/A
** 6084 792     svchost.exe     0xd38579595080  21      -       0       False   2023-04-18 08:43:26.000000      N/A
** 2512 792     svchost.exe     0xd38576f3c140  3       -       0       False   2023-04-18 08:36:19.000000      N/A
** 472  792     svchost.exe     0xd385768e7080  12      -       0       False   2023-04-18 08:36:18.000000      N/A
** 2520 792     svchost.exe     0xd38576f350c0  5       -       0       False   2023-04-18 08:36:19.000000      N/A
** 1500 792     svchost.exe     0xd385793b9080  6       -       0       False   2023-04-18 08:40:46.000000      N/A
** 3040 792     sqlwriter.exe   0xd385770ee080  4       -       0       False   2023-04-18 08:36:20.000000      N/A
** 2020 792     MsMpEng.exe     0xd38577188080  11      -       0       False   2023-04-18 08:36:20.000000      N/A
** 4072 792     svchost.exe     0xd385778bc080  8       -       0       False   2023-04-18 08:36:23.000000      N/A
** 3560 792     svchost.exe     0xd385793b8080  0       -       0       False   2023-04-18 08:40:46.000000      2023-04-18 08:40:52.000000
** 6644 792     svchost.exe     0xd38576326080  18      -       0       False   2023-04-18 08:38:04.000000      N/A
** 3068 792     svchost.exe     0xd38577199080  3       -       0       False   2023-04-18 08:36:20.000000      N/A
* 816   648     lsass.exe       0xd3857673c180  10      -       0       False   2023-04-18 08:36:18.000000      N/A
* 964   648     fontdrvhost.ex  0xd38576868080  5       -       0       False   2023-04-18 08:36:18.000000      N/A
6576    2612    Microsoft.Shar  0xd38579d130c0  11      -       1       False   2023-04-18 08:43:33.000000      N/A
```

cmdlineコマンドでそれぞれのコマンドライン引数を確認する。
powershell.exeの引数にbase64された長い文字列が存在するため、不審であると判断できる。

```
> py.exe .\vol.py -f C:\temp\memory.raw windows.cmdline
Volatility 3 Framework 2.4.2
Progress:  100.00               PDB scanning finished
PID     Process Args

4       System  Required memory at 0x20 is not valid (process exited?)
104     Registry        Required memory at 0x20 is not valid (process exited?)
436     smss.exe        \SystemRoot\System32\smss.exe
576     csrss.exe       %SystemRoot%\system32\csrss.exe ObjectDirectory=\Windows SharedSection=1024,20480,768 Windows=On SubSystemType=Windows ServerDll=basesrv,1 ServerDll=winsrv:UserServerDllInitialization,3 ServerDll=sxssrv,4 ProfileControl=Off MaxRequestThreads=16
648     wininit.exe     wininit.exe
668     csrss.exe       %SystemRoot%\system32\csrss.exe ObjectDirectory=\Windows SharedSection=1024,20480,768 Windows=On SubSystemType=Windows ServerDll=basesrv,1 ServerDll=winsrv:UserServerDllInitialization,3 ServerDll=sxssrv,4 ProfileControl=Off MaxRequestThreads=16
748     winlogon.exe    winlogon.exe
792     services.exe    C:\Windows\system32\services.exe
816     lsass.exe       C:\Windows\system32\lsass.exe
932     svchost.exe     C:\Windows\system32\svchost.exe -k DcomLaunch -p
952     fontdrvhost.ex  "fontdrvhost.exe"
964     fontdrvhost.ex  "fontdrvhost.exe"
472     svchost.exe     C:\Windows\system32\svchost.exe -k RPCSS -p
640     svchost.exe     C:\Windows\system32\svchost.exe -k DcomLaunch -p -s LSM
724     LogonUI.exe     Required memory at 0x3ec3be0020 is not valid (process exited?)
1028    dwm.exe "dwm.exe"
1088    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s gpsvc
1140    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNoNetwork -p
1148    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNetworkRestricted -p -s lmhosts
1236    svchost.exe     C:\Windows\System32\svchost.exe -k LocalSystemNetworkRestricted -p -s NcbService
1244    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNetworkRestricted -p -s TimeBrokerSvc
1252    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s Schedule
1336    svchost.exe     C:\Windows\system32\svchost.exe -k UserProfileService -p -s ProfSvc
1420    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s UserManager
1428    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s DispBrokerDesktopSvc
1472    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s nsi
1552    svchost.exe     C:\Windows\System32\svchost.exe -k netprofm -p -s netprofm
1760    VBoxService.ex  C:\Windows\System32\VBoxService.exe
1804    svchost.exe     C:\Windows\system32\svchost.exe -k NetworkService -p
1840    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNetworkRestricted -p -s EventLog
1892    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s EventSystem
1900    svchost.exe     C:\Windows\system32\svchost.exe -k LocalSystemNetworkRestricted -p -s SysMain
1908    svchost.exe     C:\Windows\System32\svchost.exe -k netsvcs -p -s Themes
1988    MemCompression  Required memory at 0x20 is not valid (process exited?)
1160    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s SENS
1684    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNetworkRestricted -p -s Dhcp
452     svchost.exe     C:\Windows\system32\svchost.exe -k appmodel -p -s StateRepository
2096    svchost.exe     C:\Windows\system32\svchost.exe -k NetSvcs -p -s hns
2116    svchost.exe     C:\Windows\System32\svchost.exe -k LocalSystemNetworkRestricted -p -s AudioEndpointBuilder
2124    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s FontCache
2164    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNetworkRestricted -p -s WinHttpAutoProxySvc
2268    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNetworkRestricted -p
2412    svchost.exe     C:\Windows\System32\svchost.exe -k LocalSystemNetworkRestricted -p -s TextInputManagementService
2512    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNetworkRestricted -p
2520    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNetworkRestricted -p
2576    svchost.exe     C:\Windows\System32\svchost.exe -k netsvcs -p -s ShellHWDetection
2712    spoolsv.exe     C:\Windows\System32\spoolsv.exe
2764    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNoNetworkFirewall -p
2792    svchost.exe     C:\Windows\System32\svchost.exe -k NetworkService -p -s LanmanWorkstation
2876    svchost.exe     C:\Windows\system32\svchost.exe -k NetSvcs -s nvagent
2916    svchost.exe     C:\Windows\system32\svchost.exe -k NetworkService -p
2924    svchost.exe     C:\Windows\System32\svchost.exe -k utcsvc -p
2936    svchost.exe     C:\Windows\System32\svchost.exe -k NetSvcs -p -s iphlpsvc
2944    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNoNetwork -p -s DPS
2964    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s LanmanServer
3040    sqlwriter.exe   "C:\Program Files\Microsoft SQL Server\90\Shared\sqlwriter.exe"
3068    svchost.exe     C:\Windows\System32\svchost.exe -k LocalSystemNetworkRestricted -p -s TrkWks
2020    MsMpEng.exe     "C:\Program Files\Windows Defender\MsMpEng.exe"
2248    wlms.exe        C:\Windows\system32\wlms\wlms.exe
2332    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s Winmgmt
2376    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s WpnService
3384    svchost.exe     C:\Windows\System32\svchost.exe -k netsvcs -p -s SharedAccess
3500    AggregatorHost  AggregatorHost.exe
3952    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNetworkRestricted -s RmSvc
4072    svchost.exe     C:\Windows\system32\svchost.exe -k WebThreatDefense -p -s webthreatdefsvc
3396    sihost.exe      sihost.exe
3640    svchost.exe     C:\Windows\system32\svchost.exe -k UnistackSvcGroup -s CDPUserSvc
3760    svchost.exe     C:\Windows\system32\svchost.exe -k LocalSystemNetworkRestricted -p -s webthreatdefusersvc
3712    svchost.exe     C:\Windows\system32\svchost.exe -k UnistackSvcGroup -s WpnUserService
3872    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s TokenBroker
3920    MicrosoftEdgeU  "C:\Program Files (x86)\Microsoft\EdgeUpdate\MicrosoftEdgeUpdate.exe" /c
3896    taskhostw.exe   taskhostw.exe {222A245B-E637-4AE9-A93F-A59CA119A75E}
4204    svchost.exe     C:\Windows\system32\svchost.exe -k wsappx -p -s AppXSvc
4344    userinit.exe    Required memory at 0x921eaf6020 is not valid (process exited?)
4384    explorer.exe    C:\Windows\Explorer.EXE
4412    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s CDPSvc
4692    svchost.exe     C:\Windows\system32\svchost.exe -k ClipboardSvcGroup -p -s cbdhsvc
4900    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s Appinfo
4972    SearchIndexer.  C:\Windows\system32\SearchIndexer.exe /Embedding
5060    svchost.exe     C:\Windows\system32\svchost.exe -k osprivacy -p -s camsvc
4112    SearchHost.exe  Required memory at 0xa16ae91020 is inaccessible (swapped)
4088    StartMenuExper  "C:\Windows\SystemApps\Microsoft.Windows.StartMenuExperienceHost_cw5n1h2txyewy\StartMenuExperienceHost.exe" -ServerName:App.AppXywbrabmsek0gm3tkwpr5kwzbs55tkqay.mca
4572    Widgets.exe     "C:\Program Files\WindowsApps\MicrosoftWindows.Client.WebExperience_423.3400.0.0_x64__cw5n1h2txyewy\Dashboard\Widgets.exe" -ServerName:Microsoft.Windows.DashboardServer
5176    RuntimeBroker.  C:\Windows\System32\RuntimeBroker.exe -Embedding
5264    RuntimeBroker.  C:\Windows\System32\RuntimeBroker.exe -Embedding
5332    svchost.exe     C:\Windows\system32\svchost.exe -k UdkSvcGroup -s UdkUserSvc
5568    dllhost.exe     C:\Windows\system32\DllHost.exe /Processid:{973D20D7-562D-44B9-B70B-5A0F49CCDF3F}
5464    ctfmon.exe      "ctfmon.exe"
2324    smartscreen.ex  C:\Windows\System32\smartscreen.exe -Embedding
4484    SecurityHealth  "C:\Windows\System32\SecurityHealthSystray.exe"
2192    SecurityHealth  C:\Windows\system32\SecurityHealthService.exe
2468    VBoxTray.exe    "C:\Windows\System32\VBoxTray.exe"
5472    OneDrive.exe    "C:\Users\User\AppData\Local\Microsoft\OneDrive\OneDrive.exe" /background
6344    svchost.exe     Required memory at 0x159275d020 is not valid (process exited?)
6624    WindowsTermina  Required memory at 0x87be78c020 is not valid (process exited?)
6804    WindowsTermina  Required memory at 0x7b3cd40020 is not valid (process exited?)
6968    WindowsTermina  Required memory at 0x3a375c2020 is not valid (process exited?)
4036    svchost.exe     C:\Windows\System32\svchost.exe -k LocalService -p -s LicenseManager
6712    taskhostw.exe   taskhostw.exe $(Arg0)
7164    WindowsTermina  Required memory at 0xd5187f3020 is not valid (process exited?)
7048    RuntimeBroker.  C:\Windows\System32\RuntimeBroker.exe -Embedding
7056    consent.exe     Required memory at 0xe40573c020 is not valid (process exited?)
2788    cmd.exe "C:\Windows\system32\cmd.exe"
2900    conhost.exe     \??\C:\Windows\system32\conhost.exe 0x4
6816    WindowsTermina  Required memory at 0xc53c621020 is not valid (process exited?)
6644    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s wuauserv
1824    svchost.exe     C:\Windows\System32\svchost.exe -k NetworkService -p
2132    svchost.exe     C:\Windows\system32\svchost.exe -k LocalSystemNetworkRestricted -p -s PcaSvc
6276    SgrmBroker.exe  C:\Windows\system32\Sgrm\SgrmBroker.exe
2108    svchost.exe     C:\Windows\System32\svchost.exe -k LocalSystemNetworkRestricted -p -s StorSvc
1176    svchost.exe     C:\Windows\System32\svchost.exe -k wsappx -p -s ClipSVC
6948    uhssvc.exe      "C:\Program Files\Microsoft Update Health Tools\uhssvc.exe"
2104    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s UsoSvc
7180    svchost.exe     C:\Windows\System32\svchost.exe -k LocalServiceNetworkRestricted -p -s wscsvc
7224    svchost.exe     C:\Windows\system32\svchost.exe -k UnistackSvcGroup
4196    dllhost.exe     C:\Windows\system32\DllHost.exe /Processid:{AB8902B4-09CA-4BB6-B78D-A8F59079A8D5}
7456    consent.exe     Required memory at 0xd128e99020 is not valid (process exited?)
4688    regedit.exe     "C:\Windows\regedit.exe"
7572    SecHealthUI.ex  Required memory at 0x5a9f441020 is not valid (process exited?)
7576    ApplicationFra  C:\Windows\system32\ApplicationFrameHost.exe -Embedding
7540    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s NPSMSvc
6868    svchost.exe     C:\Windows\system32\svchost.exe -k LocalService -p -s BthAvctpSvc
6756    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceNetworkRestricted -p -s NgcCtnrSvc
6336    svchost.exe     C:\Windows\system32\svchost.exe -k WbioSvcGroup -s WbioSrvc
7604    consent.exe     Required memory at 0xb59b439020 is not valid (process exited?)
3856    WmiPrvSE.exe    C:\Windows\system32\wbem\wmiprvse.exe
7316    SystemSettings  "C:\Windows\ImmersiveControlPanel\SystemSettings.exe" -ServerName:microsoft.windows.immersivecontrolpanel
2424    SystemSettings  Required memory at 0xe7b9dbe020 is not valid (process exited?)
3560    svchost.exe     Required memory at 0x616bf99020 is not valid (process exited?)
1500    svchost.exe     C:\Windows\system32\svchost.exe -k InvSvcGroup -p -s InventorySvc
7984    svchost.exe     C:\Windows\system32\svchost.exe -k LocalServiceAndNoImpersonation -p -s SSDPSRV
3020    msedgewebview2  "C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --embedded-browser-webview=1 --webview-exe-name=Widgets.exe --webview-exe-version=421.20070.1260.0 --user-data-dir="C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView" --noerrdialogs --disk-cache-size=52428800 --edge-webview-is-background --enable-features=msWebView2TreatAppSuspendAsDeviceSuspend,UseNativeThreadPool,UseBackgroundNativeThreadPool --lang=en-US --mojo-named-platform-channel-pipe=4572.7696.2961028307967558830
5924    msedgewebview2  "C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --type=crashpad-handler --user-data-dir=C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView /prefetch:7 --monitor-self-annotation=ptype=crashpad-handler --database=C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView\Crashpad --annotation=IsOfficialBuild=1 --annotation=channel= --annotation=chromium-version=110.0.5481.192 "--annotation=exe=C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --annotation=plat=Win64 "--annotation=prod=Edge WebView2" --annotation=ver=110.0.1587.69 --initial-client-data=0x124,0x128,0x12c,0x100,0xd0,0x7ffe47ea6750,0x7ffe47ea6760,0x7ffe47ea6770
7764    msedgewebview2  "C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --type=utility --utility-sub-type=network.mojom.NetworkService --lang=en-US --service-sandbox-type=none --noerrdialogs --user-data-dir="C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView" --webview-exe-name=Widgets.exe --webview-exe-version=421.20070.1260.0 --embedded-browser-webview=1 --mojo-platform-channel-handle=2200 --field-trial-handle=1912,i,11774737830554998915,835539642237723819,131072 --enable-features=UseBackgroundNativeThreadPool,UseNativeThreadPool,msWebView2TreatAppSuspendAsDeviceSuspend /prefetch:3
2384    msedgewebview2  "C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --type=utility --utility-sub-type=storage.mojom.StorageService --lang=en-US --service-sandbox-type=service --noerrdialogs --user-data-dir="C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView" --webview-exe-name=Widgets.exe --webview-exe-version=421.20070.1260.0 --embedded-browser-webview=1 --mojo-platform-channel-handle=2388 --field-trial-handle=1912,i,11774737830554998915,835539642237723819,131072 --enable-features=UseBackgroundNativeThreadPool,UseNativeThreadPool,msWebView2TreatAppSuspendAsDeviceSuspend /prefetch:8
4100    msedgewebview2  "C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --type=renderer --noerrdialogs --user-data-dir="C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView" --webview-exe-name=Widgets.exe --webview-exe-version=421.20070.1260.0 --embedded-browser-webview=1 --first-renderer-process --lang=en-US --device-scale-factor=1 --num-raster-threads=2 --enable-main-frame-before-activation --renderer-client-id=5 --js-flags="--harmony-weak-refs-with-cleanup-some --expose-gc --ms-user-locale=" --time-ticks-at-unix-epoch=-1681806976713676 --launch-time-ticks=319353500 --mojo-platform-channel-handle=3152 --field-trial-handle=1912,i,11774737830554998915,835539642237723819,131072 --enable-features=UseBackgroundNativeThreadPool,UseNativeThreadPool,msWebView2TreatAppSuspendAsDeviceSuspend /prefetch:1
1640    msedgewebview2  "C:\Program Files (x86)\Microsoft\EdgeWebView\Application\110.0.1587.69\msedgewebview2.exe" --type=gpu-process --noerrdialogs --user-data-dir="C:\Users\User\AppData\Local\Packages\MicrosoftWindows.Client.WebExperience_cw5n1h2txyewy\LocalState\EBWebView" --webview-exe-name=Widgets.exe --webview-exe-version=421.20070.1260.0 --embedded-browser-webview=1 --gpu-preferences=UAAAAAAAAADgAAAYAAAAAAAAAAAAAAAAAABgAAAAAAAwAAAAAAAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAAEgAAAAAAAAASAAAAAAAAAAYAAAAAgAAABAAAAAAAAAAGAAAAAAAAAAQAAAAAAAAAAAAAAAOAAAAEAAAAAAAAAABAAAADgAAAAgAAAAAAAAACAAAAAAAAAA= --use-gl=angle --use-angle=swiftshader-webgl --mojo-platform-channel-handle=3168 --field-trial-handle=1912,i,11774737830554998915,835539642237723819,131072 --enable-features=UseBackgroundNativeThreadPool,UseNativeThreadPool,msWebView2TreatAppSuspendAsDeviceSuspend /prefetch:2
5488    svchost.exe     C:\Windows\system32\svchost.exe -k netsvcs -p -s lfsvc
8164    WindowsTermina  Required memory at 0xb64ab60020 is not valid (process exited?)
4396    SystemSettings  Required memory at 0x2765af4020 is not valid (process exited?)
6084    svchost.exe     C:\Windows\System32\svchost.exe -k netsvcs -p -s BITS
5368    WmiPrvSE.exe    C:\Windows\system32\wbem\wmiprvse.exe
3668    svchost.exe     C:\Windows\system32\svchost.exe -k LocalSystemNetworkRestricted -p -s NgcSvc
6576    Microsoft.Shar  "C:\Users\User\AppData\Local\Microsoft\OneDrive\23.076.0409.0001\Microsoft.SharePoint.exe" /silentConfig
6772    cmd.exe "C:\Windows\system32\cmd.exe"
1460    conhost.exe     \??\C:\Windows\system32\conhost.exe 0x4
3596    OpenConsole.ex  "C:\Program Files\WindowsApps\Microsoft.WindowsTerminal_1.16.10262.0_x64__8wekyb3d8bbwe\OpenConsole.exe" -Embedding
7276    WindowsTermina  "C:\Program Files\WindowsApps\Microsoft.WindowsTerminal_1.16.10262.0_x64__8wekyb3d8bbwe\WindowsTerminal.exe" -Embedding
4820    ShellExperienc  "C:\Windows\SystemApps\ShellExperienceHost_cw5n1h2txyewy\ShellExperienceHost.exe" -ServerName:App.AppXtk181tbxbce2qsex02s8tw7hfxa9xb3t.mca
6208    RuntimeBroker.  C:\Windows\System32\RuntimeBroker.exe -Embedding
3552    SystemSettings  Required memory at 0x28c3184020 is not valid (process exited?)
5028    OneDriveStanda  "C:\Users\User\AppData\Local\Microsoft\OneDrive\OneDriveStandaloneUpdater.exe"
2640    OneDriveStanda  "C:\Users\User\AppData\Local\Microsoft\OneDrive\OneDriveStandaloneUpdater.exe" /reporting
7552    MoUsoCoreWorke  C:\Windows\uus\AMD64\MoUsoCoreWorker.exe
3852    svchost.exe     C:\Windows\system32\svchost.exe -k wusvcs -p -s WaaSMedicSvc
6924    sppsvc.exe      C:\Windows\system32\sppsvc.exe
8032    SystemSettings  Required memory at 0x4f4c01a020 is not valid (process exited?)
2068    powershell.exe  pOwERsHEll  -eP bYpASs -e JgAgACgAIAAkAFAAcwBIAE8AbQBlAFsANABdACsAJABwAHMASABvAE0ARQBbADMANABdACsAJwBYACcAKQAoACAATgBFAFcALQBvAEIAagBFAEMAdAAgAEkATwAuAEMATwBtAFAAcgBFAHMAcwBpAG8ATgAuAEQAZQBmAGwAYQB0AEUAUwBUAHIAZQBhAE0AKABbAHMAeQBTAHQARQBNAC4ASQBvAC4ATQBlAG0ATwBSAFkAUwB0AHIAZQBBAE0AXQAgAFsAQwBvAE4AdgBFAHIAVABdADoAOgBmAFIAbwBNAEIAQQBTAGUANgA0AFMAdABSAGkATgBnACgAJwBmAFYAZABaAGMAOQBwAEkARQBQADQAcgBVADYAbgBkAEkAQgBXAEkAUQBnAGYAWQBRAFAAawBCAFkAOQBtAFEAbQBHAE0AQgB1ACsASwBsAGUASgBEAGwAdwBTAGoARwBFAGgAYQBLAGIAVQBxAGwALwA3ADUAZgB6AHkARgBJAEgAagBaAGwATgBEADAAOQAzAFQAMwBUAGQANABmAFYAbQBjAEgAKwBlAHYAZgBUAHgAOABtAGUAVAAxAFAALwBtAHMALwA0AE8AUABUAHIAaQAyAFMALwBTAEkAZgB4AHMAMgBFAHUANwBaAHEANwBxAGwAWgArAFYASwB5AGYAawAyAGgAYwBxAFoAZwBHAC8AbgAzAEoAbgBYAGEAUgBOADQAdgBjAFAAYwBlAEMAMQBTADUAeQByADEAWABrAHoAaABsACsAKwBBAFAAbwB1AHYAZwBSAEcAcQB1AEQARgBmAFMARQBwAFYAUAB3AHUATgBpADYASAB2AGkASQBsADIAUQBBAGIAbwBMAFMAQgBvADAASABJAFkAUQBDAGsAdwAxAFUAcwB3AEUAVwB1AGcAcABvAEYAOABkAE4ARQBrAEYAQwBzAFIASQBIAEoASQBIAFoAQgBWAFUAVABGAEIANgAyAEIARQBLAEEAZwA5AFcAagBIAHcAZwA5AEMASABOAEEANQB0AEYAOQB0AEsAZQA3ADYAWABXAGcAcwAwAEYAagBnADcAVQBKADQAVgBoAHMAawB0AFkAcwB2AGwAagByAFMAagA2ADkAKwAwAHkAVAB6AFgAeABRAHgAZQAvAHoAMABWAG8AVgBVAGEANQAyAE8ARgBrAFcAagAwAFIAdwBRAFYAaQB4AHYAYQBRAGwATgA2AHQAVgBpAGUAaABlAEQANABQAE4ANAB2ADMAaAAyADAAMwBzADQAMwB0AGIAcQBWAFgAQQB5AEgAZwAvADIATwA3ADQAegBQAEwAYwAxAFMAegBZADkASgBjADEAcwAzAEUAbQBvAGEAcQByAGcAYgBPADIAQgBJAHkAUwBtAHIAWABjAEYAUQBRAE0AdQBrAFcAMwAwAFcAaQB4AC8AVgBPAGMAaABIAHgAdQBNAFgAUAAzAEUAbQAzAG4AVgBwAFkARwAyAFIAeABnAGIAZgBjAEMASwBnAEQAWgBUAHUANgBpAFEAOQBxAHYASAA3AEkAbwAvAFIAVgBpAHMANwBZAFkASABsAFUANABlAGQASABLAGkAMgBaAGUAdABQAFAAQwB6AFEAcwA3AEwAeABwADUAYwBaAFkAWABZAEIAVQA4AC8AQwBjACsAYgBHADAAcAAyAGcAYQBSAEEARABiAHEAUwBuAGwAMgB3AFkAbwBOAFYARgBMAGIAdQBkAEMAVwBYAHAATAB5AHAAKwBnADkAVQBUAGYAegBIAGoANgBiAE8AWQBTAHkAMwBHAEQATABHAGIALwBoAFAAMQBhAGQAegBtAHMAdgA2AHcALwA4AHYAZgBIAHYAMQBZADAASgBaAHYAeQBOAG8AOABrADMAYQA5AFYAMABhAGsAMgA3ADUAaQAzADcALwBoAFEAcwBVAHYATAB6AG0ATgAvAGkANAByAHEAMABOAEsAcwAxAFcARQAyAEMAQgBuADkASgAzAHUATgBoAG4AUwA3AGQAeAAwAEYASwBOADAAbgA3AEUAbAB2AEcAOQB6AGsAegBiAGYAYgBHAEwAWABZAEkAcgB1AG8AbQB6ADQASQByAEsAKwBNADMAQgBuAHUASwBBADQAdAA1ADcARQAwAFMARgB3AE0AaAA5ADQASwBzAGMAdQBEAFEANgBFAFgAYwAxAHAATQBLAG0AYwBWADMAZQBaAGMAUwBlADMATABsAFQAcQBPAGkAbQBvAEwASQA1AHYAeABHAHEANQA0AGQATABvAFcANQByADkAWABwAG4ANABZAHMANwBvAFIAawB3AEkATgA5AFEASwBiADAARgA3ACsAbQBJADYAdwBUAC8ARQBMAHgAQwBIAEQAaABrAFQAQwB5AHMAQQBiADUAZgBxAGYAOQBFADMAeABrADYAMgBUAHUAVAAzAFkAdgBTAHIAegBBAHIAdABYAGwAMQA0AHMAKwBIAFEAbgA0AEUAeQB4AFMAUwBlAEcAZgBWADQAWAAyAHoANgA4AFgAZAAvAFgAcwBVADcASAB6AFIAYgAxADgAKwBQADYAZwA0AGkAaAA2AFYAbQBzAGMAUABTAFYAaABUAEIAZABBAEcAQwB5ADYAeQBlAEoAawBkAEcASgBUAFkAdwAwAHYARAB3AHkARAB3AGEATwBNAHoARQBGAGgASQBvAEIAMABlAEQAUABJAEYAcwBuAFcAWAB5ADgASQBaAFYAcgBmAGsAaQBoAG0AMAB1AGsAbQBPADAAcwB6ADkAdABWAGcAdwB4AEgARQAxAGcAcwB1AFAAVQBGADYAMABwAFAAZwBrAHQASgAwADkANwBEAEoAOABNAFEAeABvAEsARwBEAG8AUABCAHkAVwBKAFgAaQBxADcAZwBDAGkAWgBEAFEAVgBWAHkAbQB3AFgARQBBAGcAZwBhAGkAKwAxAHcAWQBYAGUAUgBLAEYAaQBxAHQASABpAGYAVwBCAHgAKwBMAGQAQwBGAFAAcABNAGsAYQBEAHEAYwBRADEAdQBlAFAAdABqAGEAbwBxACsAMABNADIAagAzADIAeAB0AGQAdQA4AGUAUgBMAG8ANQBJAEgARgArAC8AawBtAEMAZQBpADEAcwA5AFgAaQBUAGoAMQBrAGIAbgBNADEARwA4AFMAdQBDAEUAUgA2ACsAegBrADkATQBxADAAYgB4AEUATgBvAEoAZQBJAEQAdABmAE0ARwBJADQAZQBlAFAAegBlADYAVQA5AEcAMAA3AHUARgBQAHgAdgAzAFIAagA2AHoAKwBCAHUAWgBlAEQAYgBzAHoALwAwACsAWgBZACsAKwBqAEEAUgBGADcAeQBsAFgATQB1AGYASgBTAFgAUwBLAFkASgBWAHIAdABqAHQAbwA1AGUAYgBhADMAOAA4ADYAVwBTAEYAcgBqAEYAZQBZAEQAbABXAGUAUQBiAGgAYwBQAGMAZgBEADIAVwBLAFAANgB1AFEAMQBKAGEAWgBxADIANwBhAEMAdgBJAGEAQwBEAEkAcABnAEgAdgBhADIAVQA3AEoALwBTAGoANABTAFIAcgB4AFcAVQBwAE4ATgBSADAARgAzAGEAbAAzADAAagAvAGsAaQBnAGoAYgBaAEoAMgBrAFkASwBlAFMAbwBwAFkAQgBrAG8ANwBWAHAASgBaAHQATQBnAGYAMwB2AG0AaQB1AFoAdAB4AFMAVQBCAGgAOQBsAHQAYQBEADkAUwA1AGgAcwBMADcAZQBCAE8ASgBXAFYAVQBOAGMAcwBWAGYAdABrAHMAVgBOAEkAUgA2ADAAeQBLAGUARgBWAEcAWQBYADgAMQB6AGEANABsADcAVQAxADUAbQBWAGUAUABjAG0ATQBSAGwARwBYAFQARgBwAEkAbQBkAFcATQB2AHcAWQA2AFIAZABWAFoASABGADIALwBJAHIAUQAwAHAAeQBvAEMAVgBIAE4AUABiADYAWQA4AG4AMgAvADQANwBlADMAdwBhAG0AbQB2AHEAbgBBACsANwBiAFkAUgBkAHUAaQA5ADEASABzAG8AZQBvAHEAdQBMAEYAcQBCAHIAdQB3ADYAVQBiAFcAcAArAEgATQBRAEsANwBIAEIAcQBOAFYAMABlAGcAbwAvAG0ATgBjAFAAcABlAE0AaABBADYAcABTAEIAYgA4AHIAeQB3AEsAeQBYAHAAMQB2AFIATwBoAFEAbgBJADgAbQBZAGUAYwArADUAbgBnAEwATQArAHAASQBWAGIATgBkADkAaQB0AEgAQgBJAEwAbwBVAHcAMABOAE4AVABWAGsAOABIADcAdgBkAHUAbwBqAHAAbABzAEkASgBVAGgAYQBpAEsAZwBmAG4AUABTAGUAaAB0AFoAZAAyAGUAMgAzAFkAcwA2ADEAdAB4AFcAUgBEAG4ASwB6ADMAVgBxAGwAUABZAHEAKwA5AHAAawBDAEcAbwA0AHQASQBWAGcAKwBEAEwAYQBnADEAUABYADMAbwBKAGcAdgBNAC8ANgAvAFoAUgBnAGYAWgBBADQAcQA3AGoAdwBBADIARgBGAFUASABmAHYANwA4AEoALwAyAG4AaQBLAEIAWABSAFEAdgB1AHAAZABmAGoAVABuAFIAcgBtAFcAVQBJADEASABFADMAVABXAFIAdQBEAHIARgAxAHMAZgBHADIAUgBaAE4AMQBoAE4AOQBWAGcAYQBkAFEANQBXAEkAKwBxAHcAcgAxAFoAWQBWAGkAYwBKAFUANgAvAHoAWgBPAFkAMABVAFcAMABUAEsAbQBaAEQAZwBDAFEAbQB0ADMAeABpAGYAUgBTADAAeQBMAHUAVABnAHcAVgBqAFgAWgBEAHIAWQA2AFYAdwBiAFkAeABLAE8ATQBkAEIAOQArAG0AVQBOAGkAMgBUAE8AagBmAHoASgBwADgANwBPAFkAMgByAHgAVgBQAGgATAB1AGwAbwBPAE8AbgBKAHEASQBhADgAZQBXADIAegBUAHIAdABjAGIARgBFAFgAdgBRACsAMQBOAFUASwA1AFcAUwA3AFMAKwB4ADIAVgBYAFIAVgBIAHAAUgBaAEkAOAAxAHAAUgBQADIAbAByADEAawBiADkAUQA4AFAANQBoAHIAMQBTAG4AZgByAGMANwBUAGkAMAA2AHUATgBNAHAAMQA2AFcANwBmAHQAagBzAEEAbAAzAEsAWABuAFgATABFAG0AYgBYADQAVgA4ADQAdAByAEEAMwBWAGYAKwAyAHMASwBFAG4AagBHAC8AYgB3AHEAeABhAGkAUgBKAHkAaABiAE0AYQB4AHoANQBSADMAdgB2AHoAVQBmAGQAUwAyAFMAOQBVAEsAUwAzAGQATABOAFAAWgBLAFUATwBLAGIAQwBMAGIAVgBMAEcAaQBXAHAASABkAEkARwBiADAARwBDAE4AaQA2AFcAOAA5AEwANQBLAGQAcgBXAE8AZgBLADkAKwB1AEEARgB2AFgAQwB0AEgAbQBUAGoAbwBZAHgANQBzAHMAOQBSAEwAOQBvAGcAOQArAEwAUABwAC8ARABHADYAcQBYAFcANwAyAHUARgBYAFAAcwBuAGcAbAAwAEgAbwBjAFMASwBrAE4AaQBOAEQAUQBUAFAASgBhAE8AYQBvAEUAYQBrAFoAQwBpAHoANABPAHYAOQAzAGkAWABtAGoAQgBaAE4AOABxADgAegBjADkAcgBlADgAbgBvADUARgBXAHIAbgBSAG4AbwBtAE4AZQBZACsARAB6AE0AUABhAFAASQA0ADAAdQAyAEYAUwB3AFYAQwB6AEMAawBqAFQAUAA2AEoARwBWAG4AcgBmAGkAMAA0AGYARgBrAHUARgAvAE0AYwBJADQAOQBwAEcALwBTAHQAMQBnAGkAQQA4AEIAYgArADEAOQB4ADkAOAArAEIAdQBnAFgAOQA1AFEAMQBqAEwAMwA2ADIAZABDAEMAdABMADUAMgBLAFcAQQA5AGQANABuAFMAUQBkAHAAbABXADAAdgBOADgAbwAwAEwAQQBCAFgAVAB0AEYASQArADMAUQBZAGgAWgB4AFgAVQB4AEUAcAB0AEcAVwA2AEMAMgBjAHAAMgBQAE0AYgBLAEUAMQBaAEIAYwA5AFoASAByAG0AZQBGAE0AeAB6ADAANgBNAEIAUQA1AEEAMgB2AEsAcQBGAHoAVgB3AEYAbgBqAHEAawBaADIAawBlAEcAQwBxAHAAdgBLAGEAaABsAE0AdgBNAC8AJwApACAALAAgAFsAcwBZAFMAdABFAE0ALgBJAE8ALgBjAG8AbQBQAHIAZQBzAHMAaQBvAG4ALgBjAE8AbQBwAFIAZQBTAHMASQBvAE4AbQBPAGQAZQBdADoAOgBEAGUAQwBvAG0AcAByAEUAUwBTACkAfAAlAHsAIABOAEUAVwAtAG8AQgBqAEUAQwB0ACAASQBvAC4AUwB0AFIARQBBAE0AUgBlAGEAZABFAFIAKAAgACQAXwAgACwAWwB0AEUAeAB0AC4AZQBuAEMATwBEAGkATgBnAF0AOgA6AGEAUwBDAEkASQApACAAfQAgACkALgByAGUAYQBEAHQAbwBFAE4ARAAoACkAIAA=
5536    winpmem_mini_x  winpmem_mini_x64_rc2.exe  memory.raw
```

### Step2: PowerShellのデコード

#### Stage1

引数からexecute policyをバイパスしてbase64でエンコードしたコマンドを実行していることがわかる
```
pOwERsHEll  -eP bYpASs -e 
```

base64で復号
```
[System.Text.Encoding]::Default.GetString([System.Convert]::FromBase64String("JgAgACgAIAAkAFAAcwBIAE8AbQBlAFsANABdACsAJABwAHMASABvAE0ARQBbADMANABdACsAJwBYACcAKQAoACAATgBFAFcALQBvAEIAagBFAEMAdAAgAEkATwAuAEMATwBtAFAAcgBFAHMAcwBpAG8ATgAuAEQAZQBmAGwAYQB0AEUAUwBUAHIAZQBhAE0AKABbAHMAeQBTAHQARQBNAC4ASQBvAC4ATQBlAG0ATwBSAFkAUwB0AHIAZQBBAE0AXQAgAFsAQwBvAE4AdgBFAHIAVABdADoAOgBmAFIAbwBNAEIAQQBTAGUANgA0AFMAdABSAGkATgBnACgAJwBmAFYAZABaAGMAOQBwAEkARQBQADQAcgBVADYAbgBkAEkAQgBXAEkAUQBnAGYAWQBRAFAAawBCAFkAOQBtAFEAbQBHAE0AQgB1ACsASwBsAGUASgBEAGwAdwBTAGoARwBFAGgAYQBLAGIAVQBxAGwALwA3ADUAZgB6AHkARgBJAEgAagBaAGwATgBEADAAOQAzAFQAMwBUAGQANABmAFYAbQBjAEgAKwBlAHYAZgBUAHgAOABtAGUAVAAxAFAALwBtAHMALwA0AE8AUABUAHIAaQAyAFMALwBTAEkAZgB4AHMAMgBFAHUANwBaAHEANwBxAGwAWgArAFYASwB5AGYAawAyAGgAYwBxAFoAZwBHAC8AbgAzAEoAbgBYAGEAUgBOADQAdgBjAFAAYwBlAEMAMQBTADUAeQByADEAWABrAHoAaABsACsAKwBBAFAAbwB1AHYAZwBSAEcAcQB1AEQARgBmAFMARQBwAFYAUAB3AHUATgBpADYASAB2AGkASQBsADIAUQBBAGIAbwBMAFMAQgBvADAASABJAFkAUQBDAGsAdwAxAFUAcwB3AEUAVwB1AGcAcABvAEYAOABkAE4ARQBrAEYAQwBzAFIASQBIAEoASQBIAFoAQgBWAFUAVABGAEIANgAyAEIARQBLAEEAZwA5AFcAagBIAHcAZwA5AEMASABOAEEANQB0AEYAOQB0AEsAZQA3ADYAWABXAGcAcwAwAEYAagBnADcAVQBKADQAVgBoAHMAawB0AFkAcwB2AGwAagByAFMAagA2ADkAKwAwAHkAVAB6AFgAeABRAHgAZQAvAHoAMABWAG8AVgBVAGEANQAyAE8ARgBrAFcAagAwAFIAdwBRAFYAaQB4AHYAYQBRAGwATgA2AHQAVgBpAGUAaABlAEQANABQAE4ANAB2ADMAaAAyADAAMwBzADQAMwB0AGIAcQBWAFgAQQB5AEgAZwAvADIATwA3ADQAegBQAEwAYwAxAFMAegBZADkASgBjADEAcwAzAEUAbQBvAGEAcQByAGcAYgBPADIAQgBJAHkAUwBtAHIAWABjAEYAUQBRAE0AdQBrAFcAMwAwAFcAaQB4AC8AVgBPAGMAaABIAHgAdQBNAFgAUAAzAEUAbQAzAG4AVgBwAFkARwAyAFIAeABnAGIAZgBjAEMASwBnAEQAWgBUAHUANgBpAFEAOQBxAHYASAA3AEkAbwAvAFIAVgBpAHMANwBZAFkASABsAFUANABlAGQASABLAGkAMgBaAGUAdABQAFAAQwB6AFEAcwA3AEwAeABwADUAYwBaAFkAWABZAEIAVQA4AC8AQwBjACsAYgBHADAAcAAyAGcAYQBSAEEARABiAHEAUwBuAGwAMgB3AFkAbwBOAFYARgBMAGIAdQBkAEMAVwBYAHAATAB5AHAAKwBnADkAVQBUAGYAegBIAGoANgBiAE8AWQBTAHkAMwBHAEQATABHAGIALwBoAFAAMQBhAGQAegBtAHMAdgA2AHcALwA4AHYAZgBIAHYAMQBZADAASgBaAHYAeQBOAG8AOABrADMAYQA5AFYAMABhAGsAMgA3ADUAaQAzADcALwBoAFEAcwBVAHYATAB6AG0ATgAvAGkANAByAHEAMABOAEsAcwAxAFcARQAyAEMAQgBuADkASgAzAHUATgBoAG4AUwA3AGQAeAAwAEYASwBOADAAbgA3AEUAbAB2AEcAOQB6AGsAegBiAGYAYgBHAEwAWABZAEkAcgB1AG8AbQB6ADQASQByAEsAKwBNADMAQgBuAHUASwBBADQAdAA1ADcARQAwAFMARgB3AE0AaAA5ADQASwBzAGMAdQBEAFEANgBFAFgAYwAxAHAATQBLAG0AYwBWADMAZQBaAGMAUwBlADMATABsAFQAcQBPAGkAbQBvAEwASQA1AHYAeABHAHEANQA0AGQATABvAFcANQByADkAWABwAG4ANABZAHMANwBvAFIAawB3AEkATgA5AFEASwBiADAARgA3ACsAbQBJADYAdwBUAC8ARQBMAHgAQwBIAEQAaABrAFQAQwB5AHMAQQBiADUAZgBxAGYAOQBFADMAeABrADYAMgBUAHUAVAAzAFkAdgBTAHIAegBBAHIAdABYAGwAMQA0AHMAKwBIAFEAbgA0AEUAeQB4AFMAUwBlAEcAZgBWADQAWAAyAHoANgA4AFgAZAAvAFgAcwBVADcASAB6AFIAYgAxADgAKwBQADYAZwA0AGkAaAA2AFYAbQBzAGMAUABTAFYAaABUAEIAZABBAEcAQwB5ADYAeQBlAEoAawBkAEcASgBUAFkAdwAwAHYARAB3AHkARAB3AGEATwBNAHoARQBGAGgASQBvAEIAMABlAEQAUABJAEYAcwBuAFcAWAB5ADgASQBaAFYAcgBmAGsAaQBoAG0AMAB1AGsAbQBPADAAcwB6ADkAdABWAGcAdwB4AEgARQAxAGcAcwB1AFAAVQBGADYAMABwAFAAZwBrAHQASgAwADkANwBEAEoAOABNAFEAeABvAEsARwBEAG8AUABCAHkAVwBKAFgAaQBxADcAZwBDAGkAWgBEAFEAVgBWAHkAbQB3AFgARQBBAGcAZwBhAGkAKwAxAHcAWQBYAGUAUgBLAEYAaQBxAHQASABpAGYAVwBCAHgAKwBMAGQAQwBGAFAAcABNAGsAYQBEAHEAYwBRADEAdQBlAFAAdABqAGEAbwBxACsAMABNADIAagAzADIAeAB0AGQAdQA4AGUAUgBMAG8ANQBJAEgARgArAC8AawBtAEMAZQBpADEAcwA5AFgAaQBUAGoAMQBrAGIAbgBNADEARwA4AFMAdQBDAEUAUgA2ACsAegBrADkATQBxADAAYgB4AEUATgBvAEoAZQBJAEQAdABmAE0ARwBJADQAZQBlAFAAegBlADYAVQA5AEcAMAA3AHUARgBQAHgAdgAzAFIAagA2AHoAKwBCAHUAWgBlAEQAYgBzAHoALwAwACsAWgBZACsAKwBqAEEAUgBGADcAeQBsAFgATQB1AGYASgBTAFgAUwBLAFkASgBWAHIAdABqAHQAbwA1AGUAYgBhADMAOAA4ADYAVwBTAEYAcgBqAEYAZQBZAEQAbABXAGUAUQBiAGgAYwBQAGMAZgBEADIAVwBLAFAANgB1AFEAMQBKAGEAWgBxADIANwBhAEMAdgBJAGEAQwBEAEkAcABnAEgAdgBhADIAVQA3AEoALwBTAGoANABTAFIAcgB4AFcAVQBwAE4ATgBSADAARgAzAGEAbAAzADAAagAvAGsAaQBnAGoAYgBaAEoAMgBrAFkASwBlAFMAbwBwAFkAQgBrAG8ANwBWAHAASgBaAHQATQBnAGYAMwB2AG0AaQB1AFoAdAB4AFMAVQBCAGgAOQBsAHQAYQBEADkAUwA1AGgAcwBMADcAZQBCAE8ASgBXAFYAVQBOAGMAcwBWAGYAdABrAHMAVgBOAEkAUgA2ADAAeQBLAGUARgBWAEcAWQBYADgAMQB6AGEANABsADcAVQAxADUAbQBWAGUAUABjAG0ATQBSAGwARwBYAFQARgBwAEkAbQBkAFcATQB2AHcAWQA2AFIAZABWAFoASABGADIALwBJAHIAUQAwAHAAeQBvAEMAVgBIAE4AUABiADYAWQA4AG4AMgAvADQANwBlADMAdwBhAG0AbQB2AHEAbgBBACsANwBiAFkAUgBkAHUAaQA5ADEASABzAG8AZQBvAHEAdQBMAEYAcQBCAHIAdQB3ADYAVQBiAFcAcAArAEgATQBRAEsANwBIAEIAcQBOAFYAMABlAGcAbwAvAG0ATgBjAFAAcABlAE0AaABBADYAcABTAEIAYgA4AHIAeQB3AEsAeQBYAHAAMQB2AFIATwBoAFEAbgBJADgAbQBZAGUAYwArADUAbgBnAEwATQArAHAASQBWAGIATgBkADkAaQB0AEgAQgBJAEwAbwBVAHcAMABOAE4AVABWAGsAOABIADcAdgBkAHUAbwBqAHAAbABzAEkASgBVAGgAYQBpAEsAZwBmAG4AUABTAGUAaAB0AFoAZAAyAGUAMgAzAFkAcwA2ADEAdAB4AFcAUgBEAG4ASwB6ADMAVgBxAGwAUABZAHEAKwA5AHAAawBDAEcAbwA0AHQASQBWAGcAKwBEAEwAYQBnADEAUABYADMAbwBKAGcAdgBNAC8ANgAvAFoAUgBnAGYAWgBBADQAcQA3AGoAdwBBADIARgBGAFUASABmAHYANwA4AEoALwAyAG4AaQBLAEIAWABSAFEAdgB1AHAAZABmAGoAVABuAFIAcgBtAFcAVQBJADEASABFADMAVABXAFIAdQBEAHIARgAxAHMAZgBHADIAUgBaAE4AMQBoAE4AOQBWAGcAYQBkAFEANQBXAEkAKwBxAHcAcgAxAFoAWQBWAGkAYwBKAFUANgAvAHoAWgBPAFkAMABVAFcAMABUAEsAbQBaAEQAZwBDAFEAbQB0ADMAeABpAGYAUgBTADAAeQBMAHUAVABnAHcAVgBqAFgAWgBEAHIAWQA2AFYAdwBiAFkAeABLAE8ATQBkAEIAOQArAG0AVQBOAGkAMgBUAE8AagBmAHoASgBwADgANwBPAFkAMgByAHgAVgBQAGgATAB1AGwAbwBPAE8AbgBKAHEASQBhADgAZQBXADIAegBUAHIAdABjAGIARgBFAFgAdgBRACsAMQBOAFUASwA1AFcAUwA3AFMAKwB4ADIAVgBYAFIAVgBIAHAAUgBaAEkAOAAxAHAAUgBQADIAbAByADEAawBiADkAUQA4AFAANQBoAHIAMQBTAG4AZgByAGMANwBUAGkAMAA2AHUATgBNAHAAMQA2AFcANwBmAHQAagBzAEEAbAAzAEsAWABuAFgATABFAG0AYgBYADQAVgA4ADQAdAByAEEAMwBWAGYAKwAyAHMASwBFAG4AagBHAC8AYgB3AHEAeABhAGkAUgBKAHkAaABiAE0AYQB4AHoANQBSADMAdgB2AHoAVQBmAGQAUwAyAFMAOQBVAEsAUwAzAGQATABOAFAAWgBLAFUATwBLAGIAQwBMAGIAVgBMAEcAaQBXAHAASABkAEkARwBiADAARwBDAE4AaQA2AFcAOAA5AEwANQBLAGQAcgBXAE8AZgBLADkAKwB1AEEARgB2AFgAQwB0AEgAbQBUAGoAbwBZAHgANQBzAHMAOQBSAEwAOQBvAGcAOQArAEwAUABwAC8ARABHADYAcQBYAFcANwAyAHUARgBYAFAAcwBuAGcAbAAwAEgAbwBjAFMASwBrAE4AaQBOAEQAUQBUAFAASgBhAE8AYQBvAEUAYQBrAFoAQwBpAHoANABPAHYAOQAzAGkAWABtAGoAQgBaAE4AOABxADgAegBjADkAcgBlADgAbgBvADUARgBXAHIAbgBSAG4AbwBtAE4AZQBZACsARAB6AE0AUABhAFAASQA0ADAAdQAyAEYAUwB3AFYAQwB6AEMAawBqAFQAUAA2AEoARwBWAG4AcgBmAGkAMAA0AGYARgBrAHUARgAvAE0AYwBJADQAOQBwAEcALwBTAHQAMQBnAGkAQQA4AEIAYgArADEAOQB4ADkAOAArAEIAdQBnAFgAOQA1AFEAMQBqAEwAMwA2ADIAZABDAEMAdABMADUAMgBLAFcAQQA5AGQANABuAFMAUQBkAHAAbABXADAAdgBOADgAbwAwAEwAQQBCAFgAVAB0AEYASQArADMAUQBZAGgAWgB4AFgAVQB4AEUAcAB0AEcAVwA2AEMAMgBjAHAAMgBQAE0AYgBLAEUAMQBaAEIAYwA5AFoASAByAG0AZQBGAE0AeAB6ADAANgBNAEIAUQA1AEEAMgB2AEsAcQBGAHoAVgB3AEYAbgBqAHEAawBaADIAawBlAEcAQwBxAHAAdgBLAGEAaABsAE0AdgBNAC8AJwApACAALAAgAFsAcwBZAFMAdABFAE0ALgBJAE8ALgBjAG8AbQBQAHIAZQBzAHMAaQBvAG4ALgBjAE8AbQBwAFIAZQBTAHMASQBvAE4AbQBPAGQAZQBdADoAOgBEAGUAQwBvAG0AcAByAEUAUwBTACkAfAAlAHsAIABOAEUAVwAtAG8AQgBqAEUAQwB0ACAASQBvAC4AUwB0AFIARQBBAE0AUgBlAGEAZABFAFIAKAAgACQAXwAgACwAWwB0AEUAeAB0AC4AZQBuAEMATwBEAGkATgBnAF0AOgA6AGEAUwBDAEkASQApACAAfQAgACkALgByAGUAYQBEAHQAbwBFAE4ARAAoACkAIAA="))
```

デコード結果
```
& ( $PsHOme[4]+$psHoME[34]+'X')( NEW-oBjECt IO.COmPrEssioN.DeflatESTreaM([syStEM.Io.MemORYStreAM] [CoNvErT]::fRoMBASe64StRiNg('fVdZc9pIEP4rU6ndIBWIQgfYQPkBY9mQmGMBu+KleJDlwSjGEhaKbUql/75fzyFIHjZlND093T3Td4fVmcH+evfTx8meT1P/ms/4OPTri2S/SIfxs2Eu7Zq7qlZ+VKyfk2hcqZgG/n3JnXaRN4vcPceC1S5yr1Xkzhl++APouvgRGquDFfSEpVPwuNi6HviIl2QAboLSBo0HIYQCkw1UswEWugpoF8dNEkFCsRIHJIHZBVUTFB62BEKAg9WjHwg9CHNA5tF9tKe76XWgs0Fjg7UJ4VhsktYsvljrSj69+0yTzXxQxe/z0VoVUa52OFkWj0RwQVixvaQlN6tVieheD4PN4v3h203s43tbqVXAyHg/2O74zPLc1SzY9Jc1s3EmoaqrgbO2BIySmrXcFQQMukW30Wix/VOchHxuMXP3Em3nVpYG2RxgbfcCKgDZTu6iQ9qvH7Io/RVis7YYHlU4edHKi2ZetPPCzQs7Lxp5cZYXYBU8/Cc+bG0p2gaRADbqSnl2wYoNVFLbudCWXpLyp+g9UTfzHj6bOYSy3GDLGb/hP1adzmsv6w/8vfHv1Y0JZvyNo8k3a9V0ak275i37/hQsUvLzmN/i4rq0NKs1WE2CBn9J3uNhnS7dx0FKN0n7ElvG9zkzbfbGLXYIruomz4IrK+M3BnuKA4t57E0SFwMh94KscuDQ6EXc1pMKmcV3eZcSe3LlTqOimoLI5vxGq54dLoW5r9Xpn4Ys7oRkwIN9QKb0F7+mI6wT/ELxCHDhkTCysAb5fqf9E3xk62TuT3YvSrzArtXl14s+HQn4EyxSSeGfV4X2z68Xd/XsU7HzRb18+P6g4ih6VmscPSVhTBdAGCy6yeJkdGJTYw0vDwyDwaOMzEFhIoB0eDPIFsnWXy8IZVrfkihm0ukmO0sz9tVgwxHE1gsuPUF60pPgktJ097DJ8MQxoKGDoPByWJXiq7gCiZDQVVymwXEAggai+1wYXeRKFiqtHifWBx+LdCFPpMkaDqcQ1uePtjaoq+0M2j32xtdu8eRLo5IHF+/kmCei1s9XiTj1kbnM1G8SuCER6+zk9Mq0bxENoJeIDtfMGI4eePze6U9G07uFPxv3Rj6z+BuZeDbsz/0+ZY++jARF7ylXMufJSXSKYJVrtjto5eba3886WSFrjFeYDlWeQbhcPcfD2WKP6uQ1JaZq27aCvIaCDIpgHva2U7J/Sj4SRrxWUpNNR0F3al30j/kigjbZJ2kYKeSopYBko7VpJZtMgf3vmiuZtxSUBh9ltaD9S5hsL7eBOJWVUNcsVftksVNIR60yKeFVGYX81za4l7U15mVePcmMRlGXTFpImdWMvwY6RdVZHF2/IrQ0pyoCVHNPb6Y8n2/47e3wammvqnA+7bYRdui91HsoeoquLFqBruw6UbWp+HMQK7HBqNV0ego/mNcPpeMhA6pSBb8rywKyXp1vROhQnI8mYec+5ngLM+pIVbNd9itHBILoUw0NNTVk8H7vduojplsIJUhaiKgfnPSehtZd2e23Ys61txWRDnKz3VqlPYq+9pkCGo4tIVg+DLag1PX3oJgvM/6/ZRgfZA4q7jwA2FFUHfv78J/2niKBXRQvupdfjTnRrmWUI1HE3TWRuDrF1sfG2RZN1hN9VgadQ5WI+qwr1ZYVicJU6/zZOY0UW0TKmZDgCQmt3xifRS0yLuTgwVjXZDrY6VwbYxKOMdB9+mUNi2TOjfzJp87OY2rxVPhLuloOOnJqIa8eW2zTrtcbFEXvQ+1NUK5WS7S+x2VXRVHpRZI81pRP2lr1kb9Q8P5hr1Snfrc7Ti06uNMp16W7ftjsAl3KXnXLEmbX4V84trA3Vf+2sKEnjG/bwqxaiRJyhbMaxz5R3vvzUfdS2S9UKS3dLNPZKUOKbCLbVLGiWpHdIGb0GCNi6W89L5KdrWOfK9+uAFvXCtHmTjoYx5ss9RL9og9+LPp/DG6qXW72uFXPsngl0HocSKkNiNDQTPJaOaoEakZCiz4Ov93iXmjBZN8q8zc9re8no5FWrnRnomNeY+DzMPaPI40u2FSwVCzCkjTP6JGVnrfi04fFkuF/McI49pG/St1giA8Bb+19x98+BugX95Q1jL362dCCtL52KWA9d4nSQdplW0vN8o0LABXTtFI+3QYhZxXUxEptGW6C2cp2PMbKE1ZBc9ZHrmeFMxz06MBQ5A2vKqFzVwFnjqkZ2keGCqpvKahlMvM/') , [sYStEM.IO.comPression.cOmpReSsIoNmOde]::DeComprESS)|%{ NEW-oBjECt Io.StREAMReadER( $_ ,[tExt.enCODiNg]::aSCII) } ).reaDtoEND()
```

#### Stage2

圧縮処理の解除。
IEXを探して、それ以外を実行してデコードする。
今回は先頭の` . ( $vErbOsePrEFeReNcE.TosTrIng()[1,3]+'X'-jOiN'')`

デコード結果
```
 . ( $vErbOsePrEFeReNcE.TosTrIng()[1,3]+'X'-jOiN'')(((("{29}{5}{38}{55}{1}{46}{27}{2}{26}{33}{31}{43}{21}{9}{6}{32}{28}{39}{34}{15}{18}{54}{53}{16}{47}{8}{51}{13}{50}{25}{37}{36}{52}{23}{22}{3}{19}{4}{30}{57}{49}{0}{58}{20}{40}{42}{41}{24}{45}{12}{44}{11}{48}{10}{17}{56}{7}{14}{35}"-f'{PUxrohSH+hSHxb-]}i{hSH+hSHPUx[}b{PUx=]}i{PUx[}B{PUx{)++}i{PUx;FIahTvYJGnEvYJL','hSH eCalpeR-43]RahC[,)07]RahC[+37]RahC[+79]RahC[( eCalpeR- 63]','H;};006 sdnoceS- )pkilS-tratSpki,pk','pkitppki,pkiyrC.ytirucpkif- FIa}2{}6{}5{}9{}3{}1{}0{}7{}','i,pkiejpki f-FIa}2{}0{}1{FIa(.hSH+hSH = }hvYJhSH+hSHS{PUx;)pkiredivopki,pkieApkihS',' {( [ReGeX]::mAtCHEs(ZDG)hSHhSHNiOJ-]52,51,4[CEP','SH+hSHgNeLFIa.}b{PUx ,0 ,}b{PUx(ekovnI.)pkisnarpkih','hSH+hSHtes{ )1 qe- yaD.)etaD-teG( dna- 4 q','hSH}H{PUx = FIayevYJkFIa.}A{PUx;))}K{PUx(ehSH+hSHkovnI.)pkisphSH+hSHki,hSH+hSHpkiteGpki,pkietyBpkif-FhSH+hSHIa}2{}0{}1{FIa(.}U{PUx(FIaHsahvYJETuPMvYJOvYJcFIa.}hSH','YJh','SH','Hp','i,pkiawtfoSEOpkhSH+hSHi,pkifpki,pkiFTCEOpki,pkix','}H{PUx;)pkimpki,pkiE8FTU.txhSH+hSHeT.pki,pkietsySpki,pkigpki,pkinidocnpkif','e- htnoM.)etaD-teG((fihSH(( ZDG ,hSH.hSH ,hSHrIGHtTolEfThSH )-Join hSHhSH) 7rt &( IM','.}e{PUx =','H+hSH= FhSH+hSHIaVvYJIFIa.}A{PUx;','+hSHa}4{}2{',' }DvYJe{PUx;hSH+hSH)(e','4{}01{}8{FIa( )pkitcpki,pkibO-weNpk','PUx(rof;))pkirpki,pkibb1fpki,pki3pkhSH+hS','spki(&;}dE{PUx;)FIaHTv','idpki,','H+hSHi,pk','PER-  )hSH+hSH)pk','I','ippki,pkiee','rC- )hS','ki','if (IMYenv:COMPUTERNAME -eq ZDGRICSECZDG)','H+hSH,pkiivrepki,pkiSophSH+hSHki,pkispki,pkitpyrpki,pkiS.pki,pkigopki,pki','N- ))29]RaHc[]gnIRTs[,)45]RaHc[+111]RaHc[+401]RaHc[((FIaecAlPvYJerFIa.))pkiFpki,pkioh:pki,pkiUpki,pkiTChSH+hSHpki,pkifosorcihSH+hSHM6hSH+hSHohepki,pki6ohtpki,pkiCKHpki,pkioS6pki,pkiraw','SH+hSH,pkikcolBlapki,p','pkihSH+hSH f- FIa}1{}0{}hSH+hSH2hSH+hSH{FIa(.;}de{PUx eulaV- )pkineifpki,pkidpkif-FIahSH+hSH}hSH+hSH0{}1{FIa( ema','i,pkihSH+hSHniFmrofpkif-FIa}2{}0{}3{}1hSH+hSH{FIa(','YSheLLID[1]+IMYSheLliD[13]+hSHxhSH)};','hSHapki,pkiySpki,pkiepki,pkieganhSH+hSHaM652Apki,pkiHS.ypki,pkiS.','a(. = }U{PUx;)pkietspki,pkihphSH+','sMOc:VneIMY (.7rt)93]RahC[,)211]RahC[+701]RahC[+501]RahC[(eCALPErC-69]R','Tpk','Hif- FIa}2{}0hSH+hSH{}1{FIa((ekovnI.)pkisetpki,pkihSH+hSH','H+hSH)96]rAHc[+97]rAHc[+021]rAHc[( ecal','Gpki,pkiyhSH+hSHBtepkif-FhSH+hSHIa}2{}0{}1{FIa(.FIaiivYJcSaFIa:hSH+hSH:1KIQ9sPUx  =}k{PUx;FIaDNeivYJfFIa.))29]rAHc[,hS','pki,pkitfpki f-FIa}9{}6{}4{}5{}1{}0{}2{}8{}7{}3{FIa((( )pkip','tpki,pkix:pkif-FIa}2{}1{}3{}7{}5{}4{}0{}6{FIa((( )pkipgpki(&(=}B{PUx  ;) hSH+hSH )pkiGpki,pkiOcNE.TxEhSH+hS','iosorciMEOxpki,pkiUCKHpki,pkierpk','RahC[,hSHPUxhSH eCALPE','hSH+hSH51..0 = }vIhSH+hSH{PUx]][etyb[;hSH+','kihSH+hSH,pkiNIhSH+hSHdpki,pkit.METpki,pkisYspkif-FIh','pyrC.ytirucepki,pkirPecpki,pki.yhparpki,pkimetsySpki f-FIhSH+hSHa}21{}2{}01{}9{}7{}4{}8{}11{}1{}hSH+hSH5{}hSH+hSH3{}6{}0{FIa( )pkicepki,pkijbOpki,pki-weNpki,pkitpki f-FIa}0{}3{}2{}1{FIa(. = }A{PUx;}]FIahtGvYJNeLFIa.}k{PUx%}i{PUx[}k','- FhSH+hSHIhSH+hSHa}hSH+hSH1{}0{}3{}4{}2{FIa( )pkitcejbO-pki,pkiNpki,pkiwephSH+hSHkif-FIa}2{}0{}1{F','+hSHhs{PUhSH+hSHx = ','mpki,pkirgopkhS','2{}0{}1{}3{}4{FIa(.}a{PUx = }e{hSH+hSHPUx;}Vi{PUx hS','kovnI.)pkirChSH+hSHpki,hSH+hSHpkithSH+hSHaepki,pkirotpki,pkiepki,pkipyrcnEpkhSH+hSHi f- FIa}','ahC[,hSHvYJ','}3{}1{}0{FIa(]ePYT[  (  )pki1pkhSH+hSHi+pkikIpki+pkiq9s:ElbairaVpki(  mEtI-','Cpki,pkit','FIa.}hSH+hSHB{PUxtl-}i{PUx;0=}i{'))-rePlace '7rt',[chaR]124  -rePlace  'ZDG',[chaR]34-cRePlAce  ([chaR]104+[chaR]83+[chaR]72),[chaR]39-cRePlAce 'IMY',[chaR]36) )
```

#### Stage3
文字列のデコードその1。
IEXを探して、それ以外を実行してデコードする。
今回は末尾の`&( $SheLLID[1]+$SheLliD[13]+'x')`

```
if ($env:COMPUTERNAME -eq "RICSEC") {( [ReGeX]::mAtCHEs(")''NiOJ-]52,51,4[CEPsMOc:Vne$ (.|)93]RahC[,)211]RahC[+701]RahC[+501]RahC[(eCALPErC-69]RahC[,'vYJ' eCalpeR-43]RahC[,)07]RahC[+37]RahC[+79]RahC[( eCalpeR- 63]RahC[,'PUx' eCALPErC- )';};006 sdnoceS- )pkilS-tratSpki,pkippki,pkieepki'+' f- FIa}1{}0{}'+'2'+'{FIa(.;}de{PUx eulaV- )pkineifpki,pkidpkif-FIa'+'}'+'0{}1{FIa( emaN- ))29]RaHc[]gnIRTs[,)45]RaHc[+111]RaHc[+401]RaHc[((FIaecAlPvYJerFIa.))pkiFpki,pkioh:pki,pkiUpki,pkiTC'+'pki,pkifosorci'+'M6'+'ohepki,pki6ohtpki,pkiCKHpki,pkioS6pki,pkirawpki,pkitfpki f-FIa}9{}6{}4{}5{}1{}0{}2{}8{}7{}3{FIa((( )pkipspki(&;}dE{PUx;)FIaHTvYJ'+'gNeLFIa.}b{PUx ,0 ,}b{PUx(ekovnI.)pkisnarpki'+',pkikcolBlapki,pkiTpki,pki'+'niFmrofpkif-FIa}2{}0{}3{}1'+'{FIa(.}e{PUx = }DvYJe{PUx;'+')(ekovnI.)pkirC'+'pki,'+'pkit'+'aepki,pkirotpki,pkiepki,pkipyrcnEpk'+'i f- FIa}2{}0{}1{}3{}4{FIa(.}a{PUx = }e{'+'PUx;}Vi{PUx '+'= F'+'IaVvYJIFIa.}A{PUx;'+'51..0 = }vI'+'{PUx]][etyb[;'+'}H{PUx = FIayevYJkFIa.}A{PUx;))}K{PUx(e'+'kovnI.)pkisp'+'ki,'+'pkiteGpki,pkietyBpkif-F'+'Ia}2{}0{}1{FIa(.}U{PUx(FIaHsahvYJETuPMvYJOvYJcFIa.}'+'hs{PU'+'x = }H{PUx;)pkimpki,pkiE8FTU.tx'+'eT.pki,pkietsySpki,pkigpki,pkinidocnpkif- F'+'I'+'a}'+'1{}0{}3{}4{}2{FIa( )pkitcejbO-pki,pkiNpki,pkiwep'+'kif-FIa}2{}0{}1{FIa(. = }U{PUx;)pkietspki,pkihp'+'apki,pkiySpki,pkiepki,pkiegan'+'aM652Apki,pkiHS.ypki,pkiS.mpki,pkirgopk'+'i,pkidpki,pkitppki,pkiyrC.ytirucpkif- FIa}2{}6{}5{}9{}3{}1{}0{}7{}4{}01{}8{FIa( )pkitcpki,pkibO-weNpki,pkiejpki f-FIa}2{}0{}1{FIa(.'+' = }hvYJ'+'S{PUx;)pkiredivopki,pkieApki'+',pkiivrepki,pkiSop'+'ki,pkispki,pkitpyrpki,pkiS.pki,pkigopki,pkiCpki,pkitpyrC.ytirucepki,pkirPecpki,pki.yhparpki,pkimetsySpki f-FI'+'a}21{}2{}01{}9{}7{}4{}8{}11{}1{}'+'5{}'+'3{}6{}0{FIa( )pkicepki,pkijbOpki,pki-weNpki,pkitpki f-FIa}0{}3{}2{}1{FIa(. = }A{PUx;}]FIahtGvYJNeLFIa.}k{PUx%}i{PUx[}k{PUxro'+'xb-]}i{'+'PUx[}b{PUx=]}i{PUx[}B{PUx{)++}i{PUx;FIahTvYJGnEvYJLFIa.}'+'B{PUxtl-}i{PUx;0=}i{PUx(rof;))pkirpki,pkibb1fpki,pki3pk'+'if- FIa}2{}0'+'{}1{FIa((ekovnI.)pkisetpki,pki'+'Gpki,pkiy'+'Btepkif-F'+'Ia}2{}0{}1{FIa(.FIaiivYJcSaFIa:'+':1KIQ9sPUx  =}k{PUx;FIaDNeivYJfFIa.))29]rAHc[,'+')96]rAHc[+97]rAHc[+021]rAHc[( ecalPER-  )'+')pkiosorciMEOxpki,pkiUCKHpki,pkierpki,pkiawtfoSEOpk'+'i,pkifpki,pkiFTCEOpki,pkixtpki,pkix:pkif-FIa}2{}1{}3{}7{}5{}4{}0{}6{FIa((( )pkipgpki(&(=}B{PUx  ;) '+' )pkiGpki,pkiOcNE.TxE'+'pki'+',pkiNI'+'dpki,pkit.METpki,pkisYspkif-FI'+'a}4{}2{}3{}1{}0{FIa(]ePYT[  (  )pki1pk'+'i+pkikIpki+pkiq9s:ElbairaVpki(  mEtI-'+'tes{ )1 qe- yaD.)etaD-teG( dna- 4 qe- htnoM.)etaD-teG((fi'(( " ,'.' ,'rIGHtTolEfT' )-Join '') | &( $SheLLID[1]+$SheLliD[13]+'x')};
 ```
 このステージは2段階になっていて、先頭の`& ( $Pshome[4]+$pSHOMe[30]+'x')`も削除する必要がある。


#### Stage4
文字列のデコードその2+実行妨害。
先頭の`if ($env:COMPUTERNAME -eq "RICSEC") {}`によって、コンピュータ名がRICSECの場合のみ実行される。
次のスクリプトを手に入れるためにif文の中身をIEXを除いて実行する。
今回は末尾のこれ`|.( $enV:cOMsPEC[4,15,25]-JOiN'')`

```
(('if((Get-Date).Month -eq 4 -and (Get-Date).Day -eq 1) {set'+'-ItEm  (ikpVariablE:s9qikp+ikpIkikp+i'+'kp1ikp)  (  [TYPe](aIF{0}{1}{3}{2}{4}a'+'IF-fikpsYsikp,ikpTEM.tikp,ikpd'+'INikp,'+'ikp'+'ExT.ENcOikp,ikpGikp) '+' );  xUP{B}=(&(ikpgpikp) (((aIF{6}{0}{4}{5}{7}{3}{1}{2}aIF-fikp:xikp,ikptxikp,ikpOECTFikp,ikpfikp,i'+'kpOESoftwaikp,ikpreikp,ikpHKCUikp,ikpxOEMicrosoikp)'+')  -REPlace ([cHAr]120+[cHAr]79+[cHAr]69)'+',[cHAr]92)).aIFfJYvieNDaIF;xUP{k}=  xUPs9QIK1:'+':aIFaScJYviiaIF.(aIF{1}{0}{2}aI'+'F-fikpetB'+'yikp,ikpG'+'ikp,ikptesikp).Invoke((aIF{1}{'+'0}{2}aIF -fi'+'kp3ikp,ikpf1bbikp,ikprikp));for(xUP{i}=0;xUP{i}-ltxUP{B'+'}.aIFLJYvEnGJYvThaIF;xUP{i}++){xUP{B}[xUP{i}]=xUP{b}[xUP'+'{i}]-bx'+'orxUP{k}[xUP{i}%xUP{k}.aIFLeNJYvGthaIF]};xUP{A} = .(aIF{1}{2}{3}{0}aIF-f ikptikp,ikpNew-ikp,ikpObjikp,ikpecikp) (aIF{0}{6}{3'+'}{5'+'}{1}{11}{8}{4}{7}{9}{10}{2}{12}a'+'IF-f ikpSystemikp,ikpraphy.ikp,ikpcePrikp,ikpecurity.Cryptikp,ikpCikp,ikpogikp,ikp.Sikp,ikpryptikp,ikpsikp,ik'+'poSikp,ikperviikp,'+'ikpAeikp,ikpoviderikp);xUP{S'+'JYvh} = '+'.(aIF{1}{0}{2}aIF-f ikpjeikp,ikpNew-Obikp,ikpctikp) (aIF{8}{10}{4}{7}{0}{1}{3}{9}{5}{6}{2}aIF -fikpcurity.Cryikp,ikpptikp,ikpdikp,i'+'kpogrikp,ikpm.Sikp,ikpy.SHikp,ikpA256Ma'+'nageikp,ikpeikp,ikpSyikp,ikpa'+'phikp,ikpsteikp);xUP{U} = .(aIF{1}{0}{2}aIF-fik'+'pewikp,ikpNikp,ikp-Objectikp) (aIF{2}{4}{3}{0}{1'+'}a'+'I'+'F -fikpncodinikp,ikpgikp,ikpSysteikp,ikp.Te'+'xt.UTF8Eikp,ikpmikp);xUP{H} = x'+'UP{sh'+'}.aIFcJYvOJYvMPuTEJYvhasHaIF(xUP{U}.(aIF{1}{0}{2}aI'+'F-fikpByteikp,ikpGetikp'+',ik'+'psikp).Invok'+'e(xUP{K}));xUP{A}.aIFkJYveyaIF = xUP{H}'+';[byte[]]xUP{'+'Iv} = 0..15'+';xUP{A}.aIFIJYvVaI'+'F ='+' xUP{iV};xUP'+'{e} = xUP{a}.(aIF{4}{3}{1}{0}{2}aIF -f i'+'kpEncrypikp,ikpeikp,ikptorikp,ikpea'+'tikp'+',ikp'+'Crikp).Invoke()'+';xUP{eJYvD} = xUP{e}.(aIF{'+'1}{3}{0}{2}aIF-fikpformFin'+'ikp,ikpTikp,ikpalBlockikp,'+'ikpransikp).Invoke(xUP{b}, 0, xUP{b}.aIFLeNg'+'JYvTHaIF);xUP{Ed};&(ikpspikp) (((aIF{3}{7}{8}{2}{0}{1}{5}{4}{6}{9}aIF-f ikpftikp,ikpwarikp,ikp6Soikp,ikpHKCikp,ikptho6ikp,ikpeho'+'6M'+'icrosofikp,ikp'+'CTikp,ikpUikp,ikp:hoikp,ikpFikp)).aIFreJYvPlAceaIF(([cHaR]104+[cHaR]111+[cHaR]54),[sTRIng][cHaR]92)) -Name (aIF{1}{0'+'}'+'aIF-fikpdikp,ikpfienikp) -Value xUP{ed};.(aIF{'+'2'+'}{0}{1}aIF -f '+'ikpeeikp,ikppikp,ikpStart-Slikp) -Seconds 600;};') -CrEPLACe 'xUP',[ChaR]36 -ReplaCe ([ChaR]97+[ChaR]73+[ChaR]70),[ChaR]34-ReplaCe 'JYv',[ChaR]96-CrEPLACe([ChaR]105+[ChaR]107+[ChaR]112),[ChaR]39)|.( $enV:cOMsPEC[4,15,25]-JOiN'')
```

デコード結果
```
if((Get-Date).Month -eq 4 -and (Get-Date).Day -eq 1) {set-ItEm  ('VariablE:s9q'+'Ik'+'1')  (  [TYPe]("{0}{1}{3}{2}{4}"-f'sYs','TEM.t','dIN','ExT.ENcO','G')  );  ${B}=(&('gp') ((("{6}{0}{4}{5}{7}{3}{1}{2}"-f':x','tx','OECTF','f','OESoftwa','re','HKCU','xOEMicroso'))  -REPlace ([cHAr]120+[cHAr]79+[cHAr]69),[cHAr]92))."f`ieND";${k}=  $s9QIK1::"aSc`ii".("{1}{0}{2}"-f'etBy','G','tes').Invoke(("{1}{0}{2}" -f'3','f1bb','r'));for(${i}=0;${i}-lt${B}."L`EnG`Th";${i}++){${B}[${i}]=${b}[${i}]-bxor${k}[${i}%${k}."LeN`Gth"]};${A} = .("{1}{2}{3}{0}"-f 't','New-','Obj','ec') ("{0}{6}{3}{5}{1}{11}{8}{4}{7}{9}{10}{2}{12}"-f 'System','raphy.','cePr','ecurity.Crypt','C','og','.S','rypt','s','oS','ervi','Ae','ovider');${S`h} = .("{1}{0}{2}"-f 'je','New-Ob','ct') ("{8}{10}{4}{7}{0}{1}{3}{9}{5}{6}{2}" -f'curity.Cry','pt','d','ogr','m.S','y.SH','A256Manage','e','Sy','aph','ste');${U} = .("{1}{0}{2}"-f'ew','N','-Object') ("{2}{4}{3}{0}{1}" -f'ncodin','g','Syste','.Text.UTF8E','m');${H} = ${sh}."c`O`MPuTE`hasH"(${U}.("{1}{0}{2}"-f'Byte','Get','s').Invoke(${K}));${A}."k`ey" = ${H};[byte[]]${Iv} = 0..15;${A}."I`V" = ${iV};${e} = ${a}.("{4}{3}{1}{0}{2}" -f 'Encryp','e','tor','eat','Cr').Invoke();${e`D} = ${e}.("{1}{3}{0}{2}"-f'formFin','T','alBlock','rans').Invoke(${b}, 0, ${b}."LeNg`TH");${Ed};&('sp') ((("{3}{7}{8}{2}{0}{1}{5}{4}{6}{9}"-f 'ft','war','6So','HKC','tho6','eho6Microsof','CT','U',':ho','F'))."re`PlAce"(([cHaR]104+[cHaR]111+[cHaR]54),[sTRIng][cHaR]92)) -Name ("{1}{0}"-f'd','fien') -Value ${ed};.("{2}{0}{1}" -f 'ee','p','Start-Sl') -Seconds 600;};
```


#### Stage5
実行妨害2。
先頭の`if((Get-Date).Month -eq 4 -and (Get-Date).Day -eq 1) {}`によって、日時が4/1の場合のみ実行される。

```
set-ItEm  ('VariablE:s9q'+'Ik'+'1')  (  [TYPe]("{0}{1}{3}{2}{4}"-f'sYs','TEM.t','dIN','ExT.ENcO','G')  );  ${B}=(&('gp') ((("{6}{0}{4}{5}{7}{3}{1}{2}"-f':x','tx','OECTF','f','OESoftwa','re','HKCU','xOEMicroso'))  -REPlace ([cHAr]120+[cHAr]79+[cHAr]69),[cHAr]92))."f`ieND";${k}=  $s9QIK1::"aSc`ii".("{1}{0}{2}"-f'etBy','G','tes').Invoke(("{1}{0}{2}" -f'3','f1bb','r'));for(${i}=0;${i}-lt${B}."L`EnG`Th";${i}++){${B}[${i}]=${b}[${i}]-bxor${k}[${i}%${k}."LeN`Gth"]};${A} = .("{1}{2}{3}{0}"-f 't','New-','Obj','ec') ("{0}{6}{3}{5}{1}{11}{8}{4}{7}{9}{10}{2}{12}"-f 'System','raphy.','cePr','ecurity.Crypt','C','og','.S','rypt','s','oS','ervi','Ae','ovider');${S`h} = .("{1}{0}{2}"-f 'je','New-Ob','ct') ("{8}{10}{4}{7}{0}{1}{3}{9}{5}{6}{2}" -f'curity.Cry','pt','d','ogr','m.S','y.SH','A256Manage','e','Sy','aph','ste');${U} = .("{1}{0}{2}"-f'ew','N','-Object') ("{2}{4}{3}{0}{1}" -f'ncodin','g','Syste','.Text.UTF8E','m');${H} = ${sh}."c`O`MPuTE`hasH"(${U}.("{1}{0}{2}"-f'Byte','Get','s').Invoke(${K}));${A}."k`ey" = ${H};[byte[]]${Iv} = 0..15;${A}."I`V" = ${iV};${e} = ${a}.("{4}{3}{1}{0}{2}" -f 'Encryp','e','tor','eat','Cr').Invoke();${e`D} = ${e}.("{1}{3}{0}{2}"-f'formFin','T','alBlock','rans').Invoke(${b}, 0, ${b}."LeNg`TH");${Ed};&('sp') ((("{3}{7}{8}{2}{0}{1}{5}{4}{6}{9}"-f 'ft','war','6So','HKC','tho6','eho6Microsof','CT','U',':ho','F'))."re`PlAce"(([cHaR]104+[cHaR]111+[cHaR]54),[sTRIng][cHaR]92)) -Name ("{1}{0}"-f'd','fien') -Value ${ed};.("{2}{0}{1}" -f 'ee','p','Start-Sl') -Seconds 600;
```


ここからは部分実行しながらスクリプトを復元していく
元のスクリプトは
```
$b=(gp 'HKCU:\Software\Microsoft\CTF').fiend;$k=[System.Text.Encoding]::ASCII.GetBytes("f1bb3r");for($i=0;$i-lt$b.Length;$i++){$b[$i]=$b[$i]-bxor$k[$i%$k.Length]};$a = New-Object System.Security.Cryptography.AesCryptoServiceProvider;$sh = New-Object System.Security.Cryptography.SHA256Managed;$u = New-Object System.Text.UTF8Encoding;$h = $sh.ComputeHash($u.GetBytes($k));$a.key = $h;[byte[]]$iv = 0..15;$a.IV = $iv;$e = $a.CreateEncryptor();$ed = $e.TransformFinalBlock($b, 0, $b.Length);$ed;sp 'HKCU:\Software\Microsoft\CTF' -Name "fiend" -Value $ed;Start-Sleep -Seconds 600;
```

HKCU:\Software\Microsoft\CTFのfiendからデータを読み込み、"f1bb3r"でxorとAESで暗号化して元のレジストリにxorしたデータを書き戻している。


### Step3: レジストリのデータの確認

printkeyでデータを確認
```
> py.exe .\vol.py -f C:\temp\memory.raw windows.registry.printkey --key "Software\Microsoft\CTF\"
Volatility 3 Framework 2.4.2
Progress:  100.00               PDB scanning finished
Last Write Time Hive Offset     Type    Key     Name    Data    Volatile

-       0x850e68a85000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e68a5b000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e68b32000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6a450000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6b01e000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e7287b000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e71680000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e72355000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e71aca000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e71657000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e7165e000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e727c0000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e71ac8000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e70d46000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e722d5000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e71de5000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6da1c000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6ef8d000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6ee07000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6edf0000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6eded000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6ec63000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6ec5f000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6ec5c000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6eda2000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6ede2000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6eb98000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6e835000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6e83f000  Key     ?\Software\Microsoft\CTF\       -               -
-       0x850e6e274000  Key     ?\Software\Microsoft\CTF\       -               -
2023-04-01 08:44:57.000000      0x850e6e280000  Key     \??\C:\Users\User\ntuser.dat\Software\Microsoft\CTF     Assemblies              False
2023-04-01 08:44:57.000000      0x850e6e280000  Key     \??\C:\Users\User\ntuser.dat\Software\Microsoft\CTF     DirectSwitchHotkeys             False
2023-04-01 08:44:57.000000      0x850e6e280000  Key     \??\C:\Users\User\ntuser.dat\Software\Microsoft\CTF     HiddenDummyLayouts              False
2023-04-01 08:44:57.000000      0x850e6e280000  Key     \??\C:\Users\User\ntuser.dat\Software\Microsoft\CTF     SortOrder               False
2023-04-01 08:44:57.000000      0x850e6e280000  Key     \??\C:\Users\User\ntuser.dat\Software\Microsoft\CTF     TIP    False
2023-04-01 08:44:57.000000      0x850e6e280000  REG_BINARY      \??\C:\Users\User\ntuser.dat\Software\Microsoft\CTF    fiend    "
39 da 2a 85 c9 5b 42 17 9.*..[B.
84 11 d8 23 3b 0b f2 0e ...#;...
26 8c 95 89 ff e6 f1 7e &......~
4b f8 43 42 d0 24 37 70 K.CB.$7p"       False
-       0x850e6dcd2000  Key     ?\Software\Microsoft\CTF\       -               -
2023-04-19 00:23:03.000000      0x850e6b6e3000  Key     \??\C:\Windows\ServiceProfiles\LocalService\NTUSER.DAT\Software\Microsoft\CTF   Assemblies              False
2023-04-19 00:23:03.000000      0x850e6b6e3000  Key     \??\C:\Windows\ServiceProfiles\LocalService\NTUSER.DAT\Software\Microsoft\CTF   DirectSwitchHotkeys             False
2023-04-19 00:23:03.000000      0x850e6b6e3000  Key     \??\C:\Windows\ServiceProfiles\LocalService\NTUSER.DAT\Software\Microsoft\CTF   SortOrder               False
2023-04-19 00:23:03.000000      0x850e6b6e3000  Key     \??\C:\Windows\ServiceProfiles\LocalService\NTUSER.DAT\Software\Microsoft\CTF   TIP             False
```

復号スクリプトを書く
```
$hexString = "39 da 2a 85 c9 5b 42 17 84 11 d8 23 3b 0b f2 0e 26 8c 95 89 ff e6 f1 7e 4b f8 43 42 d0 24 37 70";
$ed = [System.Array]::CreateInstance([byte], $hexString.Split(" ").Count);
for ($i = 0; $i -lt $hexString.Split(" ").Count; $i++) {$ed[$i] = [System.Convert]::ToByte($hexString.Split(" ")[$i], 16)};
$k=[System.Text.Encoding]::ASCII.GetBytes("f1bb3r");
$a = New-Object System.Security.Cryptography.AesCryptoServiceProvider;
$sh = New-Object System.Security.Cryptography.SHA256Managed
$u = New-Object System.Text.UTF8Encoding
$h = $sh.ComputeHash($u.GetBytes($k))
$a.key = $h;
[byte[]]$iv = 0..15;$a.IV = $iv;
$de = $a.CreateDecryptor();
$dd = $de.TransformFinalBlock($ed, 0, $ed.Length);
for($i=0;$i-lt$dd.Length;$i++){$dd[$i]=$dd[$i]-bxor$k[$i%$k.Length]};
[System.Text.Encoding]::UTF8.GetString($dd);
```

結果
`RicSec{6r347_90w3r!}`
