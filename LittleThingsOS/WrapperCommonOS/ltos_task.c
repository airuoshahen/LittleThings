/*
 * @Author: Hansson Li
 * @Date: 2021-12-22 14:54:15
 * @LastEditTime: 2021-12-28 14:54:04
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

/*
 *                                                     __----~~~~~~~~~~~------___
 *                                    .  .   ~~//====......          __--~ ~~
 *                    -.            \_|//     |||\\  ~~~~~~::::... /~
 *                 ___-==_       _-~o~  \/    |||  \\            _/~~-
 *         __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~
 *     _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /
 *   .~       .~       |   \\ -_    /  /-   /   ||      \   /
 *  /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /
 *  |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\
 *           '         ~-|      /|    |-~\~~       __--~~
 *                       |-~~-_/ |    |   ~\_   _-~            /\
 *                            /  \     \__   \/~                \__
 *                        _--~ _/ | .-~~____--~-/                  ~~==.
 *                       ((->/~   '.|||' -_|    ~~-/ ,              . _||
 *                                  -_     ~\      ~~---l__i__i__i--~~_/
 *                                  _-~-__   ~)  \--______________--~~
 *                                //.-~~~-~_--~- |-------~~~~~~~~
 *                                       //.-~~~--\
 *                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *                               神兽保佑            永无BUG
 */

#include "ltos_task.h"
#include "portable.h"

#define UNSUPPORT_OS_RET_NULL   return
#define UNSUPPORT_OS_RET_ERR    do{return LTOS_TASK_UNSUPPORT_OS;}while(0)

/**
 * @description: task create function
 * @param {lt_task_handle_ptr -- pointer of task handle}
 * @return LTOS_TASK_OK -- create successfully
 *         LTOS_TASK_ERR -- create failed
 */
