/*
 * @Author: Hansson Li
 * @Date: 2021-12-28 14:47:02
 * @LastEditTime: 2021-12-28 14:59:22
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __LTOS_MEM_MANAGE_H__
#define __LTOS_MEM_MANAGE_H__

#include "ltos_type.h"

void * ltos_malloc(ltos_u32 size);
void ltos_free(void *free_ptr);
ltos_u32 ltos_get_free_heap_size(void);

#endif
