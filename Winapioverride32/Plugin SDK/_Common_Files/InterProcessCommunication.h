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

#include "Registers.h"
#include "CallingConvention.h"


// dll  name
#define API_OVERRIDE_DLL_NAME32 _T("ApiOverride.dll")
#define HOOKNET_DLL_NAME32 _T("hooknet.dll")
#define INJECTLIB_DLL_NAME32 _T("InjLib.dll")

#define API_OVERRIDE_DLL_NAME64 _T("ApiOverride64.dll")
#define HOOKNET_DLL_NAME64 _T("hooknet64.dll")
#define INJECTLIB_DLL_NAME64 _T("InjLib64.dll")

#ifdef _WIN64
    #define INJECTLIB_DLL_NAME INJECTLIB_DLL_NAME64
    #define API_OVERRIDE_DLL_NAME API_OVERRIDE_DLL_NAME64
    #define HOOKNET_DLL_NAME HOOKNET_DLL_NAME64
#else
    #define INJECTLIB_DLL_NAME INJECTLIB_DLL_NAME32
    #define API_OVERRIDE_DLL_NAME API_OVERRIDE_DLL_NAME32
    #define HOOKNET_DLL_NAME HOOKNET_DLL_NAME32
#endif


#define APIOVERRIDE_MUTEX _T("APIOVERRIDE_MUTEX")
#define APIOVERRIDE_DEFINES_PATH _T("UserDefines\\")
#define APIOVERRIDE_USER_TYPES_PATH _T("UserTypes\\")

// MailSlots names. These names are followed by Target process Id (allow multiple instance of this soft)
#define APIOVERRIDE_MAILSLOT_TO_INJECTOR _T("\\\\.\\mailslot\\APIOVERRIDE_TO_INJECTOR")
#define APIOVERRIDE_MAILSLOT_FROM_INJECTOR _T("\\\\.\\mailslot\\APIOVERRIDE_FROM_INJECTOR")

// Events names. These names are followed by Target process Id (allow multiple instance of this soft)
//(Injector -> APIOverride)
#define APIOVERRIDE_EVENT_START_MONITORING _T("Global\\APIOVERRIDE_EVENT_START_MONITORING")
#define APIOVERRIDE_EVENT_STOP_MONITORING _T("Global\\APIOVERRIDE_EVENT_STOP_MONITORING")
#define APIOVERRIDE_EVENT_START_FAKING _T("Global\\APIOVERRIDE_EVENT_START_FAKING")
#define APIOVERRIDE_EVENT_STOP_FAKING _T("Global\\APIOVERRIDE_EVENT_STOP_FAKING")
#define APIOVERRIDE_EVENT_FREE_PROCESS _T("Global\\APIOVERRIDE_EVENT_FREE_PROCESS")
#define APIOVERRIDE_EVENT_SINGLETHREADEDMAILSLOTSERVER_END_WAITING_INSTRUCTIONS_LOOP _T("Global\\APIOVERRIDE_EVENT_END_SMS_LOOP")

// (APIOverride -> Injector)
#define APIOVERRIDE_EVENT_DLLPROCESS_ATTACH_COMPLETED _T("Global\\APIOVERRIDE_EVENT_DLLPROCESS_ATTACH_COMPLETED")
#define APIOVERRIDE_EVENT_DLL_DETACHED_COMPLETED _T("Global\\APIOVERRIDE_EVENT_DLLPROCESS_DETACHED_COMPLETED")
#define APIOVERRIDE_EVENT_PROCESS_FREE _T("Global\\APIOVERRIDE_EVENT_PROCESS_FREE")
#define APIOVERRIDE_EVENT_MONITORING_FILE_LOADED _T("Global\\APIOVERRIDE_EVENT_MONITORING_FILE_LOADED")
#define APIOVERRIDE_EVENT_MONITORING_FILE_UNLOADED _T("Global\\APIOVERRIDE_EVENT_MONITORING_FILE_UNLOADED")
#define APIOVERRIDE_EVENT_FAKE_API_DLL_LOADED _T("Global\\APIOVERRIDE_EVENT_FAKE_API_DLL_LOADED")
#define APIOVERRIDE_EVENT_FAKE_API_DLL_UNLOADED _T("Global\\APIOVERRIDE_EVENT_FAKE_API_DLL_UNLOADED")
#define APIOVERRIDE_EVENT_ERROR _T("Global\\APIOVERRIDE_EVENT_ERROR")
#define APIOVERRIDE_EVENT_CLIENT_MAILSLOT_OPEN _T("Global\\APIOVERRIDE_EVENT_MAILSLOT_OPEN")

