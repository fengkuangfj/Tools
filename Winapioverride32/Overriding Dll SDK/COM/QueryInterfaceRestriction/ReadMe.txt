Goal : allow you to see how to fake COM objects methods (Microsoft TreeView Control 6, AboutBox)
	and to make fail QueryInterface (Microsoft TreeView Control 6 QueryInterface)

--------------------------------------------------------------------
How to use :
1) Launch the microsoft ActiveX Test Container (TstCon)
2) Hook TstCon.exe with WinApiOverride, and enable .COM automonitoring
3) Create new a Microsoft TreeView Control 6 control inside TstCon
4) Load overriding dll inside WinApiOverride
5) Invoke the AboutBox method in TstCon

Warning take care of WinApiOverride module filters !!! AboutBox call comes from OLEAUT32.dll,
so if you see no changes disable module filtering before calling the AboutBox method, 
or use the OVERRIDING_DLL_API_OVERRIDE_EXTENDED_OPTION_DONT_CHECK_MODULES_FILTERS option in your overriding dll
