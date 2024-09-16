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
#define CR_RO_MASK         (R_CR_PLLI2SRDY_MASK | \
                            R_CR_PLLRDY_MASK | \
                            R_CR_HSERDY_MASK | \
                            R_CR_HSICAL_MASK | \
                            R_CR_HSIRDY_MASK)
#define CR_WO_MASK         (0)
#define CR_RW_MASK         (R_CR_PLLI2SON_MASK | \
                            R_CR_PLLON_MASK | \
                            R_CR_CSSON_MASK | \
                            R_CR_HSEBYP_MASK | \
                            R_CR_HSEON_MASK | \
                            R_CR_HSITRIM_MASK | \
                            R_CR_HSION_MASK)

#define PLLCFGR_RO_MASK    (0)
#define PLLCFGR_WO_MASK    (0)
#define PLLCFGR_RW_MASK    (R_PLLCFGR_PLLQ_MASK | \
                            R_PLLCFGR_PLLSRC_MASK | \
                            R_PLLCFGR_PLLP_MASK | \
                            R_PLLCFGR_PLLN_MASK | \
                            R_PLLCFGR_PLLM_MASK)

#define CFGR_RO_MASK       (R_CFGR_SWS_MASK)
#define CFGR_WO_MASK       (0)
#define CFGR_RW_MASK       (R_CFGR_MCO2_MASK | \
                            R_CFGR_MCO2PRE_MASK | \
                            R_CFGR_MCO1PRE_MASK | \
                            R_CFGR_I2SSRC_MASK | \
                            R_CFGR_MCO1_MASK | \
                            R_CFGR_RTCPRE_MASK | \
                            R_CFGR_PPRE2_MASK | \
                            R_CFGR_PPRE1_MASK | \
                            R_CFGR_HPRE_MASK | \
                            R_CFGR_SW_MASK)

#define CIR_RO_MASK        (R_CIR_CSSF_MASK | \
                            R_CIR_PLLI2SRDYF_MASK | \
                            R_CIR_PLLRDYF_MASK | \
                            R_CIR_HSERDYF_MASK | \
                            R_CIR_HSIRDYF_MASK | \
                            R_CIR_LSERDYF_MASK | \
                            R_CIR_LSIRDYF_MASK)
#define CIR_WO_MASK        (R_CIR_CSSC_MASK | \
                            R_CIR_PLLI2SRDYC_MASK | \
                            R_CIR_PLLRDYC_MASK | \
                            R_CIR_HSERDYC_MASK | \
                            R_CIR_HSIRDYC_MASK | \
                            R_CIR_LSERDYC_MASK | \
                            R_CIR_LSIRDYC_MASK)
#define CIR_RW_MASK        (R_CIR_PLLI2SRDYIE_MASK | \
                            R_CIR_PLLRDYIE_MASK | \
                            R_CIR_HSERDYIE_MASK | \
                            R_CIR_HSIRDYIE_MASK | \
                            R_CIR_LSERDYIE_MASK | \
                            R_CIR_LSIRDYIE_MASK)

#define AHB1RSTR_RO_MASK   (0)
#define AHB1RSTR_WO_MASK   (0)
#define AHB1RSTR_RW_MASK   (R_AHB1RSTR_OTGHSRST_MASK | \
                            R_AHB1RSTR_ETHMACRST_MASK | \
                            R_AHB1RSTR_DMA2RST_MASK | \
                            R_AHB1RSTR_DMA1RST_MASK | \
                            R_AHB1RSTR_CRCRST_MASK | \
                            R_AHB1RSTR_GPIOIRST_MASK | \
                            R_AHB1RSTR_GPIOHRST_MASK | \
                            R_AHB1RSTR_GPIOGRST_MASK | \
                            R_AHB1RSTR_GPIOFRST_MASK | \
                            R_AHB1RSTR_GPIOERST_MASK | \
                            R_AHB1RSTR_GPIODRST_MASK | \
                            R_AHB1RSTR_GPIOCRST_MASK | \
                            R_AHB1RSTR_GPIOBRST_MASK | \
                            R_AHB1RSTR_GPIOARST_MASK)

