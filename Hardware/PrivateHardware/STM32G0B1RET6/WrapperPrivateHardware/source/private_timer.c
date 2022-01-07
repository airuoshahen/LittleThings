/*
 * @Author: Hansson Li
 * @Date: 2022-01-07 14:32:49
 * @LastEditTime: 2022-01-07 16:25:44
 * @LastEditors: Hansson Li
 * @Description: 
 * MIT License
 * 
 * Copyright (c) 2021 一页诗词郎
 * 
 */

#include "stm32g0b1xx.h"
#include "stm32g0xx_hal_tim.h"
#include "private_timer.h"

#define TIMER_CLK       (64000000)

typedef struct{
    TIM_HandleTypeDef           hal_timer;
    uint32_t                    prescaler_us;
    uint32_t                    period_count;
    private_timer_cb_func_ptr   timer_cb_func;
}private_timer_dev_t;

// default period is 1ms
static private_timer_dev_t s_timer_dev_array[PRIVATE_TIMER_DEV_NUM] = {
    {
        .hal_timer = {
            .Instance = TIM7,
        },
        .period_count = 1000,
        .prescaler_us = 1,
        .timer_cb_func = NULL,
    },
};

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
uint32_t private_timer_get_dev_num(void)
{
    return PRIVATE_TIMER_DEV_NUM;
}

/**
 * @description: 
 * @param {private_timer_dev_e} timer_dev
 * @param {uint32_t} period_count
 * @param {uint32_t} prescaler_us
 * @return {*}
 */
private_timer_ret_e private_timer_init(private_timer_dev_e timer_dev, uint32_t period_count, uint32_t prescaler_us)
{
    if (timer_dev >= PRIVATE_TIMER_DEV_NUM)
    {
        return PRIVATE_TIMER_RET_WRONG_DEV;
    }

    s_timer_dev_array[timer_dev].hal_timer.Init.Prescaler = TIMER_CLK / (1000 * 1000) / prescaler_us - 1;
    s_timer_dev_array[timer_dev].hal_timer.Init.Period = period_count;
    s_timer_dev_array[timer_dev].hal_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
    s_timer_dev_array[timer_dev].hal_timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&(s_timer_dev_array[timer_dev].hal_timer)) != HAL_OK)
    {
        return PRIVATE_TIMER_RET_ERR;
    }

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&(s_timer_dev_array[timer_dev].hal_timer), &sMasterConfig) != HAL_OK)
    {
        return PRIVATE_TIMER_RET_ERR;
    }

    s_timer_dev_array[timer_dev].period_count = period_count;
    s_timer_dev_array[timer_dev].prescaler_us = prescaler_us;
    s_timer_dev_array[timer_dev].timer_cb_func = NULL;
    
    return PRIVATE_TIMER_RET_OK;
}

/**
 * @description: 
 * @param {private_timer_dev_e} timer_dev
 * @param {private_timer_cb_func_ptr} timer_cb_func
 * @return {*}
 */
private_timer_ret_e private_timer_add_cb_func(private_timer_dev_e timer_dev, private_timer_cb_func_ptr timer_cb_func)
{
    if (timer_dev >= PRIVATE_TIMER_DEV_NUM)
    {
        return PRIVATE_TIMER_RET_WRONG_DEV;
    }

    s_timer_dev_array[timer_dev].timer_cb_func = timer_cb_func;

    return PRIVATE_TIMER_RET_OK;
}

/**
 * @description: 
 * @param {private_timer_dev_e} timer_dev
 * @return {*}
 */
private_timer_ret_e private_timer_enable(private_timer_dev_e timer_dev)
{
    if (timer_dev < PRIVATE_TIMER_DEV_NUM)
    {
        HAL_TIM_Base_Start_IT(&(s_timer_dev_array[timer_dev].hal_timer));
        return PRIVATE_TIMER_RET_OK;
    }
    else
    {
        return PRIVATE_TIMER_RET_WRONG_DEV;
    }
}

/**
 * @description: 
 * @param {private_timer_dev_e} timer_dev
 * @return {*}
 */
private_timer_ret_e private_timer_disable(private_timer_dev_e timer_dev)
{
    if (timer_dev < PRIVATE_TIMER_DEV_NUM)
    {
        HAL_TIM_Base_Stop_IT(&(s_timer_dev_array[timer_dev].hal_timer));
        return PRIVATE_TIMER_RET_OK;
    }
    else
    {
        return PRIVATE_TIMER_RET_WRONG_DEV;
    }
}

