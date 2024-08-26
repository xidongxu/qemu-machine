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
 * Inspired by the BCM2835 CPRMAN clock manager implementation by Luc Michel.
 */

#ifndef HW_STM32F4XX_RCC_INTERNALS_H
#define HW_STM32F4XX_RCC_INTERNALS_H

#include "hw/registerfields.h"
#include "hw/misc/stm32f4xx_rcc.h"

#define TYPE_RCC_CLOCK_MUX "stm32f4xx-rcc-clock-mux"
#define TYPE_RCC_PLL "stm32f4xx-rcc-pll"

OBJECT_DECLARE_SIMPLE_TYPE(RccClockMuxState, RCC_CLOCK_MUX)
OBJECT_DECLARE_SIMPLE_TYPE(RccPllState, RCC_PLL)

/* Register map */
REG32(CR, 0x00)
    FIELD(CR, PLLI2SRDY, 27, 1)
    FIELD(CR, PLLI2SON, 26, 1)
    FIELD(CR, PLLRDY, 25, 1)
    FIELD(CR, PLLON, 24, 1)
    FIELD(CR, CSSON, 19, 1)
    FIELD(CR, HSEBYP, 18, 1)
    FIELD(CR, HSERDY, 17, 1)
    FIELD(CR, HSEON, 16, 1)
    FIELD(CR, HSICAL, 8, 8)
    FIELD(CR, HSITRIM, 3, 5)
    FIELD(CR, HSIRDY, 1, 1)
    FIELD(CR, HSION, 0, 1)
REG32(PLLCFGR, 0x04)
    FIELD(PLLCFGR, PLLQ, 24, 4)
    FIELD(PLLCFGR, PLLSRC, 22, 1)
    FIELD(PLLCFGR, PLLP, 16, 2)
    FIELD(PLLCFGR, PLLN, 6, 8)
    FIELD(PLLCFGR, PLLM, 0, 6)
REG32(CFGR, 0x08)
    FIELD(CFGR, MCO2, 30, 2)
    FIELD(CFGR, MCO2PRE, 27, 3)
    FIELD(CFGR, MCO1PRE, 24, 3)
    FIELD(CFGR, I2SSRC, 23, 1)
    FIELD(CFGR, MCO1, 21, 2)
    FIELD(CFGR, RTCPRE, 16, 5)
    FIELD(CFGR, PPRE2, 13, 3)
    FIELD(CFGR, PPRE1, 10, 3)
    FIELD(CFGR, HPRE, 4, 4)
    FIELD(CFGR, SWS, 2, 2)
    FIELD(CFGR, SW, 0, 2)
REG32(CIR, 0x0C)
    FIELD(CIR, CSSC, 23, 1)
    FIELD(CIR, PLLI2SRDYC, 21, 1)
    FIELD(CIR, PLLRDYC, 20, 1)
    FIELD(CIR, HSERDYC, 19, 1)
    FIELD(CIR, HSIRDYC, 18, 1)
    FIELD(CIR, LSERDYC, 17, 1)
    FIELD(CIR, LSIRDYC, 16, 1)
    FIELD(CIR, PLLI2SRDYIE, 13, 1)
    FIELD(CIR, PLLRDYIE, 12, 1)
    FIELD(CIR, HSERDYIE, 11, 1)
    FIELD(CIR, HSIRDYIE, 10, 1)
    FIELD(CIR, LSERDYIE, 9, 1)
    FIELD(CIR, LSIRDYIE, 8, 1)
    FIELD(CIR, CSSF, 7, 1)
    FIELD(CIR, PLLI2SRDYF, 5, 1)
    FIELD(CIR, PLLRDYF, 4, 1)
    FIELD(CIR, HSERDYF, 3, 1)
    FIELD(CIR, HSIRDYF, 2, 1)
    FIELD(CIR, LSERDYF, 1, 1)
    FIELD(CIR, LSIRDYF, 0, 1)
