/*
Copyright (C) 2004 Jacquelin POTIER <jacquelin.potier@free.fr>
Dynamic aspect ratio code Copyright (C) 2004 Jacquelin POTIER <jacquelin.potier@free.fr>

This program is free software=0; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation=0; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY=0; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program=0; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//-----------------------------------------------------------------------------
// Object: Apioverride object interface
//-----------------------------------------------------------------------------

#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 // for xp os
#endif
#include <windows.h>

#pragma warning (push)
#pragma warning(disable : 4005)// for '_stprintf' : macro redefinition in tchar.h
#include <TCHAR.h>
#pragma warning (pop)
#include "InterProcessCommunication.h"
#include "HookCom/HookComOptions.h"
#include "HookNet/HookNetOptions.h"

#define REPORT_MESSAGE_NO_PROCESS_ID 0xffffffff
#define REPORT_MESSAGE_NO_THREAD_ID  0xffffffff

// common struct used to get begin of tagLogEntryFixedSize, tagExceptionInfosWithStackEntry and tagReportEntry (see IApiOverride)
typedef struct tagCommonLogEntryStructBegin
{
    DWORD ProcessId;
    DWORD ThreadId;
    FILETIME Time;
    FILETIME ParentTime;
}COMMON_LOG_ENTRY_STRUCT_BEGIN;

typedef struct tagCallStackItemInfo
{
    PBYTE  Address;
    PBYTE  RelativeAddress;
    PBYTE  Parameters;
    TCHAR* pszModuleName;
}CALLSTACK_ITEM_INFO,*PCALLSTACK_ITEM_INFO;

typedef struct tagLogEntry
{
    tagProcessorType ProcessorType; // x86, AMD64
    PLOG_ENTRY_FIXED_SIZE pHookInfos; // according to ProcessorType
    REGISTERS RegistersBeforeCall;
    REGISTERS RegistersAfterCall;
    TCHAR* pszModuleName;
    TCHAR* pszApiName;
    TCHAR* pszCallingModuleName;
    PPARAMETER_LOG_INFOS ParametersInfoArray;// number of items is defined by pHookInfos->bNumberOfParameters
    PCALLSTACK_ITEM_INFO CallSackInfoArray;// number of items is defined by pHookInfos->CallStackSize
    tagExtendedFunctionInfosForHookType HookTypeExtendedFunctionInfos; // contains extended informations to uniquely identify function
    PPARAMETER_LOG_INFOS pReturnExtended;// extended return informations if not NULL (if NULL, that means return has no extended informations)
}LOG_ENTRY,*PLOG_ENTRY;

// types of logs
// DON'T CHANGE EXISTING VALUES TO AVOID TROUBLES RELOADING OLD MONITORING FILES
enum tagLogListEntryTypes
{
    ENTRY_LOG=0,
    ENTRY_MSG_INFORMATION=MESSAGE_INFORMATION,
    ENTRY_MSG_WARNING=MESSAGE_WARNING,
    ENTRY_MSG_ERROR=MESSAGE_ERROR,
    ENTRY_MSG_EXCEPTION=MESSAGE_EXCEPTION,
    ENTRY_MSG_EXCEPTION_CATCHED=MESSAGE_EXCEPTION_CATCHED,
    ENTRY_MSG_NET_EXCEPTION_WITH_STACK=MESSAGE_NET_EXCEPTION_WITH_STACK,
    // let space for other string messages (see tagMessageType)

    // non string messages
    ENTRY_EXCEPTION_INFOS_WITH_STACK=0x1000,
};

typedef struct tagExceptionInfosWithStackEntry
{
    // Warning begin of common log entry (see InterProcessCommunication, this allow to have tagLogEntryFixedSize, tagExceptionInfosWithStackEntry and tagReportEntry same structure begin and so easier parsing
    DWORD ProcessId;
    DWORD ThreadId;
    FILETIME ExceptionTime;
    FILETIME FirstHookedParentCallTime;
    // end of common log entry
    ULONG64 ExceptionAddress;
    TCHAR* pExceptionModulePath;
    tagProcessorType ProcessorType;
    DWORD ExceptionRelativeAddress;
    REGISTERS ExceptionContext;
    TCHAR* pExceptionMsg;
    // call stack
    PCALLSTACK_ITEM_INFO CallSackInfoArray;
    WORD CallStackSize;// number of caller found
    WORD CallStackEbpRetrievalSize;// (number of stack parameters to retrieve for each caller function found) * sizeof(PBYTE)
    
}EXCEPTION_INFOS_WITH_STACK_ENTRY,*PEXCEPTION_INFOS_WITH_STACK_ENTRY;

typedef struct tagReportEntry
{
    // Warning begin of common log entry (see InterProcessCommunication, this allow to have tagLogEntryFixedSize, tagExceptionInfosWithStackEntry and tagReportEntry same structure begin and so easier parsing
    DWORD ProcessId;
    DWORD ThreadId;
    FILETIME ReportTime;
    FILETIME FirstHookedParentCallTime;
    // end of common log entry
    TCHAR* pUserMsg;
}REPORT_ENTRY,*PREPORT_ENTRY;

typedef struct tagLogListEntry
{
    DWORD dwId;
    tagLogListEntryTypes Type;// log or information
    union
    {
        LOG_ENTRY* pLog;
        EXCEPTION_INFOS_WITH_STACK_ENTRY* pExceptionInfosWithStackEntry;
        REPORT_ENTRY ReportEntry;
    };
}LOG_LIST_ENTRY,*PLOG_LIST_ENTRY;


typedef void (STDMETHODCALLTYPE *tagCallBackLogFunc)(LOG_ENTRY* pLog,PVOID pUserParam);
typedef void (STDMETHODCALLTYPE *tagCallBackExceptionInfosFunc)(EXCEPTION_INFOS_WITH_STACK_ENTRY* pExceptionInfosWithStackEntry,PVOID pUserParam);
typedef void (STDMETHODCALLTYPE *tagCallBackUnexpectedUnload)(DWORD dwProcessID,PVOID pUserParam);
typedef void (STDMETHODCALLTYPE *tagpCallBackBeforeAppResume)(DWORD dwProcessID,PVOID pUserParam);
typedef void (STDMETHODCALLTYPE *tagCallBackReportMessages)(tagMessageType ReportMessageType,TCHAR* ReportMessage,FILETIME FileTime,FILETIME ParentCallTime,DWORD ProcessId,DWORD ThreadId,LPVOID UserParam);
typedef void (STDMETHODCALLTYPE *tagpCallBackBeforeAppResume)(DWORD dwProcessID,PVOID pUserParam);
typedef void (STDMETHODCALLTYPE *tagpCallBackOverridingDllQuery)(TCHAR* PluginName,PVOID MessageId,PBYTE pMsg,SIZE_T MsgSize,PVOID UserParam);
typedef void (STDMETHODCALLTYPE *tagCallBackErrorUserMessages)(TCHAR* ErrorMessage,LPVOID UserParam);

typedef struct tagRemoteCallInfos
{
    PBYTE ProcessInternalCallReply;
    HANDLE hevtProcessInternalCallReply;
}REMOTE_CALL_INFOS,*PREMOTE_CALL_INFOS;

class IApiOverride
{
public:
    enum StartWays
    {
        StartWaySleep,
        StartWaySuspended,
        StartWayIAT
    };

    enum tagColumnsIndex
    {
        ColumnsIndexId=0,
        ColumnsIndexDirection,
        ColumnsIndexCall,
        ColumnsIndexReturnValue,
        ColumnsIndexCallerAddress,
        ColumnsIndexCallerRelativeAddress,
        ColumnsIndexProcessID,
        ColumnsIndexThreadID,
        ColumnsIndexLastError,
        ColumnsIndexRegistersBeforeCall,
        ColumnsIndexRegistersAfterCall,
        ColumnsIndexDoubleReturnValue,
        ColumnsIndexFloatReturnValue,
        ColumnsIndexCallTime,
        ColumnsIndexCallDuration,
        ColumnsIndexModuleName,
        ColumnsIndexAPIName,
        ColumnsIndexCallerFullPath,

        NbColumns,// delimiter, must be at the end of the enum
        FirstColumn = 0,// delimiter
        LastColumn = (NbColumns-1)// delimiter
    };

    enum tagProcessInternalCall_ResultParsingType
    {
        ProcessInternalCall_ResultParsingType_NONE,
        ProcessInternalCall_ResultParsingType_EXCLUDE_REGISTERS,
        ProcessInternalCall_ResultParsingType_COMPLETE
    };

    virtual BOOL STDMETHODCALLTYPE SetParentWindow(HWND hParentWindow)=0;
    virtual HWND STDMETHODCALLTYPE GetParentWindow()=0;

    virtual BOOL STDMETHODCALLTYPE LoadMonitoringFile(TCHAR* pszFileName)=0;
    virtual BOOL STDMETHODCALLTYPE UnloadMonitoringFile(TCHAR* pszFileName)=0;
    virtual BOOL STDMETHODCALLTYPE LoadFakeAPI(TCHAR* pszFileName)=0;
    virtual BOOL STDMETHODCALLTYPE UnloadFakeAPI(TCHAR* pszFileName)=0;

    virtual BOOL STDMETHODCALLTYPE StartMonitoring()=0;
    virtual BOOL STDMETHODCALLTYPE StopMonitoring()=0;
    virtual BOOL STDMETHODCALLTYPE StartFaking()=0;
    virtual BOOL STDMETHODCALLTYPE StopFaking()=0;

    virtual BOOL STDMETHODCALLTYPE LogOnlyBaseModule(BOOL bOnlyBaseModule)=0;
    virtual BOOL STDMETHODCALLTYPE SetModuleFilteringWay(tagFilteringWay FilteringWay)=0;
    virtual BOOL STDMETHODCALLTYPE GetModuleFilteringWay(tagFilteringWay* pFilteringWay)=0;
    virtual BOOL STDMETHODCALLTYPE SetModuleLogState(TCHAR* pszModuleFullPath,BOOL bLog)=0;
    virtual BOOL STDMETHODCALLTYPE AddToFiltersModuleList(TCHAR* pszFileName)=0;
    virtual BOOL STDMETHODCALLTYPE RemoveFromFiltersModuleList(TCHAR* pszFileName)=0;
    virtual BOOL STDMETHODCALLTYPE ClearFiltersModuleList()=0;
    virtual BOOL STDMETHODCALLTYPE GetNotLoggedModuleList(TCHAR*** pArrayNotLoggedModulesNames,DWORD* pdwArrayNotLoggedModulesNamesSize)=0;
    virtual BOOL STDMETHODCALLTYPE SetMonitoringModuleFiltersState(BOOL bEnable)=0;
    virtual BOOL STDMETHODCALLTYPE SetFakingModuleFiltersState(BOOL bEnable)=0;
    virtual BOOL STDMETHODCALLTYPE SetAutoAnalysis(tagFirstBytesAutoAnalysis AutoAnalysis)=0;
    virtual BOOL STDMETHODCALLTYPE AllowTlsCallbackHooking(BOOL bAllow)=0;
    virtual BOOL STDMETHODCALLTYPE EnableCOMAutoHooking(BOOL bEnable,BOOL ShowTryToUnhookIfNeeded)=0;
    virtual BOOL STDMETHODCALLTYPE EnableCOMAutoHooking(BOOL bEnable)=0;
    virtual BOOL STDMETHODCALLTYPE SetCOMOptions(IN HOOK_COM_OPTIONS* pComOptions)=0;
    virtual BOOL STDMETHODCALLTYPE GetCOMOptions(OUT HOOK_COM_OPTIONS* pComOptions)=0;
    virtual BOOL STDMETHODCALLTYPE ShowCOMInteractionDialog()=0;
    virtual BOOL STDMETHODCALLTYPE EnableNETProfiling(BOOL bEnable)=0;// must be called to really enable NetHooking
    virtual BOOL STDMETHODCALLTYPE EnableNetAutoHooking(BOOL bEnable)=0;// used only to signal user events (in case an application was ".Net profiled")
    // as cor profiling state can't be changed after application startup
    virtual BOOL STDMETHODCALLTYPE EnableNetAutoHooking(BOOL bEnable,BOOL ShowTryToUnhookIfNeeded)=0;// used only to signal user events (in case an application was ".Net profiled")
    // as cor profiling state can't be changed after application startup
    virtual BOOL STDMETHODCALLTYPE SetNetOptions(IN HOOK_NET_OPTIONS* pNetOptions)=0;
    virtual BOOL STDMETHODCALLTYPE GetNetOptions(OUT HOOK_NET_OPTIONS* pNetOptions)=0;
	virtual BOOL STDMETHODCALLTYPE AddHookNetFromTokenForCompiledFuntions(TCHAR* AssemblyName,SIZE_T NbToken,ULONG32* TokenArray)=0;
	virtual BOOL STDMETHODCALLTYPE RemoveHookNetFromTokenForCompiledFuntion(TCHAR* AssemblyName,SIZE_T NbToken,ULONG32* TokenArray)=0;
    virtual BOOL STDMETHODCALLTYPE ShowNetInteractionDialog()=0;
    virtual BOOL STDMETHODCALLTYPE SetCallStackRetrieval(BOOL bLogCallStack,DWORD CallStackParametersRetrievalSize)=0;
    virtual BOOL STDMETHODCALLTYPE BreakDialogDontBreakApioverrideThreads(BOOL bDontBreak)=0;
    virtual BOOL STDMETHODCALLTYPE SetMonitoringFileDebugMode(BOOL bActiveMode)=0;
    virtual BOOL STDMETHODCALLTYPE SetMonitoringAllApiInInOutMode(BOOL bEnableInOutForAllApi)=0;

    virtual BOOL STDMETHODCALLTYPE Dump()=0;

    virtual BOOL STDMETHODCALLTYPE SetErrorUserMessagesCallBack(tagCallBackErrorUserMessages pCallBackFunc,LPVOID pUserParam)=0;
    virtual BOOL STDMETHODCALLTYPE SetReportMessagesCallBack(tagCallBackReportMessages pCallBackFunc,LPVOID pUserParam)=0;
    virtual BOOL STDMETHODCALLTYPE SetUnexpectedUnloadCallBack(tagCallBackUnexpectedUnload pCallBackFunc,LPVOID pUserParam)=0;
    virtual BOOL STDMETHODCALLTYPE SetMonitoringCallback(tagCallBackLogFunc pCallBackLogFunc,LPVOID pUserParam,BOOL bManualFreeLogEntry)=0;
    virtual BOOL STDMETHODCALLTYPE SetExceptionInfosWithStackCallback(tagCallBackExceptionInfosFunc pCallBackExceptionInfosFunc,LPVOID pUserParam,BOOL bManualFreeExceptionInfosEntry)=0;
    virtual void STDMETHODCALLTYPE FreeLogEntry(LOG_ENTRY* pLog,HANDLE Heap)=0;
    virtual void STDMETHODCALLTYPE FreeExceptionInfosWithStack(EXCEPTION_INFOS_WITH_STACK_ENTRY* pExceptionInfosWithStackEntry,HANDLE Heap)=0;
    virtual BOOL STDMETHODCALLTYPE SetMonitoringListview(HWND hListView)=0;
    virtual BOOL STDMETHODCALLTYPE InitializeMonitoringListview()=0;

    virtual BOOL STDMETHODCALLTYPE AddLogEntry(LOG_LIST_ENTRY* pLogEntry,BOOL bStorePointerInListViewItemUserData)=0;
    virtual BOOL STDMETHODCALLTYPE AddLogEntry(LOG_LIST_ENTRY* pLogEntry,BOOL bStorePointerInListViewItemUserData,int Increment)=0;
    virtual BOOL STDMETHODCALLTYPE AddLogEntryEx(LOG_LIST_ENTRY* pLogEntry,PVOID PointerToStoreInListViewItemUserData2)=0;
    virtual BOOL STDMETHODCALLTYPE AddLogEntryEx(LOG_LIST_ENTRY* pLogEntry,PVOID PointerToStoreInListViewItemUserData2,int Increment)=0;
    virtual LOG_LIST_ENTRY* STDMETHODCALLTYPE GetLogEntryInfosFromListView(int ListViewItemIndex)=0;
    virtual PVOID STDMETHODCALLTYPE GetUserDataFromListView(int ListViewItemIndex)=0;

    virtual BOOL STDMETHODCALLTYPE Stop()=0;
    virtual BOOL STDMETHODCALLTYPE Start(DWORD dwPID)=0;
    virtual BOOL STDMETHODCALLTYPE Start(TCHAR* pszFileName)=0;
    virtual BOOL STDMETHODCALLTYPE Start(TCHAR* pszFileName,tagpCallBackBeforeAppResume pCallBackFunc,LPVOID pUserParam)=0;
    virtual BOOL STDMETHODCALLTYPE Start(TCHAR* pszFileName,TCHAR* pszCmdLine,tagpCallBackBeforeAppResume pCallBackFunc,LPVOID pUserParam)=0;
    virtual BOOL STDMETHODCALLTYPE Start(TCHAR* pszFileName,TCHAR* pszCmdLine,tagpCallBackBeforeAppResume pCallBackFunc,LPVOID pUserParam,StartWays StartMethod,DWORD dwResumeTimeAtStartup)=0;
    virtual BOOL STDMETHODCALLTYPE Start(TCHAR* pszFileName,TCHAR* pszCmdLine,tagpCallBackBeforeAppResume pCallBackFunc,LPVOID pUserParam,StartWays StartMethod,DWORD dwResumeTimeAtStartup,OUT STARTUPINFO* pStartupInfo,OUT PROCESS_INFORMATION* pProcessInformation)=0;
    virtual BOOL STDMETHODCALLTYPE Start(TCHAR* pszFileName,TCHAR* pszCmdLine,tagpCallBackBeforeAppResume pCallBackFunc,LPVOID pUserParam,StartWays StartMethod,DWORD dwResumeTimeAtStartup,OUT STARTUPINFO* pStartupInfo,OUT PROCESS_INFORMATION* pProcessInformation,BOOL bRunAsUser,TCHAR* UserNameUnc,TCHAR* Password)=0;
    virtual BOOL STDMETHODCALLTYPE StartAtProcessCreation(DWORD ProcessId,DWORD ThreadId,BOOL bLetThreadSuspended,tagpCallBackBeforeAppResume pCallBackFunc,PVOID pUserParam)=0;

    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,DWORD NbParams,PSTRUCT_FUNC_PARAM pParams,PBYTE* pReturnValue)=0;
    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,DWORD NbParams,PSTRUCT_FUNC_PARAM pParams,PBYTE* pReturnValue,DWORD dwTimeOutMs)=0;
    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,DWORD NbParams,PSTRUCT_FUNC_PARAM pParams,REGISTERS_UNION* pRegisters,PBYTE* pReturnValue,DWORD dwTimeOutMs)=0;
    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,DWORD NbParams,PSTRUCT_FUNC_PARAM pParams,REGISTERS_UNION* pRegisters,PBYTE* pReturnValue,double* FloatingReturn,DWORD dwTimeOutMs,DWORD ThreadId)=0;
    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,DWORD NbParams,PSTRUCT_FUNC_PARAM pParams,REGISTERS_UNION* pRegisters,PBYTE* pReturnValue,double* FloatingReturn,DWORD dwTimeOutMs,DWORD ThreadId,tagCALLING_CONVENTION CallingConvention)=0;
    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,TCHAR* Parameters,REGISTERS_UNION* pRegisters,PBYTE* pReturnValue,double* FloatingReturn,DWORD dwTimeOutMs,DWORD ThreadId,tagCALLING_CONVENTION CallingConvention)=0;
    virtual BOOL STDMETHODCALLTYPE ProcessInternalCall(TCHAR* LibName,TCHAR* FuncName,TCHAR* Parameters,REGISTERS_UNION* pRegisters,PBYTE* pReturnValue,double* FloatingReturn,DWORD dwTimeOutMs,DWORD ThreadId,tagCALLING_CONVENTION CallingConvention,BOOL* pHasOutParameter,tagProcessInternalCall_ResultParsingType ResultParsing,TCHAR** pStrResult)=0;

    virtual DWORD STDMETHODCALLTYPE GetProcessID()=0;
    virtual BOOL  STDMETHODCALLTYPE GetProcessName(TCHAR* ProcessName,DWORD ProcessNameMaxSize)=0;
    virtual BOOL  STDMETHODCALLTYPE GetProcessFullPathName(TCHAR* ProcessFullPathName,DWORD ProcessFullPathNameMaxSize)=0;

    virtual BOOL STDMETHODCALLTYPE SetMonitoringLogHeap(HANDLE Heap)=0; // must be protected by WaitAndLockMonitoringLogHeap and UnlockMonitoringLogHeap
    virtual HANDLE STDMETHODCALLTYPE GetMonitoringLogHeap()=0;
    virtual BOOL STDMETHODCALLTYPE WaitAndLockMonitoringLogHeap()=0;
    virtual BOOL STDMETHODCALLTYPE UnlockMonitoringLogHeap()=0;

    virtual BOOL STDMETHODCALLTYPE ClearUserDataTypeCache()=0;
    
    virtual BOOL STDMETHODCALLTYPE SetOverridingDllQueryCallBack(tagpCallBackOverridingDllQuery pCallBackFunc,LPVOID pUserParam)=0;
    virtual BOOL STDMETHODCALLTYPE SendReplyToOverridingDllQuery(HANDLE MessageId,PBYTE pMsg,SIZE_T MsgSize)=0;

    virtual tagProcessorType STDMETHODCALLTYPE GetHookedProcessProcessorType()=0;
    virtual float STDMETHODCALLTYPE ConvertDoubleReturnToFloatReturn(LOG_ENTRY* pLogEntry)=0;

    virtual BOOL STDMETHODCALLTYPE SetThreadsHookInfos(API_OVERRIDE_THREADS_INFOS* pThreadInfosArray,SIZE_T ThreadInfosArrayCount,BOOL HookNewThreads)=0;
    virtual BOOL STDMETHODCALLTYPE GetThreadsHookInfos(OUT API_OVERRIDE_THREADS_INFOS** ppThreadInfosArray,OUT SIZE_T* pThreadInfosArrayCount,OUT BOOL* pHookNewThreads)=0;

    virtual BOOL STDMETHODCALLTYPE ShowDisasmDialog()=0;
    virtual BOOL STDMETHODCALLTYPE ShowSectionDialog()=0;
    virtual BOOL STDMETHODCALLTYPE ShowThreadsDialog()=0;
    virtual BOOL STDMETHODCALLTYPE ShowAllCallStacksDialog()=0;

    static FORCEINLINE COMMON_LOG_ENTRY_STRUCT_BEGIN* GetCommonLogEntryStructBegin(LOG_LIST_ENTRY* pLogListEntry)
    {
        switch (pLogListEntry->Type)
        {
        case ENTRY_LOG:
            return (COMMON_LOG_ENTRY_STRUCT_BEGIN*)(pLogListEntry->pLog->pHookInfos);
        case ENTRY_EXCEPTION_INFOS_WITH_STACK:
            return (COMMON_LOG_ENTRY_STRUCT_BEGIN*)(pLogListEntry->pExceptionInfosWithStackEntry);
        default:
            return (COMMON_LOG_ENTRY_STRUCT_BEGIN*)(&pLogListEntry->ReportEntry);
        }
    }
};