#define AHB2RSTR_RO_MASK   (0)
#define AHB2RSTR_WO_MASK   (0)
#define AHB2RSTR_RW_MASK   (R_AHB2RSTR_OTGFSRST_MASK | \
                            R_AHB2RSTR_RNGRST_MASK | \
                            R_AHB2RSTR_HASHRST_MASK | \
                            R_AHB2RSTR_CRYPRST_MASK | \
                            R_AHB2RSTR_DCMIRST_MASK)

#define AHB3RSTR_RO_MASK   (0)
#define AHB3RSTR_WO_MASK   (0)
#define AHB3RSTR_RW_MASK   (R_AHB3RSTR_FSMCRST_MASK)

#define APB1RSTR_RO_MASK   (0)
#define APB1RSTR_WO_MASK   (0)
#define APB1RSTR_RW_MASK   (R_APB1RSTR_DACRST_MASK | \
                            R_APB1RSTR_PWRRST_MASK | \
                            R_APB1RSTR_CAN2RST_MASK | \
                            R_APB1RSTR_CAN1RST_MASK | \
                            R_APB1RSTR_I2C3RST_MASK | \
                            R_APB1RSTR_I2C2RST_MASK | \
                            R_APB1RSTR_I2C1RST_MASK | \
                            R_APB1RSTR_UART5RST_MASK | \
                            R_APB1RSTR_UART4RST_MASK | \
                            R_APB1RSTR_USART3RST_MASK | \
                            R_APB1RSTR_USART2RST_MASK | \
                            R_APB1RSTR_SPI3RST_MASK | \
                            R_APB1RSTR_SPI2RST_MASK | \
                            R_APB1RSTR_WWDGRST_MASK | \
                            R_APB1RSTR_TIM14RST_MASK | \
                            R_APB1RSTR_TIM13RST_MASK | \
                            R_APB1RSTR_TIM12RST_MASK | \
                            R_APB1RSTR_TIM7RST_MASK | \
                            R_APB1RSTR_TIM6RST_MASK | \
                            R_APB1RSTR_TIM5RST_MASK | \
                            R_APB1RSTR_TIM4RST_MASK | \
                            R_APB1RSTR_TIM3RST_MASK | \
                            R_APB1RSTR_TIM2RST_MASK)

#define APB2RSTR_RO_MASK   (0)
#define APB2RSTR_WO_MASK   (0)
#define APB2RSTR_RW_MASK   (R_APB2RSTR_TIM11RST_MASK | \
                            R_APB2RSTR_TIM10RST_MASK | \
                            R_APB2RSTR_TIM9RST_MASK | \
                            R_APB2RSTR_SYSCFGRST_MASK | \
                            R_APB2RSTR_SPI1RST_MASK | \
                            R_APB2RSTR_SDIORST_MASK | \
                            R_APB2RSTR_ADCRST_MASK | \
                            R_APB2RSTR_USART6RST_MASK | \
                            R_APB2RSTR_USART1RST_MASK | \
                            R_APB2RSTR_TIM8RST_MASK | \
                            R_APB2RSTR_TIM1RST_MASK)

#define AHB1ENR_RO_MASK    (0)
#define AHB1ENR_WO_MASK    (0)
#define AHB1ENR_RW_MASK    (R_AHB1ENR_OTGHSULPIEN_MASK | \
                            R_AHB1ENR_OTGHSEN_MASK | \
                            R_AHB1ENR_ETHMACPTPEN_MASK | \
                            R_AHB1ENR_ETHMACRXEN_MASK | \
                            R_AHB1ENR_ETHMACTXEN_MASK | \
                            R_AHB1ENR_ETHMACEN_MASK | \
                            R_AHB1ENR_DMA2EN_MASK | \
                            R_AHB1ENR_DMA1EN_MASK | \
                            R_AHB1ENR_CCMDATARAMEN_MASK | \
                            R_AHB1ENR_BKPSRAMEN_MASK | \
                            R_AHB1ENR_CRCEN_MASK | \
                            R_AHB1ENR_GPIOIEN_MASK | \
                            R_AHB1ENR_GPIOHEN_MASK | \
                            R_AHB1ENR_GPIOGEN_MASK | \
                            R_AHB1ENR_GPIOFEN_MASK | \
                            R_AHB1ENR_GPIOEEN_MASK | \
                            R_AHB1ENR_GPIODEN_MASK | \
                            R_AHB1ENR_GPIOCEN_MASK | \
                            R_AHB1ENR_GPIOBEN_MASK | \
                            R_AHB1ENR_GPIOAEN_MASK)

