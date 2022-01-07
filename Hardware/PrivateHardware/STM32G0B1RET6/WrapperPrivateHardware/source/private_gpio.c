/*
 * @Author: Hansson Li
 * @Date: 2022-01-06 15:45:53
 * @LastEditTime: 2022-01-07 13:08:42
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
#include "stm32g0xx_hal_gpio.h"
#include "private_gpio.h"


typedef struct
{
    GPIO_TypeDef*  gpio_port;
    uint32_t       gpio_pin;
}private_gpio_dev_t;

// this variable should be defined by user
static private_gpio_dev_t s_private_gpio_dev_array[PRIVATE_GPIO_NUM] = {
    {
        GPIOA,
        GPIO_PIN_5
    },
};


static private_gpio_ret_e private_gpio_enable_port_clk(private_gpio_pin_e pin);
static private_gpio_ret_e private_gpio_disenable_port_clk(private_gpio_pin_e pin);


uint32_t private_gpio_get_support_num(void)
{
    return PRIVATE_GPIO_NUM;
}

private_gpio_ret_e private_gpio_init(private_gpio_pin_e configure_pin, private_gpio_mode_e configure_mode)
{
    private_gpio_ret_e ret_state;
    
    if (configure_pin < PRIVATE_GPIO_NUM)
    {
        // enable clock of PORT
        ret_state = private_gpio_enable_port_clk(configure_pin);
        if (ret_state != PRIVATE_GPIO_RET_OK)
        {
            return ret_state;
        }

        HAL_GPIO_WritePin(s_private_gpio_dev_array[configure_pin].gpio_port, s_private_gpio_dev_array[configure_pin].gpio_pin, GPIO_PIN_RESET);

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_InitStruct.Pin = s_private_gpio_dev_array[configure_pin].gpio_pin;
        if (configure_mode == PRIVATE_GPIO_MODE_INPUT)
        {
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        }
        else if (configure_mode == PRIVATE_GPIO_MODE_OUTPUT)
        {
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        }
        else
        {
            ret_state = private_gpio_disenable_port_clk(configure_pin);
            if (ret_state != PRIVATE_GPIO_RET_OK)
            {
                return ret_state;
            }
            return PRIVATE_GPIO_RET_WRONG_MODE;
        }

        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(s_private_gpio_dev_array[configure_pin].gpio_port, &GPIO_InitStruct);

        return PRIVATE_GPIO_RET_OK;
    }
    else
    {
        return PRIVATE_GPIO_RET_WRONG_PIN;
    }
}

private_gpio_ret_e private_gpio_write(private_gpio_pin_e write_pin, private_gpio_state_e output_state)
{
    if (write_pin >= PRIVATE_GPIO_NUM)
    {
        return PRIVATE_GPIO_RET_WRONG_PIN;
    }
    
    if (output_state >= PRIVATE_GPIO_STATE_NUM)
    {
        return PRIVATE_GPIO_RET_WRONG_STATE;
    }

    switch (output_state)
    {
        case PRIVATE_GPIO_LOW:
        {
            HAL_GPIO_WritePin(s_private_gpio_dev_array[write_pin].gpio_port, s_private_gpio_dev_array[write_pin].gpio_pin, GPIO_PIN_RESET);
            break;
        }
        case PRIVATE_GPIO_HIGH:
        {
            HAL_GPIO_WritePin(s_private_gpio_dev_array[write_pin].gpio_port, s_private_gpio_dev_array[write_pin].gpio_pin, GPIO_PIN_SET);
            break;
        }
        case PRIVATE_GPIO_REVERSE:
        {
            HAL_GPIO_TogglePin(s_private_gpio_dev_array[write_pin].gpio_port, s_private_gpio_dev_array[write_pin].gpio_pin);
            break;
        }
        default:
        {
            return PRIVATE_GPIO_RET_WRONG_STATE;
        }
    }

    return PRIVATE_GPIO_RET_OK;
}

private_gpio_ret_e private_gpio_read(private_gpio_pin_e read_pin, private_gpio_state_e *p_read_state)
{
    if (read_pin >= PRIVATE_GPIO_NUM)
    {
        return PRIVATE_GPIO_RET_WRONG_PIN;
    }

    *p_read_state = HAL_GPIO_ReadPin(s_private_gpio_dev_array[read_pin].gpio_port, s_private_gpio_dev_array[read_pin].gpio_pin);

    return PRIVATE_GPIO_RET_OK;
}


static private_gpio_ret_e private_gpio_enable_port_clk(private_gpio_pin_e pin)
{
    switch(s_private_gpio_dev_array[pin].gpio_port)
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
            return PRIVATE_GPIO_RET_WRONG_PORT;
        }
    }
    
    return PRIVATE_GPIO_RET_OK;
}

static private_gpio_ret_e private_gpio_disenable_port_clk(private_gpio_pin_e pin)
{
    switch(s_private_gpio_dev_array[pin].gpio_port)
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
            return PRIVATE_GPIO_RET_WRONG_PORT;
        }
    }
    
    return PRIVATE_GPIO_RET_OK;
}
