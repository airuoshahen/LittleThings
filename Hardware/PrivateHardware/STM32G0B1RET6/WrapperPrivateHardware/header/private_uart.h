/*
 * @Author: Hansson Li
 * @Date: 2022-01-06 13:59:20
 * @LastEditTime: 2022-01-06 14:48:31
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#ifndef __PRIVATE_UART_H__
#define __PRIVATE_UART_H__

#include <stdint.h>

// this enum should be changed by referring to HW
typedef enum{
    PRIVATE_UART_DEV_0,
    PRIVATE_UART_DEV_1,
    PRIVATE_UART_DEV_NUM
}private_uart_dev_e;

typedef enum{
    PRIVATE_UART_9600,
    PRIVATE_UART_38400,
    PRIVATE_UART_115200
}private_uart_baudrate_e;

typedef enum{
    PRIVATE_UART_MODE_IT,  // interrupt mode
    PRIVATE_UART_MODE_DMA, // interrupt and dma mode
}private_uart_mode_e;

typedef enum{
    PRIVATE_UART_STOP_BIT_1,
    PRIVATE_UART_STOP_BIT_2,
}private_uart_stop_bit_e;

typedef enum{
    PRIVATE_UART_NONE_PARITY,
    PRIVATE_UART_ODD_PARITY,
    PRIVATE_UART_EVEN_PARITY,
}private_uart_parity_e;

typedef enum{
    PRIVATE_UART_RET_OK,
    PRIVATE_UART_RET_ERR
}private_uart_ret_e;

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
uint32_t private_uart_get_dev_num(void);

/**
 * @description: easy initialization with none parity, stop_bit_1 and IT mode
 * @param {private_uart_dev_e} uart_dev
 * @param {private_uart_baudrate_e} uart_baudrate
 * @return {*}
 */
private_uart_ret_e private_uart_easy_init(private_uart_dev_e uart_dev, private_uart_baudrate_e uart_baudrate);



#endif
