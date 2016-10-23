@echo off
set name="Service KMSELDI"
sc stop %name% 
sc delete %name% 
set name="KMSServerService"
sc stop %name% 
sc delete %name% 
exit
