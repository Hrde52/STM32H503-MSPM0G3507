#define GLOBALS_LOGIC
#include "zscl_logic.h"

extern void scl_txd_start(unsigned char tx[],unsigned char len);
extern void can_txd_start(unsigned char tx[],unsigned char p_StdId);
extern void DL_Common_delayCycles(uint32_t cycles);
extern void SCL1_TXEN(uint8_t * src,uint8_t TxLength);
extern void SCL2_TXEN(uint8_t TxLength,uint8_t * src);
extern void SCL3_TXEN(uint8_t TxLength,uint8_t * src);



/*===============================================================
   Name:  mem_copy
   Func:  
   Para:                                                    
   Retn:  void
   Auth:  panyuxi@Ropente.com                                          
================================================================*/
void mem_copy(void *ptrTo, const void *ptrFrom, unsigned short p_size)
{
    unsigned char *ptr1 = (unsigned char *)ptrTo;
    unsigned char *ptr2 = (unsigned char *)ptrFrom;
	//-------------------------------------------
    while (p_size--) {
        *ptr1++ = *ptr2++;
    }
}


/*===============================================================
   Name:  mem_set
   Func:  
   Para:                                                    
   Retn:  void
   Auth:  panyuxi@Ropente.com                                          
================================================================*/
void mem_set(void *ptrTo, unsigned char p_value, unsigned short p_size)
{
    unsigned char *ptr = (unsigned char *)ptrTo;
	//-------------------------------------------
    while (p_size--) 
	{
        *ptr++ = p_value;
    }
}


/*********************************************************************************************
   Name:  xor_check_sum                           
   Func:                        
   Para:                                          
   Retn: 
   Auth:  panyuxi@ropente.com                                  
*********************************************************************************************/
unsigned char xor_check_sum(unsigned char p_start,unsigned char p_end,unsigned char p_data[])
{
	unsigned char i,sum=0;
	for(i=p_start;i<=p_end;i++)
	{
		sum ^= p_data[i];
	}
	//-----------------------------
	return sum;
}



void get_scla_tdata_can(txd_uart_TypeDef *pt_txd_scla,unsigned char p_can_m[],unsigned char p_can_s[],unsigned char p_can_req[])
{
	pt_txd_scla->txd_uart_data[0] = 0x86;
	
	pt_txd_scla->txd_uart_data[1] = p_can_m[0];   // 主门
	pt_txd_scla->txd_uart_data[2] = p_can_m[1];   // 主门
	
	pt_txd_scla->txd_uart_data[3] = p_can_s[0];;   // 副门
	pt_txd_scla->txd_uart_data[4] = p_can_s[1];;   // 副门
	
	pt_txd_scla->txd_uart_data[5] = p_can_m[4];  // 主副门

	
	pt_txd_scla->txd_uart_data[6] = 0;


	/*pt_txd_scla->txd_uart_data[7] = (can_cnt_tx>>24)&0xff;
	pt_txd_scla->txd_uart_data[8] = (can_cnt_tx>>16)&0xff;
	pt_txd_scla->txd_uart_data[9] = (can_cnt_tx>>8)&0xff;
	pt_txd_scla->txd_uart_data[10] = (can_cnt_tx>>0)&0xff;
	
	pt_txd_scla->txd_uart_data[11] = (can_cnt_rx>>24)&0xff;
	pt_txd_scla->txd_uart_data[12] = (can_cnt_rx>>16)&0xff;
	pt_txd_scla->txd_uart_data[13] = (can_cnt_rx>>8)&0xff;
	pt_txd_scla->txd_uart_data[14] = (can_cnt_rx>>0)&0xff;*/


	

	
	pt_txd_scla->txd_uart_data[7] = 0;
	pt_txd_scla->txd_uart_data[8] = p_can_req[0];
	pt_txd_scla->txd_uart_data[9] = p_can_req[1];
	pt_txd_scla->txd_uart_data[10] = p_can_req[2];
	
	pt_txd_scla->txd_uart_data[11] = p_can_req[3];
	pt_txd_scla->txd_uart_data[12] = p_can_req[4];
	pt_txd_scla->txd_uart_data[13] = p_can_req[5];
	pt_txd_scla->txd_uart_data[14] = p_can_req[6];
        
        if(((p_can_m[2]&0x1)||(p_can_s[2]&0x1))&&(poweroff_done==0))   //CAN帧收到重启标志
        {
          poweroff_done = 1;
          poweroff = 1;
          p_can_m[2] = 0;
          p_can_s[2] = 0;
        }
        
        int i;
        for(i=0;i<14;i++)
        {
          pt_txd_scla->txd_uart_data[i] = i;
        }
	
	
	pt_txd_scla->txd_uart_data[15] = xor_check_sum(0,14,pt_txd_scla->txd_uart_data);
}