#define AHB2ENR_RO_MASK    (0)
#define AHB2ENR_WO_MASK    (0)
#define AHB2ENR_RW_MASK    (R_AHB2ENR_OTGFSEN_MASK | \
                            R_AHB2ENR_RNGEN_MASK | \
                            R_AHB2ENR_HASHEN_MASK | \
                            R_AHB2ENR_CRYPEN_MASK | \
                            R_AHB2ENR_DCMIEN_MASK)

#define AHB3ENR_RO_MASK    (0)
#define AHB3ENR_WO_MASK    (0)
#define AHB3ENR_RW_MASK    (R_AHB3ENR_FSMCEN_MASK)

#define APB1ENR_RO_MASK    (0)
#define APB1ENR_WO_MASK    (0)
#define APB1ENR_RW_MASK    (R_APB1ENR_DACEN_MASK | \
                            R_APB1ENR_PWREN_MASK | \
                            R_APB1ENR_CAN2EN_MASK | \
                            R_APB1ENR_CAN1EN_MASK | \
                            R_APB1ENR_I2C3EN_MASK | \
                            R_APB1ENR_I2C2EN_MASK | \
                            R_APB1ENR_I2C1EN_MASK | \
                            R_APB1ENR_UART5EN_MASK | \
                            R_APB1ENR_UART4EN_MASK | \
                            R_APB1ENR_USART3EN_MASK | \
                            R_APB1ENR_USART2EN_MASK | \
                            R_APB1ENR_SPI3EN_MASK | \
                            R_APB1ENR_SPI2EN_MASK | \
                            R_APB1ENR_WWDGEN_MASK | \
                            R_APB1ENR_TIM14EN_MASK | \
                            R_APB1ENR_TIM13EN_MASK | \
                            R_APB1ENR_TIM12EN_MASK | \
                            R_APB1ENR_TIM7EN_MASK | \
                            R_APB1ENR_TIM6EN_MASK | \
                            R_APB1ENR_TIM5EN_MASK | \
                            R_APB1ENR_TIM4EN_MASK | \
                            R_APB1ENR_TIM3EN_MASK | \
                            R_APB1ENR_TIM2EN_MASK)

#define APB2ENR_RO_MASK    (0)
#define APB2ENR_WO_MASK    (0)
#define APB2ENR_RW_MASK    (R_APB2ENR_TIM11EN_MASK | \
                            R_APB2ENR_TIM10EN_MASK | \
                            R_APB2ENR_TIM9EN_MASK | \
                            R_APB2ENR_SYSCFGEN_MASK | \
                            R_APB2ENR_SPI1EN_MASK | \
                            R_APB2ENR_SDIOEN_MASK | \
                            R_APB2ENR_ADC3EN_MASK | \
                            R_APB2ENR_ADC2EN_MASK | \
                            R_APB2ENR_ADC1EN_MASK | \
                            R_APB2ENR_USART6EN_MASK | \
                            R_APB2ENR_USART1EN_MASK | \
                            R_APB2ENR_TIM8EN_MASK | \
                            R_APB2ENR_TIM1EN_MASK)

#define AHB1LPENR_RO_MASK  (0)
#define AHB1LPENR_WO_MASK  (0)
#define AHB1LPENR_RW_MASK  (R_AHB1LPENR_OTGHSULPILPEN_MASK | \
                            R_AHB1LPENR_OTGHSLPEN_MASK | \
                            R_AHB1LPENR_ETHMACPTPLPEN_MASK | \
                            R_AHB1LPENR_ETHMACRXLPEN_MASK | \
                            R_AHB1LPENR_ETHMACTXLPEN_MASK | \
                            R_AHB1LPENR_ETHMACLPEN_MASK | \
                            R_AHB1LPENR_DMA2LPEN_MASK | \
                            R_AHB1LPENR_DMA1LPEN_MASK | \
                            R_AHB1LPENR_BKPSRAMLPEN_MASK | \
                            R_AHB1LPENR_SRAM2LPEN_MASK | \
                            R_AHB1LPENR_SRAM1LPEN_MASK | \
                            R_AHB1LPENR_FLITFLPEN_MASK | \
                            R_AHB1LPENR_CRCLPEN_MASK | \
                            R_AHB1LPENR_GPIOILPEN_MASK | \
                            R_AHB1LPENR_GPIOHLPEN_MASK | \
                            R_AHB1LPENR_GPIOGLPEN_MASK | \
                            R_AHB1LPENR_GPIOFLPEN_MASK | \
                            R_AHB1LPENR_GPIOELPEN_MASK | \
                            R_AHB1LPENR_GPIODLPEN_MASK | \
                            R_AHB1LPENR_GPIOCLPEN_MASK | \
                            R_AHB1LPENR_GPIOBLPEN_MASK | \
                            R_AHB1LPENR_GPIOALPEN_MASK)

