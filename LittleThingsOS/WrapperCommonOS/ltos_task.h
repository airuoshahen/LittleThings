/*
 * @Author: Hansson Li
 * @Date: 2021-12-22 16:08:39
 * @LastEditTime: 2021-12-24 13:38:08
 * @LastEditors: Hansson Li
 * @Description: LittleThings OS task header file
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __LTOS_TASK_H__
#define __LTOS_TASK_H__

#include "ltos_type.h"

typedef enum
{
    LTOS_TASK_OK = 0,
    LTOS_TASK_ERR,
    LTOS_TASK_UNSUPPORT_OS,
}ltos_task_ret_e;

ltos_task_ret_e ltos_task_create(ltos_task_handle_t *lt_task_handle_ptr, const ltos_s8 * const lt_task_name,
    ltos_task_function_t lt_task_function, void * const lt_task_input_parameter, ltos_u16 lt_task_stack_size,
    ltos_u16 lt_task_priority);
void ltos_task_delay(ltos_tick_t delay_ticks);
void ltos_task_delete(ltos_task_handle_t lt_task_handle);
void ltos_task_disable_interrupts(void);
void ltos_task_enable_interrupts(void);
void ltos_task_enter_critical(void);
void ltos_task_exit_critical(void);
void ltos_task_enter_critical_from_isr(void);
void ltos_task_exit_critical_from_isr(void);
ltos_task_ret_e ltos_task_notify(ltos_task_handle_t lt_task_handle);
ltos_task_ret_e ltos_task_notify_increment(ltos_task_handle_t lt_task_handle);
ltos_task_ret_e ltos_task_notify_setbits(ltos_task_handle_t lt_task_handle, ltos_u32 bit_value);
ltos_task_ret_e ltos_task_notify_setvalue(ltos_task_handle_t lt_task_handle, ltos_u32 set_value);
ltos_task_ret_e ltos_task_notify_from_isr(ltos_task_handle_t lt_task_handle);
ltos_task_ret_e ltos_task_notify_increment_from_isr(ltos_task_handle_t lt_task_handle);
ltos_task_ret_e ltos_task_notify_setbits_from_isr(ltos_task_handle_t lt_task_handle, ltos_u32 bit_value);
ltos_task_ret_e ltos_task_notify_setvalue_from_isr(ltos_task_handle_t lt_task_handle, ltos_u32 set_value);
ltos_task_ret_e ltos_task_notify_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 *lt_previous_notify_value_ptr);
ltos_task_ret_e ltos_task_notify_increment_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 *lt_previous_notify_value_ptr);
ltos_task_ret_e ltos_task_notify_setbits_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 bit_value, ltos_u32 *lt_previous_notify_value_ptr);
ltos_task_ret_e ltos_task_notify_setvalue_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 set_value, ltos_u32 *lt_previous_notify_value_ptr);
ltos_task_ret_e ltos_task_notify_give(ltos_task_handle_t lt_task_handle);
ltos_task_ret_e ltos_task_notify_give_from_isr(ltos_task_handle_t lt_task_handle);
ltos_u32 ltos_task_notify_take_clear(ltos_tick_t lt_wait_tick);
ltos_u32 ltos_task_notify_take_decrement(ltos_tick_t lt_wait_tick);
void ltos_task_resume(ltos_task_handle_t lt_resume_task);
ltos_task_ret_e ltos_task_resume_all(void);
ltos_task_ret_e ltos_task_resume_from_isr(ltos_task_handle_t lt_resume_task);
void ltos_task_start_scheduler(void);
void ltos_task_suspend(ltos_task_handle_t lt_suspend_task);
void ltos_task_suspend_all(void);


#endif
