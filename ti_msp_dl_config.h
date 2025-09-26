/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for ZCLK1 */
#define ZCLK1_INST                                                         TIMA1
#define ZCLK1_INST_IRQHandler                                   TIMA1_IRQHandler
#define ZCLK1_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define ZCLK1_INST_CLK_FREQ                                             10000000
/* GPIO defines for channel 0 */
#define GPIO_ZCLK1_C0_PORT                                                 GPIOA
#define GPIO_ZCLK1_C0_PIN                                         DL_GPIO_PIN_15
#define GPIO_ZCLK1_C0_IOMUX                                      (IOMUX_PINCM37)
#define GPIO_ZCLK1_C0_IOMUX_FUNC                     IOMUX_PINCM37_PF_TIMA1_CCP0
#define GPIO_ZCLK1_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 0 */
#define GPIO_ZCLK1_C0_CMPL_PORT                                            GPIOA
#define GPIO_ZCLK1_C0_CMPL_PIN                                     DL_GPIO_PIN_8
#define GPIO_ZCLK1_C0_CMPL_IOMUX                                 (IOMUX_PINCM19)
#define GPIO_ZCLK1_C0_CMPL_IOMUX_FUNC           IOMUX_PINCM19_PF_TIMA1_CCP0_CMPL


/* Defines for ZCLK2 */
#define ZCLK2_INST                                                         TIMA0
#define ZCLK2_INST_IRQHandler                                   TIMA0_IRQHandler
#define ZCLK2_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define ZCLK2_INST_CLK_FREQ                                             10000000
/* GPIO defines for channel 0 */
#define GPIO_ZCLK2_C0_PORT                                                 GPIOA
#define GPIO_ZCLK2_C0_PIN                                          DL_GPIO_PIN_0
#define GPIO_ZCLK2_C0_IOMUX                                       (IOMUX_PINCM1)
#define GPIO_ZCLK2_C0_IOMUX_FUNC                      IOMUX_PINCM1_PF_TIMA0_CCP0
#define GPIO_ZCLK2_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 0 */
#define GPIO_ZCLK2_C0_CMPL_PORT                                            GPIOA
#define GPIO_ZCLK2_C0_CMPL_PIN                                    DL_GPIO_PIN_22
#define GPIO_ZCLK2_C0_CMPL_IOMUX                                 (IOMUX_PINCM47)
#define GPIO_ZCLK2_C0_CMPL_IOMUX_FUNC           IOMUX_PINCM47_PF_TIMA0_CCP0_CMPL




/* Defines for scl1_time */
#define scl1_time_INST                                                   (TIMG0)
#define scl1_time_INST_IRQHandler                               TIMG0_IRQHandler
#define scl1_time_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define scl1_time_INST_LOAD_VALUE                                         (999U)
/* Defines for scl1_com_idle */
#define scl1_com_idle_INST                                               (TIMG6)
#define scl1_com_idle_INST_IRQHandler                           TIMG6_IRQHandler
#define scl1_com_idle_INST_INT_IRQN                             (TIMG6_INT_IRQn)
#define scl1_com_idle_INST_LOAD_VALUE                                     (399U)
/* Defines for scl2_com_idle */
#define scl2_com_idle_INST                                               (TIMG7)
#define scl2_com_idle_INST_IRQHandler                           TIMG7_IRQHandler
#define scl2_com_idle_INST_INT_IRQN                             (TIMG7_INT_IRQn)
#define scl2_com_idle_INST_LOAD_VALUE                                    (1999U)