// (Hook net -> Injector)
#define APIOVERRIDE_EVENT_HOOKNET_STARTED _T("Global\\APIOVERRIDE_EVENT_HOOKNET_STARTED")

// tag to specify internal address of software instead of a libname/funcname
#define EXE_INTERNAL_PREFIX _T("EXE_INTERNAL@0x")
#define EXE_INTERNAL_POINTER_PREFIX _T("EXE_INTERNAL_POINTER@0x")
#define EXE_INTERNAL_RVA_PREFIX _T("EXE_INTERNAL_RVA@0x")
#define EXE_INTERNAL_RVA_POINTER_PREFIX _T("EXE_INTERNAL_RVA_POINTER@0x")
// tag to specify internal address of a dll instead of an exported funcname
// allow to hook non exported function without knowing loaded bas address
#define DLL_INTERNAL_PREFIX _T("DLL_INTERNAL@0x")
#define DLL_INTERNAL_POINTER_PREFIX _T("DLL_INTERNAL_POINTER@0x")

// tag to specify ordinal exported address of a dll instead of an exported funcname
// allow to hook non exported function without knowing loaded bas address
#define DLL_ORDINAL_PREFIX _T("DLL_ORDINAL@0x")

#define DLL_OR_EXE_NET_PREFIX _T(".NET@")

///////////////////////////////////
// parameter type extended flags //
///////////////////////////////////
#define EXTENDED_TYPE_FLAG_NET_SINGLE_DIM_ARRAY     0x80000000 // used internally by injected dll only
#define EXTENDED_TYPE_FLAG_NET_MULTIPLE_DIM_ARRAY   0x40000000 // used internally by injected dll only
#define EXTENDED_TYPE_FLAG_HAS_ASSOCIATED_DEFINE_VALUES_FILE 0x20000000 // used by winapioverride and injected dll
#define EXTENDED_TYPE_FLAG_HAS_ASSOCIATED_USER_DATA_TYPE_FILE 0x10000000 // used by winapioverride and injected dll
#define EXTENDED_TYPE_FLAG_PARAM_IS_LARGE_RETURN    0x08000000 // used internally by injected dll only
#define EXTENDED_TYPE_FLAG_PARAM_STACK_LARGE_RETURN 0x04000000 // force large return to be passed on stack used internally by injected dll only
#define EXTENDED_TYPE_FLAG_POINTER_REFERENCE        0x02000000 // used by winapioverride and injected dll 
#define EXTENDED_TYPE_FLAG_X86_64BITS_RETURN        0x01000000 // x86 64bit return
//#define EXTENDED_TYPE_FLAG_                         0x008000000 // SIMPLE_TYPE_FLAG_MASK + EXTENDED_TYPE_FLAG_MASK to be changed for next EXTENDED_TYPE_FLAG_
#define EXTENDED_TYPE_FLAG_MASK                     0xFF000000 // (~SIMPLE_TYPE_FLAG_MASK)
#define SIMPLE_TYPE_FLAG_MASK                       0x00FFFFFF  // winapioverrride enum type mask (allow to use unused PARAMETER_INFOS.dwType first bytes as extended informations)
#define EXTENDED_TYPE_SetNewSimpleType(Var,NewSimpleType)( Var = ( (Var&EXTENDED_TYPE_FLAG_MASK)|NewSimpleType) ) // keep extended type, but change simple type

