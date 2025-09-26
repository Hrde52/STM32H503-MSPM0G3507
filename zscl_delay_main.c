


		/*
		If the UART has already been enabled, then it must be made ready for
		configuration by first calling @ref DL_UART_changeConfig
		DL_UART_changeConfig was called, then the UART must be
		re-enabled by calling @ref DL_UART_enable
		*/

/*
DL_UART_changeConfig(ZSCL1_INST);
DL_UART_Main_setDirection(ZSCL1_INST,DL_UART_MAIN_DIRECTION_TX);
DL_UART_Main_setDirection(ZSCL1_INST,DL_UART_MAIN_DIRECTION_RX);
DL_UART_Main_setDirection(ZSCL1_INST,DL_UART_MAIN_DIRECTION_TX_RX);
DL_UART_Main_enable(ZSCL1_INST);
*/
                  
                  
/*


// pg_t01


*/

	




#include "ti_msp_dl_config.h"
// #include "typdef.h"

#include "zscl_logic.h"
#include "zcom485.h"


#define FLASH_LED_SCL() 	DL_GPIO_togglePins(GPIOB, ZCRESET2_PIN_2_PIN)
#define FLASH_LED_CAN() 	DL_GPIO_togglePins(GPIOB, ZTXEN2_PIN_3_PIN)
#define FLASH_LED_485B() 	DL_GPIO_togglePins(GPIOB, LED_485B_PIN_11_PIN)
#define FLASH_LED_MCU() 	//DL_GPIO_togglePins(GPIOB, LED_MCU_PIN_12_PIN)





#define ID_MODE_STANDARD (0x0U)
#define ID_MODE_EXTENDED (0x1U)

/* Delay for 5ms to ensure UART TX is idle before starting transmission */
#define UART_TX_DELAY 	(160000)
#define SCL1_TX 				DL_GPIO_setPins(GPIOB, ZTXEN1_PIN_1_PIN)
#define SCL1_RX 				DL_GPIO_clearPins(GPIOB, ZTXEN1_PIN_1_PIN)
#define SCL2_TX 				DL_GPIO_setPins(GPIOB, ZTXEN2_PIN_3_PIN)
#define SCL2_RX 				DL_GPIO_clearPins(GPIOB, ZTXEN2_PIN_3_PIN)
#define SCL1_LED_OFF 	  DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_0)
#define SCL1_LED_ON 		DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_0)
#define SCL2_LED_OFF 		DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_1)
#define SCL2_LED_ON 		DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_1)

#define RS485B_TX 				DL_GPIO_setPins(GPIOB, m485BTE_PIN_10_PIN)
#define RS485B_RX 				DL_GPIO_clearPins(GPIOB, m485BTE_PIN_10_PIN)

#define RS485A_TX 				DL_GPIO_setPins(GPIOA, ZTXEN3_PIN_8_PIN)
#define RS485A_RX 				DL_GPIO_clearPins(GPIOA, ZTXEN3_PIN_8_PIN)

extern uint8_t Scl2RxBufx[60];
extern uint8_t 	Scl1RxBufx[60];
extern void Scl2_Rx_Verify(void);
extern void Scl1_Data_Pack(void);
extern void Scl1_Rx_Verify(void);
extern void Scl_Err_Process(void);
extern uint8_t   Scl1RxBufCnt;
extern uint8_t  Scl1RxBufCntX;
extern uint8_t   Scl2RxBufCnt;
extern uint16_t  Scl2CommRate[128];
extern detecte  	Scl1CommRate[128];
extern uint32_t  const Scl1DeviceNum;
extern uint16_t  Scl1led_num;
extern uint16_t  Scl2led_num;
uint64_t 	Scl_Err_Check;
int16_t		Scl2_Tx_Done;
int16_t		Scl1_Tx_Done;
uint8_t		Scl2_Rx_Delay;
uint8_t		Scl1_Rx_Delay;
int16_t   Clear_Com_rate;
int16_t   Scl1led_Cnt;
int16_t   Scl2led_Cnt;
uint8_t   Scl2_com_sucss;
uint8_t   Scl1_com_sucss;
uint8_t   Version;


rxd_uart_TypeDef rxd_uart0;
rxd_uart_TypeDef rxd_uart0_tmp;

txd_uart_TypeDef txd_uart0;


rxd_uart_TypeDef rxd_uart1;
rxd_uart_TypeDef rxd_uart1_tmp;

txd_uart_TypeDef txd_uart1;

rxd_uart_TypeDef rxd_uart2;
rxd_uart_TypeDef rxd_uart2_tmp;

txd_uart_TypeDef txd_uart2;

uint8_t rxd_flag;
uint8_t uart_sending_flag;



uint8_t rxd_flag_rs485A;
uint8_t rxd_flag_rs485B;
uint8_t time_100ms = 0;


volatile uint32_t gInterruptLine1Status;
unsigned char gServiceInt;
unsigned char g_can_rx_flag;
unsigned char g_can_datan_time;
// --------------------------------------------
void can_txd_test(void);
void UART_setDirection(    UART_Regs *uart, DL_UART_DIRECTION direction);

static void rs485B_txd_start(unsigned char tx[],unsigned char len);
void SCL2_TXEN(uint8_t TxLength,uint8_t * src);
void SCL3_TXEN(uint8_t TxLength,uint8_t * src);
extern void board_test(void);
extern void boardtest_loop_process();
extern bool handle_com_data();


