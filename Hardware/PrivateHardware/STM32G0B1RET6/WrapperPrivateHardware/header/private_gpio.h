/*
 * @Author: Hansson Li
 * @Date: 2022-01-06 11:01:01
 * @LastEditTime: 2022-01-06 13:37:18
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __PRIVATE_GPIO_H__
#define __PRIVATE_GPIO_H__

#include <stdint.h>

// this enum should be changed by the user, because the user get know which gpio is supported by HW
typedef enum{
    PRIVATE_GPIO_0,
    PRIVATE_GPIO_1,
    PRIVATE_GPIO_2,
    PRIVATE_GPIO_NUM
}private_gpio_pin_e;

typedef enum{
    PRIVATE_GPIO_LOW,
    PRIVATE_GPIO_HIGH,
    PRIVATE_GPIO_OUTPUT_NUM
}private_gpio_state_e;

typedef enum{
    PRIVATE_GPIO_MODE_OUTPUT,
    PRIVATE_GPIO_MODE_INPUT,
    PRIVATE_GPIO_MODE_NUM
}private_gpio_mode_e;

typedef enum{
    PRIVATE_GPIO_RET_OK,
    PRIVATE_GPIO_RET_ERR
}private_gpio_ret_e;

/**
 * @description: used to get the num of supproted gpio
 * @param {*}
 * @return {uint32_t} the num of support gpio
 */
uint32_t private_gpio_get_support_num(void);

/**
 * @description: gpio initialization function, now only supporting initialize the mode of gpio
 * @param {private_gpio_pin_e} configure_pin
 * @param {private_gpio_mode_e} configure_mode
 * @return {*}
 */
void private_gpio_init(private_gpio_pin_e configure_pin, private_gpio_mode_e configure_mode);


/**
 * @description: used to set up gpio to output high or low voltage
 * @param {private_gpio_pin_e} write_pin
 * @param {private_gpio_state_e} output_state
 * @return {private_gpio_ret_e} if gpio is configured as input, return err
 */
private_gpio_ret_e private_gpio_write(private_gpio_pin_e write_pin, private_gpio_state_e output_state);

/**
 * @description: 
 * @param {private_gpio_pin_e} read_pin
 * @param {private_gpio_state_e} *p_read_state -- used to save the state read from read pin
 * @return {private_gpio_ret_e} if gpio is configured with output mode, return err
 */
private_gpio_ret_e private_gpio_read(private_gpio_pin_e read_pin, const private_gpio_state_e *p_read_state);


#endif
