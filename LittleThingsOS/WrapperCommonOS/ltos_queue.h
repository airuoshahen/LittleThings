/*
 * @Author: Hansson Li
 * @Date: 2021-12-24 13:36:59
 * @LastEditTime: 2021-12-24 16:16:28
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __LTOS_QUEUE_H__
#define __LTOS_QUEUE_H__

#include "ltos_type.h"

typedef enum
{
    LTOS_QUEUE_OK = 0,
    LTOS_QUEUE_ERR,
    LTOS_QUEUE_UNSUPPORT_OS,
}ltos_queue_ret_e;

ltos_queue_handle_t ltos_queue_create(ltos_u32 lt_queue_item_count, ltos_u32 lt_queue_item_size);
void ltos_queue_delete(ltos_queue_handle_t lt_delete_queue);
ltos_queue_ret_e ltos_queue_is_empty_from_isr(const ltos_queue_handle_t lt_queue);
ltos_queue_ret_e ltos_queue_is_full_from_isr(const ltos_queue_handle_t lt_queue);
ltos_u32 ltos_queue_query_item_count(ltos_queue_handle_t lt_queue);
ltos_u32 ltos_queue_query_item_count_from_isr(ltos_queue_handle_t lt_queue);
ltos_queue_ret_e ltos_queue_receive(ltos_queue_handle_t lt_queue, void *lt_rx_buffer, ltos_u32 lt_wait_tick);
ltos_queue_ret_e ltos_queue_receive_from_isr(ltos_queue_handle_t lt_queue, void *lt_rx_buffer);
ltos_queue_ret_e ltos_queue_reset(ltos_queue_handle_t lt_reset_queue);
ltos_queue_ret_e ltos_queue_send_to_front(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr, ltos_tick_t lt_wait_tick);
ltos_queue_ret_e ltos_queue_send_to_back(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr, ltos_tick_t lt_wait_tick);
ltos_queue_ret_e ltos_queue_send_to_front_from_isr(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr);
ltos_queue_ret_e ltos_queue_send_to_back_from_isr(ltos_queue_handle_t lt_queue, const void *lt_tx_item_ptr);


#endif