/* Defines for ZSCL1 */
#define ZSCL1_INST                                                         UART3
#define ZSCL1_INST_IRQHandler                                   UART3_IRQHandler
#define ZSCL1_INST_INT_IRQN                                       UART3_INT_IRQn
#define GPIO_ZSCL1_RX_PORT                                                 GPIOA
#define GPIO_ZSCL1_TX_PORT                                                 GPIOA
#define GPIO_ZSCL1_RX_PIN                                         DL_GPIO_PIN_13
#define GPIO_ZSCL1_TX_PIN                                         DL_GPIO_PIN_14
#define GPIO_ZSCL1_IOMUX_RX                                      (IOMUX_PINCM35)
#define GPIO_ZSCL1_IOMUX_TX                                      (IOMUX_PINCM36)
#define GPIO_ZSCL1_IOMUX_RX_FUNC                       IOMUX_PINCM35_PF_UART3_RX
#define GPIO_ZSCL1_IOMUX_TX_FUNC                       IOMUX_PINCM36_PF_UART3_TX
#define ZSCL1_BAUD_RATE                                                 (125000)
#define ZSCL1_IBRD_80_MHZ_125000_BAUD                                       (40)
#define ZSCL1_FBRD_80_MHZ_125000_BAUD                                        (0)
/* Defines for ZSCL2 */
#define ZSCL2_INST                                                         UART1
#define ZSCL2_INST_IRQHandler                                   UART1_IRQHandler
#define ZSCL2_INST_INT_IRQN                                       UART1_INT_IRQn
#define GPIO_ZSCL2_RX_PORT                                                 GPIOB
#define GPIO_ZSCL2_TX_PORT                                                 GPIOB
#define GPIO_ZSCL2_RX_PIN                                          DL_GPIO_PIN_7
#define GPIO_ZSCL2_TX_PIN                                          DL_GPIO_PIN_6
#define GPIO_ZSCL2_IOMUX_RX                                      (IOMUX_PINCM24)
#define GPIO_ZSCL2_IOMUX_TX                                      (IOMUX_PINCM23)
#define GPIO_ZSCL2_IOMUX_RX_FUNC                       IOMUX_PINCM24_PF_UART1_RX
#define GPIO_ZSCL2_IOMUX_TX_FUNC                       IOMUX_PINCM23_PF_UART1_TX


#define ZSCL2_BAUD_RATE                                                 (125000)
#define ZSCL2_IBRD_40_MHZ_125000_BAUD                                       (20)
#define ZSCL2_FBRD_40_MHZ_125000_BAUD                                        (0)


/*#define ZSCL2_BAUD_RATE                                                 (115200)
#define ZSCL2_IBRD_40_MHZ_125000_BAUD                                       (21)
#define ZSCL2_FBRD_40_MHZ_125000_BAUD                                       (45)*/

/* Defines for ZSCL3 */
#define ZSCL3_INST                                                         UART0
#define ZSCL3_INST_IRQHandler                                   UART0_IRQHandler
#define ZSCL3_INST_INT_IRQN                                       UART0_INT_IRQn
#define GPIO_ZSCL3_RX_PORT                                                 GPIOA
#define GPIO_ZSCL3_TX_PORT                                                 GPIOA
#define GPIO_ZSCL3_RX_PIN                                         DL_GPIO_PIN_31
#define GPIO_ZSCL3_TX_PIN                                         DL_GPIO_PIN_28
#define GPIO_ZSCL3_IOMUX_RX                                       (IOMUX_PINCM6)
#define GPIO_ZSCL3_IOMUX_TX                                       (IOMUX_PINCM3)
#define GPIO_ZSCL3_IOMUX_RX_FUNC                        IOMUX_PINCM6_PF_UART0_RX
#define GPIO_ZSCL3_IOMUX_TX_FUNC                        IOMUX_PINCM3_PF_UART0_TX
#define ZSCL3_BAUD_RATE                                                 (125000)
#define ZSCL3_IBRD_40_MHZ_125000_BAUD                                       (20)
#define ZSCL3_FBRD_40_MHZ_125000_BAUD                                        (0)


/* Defines for DMA_SCL1_TX */
#define DMA_SCL1_TX_CHAN_ID                                                  (0)
#define ZSCL1_INST_DMA_TRIGGER                               (DMA_UART3_TX_TRIG)

