/*
Copyright (C) 2004 Jacquelin POTIER <jacquelin.potier@free.fr>
Dynamic aspect ratio code Copyright (C) 2004 Jacquelin POTIER <jacquelin.potier@free.fr>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <Windows.h>
#pragma warning (push)
#pragma warning(disable : 4005)// for '_stprintf' : macro redefinition in tchar.h
#include <TCHAR.h>
#pragma warning (pop)

extern "C" BOOL AsmRotate64();
#pragma comment (lib,"AsmRotate64.lib")

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                   )
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nCmdShow);
    UNREFERENCED_PARAMETER(lpCmdLine);


    if (AsmRotate64())
    {
        ::MessageBox(NULL,_T("Good registers values"),_T("Success"),MB_OK | MB_ICONINFORMATION);
    }
    else
    {
        ::MessageBox(NULL,_T("Bad registers values"),_T("Error"),MB_OK | MB_ICONERROR);
    }

    return 0;
}