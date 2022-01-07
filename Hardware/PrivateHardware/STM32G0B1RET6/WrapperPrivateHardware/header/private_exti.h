/*
 * @Author: Hansson Li
 * @Date: 2022-01-06 13:24:34
 * @LastEditTime: 2022-01-07 13:31:00
 * @LastEditors: Hansson Li
 * @Description: I think external interrupt of gpio is different from input and output, so this function is implemented in independent file
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __PRIVATE_EXTI_H__
#define __PRIVATE_EXTI_H__

#include <stdint.h>

// this enum should be changed by user according to the HW
typedef enum{
    PRIVATE_EXTI_DEV_0,
    PRIVATE_EXTI_DEV_1,
    PRIVATE_EXTI_DEV_NUM
}private_exti_dev_e;

typedef enum{
    PRIVATE_EXTI_LOW_TRIGGER,
    PRIVATE_EXTI_HIGH_TRIGGER,
    PRIVATE_EXTI_PULSE_TRIGGER,
    PRIVATE_EXTI_TRIGGER_NUM,
}private_exti_mode_e;

typedef enum{
    PRIVATE_EXTI_RET_OK,
    PRIVATE_EXTI_RET_ERR,
    PRIVATE_EXTI_RET_WRONG_DEV,
    PRIVATE_EXTI_RET_WRONG_TRIGGER,
    PRIVATE_EXTI_RET_WRONG_PORT,
    PRIVATE_EXTI_RET_WRONG_CB_FUNC,
}private_exti_ret_e;

typedef void (*private_exti_callback_ptr)(private_exti_dev_e, private_exti_mode_e);

/**
 * @description: 
 * @param {*}
 * @return {uint32_t} return the num of supported exti device
 */
uint32_t private_exti_get_dev_num(void);

/**
 * @description:
 * @param {private_exti_dev_e} init_exti_dev
 * @return {*}
 */
private_exti_ret_e private_exti_init(private_exti_dev_e init_exti_dev, private_exti_mode_e trigger_mode);

/**
 * @description: if this function is not invoked, isr will invoke the default handler function
 * @param {private_exti_dev_e} exti_dev
 * @param {private_exti_callback_ptr} callback_func
 * @return {*}
 */
private_exti_ret_e private_exti_add_callback(private_exti_dev_e exti_dev, private_exti_callback_ptr callback_func);

#endif
