/*
 * @Author: Hansson Li
 * @Date: 2021-12-24 16:18:57
 * @LastEditTime: 2021-12-28 14:25:32
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


ltos_sem_handle_t ltos_sem_create_binary(void);
ltos_sem_handle_t ltos_sem_create_counting(void);
ltos_sem_handle_t ltos_sem_create_mutex(void);
void ltos_sem_delete(ltos_sem_handle_t delete_sem);
ltos_u32 ltos_sem_get_count(ltos_sem_handle_t get_sem);
ltos_task_handle_t ltos_sem_get_mutex_holder(ltos_sem_handle_t get_mutex);
ltos_sem_e ltos_sem_give(ltos_sem_handle_t give_sem);
ltos_sem_e ltos_sem_give_from_isr(ltos_sem_handle_t give_sem);
ltos_sem_e ltos_sem_take(ltos_sem_handle_t take_sem, ltos_tick_t wait_ticks);
ltos_sem_e ltos_sem_take_from_isr(ltos_sem_handle_t take_sem);


#endif