REG32(AHB1RSTR, 0x10)
    FIELD(AHB1RSTR, OTGHSRST, 29, 1)
    FIELD(AHB1RSTR, ETHMACRST, 25, 1)
    FIELD(AHB1RSTR, DMA2RST, 22, 1)
    FIELD(AHB1RSTR, DMA1RST, 21, 1)
    FIELD(AHB1RSTR, CRCRST, 12, 1)
    FIELD(AHB1RSTR, GPIOIRST, 8, 1)
    FIELD(AHB1RSTR, GPIOHRST, 7, 1)
    FIELD(AHB1RSTR, GPIOGRST, 6, 1)
    FIELD(AHB1RSTR, GPIOFRST, 5, 1)
    FIELD(AHB1RSTR, GPIOERST, 4, 1)
    FIELD(AHB1RSTR, GPIODRST, 3, 1)
    FIELD(AHB1RSTR, GPIOCRST, 2, 1)
    FIELD(AHB1RSTR, GPIOBRST, 1, 1)
    FIELD(AHB1RSTR, GPIOARST, 0, 1)
REG32(AHB2RSTR, 0x14)
    FIELD(AHB2RSTR, OTGFSRST, 7, 1)
    FIELD(AHB2RSTR, RNGRST, 6, 1)
    FIELD(AHB2RSTR, HASHRST, 5, 1)
    FIELD(AHB2RSTR, CRYPRST, 4, 1)
    FIELD(AHB2RSTR, DCMIRST, 0, 1)
REG32(AHB3RSTR, 0x18)
    FIELD(AHB3RSTR, FSMCRST, 0, 1)
REG32(APB1RSTR, 0x20)
    FIELD(APB1RSTR, DACRST, 29, 1)
    FIELD(APB1RSTR, PWRRST, 28, 1)
    FIELD(APB1RSTR, CAN2RST, 26, 1)
    FIELD(APB1RSTR, CAN1RST, 25, 1)
    FIELD(APB1RSTR, I2C3RST, 23, 1)
    FIELD(APB1RSTR, I2C2RST, 22, 1)
    FIELD(APB1RSTR, I2C1RST, 21, 1)
    FIELD(APB1RSTR, UART5RST, 20, 1)
    FIELD(APB1RSTR, UART4RST, 19, 1)
    FIELD(APB1RSTR, USART3RST, 18, 1)
    FIELD(APB1RSTR, USART2RST, 17, 1)
    FIELD(APB1RSTR, SPI3RST, 15, 1)
    FIELD(APB1RSTR, SPI2RST, 14, 1)
    FIELD(APB1RSTR, WWDGRST, 11, 1)
    FIELD(APB1RSTR, TIM14RST, 8, 1)
    FIELD(APB1RSTR, TIM13RST, 7, 1)
    FIELD(APB1RSTR, TIM12RST, 6, 1)
    FIELD(APB1RSTR, TIM7RST, 5, 1)
    FIELD(APB1RSTR, TIM6RST, 4, 1)
    FIELD(APB1RSTR, TIM5RST, 3, 1)
    FIELD(APB1RSTR, TIM4RST, 2, 1)
    FIELD(APB1RSTR, TIM3RST, 1, 1)
    FIELD(APB1RSTR, TIM2RST, 0, 1)
REG32(APB2RSTR, 0x24)
    FIELD(APB2RSTR, TIM11RST, 18, 1)
    FIELD(APB2RSTR, TIM10RST, 17, 1)
    FIELD(APB2RSTR, TIM9RST, 16, 1)
    FIELD(APB2RSTR, SYSCFGRST, 14, 1)
    FIELD(APB2RSTR, SPI1RST, 12, 1)
    FIELD(APB2RSTR, SDIORST, 11, 1)
    FIELD(APB2RSTR, ADCRST, 8, 1)
    FIELD(APB2RSTR, USART6RST, 5, 1)
    FIELD(APB2RSTR, USART1RST, 4, 1)
    FIELD(APB2RSTR, TIM8RST, 1, 1)
    FIELD(APB2RSTR, TIM1RST, 0, 1)