/*
DL_UART_changeConfig(ZSCL1_INST);
DL_UART_Main_setDirection(ZSCL1_INST,DL_UART_MAIN_DIRECTION_TX);
DL_UART_Main_setDirection(ZSCL1_INST,DL_UART_MAIN_DIRECTION_RX);
DL_UART_Main_setDirection(ZSCL1_INST,DL_UART_MAIN_DIRECTION_TX_RX);
DL_UART_Main_enable(ZSCL1_INST);
*/


// void UART_setDirection(    UART_Regs *uart, DL_UART_DIRECTION direction)
void scl_setDirection(    DL_UART_DIRECTION direction)
{
	DL_UART_changeConfig(ZSCL1_INST);
	DL_UART_Main_setDirection(ZSCL1_INST,direction);
	DL_UART_Main_enable(ZSCL1_INST);
}


void ROUT(uint32_t pin,uint8_t value)
{
	if(value)
	{
		DL_GPIO_setPins(GPIOB,pin);
	}
	else
	{
		DL_GPIO_clearPins(GPIOB,pin);
	}
}

void Rout_init(void)
{

  ROUT(DL_GPIO_PIN_20,0);  //ROUT_Y0-Y3 低有效
  ROUT(DL_GPIO_PIN_21,0);
  ROUT(DL_GPIO_PIN_22,0);
  ROUT(DL_GPIO_PIN_23,1);  //ROUT_Y4-Y7 高有效
  ROUT(DL_GPIO_PIN_24,1);
  ROUT(DL_GPIO_PIN_25,1);
  ROUT(DL_GPIO_PIN_26,1);
}




void can_txd_start(unsigned char tx[],unsigned char p_StdId)
{

    DL_MCAN_TxBufElement txMsg;
    /* Initialize message to transmit. */
    /* Identifier Value. */
    // txMsg.id = ((uint32_t)(0x4)) << 18U;
	  txMsg.id = ((uint32_t)(p_StdId)) << 18U;
	
    /* Transmit data frame. */
    txMsg.rtr = 0U;
	
    /* 11-bit standard identifier. */
    txMsg.xtd = 0U;
	
    /* ESI bit in CAN FD format depends only on gError passive flag. */
    txMsg.esi = 0U;
	
    /* Transmitting 4 bytes. */
    txMsg.dlc = 8U;
	
    /* CAN FD frames transmitted with bit rate switching. */
    txMsg.brs = 1U;
    /* Frame transmitted in CAN FD format. */
    txMsg.fdf = 1U;
    /* Store Tx events. */
    txMsg.efc = 1U;
    /* Message Marker. */
    txMsg.mm = 0xAAU;
	
    /* Data bytes. */
    txMsg.data[0] = tx[0];
    txMsg.data[1] = tx[1];
    txMsg.data[2] = tx[2];
    txMsg.data[3] = tx[3];
    txMsg.data[4] = tx[4];
    txMsg.data[5] = tx[5];
    txMsg.data[6] = tx[6];
    txMsg.data[7] = tx[7];

	/* Write Tx Message to the Message RAM. */
	DL_MCAN_writeMsgRam(MCAN0_INST, DL_MCAN_MEM_TYPE_BUF, 1U, &txMsg);

	/* Enable Transmission interrupt.*/
	DL_MCAN_TXBufTransIntrEnable(MCAN0_INST, 1U, 1U);

	/* Add request for transmission. */
	DL_MCAN_TXBufAddReq(MCAN0_INST, 1U);





}



void can_txd_test(void)
{
    DL_MCAN_TxBufElement txMsg;
    /* Initialize message to transmit. */
    /* Identifier Value. */
    // txMsg.id = ((uint32_t)(0x4)) << 18U;
	  txMsg.id = ((uint32_t)(0xf1)) << 18U;
	
    /* Transmit data frame. */
    txMsg.rtr = 0U;
	
    /* 11-bit standard identifier. */
    txMsg.xtd = 0U;
	
    /* ESI bit in CAN FD format depends only on gError passive flag. */
    txMsg.esi = 0U;
	
    /* Transmitting 4 bytes. */
    txMsg.dlc = 4U;
    /* CAN FD frames transmitted with bit rate switching. */
    txMsg.brs = 1U;
    /* Frame transmitted in CAN FD format. */
    txMsg.fdf = 1U;
    /* Store Tx events. */
    txMsg.efc = 1U;
    /* Message Marker. */
    txMsg.mm = 0xAAU;
    /* Data bytes. */
    txMsg.data[0] = 0x12;
    txMsg.data[1] = 0x34;
    txMsg.data[2] = 0x56;
    txMsg.data[3] = 0x78;

	/* Write Tx Message to the Message RAM. */
	DL_MCAN_writeMsgRam(MCAN0_INST, DL_MCAN_MEM_TYPE_BUF, 1U, &txMsg);

	/* Enable Transmission interrupt.*/
	DL_MCAN_TXBufTransIntrEnable(MCAN0_INST, 1U, 1U);

	/* Add request for transmission. */
	DL_MCAN_TXBufAddReq(MCAN0_INST, 1U);
}












void processRxMsg(DL_MCAN_RxBufElement *rxMsg)
{
    uint32_t idMode;
    uint32_t id;

	CanRxMsg RxMessage;
	unsigned char rx[8];
	
    idMode = rxMsg->xtd;
    if (ID_MODE_EXTENDED == idMode) 
	{
        id = rxMsg->id;
    } 
	else 
	{
        id = ((rxMsg->id & (uint32_t) 0x1FFC0000) >> (uint32_t) 18);
		RxMessage.StdId = id;
                if(RxMessage.StdId==0x14)
                {
                  mtestmsg.can_flag = 1;
                }
		// ------------------------------------
		rx[0] = (rxMsg->data[0]&0xff);
		rx[1] = (rxMsg->data[1]&0xff);
		rx[2] = (rxMsg->data[2]&0xff);
		rx[3] = (rxMsg->data[3]&0xff);

		rx[4] = (rxMsg->data[4]&0xff);
		rx[5] = (rxMsg->data[5]&0xff);
		rx[6] = (rxMsg->data[6]&0xff);
		rx[7] = (rxMsg->data[7]&0xff);
		mem_copy(RxMessage.Data,rx,8);
		can_process(RxMessage);
    }
}



