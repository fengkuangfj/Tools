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

//-----------------------------------------------------------------------------
// Object: winapioverride options interface
//-----------------------------------------------------------------------------

#pragma once

#define IWinApiOverrideOptions_DEBUG_SYMBOLS_SERVER_MAX_SIZE 4096
#define IWinApiOverrideOptions_MAX_SIZE 512
#define IWinApiOverrideOptions_MAX_COMMAND_LINE 2048

class IWinApiOverrideOptions
{
public:
    virtual BOOL Load(TCHAR* OptionsFileName)=0; // load current winapioverride options from a configuration file
    virtual BOOL Save(TCHAR* OptionsFileName)=0;
    virtual HOOK_COM_OPTIONS* GetComOptionsPointer()=0; // to change options, just act on returned pointer fields
    virtual HOOK_NET_OPTIONS* GetNetOptionsPointer()=0; // to change options, just act on returned pointer fields

    TCHAR* FileName;
    enum tagStartWay
    {
        START_WAY_PID=0,
        START_WAY_LAUNCH_APPLICATION,
        START_WAY_ALL_PROCESSES
    };

    TCHAR ExclusionFiltersModulesFileList[MAX_PATH];
    TCHAR InclusionFiltersModulesFileList[MAX_PATH];
    TCHAR StartupApplicationPath[MAX_PATH];
    TCHAR StartupApplicationCmd[IWinApiOverrideOptions_MAX_COMMAND_LINE];
    TCHAR AllProcessesInclusion[IWinApiOverrideOptions_MAX_SIZE];
    TCHAR AllProcessesExclusion[IWinApiOverrideOptions_MAX_SIZE];
    TCHAR AllProcessesParentInclusion[IWinApiOverrideOptions_MAX_SIZE];
    TCHAR AllProcessesParentExclusion[IWinApiOverrideOptions_MAX_SIZE];
    TCHAR AllProcessesParentPID[IWinApiOverrideOptions_MAX_SIZE];
    TCHAR StartupApplicationPID[IWinApiOverrideOptions_MAX_SIZE];
    BOOL StartupApplicationbOnlyAfter;
    DWORD StartupApplicationOnlyAfterMs;
    BOOL StartAllProcessesbOnlyAfter;
    DWORD StartAllProcessesOnlyAfterMs;
    BOOL ExportOnlySelected;
    BOOL ExportOnlyVisible;
    BOOL ExportFullParametersContent;
    tagFirstBytesAutoAnalysis AutoAnalysis;
    BOOL bLogCallStack;
    BOOL bMonitoringFileDebugMode;
    BOOL bMonitoringForceInOutForAllApi;
    BOOL bOnlyBaseModule;
    DWORD CallStackNbParameters;
    BOOL bFiltersApplyToMonitoring;
    BOOL bFiltersApplyToOverriding;
    tagStartWay StartWay;
    BOOL bFilterModulesFileListIsExclusionList;
    BOOL bUseFilterModulesFileList;
    BOOL BreakDialogDontBreakAPIOverrideThreads;
    BOOL bAllowTlsCallbackHooks;
    BOOL bComAutoHookingEnabled;
    BOOL bNetAutoHookingEnabled;
    BOOL bNetProfilingEnabled;
    BOOL bExeIATHooks;
    BOOL StopAndKillAfter;
    SIZE_T StopAndKillAfterMs;
    BOOL bUseDebugSymbolsServer;
    TCHAR DebugSymbolsServer[IWinApiOverrideOptions_DEBUG_SYMBOLS_SERVER_MAX_SIZE];
    BOOL bPreferCsrssHookToSpyNewCreatedProcesses;
    BOOL AllProcessesFiltersInclude32bitsProcesses;
    BOOL AllProcessesFiltersInclude64bitsProcesses;
    BOOL bWizardFunctionNameFilterEnabled;
    BOOL bSingleAppHookAtStartupAutoResumeAndAutoReload;
    BOOL bAskToSaveLogsListChanges;
    BOOL LogListTreeViewMode;

    BOOL LogListAutoScrollDelayRefreshEnabled;
    UINT LogListAutoScrollDelayRefreshTimeInMs;
    DWORD LogListMaxOneParameterStringSizeForCallColumn;
    BOOL SyntaxHighlightingEnabled;
    BOOL ThreadsHighlightingEnabled;
    BOOL SyntaxHighlightingShowNameForSubTypes;
    BOOL SyntaxHighlightingShowDefineRawValue;
    BOOL SyntaxHighlightingShowPointerForValidString;
    COLORREF ColorFunction  ;
    COLORREF ColorString    ;
    COLORREF ColorNumber    ;
    COLORREF ColorDefine    ;
    COLORREF ColorPointer   ;
    COLORREF ColorEnum      ;
    COLORREF ColorSyntax    ;
    COLORREF ColorBadPointer;
};