REG32(AHB1ENR, 0x30)
    FIELD(AHB1ENR, OTGHSULPIEN, 30, 1)
    FIELD(AHB1ENR, OTGHSEN, 29, 1)
    FIELD(AHB1ENR, ETHMACPTPEN, 28, 1)
    FIELD(AHB1ENR, ETHMACRXEN, 27, 1)
    FIELD(AHB1ENR, ETHMACTXEN, 26, 1)
    FIELD(AHB1ENR, ETHMACEN, 25, 1)
    FIELD(AHB1ENR, DMA2EN, 22, 1)
    FIELD(AHB1ENR, DMA1EN, 21, 1)
    FIELD(AHB1ENR, CCMDATARAMEN, 20, 1)
    FIELD(AHB1ENR, BKPSRAMEN, 18, 1)
    FIELD(AHB1ENR, CRCEN, 12, 1)
    FIELD(AHB1ENR, GPIOIEN, 8, 1)
    FIELD(AHB1ENR, GPIOHEN, 7, 1)
    FIELD(AHB1ENR, GPIOGEN, 6, 1)
    FIELD(AHB1ENR, GPIOFEN, 5, 1)
    FIELD(AHB1ENR, GPIOEEN, 4, 1)
    FIELD(AHB1ENR, GPIODEN, 3, 1)
    FIELD(AHB1ENR, GPIOCEN, 2, 1)
    FIELD(AHB1ENR, GPIOBEN, 1, 1)
    FIELD(AHB1ENR, GPIOAEN, 0, 1)
REG32(AHB2ENR, 0x34)
    FIELD(AHB2ENR, OTGFSEN, 7, 1)
    FIELD(AHB2ENR, RNGEN, 6, 1)
    FIELD(AHB2ENR, HASHEN, 5, 1)
    FIELD(AHB2ENR, CRYPEN, 4, 1)
    FIELD(AHB2ENR, DCMIEN, 0, 1)
REG32(AHB3ENR, 0x38)
    FIELD(AHB3ENR, FSMCEN, 0, 1)
REG32(APB1ENR, 0x40)
    FIELD(APB1ENR, DACEN, 29, 1)
    FIELD(APB1ENR, PWREN, 28, 1)
    FIELD(APB1ENR, CAN2EN, 26, 1)
    FIELD(APB1ENR, CAN1EN, 25, 1)
    FIELD(APB1ENR, I2C3EN, 23, 1)
    FIELD(APB1ENR, I2C2EN, 22, 1)
    FIELD(APB1ENR, I2C1EN, 21, 1)
    FIELD(APB1ENR, UART5EN, 20, 1)
    FIELD(APB1ENR, UART4EN, 19, 1)
    FIELD(APB1ENR, USART3EN, 18, 1)
    FIELD(APB1ENR, USART2EN, 17, 1)
    FIELD(APB1ENR, SPI3EN, 15, 1)
    FIELD(APB1ENR, SPI2EN, 14, 1)
    FIELD(APB1ENR, WWDGEN, 11, 1)
    FIELD(APB1ENR, TIM14EN, 8, 1)
    FIELD(APB1ENR, TIM13EN, 7, 1)
    FIELD(APB1ENR, TIM12EN, 6, 1)
    FIELD(APB1ENR, TIM7EN, 5, 1)
    FIELD(APB1ENR, TIM6EN, 4, 1)
    FIELD(APB1ENR, TIM5EN, 3, 1)
    FIELD(APB1ENR, TIM4EN, 2, 1)
    FIELD(APB1ENR, TIM3EN, 1, 1)
    FIELD(APB1ENR, TIM2EN, 0, 1)
REG32(APB2ENR, 0x44)
    FIELD(APB2ENR, TIM11EN, 18, 1)
    FIELD(APB2ENR, TIM10EN, 17, 1)
    FIELD(APB2ENR, TIM9EN, 16, 1)
    FIELD(APB2ENR, SYSCFGEN, 14, 1)
    FIELD(APB2ENR, SPI1EN, 12, 1)
    FIELD(APB2ENR, SDIOEN, 11, 1)
    FIELD(APB2ENR, ADC3EN, 10, 1)
    FIELD(APB2ENR, ADC2EN, 9, 1)
    FIELD(APB2ENR, ADC1EN, 8, 1)
    FIELD(APB2ENR, USART6EN, 5, 1)
    FIELD(APB2ENR, USART1EN, 4, 1)
    FIELD(APB2ENR, TIM8EN, 1, 1)
    FIELD(APB2ENR, TIM1EN, 0, 1)
