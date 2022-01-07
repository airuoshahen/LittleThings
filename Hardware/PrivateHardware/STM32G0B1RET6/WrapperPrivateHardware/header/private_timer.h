/*
 * @Author: Hansson Li
 * @Date: 2022-01-07 14:07:15
 * @LastEditTime: 2022-01-07 16:18:27
 * @LastEditors: Hansson Li
 * @Description: timer is only used to trigger MCU periodically, Yes, just implement the basic function of timer
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __PRIVATE_TIMER_H__
#define __PRIVATE_TIMER_H__

#include <stdint.h>

typedef enum{
    PRIVATE_TIMER_DEV0,
    PRIVATE_TIMER_DEV_NUM,
}private_timer_dev_e;

typedef enum{
    PRIVATE_TIMER_RET_OK,
    PRIVATE_TIMER_RET_ERR,
    PRIVATE_TIMER_RET_WRONG_DEV,
}private_timer_ret_e;

typedef void (*private_timer_cb_func_ptr)(private_timer_dev_e timer_dev);

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
uint32_t private_timer_get_dev_num(void);

/**
 * @description: this function should be invoked firstly, period = period_count * prescaler_us
 * @param {private_timer_dev_e} timer_dev
 * @param {uint32_t} period_count
 * @param {uint32_t} prescaler_us
 * @return {*}
 */
private_timer_ret_e private_timer_init(private_timer_dev_e timer_dev, uint32_t period_count, uint32_t prescaler_us);

/**
 * @description: should be used secondly
 * @param {private_timer_dev_e} timer_dev
 * @param {private_timer_cb_func_ptr} timer_cb_func
 * @return {*}
 */
private_timer_ret_e private_timer_add_cb_func(private_timer_dev_e timer_dev, private_timer_cb_func_ptr timer_cb_func);

/**
 * @description: after init and adding cb function, this function can be used to enable timer
 * @param {private_timer_dev_e} timer_dev
 * @return {*}
 */
private_timer_ret_e private_timer_enable(private_timer_dev_e timer_dev);

/**
 * @description: after init and adding cb function, this function can be used to disable timer
 * @param {private_timer_dev_e} timer_dev
 * @return {*}
 */
private_timer_ret_e private_timer_disable(private_timer_dev_e timer_dev);

/**
 * @description: used to get current time, the start point is when timer is triggered
 * @param {private_timer_dev_e} timer_dev
 * @param {uint32_t} *p_time_us
 * @return {*}
 */
private_timer_ret_e private_timer_get_us(private_timer_dev_e timer_dev, uint32_t *p_time_us);

/**
 * @description: used to get current time, the start point is when timer is triggered
 * @param {private_timer_dev_e} timer_dev
 * @param {uint32_t} *p_time_ms
 * @return {*}
 */
private_timer_ret_e private_timer_get_ms(private_timer_dev_e timer_dev, uint32_t *p_time_ms);

/**
 * @description: before using this function to change period of timer, timer should be disabled
 * @param {private_timer_dev_e} timer_dev
 * @param {uint32_t} period_ms
 * @param {uint32_t} period_us
 * @return {*}
 */
private_timer_ret_e private_timer_change_period(private_timer_dev_e timer_dev, uint32_t period_ms, uint32_t period_us);

#endif
