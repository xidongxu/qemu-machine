/*
 * STM32F4XX RCC (Reset and clock control)
 *
 * Copyright (c) 2023 Arnaud Minier <arnaud.minier@telecom-paris.fr>
 * Copyright (c) 2023 Inès Varhol <ines.varhol@telecom-paris.fr>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 * The reference used is the STMicroElectronics RM0351 Reference manual
 * for STM32F4xx advanced Arm ® -based 32-bit MCUs.
 *
 * Inspired by the BCM2835 CPRMAN clock manager by Luc Michel.
 */

#ifndef HW_STM32F4XX_RCC_H
#define HW_STM32F4XX_RCC_H

#include "hw/sysbus.h"
#include "qom/object.h"

#define TYPE_STM32F4XX_RCC "stm32f4xx-rcc"
OBJECT_DECLARE_SIMPLE_TYPE(STM32F4XXRCCState, STM32F4XX_RCC)

/* In the stm32f4xx clock tree, mux have at most 5 sources */
#define RCC_NUM_CLOCK_MUX_SRC 5

typedef enum PllCommonChannels {
    RCC_PLL_COMMON_CHANNEL_P = 0,
    RCC_PLL_COMMON_CHANNEL_Q = 1,
    RCC_PLL_COMMON_CHANNEL_R = 2,

    RCC_NUM_CHANNEL_PLL_OUT = 3
} PllCommonChannels;

/* NB: Prescaler are assimilated to mux with one source and one output */
typedef enum RccClockMux {
    /* Internal muxes that arent't exposed publicly to other peripherals */
    RCC_CLOCK_MUX_SYSCLK,
    RCC_CLOCK_MUX_PLL_INPUT,
    RCC_CLOCK_MUX_HCLK,
    RCC_CLOCK_MUX_PCLK1,
    RCC_CLOCK_MUX_PCLK2,
    RCC_CLOCK_MUX_HSE_RTC,
    RCC_CLOCK_MUX_RTC_COMMON,

    /* Muxes with a publicly available output */
    RCC_CLOCK_MUX_CORTEX_REFCLK,
    RCC_CLOCK_MUX_MCO1,
    RCC_CLOCK_MUX_MCO2,
    RCC_CLOCK_MUX_I2S,
    
    /*
     * Mux that have only one input and one output assigned to as peripheral.
     * They could be direct lines but it is simpler
     * to use the same logic for all outputs.
     */
    /* - AHB1 */
    RCC_CLOCK_MUX_OTGHSULPI,
    RCC_CLOCK_MUX_OTGHS,
    RCC_CLOCK_MUX_ETHMACPTP,
    RCC_CLOCK_MUX_ETHMACRX,
    RCC_CLOCK_MUX_ETHMACTX,
    RCC_CLOCK_MUX_ETHMAC,
    RCC_CLOCK_MUX_DMA2,
    RCC_CLOCK_MUX_DMA1,
    RCC_CLOCK_MUX_CCMDATARAM,
    RCC_CLOCK_MUX_BKPSRAM,
    RCC_CLOCK_MUX_CRC,
    RCC_CLOCK_MUX_GPIOI,
    RCC_CLOCK_MUX_GPIOH,
    RCC_CLOCK_MUX_GPIOG,
    RCC_CLOCK_MUX_GPIOF,
    RCC_CLOCK_MUX_GPIOE,
    RCC_CLOCK_MUX_GPIOD,
    RCC_CLOCK_MUX_GPIOC,
    RCC_CLOCK_MUX_GPIOB,
    RCC_CLOCK_MUX_GPIOA,

    /* - AHB2 */
    RCC_CLOCK_MUX_OTGFS,
    RCC_CLOCK_MUX_RNG,
    RCC_CLOCK_MUX_HASH,
    RCC_CLOCK_MUX_CRYP,
    RCC_CLOCK_MUX_DCMI,

    /* - AHB3 */
    RCC_CLOCK_MUX_FSMC,

    /* - APB1 */
    RCC_CLOCK_MUX_DAC,
    RCC_CLOCK_MUX_PWR,
    RCC_CLOCK_MUX_CAN2,
    RCC_CLOCK_MUX_CAN1,
    RCC_CLOCK_MUX_I2C3,
    RCC_CLOCK_MUX_I2C2,
    RCC_CLOCK_MUX_I2C1,
    RCC_CLOCK_MUX_UART5,
    RCC_CLOCK_MUX_UART4,
    RCC_CLOCK_MUX_USART3,
    RCC_CLOCK_MUX_USART2,
    RCC_CLOCK_MUX_SPI3,
    RCC_CLOCK_MUX_SPI2,
    RCC_CLOCK_MUX_WWDG,
    RCC_CLOCK_MUX_TIM14,
    RCC_CLOCK_MUX_TIM13,
    RCC_CLOCK_MUX_TIM12,
    RCC_CLOCK_MUX_TIM7,
    RCC_CLOCK_MUX_TIM6,
    RCC_CLOCK_MUX_TIM5,
    RCC_CLOCK_MUX_TIM4,
    RCC_CLOCK_MUX_TIM3,
    RCC_CLOCK_MUX_TIM2,

    /* - APB2 */
    RCC_CLOCK_MUX_TIM11,
    RCC_CLOCK_MUX_TIM10,
    RCC_CLOCK_MUX_TIM9,
    RCC_CLOCK_MUX_SYSCFG,
    RCC_CLOCK_MUX_SPI1,
    RCC_CLOCK_MUX_SDIO,
    RCC_CLOCK_MUX_ADC3,
    RCC_CLOCK_MUX_ADC2,
    RCC_CLOCK_MUX_ADC1,
    RCC_CLOCK_MUX_USART6,
    RCC_CLOCK_MUX_USART1,
    RCC_CLOCK_MUX_TIM8,
    RCC_CLOCK_MUX_TIM1,

    /* - BDCR */
    RCC_CLOCK_MUX_RTC,

    /* - OTHER */
    RCC_CLOCK_MUX_SSCG,
    RCC_CLOCK_MUX_CORTEX_FCLK,

    RCC_NUM_CLOCK_MUX
} RccClockMux;

