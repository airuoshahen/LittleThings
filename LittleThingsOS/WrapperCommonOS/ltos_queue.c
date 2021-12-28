/*
 * @Author: Hansson Li
 * @Date: 2021-12-24 13:35:46
 * @LastEditTime: 2021-12-28 14:53:11
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


#include "ltos_queue.h"
#include "portable.h"

#define UNSUPPORT_OS_RET_NULL   return
#define UNSUPPORT_OS_RET_ERR    do{return LTOS_QUEUE_UNSUPPORT_OS;}while(0)

/**
 * @description: create queue, the size of queue is item_count * item_size
 * @param {ltos_u32} lt_queue_item_count
 * @param {ltos_u32} lt_queue_item_size
 * @return {ltos_queue_handle_t} queue handle(NULL failed)
 */
ltos_queue_handle_t ltos_queue_create(ltos_u32 lt_queue_item_count, ltos_u32 lt_queue_item_size)
{
    #ifdef USE_FREERTOS
    return xQueueCreate(lt_queue_item_count, lt_queue_item_size);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_delete_queue
 * @return {*}
 */
void ltos_queue_delete(ltos_queue_handle_t lt_delete_queue)
{
    #ifdef USE_FREERTOS
    vQueueDelete(lt_delete_queue);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: check whether queue is empty or not in isr
 * @param {ltos_queue_handle_t} lt_queue
 * @return {*} ok -- empty err -- not empty
 */
ltos_queue_ret_e ltos_queue_is_empty_from_isr(const ltos_queue_handle_t lt_queue)
{
    #ifdef USE_FREERTOS
    if (xQueueIsQueueEmptyFromISR(lt_queue) == pdFALSE)
    {
        return LTOS_QUEUE_OK;
    }
    else
    {
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: check whether queue is full or not in isr
 * @param {ltos_queue_handle_t} lt_queue
 * @return {*} OK -- full ERR -- not full
 */
ltos_queue_ret_e ltos_queue_is_full_from_isr(const ltos_queue_handle_t lt_queue)
{
    #ifdef USE_FREERTOS
    if (xQueueIsQueueFullFromISR(lt_queue) != pdFALSE)
    {
        return LTOS_QUEUE_OK;
    }
    else
    {
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: query the count of item in queue 
 * @param {ltos_queue_handle_t} lt_queue
 * @return {*} the count of items in queue
 */
ltos_u32 ltos_queue_query_item_count(ltos_queue_handle_t lt_queue)
{
    #ifdef USE_FREERTOS
    return uxQueueMessagesWaiting(lt_queue);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: query the count of item in queue from isr
 * @param {ltos_queue_handle_t} lt_queue
 * @return {*} the count of items in queue
 */
ltos_u32 ltos_queue_query_item_count_from_isr(ltos_queue_handle_t lt_queue)
{
    #ifdef USE_FREERTOS
    return uxQueueMessagesWaitingFromISR(lt_queue);
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_queue
 * @param {void} *lt_rx_buffer
 * @param {ltos_u32} lt_wait_tick
 * @return {*} OK -- received ERR -- empty queue
 */
ltos_queue_ret_e ltos_queue_receive(ltos_queue_handle_t lt_queue, void *lt_rx_buffer, ltos_u32 lt_wait_tick)
{
    #ifdef USE_FREERTOS
    if (xQueueReceive(lt_queue, lt_rx_buffer, lt_wait_tick) == pdPASS)
    {
        return LTOS_QUEUE_OK;
    }
    else
    {
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_queue
 * @param {void} *lt_rx_buffer
 * @return {*}
 */
ltos_queue_ret_e ltos_queue_receive_from_isr(ltos_queue_handle_t lt_queue, void *lt_rx_buffer)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken;
    
    if (xQueueReceiveFromISR(lt_queue, lt_rx_buffer, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_QUEUE_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: reset queue to its original empty state
 * @param {ltos_queue_handle_t} lt_reset_queue
 * @return {*}
 */
ltos_queue_ret_e ltos_queue_reset(ltos_queue_handle_t lt_reset_queue)
{
    #ifdef USE_FREERTOS
    if (xQueueReset(lt_reset_queue) == pdPASS)
    {
        return LTOS_QUEUE_OK;
    }
    else
    {
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}

/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_queue
 * @param {void} *lt_tx_item_ptr
 * @param {ltos_tick_t} lt_wait_tick
 * @return {*}
 */
ltos_queue_ret_e ltos_queue_send_to_front(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr, ltos_tick_t lt_wait_tick)
{
    #ifdef USE_FREERTOS
    if (xQueueSendToFront(lt_queue, lt_tx_item_ptr, lt_wait_tick) == pdPASS)
    {
        return LTOS_QUEUE_OK;
    }
    else
    {
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_queue
 * @param {void} *lt_tx_item_ptr
 * @param {ltos_tick_t} lt_wait_tick
 * @return {*}
 */
ltos_queue_ret_e ltos_queue_send_to_back(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr, ltos_tick_t lt_wait_tick)
{
    #ifdef USE_FREERTOS
    
    if (xQueueSendToBack(lt_queue, lt_tx_item_ptr, lt_wait_tick) == pdPASS)
    {
        return LTOS_QUEUE_OK;
    }
    else
    {
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_queue
 * @param {void} *lt_tx_item_ptr
 * @return {*}
 */
ltos_queue_ret_e ltos_queue_send_to_front_from_isr(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken;
    
    if (xQueueSendToFrontFromISR(lt_queue, lt_tx_item_ptr, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_QUEUE_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}


/**
 * @description: 
 * @param {ltos_queue_handle_t} lt_queue
 * @param {void} *lt_tx_item_ptr
 * @return {*}
 */
ltos_queue_ret_e ltos_queue_send_to_back_from_isr(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr)
{
    #ifdef USE_FREERTOS
    BaseType_t lt_higher_priority_task_woken;
    
    if (xQueueSendToBackFromISR(lt_queue, lt_tx_item_ptr, &lt_higher_priority_task_woken) == pdPASS)
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_QUEUE_OK;
    }
    else
    {
        portYIELD_FROM_ISR(lt_higher_priority_task_woken);
        return LTOS_QUEUE_ERR;
    }
    #else
    UNSUPPORT_OS_RET_ERR;
    #endif
}