/* Defines for DMA_SCL2_TX */
#define DMA_SCL2_TX_CHAN_ID                                                  (1)
#define ZSCL2_INST_DMA_TRIGGER                               (DMA_UART1_TX_TRIG)

/* Defines for DMA_SCL3_TX */
#define DMA_SCL3_TX_CHAN_ID                                                  (2)
#define ZSCL3_INST_DMA_TRIGGER                               (DMA_UART0_TX_TRIG)


/* Port definition for Pin Group ZCRESET1 */
#define ZCRESET1_PORT                                                    (GPIOB)

/* Defines for PIN_0: GPIOB.15 with pinCMx 32 on package pin 3 */
#define ZCRESET1_PIN_0_PIN                                      (DL_GPIO_PIN_15)
#define ZCRESET1_PIN_0_IOMUX                                     (IOMUX_PINCM32)
/* Port definition for Pin Group ZTXEN1 */
#define ZTXEN1_PORT                                                      (GPIOB)

/* Defines for PIN_1: GPIOB.16 with pinCMx 33 on package pin 4 */
#define ZTXEN1_PIN_1_PIN                                        (DL_GPIO_PIN_16)
#define ZTXEN1_PIN_1_IOMUX                                       (IOMUX_PINCM33)
/* Port definition for Pin Group ZCRESET2 */
#define ZCRESET2_PORT                                                    (GPIOB)

/* Defines for PIN_2: GPIOB.4 with pinCMx 17 on package pin 52 */
#define ZCRESET2_PIN_2_PIN                                       (DL_GPIO_PIN_4)
#define ZCRESET2_PIN_2_IOMUX                                     (IOMUX_PINCM17)
/* Port definition for Pin Group ZTXEN2 */
#define ZTXEN2_PORT                                                      (GPIOB)

/* Defines for PIN_3: GPIOB.5 with pinCMx 18 on package pin 53 */
#define ZTXEN2_PIN_3_PIN                                         (DL_GPIO_PIN_5)
#define ZTXEN2_PIN_3_IOMUX                                       (IOMUX_PINCM18)
/* Port definition for Pin Group ROUT_Y0 */
#define ROUT_Y0_PORT                                                     (GPIOB)

/* Defines for PIN_20: GPIOB.20 with pinCMx 48 on package pin 19 */
#define ROUT_Y0_PIN_20_PIN                                      (DL_GPIO_PIN_20)
#define ROUT_Y0_PIN_20_IOMUX                                     (IOMUX_PINCM48)
/* Port definition for Pin Group ROUT_Y1 */
#define ROUT_Y1_PORT                                                     (GPIOB)

/* Defines for PIN_4: GPIOB.21 with pinCMx 49 on package pin 20 */
#define ROUT_Y1_PIN_4_PIN                                       (DL_GPIO_PIN_21)
#define ROUT_Y1_PIN_4_IOMUX                                      (IOMUX_PINCM49)
/* Port definition for Pin Group ROUT_Y2 */
#define ROUT_Y2_PORT                                                     (GPIOB)

/* Defines for PIN_5: GPIOB.22 with pinCMx 50 on package pin 21 */
#define ROUT_Y2_PIN_5_PIN                                       (DL_GPIO_PIN_22)
#define ROUT_Y2_PIN_5_IOMUX                                      (IOMUX_PINCM50)
/* Port definition for Pin Group ROUT_Y3 */
#define ROUT_Y3_PORT                                                     (GPIOB)

/* Defines for PIN_6: GPIOB.23 with pinCMx 51 on package pin 22 */
#define ROUT_Y3_PIN_6_PIN                                       (DL_GPIO_PIN_23)
#define ROUT_Y3_PIN_6_IOMUX                                      (IOMUX_PINCM51)
/* Port definition for Pin Group ROUT_Y6 */
#define ROUT_Y6_PORT                                                     (GPIOB)