#define AHB2LPENR_RO_MASK  (0)
#define AHB2LPENR_WO_MASK  (0)
#define AHB2LPENR_RW_MASK  (R_AHB2LPENR_OTGFSLPEN_MASK | \
                            R_AHB2LPENR_RNGLPEN_MASK | \
                            R_AHB2LPENR_HASHLPEN_MASK | \
                            R_AHB2LPENR_CRYPLPEN_MASK | \
                            R_AHB2LPENR_DCMILPEN_MASK)

#define AHB3LPENR_RO_MASK  (0)
#define AHB3LPENR_WO_MASK  (0)
#define AHB3LPENR_RW_MASK  (R_AHB3LPENR_FSMCLPEN_MASK)

#define APB1LPENR_RO_MASK  (0)
#define APB1LPENR_WO_MASK  (0)
#define APB1LPENR_RW_MASK  (R_APB1LPENR_DACLPEN_MASK | \
                            R_APB1LPENR_PWRLPEN_MASK | \
                            R_APB1LPENR_CAN2LPEN_MASK | \
                            R_APB1LPENR_CAN1LPEN_MASK | \
                            R_APB1LPENR_I2C3LPEN_MASK | \
                            R_APB1LPENR_I2C2LPEN_MASK | \
                            R_APB1LPENR_I2C1LPEN_MASK | \
                            R_APB1LPENR_UART5LPEN_MASK | \
                            R_APB1LPENR_UART4LPEN_MASK | \
                            R_APB1LPENR_USART3LPEN_MASK | \
                            R_APB1LPENR_USART2LPEN_MASK | \
                            R_APB1LPENR_SPI3LPEN_MASK | \
                            R_APB1LPENR_SPI2LPEN_MASK | \
                            R_APB1LPENR_WWDGLPEN_MASK | \
                            R_APB1LPENR_TIM14LPEN_MASK | \
                            R_APB1LPENR_TIM13LPEN_MASK | \
                            R_APB1LPENR_TIM12LPEN_MASK | \
                            R_APB1LPENR_TIM7LPEN_MASK | \
                            R_APB1LPENR_TIM6LPEN_MASK | \
                            R_APB1LPENR_TIM5LPEN_MASK | \
                            R_APB1LPENR_TIM4LPEN_MASK | \
                            R_APB1LPENR_TIM3LPEN_MASK | \
                            R_APB1LPENR_TIM2LPEN_MASK)

#define APB2LPENR_RO_MASK  (0)
#define APB2LPENR_WO_MASK  (0)
#define APB2LPENR_RW_MASK  (R_APB2LPENR_TIM11LPEN_MASK | \
                            R_APB2LPENR_TIM10LPEN_MASK | \
                            R_APB2LPENR_TIM9LPEN_MASK | \
                            R_APB2LPENR_SYSCFGLPEN_MASK | \
                            R_APB2LPENR_SPI1LPEN_MASK | \
                            R_APB2LPENR_SDIOLPEN_MASK | \
                            R_APB2LPENR_ADC3LPEN_MASK | \
                            R_APB2LPENR_ADC2LPEN_MASK | \
                            R_APB2LPENR_ADC1LPEN_MASK | \
                            R_APB2LPENR_USART6LPEN_MASK | \
                            R_APB2LPENR_USART1LPEN_MASK | \
                            R_APB2LPENR_TIM8LPEN_MASK | \
                            R_APB2LPENR_TIM1LPEN_MASK)

