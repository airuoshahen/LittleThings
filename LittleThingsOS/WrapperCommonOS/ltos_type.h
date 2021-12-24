/*
 * @Author: Hansson Li
 * @Date: 2021-12-23 09:00:27
 * @LastEditTime: 2021-12-24 16:27:31
 * @LastEditors: Hansson Li
 * @Description: used to define common data tye
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __LTOS_TYPE__
#define __LTOS_TYPE__

#include "ltos_config.h"
#ifdef USE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#endif

#ifdef USE_FREERTOS
typedef TaskFunction_t          ltos_task_function_t;
typedef TaskHandle_t            ltos_task_handle_t;
typedef TickType_t              ltos_tick_t;
typedef QueueHandle_t           ltos_queue_handle_t;
typedef SemaphoreHandle_t       ltos_sem_handle_t;
#else
typedef void                     ltos_task_handle_t
typedef void (*ltos_task_function_t)( void * );
#endif

typedef unsigned char           ltos_u8;
typedef char                    ltos_s8;
typedef unsigned short          ltos_u16;
typedef short                   ltos_s16;
typedef unsigned int            ltos_u32;
typedef int                     ltos_s32;
typedef unsigned long           ltos_u64;
typedef long                    ltos_s64;
typedef float                   ltos_float;

#endif