REG32(AHB1LPENR, 0x50)
    FIELD(AHB1LPENR, OTGHSULPILPEN, 30, 1)
    FIELD(AHB1LPENR, OTGHSLPEN, 29, 1)
    FIELD(AHB1LPENR, ETHMACPTPLPEN, 28, 1)
    FIELD(AHB1LPENR, ETHMACRXLPEN, 27, 1)
    FIELD(AHB1LPENR, ETHMACTXLPEN, 26, 1)
    FIELD(AHB1LPENR, ETHMACLPEN, 25, 1)
    FIELD(AHB1LPENR, DMA2LPEN, 22, 1)
    FIELD(AHB1LPENR, DMA1LPEN, 21, 1)
    FIELD(AHB1LPENR, BKPSRAMLPEN, 18, 1)
    FIELD(AHB1LPENR, SRAM2LPEN, 17, 1)
    FIELD(AHB1LPENR, SRAM1LPEN, 16, 1)
    FIELD(AHB1LPENR, FLITFLPEN, 15, 1)
    FIELD(AHB1LPENR, CRCLPEN, 12, 1)
    FIELD(AHB1LPENR, GPIOILPEN, 8, 1)
    FIELD(AHB1LPENR, GPIOHLPEN, 7, 1)
    FIELD(AHB1LPENR, GPIOGLPEN, 6, 1)
    FIELD(AHB1LPENR, GPIOFLPEN, 5, 1)
    FIELD(AHB1LPENR, GPIOELPEN, 4, 1)
    FIELD(AHB1LPENR, GPIODLPEN, 3, 1)
    FIELD(AHB1LPENR, GPIOCLPEN, 2, 1)
    FIELD(AHB1LPENR, GPIOBLPEN, 1, 1)
    FIELD(AHB1LPENR, GPIOALPEN, 0, 1)
REG32(AHB2LPENR, 0x54)
    FIELD(AHB2LPENR, OTGFSLPEN, 7, 1)
    FIELD(AHB2LPENR, RNGLPEN, 6, 1)
    FIELD(AHB2LPENR, HASHLPEN, 5, 1)
    FIELD(AHB2LPENR, CRYPLPEN, 4, 1)
    FIELD(AHB2LPENR, DCMILPEN, 0, 1)
REG32(AHB3LPENR, 0x58)
    FIELD(AHB3LPENR, FSMCLPEN, 0, 1)
REG32(APB1LPENR, 0x60)
    FIELD(APB1LPENR, DACLPEN, 29, 1)
    FIELD(APB1LPENR, PWRLPEN, 28, 1)
    FIELD(APB1LPENR, CAN2LPEN, 26, 1)
    FIELD(APB1LPENR, CAN1LPEN, 25, 1)
    FIELD(APB1LPENR, I2C3LPEN, 23, 1)
    FIELD(APB1LPENR, I2C2LPEN, 22, 1)
    FIELD(APB1LPENR, I2C1LPEN, 21, 1)
    FIELD(APB1LPENR, UART5LPEN, 20, 1)
    FIELD(APB1LPENR, UART4LPEN, 19, 1)
    FIELD(APB1LPENR, USART3LPEN, 18, 1)
    FIELD(APB1LPENR, USART2LPEN, 17, 1)
    FIELD(APB1LPENR, SPI3LPEN, 15, 1)
    FIELD(APB1LPENR, SPI2LPEN, 14, 1)
    FIELD(APB1LPENR, WWDGLPEN, 11, 1)
    FIELD(APB1LPENR, TIM14LPEN, 8, 1)
    FIELD(APB1LPENR, TIM13LPEN, 7, 1)
    FIELD(APB1LPENR, TIM12LPEN, 6, 1)
    FIELD(APB1LPENR, TIM7LPEN, 5, 1)
    FIELD(APB1LPENR, TIM6LPEN, 4, 1)
    FIELD(APB1LPENR, TIM5LPEN, 3, 1)
    FIELD(APB1LPENR, TIM4LPEN, 2, 1)
    FIELD(AHB1LPENR, TIM3LPEN, 1, 1)
    FIELD(AHB1LPENR, TIM2LPEN, 0, 1)
REG32(APB2LPENR, 0x64)
    FIELD(APB2LPENR, TIM11LPEN, 18, 1)
    FIELD(APB2LPENR, TIM10LPEN, 17, 1)
    FIELD(APB2LPENR, TIM9LPEN, 16, 1)
    FIELD(APB2LPENR, SYSCFGLPEN, 14, 1)
    FIELD(APB2LPENR, SPI1LPEN, 12, 1)
    FIELD(APB2LPENR, SDIOLPEN, 11, 1)
    FIELD(APB2LPENR, ADC3LPEN, 10, 1)
    FIELD(APB2LPENR, ADC2LPEN, 9, 1)
    FIELD(APB2LPENR, ADC1LPEN, 8, 1)
    FIELD(APB2LPENR, USART6LPEN, 5, 1)
    FIELD(APB2LPENR, USART1LPEN, 4, 1)
    FIELD(APB2LPENR, TIM8LPEN, 1, 1)
    FIELD(APB2LPENR, TIM1LPEN, 0, 1)
