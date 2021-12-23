/*
 * @Author: Hansson Li
 * @Date: 2021-12-22 16:08:39
 * @LastEditTime: 2021-12-22 16:32:16
 * @LastEditors: Hansson Li
 * @Description: LittleThings OS task header file
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __LTOS_TASK_H__
#define __LTOS_TASK_H__

typedef enum
{
    LTOS_TASK_OK = 0,
    LTOS_TASK_ERR
}ltos_task_ret_e;

typedef void (*ltos_task_function_t)( void * );

// TODO: complete the definition of task type

#endif
