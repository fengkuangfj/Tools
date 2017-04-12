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

#include "IApiOverride.h"
#include "IWinApiOverrideOptions.h"
#include "IWinApiOverrideLogs.h"
#include "IWinApiOverrideMenu.h"

class IWinApiOverrideRaiseEvents
{
public:
    virtual void STDMETHODCALLTYPE RaiseEventAfterProcessHooking(IApiOverride* pApiOverride)=0;
    virtual void STDMETHODCALLTYPE RaiseEventBeforeProcessUnhooking(IApiOverride* pApiOverride)=0;
};

class IWinApiOverride:protected IUnknown // currently protected but may will change in case of COM implementation
{
public:
    // return FALSE to stop foreach (break like), TRUE to continue it
    typedef BOOL (STDMETHODCALLTYPE *pfForEachApiOverrideItemCallBack)(IApiOverride* pApiOverride,PVOID UserParam);

    // to report messages to listview
    virtual void STDMETHODCALLTYPE ReportMessage(TCHAR* pszMsg, tagMessageType MsgType)=0;
    virtual void ReportHookedProcess(IApiOverride* pApiOverride,DWORD ProcessId,BOOL bSuccess)=0;
    virtual void ReportUnhookedProcess(IApiOverride* pApiOverride,BOOL bSuccess)=0;

    // logs
    virtual IWinApiOverrideLogs* STDMETHODCALLTYPE GetLogsInterface()=0;

    // options
    virtual IWinApiOverrideOptions* STDMETHODCALLTYPE CreateOptions()=0;
    virtual void STDMETHODCALLTYPE DestroyOptions(IWinApiOverrideOptions* pOptions)=0;
    virtual IWinApiOverrideOptions* STDMETHODCALLTYPE GetOptions()=0;// options for all hooked processes Options
    virtual BOOL STDMETHODCALLTYPE UpdateGUIFromOptions()=0;// update gui from options
    virtual BOOL STDMETHODCALLTYPE UpdateOptionsFromGUI()=0;// update options from gui

    // Enumerates all ApiOverride Items
    virtual void STDMETHODCALLTYPE ForEachApiOverrideItem(pfForEachApiOverrideItemCallBack CallBack,PVOID UserParam)=0;

    virtual IApiOverride* STDMETHODCALLTYPE CreateApiOverride()=0;
    virtual void STDMETHODCALLTYPE DestroyApiOverride(IApiOverride* pApiOverride)=0;
    // MUST BE CALLED FOR A WINAPIOVERRIDE INTEGRATION
    // call order : 
    //      1) SetBeforeStartOptions
    //      2) pApiOverride->Start
    //      3) SetAfterStartOptions [MUST BE CALLED IN CallBackBeforeAppResume for START_WAY_LAUNCH_APPLICATION way]
    virtual BOOL STDMETHODCALLTYPE SetBeforeStartOptions(IApiOverride* pApiOverride,IWinApiOverrideOptions* pOptions)=0;
    virtual BOOL STDMETHODCALLTYPE SetAfterStartOptions(IApiOverride* pApiOverride,IWinApiOverrideOptions* pOptions)=0;

    // MUST BE CALLED FOR A WINAPIOVERRIDE INTEGRATION instead of pApiOverride->Stop, 
    virtual BOOL STDMETHODCALLTYPE StopApiOverride(IApiOverride* pApiOverride)=0;

    // the following functions applies for all apioverride objects and update GUI
    virtual BOOL STDMETHODCALLTYPE StartStop(BOOL Start)=0;
    
    // close WinApiOverride software
    virtual void STDMETHODCALLTYPE Close()=0;// query close operation. Returns before Winapioverride Stops (use your plugin "Destroy" method to get a more close event)
    
    // load a monitoring file in all hooked processes
    virtual BOOL STDMETHODCALLTYPE LoadMonitoringFile(TCHAR* pszFile)=0;
    virtual BOOL STDMETHODCALLTYPE UnloadMonitoringFile(TCHAR* pszFile)=0;
    virtual BOOL STDMETHODCALLTYPE StartStopMonitoring(BOOL Start)=0;