/*********************************************************************************************
   Name:  txd_start_scla
   Func:
   Para:
   Retn:
   Auth:  panyuxi@ropente.com
*********************************************************************************************/
void txd_start_scla(unsigned char p_txd_data[],unsigned char p_length)
{
	scl_txd_start(p_txd_data,p_length);
}




void can_txd(unsigned char data_scl[],unsigned char p_StdId)
{
	can_txd_start(data_scl,p_StdId);
}





void timeout_can(void)   // 1ms
{	
	rxd_can_timeout_m++;
	if(rxd_can_timeout_m >=400) // 400ms 
	{
		rxd_can_timeout_m = 0;

		mem_set(&can_master_data[0],0,sizeof(can_master_data));
		get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	
	}
	// -----------------------------
	rxd_can_timeout_s++;
	if(rxd_can_timeout_s >=400) // 400ms 
	{
		rxd_can_timeout_s = 0;

		mem_set(&can_slave_data[0],0,sizeof(can_slave_data));
		get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	
	}
	// -----------------------------
	rxd_can_timeout_req++;
	if(rxd_can_timeout_req >=400) // 400ms 
	{
		rxd_can_timeout_req = 0;
		
		mem_set(&can_req_data[0],0,sizeof(can_req_data));
		get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	
	}
}





void can_process(CanRxMsg RxMessage)
{
	blink_cnt_can = 3;
	out_y0_cnt = 0;

	
	if(CAN_ID_S2D_M == RxMessage.StdId)
	{
		rxd_can_timeout = 0;
		rxd_can_timeout_m = 0;

		can_cnt_rx++;
		
		//mem_copy(can_master_data,RxMessage.Data,sizeof(can_master_data));
		can_master_data[0] = RxMessage.Data[0];
		
		can_master_data[1] = RxMessage.Data[1];
		can_master_data[2] = RxMessage.Data[2];
		can_master_data[3] = RxMessage.Data[3];
		can_master_data[4] = RxMessage.Data[4];
		can_master_data[5] = RxMessage.Data[5];
		can_master_data[6] = RxMessage.Data[6];
		can_master_data[7] = RxMessage.Data[7];                
		get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	
	}
	else if(CAN_ID_S2D_S == RxMessage.StdId)
	{
		rxd_can_timeout_s = 0;
		
		//mem_copy(can_slave_data,RxMessage.Data,sizeof(can_slave_data));
 		can_slave_data[0] = RxMessage.Data[0];
		
		can_slave_data[1] = RxMessage.Data[1];
		can_slave_data[2] = RxMessage.Data[2];
		can_slave_data[3] = RxMessage.Data[3];
		can_slave_data[4] = RxMessage.Data[4];
		can_slave_data[5] = RxMessage.Data[5];
		can_slave_data[6] = RxMessage.Data[6];
		can_slave_data[7] = RxMessage.Data[7];                 
		get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	
	}
	// 操作对象
	else if( (0x71 == RxMessage.StdId) || (0x72 == RxMessage.StdId) ||
		     (0x73 == RxMessage.StdId) || (0x74 == RxMessage.StdId) )
	{		
		rxd_can_timeout_req = 0;
		
		can_req_data[0] = RxMessage.Data[0];
		
		can_req_data[1] = RxMessage.Data[1];
		can_req_data[2] = RxMessage.Data[2];
		can_req_data[3] = RxMessage.Data[3];
		can_req_data[4] = RxMessage.Data[4];
		can_req_data[5] = RxMessage.Data[5];
		can_req_data[6] = RxMessage.Data[6];
		can_req_data[7] = RxMessage.Data[7];

		get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	
	}
}