// struct for commands (Injector -> APIOverride)
enum tagAPIOverrideCommands
{
    CMD_LOAD_MONITORING_FILE =0,
    CMD_UNLOAD_MONITORING_FILE,
    CMD_LOAD_FAKE_API_DLL,
    CMD_UNLOAD_FAKE_API_DLL,
    CMD_FREE_PROCESS,
    CMD_MONITORING_LOG,
    CMD_PROCESS_INTERNAL_CALL_QUERY,
    CMD_PROCESS_INTERNAL_CALL_STR_PARAM_QUERY,
    CMD_PROCESS_INTERNAL_CALL_REPLY,
    CMD_START_LOG_ONLY_BASE_MODULE,
    CMD_STOP_LOG_ONLY_BASE_MODULE,
    CMD_START_MODULE_LOGGING,
    CMD_STOP_MODULE_LOGGING,
    CMD_ADD_MODULE_TO_FILTER_LIST,
    CMD_REMOVE_MODULE_FROM_FILTER_LIST,
    CMD_SET_LOGGED_MODULE_LIST_FILTERS_WAY,
    CMD_GET_LOGGED_MODULE_LIST_FILTERS_WAY_QUERY,
    CMD_GET_LOGGED_MODULE_LIST_FILTERS_WAY_REPLY,
    CMD_CLEAR_LOGGED_MODULE_LIST_FILTERS,
    CMD_ENABLE_MODULE_FILTERS_FOR_MONITORING,
    CMD_DISABLE_MODULE_FILTERS_FOR_MONITORING,
    CMD_ENABLE_MODULE_FILTERS_FOR_FAKING,
    CMD_DISABLE_MODULE_FILTERS_FOR_FAKING,
    CMD_NOT_LOGGED_MODULE_LIST_QUERY,
    CMD_NOT_LOGGED_MODULE_LIST_REPLY,
    CMD_DUMP,
    CMD_MONITORING_FILE_DEBUG_MODE,
    CMD_MONITORING_FILE_FORCE_IN_OUT_FOR_ALL_API,
    CMD_CALLSTACK_RETRIEVAL,
    CMD_AUTOANALYSIS,
    CMD_BREAK_DONT_BREAK_APIOVERRIDE_THREADS,
    CMD_REPORT_MESSAGE,
    CMD_CLEAR_USER_DATA_TYPE_CACHE,
    CMD_EXCEPTION_INFOS_WITH_STACK,
    // hook COM dll msg
    CMD_COM_HOOKING_START_STOP,
    CMD_COM_HOOKING_OPTIONS,
    CMD_COM_INTERACTION,
    CMD_COM_RELEASE_CREATED_COM_OBJECTS_FOR_STATIC_HOOKS,
    CMD_COM_RELEASE_AUTO_HOOKED_OBJECTS,
    // Hook Net dll msg
    CMD_NET_INITIALIZE_HOOKNET_DLL,
    CMD_NET_SHUTDOWN_HOOKNET_DLL,
    CMD_NET_HOOKING_START_STOP,
    CMD_NET_HOOKING_OPTIONS,
    CMD_NET_INTERACTION,
    CMD_NET_RELEASE_HOOKED_METHODS,

    // plug in to overriding dll communication
    CMD_OVERRIDING_DLL_QUERY_TO_PLUGIN,
    CMD_PLUGIN_REPLY_TO_OVERRIDING_DLL_QUERY,

	// .Net plug in interactions
	CMD_NET_HOOK_FROM_TOKEN,
	CMD_NET_UNHOOK_FROM_TOKEN,

    // thread filtering commands
    CMD_GET_THREADS_HOOKED_INFOS_LIST_QUERY,
    CMD_GET_THREADS_HOOKED_INFOS_LIST_REPLY,
    CMD_SET_THREADS_HOOKED_INFOS_LIST,

    // process interaction command
    CMD_SHOW_SECTIONS,
    CMD_SHOW_DISASM,
    CMD_SHOW_THREADS,
    CMD_SHOW_ALL_CALLSTACKS,

    // magic command : allow clean unload after WinApiOverride crash
    CMD_UNLOAD_ALL // provide a clean way for unloading after a winapioverride crash
};

// types of report messages
// DON'T CHANGE EXISTING VALUES TO AVOID TROUBLES RELOADING OLD MONITORING FILES
enum tagMessageType
{
    // do not use 0 : reserved for logs in log list entry (see CApiOverride ENTRY_LOG)
    MESSAGE_INFORMATION=1,
    MESSAGE_WARNING=2,
    MESSAGE_ERROR=3,
    MESSAGE_EXCEPTION=4,
    MESSAGE_EXCEPTION_CATCHED=5,
    MESSAGE_NET_EXCEPTION_WITH_STACK=6

    // do not use 0x1000 : reserved for exception info with stack in log list entry (see CApiOverride ENTRY_EXCEPTION_INFOS_WITH_STACK)
    // ENTRY_EXCEPTION_INFOS_WITH_STACK=0x1000,
};

enum tagFirstBytesAutoAnalysis
{
    FIRST_BYTES_AUTO_ANALYSIS_NONE=0,    // no first bytes analysis is done
    FIRST_BYTES_AUTO_ANALYSIS_SECURE,  // first bytes analysis is done and used only 
                                       // - if first instruction length is more than HOOK_SIZE
                                       // - if first bytes match a well known sequence
    FIRST_BYTES_AUTO_ANALYSIS_INSECURE// first bytes analysis is done and used even 
                                       // if first instruction length is less than HOOK_SIZE
};

enum tagProcessorType
{
    ProcessorType_X86 = 0, // default one
    ProcessorType_AMD64,

    ProcessorType_UNDEFINED
};