REG32(BDCR, 0x70)
    FIELD(BDCR, BDRST, 16, 1)
    FIELD(BDCR, RTCEN, 15, 1)
    FIELD(BDCR, RTCSEL, 8, 2)
    FIELD(BDCR, LSEBYP, 2, 1)
    FIELD(BDCR, LSERDY, 1, 1)
    FIELD(BDCR, LSEON, 0, 1)
REG32(CSR, 0x74)
    FIELD(CSR, LPWRRSTF, 31, 1)
    FIELD(CSR, WWDGRSTF, 30, 1)
    FIELD(CSR, IWDGRSTF, 29, 1)
    FIELD(CSR, SFTRSTF, 28, 1)
    FIELD(CSR, PORRSTF, 27, 1)
    FIELD(CSR, PINRSTF, 26, 1)
    FIELD(CSR, BORRSTF, 25, 1)
    FIELD(CSR, RMVF, 24, 1)
    FIELD(CSR, LSIRDY, 1, 1)
    FIELD(CSR, LSION, 0, 1)
REG32(SSCGR, 0x80)
    FIELD(SSCGR, SSCGEN, 31, 1)
    FIELD(SSCGR, SPREADSEL, 30, 1)
    FIELD(SSCGR, INCSTEP, 13, 15)
    FIELD(SSCGR, MODPER, 0, 13)
REG32(PLLI2SCFGR, 0x84)
    FIELD(PLLI2SCFGR, PLLI2SR, 28, 3)
    FIELD(PLLI2SCFGR, PLLI2SN, 6, 9)

/* Read Only masks to prevent writes in unauthorized bits */
#define CR_READ_ONLY_MASK (R_CR_PLLSAI2RDY_MASK | \
                           R_CR_PLLSAI1RDY_MASK | \
                           R_CR_PLLRDY_MASK     | \
                           R_CR_HSERDY_MASK     | \
                           R_CR_HSIRDY_MASK     | \
                           R_CR_MSIRDY_MASK)
#define CR_READ_SET_MASK (R_CR_CSSON_MASK | R_CR_MSIRGSEL_MASK)
#define ICSCR_READ_ONLY_MASK (R_ICSCR_HSICAL_MASK | R_ICSCR_MSICAL_MASK)
#define CFGR_READ_ONLY_MASK (R_CFGR_SWS_MASK)
#define CIFR_READ_ONLY_MASK (R_CIFR_LSECSSF_MASK     | \
                             R_CIFR_CSSF_MASK        | \
                             R_CIFR_PLLSAI2RDYF_MASK | \
                             R_CIFR_PLLSAI1RDYF_MASK | \
                             R_CIFR_PLLRDYF_MASK     | \
                             R_CIFR_HSERDYF_MASK     | \
                             R_CIFR_HSIRDYF_MASK     | \
                             R_CIFR_MSIRDYF_MASK     | \
                             R_CIFR_LSERDYF_MASK     | \
                             R_CIFR_LSIRDYF_MASK)
#define CIFR_IRQ_MASK CIFR_READ_ONLY_MASK
#define APB2ENR_READ_SET_MASK (R_APB2ENR_FWEN_MASK)
#define BDCR_READ_ONLY_MASK (R_BDCR_LSECSSD_MASK | R_BDCR_LSERDY_MASK)
#define CSR_READ_ONLY_MASK (R_CSR_LPWRRSTF_MASK | \
                            R_CSR_WWDGRSTF_MASK | \
                            R_CSR_IWWGRSTF_MASK | \
                            R_CSR_SFTRSTF_MASK  | \
                            R_CSR_BORRSTF_MASK  | \
                            R_CSR_PINRSTF_MASK  | \
                            R_CSR_OBLRSTF_MASK  | \
                            R_CSR_FWRSTF_MASK   | \
                            R_CSR_LSIRDY_MASK)

