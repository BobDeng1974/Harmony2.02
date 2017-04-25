/* Created by plibgen $Revision: 1.31 $ */

#ifndef _POWER_P32MX275F256D_H
#define _POWER_P32MX275F256D_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>

#include "peripheral/peripheral_common_32bit.h"

/* Default definition used for all API dispatch functions */
#ifndef PLIB_INLINE_API
    #define PLIB_INLINE_API extern inline
#endif

/* Default definition used for all other functions */
#ifndef PLIB_INLINE
    #define PLIB_INLINE extern inline
#endif

typedef enum {

    POWER_NUMBER_OF_MODULES = 0

} POWER_MODULE_ID;

typedef enum {

    POWER_MODULE_NONE

} POWER_MODULE;

typedef enum {

    HLVD_LIMIT_NONE

} HLVD_LIMIT;

typedef enum {

    HLVD_MODE_NONE

} HLVD_MODE;

typedef enum {

    DEEP_SLEEP_MODULE_NONE

} DEEP_SLEEP_MODULE;

typedef enum {

    DEEP_SLEEP_WAKE_UP_EVENT_NONE

} DEEP_SLEEP_WAKE_UP_EVENT;

typedef enum {

    DEEP_SLEEP_EVENT_NONE

} DEEP_SLEEP_EVENT;

typedef enum {

    DEEP_SLEEP_GPR_NONE

} DEEP_SLEEP_GPR;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE PLIB_INLINE

/* Section 3 - PLIB dispatch function definitions */

PLIB_INLINE_API bool PLIB_POWER_ExistsPeripheralModuleControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_PeripheralModuleDisable(POWER_MODULE_ID index, POWER_MODULE source)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_PeripheralModuleEnable(POWER_MODULE_ID index, POWER_MODULE source)
{
     
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_PeripheralModuleIsEnabled(POWER_MODULE_ID index, POWER_MODULE source)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsVoltageRegulatorControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_VoltageRegulatorEnable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_VoltageRegulatorDisable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_VoltageRegulatorIsEnabled(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsSleepStatus(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeviceWasInSleepMode(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_ClearSleepStatus(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsIdleStatus(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeviceWasInIdleMode(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_ClearIdleStatus(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHighVoltageOnVDD1V8(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_HighVoltageOnVDD1V8HasOccurred(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepModeOccurrence(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModeHasOccurred(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepStatusClear(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHLVDEnableControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_HLVDEnable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_HLVDDisable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_HLVDIsEnabled(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHLVDStopInIdleControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_HLVDStopInIdleEnable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_HLVDStopInIdleDisable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_HLVDStopInIdleIsEnabled(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHLVDStatus(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_HLVDStatusGet(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHLVDModeControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_HLVDModeSelect(POWER_MODULE_ID index, HLVD_MODE mode)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHLVDBandGapVoltageStability(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_HLVDBandGapVoltageIsStable(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsHLVDLimitSelection(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_HLVDLimitSelect(POWER_MODULE_ID index, HLVD_LIMIT limit)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepMode(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModeEnable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModeDisable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModeIsEnabled(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepGPRsRetentionControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepGPRsRetentionEnable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepGPRsRetentionDisable(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepModuleControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModuleEnable(POWER_MODULE_ID index, DEEP_SLEEP_MODULE module)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModuleDisable(POWER_MODULE_ID index, DEEP_SLEEP_MODULE module)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepWakeupEventControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepWakeupEventEnable(POWER_MODULE_ID index, DEEP_SLEEP_WAKE_UP_EVENT event)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepWakeupEventDisable(POWER_MODULE_ID index, DEEP_SLEEP_WAKE_UP_EVENT event)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepPortPinsStateControl(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepPortPinsStateRetain(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepPortPinsStateRelease(POWER_MODULE_ID index)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepEventStatus(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API DEEP_SLEEP_EVENT _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepEventStatusGet(POWER_MODULE_ID index)
{
     return (DEEP_SLEEP_EVENT)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepEventStatusClear(POWER_MODULE_ID index, DEEP_SLEEP_EVENT event)
{
     
}

PLIB_INLINE_API bool PLIB_POWER_ExistsDeepSleepGPROperation(POWER_MODULE_ID index)
{
     return (bool)0;
}

PLIB_INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepGPRWrite(POWER_MODULE_ID index, DEEP_SLEEP_GPR gpr, uint32_t data)
{
     
}

PLIB_INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepGPRRead(POWER_MODULE_ID index, DEEP_SLEEP_GPR gpr)
{
     return (uint32_t)0;
}

#endif
