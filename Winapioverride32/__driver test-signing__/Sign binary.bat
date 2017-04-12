Echo off
rem set BINDIR="C:\WinDDK\7600.16385.1\bin\x86\"
rem set BINDIR="C:\WinDDK\7600.16385.1\bin\amd64\"

set BINDIR="C:\WinDDK\7600.16385.1\bin\amd64\"
Echo On

@Echo *******************************************************************************
@Echo We will also embed sign the driver binaries.  For boot critical drivers you
@Echo should embed sign the binaries to optimize boot performance.
@Echo We will use signtool.exe to sign the binaries file.
@Echo .
@Echo Syntax: SignTool sign /s YourPrivateCertStore yourdriver.sys
@Echo                 SignTool sign /s PrivateCertStore mydriver.sys
@Echo                 SignTool sign /s PrivateCertStore mydll.dll
@Echo .
@Echo *******************************************************************************

%BINDIR%SignTool sign /a /s PrivateCertStore ../KernelMemoryAccess64.sys
%BINDIR%SignTool sign /a /s PrivateCertStore ../ProcMonDrvJP64.sys


@Echo *******************************************************************************
@Echo IMPORTANT: If you are signing a driver for public release you should be using
@Echo a Software Publisher Certificate with a Cross Certificate to the Microsoft
@Echo root.  And you should TIMESTAMP your signature.  The syntax for production
@Echo signing is:
@Echo Signtool sign /v /ac CrossCertificateFile /s SPCCertificateStore 
@Echo     /n SPCSubjectName /t http://timestamp.verisign.com /scripts/timestamp.dll
@Echo     yourCat.cat
@Echo .
@Echo For more information on signing for publication, go to:
@Echo http://www.microsoft.com/whdc/winlogo/drvsign/drvsign.mspx
@Echo *******************************************************************************