    // load an overriding dll in all hooked processes
    virtual BOOL STDMETHODCALLTYPE LoadOverridingFile(TCHAR* pszFile)=0;
    virtual BOOL STDMETHODCALLTYPE UnloadOverridingFile(TCHAR* pszFile)=0;
    virtual BOOL STDMETHODCALLTYPE StartStopFaking(BOOL Start)=0;

    virtual BOOL STDMETHODCALLTYPE LogOnlyBaseModule(BOOL OnlyBaseModule)=0;
    virtual BOOL STDMETHODCALLTYPE StartStopCOMHooking(BOOL Start)=0;
    virtual BOOL STDMETHODCALLTYPE StartStopNETHooking(BOOL Start)=0;

    // load all monitoring files present in listbox into specified hooked process
    virtual BOOL STDMETHODCALLTYPE LoadCurrentMonitoringFiles(IApiOverride* pApiOverride)=0;
    // load all overriding files present in listbox into specified hooked process
    virtual BOOL STDMETHODCALLTYPE LoadCurrentOverridingFiles(IApiOverride* pApiOverride)=0;

    // jump to log id
    virtual void STDMETHODCALLTYPE JumpToLogId(DWORD LogId,BOOL bSetForegroundWindow)=0;
    virtual void STDMETHODCALLTYPE CompareLogs(LOG_ENTRY* pLog1,LOG_ENTRY* pLog2)=0;
    virtual void STDMETHODCALLTYPE CompareLogsFiles(TCHAR* LogsFileName1,TCHAR* LogsFileName2)=0;

    // detailed stats
    virtual void STDMETHODCALLTYPE ShowStatsDetailsForSelectedFunction()=0;
    virtual void STDMETHODCALLTYPE ShowTimingChartForAllFunctions()=0;
    virtual void STDMETHODCALLTYPE ShowTimingChartForSelectedFunctions()=0;

    // sequence auto-detection
    typedef enum tagSequenceAutoDetectionFavor
    {
        SequenceAutoDetection_FavorSequenceLenght=0,
        SequenceAutoDetection_FavorRepetitionCount
    };
    virtual void STDMETHODCALLTYPE SequencesAutoDetect(BOOL SearchCrossThreadsSequence,
                                                        BOOL SearchCrossProcessesSequence,
                                                        DWORD MinNbRepeatTimeForSequence,
                                                        DWORD MinNbDifferentFunctionCallForSequence,
                                                        tagSequenceAutoDetectionFavor Favor)=0;

    // known sequence detection
    virtual void STDMETHODCALLTYPE KnownSequencesSearchAll()=0;
    virtual void STDMETHODCALLTYPE KnownSequencesSearch(TCHAR** FileNameArray,SIZE_T FileNameArraySize)=0;


    /////////////////////////////////////////////////////////////////////////
    // plugin menu
    /////////////////////////////////////////////////////////////////////////
    // allow plug in to have menu and sub menu entries in the plug in menu
    virtual IWinApiOverrideMenu* STDMETHODCALLTYPE GetPluginMenu()=0;
    virtual IWinApiOverrideMenu* STDMETHODCALLTYPE CreateMenu(IWinApiOverrideMenu* pParentMenu)=0;// pParentMenu = NULL for Plug in Menu
    virtual void STDMETHODCALLTYPE DestroyMenu(IWinApiOverrideMenu* pMenu)=0;

    // for auto updaters or check for update at startup
    virtual BOOL STDMETHODCALLTYPE CheckForUpdate(BOOL* pbNewVersionIsAvailable,WCHAR** ppDownloadLink)=0;

    // RaiseEvents
    virtual IWinApiOverrideRaiseEvents* STDMETHODCALLTYPE GetRaiseEventsInterface()=0;
};


// next version : IWinApiOverride2:public IWinApiOverride