typedef enum RccPll {
    RCC_PLL_PLL,
    RCC_PLL_PLLI2S,

    RCC_NUM_PLL
} RccPll;

typedef struct RccClockMuxState {
    DeviceState parent_obj;

    RccClockMux id;
    Clock *srcs[RCC_NUM_CLOCK_MUX_SRC];
    Clock *out;
    bool enabled;
    uint32_t src;
    uint32_t multiplier;
    uint32_t divider;

    /*
     * Used by clock srcs update callback to retrieve both the clock and the
     * source number.
     */
    struct RccClockMuxState *backref[RCC_NUM_CLOCK_MUX_SRC];
} RccClockMuxState;

typedef struct RccPllState {
    DeviceState parent_obj;

    RccPll id;
    Clock *in;
    uint32_t vco_multiplier;
    Clock *channels[RCC_NUM_CHANNEL_PLL_OUT];
    /* Global pll enabled flag */
    bool enabled;
    /* 'enabled' refers to the runtime configuration */
    bool channel_enabled[RCC_NUM_CHANNEL_PLL_OUT];
    /*
     * 'exists' refers to the physical configuration
     * It should only be set at pll initialization.
     * e.g. pllsai2 doesn't have a Q output.
     */
    bool channel_exists[RCC_NUM_CHANNEL_PLL_OUT];
    uint32_t channel_divider[RCC_NUM_CHANNEL_PLL_OUT];
} RccPllState;

struct STM32F4XXRCCState {
    SysBusDevice parent_obj;

    MemoryRegion mmio;

    uint32_t cr;
    uint32_t pllcfgr;
    uint32_t cfgr;
    uint32_t cir;
    uint32_t ahb1rstr;
    uint32_t ahb2rstr;
    uint32_t ahb3rstr;
    uint32_t apb1rstr;
    uint32_t apb2rstr;
    uint32_t ahb1enr;
    uint32_t ahb2enr;
    uint32_t ahb3enr;
    uint32_t apb1enr;
    uint32_t apb2enr;
    uint32_t ahb1lpenr;
    uint32_t ahb2lpenr;
    uint32_t ahb3lpenr;
    uint32_t apb1lpenr;
    uint32_t apb2lpenr;
    uint32_t bdcr;
    uint32_t csr;
    uint32_t sscgr;
    uint32_t plli2scfgr;

    /* Clock sources */
    Clock *gnd;
    Clock *lse;
    Clock *lsi_rc;
    Clock *hsi_rc;
    Clock *hse;
    Clock *i2s_extclk;

    /* PLLs */
    RccPllState plls[RCC_NUM_PLL];

    /* Muxes ~= outputs */
    RccClockMuxState clock_muxes[RCC_NUM_CLOCK_MUX];

    qemu_irq irq;
    uint64_t hse_frequency;
    uint64_t i2s_extclk_frequency;
};

#endif /* HW_STM32F4XX_RCC_H */
