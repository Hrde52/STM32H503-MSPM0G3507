/*
 * File      : zscl1_variate.h
 *
 * Change Logs:
 *---------------------------------------------------------------------------------------
 * Date         |  Author    |   Notes
 *---------------------------------------------------------------------------------------
 * 2023-11-25   |  ³ÂÐÛÎ°	   |   the first version
 *---------------------------------------------------------------------------------------
 */
#ifndef __zscl1_variate_h__
#define __zscl1_variate_h__

#include "typdef.h"
#include "define.h"







// extern void SCL1_TXEN(uint8_t TxLength,uint8_t * dest);
extern void SCL1_TXEN(uint8_t * dest,uint8_t TxLength);

extern void Scl1set_n100us(uint32_t n);

extern uint8_t Scl1TxBuf[60];
extern uint8_t Scl1RxBuf[60];
extern uint32_t Scl1TxPackNo;
extern uint32_t Scl1RxPackNo;
extern uint8_t  Scl1RxNum;
extern uint8_t  Scl1TxNum; 
extern uint8_t  Scl1DevErrJudge[128];
extern uint64_t Scl1DevComStatusH;
extern uint64_t Scl1DevComStatusL;
extern uint8_t  Scl1TxRefreshTable1[400];	 
extern uint8_t  Scl1RxRefreshTable1[400];
extern uint64_t Scl1RxCnt;
extern uint64_t Scl1RxHeadErrCnt;
extern uint64_t Scl1RxSumErrCnt;
extern uint64_t Scl1RxXorErrCnt;
extern detecte  Scl1CommRate[128];
extern uint8_t   Scl1RxBufCnt;
extern uint8_t   Scl1RxBufCntX;
extern uint8_t   Scl1RxBufCntXX;
extern uint8_t Scl1RxBufx[60];
extern uint8_t  Scl1ErrBuf[64][2];
extern uint8_t  Scl1ErrBufCnt;
extern uint16_t  Scl1led_num;

extern uint64_t const bitset[64];
extern uint32_t const Scl1DeviceNum;
extern uint32_t const Scl1TrxTimingTblNum;
extern uint32_t const Scl1FormTxTblNum;
extern uint32_t const Scl1FormRxTblNum;
extern const device_trx_configure Scl1ConfigTbl[];
extern const device_trx_timing Scl1TimingTbl[];
extern const device_trx_form Scl1FormTxTbl[];
extern const device_trx_form Scl1FormRxTbl[];
// ****************************************************************************************
#endif