/* Defines for PIN_7: GPIOB.26 with pinCMx 57 on package pin 28 */
#define ROUT_Y6_PIN_7_PIN                                       (DL_GPIO_PIN_26)
#define ROUT_Y6_PIN_7_IOMUX                                      (IOMUX_PINCM57)
/* Port definition for Pin Group ROUT_Y5 */
#define ROUT_Y5_PORT                                                     (GPIOB)

/* Defines for PIN_8: GPIOB.25 with pinCMx 56 on package pin 27 */
#define ROUT_Y5_PIN_8_PIN                                       (DL_GPIO_PIN_25)
#define ROUT_Y5_PIN_8_IOMUX                                      (IOMUX_PINCM56)
/* Port definition for Pin Group PWR_FSEN */
#define PWR_FSEN_PORT                                                    (GPIOA)

/* Defines for PIN_9: GPIOA.30 with pinCMx 5 on package pin 37 */
#define PWR_FSEN_PIN_9_PIN                                      (DL_GPIO_PIN_30)
#define PWR_FSEN_PIN_9_IOMUX                                      (IOMUX_PINCM5)
/* Port definition for Pin Group m485BTE */
#define m485BTE_PORT                                                     (GPIOB)

/* Defines for PIN_10: GPIOB.8 with pinCMx 25 on package pin 60 */
#define m485BTE_PIN_10_PIN                                       (DL_GPIO_PIN_8)
#define m485BTE_PIN_10_IOMUX                                     (IOMUX_PINCM25)
/* Port definition for Pin Group LED_485B */
#define LED_485B_PORT                                                    (GPIOB)

/* Defines for PIN_11: GPIOB.1 with pinCMx 13 on package pin 48 */
#define LED_485B_PIN_11_PIN                                      (DL_GPIO_PIN_1)
#define LED_485B_PIN_11_IOMUX                                    (IOMUX_PINCM13)
///* Port definition for Pin Group LED_MCU */
//#define LED_MCU_PORT                                                     (GPIOB)
//
/////* Defines for PIN_12: GPIOB.9 with pinCMx 26 on package pin 61 */
//#define LED_MCU_PIN_12_PIN                                       (DL_GPIO_PIN_9)
//#define LED_MCU_PIN_12_IOMUX                                     (IOMUX_PINCM26)
/* Port definition for Pin Group ROUT_Y4 */
#define ROUT_Y4_PORT                                                     (GPIOB)

/* Defines for PIN_13: GPIOB.24 with pinCMx 52 on package pin 23 */
#define ROUT_Y4_PIN_13_PIN                                      (DL_GPIO_PIN_24)
#define ROUT_Y4_PIN_13_IOMUX                                     (IOMUX_PINCM52)

/* Defines for PIN_7: GPIOB.9 with pinCMx 26 on package pin 61 */
#define IO_FUNC4_PIN_7_PIN                                       (DL_GPIO_PIN_9)
#define IO_FUNC4_PIN_7_IOMUX                                     (IOMUX_PINCM26)
/* Port definition for Pin Group ZTXEN3 */
#define ZTXEN3_PORT  
/* Defines for PIN_8: GPIOA.10 with pinCMx 21 on package pin 56 */
#define ZTXEN3_PIN_8_PIN                                        (DL_GPIO_PIN_10)
#define ZTXEN3_PIN_8_IOMUX                                       (IOMUX_PINCM21)
   
/* Port definition for Pin Group IX0 */
#define IX0_PORT                                                         (GPIOB)

/* Defines for PIN_9: GPIOB.10 with pinCMx 27 on package pin 62 */
#define IX0_PIN_9_PIN                                           (DL_GPIO_PIN_10)
#define IX0_PIN_9_IOMUX                                          (IOMUX_PINCM27)
/* Port definition for Pin Group IX1 */
#define IX1_PORT                                                         (GPIOB)

/* Defines for PIN_10: GPIOB.11 with pinCMx 28 on package pin 63 */
#define IX1_PIN_10_PIN                                          (DL_GPIO_PIN_11)
#define IX1_PIN_10_IOMUX                                         (IOMUX_PINCM28)
/* Port definition for Pin Group IX2 */
#define IX2_PORT                                                         (GPIOB)

