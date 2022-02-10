/*
 * @Author: Hansson Li
 * @Date: 2022-01-07 10:04:39
 * @LastEditTime: 2022-02-10 15:34:04
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

#include "stm32g030xx.h"
#include "stm32g0xx_hal_rcc.h"
#include "stm32g0xx_hal_cortex.h"
#include "stm32g0xx_hal_gpio.h"
#include "private_exti.h"

#define EXTI_INT_SECTION0   2 // EXTI0_1_IRQn
#define EXTI_INT_SECTION1   4 // EXTI2_3_IRQn

typedef struct
{
    GPIO_TypeDef*               exti_port;
    uint32_t                    exti_pin;
    private_exti_callback_ptr   exti_cb_func;
}private_exti_dev_t;

// this variable should be defined by user
static private_exti_dev_t s_private_exti_dev_array[PRIVATE_EXTI_DEV_NUM] = {
    {
        GPIOC,
        GPIO_PIN_13,
        NULL
    },
};

static private_exti_ret_e private_exti_enable_port_clk(private_exti_dev_e exti);
static private_exti_ret_e private_exti_disenable_port_clk(private_exti_dev_e exti);
static void private_exti_exti_interrupt_init(private_exti_dev_e exti);
static private_exti_ret_e private_exti_find_dev(uint32_t exti_pin, uint32_t *p_exti_dev_index);

/**
 * @description: 
 * @param {*}
 * @return {uint32_t} return supported exti devices number
 */
uint32_t private_exti_get_dev_num(void)
{
    return PRIVATE_EXTI_DEV_NUM;
}

/**
 * @description: 
 * @param {private_exti_dev_e} init_exti_dev
 * @param {private_exti_mode_e} trigger_mode
 * @return {*}
 */
private_exti_ret_e private_exti_init(private_exti_dev_e init_exti_dev, private_exti_mode_e trigger_mode)
{
    if (init_exti_dev >= PRIVATE_EXTI_DEV_NUM)
    {
        return PRIVATE_EXTI_RET_WRONG_DEV;
    }

    if (trigger_mode >= PRIVATE_EXTI_TRIGGER_NUM)
    {
        return PRIVATE_EXTI_RET_WRONG_TRIGGER;
    }

    uint32_t ret_state = PRIVATE_EXTI_RET_OK;

    ret_state = private_exti_enable_port_clk(init_exti_dev);
    if (ret_state != PRIVATE_EXTI_RET_OK)
    {
        return ret_state;
    }

    GPIO_InitTypeDef gpio_init_struct = {0};

    gpio_init_struct.Pin = s_private_exti_dev_array[init_exti_dev].exti_pin;
    if (trigger_mode == PRIVATE_EXTI_HIGH_TRIGGER)
    {
        gpio_init_struct.Mode = GPIO_MODE_IT_RISING;
    }
    else if(trigger_mode == PRIVATE_EXTI_LOW_TRIGGER)
    {
        gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    }
    else
    {
        gpio_init_struct.Mode = GPIO_MODE_IT_RISING_FALLING;
    }
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(s_private_exti_dev_array[init_exti_dev].exti_port, &gpio_init_struct);

    private_exti_exti_interrupt_init(init_exti_dev);
    return ret_state;
}

/**
 * @description: 
 * @param {private_exti_dev_e} exti_dev
 * @param {private_exti_callback_ptr} callback_func
 * @return {*}
 */
private_exti_ret_e private_exti_add_callback(private_exti_dev_e exti_dev, private_exti_callback_ptr callback_func)
{
    if (exti_dev >= PRIVATE_EXTI_DEV_NUM)
    {
        return PRIVATE_EXTI_RET_WRONG_DEV;
    }

    if (callback_func == NULL)
    {
        return PRIVATE_EXTI_RET_WRONG_CB_FUNC;
    }

    s_private_exti_dev_array[exti_dev].exti_cb_func = callback_func;

    return PRIVATE_EXTI_RET_OK;
}