FORCEINLINE const TCHAR* GetProcessorTypeString(tagProcessorType ProcessorType)
{
    switch (ProcessorType)
    {
    case ProcessorType_AMD64:
#ifdef _WIN64
    default:
#endif
        return TEXT("64 bits");
    case ProcessorType_X86:
#ifndef _WIN64
    default:
#endif
        return TEXT("32 bits");
    }
}

#ifndef GetCurrentProcessorType
#ifdef _WIN64
    #define GetCurrentProcessorType() (ProcessorType_AMD64)
#else
    #define GetCurrentProcessorType() (ProcessorType_X86)
#endif

#endif

enum tagFilteringWay
{
    FILTERING_WAY_ONLY_SPECIFIED_MODULES=0,
    FILTERING_WAY_NOT_SPECIFIED_MODULES,
    FILTERING_WAY_DONT_USE_LIST // pseudo type used only by CApiOverride, not in injected dll
};

#pragma pack(push)
#pragma pack(8)

#define MAX_CMD_PARAMS 10
typedef struct _STRUCT_COMMAND // standard command for data exchange between exe and ApiOverride.dll
{
    DWORD dwCommand_ID;// must be at first position // let DWORD : better for 32 - 64 bit cross injection
    union {
        TCHAR pszStringParam[MAX_PATH];
        DWORD Param[MAX_CMD_PARAMS];
    };
}STRUCT_COMMAND,*PSTRUCT_COMMAND;

// struct for api logging (APIOverride -> Injector)
enum tagParamDirectionType// Param direction type enum
{
    PARAM_DIR_TYPE_IN=0,
    PARAM_DIR_TYPE_OUT,
    PARAM_DIR_TYPE_IN_NO_RETURN,
    PARAM_DIR_TYPE_INOUT_PART_IN_NO_RETURN, // act like PARAM_DIR_TYPE_IN_NO_RETURN, just specifies that there is an associated PARAM_DIR_TYPE_INOUT_PART_OUT log (needed for quicker logs post processing)
    PARAM_DIR_TYPE_INOUT_PART_OUT,// act like PARAM_DIR_TYPE_OUT, just specifies that there is an associated PARAM_DIR_TYPE_INOUT_PART_IN_NO_RETURN log (needed for quicker logs post processing)
};

#define IsInNoRetParamDirectionType(x) ( (x == PARAM_DIR_TYPE_IN_NO_RETURN) || (x == PARAM_DIR_TYPE_INOUT_PART_IN_NO_RETURN) )
#define IsReturnValueAvailable(x) (!IsInNoRetParamDirectionType(x))
#define IsOutParamDirectionType(x) ( (x == PARAM_DIR_TYPE_OUT) || (x == PARAM_DIR_TYPE_INOUT_PART_OUT) )
#define IsInOutParamDirectionType(x) ( (x == PARAM_DIR_TYPE_INOUT_PART_IN_NO_RETURN) || (x == PARAM_DIR_TYPE_INOUT_PART_OUT) )

#define ParamDirectionTypeString_MAX_LENGTH 16
inline TCHAR* GetParamDirectionTypeString(tagParamDirectionType ParamDirectionType)
{
    // Warning ParamDirectionTypeString_MAX_LENGTH must be changed if following fields are modified !!!
    switch (ParamDirectionType)
    {
    case PARAM_DIR_TYPE_IN:
        return TEXT("In");
    case PARAM_DIR_TYPE_OUT:
        return TEXT("Out");
    case PARAM_DIR_TYPE_IN_NO_RETURN:
        return TEXT("In No Return");
    case PARAM_DIR_TYPE_INOUT_PART_IN_NO_RETURN:
        return TEXT("InOut (In part)");
    case PARAM_DIR_TYPE_INOUT_PART_OUT:
        return TEXT("InOut (Out part)");
    default:
#ifdef _DEBUG
        if (::IsDebuggerPresent())
            ::DebugBreak();
#endif
        return TEXT("");
    }
}

enum HOOK_TYPE // used in saved logged files : don't change values
{
    HOOK_TYPE_API=0, // must be 0 (used as default value, no need to be changed after an allocation with zeromemory)
    HOOK_TYPE_COM=1,
    HOOK_TYPE_NET=2
};

typedef struct tagExtendedFunctionInfosForNET
{
    ULONG32 FunctionToken;
}EXTENDED_FUNCTION_INFOS_FOR_NET;
typedef struct tagExtendedFunctionInfosForCOM
{
    CLSID ClassID;
    IID InterfaceID;
    DWORD VTBLIndex;
}EXTENDED_FUNCTION_INFOS_FOR_COM;