/* Pll Channels */
enum PllChannels {
    RCC_PLL_CHANNEL_PLLSAI3CLK = 0,
    RCC_PLL_CHANNEL_PLL48M1CLK = 1,
    RCC_PLL_CHANNEL_PLLCLK = 2,
};

enum PllSai1Channels {
    RCC_PLLSAI1_CHANNEL_PLLSAI1CLK = 0,
    RCC_PLLSAI1_CHANNEL_PLL48M2CLK = 1,
    RCC_PLLSAI1_CHANNEL_PLLADC1CLK = 2,
};

enum PllSai2Channels {
    RCC_PLLSAI2_CHANNEL_PLLSAI2CLK = 0,
    /* No Q channel */
    RCC_PLLSAI2_CHANNEL_PLLADC2CLK = 2,
};

typedef enum RccClockMuxSource {
    RCC_CLOCK_MUX_SRC_GND = 0,
    RCC_CLOCK_MUX_SRC_HSI,
    RCC_CLOCK_MUX_SRC_HSE,
    RCC_CLOCK_MUX_SRC_MSI,
    RCC_CLOCK_MUX_SRC_LSI,
    RCC_CLOCK_MUX_SRC_LSE,
    RCC_CLOCK_MUX_SRC_SAI1_EXTCLK,
    RCC_CLOCK_MUX_SRC_SAI2_EXTCLK,
    RCC_CLOCK_MUX_SRC_PLL,
    RCC_CLOCK_MUX_SRC_PLLSAI1,
    RCC_CLOCK_MUX_SRC_PLLSAI2,
    RCC_CLOCK_MUX_SRC_PLLSAI3,
    RCC_CLOCK_MUX_SRC_PLL48M1,
    RCC_CLOCK_MUX_SRC_PLL48M2,
    RCC_CLOCK_MUX_SRC_PLLADC1,
    RCC_CLOCK_MUX_SRC_PLLADC2,
    RCC_CLOCK_MUX_SRC_SYSCLK,
    RCC_CLOCK_MUX_SRC_HCLK,
    RCC_CLOCK_MUX_SRC_PCLK1,
    RCC_CLOCK_MUX_SRC_PCLK2,
    RCC_CLOCK_MUX_SRC_HSE_OVER_32,
    RCC_CLOCK_MUX_SRC_LCD_AND_RTC_COMMON,

    RCC_CLOCK_MUX_SRC_NUMBER,
} RccClockMuxSource;

/* PLL init info */
typedef struct PllInitInfo {
    const char *name;

    const char *channel_name[RCC_NUM_CHANNEL_PLL_OUT];
    bool channel_exists[RCC_NUM_CHANNEL_PLL_OUT];
    uint32_t default_channel_divider[RCC_NUM_CHANNEL_PLL_OUT];

    RccClockMuxSource src_mapping[RCC_NUM_CLOCK_MUX_SRC];
} PllInitInfo;

static const PllInitInfo PLL_INIT_INFO[] = {
    [RCC_PLL_PLL] = {
        .name = "pll",
        .channel_name = {
            "pllsai3clk",
            "pll48m1clk",
            "pllclk"
        },
        .channel_exists = {
            true, true, true
        },
        /* From PLLCFGR register documentation */
        .default_channel_divider = {
            7, 2, 2
        }
    },
    [RCC_PLL_PLLSAI1] = {
        .name = "pllsai1",
        .channel_name = {
            "pllsai1clk",
            "pll48m2clk",
            "plladc1clk"
        },
        .channel_exists = {
            true, true, true
        },
        /* From PLLSAI1CFGR register documentation */
        .default_channel_divider = {
            7, 2, 2
        }
    },
    [RCC_PLL_PLLSAI2] = {
        .name = "pllsai2",
        .channel_name = {
            "pllsai2clk",
            NULL,
            "plladc2clk"
        },
        .channel_exists = {
            true, false, true
        },
        /* From PLLSAI2CFGR register documentation */
        .default_channel_divider = {
            7, 0, 2
        }
    }
};

static inline void set_pll_init_info(RccPllState *pll,
                                     RccPll id)
{
    int i;

    pll->id = id;
    pll->vco_multiplier = 1;
    for (i = 0; i < RCC_NUM_CHANNEL_PLL_OUT; i++) {
        pll->channel_enabled[i] = false;
        pll->channel_exists[i] = PLL_INIT_INFO[id].channel_exists[i];
        pll->channel_divider[i] = PLL_INIT_INFO[id].default_channel_divider[i];
    }
}

