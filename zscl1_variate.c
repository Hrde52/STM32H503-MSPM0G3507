/*
 * File      : zscl1_variate.c
 *
 * Change Logs:
 *---------------------------------------------------------------------------------------
 * Date         |  Author    |   Notes
 *---------------------------------------------------------------------------------------
 * 2023-11-25   |  陈雄伟	   |   the first version
 *---------------------------------------------------------------------------------------
 */

#include "zscl1_variate.h"

uint8_t	 Scl1TxBuf[60];
uint8_t  Scl1RxBuf[60];
uint32_t Scl1TxPackNo;
uint32_t Scl1RxPackNo;
uint8_t  Scl1RxNum; 
uint8_t  Scl1TxNum; 
uint8_t  Scl1DevErrJudge[128];
uint64_t Scl1DevComStatusH;
uint64_t Scl1DevComStatusL;
uint8_t  Scl1TxRefreshTable1[400];	 
uint8_t  Scl1RxRefreshTable1[400];
uint64_t Scl1RxCnt;
uint64_t Scl1RxHeadErrCnt;
uint64_t Scl1RxSumErrCnt;
uint64_t Scl1RxXorErrCnt;
detecte  Scl1CommRate[128];
uint8_t  Scl1RxBufCnt;
uint8_t  Scl1RxBufCntX;
uint8_t  Scl1RxBufCntXX;
uint8_t  Scl1RxBufx[60];
uint8_t  Scl1ErrBuf[64][2];
uint8_t  Scl1ErrBufCnt;
uint16_t Scl1led_num;

uint64_t const bitset[64]=
{
  0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,
  0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080,
  0x0000000000000100,0x0000000000000200,0x0000000000000400,0x0000000000000800,
  0x0000000000001000,0x0000000000002000,0x0000000000004000,0x0000000000008000,
  0x0000000000010000,0x0000000000020000,0x0000000000040000,0x0000000000080000,
  0x0000000000100000,0x0000000000200000,0x0000000000400000,0x0000000000800000,
  0x0000000001000000,0x0000000002000000,0x0000000004000000,0x0000000008000000,
  0x0000000010000000,0x0000000020000000,0x0000000040000000,0x0000000080000000,
  0x0000000100000000,0x0000000200000000,0x0000000400000000,0x0000000800000000,
  0x0000001000000000,0x0000002000000000,0x0000004000000000,0x0000008000000000,
  0x0000010000000000,0x0000020000000000,0x0000040000000000,0x0000080000000000,
  0x0000100000000000,0x0000200000000000,0x0000400000000000,0x0000800000000000,
  0x0001000000000000,0x0002000000000000,0x0004000000000000,0x0008000000000000,
  0x0010000000000000,0x0020000000000000,0x0040000000000000,0x0080000000000000,
  0x0100000000000000,0x0200000000000000,0x0400000000000000,0x0800000000000000,
  0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000
};
const device_trx_configure Scl1ConfigTbl[] =																								// 设备发送接收配置表
{

};
uint32_t  const Scl1DeviceNum =	sizeof(Scl1ConfigTbl) / sizeof(Scl1ConfigTbl[0]);

const device_trx_timing Scl1TimingTbl[] = 																								// 设备发送接收实时表
{

};
uint32_t const Scl1TrxTimingTblNum =	sizeof(Scl1TimingTbl) / sizeof(Scl1TimingTbl[0]);

const device_trx_form Scl1FormTxTbl[] =																											// 设备Tx数据帧格式表
{

};
uint32_t  const Scl1FormTxTblNum =	sizeof(Scl1FormTxTbl) / sizeof(Scl1FormTxTbl[0]);

const device_trx_form Scl1FormRxTbl[] = 																										// 设备Rx数据帧格式表
{

};
uint32_t  const Scl1FormRxTblNum =	sizeof(Scl1FormRxTbl) / sizeof(Scl1FormRxTbl[0]);	