void uart_proc_entry(rxd_uart_TypeDef *pt_rxd_data)
{
	unsigned char data_check;
	unsigned char p_can_txd[8];
	unsigned char p_door_length_sf[2];
	
	data_check = xor_check_sum(0,15,pt_rxd_data->rxd_uart_data);
	if( (0x87 == pt_rxd_data->rxd_uart_data[0]) &&
		  (data_check == pt_rxd_data->rxd_uart_data[16]) &&
		( 17 == pt_rxd_data->rxd_uart_length) )
	{
		rxd_scl_timeout = 0;
	    blink_cnt_scl = 3;
		mem_copy(rxd_buff_scl,pt_rxd_data->rxd_uart_data,17);
		
		// get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	

		// txd_start_scla(txd_scla.txd_uart_data,16);
		SCL1_TXEN(txd_scla.txd_uart_data,16);
                //SCL2_TXEN(16,txd_scla.txd_uart_data);
		// ------------------------------------------
		if(txd_scla.txd_uart_data[1]&0x03)	  // 轿内趋势bit1；厅外趋势bit0；
		{
                    // pg_t01
             
			// ROUT(ROUT_Y0_PIN_20_PIN,1);
		}
		else
		{
			// ROUT(ROUT_Y0_PIN_20_PIN,0);
		}
		// --------------------------------------
		p_can_txd[0] = rxd_buff_scl[1];
		p_can_txd[1] = rxd_buff_scl[2];
		p_can_txd[2] = rxd_buff_scl[3];
		p_can_txd[3] = 0;
		p_can_txd[4] = 0;
		p_can_txd[5] = 0;	
		p_can_txd[6] = rxd_buff_scl[7];
		p_can_txd[7] = 0;	
		// can_txd(&p_can_txd[0],CAN_ID_D2S_M);  // scl to can

		
		Can_tx_master.StdId = CAN_ID_D2S_M;
		mem_copy(Can_tx_master.Data,p_can_txd,8);
		time_out_can = 50*100;  // 100mS 立刻发送
		can_cnt_tx++;
		// ----------------------------------------
		p_can_txd[0] = rxd_buff_scl[4];
		p_can_txd[1] = rxd_buff_scl[5];
		p_can_txd[2] = rxd_buff_scl[6];
		p_can_txd[3] = 0;
		p_can_txd[4] = 0;
		p_can_txd[5] = 0;	
		p_can_txd[6] = rxd_buff_scl[7];
		p_can_txd[7] = 0;	
		// can_txd(&p_can_txd[0],CAN_ID_D2S_S);  // scl to can
		Can_tx_slave.StdId = CAN_ID_D2S_S;
		mem_copy(Can_tx_slave.Data,p_can_txd,8);
		// ----------------------------------------
		if(rxd_buff_scl[9])  // 存在操作对象
		{
			// can_txd(&(rxd_buff_scl[9]),rxd_buff_scl[9]); 
			Can_tx_object.StdId = rxd_buff_scl[9];
			mem_copy(Can_tx_object.Data,&rxd_buff_scl[9],8);
		}
		
		// -------------------------------------------
		door_data = rxd_buff_scl[3];

//								  // 地坎遮挡				 // 遗留物、儿童单独乘梯				 // 非关门到位 				
//		if(((txd_scla.txd_uart_data[1]&0x80) || (txd_scla.txd_uart_data[5]&0x30)) && (0 == (rxd_buff_scl[1]&0x20)))
//		{
//                        if(txd_scla.txd_uart_data[5]&0x20)
//                        {
//                          blink_mode_yiliuwu = 1;
//                        }
//                        else
//                        {
//                          blink_mode_yiliuwu = 0;
//                        }
//			blink_mode = 10;
//		}
                if((rxd_buff_scl[1]&0x80))    //指示灯闪烁
                {
                  blink_mode = 10;
                }
		else if( (rxd_buff_scl[1]&0x01) )	// 开门指令
		{
			blink_mode = 1;
		}
		else if( (0 == (rxd_buff_scl[1]&0x20) ) && (rxd_buff_scl[1]&0x02) )  // 关门指令
		{
			blink_mode = 2;
		}
		else if( (rxd_buff_scl[1]&0x20) ) // 关门到位
		{
			blink_mode = 3;
		}
		else
		{
			blink_mode = 0;
		}
                
                if((txd_scla.txd_uart_data[1]&0x03)&&(0==(rxd_buff_scl[1]&0x40)))  //主门趋势信号有效无关门输入按钮
                {
                  ROUT(ROUT_Y0_PIN_20_PIN,1);
                }
                else
                {
                  ROUT(ROUT_Y0_PIN_20_PIN,0);
                }
                
	}
	// 门机SCL数据
	else if( (0x8C == pt_rxd_data->rxd_uart_data[0]) && 
			 (0xA2 == pt_rxd_data->rxd_uart_data[1]) &&
			 ( 32 == pt_rxd_data->rxd_uart_length) )
	{
		// p_data_sf = ((pt_rxd_data->rxd_uart_data[3])&0x08);	// 光幕信号位 
	
		p_door_length_sf[0] = pt_rxd_data->rxd_uart_data[6];  // 6
		p_door_length_sf[1] = pt_rxd_data->rxd_uart_data[7];  // 7

		door_length_sf = ((p_door_length_sf[0]<<8) | (p_door_length_sf[1]));
		pt_rxd_data->rxd_uart_data[0] = 0;
		pt_rxd_data->rxd_uart_data[1] = 0;
	}
}