/* Clock mux init info */
typedef struct ClockMuxInitInfo {
    const char *name;

    uint32_t multiplier;
    uint32_t divider;
    bool enabled;
    /* If this is true, the clock will not be exposed outside of the device */
    bool hidden;

    RccClockMuxSource src_mapping[RCC_NUM_CLOCK_MUX_SRC];
} ClockMuxInitInfo;

#define FILL_DEFAULT_FACTOR \
    .multiplier = 1, \
    .divider =  1

#define FILL_DEFAULT_INIT_ENABLED \
    FILL_DEFAULT_FACTOR, \
    .enabled = true

#define FILL_DEFAULT_INIT_DISABLED \
    FILL_DEFAULT_FACTOR, \
    .enabled = false


static const ClockMuxInitInfo CLOCK_MUX_INIT_INFO[] = {
    [RCC_CLOCK_MUX_SYSCLK] = {
        .name = "sysclk",
        /* Same mapping as: CFGR_SW */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_MSI,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_HSE,
            RCC_CLOCK_MUX_SRC_PLL,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    [RCC_CLOCK_MUX_PLL_INPUT] = {
        .name = "pll-input",
        /* Same mapping as: PLLCFGR_PLLSRC */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_MSI,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_HSE,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    [RCC_CLOCK_MUX_HCLK] = {
        .name = "hclk",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    [RCC_CLOCK_MUX_PCLK1] = {
        .name = "pclk1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    [RCC_CLOCK_MUX_PCLK2] = {
        .name = "pclk2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    [RCC_CLOCK_MUX_HSE_OVER_32] = {
        .name = "hse-divided-by-32",
        .multiplier = 1,
        .divider = 32,
        .enabled = true,
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HSE,
        },
        .hidden = true,
    },
    [RCC_CLOCK_MUX_LCD_AND_RTC_COMMON] = {
        .name = "lcd-and-rtc-common-mux",
        /* Same mapping as: BDCR_RTCSEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_GND,
            RCC_CLOCK_MUX_SRC_LSE,
            RCC_CLOCK_MUX_SRC_LSI,
            RCC_CLOCK_MUX_SRC_HSE_OVER_32,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    /* From now on, muxes with a publicly available output */
    [RCC_CLOCK_MUX_CORTEX_REFCLK] = {
        .name = "cortex-refclk",
        .multiplier = 1,
        /* REFCLK is always HCLK/8 */
        .divider = 8,
        .enabled = true,
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        }
    },
    [RCC_CLOCK_MUX_USART1] = {
        .name = "usart1",
        /* Same mapping as: CCIPR_USART1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_USART2] = {
        .name = "usart2",
        /* Same mapping as: CCIPR_USART2SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_USART3] = {
        .name = "usart3",
        /* Same mapping as: CCIPR_USART3SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_UART4] = {
        .name = "uart4",
        /* Same mapping as: CCIPR_UART4SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_UART5] = {
        .name = "uart5",
        /* Same mapping as: CCIPR_UART5SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_LPUART1] = {
        .name = "lpuart1",
        /* Same mapping as: CCIPR_LPUART1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_I2C1] = {
        .name = "i2c1",
        /* Same mapping as: CCIPR_I2C1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_I2C2] = {
        .name = "i2c2",
        /* Same mapping as: CCIPR_I2C2SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_I2C3] = {
        .name = "i2c3",
        /* Same mapping as: CCIPR_I2C3SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_HSI,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_LPTIM1] = {
        .name = "lptim1",
        /* Same mapping as: CCIPR_LPTIM1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_LSI,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_LPTIM2] = {
        .name = "lptim2",
        /* Same mapping as: CCIPR_LPTIM2SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_LSI,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SWPMI1] = {
        .name = "swpmi1",
        /* Same mapping as: CCIPR_SWPMI1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
            RCC_CLOCK_MUX_SRC_HSI,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_MCO] = {
        .name = "mco",
        /* Same mapping as: CFGR_MCOSEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_MSI,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_HSE,
            RCC_CLOCK_MUX_SRC_PLL,
            RCC_CLOCK_MUX_SRC_LSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_LSCO] = {
        .name = "lsco",
        /* Same mapping as: BDCR_LSCOSEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_LSI,
            RCC_CLOCK_MUX_SRC_LSE,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DFSDM1] = {
        .name = "dfsdm1",
        /* Same mapping as: CCIPR_DFSDM1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ADC] = {
        .name = "adc",
        /* Same mapping as: CCIPR_ADCSEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_GND,
            RCC_CLOCK_MUX_SRC_PLLADC1,
            RCC_CLOCK_MUX_SRC_PLLADC2,
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CLK48] = {
        .name = "clk48",
        /* Same mapping as: CCIPR_CLK48SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_GND,
            RCC_CLOCK_MUX_SRC_PLL48M2,
            RCC_CLOCK_MUX_SRC_PLL48M1,
            RCC_CLOCK_MUX_SRC_MSI,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SAI2] = {
        .name = "sai2",
        /* Same mapping as: CCIPR_SAI2SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PLLSAI1,
            RCC_CLOCK_MUX_SRC_PLLSAI2,
            RCC_CLOCK_MUX_SRC_PLLSAI3,
            RCC_CLOCK_MUX_SRC_SAI2_EXTCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SAI1] = {
        .name = "sai1",
        /* Same mapping as: CCIPR_SAI1SEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PLLSAI1,
            RCC_CLOCK_MUX_SRC_PLLSAI2,
            RCC_CLOCK_MUX_SRC_PLLSAI3,
            RCC_CLOCK_MUX_SRC_SAI1_EXTCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    /* From now on, these muxes only have one valid source */
    [RCC_CLOCK_MUX_TSC] = {
        .name = "tsc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CRC] = {
        .name = "crc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_FLASH] = {
        .name = "flash",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DMA2] = {
        .name = "dma2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DMA1] = {
        .name = "dma1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_RNG] = {
        .name = "rng",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_AES] = {
        .name = "aes",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_OTGFS] = {
        .name = "otgfs",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOA] = {
        .name = "gpioa",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOB] = {
        .name = "gpiob",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOC] = {
        .name = "gpioc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOD] = {
        .name = "gpiod",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOE] = {
        .name = "gpioe",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOF] = {
        .name = "gpiof",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOG] = {
        .name = "gpiog",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOH] = {
        .name = "gpioh",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_QSPI] = {
        .name = "qspi",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_FMC] = {
        .name = "fmc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_OPAMP] = {
        .name = "opamp",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DAC1] = {
        .name = "dac1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_PWR] = {
        .name = "pwr",
        /*
         * PWREN is in the APB1ENR1 register,
         * but PWR uses SYSCLK according to the clock tree.
         */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CAN1] = {
        .name = "can1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SPI3] = {
        .name = "spi3",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SPI2] = {
        .name = "spi2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_WWDG] = {
        .name = "wwdg",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_LCD] = {
        .name = "lcd",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_LCD_AND_RTC_COMMON,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM7] = {
        .name = "tim7",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM6] = {
        .name = "tim6",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM5] = {
        .name = "tim5",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM4] = {
        .name = "tim4",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM3] = {
        .name = "tim3",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM2] = {
        .name = "tim2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM17] = {
        .name = "tim17",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM16] = {
        .name = "tim16",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM15] = {
        .name = "tim15",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM8] = {
        .name = "tim8",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SPI1] = {
        .name = "spi1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM1] = {
        .name = "tim1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SDMMC1] = {
        .name = "sdmmc1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_FW] = {
        .name = "fw",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SYSCFG] = {
        .name = "syscfg",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_RTC] = {
        .name = "rtc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_LCD_AND_RTC_COMMON,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CORTEX_FCLK] = {
        .name = "cortex-fclk",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_ENABLED,
    },
};

static inline void set_clock_mux_init_info(RccClockMuxState *mux,
                                           RccClockMux id)
{
    mux->id = id;
    mux->multiplier = CLOCK_MUX_INIT_INFO[id].multiplier;
    mux->divider = CLOCK_MUX_INIT_INFO[id].divider;
    mux->enabled = CLOCK_MUX_INIT_INFO[id].enabled;
    /*
     * Every peripheral has the first source of their source list as
     * as their default source.
     */
    mux->src = 0;
}

#endif /* HW_STM32F4XX_RCC_INTERNALS_H */