/* Defines for PIN_11: GPIOB.12 with pinCMx 29 on package pin 64 */
#define IX2_PIN_11_PIN                                          (DL_GPIO_PIN_12)
#define IX2_PIN_11_IOMUX                                         (IOMUX_PINCM29)
/* Port definition for Pin Group IX3 */
#define IX3_PORT                                                         (GPIOB)

/* Defines for PIN_12: GPIOB.13 with pinCMx 30 on package pin 1 */
#define IX3_PIN_12_PIN                                          (DL_GPIO_PIN_13)
#define IX3_PIN_12_IOMUX                                         (IOMUX_PINCM30)
/* Port definition for Pin Group IX4 */
#define IX4_PORT                                                         (GPIOB)

/* Defines for PIN_13: GPIOB.14 with pinCMx 31 on package pin 2 */
#define IX4_PIN_13_PIN                                          (DL_GPIO_PIN_14)
#define IX4_PIN_13_IOMUX                                         (IOMUX_PINCM31)
/* Port definition for Pin Group IX5 */
#define IX5_PORT                                                         (GPIOB)

/* Defines for PIN_14: GPIOB.2 with pinCMx 15 on package pin 50 */
#define IX5_PIN_14_PIN                                           (DL_GPIO_PIN_2)
#define IX5_PIN_14_IOMUX                                         (IOMUX_PINCM15)
/* Port definition for Pin Group IX6 */
#define IX6_PORT                                                         (GPIOB)

/* Defines for PIN_15: GPIOB.3 with pinCMx 16 on package pin 51 */
#define IX6_PIN_15_PIN                                           (DL_GPIO_PIN_3)
#define IX6_PIN_15_IOMUX                                         (IOMUX_PINCM16)
/* Port definition for Pin Group IX7 */
#define IX7_PORT                                                         (GPIOB)

/* Defines for PIN_16: GPIOB.17 with pinCMx 43 on package pin 14 */
#define IX7_PIN_16_PIN                                          (DL_GPIO_PIN_17)
#define IX7_PIN_16_IOMUX                                         (IOMUX_PINCM43)   
   
/* Port definition for Pin Group IO_FUNC1 */
#define IO_FUNC1_PORT                                                    (GPIOA)

/* Defines for PIN_4: GPIOA.16 with pinCMx 38 on package pin 9 */
#define IO_FUNC1_PIN_4_PIN                                      (DL_GPIO_PIN_16)
#define IO_FUNC1_PIN_4_IOMUX                                     (IOMUX_PINCM38)
/* Port definition for Pin Group IO_FUNC2 */
#define IO_FUNC2_PORT                                                    (GPIOA)

/* Defines for PIN_5: GPIOA.17 with pinCMx 39 on package pin 10 */
#define IO_FUNC2_PIN_5_PIN                                      (DL_GPIO_PIN_17)
#define IO_FUNC2_PIN_5_IOMUX                                     (IOMUX_PINCM39)
/* Port definition for Pin Group IO_FUNC3 */
#define IO_FUNC3_PORT                                                    (GPIOA)

/* Defines for PIN_6: GPIOA.9 with pinCMx 20 on package pin 55 */
#define IO_FUNC3_PIN_6_PIN                                       (DL_GPIO_PIN_9)
#define IO_FUNC3_PIN_6_IOMUX                                     (IOMUX_PINCM20)
/* Port definition for Pin Group IO_FUNC4 */
#define IO_FUNC4_PORT                                                    (GPIOB)

/* Defines for PIN_7: GPIOB.9 with pinCMx 26 on package pin 61 */
#define IO_FUNC4_PIN_7_PIN                                       (DL_GPIO_PIN_9)
#define IO_FUNC4_PIN_7_IOMUX                                     (IOMUX_PINCM26)  
  
