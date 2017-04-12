Echo off
rem set BINDIR="C:\WinDDK\7600.16385.1\bin\x86\"
rem set BINDIR="C:\WinDDK\7600.16385.1\bin\amd64\"

set BINDIR="C:\WinDDK\7600.16385.1\bin\amd64\"
Echo On


@Echo *******************************************************************************
@Echo First, We will create a certificate with the makecert.exe tool.
@Echo Syntax: Makecert -r -pe -ss YourCertStore -n "CN=TestCertName" TestCert.cer
@Echo *******************************************************************************
%BINDIR%Makecert -r -pe -ss PrivateCertStore -n "CN=TestCertforWDK" TestCert.cer


@Echo *******************************************************************************
@Echo Before you can install your Driver Package you must add your test certificates
@Echo into the certificate store on the target machine.
@Echo .
@Echo You can automate certificate installation using the certmgr.exe tool.
@Echo Syntax: certmgr.exe -add TestCert.cer -s -r localMachine root 
@Echo *******************************************************************************

%BINDIR%certmgr.exe -add testcert.cer -s -r localMachine root 
%BINDIR%certmgr.exe -add testcert.cer -s -r localMachine trustedpublisher