Goal : show how to override an exe internal function

--------------------------------------------------------------------
How to Build :
1) build Target Sample
2) With DebugInfoViewer, get RVA of StupidAdd function
3) update FakeAPI.cpp array if necessary (replace the EXE_INTERNAL_RVA@XXXX by the new RVA)
4) build dll

--------------------------------------------------------------------
How to use :
1) Run target, and click "Exe Internal Call" button.
	You will see the result of a stupid add.
2) Run WinApiOverride and hook target
3) load the overriding dll (FakeExeInternal.dll) with WinApiOverride
4) click "Exe Internal Call" button again
	You will see the result of your dll code (a multiplication)