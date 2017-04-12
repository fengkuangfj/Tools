Goal : add pre + post + overriding functions on .NET target

--------------------------------------------------------------------
How to use :
1) Enable .NET Hooking in WinApiOverride
2) start NET_Target.exe
3) Hook NET_Target with WinApiOverride
4) Load overriding dll inside WinApiOverride
5) click the NET_Target button

Warning take care of WinApiOverride module filters !!! 
.NET Forms callback (like button clicks) are called by System.Windows.Forms.XXX.dll,
so disable/adjust module filtering in winapioverride or 
use the OVERRIDING_DLL_API_OVERRIDE_EXTENDED_OPTION_DONT_CHECK_MODULES_FILTERS option in your overriding dll