/**
 * @description: this function is used to implement the isr section of EXTI, the solution of implement maybe change when using other MCU
 * @param {uint16_t} GPIO_Pin
 * @return {*}
 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
    uint32_t exti_dev_index;
    if (private_exti_find_dev(GPIO_Pin, &exti_dev_index) == PRIVATE_EXTI_RET_OK)
    {
        if (s_private_exti_dev_array[exti_dev_index].exti_cb_func != NULL)
        {
            s_private_exti_dev_array[exti_dev_index].exti_cb_func(exti_dev_index, PRIVATE_EXTI_HIGH_TRIGGER);
        }
    }
}

/**
 * @description: this function is used to implement the isr section of EXTI, the solution of implement maybe change when using other MCU
 * @param {uint16_t} GPIO_Pin
 * @return {*}
 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    uint32_t exti_dev_index;
    if (private_exti_find_dev(GPIO_Pin, &exti_dev_index) == PRIVATE_EXTI_RET_OK)
    {
        if (s_private_exti_dev_array[exti_dev_index].exti_cb_func != NULL)
        {
            s_private_exti_dev_array[exti_dev_index].exti_cb_func(exti_dev_index, PRIVATE_EXTI_LOW_TRIGGER);
        }
    }
}

/**
 * @description: 
 * @param {private_exti_dev_t} exti
 * @return {*}
 */
static private_exti_ret_e private_exti_enable_port_clk(private_exti_dev_e exti)
{
    switch(s_private_exti_dev_array[exti].exti_port)
    {
        case GPIOA:
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        }
        case GPIOB:
        {
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        }
        case GPIOC:
        {
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        }
        case GPIOD:
        {
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        }
        case GPIOF:
        {
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        }
        default:
        {
            return PRIVATE_EXTI_RET_WRONG_PORT;
        }
    }
    
    return PRIVATE_EXTI_RET_OK;
}


/**
 * @description: 
 * @param {private_exti_dev_t} exti
 * @return {*}
 */
static private_exti_ret_e private_exti_disenable_port_clk(private_exti_dev_e exti)
{
    switch(s_private_exti_dev_array[exti].exti_port)
    {
        case GPIOA:
        {
            __HAL_RCC_GPIOA_CLK_DISABLE();
            break;
        }
        case GPIOB:
        {
            __HAL_RCC_GPIOB_CLK_DISABLE();
            break;
        }
        case GPIOC:
        {
            __HAL_RCC_GPIOC_CLK_DISABLE();
            break;
        }
        case GPIOD:
        {
            __HAL_RCC_GPIOD_CLK_DISABLE();
            break;
        }
        case GPIOF:
        {
            __HAL_RCC_GPIOF_CLK_DISABLE();
            break;
        }
        default:
        {
            return PRIVATE_EXTI_RET_WRONG_PORT;
        }
    }
    
    return PRIVATE_EXTI_RET_OK;
}

/**
 * @description: 
 * @param {private_exti_dev_e} exti
 * @return {*}
 */
static void private_exti_exti_interrupt_init(private_exti_dev_e exti)
{
    if (s_private_exti_dev_array[exti].exti_pin < EXTI_INT_SECTION0)
    {
        HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    }
    else if (s_private_exti_dev_array[exti].exti_pin < EXTI_INT_SECTION1)
    {
        HAL_NVIC_SetPriority(EXTI2_3_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
    }
    else
    {
        HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
    }
}


/**
 * @description: 
 * @param {uint32_t} exti_pin
 * @return {*}
 */
static private_exti_ret_e private_exti_find_dev(uint32_t exti_pin, uint32_t *p_exti_dev_index)
{
    for (uint32_t i = 0; i < PRIVATE_EXTI_DEV_NUM; i++)
    {
        if (s_private_exti_dev_array[i].exti_pin == exti_pin)
        {
            *p_exti_dev_index = i;
            return PRIVATE_EXTI_RET_OK;
        }
    }
    return PRIVATE_EXTI_RET_ERR;
}