#define BDCR_RO_MASK       (R_BDCR_LSERDY_MASK)
#define BDCR_WO_MASK       (0)
#define BDCR_RW_MASK       (R_BDCR_BDRST_MASK | \
                            R_BDCR_RTCEN_MASK | \
                            R_BDCR_RTCSEL_MASK | \
                            R_BDCR_LSEBYP_MASK | \
                            R_BDCR_LSEON_MASK)

#define CSR_RO_MASK        (R_CSR_LPWRRSTF_MASK | \
                            R_CSR_WWDGRSTF_MASK | \
                            R_CSR_IWDGRSTF_MASK | \
                            R_CSR_SFTRSTF_MASK | \
                            R_CSR_PORRSTF_MASK | \
                            R_CSR_PINRSTF_MASK | \
                            R_CSR_BORRSTF_MASK | \
                            R_CSR_LSIRDY_MASK)
#define CSR_WO_MASK        (0)
#define CSR_RW_MASK        (R_CSR_RMVF_MASK | \
                            R_CSR_LSION_MASK)

#define SSCGR_RO_MASK      (0)
#define SSCGR_WO_MASK      (0)
#define SSCGR_RW_MASK      (R_SSCGR_SSCGEN_MASK | \
                            R_SSCGR_SPREADSEL_MASK | \
                            R_SSCGR_INCSTEP_MASK | \
                            R_SSCGR_MODPER_MASK)

#define PLLI2SCFGR_RO_MASK (0)
#define PLLI2SCFGR_WO_MASK (0)
#define PLLI2SCFGR_RW_MASK (R_PLLI2SCFGR_PLLI2SR_MASK | \
                            R_PLLI2SCFGR_PLLI2SN_MASK)

/* Pll Channels */
enum PllChannels {
    RCC_PLL_CHANNEL_PLLCLK = 0,
    RCC_PLL_CHANNEL_PLL48MCLK = 1,
};

/* PllI2S Channels */
enum PllI2SChannels {
    RCC_PLLSAI1_CHANNEL_PLLI2SCLK = 0,
};

