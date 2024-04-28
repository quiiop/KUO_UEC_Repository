/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
    See http://www.freertos.org/a00110.html for an explanation of the
    definitions contained in this file.
******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 * http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
#include <stdint.h>
#include <stdio.h>
#include "common.h"
#include "syslog.h"
#endif /* #if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__) */

#include "memory_map.h"

#ifdef MTK_OS_HEAP_EXTEND
#if defined(MTK_WIFI_ROUTER_ENABLE)
#define configTOTAL_HEAP_SIZE                   ((size_t)(359 * 1024))
#else /* #if defined(MTK_WIFI_ROUTER_ENABLE) */
#define configTOTAL_HEAP_SIZE                   ((size_t)(389 * 1024))
#endif /* #if defined(MTK_WIFI_ROUTER_ENABLE) */
#define configPlatform_HEAP_SIZE                ((size_t)(3400 * 1024))
/* Use TFM 512K PSRAM as AIA Heap*/
#define configAIA_HEAP_SIZE                     ((size_t)(512 * 1024))
#define aiaRegionID                             (2)
#else /* #ifdef MTK_OS_HEAP_EXTEND */
#define configTOTAL_HEAP_SIZE                   ((size_t)(437 * 1024))
#endif /* #ifdef MTK_OS_HEAP_EXTEND */

/* Cortex M33 port configuration. */

#define configENABLE_MPU                           0
#define configENABLE_FPU                           1
#define configENABLE_TRUSTZONE                     0


#ifndef configRUN_FREERTOS_SECURE_ONLY
#ifdef MTK_TFM_ENABLE
#define configRUN_FREERTOS_SECURE_ONLY                 0
#else /* #ifdef MTK_TFM_ENABLE */
#define configRUN_FREERTOS_SECURE_ONLY                 1
#endif /* #ifdef MTK_TFM_ENABLE */
#endif /* #ifndef configRUN_FREERTOS_SECURE_ONLY */

/* Constants related to the behaviour or the scheduler. */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION            0
#define configUSE_PREEMPTION                                         1
#define configMAX_PRIORITIES                                       ( 20 )
#define configIDLE_SHOULD_YIELD                                    1
#define configUSE_16_BIT_TICKS                                     0 /* Only for 8 and 16-bit hardware. */


/* Constants that describe the hardware and memory usage. */

#ifdef HAL_CLOCK_MODULE_ENABLED
extern uint32_t SystemCoreClock;
#define configCPU_CLOCK_HZ                                          SystemCoreClock
#else /* #ifdef HAL_CLOCK_MODULE_ENABLED */
#define configCPU_CLOCK_HZ                                      26000000 // default 26MHz
#endif /* #ifdef HAL_CLOCK_MODULE_ENABLED */



#define configTICK_RATE_HZ                            ( ( TickType_t ) 1000 )
#define configMINIMAL_STACK_SIZE                                  ( ( uint16_t ) 1792 )
#define configMINIMAL_SECURE_STACK_SIZE                       ( 1024 )
#define configMAX_TASK_NAME_LEN                                 ( 20 )

/* Constants that build features in or out. */
#define configUSE_MUTEXES                                           1

#define configUSE_TICKLESS_IDLE                                 0

#if 0
#define configPRINTF( X )                           do { } while ( 0 )
#else /* #if 0 */
void vLoggingPrintf(const char *pcFormat, ...);
#define configPRINTF( X )                           vLoggingPrintf X
#endif /* #if 0 */


#ifdef MTK_POSIX_SUPPORT_ENABLE
#define configUSE_POSIX_ERRNO                          1
#define configUSE_APPLICATION_TASK_TAG                 1
#else /* #ifdef MTK_POSIX_SUPPORT_ENABLE */
#define configUSE_APPLICATION_TASK_TAG                         0
#endif /* #ifdef MTK_POSIX_SUPPORT_ENABLE */


#define configUSE_NEWLIB_REENTRANT                               0
#define configUSE_CO_ROUTINES                                    0
#define configUSE_COUNTING_SEMAPHORES                                    1
#define configUSE_RECURSIVE_MUTEXES                              1
#define configUSE_QUEUE_SETS                                     1
#define configUSE_TASK_NOTIFICATIONS                                     1
#define configUSE_TRACE_FACILITY                                 1


#ifndef configSUPPORT_STATIC_ALLOCATION
#if defined(MTK_TFM_ENABLE) || defined(MTK_POSIX_SUPPORT_ENABLE)
#define configSUPPORT_STATIC_ALLOCATION         1
#endif /* #if defined(MTK_TFM_ENABLE) || defined(MTK_POSIX_SUPPORT_ENABLE) */
#endif /* #ifndef configSUPPORT_STATIC_ALLOCATION */