void MCAN0_INST_IRQHandler(void)
{
	DL_MCAN_IIDX flag;

	__disable_irq();
	
	flag = DL_MCAN_getPendingInterrupt(MCAN0_INST);

    // switch (DL_MCAN_getPendingInterrupt(MCAN0_INST)) 
	switch (flag) 
	{
        case DL_MCAN_IIDX_LINE1:				
	        // intrStatus = DL_MCAN_getIntrStatus(MCAN0_INST) & MCAN0_INST_MCAN_INTERRUPTS;
	        // gInterruptLine1Status |= (DL_MCAN_getIntrStatus(MCAN0_INST) & MCAN0_INST_MCAN_INTERRUPTS);

			
	    gInterruptLine1Status = DL_MCAN_getIntrStatus(MCAN0_INST);
		DL_MCAN_clearIntrStatus(MCAN0_INST, gInterruptLine1Status, DL_MCAN_INTR_SRC_MCAN_LINE_1);

		if(gInterruptLine1Status&MCAN0_INST_MCAN_INTERRUPTS)
		{
			 g_can_rx_flag = 1;

		}
			
            break;
        default:
            break;
    }

	__enable_irq();
	
}




void scl_txd_start(unsigned char tx[],unsigned char len)
{
	SCL1_TX;
	// scl_setDirection(DL_UART_MAIN_DIRECTION_TX);
	
	// uart_sending_flag = 1;

	/*
	DL_UART_clearInterruptStatus(ZSCL1_INST,DL_UART_MAIN_IIDX_RX|DL_UART_MAIN_INTERRUPT_EOT_DONE|
											DL_UART_MAIN_IIDX_TX|DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR);

    DL_UART_disableInterrupt(ZSCL1_INST,DL_UART_MAIN_INTERRUPT_RX);
	*/
	
	
	
	mem_copy(&(txd_uart0.txd_uart_data[0]),tx,len);
	
	txd_uart0.txd_uart_cnt = 1;
	txd_uart0.txd_uart_length = len;
	DL_UART_Main_transmitData(ZSCL1_INST, txd_uart0.txd_uart_data[0]);
}




static void rs485B_txd_start(unsigned char tx[],unsigned char len)
{
	RS485B_TX;
	DL_UART_disableInterrupt(ZSCL2_INST,DL_UART_MAIN_INTERRUPT_RX);
	
	mem_copy(&(txd_uart1.txd_uart_data[0]),tx,len);
	
	txd_uart1.txd_uart_cnt = 1;
	txd_uart1.txd_uart_length = len;
	DL_UART_Main_transmitData(ZSCL2_INST, txd_uart1.txd_uart_data[0]);
}



