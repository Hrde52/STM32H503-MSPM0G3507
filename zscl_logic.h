
// #include "zscl_logic.h"
#ifndef __LOGIC_H__
#define __LOGIC_H__
//-----------------------------------------------------------
#ifdef GLOBALS_LOGIC
    #define EXT_LOGIC
#else
    #define EXT_LOGIC extern
#endif	
//-----------------------------------------------------------
#include "ti_msp_dl_config.h"
#include "typdef.h"
//-----------------------------------------------------------

extern void ROUT(uint32_t pin,uint8_t value);


// 中继板发送到传感器CAN_ID(主门)
#define CAN_ID_D2S_M		0xf1

// 传感器发送到中继板CAN_ID(主门)
#define CAN_ID_S2D_M		0xf2


// 中继板发送到传感器CAN_ID(福门)
#define CAN_ID_D2S_S		0xf3

// 传感器发送到中继板CAN_ID(副门)
#define CAN_ID_S2D_S		0xf4



#define OUT1_OFF()	  ROUT(ROUT_Y0_PIN_20_PIN,0) 
#define OUT1_ON()	  ROUT(ROUT_Y0_PIN_20_PIN,1) 

#define OUT2_OFF()	   
#define OUT2_ON()	   

#define OUT3_OFF()	  
#define OUT3_ON()	   


#define OUT4_OFF()	     
#define OUT4_ON()	   





EXT_LOGIC txd_uart_TypeDef txd_scla;
EXT_LOGIC txd_uart_TypeDef txd2_scla;

EXT_LOGIC unsigned short rxd_can_timeout_m;
EXT_LOGIC unsigned short rxd_can_timeout_s;

EXT_LOGIC unsigned short rxd_can_timeout_req;



EXT_LOGIC unsigned short rxd_can_timeout;
EXT_LOGIC unsigned short rxd_scl_timeout;


EXT_LOGIC unsigned char can_req_data[8];
EXT_LOGIC unsigned char can_master_data[8];
EXT_LOGIC unsigned char can_slave_data[8];
EXT_LOGIC unsigned short door_length;
EXT_LOGIC unsigned char door_data;
EXT_LOGIC unsigned short door_length_sf;
EXT_LOGIC unsigned char blink_mode;
EXT_LOGIC unsigned char blink_mode_yiliuwu;
EXT_LOGIC unsigned char poweroff;
EXT_LOGIC unsigned char poweroff_done;
EXT_LOGIC unsigned char poweron;
EXT_LOGIC unsigned char poweroff_delaycnt;
EXT_LOGIC unsigned char poweroff_on_cnt;
EXT_LOGIC unsigned char poweroff_on_en;
EXT_LOGIC unsigned short poweroff_on_en_timer;
EXT_LOGIC unsigned char can_nodata_cnt;

EXT_LOGIC unsigned char rxd_buff_scl[32];

EXT_LOGIC CanRxMsg Can_tx_master;
EXT_LOGIC CanRxMsg Can_tx_slave;
EXT_LOGIC CanRxMsg Can_tx_object;
EXT_LOGIC CanRxMsg Can_tx_boardtest;
EXT_LOGIC unsigned short time_out_can;

EXT_LOGIC unsigned char blink_cnt_scl;
EXT_LOGIC unsigned char blink_cnt_can;
EXT_LOGIC unsigned char blink_cnt_485B;

EXT_LOGIC unsigned char out_y0_cnt;
EXT_LOGIC unsigned char out_y3_cnt;
EXT_LOGIC unsigned char out_y3_delay_cnt;


EXT_LOGIC uint32_t can_cnt_tx;
EXT_LOGIC uint32_t can_cnt_rx;

EXT_LOGIC uint32_t board_sw1;
EXT_LOGIC uint32_t board_sw2;
EXT_LOGIC uint32_t board_sw3;
EXT_LOGIC uint32_t board_sw4;

EXT_LOGIC uint32_t board_IX5;
EXT_LOGIC uint32_t board_IX6;

EXT_LOGIC void mem_copy(void *ptrTo, const void *ptrFrom, unsigned short p_size);
EXT_LOGIC unsigned char xor_check_sum(unsigned char p_start,unsigned char p_end,unsigned char p_data[]);
EXT_LOGIC void uart_proc_entry(rxd_uart_TypeDef *pt_rxd_data);


EXT_LOGIC void rs485_proc_entry(rxd_uart_TypeDef *pt_rxd_data);

extern  void rs485A_proc_entry(rxd_uart_TypeDef *pt_rxd_data);

EXT_LOGIC void can_process(CanRxMsg RxMessage);

EXT_LOGIC void timeout_can(void);



#endif