typedef enum RccClockMuxSource {
    RCC_CLOCK_MUX_SRC_GND = 0,
    RCC_CLOCK_MUX_SRC_HSI,
    RCC_CLOCK_MUX_SRC_HSE,
    RCC_CLOCK_MUX_SRC_LSI,
    RCC_CLOCK_MUX_SRC_LSE,
    RCC_CLOCK_MUX_SRC_PLL,
    RCC_CLOCK_MUX_SRC_PLLI2SCLK,
    RCC_CLOCK_MUX_SRC_EXTCLK,
    RCC_CLOCK_MUX_SRC_SYSCLK,
    RCC_CLOCK_MUX_SRC_HCLK,
    RCC_CLOCK_MUX_SRC_PCLK1,
    RCC_CLOCK_MUX_SRC_PCLK2,
    RCC_CLOCK_MUX_SRC_HSE_RTC,
    RCC_CLOCK_MUX_SRC_RTC_COMMON,

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
            "pllclk",
            "pll48mclk",
            "null"
        },
        .channel_exists = {
            true, true, false
        },
        /* From PLLCFGR register documentation */
        .default_channel_divider = {
            2, 4, 0
        }
    },
    [RCC_PLL_PLLI2S] = {
        .name = "plli2s",
        .channel_name = {
            "plli2sclk",
            "null",
            "null"
        },
        .channel_exists = {
            false, false, true
        },
        .default_channel_divider = {
            0, 0, 2
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
    [RCC_CLOCK_MUX_HSE_RTC] = {
        .name = "hse-rtc",
        .multiplier = 1,
        .divider = 2,
        .enabled = true,
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HSE,
        },
        .hidden = true,
    },
    [RCC_CLOCK_MUX_RTC_COMMON] = {
        .name = "rtc-common",
        /* Same mapping as: BDCR_RTCSEL */
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_GND,
            RCC_CLOCK_MUX_SRC_LSE,
            RCC_CLOCK_MUX_SRC_LSI,
            RCC_CLOCK_MUX_SRC_HSE_RTC,
        },
        .hidden = true,
        FILL_DEFAULT_INIT_ENABLED,
    },
    [RCC_CLOCK_MUX_CORTEX_SYSTEM_TIMER] = {
        .name = "cortex-system-timer",
        .multiplier = 1,
        /* TIMER is always HCLK/8 */
        .divider = 8,
        .enabled = true,
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        }
    },
    [RCC_CLOCK_MUX_MCO1] = {
        .name = "mco1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_LSE,
            RCC_CLOCK_MUX_SRC_HSE,
            RCC_CLOCK_MUX_SRC_HSI,
            RCC_CLOCK_MUX_SRC_PLL,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_MCO2] = {
        .name = "mco2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_SYSCLK,
            RCC_CLOCK_MUX_SRC_PLLI2SCLK,
            RCC_CLOCK_MUX_SRC_HSE,
            RCC_CLOCK_MUX_SRC_PLL,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_I2S] = {
        .name = "i2s",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PLLI2SCLK,
            RCC_CLOCK_MUX_SRC_EXTCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    /* From now on, these muxes only have one valid source */
    /* - AHB1 */
    [RCC_CLOCK_MUX_OTGHSULPI] = {
        .name = "otghsulpi",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_OTGHS] = {
        .name = "otghs",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ETHMACPTP] = {
        .name = "ethmacptp",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ETHMACRX] = {
        .name = "ethmacrx",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ETHMACTX] = {
        .name = "ethmactx",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ETHMAC] = {
        .name = "ethmac",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DMA2] = {
        .name = "dma2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DMA1] = {
        .name = "dma1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CCMDATARAM] = {
        .name = "ccmdataram",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_BKPSRAM] = {
        .name = "bkpsram",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CRC] = {
        .name = "crc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOI] = {
        .name = "gpioi",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOH] = {
        .name = "gpioh",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOG] = {
        .name = "gpiog",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOF] = {
        .name = "gpiof",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOE] = {
        .name = "gpioe",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOD] = {
        .name = "gpiod",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOC] = {
        .name = "gpioc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOB] = {
        .name = "gpiob",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_GPIOA] = {
        .name = "gpioa",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    /* - AHB2 */
    [RCC_CLOCK_MUX_OTGFS] = {
        .name = "otgfs",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_RNG] = {
        .name = "rng",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_HASH] = {
        .name = "hash",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CRYP] = {
        .name = "cryp",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_DCMI] = {
        .name = "dcmi",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    /* - AHB3 */
    [RCC_CLOCK_MUX_FSMC] = {
        .name = "fsmc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_HCLK,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    /* From now on, these muxes only have one valid source */
    /* - APB1 */
    [RCC_CLOCK_MUX_DAC] = {
        .name = "dac",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_PWR] = {
        .name = "pwr",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_CAN2] = {
        .name = "can2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
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
    [RCC_CLOCK_MUX_I2C3] = {
        .name = "i2c3",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_I2C2] = {
        .name = "i2c2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_I2C1] = {
        .name = "i2c1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_UART5] = {
        .name = "uart5",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_UART4] = {
        .name = "uart4",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_USART3] = {
        .name = "usart3",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_USART2] = {
        .name = "usart2",
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
    [RCC_CLOCK_MUX_TIM14] = {
        .name = "tim14",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM13] = {
        .name = "tim13",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM12] = {
        .name = "tim12",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK1,
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
    /* - APB2 */
    [RCC_CLOCK_MUX_TIM11] = {
        .name = "tim11",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM10] = {
        .name = "tim10",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_TIM9] = {
        .name = "tim9",
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
    [RCC_CLOCK_MUX_SPI1] = {
        .name = "spi1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SDIO] = {
        .name = "sdio",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ADC3] = {
        .name = "adc3",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ADC2] = {
        .name = "adc2",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_ADC1] = {
        .name = "adc1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_USART6] = {
        .name = "usart6",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_USART1] = {
        .name = "usart1",
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
    [RCC_CLOCK_MUX_TIM1] = {
        .name = "tim1",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PCLK2,
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_RTC] = {
        .name = "rtc",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_RTC_COMMON
        },
        FILL_DEFAULT_INIT_DISABLED,
    },
    [RCC_CLOCK_MUX_SSCG] = {
        .name = "sscg",
        .src_mapping = {
            RCC_CLOCK_MUX_SRC_PLL,
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