uint8_t test_start = 0;
int main(void)
{
	uint8_t tx[3];
	DL_MCAN_RxBufElement rxMsg;
	DL_MCAN_RxFIFOStatus rxFS;
	
	uint8_t i;
	
	__disable_irq();
    SYSCFG_DL_init();

	SCL1_RX;
	// scl_setDirection(DL_UART_MAIN_DIRECTION_RX);
	
	NVIC_ClearPendingIRQ(ZSCL1_INST_INT_IRQN);
	NVIC_EnableIRQ(ZSCL1_INST_INT_IRQN);
	
	NVIC_ClearPendingIRQ(ZSCL2_INST_INT_IRQN);
	NVIC_EnableIRQ(ZSCL2_INST_INT_IRQN);
        
	NVIC_ClearPendingIRQ(ZSCL3_INST_INT_IRQN);
	NVIC_EnableIRQ(ZSCL3_INST_INT_IRQN);        
	
	// NVIC_EnableIRQ(scl1_time_INST_INT_IRQN);
	
	NVIC_ClearPendingIRQ(scl1_com_idle_INST_INT_IRQN);
	NVIC_EnableIRQ(scl1_com_idle_INST_INT_IRQN);
	
	// NVIC_EnableIRQ(scl2_com_idle_INST_INT_IRQN);
	
	NVIC_ClearPendingIRQ(MCAN0_INST_INT_IRQN);
	NVIC_EnableIRQ(MCAN0_INST_INT_IRQN);
	
	// delay_cycles(UART_TX_DELAY);
	
	__enable_irq();
	// DL_TimerG_startCounter(scl1_time_INST);
	DL_TimerG_startCounter(scl1_com_idle_INST);
	// DL_TimerG_startCounter(scl2_com_idle_INST);
	// SCL2_RX;

	Version =100;  //程序版本
	
	  
	DL_TimerA_startCounter(ZCLK1_INST);
	rxd_uart0.rxd_uart_cnt = 0;
	rxd_flag = 0;
	SCL1_RX;
	
	Scl1_Rx_Delay = 0;
	g_can_rx_flag = 0;

	rxd_uart1.rxd_uart_cnt = 0;
	rxd_flag_rs485B = 0;
rxd_flag_rs485A = 0;
	RS485B_RX;
	RS485A_RX;



	// DL_GPIO_clearPins(GPIOB, ZCRESET2_PIN_2_PIN|ZTXEN2_PIN_3_PIN);
	// DL_GPIO_setPins(GPIOB, ZCRESET2_PIN_2_PIN|ZTXEN2_PIN_3_PIN);

	blink_cnt_scl = 6;
	blink_cnt_can = 6;
	blink_cnt_485B = 6;

	
	out_y0_cnt = 0;

	uart_sending_flag = 0;

	rxd_can_timeout_m = 0;
	rxd_can_timeout_s = 0;
	rxd_can_timeout_req = 0;
	rxd_scl_timeout = 0;

	can_cnt_rx = 0;
	can_cnt_tx = 0;
	
    while (1)
	{
		__WFI();
                           
                if(time_100ms==1)
                {
                  time_100ms = 0;
                  boardtest_loop_process();
                }
		// ----------------------------rs485B--------------------------------------------
		if(rxd_flag_rs485B)
		{
			rxd_flag_rs485B = 0;

			blink_cnt_485B = 3;
			// rs485B_txd_start(rxd_uart1_tmp.rxd_uart_data,rxd_uart1_tmp.rxd_uart_length);
			//rxd_uart1_tmp.rxd_uart_length = 0;

			/*
			RS485B_TX;
			DL_UART_disableInterrupt(ZSCL2_INST,DL_UART_MAIN_INTERRUPT_RX);
			
			// mem_copy(&(txd_uart1.txd_uart_data[0]),rxd_uart1_tmp.rxd_uart_data,rxd_uart1_tmp.rxd_uart_length);
			
			
			// txd_uart1.txd_uart_length = rxd_uart1_tmp.rxd_uart_length;
			txd_uart1.txd_uart_cnt = 1;
			txd_uart1.txd_uart_length = 16;
			txd_uart1.txd_uart_data[0] = 0x86;
			txd_uart1.txd_uart_data[15] = 0x86;
			DL_UART_Main_transmitData(ZSCL2_INST, txd_uart1.txd_uart_data[0]);
			*/

			/*
			txd_uart1.txd_uart_data[0] = 0x86;
			txd_uart1.txd_uart_data[15] = 0x86;
			SCL2_TXEN(16,txd_uart1.txd_uart_data);
			*/

			rs485_proc_entry(&rxd_uart1_tmp);
		}
		// ----------------------------SCL--------------------------------------------
		if( 1 == rxd_flag)
		{
			rxd_flag = 0;

			/*
			rxd_uart0_tmp.rxd_uart_data[0] = 0x87;
			rxd_uart0_tmp.rxd_uart_data[9] = 0xaa;
			rxd_uart0_tmp.rxd_uart_data[10] = 0x10;
			rxd_uart0_tmp.rxd_uart_data[11] = 0x11;
			rxd_uart0_tmp.rxd_uart_data[16] = xor_check_sum(0,15,rxd_uart0_tmp.rxd_uart_data);
			rxd_uart0_tmp.rxd_uart_length = 17;
			*/
			
			
			uart_proc_entry(&rxd_uart0_tmp);

            
			/*
			tx[0] = 1;
			tx[1] = 2;
			tx[2] = 3;
			
			scl_txd_start(tx,3);
			*/


			
			/*
			SCL1_TX;
			txd_uart0.txd_uart_data[0] = 1;
			txd_uart0.txd_uart_data[1] = 2;
			txd_uart0.txd_uart_data[2] = 3; //(txd_uart0.txd_uart_data[0]^txd_uart0.txd_uart_data[1]);
			
			txd_uart0.txd_uart_cnt = 1;
			txd_uart0.txd_uart_length = 3;
			DL_UART_Main_transmitData(ZSCL1_INST, txd_uart0.txd_uart_data[0]);
			*/
		}
		// ---------------------------CAN---------------------------------------------		
		if(g_can_rx_flag == 0x01)
		{
			g_can_rx_flag = 0;
			
			rxFS.fillLvl = 0;
                        
                        can_nodata_cnt = 0;
                        
                        g_can_datan_time = 0;

			
			// if ((gInterruptLine1Status & MCAN_IR_RF0N_MASK) == MCAN_IR_RF0N_MASK) 
			if ( gInterruptLine1Status & MCAN0_INST_MCAN_INTERRUPTS )
			{
				rxFS.num = DL_MCAN_RX_FIFO_NUM_0;
				while ((rxFS.fillLvl) == 0) 
				{
					DL_MCAN_getRxFIFOStatus(MCAN0_INST, &rxFS);
				}
				__disable_irq();
				DL_MCAN_readMsgRam(MCAN0_INST, DL_MCAN_MEM_TYPE_FIFO, 0U, rxFS.num, &rxMsg);
				DL_MCAN_writeRxFIFOAck(MCAN0_INST, rxFS.num, rxFS.getIdx);
				__enable_irq();
				processRxMsg(&rxMsg);
				// gInterruptLine1Status &= ~(MCAN_IR_RF0N_MASK);
			}	
			// --------------------------
			gInterruptLine1Status = 0;	
		   }
                

	}
}

//****************************************************************************************
//功能：SCL1通信发送启动函数
//入参：TxLength（发送数据BUF长度），src发送数据BUF地址
//返回：无
//****************************************************************************************
// void SCL1_TXEN(uint8_t TxLength,uint8_t * src)
void SCL1_TXEN(uint8_t * src,uint8_t TxLength)

{
	Scl1_Tx_Done = -1;
	SCL1_TX;
	DL_DMA_setSrcAddr(DMA, DMA_SCL1_TX_CHAN_ID, (uint32_t) &src[0]);
	DL_DMA_setDestAddr(DMA, DMA_SCL1_TX_CHAN_ID, (uint32_t)(&ZSCL1_INST->TXDATA));
	DL_DMA_setTransferSize(DMA, DMA_SCL1_TX_CHAN_ID, TxLength);
	/*
	DL_TimerA_stopCounter(ZCLK1_INST);
	DL_TimerA_startCounter(ZCLK1_INST);
	delay_cycles(50);
	*/
	DL_DMA_enableChannel(DMA, DMA_SCL1_TX_CHAN_ID);
}