#if (MTK_OS_HEAP_EXTEND == HEAP_EXTEND_MULTI)
#ifndef configMAX_HEAP_REGION
#define configMAX_HEAP_REGION                          (eHeapRegion_Default_MAX+1)
#endif /* #ifndef configMAX_HEAP_REGION */

#ifndef configUSE_HEAP_REGION_DEFAULT
#define configUSE_HEAP_REGION_DEFAULT                  eHeapRegion_PLATFORM
#endif /* #ifndef configUSE_HEAP_REGION_DEFAULT */

#ifndef configTOTAL_HEAP_SIZE
#define configTOTAL_HEAP_SIZE                          ((size_t)(100 * 1024))
#endif /* #ifndef configTOTAL_HEAP_SIZE */

#ifndef configPlatform_HEAP_SIZE
#define configPlatform_HEAP_SIZE                       ((size_t)(500 * 1024))
#endif /* #ifndef configPlatform_HEAP_SIZE */

#else /* #if (MTK_OS_HEAP_EXTEND == HEAP_EXTEND_MULTI) */
#ifndef configTOTAL_HEAP_SIZE
#define configTOTAL_HEAP_SIZE                          ((size_t)(100 * 1024))
#endif /* #ifndef configTOTAL_HEAP_SIZE */
#endif /* #if (MTK_OS_HEAP_EXTEND == HEAP_EXTEND_MULTI) */



/* Constants that define which hook (callback) functions should be used. */

#define configUSE_IDLE_HOOK                                        1
#define configUSE_TICK_HOOK                                      0


#if defined(MTK_OS_CPU_UTILIZATION_ENABLE)
/* Run time stats gathering definitions. */
void vConfigureTimerForRunTimeStats(void);
uint32_t ulGetRunTimeCounterValue(void);
#define configGENERATE_RUN_TIME_STATS                   1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()        vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE()                ulGetRunTimeCounterValue()
#endif /* #if defined(MTK_OS_CPU_UTILIZATION_ENABLE) */

/* Software timer definitions. */
#define configUSE_TIMERS                                                1
#define configTIMER_TASK_PRIORITY                                 (configMAX_PRIORITIES - 1)

#define configTIMER_QUEUE_LENGTH                                    10

#define configTIMER_TASK_STACK_DEPTH                            ( configMINIMAL_STACK_SIZE * 2 )


/* Set the following definitions to 1 to include the API function, or zero
 * to exclude the API function.  NOTE:  Setting an INCLUDE_ parameter to 0 is
 * only necessary if the linker does not automatically remove functions that are
 * not referenced anyway. */

#define INCLUDE_vTaskPrioritySet                                    1
#define INCLUDE_uxTaskPriorityGet                                 1
#define INCLUDE_vTaskDelete                                           1
#define INCLUDE_vTaskSuspend                                          1
#define INCLUDE_xTaskDelayUntil                                     1



#define INCLUDE_vTaskDelay                                            1
#define INCLUDE_uxTaskGetStackHighWaterMark                 1
#define INCLUDE_xTaskGetIdleTaskHandle                          1
#define INCLUDE_eTaskGetState                                         1
#define INCLUDE_xTaskResumeFromISR                                1
#define INCLUDE_xTaskGetCurrentTaskHandle                       1
#define INCLUDE_xTaskGetSchedulerState                          1
#define INCLUDE_xSemaphoreGetMutexHolder                        1
#define INCLUDE_xTimerPendFunctionCall                          1


/* This demo makes use of one or more example stats formatting functions.  These
 * format the raw data provided by the uxTaskGetSystemState() function in to
 * human readable ASCII form.  See the notes in the implementation of vTaskList()
 * within FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS            1


/* Interrupt priority configuration follows...................... */

/* Use the system definition, if there is one. */
#ifndef configPRIO_BITS
#ifdef __NVIC_PRIO_BITS
#define configPRIO_BITS                                             __NVIC_PRIO_BITS
#else /* #ifdef __NVIC_PRIO_BITS */
#define configPRIO_BITS                                             5    /* 32 priority levels. */
#endif /* #ifdef __NVIC_PRIO_BITS */
#endif /* #ifndef configPRIO_BITS */

/* The highest interrupt priority that can be used by any interrupt service
 * routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT
 * CALL INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A
 * HIGHER PRIORITY THAN THIS! (higher priorities are lower numeric values). */
#ifndef configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY      5
#endif /* #ifndef configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY */


/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
 * See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY
#define configMAX_SYSCALL_INTERRUPT_PRIORITY                ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )
#endif /* #ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY */


