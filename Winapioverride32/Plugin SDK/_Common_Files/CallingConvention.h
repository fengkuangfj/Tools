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

#pragma once

enum tagCALLING_CONVENTION
{
    CALLING_CONVENTION_STDCALL_OR_CDECL=0,
    CALLING_CONVENTION_STDCALL,
    CALLING_CONVENTION_CDECL,
    CALLING_CONVENTION_FASTCALL,
    CALLING_CONVENTION_THISCALL,
    CALLING_CONVENTION_FASTCALL_PUSHED_LEFT_TO_RIGHT, // used for process internal call only do not use this type for APIInfo field
    CALLING_CONVENTION_ABI_x64, // classic x64 calling convention
    CALLING_CONVENTION_ABI_x64_NO_SHADOW,
    CALLING_CONVENTION_BORLAND_FASTCALL // borland fastcall parameters are passed through eax, edx, ecx + are pushed left to right on stack
};