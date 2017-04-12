@rem notice "if not %PROCESSOR_ARCHITECTURE% == AMD64 goto" can't be used because when launched from @rem vs2010, as vs 2010 IDE is always a 32 bit process, it will always return x86 instead of AMD64

@rem select VS 2010\VC directory
@set VCDIR=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\
@rem set VCDIR=C:\Program Files\Microsoft Visual Studio 10.0\VC\

@rem select compiler or cross compiler
@rem for building amd64 from amd64:   @set ARG=amd64
@rem for building amd64 from x86:     @set ARG=x86_amd64
@set ARG=amd64

@rem set all directories var for tools
@call "%VCDIR%vcvarsall.bat" %ARG%

@rem asm -> obj
@ml64.exe /c /Cx /W3 /Zi Target64.Asm 


@rem obj -> lib (allow #pragma comment(lib,"AsmRotate64.lib") usage in source code and avoid manual inclusion of obj files
@lib.exe Target64.obj /out:AsmRotate64.lib