uint8_t gEchoData_rs485;

void ZSCL2_INST_IRQHandler(void)
{
	uint8_t rsv;
	// __disable_irq();
	
    switch (DL_UART_Main_getPendingInterrupt(ZSCL2_INST)) 
	{
		DL_UART_clearInterruptStatus(ZSCL2_INST,DL_UART_MAIN_IIDX_RX|DL_UART_MAIN_INTERRUPT_EOT_DONE|
		 	                                    DL_UART_MAIN_IIDX_TX|DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR);

		
		case DL_UART_MAIN_IIDX_RX:
			gEchoData_rs485 = DL_UART_Main_receiveData(ZSCL2_INST);
			if( rxd_uart1.rxd_uart_cnt < 64)   // in case of overflow
			{
				rxd_uart1.rxd_uart_idle = 0;
				rxd_uart1.rxd_uart_data[rxd_uart1.rxd_uart_cnt] = gEchoData_rs485; // Uart_ReceiveData(M0P_UART0);
				rxd_uart1.rxd_uart_cnt++;
			}	
			break;

		case DL_UART_MAIN_IIDX_TX:
			if (txd_uart1.txd_uart_cnt < txd_uart1.txd_uart_length)
			{
				DL_UART_Main_transmitData(ZSCL2_INST,txd_uart1.txd_uart_data[txd_uart1.txd_uart_cnt]);
				txd_uart1.txd_uart_cnt++;
			}
			break;
			
		case DL_UART_MAIN_IIDX_EOT_DONE:
			 RS485B_RX;
			 DL_UART_enableInterrupt(ZSCL2_INST,DL_UART_MAIN_INTERRUPT_RX);
			 break;
		
        default:
            break;
    }
	// -----------------------------------------------------------
	// __enable_irq();
}

uint8_t gEchoData_rs485A;

void ZSCL3_INST_IRQHandler(void)
{
	uint8_t rsv;
	// __disable_irq();
	
    switch (DL_UART_Main_getPendingInterrupt(ZSCL3_INST)) 
	{
		DL_UART_clearInterruptStatus(ZSCL3_INST,DL_UART_MAIN_IIDX_RX|DL_UART_MAIN_INTERRUPT_EOT_DONE|
		 	                                    DL_UART_MAIN_IIDX_TX|DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR);

		
		case DL_UART_MAIN_IIDX_RX:
			gEchoData_rs485A = DL_UART_Main_receiveData(ZSCL3_INST);
			if( rxd_uart2.rxd_uart_cnt < 64)   // in case of overflow
			{
				rxd_uart2.rxd_uart_idle = 0;
				rxd_uart2.rxd_uart_data[rxd_uart2.rxd_uart_cnt] = gEchoData_rs485A; // Uart_ReceiveData(M0P_UART0);
				rxd_uart2.rxd_uart_cnt++;
			}	
			break;

		case DL_UART_MAIN_IIDX_TX:
			if (txd_uart2.txd_uart_cnt < txd_uart2.txd_uart_length)
			{
				DL_UART_Main_transmitData(ZSCL3_INST,txd_uart2.txd_uart_data[txd_uart2.txd_uart_cnt]);
				txd_uart2.txd_uart_cnt++;
			}
			break;
			
		case DL_UART_MAIN_IIDX_EOT_DONE:
			 RS485A_RX;
			 DL_UART_enableInterrupt(ZSCL3_INST,DL_UART_MAIN_INTERRUPT_RX);
			 break;
		
        default:
            break;
    }
	// -----------------------------------------------------------
	// __enable_irq();
}





//****************************************************************************************
//功能：SCL1通信串口中断服务函数
//入参：无
//返回：无
//****************************************************************************************


void ZSCL1_INST_IRQHandler(void)
{


	uint8_t gEchoData;
	
	uint8_t rsv;

	// __disable_irq();
	
    switch (DL_UART_Main_getPendingInterrupt(ZSCL1_INST)) 
	{
		DL_UART_clearInterruptStatus(ZSCL1_INST,DL_UART_MAIN_IIDX_RX|DL_UART_MAIN_INTERRUPT_EOT_DONE|
			                                    DL_UART_MAIN_IIDX_TX|DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR);

		
		case DL_UART_MAIN_IIDX_RX:
			gEchoData = DL_UART_Main_receiveData(ZSCL1_INST);
			if( rxd_uart0.rxd_uart_cnt < 64)   // in case of overflow
			{
				rxd_uart0.rxd_uart_idle = 0;
				rxd_uart0.rxd_uart_data[rxd_uart0.rxd_uart_cnt] = gEchoData; // Uart_ReceiveData(M0P_UART0);
				rxd_uart0.rxd_uart_cnt++;
			}	
			break;

		case DL_UART_MAIN_IIDX_TX:
			if (txd_uart0.txd_uart_cnt < txd_uart0.txd_uart_length)
			{
				DL_UART_Main_transmitData(ZSCL1_INST,txd_uart0.txd_uart_data[txd_uart0.txd_uart_cnt]);
				txd_uart0.txd_uart_cnt++;
			}
			break;
			
		case DL_UART_MAIN_IIDX_EOT_DONE:
			 SCL1_RX;
			 // scl_setDirection(DL_UART_MAIN_DIRECTION_RX);
			 DL_UART_enableInterrupt(ZSCL1_INST,DL_UART_MAIN_INTERRUPT_RX);

		
			 break;
		
        default:
            break;
    }
	// -----------------------------------------------------------
	// __enable_irq();
}

