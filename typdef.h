// #include "typdef.h"



#ifndef __typedef_h__
#define __typedef_h__

#include "stdint.h"

typedef struct
{
	uint8_t  device_no;																				// 设备号
	uint16_t tx_addr;																					// Tx数据帧格式起始地址
	uint8_t  tx_length;																				// Tx数据帧长度
	uint16_t rx_addr;																					// Rx数据帧格式起始地址
	uint8_t  rx_length;																				// Rx数据帧长度
}device_trx_configure;																			// 设备发送接收配置表结构体定义

typedef struct
{
	uint8_t  device_no;																				// 数据类型
	uint16_t timing_value;																		// 时间间隔
}device_trx_timing;																					// 设备发送接收时序表结构体定义

typedef struct
{
	uint8_t  data_type;																				// 数据类型
	uint16_t data_value;																			// 数据值
}device_trx_form;																						// 设备Tx/Rx数据帧格式表结构体定义

typedef struct
{
	uint8_t  device_no;
	uint8_t  head;
	uint8_t  length;
}device_trx_configure1;

typedef struct      
{
	uint64_t SentCnt;						// 发送次数
	uint64_t ReceiveCnt;				// 接收次数
	uint64_t SentCntx;
	uint64_t ReceiveCntx;
	uint16_t mRateNow;				  // 通信成功率现在值
	uint16_t mRateEvil;				  // 通信成功率最恶值
	uint16_t mRateBest;				  // 通信成功率最良值
	uint16_t mRateAverage;		  // 通信成功率平均值
	uint16_t cycle;
	uint16_t detectecnt;
	uint8_t  OkFlag;						// 通信状态信息
	uint8_t  ErrorCount;				// 错误状态信息
}detecte;
// ****************************************************************************************


typedef struct
{
	unsigned char rxd_uart_length;
	unsigned char rxd_uart_cnt;
	unsigned char rxd_uart_data[64];
	unsigned char rxd_uart_idle;
	unsigned char rxd_uart_channel;
}rxd_uart_TypeDef;

//----------------------------------------------------
typedef struct
{
	unsigned char txd_uart_length;
	unsigned char txd_uart_cnt;
	unsigned char txd_uart_data[64];
	unsigned char txd_uart_idle;
}txd_uart_TypeDef;


typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be received. This parameter can be a value of 
                        @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to 
                        0xFF. */

  uint8_t FMI;     /*!< Specifies the index of the filter the message stored in 
                        the mailbox passes through. This parameter can be a 
                        value between 0 to 0xFF */
} CanRxMsg;






#endif
