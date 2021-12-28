/*
 * @Author: Hansson Li
 * @Date: 2021-12-28 14:46:45
 * @LastEditTime: 2021-12-28 14:59:04
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#include "ltos_mem_manage.h"
#include "portable.h"


/**
 * @description: 
 * @param {ltos_u32} size
 * @return {*}
 */
void * ltos_malloc(ltos_u32 size)
{
    #ifdef USE_FREERTOS
    return pvPortMalloc(size);
    #else
    return NULL;
    #endif
}

/**
 * @description: 
 * @param {void} *free_ptr
 * @return {*}
 */
void ltos_free(void *free_ptr)
{
    #ifdef USE_FREERTOS
    vPortFree(free_ptr);
    #else
    return;
    #endif
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
ltos_u32 ltos_get_free_heap_size(void)
{
    #ifdef USE_FREERTOS
    return xPortGetFreeHeapSize();
    #else
    return NULL;
    #endif
}