//****************************************************************************************
//功能：SCL1通信时序定时器中断服务函数
//入参：无
//返回：无
//****************************************************************************************
void scl1_time_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(scl1_time_INST)) 
		{
        case DL_TIMER_IIDX_ZERO:
			Scl1_Data_Pack();
            break;
        default:
            break;
    }
}

//****************************************************************************************
//功能：SCL1通信时序定时器设置
//入参：定时时间数值(单位100us)
//返回：无
//****************************************************************************************
void Scl1set_n100us(uint32_t n)
{
	DL_TimerG_setLoadValue(scl1_time_INST,(n * scl1_time_INST_LOAD_VALUE));
	DL_TimerG_startCounter(scl1_time_INST);
}




void uart0_receive(void)
{
	unsigned char i;
	unsigned char p_xor;
	rxd_uart0.rxd_uart_length = rxd_uart0.rxd_uart_cnt;
	rxd_uart0.rxd_uart_cnt = 0;
	rxd_uart0.rxd_uart_idle = 0;
	//------------------------------------------------------------
	for(i=0;i<rxd_uart0.rxd_uart_length;i++)
	{
		rxd_uart0_tmp.rxd_uart_data[i] = rxd_uart0.rxd_uart_data[i];
	}
	rxd_uart0_tmp.rxd_uart_length = rxd_uart0.rxd_uart_length;
	//------------------------------------------------------------
	/*
	if( (6 == rxd_uart0_tmp.rxd_uart_length) && 
		(0xAC== rxd_uart0_tmp.rxd_uart_data[0]) )
	*/
	if(rxd_uart0_tmp.rxd_uart_length >= 17)
	{
		rxd_flag = 1;
	}
        
	if( (rxd_uart0_tmp.rxd_uart_length>=4) && 
		(0xA9== rxd_uart0_tmp.rxd_uart_data[0]) &&
                  (0x13== rxd_uart0_tmp.rxd_uart_data[1]))
        {
          mtestmsg.rxd_flag = 1;
        }
}




void uart_receive_rs485(void)
{
	unsigned char i;
	unsigned char p_xor;
	rxd_uart1.rxd_uart_length = rxd_uart1.rxd_uart_cnt;
	rxd_uart1.rxd_uart_cnt = 0;
	rxd_uart1.rxd_uart_idle = 0;
	//------------------------------------------------------------
	for(i=0;i<rxd_uart1.rxd_uart_length;i++)
	{
		rxd_uart1_tmp.rxd_uart_data[i] = rxd_uart1.rxd_uart_data[i];
	}
	rxd_uart1_tmp.rxd_uart_length = rxd_uart1.rxd_uart_length;
	//------------------------------------------------------------
	//if(rxd_uart1_tmp.rxd_uart_length >= 17)
        if(rxd_uart1_tmp.rxd_uart_length >= 10)
	{
		rxd_flag_rs485B = 1;
	}
	//------------------------------------------------------------
	
	if( (rxd_uart1_tmp.rxd_uart_length>=4) && 
		(0xA9== rxd_uart1_tmp.rxd_uart_data[0]) 
                  &&(0x16== rxd_uart1_tmp.rxd_uart_data[1]))
        {
          mtestmsg.rs485a_flag = 1;
        }
        
 	if( (rxd_uart1_tmp.rxd_uart_length>=4) && 
		(0xA9== rxd_uart1_tmp.rxd_uart_data[0]) 
                  &&(0x26== rxd_uart1_tmp.rxd_uart_data[1]))
        {
          mtestmsg.rs485b_flag = 1;
           mtestmsg.io_value = rxd_uart1_tmp.rxd_uart_data[2];
        }       
	

	/*
	p_xor = xor_check_sum(0,15,rxd_uart1.rxd_uart_data);
	if( (17 == rxd_uart1.rxd_uart_length) && 
		(p_xor == rxd_uart1.rxd_uart_data[16]) &&
		(0x87 == rxd_uart1.rxd_uart_data[0]) )
	{
		rxd_flag_rs485B = 1;
	}
	*/
}


void uart_receive_rs485A(void)
{
	unsigned char i;
	unsigned char p_xor;
        
        handle_com_data();
	rxd_uart2.rxd_uart_length = rxd_uart2.rxd_uart_cnt;
	rxd_uart2.rxd_uart_cnt = 0;
	rxd_uart2.rxd_uart_idle = 0;
        
	//------------------------------------------------------------
	for(i=0;i<rxd_uart2.rxd_uart_length;i++)
	{
		rxd_uart2_tmp.rxd_uart_data[i] = rxd_uart2.rxd_uart_data[i];
	}
	rxd_uart2_tmp.rxd_uart_length = rxd_uart2.rxd_uart_length;
	//------------------------------------------------------------
	if(rxd_uart2_tmp.rxd_uart_length >= 17)
	{
		rxd_flag_rs485A = 1;
	}
        
	/*if( ( rxd_uart2_tmp.rxd_uart_length>=4) && 
		(0x9A== rxd_uart2_tmp.rxd_uart_data[0]) &&
                  (0x61== rxd_uart2_tmp.rxd_uart_data[1]))
        {
          mtestmsg.rs485a_flag = 1;
        } */                 
	//------------------------------------------------------------
	/*
	if( (6 == rxd_uart0_tmp.rxd_uart_length) && 
		(0xAC== rxd_uart0_tmp.rxd_uart_data[0]) )
	*/

	/*
	p_xor = xor_check_sum(0,15,rxd_uart1.rxd_uart_data);
	if( (17 == rxd_uart1.rxd_uart_length) && 
		(p_xor == rxd_uart1.rxd_uart_data[16]) &&
		(0x87 == rxd_uart1.rxd_uart_data[0]) )
	{
		rxd_flag_rs485B = 1;
	}
	*/  
}