/* Port definition for Pin Group LED_STA */
#define LED_STA_PORT                                                     (GPIOA)
/* Defines for PIN_17: GPIOA.8 with pinCMx 19 on package pin 54 */
#define LED_STA_PIN_17_PIN                                       (DL_GPIO_PIN_8)
#define LED_STA_PIN_17_IOMUX                                     (IOMUX_PINCM19)  

/* Defines for WWDT */
#define WWDT0_INST                                                       (WWDT0)
#define WWDT0_INT_IRQN                                          (WWDT0_INT_IRQn)



/* Defines for MCAN0 */
#define MCAN0_INST                                                        CANFD0
#define GPIO_MCAN0_CAN_TX_PORT                                             GPIOA
#define GPIO_MCAN0_CAN_TX_PIN                                     DL_GPIO_PIN_26
#define GPIO_MCAN0_IOMUX_CAN_TX                                  (IOMUX_PINCM59)
#define GPIO_MCAN0_IOMUX_CAN_TX_FUNC               IOMUX_PINCM59_PF_CANFD0_CANTX
#define GPIO_MCAN0_CAN_RX_PORT                                             GPIOA
#define GPIO_MCAN0_CAN_RX_PIN                                     DL_GPIO_PIN_27
#define GPIO_MCAN0_IOMUX_CAN_RX                                  (IOMUX_PINCM60)
#define GPIO_MCAN0_IOMUX_CAN_RX_FUNC               IOMUX_PINCM60_PF_CANFD0_CANRX
#define MCAN0_INST_IRQHandler                                 CANFD0_IRQHandler
#define MCAN0_INST_INT_IRQN                                     CANFD0_INT_IRQn


/* Defines for MCAN0 MCAN RAM configuration */
#define MCAN0_INST_MCAN_STD_ID_FILT_START_ADDR     (0)
#define MCAN0_INST_MCAN_STD_ID_FILTER_NUM          (1)
#define MCAN0_INST_MCAN_EXT_ID_FILT_START_ADDR     (48)
#define MCAN0_INST_MCAN_EXT_ID_FILTER_NUM          (1)
#define MCAN0_INST_MCAN_TX_BUFF_START_ADDR         (148)
#define MCAN0_INST_MCAN_TX_BUFF_SIZE               (2)
#define MCAN0_INST_MCAN_FIFO_1_START_ADDR          (192)
#define MCAN0_INST_MCAN_FIFO_1_NUM                 (2)
#define MCAN0_INST_MCAN_TX_EVENT_START_ADDR        (164)
#define MCAN0_INST_MCAN_TX_EVENT_SIZE              (2)
#define MCAN0_INST_MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)
#define MCAN0_INST_MCAN_RX_BUFF_START_ADDR         (208)
#define MCAN0_INST_MCAN_FIFO_0_START_ADDR          (172)
#define MCAN0_INST_MCAN_FIFO_0_NUM                 (3)

#define MCAN0_INST_MCAN_INTERRUPTS (DL_MCAN_INTERRUPT_DRX | \
						DL_MCAN_INTERRUPT_RF0F | \
						DL_MCAN_INTERRUPT_RF0L | \
						DL_MCAN_INTERRUPT_RF0N | \
						DL_MCAN_INTERRUPT_RF0W | \
						DL_MCAN_INTERRUPT_RF1F | \
						DL_MCAN_INTERRUPT_RF1L | \
						DL_MCAN_INTERRUPT_RF1N | \
						DL_MCAN_INTERRUPT_RF1W)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_ZCLK1_init(void);
void SYSCFG_DL_ZCLK2_init(void);
void SYSCFG_DL_scl1_time_init(void);
void SYSCFG_DL_scl1_com_idle_init(void);
void SYSCFG_DL_scl2_com_idle_init(void);
void SYSCFG_DL_ZSCL1_init(void);
void SYSCFG_DL_ZSCL2_init(void);
void SYSCFG_DL_ZSCL3_init(void);
void SYSCFG_DL_DMA_init(void);

void SYSCFG_DL_WWDT0_init(void);
void SYSCFG_DL_MCAN0_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