ltos_task_ret_e ltos_task_create(ltos_task_handle_t *lt_task_handle_ptr, const ltos_s8 * const lt_task_name,
    ltos_task_function_t lt_task_function, void * const lt_task_input_parameter, ltos_u16 lt_task_stack_size,
    ltos_u16 lt_task_priority)
{
    #ifdef USE_FREERTOS
    if (xTaskCreate(lt_task_function, lt_task_name, lt_task_stack_size, lt_task_input_parameter, lt_task_priority,
        lt_task_handle_ptr) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: task delay function
 * @param {ltos_tick_t} delay_ticks -- ticks need to delay(1ms)
 * @return {*}
 */
void ltos_task_delay(ltos_tick_t delay_ticks)
{
    #ifdef USE_FREERTOS
    vTaskDelay(delay_ticks);
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: delete the unused task
 * @param {ltos_task_handle_t} lt_task_handle -- handle want to delete
 * @return {*}
 */
void ltos_task_delete(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    vTaskDelete(lt_task_handle);
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: disable interrupts (it is effected by the configMAX_SYSCALL_INTERRUPT_PRIORITY paramter in configuration file)
 * @param {*}
 * @return {*}
 */
void ltos_task_disable_interrupts(void)
{
    #ifdef USE_FREERTOS
    taskDISABLE_INTERRUPTS();
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: enable interrupts
 * @param {*}
 * @return {*}
 */
void ltos_task_enable_interrupts(void)
{
    #ifdef USE_FREERTOS
    taskENABLE_INTERRUPTS();
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: it must be used in pair with ltos_task_enter_critical, after it's called, critical section will be entered
 *               with simply disabling interrupts, it can't be called from an interrupt service routine
 * @param {*}
 * @return {*}
 */
void ltos_task_enter_critical(void)
{
    #ifdef USE_FREERTOS
    taskENTER_CRITICAL();
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: exit critical section, same note with ltos_task_enter_critical function
 * @param {*}
 * @return {*}
 */
void ltos_task_exit_critical(void)
{
    #ifdef USE_FREERTOS
    taskEXIT_CRITICAL();
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: can be used in an interrupt service routine
 * @param {*}
 * @return {*}
 */
void ltos_task_enter_critical_from_isr(void)
{
    #ifdef USE_FREERTOS
    taskENTER_CRITICAL_FROM_ISR();
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void ltos_task_exit_critical_from_isr(void)
{
    #ifdef USE_FREERTOS
    taskEXIT_CRITICAL_FROM_ISR();
    #else
    UNSUPPORT_OS_RET_NULL;
    #endif
}

/**
 * @description: used to communication between tasks
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    if (xTaskNotify(lt_task_handle, 0, eNoAction) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value is incremented by one
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_increment(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    if (xTaskNotify(lt_task_handle, 0, eIncrement) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value and bit_value is ORed
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} bit_value -- 1 << 8
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_setbits(ltos_task_handle_t lt_task_handle, ltos_u32 bit_value)
{
    #ifdef USE_FREERTOS
    if (xTaskNotify(lt_task_handle, bit_value, eSetBits) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value will be set set_value, if task has unhandled notification, 
 *               this function will return ERROR
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} set_value
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_setvalue(ltos_task_handle_t lt_task_handle, ltos_u32 set_value)
{
    #ifdef USE_FREERTOS
    if (xTaskNotify(lt_task_handle, set_value, eSetValueWithoutOverwrite) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: used to communication between tasks
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_from_isr(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;
    
    if (xTaskNotifyFromISR(lt_task_handle, 0, eNoAction, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value is incremented by one
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_increment_from_isr(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;

    if (xTaskNotifyFromISR(lt_task_handle, 0, eIncrement, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value and bit_value is ORed
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} bit_value -- 1 << 8
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_setbits_from_isr(ltos_task_handle_t lt_task_handle, ltos_u32 bit_value)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;

    if (xTaskNotifyFromISR(lt_task_handle, bit_value, eSetBits, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value will be set set_value, if task has unhandled notification, 
 *               this function will return ERROR
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} set_value
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_setvalue_from_isr(ltos_task_handle_t lt_task_handle, ltos_u32 set_value)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;

    if (xTaskNotifyFromISR(lt_task_handle, set_value, eSetValueWithoutOverwrite, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} *lt_previous_notify_value_ptr -- used to get the previous notify value of this task
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 *lt_previous_notify_value_ptr)
{
    #ifdef USE_FREERTOS
    if (xTaskNotifyAndQuery(lt_task_handle, 0, eNoAction, lt_previous_notify_value_ptr) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value is incremented by one
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_increment_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 *lt_previous_notify_value_ptr)
{
    #ifdef USE_FREERTOS
    if (xTaskNotifyAndQuery(lt_task_handle, 0, eIncrement, lt_previous_notify_value_ptr) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value and bit_value is ORed
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} bit_value -- 1 << 8
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_setbits_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 bit_value, ltos_u32 *lt_previous_notify_value_ptr)
{
    #ifdef USE_FREERTOS
    if (xTaskNotifyAndQuery(lt_task_handle, bit_value, eSetBits, lt_previous_notify_value_ptr) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: the task's notification value will be set set_value, if task has unhandled notification, 
 *               this function will return ERROR
 * @param {ltos_task_handle_t} lt_task_handle
 * @param {ltos_u32} set_value
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_setvalue_with_query(ltos_task_handle_t lt_task_handle, ltos_u32 set_value, ltos_u32 *lt_previous_notify_value_ptr)
{
    #ifdef USE_FREERTOS
    if (xTaskNotifyAndQuery(lt_task_handle, set_value, eSetValueWithoutOverwrite, lt_previous_notify_value_ptr) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_give(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    if (xTaskNotifyGive(lt_task_handle) == pdPASS)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: used in interrupt service routine
 * @param {ltos_task_handle_t} lt_task_handle
 * @return {*}
 */
ltos_task_ret_e ltos_task_notify_give_from_isr(ltos_task_handle_t lt_task_handle)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken = pdFALSE;
    
    if (vTaskGenericNotifyGiveFromISR(lt_task_handle, 0, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: after it is called, it will clear the notification value of task
 * @param {ltos_tick_t} lt_wait_tick
 * @return {ltos_u32} return the value of the task's notification value before it's cleared
 */
ltos_u32 ltos_task_notify_take_clear(ltos_tick_t lt_wait_tick)
{
    #ifdef USE_FREERTOS
    return ulTaskGenericNotifyTake(0, pdTRUE, lt_wait_tick);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: after it is called, it will be decremented the notification value of task
 * @param {ltos_tick_t} lt_wait_tick
 * @return {ltos_u32} return the value of the task's notification value before it's decremented
 */
ltos_u32 ltos_task_notify_take_decrement(ltos_tick_t lt_wait_tick)
{
    #ifdef USE_FREERTOS
    return ulTaskGenericNotifyTake(0, pdFALSE, lt_wait_tick);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_task_handle_t} lt_resume_task
 * @return {*}
 */
void ltos_task_resume(ltos_task_handle_t lt_resume_task)
{
    #ifdef USE_FREERTOS
    vTaskResume(lt_resume_task);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {*}
 * @return {*}
 */
ltos_task_ret_e ltos_task_resume_all(void)
{
    #ifdef USE_FREERTOS
    if (xTaskResumeAll() == pdTRUE)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_task_handle_t} lt_resume_task
 * @return {*}
 */
ltos_task_ret_e ltos_task_resume_from_isr(ltos_task_handle_t lt_resume_task)
{
    #ifdef USE_FREERTOS
    if (xTaskResumeFromISR(lt_resume_task) == pdTRUE)
    {
        return LTOS_TASK_OK;
    }
    else
    {
        return LTOS_TASK_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void ltos_task_start_scheduler(void)
{
    #ifdef USE_FREERTOS
    vTaskStartScheduler();
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_task_handle_t} lt_suspend_task
 * @return {*}
 */
void ltos_task_suspend(ltos_task_handle_t lt_suspend_task)
{
    #ifdef USE_FREERTOS
    vTaskSuspend();
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void ltos_task_suspend_all(void)
{
    #ifdef USE_FREERTOS
    vTaskSuspendAll();
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}