#ifndef configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H
#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H    1
#define FREERTOS_TASKS_C_ADDITIONS_INIT              vApplicationTaskInit
#endif /* #ifndef configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H */

#ifndef configASSERT
extern void platform_assert(const char *, const char *, int);
#define configASSERT( x )                                      if( (x) == 0 ) { platform_assert(#x, __FILE__, __LINE__); }
#endif /* #ifndef configASSERT */

#ifndef portSUPPRESS_TICKS_AND_SLEEP
#if configUSE_TICKLESS_IDLE == 2
extern void tickless_handler(uint32_t xExpectedIdleTime);
#define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )      tickless_handler( xExpectedIdleTime )
#ifndef TICKLESS_CONFIG
#define TICKLESS_CONFIG xDefaultTicklessConfig
#endif /* #ifndef TICKLESS_CONFIG */
#endif /* #if configUSE_TICKLESS_IDLE == 2 */
#endif /* #ifndef portSUPPRESS_TICKS_AND_SLEEP */

#if defined(MTK_SWLA_ENABLE)
#undef traceTASK_SWITCHED_IN
extern void vTraceTaskSwitchIn(uint32_t pRio);
#define traceTASK_SWITCHED_IN() \
    {\
        vTraceTaskSwitchIn(pxCurrentTCB->uxPriority);\
    }
#endif /* #if defined(MTK_SWLA_ENABLE) */

#ifndef configNUM_THREAD_LOCAL_STORAGE_POINTERS
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    1
#endif /* #ifndef configNUM_THREAD_LOCAL_STORAGE_POINTERS */

#if defined(MTK_OS_TIMER_LIST_ENABLE)
extern void vTraceTimerCreate(void *pxNewTimer);
#define traceTIMER_CREATE( pxNewTimer ) vTraceTimerCreate( pxNewTimer )
#endif /* #if defined(MTK_OS_TIMER_LIST_ENABLE) */

#define INCLUDE_xTaskAbortDelay                         1

#define configPRINT_STRING printf

#define configLOGGING_MAX_MESSAGE_LENGTH        (120)

#define configLOGGING_INCLUDE_TIME_AND_TASK_NAME (1)


/* The address of an echo server that will be used by the two demo echo client
 * tasks:
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients.html
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/UDP_Echo_Clients.html
 */
#define configECHO_SERVER_ADDR0              192
#define configECHO_SERVER_ADDR1              168
#define configECHO_SERVER_ADDR2              0
#define configECHO_SERVER_ADDR3              105
#define configTCP_ECHO_CLIENT_PORT           45000

/* Default MAC address configuration.  The demo creates a virtual network
 * connection that uses this MAC address by accessing the raw Ethernet/WiFi data
 * to and from a real network connection on the host PC.  See the
 * configNETWORK_INTERFACE_TO_USE definition above for information on how to
 * configure the real network connection to use. */
#define configMAC_ADDR0                      0x00
#define configMAC_ADDR1                      0x11
#define configMAC_ADDR2                      0x22
#define configMAC_ADDR3                      0x33
#define configMAC_ADDR4                      0x44
#define configMAC_ADDR5                      0x21

/* Default IP address configuration.  Used in ipconfigUSE_DHCP is set to 0, or
 * ipconfigUSE_DHCP is set to 1 but a DNS server cannot be contacted. */
#define configIP_ADDR0                       192
#define configIP_ADDR1                       168
#define configIP_ADDR2                       0
#define configIP_ADDR3                       105

/* Default gateway IP address configuration.  Used in ipconfigUSE_DHCP is set to
 * 0, or ipconfigUSE_DHCP is set to 1 but a DNS server cannot be contacted. */
#define configGATEWAY_ADDR0                  192
#define configGATEWAY_ADDR1                  168
#define configGATEWAY_ADDR2                  0
#define configGATEWAY_ADDR3                  1

/* Default DNS server configuration.  OpenDNS addresses are 208.67.222.222 and
 * 208.67.220.220.  Used in ipconfigUSE_DHCP is set to 0, or ipconfigUSE_DHCP is
 * set to 1 but a DNS server cannot be contacted.*/
#define configDNS_SERVER_ADDR0               208
#define configDNS_SERVER_ADDR1               67
#define configDNS_SERVER_ADDR2               222
#define configDNS_SERVER_ADDR3               222

/* Default netmask configuration.  Used in ipconfigUSE_DHCP is set to 0, or
 * ipconfigUSE_DHCP is set to 1 but a DNS server cannot be contacted. */
#define configNET_MASK0                      255
#define configNET_MASK1                      255
#define configNET_MASK2                      255
#define configNET_MASK3                      0

#endif /* #ifndef FREERTOS_CONFIG_H */