//****************************************************************************************
//功能：通信空闲定时器中断服务函数
//入参：无
//返回：无
//****************************************************************************************

// 20 uS
void scl1_com_idle_INST_IRQHandler(void)
{
	uint8_t tx[8];
	static uint16_t time_out = 0;
	static uint16_t time_out_1ms = 0;
        static uint16_t time_out_100ms = 0;
	static uint16_t time_out_40ms = 0;
        static uint16_t time_out_300ms = 0;
        static uint16_t time_out_1s = 0;
	uint8_t i,rsv;


	__disable_irq();

	
    switch (DL_TimerG_getPendingInterrupt(scl1_com_idle_INST)) 
		{
        case DL_TIMER_IIDX_ZERO:
			DL_TimerG_setLoadValue(scl1_com_idle_INST,scl1_com_idle_INST_LOAD_VALUE);
			DL_TimerG_startCounter(scl1_com_idle_INST);
			// -----------------------------------------
			time_out_1ms++;
			if(time_out_1ms >= 50)
			{
                          
				time_out_1ms = 0;
				timeout_can();
			}
                        
			time_out_100ms++;
			if(time_out_100ms >= 50*100)
			{
                          
				time_out_100ms = 0;
                                time_100ms = 1;
			}                        
                        
                        time_out_1s++;
                      if(time_out_1s>50*1000)
                        {
                          time_out_1s = 0;
                          if(g_can_rx_flag==0)
                          {
                            g_can_datan_time++;
                            if(g_can_datan_time>180)
                            {
                              g_can_datan_time = 0;
                              poweroff = 1;
                              can_nodata_cnt++;
                              if(can_nodata_cnt>3)
                              {
                                poweroff_on_en = 1;
                              }
                            }
                          }
                          else
                          {
                            can_nodata_cnt = 0;
                          }
                          
                          if(poweroff==1)
                          {
                            poweroff_delaycnt++;
                            if(poweroff_delaycnt>5)
                            {
                              poweroff_delaycnt = 0;
                              poweroff = 0;
                              poweron = 1;
                            }
                          }
                          
                          //if((poweroff_on_en==1)&&(g_can_rx_flag!=0))
                          if((poweroff_on_en==1)&&(can_nodata_cnt==0))
                          {
                            poweroff_on_en_timer++;
                            if(poweroff_on_en_timer>1800)
                            {
                              poweroff_on_en_timer = 0;
                              poweroff_on_en = 0;
                              poweroff_on_cnt = 0;
                              //can_nodata_cnt = 0;
                            }                              
                          }
                          
                          if(poweroff_on_en==0)
                          {
                            if(poweroff==1)
                            {
                              DL_GPIO_setPins(PWR_FSEN_PORT, PWR_FSEN_PIN_9_PIN);
                            }
                            if(poweron==1)
                            {
                              poweron = 0;
                              poweroff_on_cnt++;
                              if(poweroff_on_cnt>5)
                              {
                                poweroff_on_cnt = 0;
                                poweroff_on_en = 1;
                              }
                              poweroff_done = 0;
                              DL_GPIO_clearPins(PWR_FSEN_PORT,PWR_FSEN_PIN_9_PIN);                
                            }
                          }                          
                        }
                       
			// -----------------------------------------
			time_out_40ms++;
			if(time_out_40ms >= 50*300)
			{
				time_out_40ms = 0;
				rxd_scl_timeout++;
				rxd_can_timeout++;

				// if( (rxd_scl_timeout <= 3) && (rxd_can_timeout <= 3))
				{
					DL_WWDT_restart(WWDT0_INST);
				}
			}
                        // -----------------------------------------
                        /*if(time_out_300ms++ > 50*300)
                        {
                          time_out_300ms = 0;
                                if(blink_mode==10)
                                {
                                  if(blink_mode_yiliuwu==1)
                                  {
                                    out_y3_delay_cnt ++;
                                    if(out_y3_delay_cnt<20)
                                    {
                                      ROUT(ROUT_Y3_PIN_6_PIN,0);  //开门维持绿灯
                                      ROUT(ROUT_Y4_PIN_13_PIN,1);                                    
                                    }
                                    else
                                    {
                                    	out_y3_delay_cnt = 20;
                                      if(out_y3_cnt++>=1)
                                      {
                                         if(out_y3_cnt++>=2)
                                         {
                                            out_y3_cnt = 0;
                                         }
                                       ROUT(ROUT_Y4_PIN_13_PIN,0);
                                      }
                                      else
                                      {
                                         ROUT(ROUT_Y4_PIN_13_PIN,1);
                                      }
                                      ROUT(ROUT_Y3_PIN_6_PIN,1);                                     
                                    }
                                  }
                                  else
                                  {
                                  if(out_y3_cnt++>=1)
                                  {
                                    if(out_y3_cnt++>=2)
                                    {
                                      out_y3_cnt = 0;
                                    }
                                    ROUT(ROUT_Y4_PIN_13_PIN,0);
                                  }
                                  else
                                  {
                                    ROUT(ROUT_Y4_PIN_13_PIN,1);
                                  }
                                  ROUT(ROUT_Y3_PIN_6_PIN,1);
                                  }
                                }
                                else
                                {
                                  out_y3_delay_cnt = 0;
                                  out_y3_cnt = 0;
                                  if(blink_mode==1)
                                  {
                                    ROUT(ROUT_Y3_PIN_6_PIN,0);
                                    ROUT(ROUT_Y4_PIN_13_PIN,1);
                                  }
                                  else if(blink_mode==2)
                                  {
                                    ROUT(ROUT_Y3_PIN_6_PIN,1);
                                    ROUT(ROUT_Y4_PIN_13_PIN,0);                       
                                  }
                                  else
                                  {
                                    ROUT(ROUT_Y3_PIN_6_PIN,1);
                                    ROUT(ROUT_Y4_PIN_13_PIN,1); 
                                  }
                                }                         
                        }*/
			// -----------------------------------------
			if(time_out++ > 50*500)
			{
				time_out = 0;

                                

                                  
				if(out_y0_cnt++ >= 12) 
				{
					out_y0_cnt = 0;
					//ROUT(ROUT_Y0_PIN_20_PIN,0);
				}
				// ------------------------------------
				FLASH_LED_MCU();
				if(blink_cnt_scl)
				{
					blink_cnt_scl--;
					FLASH_LED_SCL();
				}
				// ------------------------
				if(blink_cnt_can)
				{
					blink_cnt_can--;
					FLASH_LED_CAN();
				}
				// ------------------------
				if(blink_cnt_485B)
				{
					blink_cnt_485B--;
					FLASH_LED_485B();
				}
			}
			// -----------------------------------------
			if(rxd_uart0.rxd_uart_cnt)
			{
				rxd_uart0.rxd_uart_idle++;
				if(rxd_uart0.rxd_uart_idle >= 6)   // 120uS
				{
					uart0_receive();
				}
			}
			// -----------------------------------------
			if(rxd_uart1.rxd_uart_cnt)
			{
				rxd_uart1.rxd_uart_idle++;
				if(rxd_uart1.rxd_uart_idle >= 6)   // 
				{
					uart_receive_rs485();
				}
			}
			if(rxd_uart2.rxd_uart_cnt)
			{
				rxd_uart2.rxd_uart_idle++;
				if(rxd_uart2.rxd_uart_idle >= 6)   // 
				{
					uart_receive_rs485A();
				}
			}
			 // -----------------------------------------
			 if(time_out_can++ > 50*8)  // 
			 {
				   time_out_can = 0;

				   
				   if(Can_tx_master.StdId)
				   {
						can_txd_start(Can_tx_master.Data,(unsigned char)Can_tx_master.StdId);
						Can_tx_master.StdId = 0;
				   }
				   else if(Can_tx_slave.StdId)
				   {
					   can_txd_start(Can_tx_slave.Data,(unsigned char)Can_tx_slave.StdId);
					   Can_tx_slave.StdId = 0;
				   }
				   else if(Can_tx_object.StdId)
				   {
					   can_txd_start(Can_tx_object.Data,(unsigned char)Can_tx_object.StdId);
					   Can_tx_object.StdId = 0;
				   }
				   
				   


				   /*
				   // can_txd_test();
				   tx[0] = 1;
				   tx[1] = 2;
				   tx[2] = 3;
				   tx[3] = 4;
				   tx[4] = 5;
				   tx[5] = 6;
				   tx[6] = 7;
				   tx[7] = 8;
				   // can_txd_start(tx,0xf1);
				   */
			 }
            break;
        default:
            break;
    }
	// --------------------------------------------------
	__enable_irq();
	
}