void rs485_proc_entry(rxd_uart_TypeDef *pt_rxd_data)
{
	unsigned char data_check;
	unsigned char p_can_txd[8];
	unsigned char p_door_length_sf[2];
        
        //SCL3_TXEN(16,txd_scla.txd_uart_data);
	
	data_check = xor_check_sum(0,15,pt_rxd_data->rxd_uart_data);
	if( (0x87 == pt_rxd_data->rxd_uart_data[0]) &&
		  (data_check == pt_rxd_data->rxd_uart_data[16]) &&
		( 17 == pt_rxd_data->rxd_uart_length) )
	{
		rxd_scl_timeout = 0;
	    blink_cnt_scl = 3;
		mem_copy(rxd_buff_scl,pt_rxd_data->rxd_uart_data,17);
		
		// get_scla_tdata_can(&txd_scla,can_master_data,can_slave_data,&can_req_data[0]);	

		// txd_start_scla(txd_scla.txd_uart_data,16);
		SCL2_TXEN(16,txd_scla.txd_uart_data);
		// ------------------------------------------
		if(txd_scla.txd_uart_data[1]&0x03)	  // 轿内趋势bit1；厅外趋势bit0；
		{
                    // pg_t01
             
			// ROUT(ROUT_Y0_PIN_20_PIN,1);
		}
		else
		{
			// ROUT(ROUT_Y0_PIN_20_PIN,0);
		}
		// --------------------------------------
		p_can_txd[0] = rxd_buff_scl[1];
		p_can_txd[1] = rxd_buff_scl[2];
		p_can_txd[2] = rxd_buff_scl[3];
		p_can_txd[3] = 0;
		p_can_txd[4] = 0;
		p_can_txd[5] = 0;	
		p_can_txd[6] = rxd_buff_scl[7];
		p_can_txd[7] = 0;	
		// can_txd(&p_can_txd[0],CAN_ID_D2S_M);  // scl to can

		
		Can_tx_master.StdId = CAN_ID_D2S_M;
		mem_copy(Can_tx_master.Data,p_can_txd,8);
		time_out_can = 50*100;  // 100mS 立刻发送
		can_cnt_tx++;
		
		
		// ----------------------------------------
		p_can_txd[0] = rxd_buff_scl[4];
		p_can_txd[1] = rxd_buff_scl[5];
		p_can_txd[2] = rxd_buff_scl[6];
		p_can_txd[3] = 0;
		p_can_txd[4] = 0;
		p_can_txd[5] = 0;	
		p_can_txd[6] = rxd_buff_scl[7];
		p_can_txd[7] = 0;	
		// can_txd(&p_can_txd[0],CAN_ID_D2S_S);  // scl to can

		/*
		Can_tx_slave.StdId = CAN_ID_D2S_S;
		mem_copy(Can_tx_slave.Data,p_can_txd,8);
		// ----------------------------------------
		if(rxd_buff_scl[9])  // 存在操作对象
		{
			// can_txd(&(rxd_buff_scl[9]),rxd_buff_scl[9]); 
			Can_tx_object.StdId = rxd_buff_scl[9];
			mem_copy(Can_tx_object.Data,&rxd_buff_scl[9],8);
		}
		*/
                
		Can_tx_slave.StdId = CAN_ID_D2S_S;
		mem_copy(Can_tx_slave.Data,p_can_txd,8);
		// ----------------------------------------
		if(rxd_buff_scl[9])  // 存在操作对象
		{
			// can_txd(&(rxd_buff_scl[9]),rxd_buff_scl[9]); 
			Can_tx_object.StdId = rxd_buff_scl[9];
			mem_copy(Can_tx_object.Data,&rxd_buff_scl[9],8);
		}                
		
		// -------------------------------------------
		door_data = rxd_buff_scl[3];

//								  // 地坎遮挡				 // 遗留物、儿童单独乘梯				 // 非关门到位 				
//		if(((txd_scla.txd_uart_data[1]&0x80) || (txd_scla.txd_uart_data[5]&0x30)) && (0 == (rxd_buff_scl[1]&0x20)))
//		{
//                        if(txd_scla.txd_uart_data[5]&0x20)
//                        {
//                          blink_mode_yiliuwu = 1;
//                        }
//                        else
//                        {
//                          blink_mode_yiliuwu = 0;
//                        }
//			blink_mode = 10;
//		}
                if((rxd_buff_scl[1]&0x80))    //指示灯闪烁
                {
                  blink_mode = 10;
                }                
		else if( (rxd_buff_scl[1]&0x01) )	// 开门指令
		{
			blink_mode = 1;
		}
		else if( (0 == (rxd_buff_scl[1]&0x20) ) && (rxd_buff_scl[1]&0x02) )  // 关门指令
		{
			blink_mode = 2;
		}
		else if( (rxd_buff_scl[1]&0x20) ) // 关门到位
		{
			blink_mode = 3;
		}
		else
		{
			blink_mode = 0;
		}
                
                if((txd_scla.txd_uart_data[1]&0x03)&&(0==(rxd_buff_scl[1]&0x40)))  //主门趋势信号有效无关门输入按钮
                {
                  ROUT(ROUT_Y0_PIN_20_PIN,1);
                }
                else
                {
                  ROUT(ROUT_Y0_PIN_20_PIN,0);
                }                
	}
	// 门机SCL数据
	else if( (0x8C == pt_rxd_data->rxd_uart_data[0]) && 
			 (0xA2 == pt_rxd_data->rxd_uart_data[1]) &&
			 ( 32 == pt_rxd_data->rxd_uart_length) )
	{
		// p_data_sf = ((pt_rxd_data->rxd_uart_data[3])&0x08);	// 光幕信号位 
	
		p_door_length_sf[0] = pt_rxd_data->rxd_uart_data[6];  // 6
		p_door_length_sf[1] = pt_rxd_data->rxd_uart_data[7];  // 7

		door_length_sf = ((p_door_length_sf[0]<<8) | (p_door_length_sf[1]));
		pt_rxd_data->rxd_uart_data[0] = 0;
		pt_rxd_data->rxd_uart_data[1] = 0;
	}
}





