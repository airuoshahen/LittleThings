/*
 * @Author: Hansson Li
 * @Date: 2021-12-24 16:18:57
 * @LastEditTime: 2021-12-24 16:20:26
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __LTOS_SEMAPHORE_H__
#define __LTOS_SEMAPHORE_H__

#include "ltos_type.h"

typedef enum
{
    LTOS_SEM_OK,
    LTOS_SEM_ERR,
    LTOS_SEM_UNSUPPORT_OS
}ltos_sem_e;

#endif