//****************************************************************************************
//功能：通信空闲定时器中断服务函数
//入参：无
//返回：无
//****************************************************************************************
void scl2_com_idle_INST_IRQHandler(void)
{
		uint8_t i,rsv;
    switch (DL_TimerG_getPendingInterrupt(scl2_com_idle_INST)) 
		{
        case DL_TIMER_IIDX_ZERO:		
            break;
        default:
            break;
    }
}



//****************************************************************************************
//功能：SCL2通信发送启动
//入参：TxLength（发送数据长度），src(发送数据储存BUF地址)
//返回：无
//****************************************************************************************
void SCL2_TXEN(uint8_t TxLength,uint8_t * src)
{
	// Scl2_Tx_Done = -1;
	// SCL2_TX;

	RS485B_TX;
	DL_DMA_setSrcAddr(DMA, DMA_SCL2_TX_CHAN_ID, (uint32_t) &src[0]);
	DL_DMA_setDestAddr(DMA, DMA_SCL2_TX_CHAN_ID, (uint32_t)(&ZSCL2_INST->TXDATA));
	DL_DMA_setTransferSize(DMA, DMA_SCL2_TX_CHAN_ID, TxLength);
	/*
	DL_TimerA_stopCounter(ZCLK2_INST);
	DL_TimerA_startCounter(ZCLK2_INST);
	delay_cycles(50);
	*/
	DL_DMA_enableChannel(DMA, DMA_SCL2_TX_CHAN_ID);
}

void SCL3_TXEN(uint8_t TxLength,uint8_t * src)
{
	// Scl2_Tx_Done = -1;
	// SCL2_TX;

	RS485A_TX;
	DL_DMA_setSrcAddr(DMA, DMA_SCL3_TX_CHAN_ID, (uint32_t) &src[0]);
	DL_DMA_setDestAddr(DMA, DMA_SCL3_TX_CHAN_ID, (uint32_t)(&ZSCL3_INST->TXDATA));
	DL_DMA_setTransferSize(DMA, DMA_SCL3_TX_CHAN_ID, TxLength);
	/*
	DL_TimerA_stopCounter(ZCLK2_INST);
	DL_TimerA_startCounter(ZCLK2_INST);
	delay_cycles(50);
	*/
	DL_DMA_enableChannel(DMA, DMA_SCL3_TX_CHAN_ID);
}