union tagExtendedFunctionInfosForHookType
{
    tagExtendedFunctionInfosForCOM InfosForCOM;
    tagExtendedFunctionInfosForNET InfosForNET;
};

typedef struct tagLogEntryFixedSize
{
    // Warning begin of common log entry this allow to have tagLogEntryFixedSize, tagExceptionInfosWithStackEntry and tagReportEntry (see IApiOverride tagCommonLogEntryStructBegin) same structure begin and so easier parsing
    DWORD dwProcessId;
    DWORD dwThreadId;
    FILETIME CallTime;   // time of call in 100 ns
    FILETIME FirstHookedParentCallTime;// id of the first previous hooked caller, null if no parent 
                                        // use logged caller start time (CallTime) as it is unique by thread
                                        // this field is useful only for call stack analysis
    // end of common log entry

    ULONG64 pOriginAddress;// caller virtual address (VA)
    ULONG64 RelativeAddressFromCallingModuleName;// caller relative virtual address (RVA)

    ULONG64 ReturnValue; // return value (content of eax/rax)
    double DoubleResult; // floating return (float or double)

    DWORD dwLastError;   // value returned by GetLastError after api call
    DWORD dwLastErrorBeforeCall;// value returned by GetLastError before api call
    DWORD dwCallDuration;// duration of the api call in us

    BOOLEAN bFailure;// don't use bSuccess because as memory is set to 0 by default, default value is FALSE
                     // Using bFailure allow to have a successful return for undefined Failure returned type
    BOOLEAN bReturnExtended;// before 6.1 : BYTE _DummyForAlign;
    BYTE bParamDirectionType; // tagParamDirectionType:  InNoRet, In, Out, InOut ( PARAM_DIR_TYPE_IN,PARAM_DIR_TYPE_OUT,PARAM_DIR_TYPE_IN_NO_RETURN )
    BYTE bNumberOfParameters;
    WORD CallStackSize;// number of caller found
    WORD CallStackEbpRetrievalSize;// (number of stack parameters to retrieve for each caller function found) * sizeof(PBYTE)


    HOOK_TYPE HookType; // specify hook type API / COM / NET
    DWORD dwCallDurationWithHookDuration;// duration of the api call + duration of hook extra treatment in us
}LOG_ENTRY_FIXED_SIZE,*PLOG_ENTRY_FIXED_SIZE;

#define PARAMETER_LOG_INFOS_PARAM_NAME_MAX_SIZE 40

typedef struct tagParameterLogInfos
// /!\ WARNING IF MODIFIED, tagParameterLogInfos32 in SupportedParameters.h must be modified
{
    DWORD dwType;
    PBYTE Value;// if (dwSizeOfPointedValue >0 )
                // {
                //      Value = pointer value // data value is in pbValue
                // }
                // else
                // {
                //      if (dwSizeOfData < REGISTER_BYTE_SIZE) // direct data value
                //          {Value = value of parameter}
                //      else 
                //          {value is stored in pbValue and Value = 0}
                // }
    DWORD dwSizeOfData;// size of Data. If <=REGISTER_BYTE_SIZE param value is stored in Value (no memory allocation) else in pbValue 
    DWORD dwSizeOfPointedValue;// size of pbValue.
    TCHAR pszParameterName[PARAMETER_LOG_INFOS_PARAM_NAME_MAX_SIZE];
    BYTE* pbValue;// content of data if dwSizeOfData > REGISTER_BYTE_SIZE
                  // content of pointer if dwSizeOfPointedData > 0
                  // NULL if (dwSizeOfData <= REGISTER_BYTE_SIZE) && (dwSizeOfPointedData==0)
    TCHAR* pszDefineNamesFile; 
    TCHAR* pszUserDataTypeName;
}PARAMETER_LOG_INFOS,*PPARAMETER_LOG_INFOS;

typedef struct _STRUCT_FUNC_PARAM
{
    BOOL bPassAsRef;    // true if param is pass as ref
    DWORD dwDataSize;   // size in byte
    ULONG64 pData;        // pointer to data // changed from PBYTE to ULONG64 for 32bit hooking compatibility from WinApiOverride64
    
    DWORD/*tagSupportedParameters*/ Type;// used only for WIN64 to know if parameter is passed through xmm register
                                // no #ifdef _WIN64 for 32bit hooking compatibility from WinApiOverride64
}STRUCT_FUNC_PARAM,*PSTRUCT_FUNC_PARAM;

typedef struct tagApiOverrideThreadsInfos
{
    DWORD ThreadId;
    /*DWORD*/ BOOL Hooked;
}API_OVERRIDE_THREADS_INFOS;

#pragma pack(pop)