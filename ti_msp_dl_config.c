/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gZCLK1Backup;
DL_TimerA_backupConfig gZCLK2Backup;
DL_TimerG_backupConfig gscl1_com_idleBackup;
DL_TimerG_backupConfig gscl2_com_idleBackup;
DL_UART_Main_backupConfig gZSCL1Backup;
DL_MCAN_backupConfig gMCAN0Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_ZCLK1_init();
    SYSCFG_DL_ZCLK2_init();
    SYSCFG_DL_scl1_time_init();
    SYSCFG_DL_scl1_com_idle_init();
    SYSCFG_DL_scl2_com_idle_init();
    SYSCFG_DL_ZSCL1_init();
    SYSCFG_DL_ZSCL2_init();
    SYSCFG_DL_ZSCL3_init();
    SYSCFG_DL_DMA_init();
    SYSCFG_DL_WWDT0_init();
    SYSCFG_DL_MCAN0_init();
    /* Ensure backup structures have no valid state */
	gZCLK1Backup.backupRdy 	= false;
	gZCLK2Backup.backupRdy 	= false;
	gscl1_com_idleBackup.backupRdy 	= false;
	gscl2_com_idleBackup.backupRdy 	= false;
	gZSCL1Backup.backupRdy 	= false;
	gMCAN0Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(ZCLK1_INST, &gZCLK1Backup);
	retStatus &= DL_TimerA_saveConfiguration(ZCLK2_INST, &gZCLK2Backup);
	retStatus &= DL_TimerG_saveConfiguration(scl1_com_idle_INST, &gscl1_com_idleBackup);
	retStatus &= DL_TimerG_saveConfiguration(scl2_com_idle_INST, &gscl2_com_idleBackup);
	retStatus &= DL_UART_Main_saveConfiguration(ZSCL1_INST, &gZSCL1Backup);
	retStatus &= DL_MCAN_saveConfiguration(MCAN0_INST, &gMCAN0Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(ZCLK1_INST, &gZCLK1Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(ZCLK2_INST, &gZCLK2Backup, false);
	retStatus &= DL_TimerG_restoreConfiguration(scl1_com_idle_INST, &gscl1_com_idleBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(scl2_com_idle_INST, &gscl2_com_idleBackup, false);
	retStatus &= DL_UART_Main_restoreConfiguration(ZSCL1_INST, &gZSCL1Backup);
	retStatus &= DL_MCAN_restoreConfiguration(MCAN0_INST, &gMCAN0Backup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(ZCLK1_INST);
    DL_TimerA_reset(ZCLK2_INST);
    DL_TimerG_reset(scl1_time_INST);
    DL_TimerG_reset(scl1_com_idle_INST);
    DL_TimerG_reset(scl2_com_idle_INST);
    DL_UART_Main_reset(ZSCL1_INST);
    DL_UART_Main_reset(ZSCL2_INST);
    DL_UART_Main_reset(ZSCL3_INST);

    DL_WWDT_reset(WWDT0_INST);
    DL_MCAN_reset(MCAN0_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(ZCLK1_INST);
    DL_TimerA_enablePower(ZCLK2_INST);
    DL_TimerG_enablePower(scl1_time_INST);
    DL_TimerG_enablePower(scl1_com_idle_INST);
    DL_TimerG_enablePower(scl2_com_idle_INST);
    DL_UART_Main_enablePower(ZSCL1_INST);
    DL_UART_Main_enablePower(ZSCL2_INST);
    DL_UART_Main_enablePower(ZSCL3_INST);

    DL_WWDT_enablePower(WWDT0_INST);
    DL_MCAN_enablePower(MCAN0_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

    DL_GPIO_initPeripheralOutputFunction(GPIO_ZCLK1_C0_IOMUX,GPIO_ZCLK1_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_ZCLK1_C0_PORT, GPIO_ZCLK1_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_ZCLK1_C0_CMPL_IOMUX,GPIO_ZCLK1_C0_CMPL_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_ZCLK1_C0_CMPL_PORT, GPIO_ZCLK1_C0_CMPL_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_ZCLK2_C0_IOMUX,GPIO_ZCLK2_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_ZCLK2_C0_PORT, GPIO_ZCLK2_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_ZCLK2_C0_CMPL_IOMUX,GPIO_ZCLK2_C0_CMPL_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_ZCLK2_C0_CMPL_PORT, GPIO_ZCLK2_C0_CMPL_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ZSCL1_IOMUX_TX, GPIO_ZSCL1_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_ZSCL1_IOMUX_RX, GPIO_ZSCL1_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ZSCL2_IOMUX_TX, GPIO_ZSCL2_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_ZSCL2_IOMUX_RX, GPIO_ZSCL2_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ZSCL3_IOMUX_TX, GPIO_ZSCL3_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_ZSCL3_IOMUX_RX, GPIO_ZSCL3_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(ZCRESET1_PIN_0_IOMUX);

    DL_GPIO_initDigitalOutput(ZTXEN1_PIN_1_IOMUX);

    DL_GPIO_initDigitalOutput(ZCRESET2_PIN_2_IOMUX);

    DL_GPIO_initDigitalOutput(ZTXEN2_PIN_3_IOMUX);

    DL_GPIO_initDigitalOutput(ROUT_Y0_PIN_20_IOMUX);

    DL_GPIO_initDigitalOutput(ROUT_Y1_PIN_4_IOMUX);

    DL_GPIO_initDigitalOutput(ROUT_Y2_PIN_5_IOMUX);

    DL_GPIO_initDigitalOutput(ROUT_Y3_PIN_6_IOMUX);

    DL_GPIO_initDigitalOutput(ROUT_Y6_PIN_7_IOMUX);

    DL_GPIO_initDigitalOutput(ROUT_Y5_PIN_8_IOMUX);

    DL_GPIO_initDigitalOutput(PWR_FSEN_PIN_9_IOMUX);

    DL_GPIO_initDigitalOutput(m485BTE_PIN_10_IOMUX);

    DL_GPIO_initDigitalOutput(LED_485B_PIN_11_IOMUX);


    DL_GPIO_initDigitalOutput(ROUT_Y4_PIN_13_IOMUX);
    
    DL_GPIO_initDigitalOutput(ZTXEN3_PIN_8_IOMUX);
    
    DL_GPIO_clearPins(GPIOA, ZTXEN3_PIN_8_PIN);
    DL_GPIO_enableOutput(GPIOA, ZTXEN3_PIN_8_PIN);   
    
     DL_GPIO_initDigitalInput(IX0_PIN_9_IOMUX);

    DL_GPIO_initDigitalInput(IX1_PIN_10_IOMUX);

    DL_GPIO_initDigitalInput(IX2_PIN_11_IOMUX);

    DL_GPIO_initDigitalInput(IX3_PIN_12_IOMUX);

    DL_GPIO_initDigitalInput(IX4_PIN_13_IOMUX);

    DL_GPIO_initDigitalInput(IX5_PIN_14_IOMUX);

    DL_GPIO_initDigitalInput(IX6_PIN_15_IOMUX);   
    
    DL_GPIO_initDigitalInput(IX7_PIN_16_IOMUX);
    
    DL_GPIO_initDigitalInput(IO_FUNC1_PIN_4_IOMUX);

    DL_GPIO_initDigitalInput(IO_FUNC2_PIN_5_IOMUX);

    DL_GPIO_initDigitalInput(IO_FUNC3_PIN_6_IOMUX);

    DL_GPIO_initDigitalInput(IO_FUNC4_PIN_7_IOMUX);  

    DL_GPIO_initDigitalOutput(LED_STA_PIN_17_IOMUX);

    DL_GPIO_clearPins(GPIOA, ZTXEN3_PIN_8_PIN |
		LED_STA_PIN_17_PIN);
    DL_GPIO_enableOutput(GPIOA, ZTXEN3_PIN_8_PIN |
		LED_STA_PIN_17_PIN);    
        

    DL_GPIO_clearPins(PWR_FSEN_PORT, PWR_FSEN_PIN_9_PIN);
    DL_GPIO_enableOutput(PWR_FSEN_PORT, PWR_FSEN_PIN_9_PIN);
    DL_GPIO_clearPins(GPIOB, ROUT_Y3_PIN_6_PIN |
		ROUT_Y6_PIN_7_PIN |
		ROUT_Y5_PIN_8_PIN |
		m485BTE_PIN_10_PIN |
		LED_485B_PIN_11_PIN |
		ROUT_Y4_PIN_13_PIN);
    DL_GPIO_setPins(GPIOB, ZCRESET1_PIN_0_PIN |
		ZTXEN1_PIN_1_PIN |
		ZCRESET2_PIN_2_PIN |
		ZTXEN2_PIN_3_PIN |
		ROUT_Y0_PIN_20_PIN |
		ROUT_Y1_PIN_4_PIN |
		ROUT_Y2_PIN_5_PIN);
    DL_GPIO_enableOutput(GPIOB, ZCRESET1_PIN_0_PIN |
		ZTXEN1_PIN_1_PIN |
		ZCRESET2_PIN_2_PIN |
		ZTXEN2_PIN_3_PIN |
		ROUT_Y0_PIN_20_PIN |
		ROUT_Y1_PIN_4_PIN |
		ROUT_Y2_PIN_5_PIN |
		ROUT_Y3_PIN_6_PIN |
		ROUT_Y6_PIN_7_PIN |
		ROUT_Y5_PIN_8_PIN |
		m485BTE_PIN_10_PIN |
		LED_485B_PIN_11_PIN |
		ROUT_Y4_PIN_13_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_MCAN0_IOMUX_CAN_TX, GPIO_MCAN0_IOMUX_CAN_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_MCAN0_IOMUX_CAN_RX, GPIO_MCAN0_IOMUX_CAN_RX_FUNC);
    Rout_init();

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 3,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_ENABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_SYSOSC,
	.qDiv                   = 4,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);

}


/*
 * Timer clock configuration to be sourced by  / 8 (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   10000000 Hz = 10000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gZCLK1ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gZCLK1Config = {
    .pwmMode = DL_TIMER_PWM_MODE_CENTER_ALIGN,
    .period = 80,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_ZCLK1_init(void) {

    DL_TimerA_setClockConfig(
        ZCLK1_INST, (DL_TimerA_ClockConfig *) &gZCLK1ClockConfig);

    DL_TimerA_initPWMMode(
        ZCLK1_INST, (DL_TimerA_PWMConfig *) &gZCLK1Config);

    DL_TimerA_setCaptureCompareValue(ZCLK1_INST, 20, DL_TIMER_CC_0_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(ZCLK1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(ZCLK1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_enableClock(ZCLK1_INST);


    
    DL_TimerA_setCCPDirection(ZCLK1_INST , DL_TIMER_CC0_OUTPUT );

}
/*
 * Timer clock configuration to be sourced by  / 8 (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   10000000 Hz = 10000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gZCLK2ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gZCLK2Config = {
    .pwmMode = DL_TIMER_PWM_MODE_CENTER_ALIGN,
    .period = 80,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_ZCLK2_init(void) {

    DL_TimerA_setClockConfig(
        ZCLK2_INST, (DL_TimerA_ClockConfig *) &gZCLK2ClockConfig);

    DL_TimerA_initPWMMode(
        ZCLK2_INST, (DL_TimerA_PWMConfig *) &gZCLK2Config);

    DL_TimerA_setCaptureCompareValue(ZCLK2_INST, 20, DL_TIMER_CC_0_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(ZCLK2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(ZCLK2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_enableClock(ZCLK2_INST);


    
    DL_TimerA_setCCPDirection(ZCLK2_INST , DL_TIMER_CC0_OUTPUT );

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   10000000 Hz = 10000000 Hz / (4 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gscl1_timeClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * scl1_time_INST_LOAD_VALUE = (0.1 ms * 10000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gscl1_timeTimerConfig = {
    .period     = scl1_time_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_scl1_time_init(void) {

    DL_TimerG_setClockConfig(scl1_time_INST,
        (DL_TimerG_ClockConfig *) &gscl1_timeClockConfig);

    DL_TimerG_initTimerMode(scl1_time_INST,
        (DL_TimerG_TimerConfig *) &gscl1_timeTimerConfig);
    DL_TimerG_enableInterrupt(scl1_time_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(scl1_time_INST);




}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (20000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000000 Hz = 20000000 Hz / (4 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gscl1_com_idleClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * scl1_com_idle_INST_LOAD_VALUE = (0.02 ms * 20000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gscl1_com_idleTimerConfig = {
    .period     = scl1_com_idle_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_scl1_com_idle_init(void) {

    DL_TimerG_setClockConfig(scl1_com_idle_INST,
        (DL_TimerG_ClockConfig *) &gscl1_com_idleClockConfig);

    DL_TimerG_initTimerMode(scl1_com_idle_INST,
        (DL_TimerG_TimerConfig *) &gscl1_com_idleTimerConfig);
    DL_TimerG_enableInterrupt(scl1_com_idle_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(scl1_com_idle_INST);




}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (20000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000000 Hz = 20000000 Hz / (4 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gscl2_com_idleClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * scl2_com_idle_INST_LOAD_VALUE = (0.1 ms * 20000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gscl2_com_idleTimerConfig = {
    .period     = scl2_com_idle_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_scl2_com_idle_init(void) {

    DL_TimerG_setClockConfig(scl2_com_idle_INST,
        (DL_TimerG_ClockConfig *) &gscl2_com_idleClockConfig);

    DL_TimerG_initTimerMode(scl2_com_idle_INST,
        (DL_TimerG_TimerConfig *) &gscl2_com_idleTimerConfig);
    DL_TimerG_enableInterrupt(scl2_com_idle_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(scl2_com_idle_INST);




}



static const DL_UART_Main_ClockConfig gZSCL1ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gZSCL1Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_EVEN,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_ZSCL1_init(void)
{
    DL_UART_Main_setClockConfig(ZSCL1_INST, (DL_UART_Main_ClockConfig *) &gZSCL1ClockConfig);

    DL_UART_Main_init(ZSCL1_INST, (DL_UART_Main_Config *) &gZSCL1Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 125000
     *  Actual baud rate: 125000
     */
    DL_UART_Main_setOversampling(ZSCL1_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(ZSCL1_INST, ZSCL1_IBRD_80_MHZ_125000_BAUD, ZSCL1_FBRD_80_MHZ_125000_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(ZSCL1_INST,
                                 DL_UART_MAIN_INTERRUPT_EOT_DONE |
                                 DL_UART_MAIN_INTERRUPT_RX |
                                 DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR |
                                 DL_UART_MAIN_INTERRUPT_TX);
    /* Setting the Interrupt Priority */
    // NVIC_SetPriority(ZSCL1_INST_INT_IRQN, 0);
	NVIC_SetPriority(ZSCL1_INST_INT_IRQN, 1);

    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(ZSCL1_INST);

    DL_UART_Main_enable(ZSCL1_INST);
}

static const DL_UART_Main_ClockConfig gZSCL2ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gZSCL2Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_EVEN,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_ZSCL2_init(void)
{
    DL_UART_Main_setClockConfig(ZSCL2_INST, (DL_UART_Main_ClockConfig *) &gZSCL2ClockConfig);

    DL_UART_Main_init(ZSCL2_INST, (DL_UART_Main_Config *) &gZSCL2Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 125000
     *  Actual baud rate: 125000
     */
    DL_UART_Main_setOversampling(ZSCL2_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(ZSCL2_INST, ZSCL2_IBRD_40_MHZ_125000_BAUD, ZSCL2_FBRD_40_MHZ_125000_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(ZSCL2_INST,
                                 DL_UART_MAIN_INTERRUPT_EOT_DONE |
                                 DL_UART_MAIN_INTERRUPT_RX |
                                 DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR |
                                 DL_UART_MAIN_INTERRUPT_TX);


	NVIC_SetPriority(ZSCL2_INST_INT_IRQN, 1);

    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(ZSCL2_INST);

    DL_UART_Main_enable(ZSCL2_INST);
}

static const DL_UART_Main_ClockConfig gZSCL3ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gZSCL3Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_EVEN,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_ZSCL3_init(void)
{
    DL_UART_Main_setClockConfig(ZSCL3_INST, (DL_UART_Main_ClockConfig *) &gZSCL3ClockConfig);

    DL_UART_Main_init(ZSCL3_INST, (DL_UART_Main_Config *) &gZSCL3Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 38400
     *  Actual baud rate: 38396.93
     */
    DL_UART_Main_setOversampling(ZSCL3_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(ZSCL3_INST, ZSCL3_IBRD_40_MHZ_125000_BAUD, ZSCL3_IBRD_40_MHZ_125000_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(ZSCL3_INST,
                                  DL_UART_MAIN_INTERRUPT_EOT_DONE |
                                 DL_UART_MAIN_INTERRUPT_RX |
                                 DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR |
                                 DL_UART_MAIN_INTERRUPT_TX);


	NVIC_SetPriority(ZSCL3_INST_INT_IRQN, 1);

    /* Configure DMA Transmit Event */
    DL_UART_Main_enableDMATransmitEvent(ZSCL3_INST);
    DL_UART_Main_enable(ZSCL3_INST);
}
static const DL_DMA_Config gDMA_SCL1_TXConfig = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = ZSCL1_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_SCL1_TX_init(void)
{
    DL_DMA_initChannel(DMA, DMA_SCL1_TX_CHAN_ID , (DL_DMA_Config *) &gDMA_SCL1_TXConfig);
}
static const DL_DMA_Config gDMA_SCL2_TXConfig = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = ZSCL2_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_SCL2_TX_init(void)
{
    DL_DMA_initChannel(DMA, DMA_SCL2_TX_CHAN_ID , (DL_DMA_Config *) &gDMA_SCL2_TXConfig);
}
static const DL_DMA_Config gDMA_SCL3_TXConfig = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement   = DL_DMA_ADDR_INCREMENT,
    .destWidth      = DL_DMA_WIDTH_BYTE,
    .srcWidth       = DL_DMA_WIDTH_BYTE,
    .trigger        = ZSCL3_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_SCL3_TX_init(void)
{
    DL_DMA_initChannel(DMA, DMA_SCL3_TX_CHAN_ID , (DL_DMA_Config *) &gDMA_SCL3_TXConfig);
}
SYSCONFIG_WEAK void SYSCFG_DL_DMA_init(void){
    SYSCFG_DL_DMA_SCL1_TX_init();
    SYSCFG_DL_DMA_SCL2_TX_init();
    SYSCFG_DL_DMA_SCL3_TX_init();
}


SYSCONFIG_WEAK void SYSCFG_DL_WWDT0_init(void)
{
    /*
     * Initialize WWDT0 in Watchdog mode with following settings
     *   Watchdog Source Clock = (LFCLK Freq) / (WWDT Clock Divider)
     *                         = 32768Hz / 4 = 8.19 kHz
     *   Watchdog Period       = (WWDT Clock Divider) âˆ?(WWDT Period Count) / 32768Hz
     *                         = 4 * 2^12 / 32768Hz = 500.00 ms
     *   Window0 Closed Period = (WWDT Period) * (Window0 Closed Percent)
     *                         = 500.00 ms * 25% = 125.00 ms
     *   Window1 Closed Period = (WWDT Period) * (Window1 Closed Percent)
     *                         = 500.00 ms * 0% = 0.00 s
     */
    DL_WWDT_initWatchdogMode(WWDT0_INST, DL_WWDT_CLOCK_DIVIDE_4,
        DL_WWDT_TIMER_PERIOD_12_BITS, DL_WWDT_RUN_IN_SLEEP,
        DL_WWDT_WINDOW_PERIOD_25, DL_WWDT_WINDOW_PERIOD_0);

    /* Set Window0 as active window */
    DL_WWDT_setActiveWindow(WWDT0_INST, DL_WWDT_WINDOW0);

}


static const DL_MCAN_ClockConfig gMCAN0ClockConf = {
    .clockSel = DL_MCAN_FCLK_SYSPLLCLK1,
    .divider  = DL_MCAN_FCLK_DIV_1,
};

static const DL_MCAN_InitParams gMCAN0InitParams= {

/* Initialize MCAN Init parameters.    */
    .fdMode            = false,
    .brsEnable         = false,
    .txpEnable         = false,
    .efbi              = false,
    .pxhddisable       = false,
    .darEnable         = false,
    .wkupReqEnable     = true,
    .autoWkupEnable    = true,
    .emulationEnable   = true,
    .tdcEnable         = false,
    .wdcPreload        = 255,

/* Transmitter Delay Compensation parameters. */
    .tdcConfig.tdcf    = 10,
    .tdcConfig.tdco    = 6,
};


static const DL_MCAN_MsgRAMConfigParams gMCAN0MsgRAMConfigParams ={

    /* Standard ID Filter List Start Address. */
    .flssa                = MCAN0_INST_MCAN_STD_ID_FILT_START_ADDR,
    /* List Size: Standard ID. */
    .lss                  = MCAN0_INST_MCAN_STD_ID_FILTER_NUM,
    /* Extended ID Filter List Start Address. */
    .flesa                = MCAN0_INST_MCAN_EXT_ID_FILT_START_ADDR,
    /* List Size: Extended ID. */
    .lse                  = MCAN0_INST_MCAN_EXT_ID_FILTER_NUM,
    /* Tx Buffers Start Address. */
    .txStartAddr          = MCAN0_INST_MCAN_TX_BUFF_START_ADDR,
    /* Number of Dedicated Transmit Buffers. */
    .txBufNum             = MCAN0_INST_MCAN_TX_BUFF_SIZE,
    .txFIFOSize           = 0,
    /* Tx Buffer Element Size. */
    .txBufMode            = 0,
    .txBufElemSize        = DL_MCAN_ELEM_SIZE_64BYTES,
    /* Tx Event FIFO Start Address. */
    .txEventFIFOStartAddr = MCAN0_INST_MCAN_TX_EVENT_START_ADDR,
    /* Event FIFO Size. */
    .txEventFIFOSize      = MCAN0_INST_MCAN_TX_EVENT_SIZE,
    /* Level for Tx Event FIFO watermark interrupt. */
    .txEventFIFOWaterMark = 3,
    /* Rx FIFO0 Start Address. */
    .rxFIFO0startAddr     = MCAN0_INST_MCAN_FIFO_0_START_ADDR,
    /* Number of Rx FIFO elements. */
    .rxFIFO0size          = MCAN0_INST_MCAN_FIFO_0_NUM,
    /* Rx FIFO0 Watermark. */
    .rxFIFO0waterMark     = 3,
    .rxFIFO0OpMode        = 0,
    /* Rx FIFO1 Start Address. */
    .rxFIFO1startAddr     = MCAN0_INST_MCAN_FIFO_1_START_ADDR,
    /* Number of Rx FIFO elements. */
    .rxFIFO1size          = MCAN0_INST_MCAN_FIFO_1_NUM,
    /* Level for Rx FIFO 1 watermark interrupt. */
    .rxFIFO1waterMark     = 3,
    /* FIFO blocking mode. */
    .rxFIFO1OpMode        = 0,
    /* Rx Buffer Start Address. */
    .rxBufStartAddr       = MCAN0_INST_MCAN_RX_BUFF_START_ADDR,
    /* Rx Buffer Element Size. */
    .rxBufElemSize        = DL_MCAN_ELEM_SIZE_64BYTES,
    /* Rx FIFO0 Element Size. */
    .rxFIFO0ElemSize      = DL_MCAN_ELEM_SIZE_64BYTES,
    /* Rx FIFO1 Element Size. */
    .rxFIFO1ElemSize      = DL_MCAN_ELEM_SIZE_64BYTES,
};



static const DL_MCAN_BitTimingParams   gMCAN0BitTimes = {
    /* Arbitration Baud Rate Pre-scaler. */
    .nomRatePrescalar   = 0,
    /* Arbitration Time segment before sample point. */
    .nomTimeSeg1        = 173,
    /* Arbitration Time segment after sample point. */
    .nomTimeSeg2        = 24,
    /* Arbitration (Re)Synchronization Jump Width Range. */
    .nomSynchJumpWidth  = 24,
    /* Data Baud Rate Pre-scaler. */
    .dataRatePrescalar  = 0,
    /* Data Time segment before sample point. */
    .dataTimeSeg1       = 0,
    /* Data Time segment after sample point. */
    .dataTimeSeg2       = 0,
    /* Data (Re)Synchronization Jump Width.   */
    .dataSynchJumpWidth = 0,
};


SYSCONFIG_WEAK void SYSCFG_DL_MCAN0_init(void) {
    DL_MCAN_RevisionId revid_MCAN0;

    DL_MCAN_enableModuleClock(MCAN0_INST);

    DL_MCAN_setClockConfig(MCAN0_INST, (DL_MCAN_ClockConfig *) &gMCAN0ClockConf);

    /* Get MCANSS Revision ID. */
    DL_MCAN_getRevisionId(MCAN0_INST, &revid_MCAN0);

    /* Wait for Memory initialization to be completed. */
    while(false == DL_MCAN_isMemInitDone(MCAN0_INST));

    /* Put MCAN in SW initialization mode. */

    DL_MCAN_setOpMode(MCAN0_INST, DL_MCAN_OPERATION_MODE_SW_INIT);

    /* Wait till MCAN is not initialized. */
    while (DL_MCAN_OPERATION_MODE_SW_INIT != DL_MCAN_getOpMode(MCAN0_INST));

    /* Initialize MCAN module. */
    DL_MCAN_init(MCAN0_INST, (DL_MCAN_InitParams *) &gMCAN0InitParams);


    /* Configure Bit timings. */
    DL_MCAN_setBitTime(MCAN0_INST, (DL_MCAN_BitTimingParams*) &gMCAN0BitTimes);

    /* Configure Message RAM Sections */
    DL_MCAN_msgRAMConfig(MCAN0_INST, (DL_MCAN_MsgRAMConfigParams*) &gMCAN0MsgRAMConfigParams);



    /* Set Extended ID Mask. */
    DL_MCAN_setExtIDAndMask(MCAN0_INST, MCAN0_INST_MCAN_EXT_ID_AND_MASK );

    /* Loopback mode */

    /* Take MCAN out of the SW initialization mode */
    DL_MCAN_setOpMode(MCAN0_INST, DL_MCAN_OPERATION_MODE_NORMAL);

    while (DL_MCAN_OPERATION_MODE_NORMAL != DL_MCAN_getOpMode(MCAN0_INST));

    /* Enable MCAN mopdule Interrupts */
    DL_MCAN_enableIntr(MCAN0_INST, MCAN0_INST_MCAN_INTERRUPTS, 1U);

    DL_MCAN_selectIntrLine(MCAN0_INST, DL_MCAN_INTR_MASK_ALL, DL_MCAN_INTR_LINE_NUM_1);
    DL_MCAN_enableIntrLine(MCAN0_INST, DL_MCAN_INTR_LINE_NUM_1, 1U);

    /* Enable MSPM0 MCAN interrupt */
    DL_MCAN_clearInterruptStatus(MCAN0_INST,(DL_MCAN_MSP_INTERRUPT_LINE1));
    DL_MCAN_enableInterrupt(MCAN0_INST,(DL_MCAN_MSP_INTERRUPT_LINE1));

}

