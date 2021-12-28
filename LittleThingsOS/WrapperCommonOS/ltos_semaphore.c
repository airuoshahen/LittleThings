/*
 * @Author: Hansson Li
 * @Date: 2021-12-24 16:18:06
 * @LastEditTime: 2021-12-28 14:54:22
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#include "ltos_semaphore.h"
#include "portable.h"

#define UNSUPPORT_OS_RET_NULL   return
#define UNSUPPORT_OS_RET_ERR    do{return LTOS_QUEUE_UNSUPPORT_OS;}while(0)

/**
 * @description: binary sem can be used for implementing synchronization (between tasks or between an interrupt and a task)
 * @param {*}
 * @return {*} NULL -- failed
 */
ltos_sem_handle_t ltos_sem_create_binary(void)
{
    #ifdef USE_FREERTOS
    return xSemaphoreCreateBinary();
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: counting sem is used for counting events and resource management
 * @param {*}
 * @return {*} NULL -- failed
 */
ltos_sem_handle_t ltos_sem_create_counting(void)
{
    #ifdef USE_FREERTOS
    return xSemaphoreCreateCounting();
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: mutex is better used for implementing simple mutual exclusion
 * @param {*}
 * @return {*} NULL -- failed
 */
ltos_sem_handle_t ltos_sem_create_mutex(void)
{
    #ifdef USE_FREERTOS
    return xSemaphoreCreateMutex();
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: used to delete binary, counting, mutex
 * @param {ltos_sem_handle_t} delete_sem
 * @return {*}
 */
void ltos_sem_delete(ltos_sem_handle_t delete_sem)
{
    #ifdef USE_FREERTOS
    vSemaphoreDelete(delete_sem);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: used to get count value of counting sem
 * @param {ltos_sem_handle_t} get_sem
 * @return {*} the count value
 */
ltos_u32 ltos_sem_get_count(ltos_sem_handle_t get_sem)
{
    #ifdef USE_FREERTOS
    return uxSemaphoreGetCount(get_sem);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_sem_handle_t} get_mutex
 * @return {*} return task handler which is holding mutex
 */
ltos_task_handle_t ltos_sem_get_mutex_holder(ltos_sem_handle_t get_mutex)
{
    #ifdef USE_FREERTOS
    return xSemaphoreGetMutexHolder(get_mutex);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: giv sem
 * @param {ltos_sem_handle_t} give_sem
 * @return {*}
 */
ltos_sem_e ltos_sem_give(ltos_sem_handle_t give_sem)
{
    #ifdef USE_FREERTOS
    if (xSemaphoreGive(give_sem) == pdPASS)
    {
        return LTOS_SEM_OK;
    }
    else
    {
        return LTOS_SEM_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_sem_handle_t} give_sem
 * @return {*}
 */
ltos_sem_e ltos_sem_give_from_isr(ltos_sem_handle_t give_sem)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;
    
    if (xSemaphoreGiveFromISR(give_sem, &lt_higher_priority_task_woken) == pdTRUE)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_SEM_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_SEM_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_sem_handle_t} take_sem
 * @param {ltos_tick_t} wait_ticks
 * @return {*}
 */
ltos_sem_e ltos_sem_take(ltos_sem_handle_t take_sem, ltos_tick_t wait_ticks)
{
    #ifdef USE_FREERTOS
    if (xSemaphoreTake(take_sem, wait_ticks) == pdTRUE)
    {
        return LTOS_SEM_OK;
    }
    else
    {
        return LTOS_SEM_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_sem_handle_t} take_sem
 * @return {*}
 */
ltos_sem_e ltos_sem_take_from_isr(ltos_sem_handle_t take_sem)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;
    
    if (xSemaphoreTakeFromISR(take_sem, &lt_higher_priority_task_woken) == pdTRUE)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_SEM_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_SEM_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}
