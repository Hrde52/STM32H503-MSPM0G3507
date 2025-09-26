/*
 * File      : zscl2_process.h
 *
 * Change Logs:
 *---------------------------------------------------------------------------------------
 * Date         |  Author    |   Notes
 *---------------------------------------------------------------------------------------
 * 2023-11-25   |  ³ÂÐÛÎ°	   |   the first version
 *---------------------------------------------------------------------------------------
 */
#ifndef __zscl2_process_h__
#define __zscl2_process_h__

#include "typdef.h"
#include "define.h"

extern uint8_t xor_chk(uint8_t *verify_data, uint16_t verify_cnt);
extern uint8_t sum_chk(uint8_t *verify_data, uint16_t verify_cnt);
extern void SCL2_TXEN(uint8_t TxLength,uint8_t * src);

extern uint8_t 		Scl2TxBuf[60];
extern uint8_t 		Scl2RxBuf[60];
extern uint32_t 	Scl2TxPackNo;
extern uint32_t 	Scl2RxPackNo;
extern uint8_t  	Scl2RxNum; 
extern uint8_t  	Scl2TxNum; 
extern uint8_t  	Scl2DevErrJudge[128];
extern uint64_t 	Scl2DevComStatusH;
extern uint64_t 	Scl2DevComStatusL;
extern uint64_t 	Scl2RxCnt;
extern uint64_t 	Scl2RxErrCnt;
extern uint8_t   	Scl2RxBufCnt;
extern uint8_t   	Scl2RxBufCntX;
extern uint8_t  	Scl1TxRefreshTable1[400];	 
extern uint8_t  	Scl1RxRefreshTable1[400];
extern detecte  	Scl1CommRate[128];
extern uint16_t  	Scl2CommRate[128];
extern uint8_t 		Scl2RxBufx[60];
extern int8_t			Scl2CommOk[128];
extern int16_t		Clear_Com_rate;

extern uint64_t const bitset[64];
extern uint32_t const Scl1DeviceNum;
extern uint32_t const Scl1TrxTimingTblNum;
extern uint32_t const Scl1FormTxTblNum;
extern uint32_t const Scl1FormRxTblNum;
extern const device_trx_configure Scl1ConfigTbl[];
extern const device_trx_timing Scl1TimingTbl[];
extern const device_trx_form Scl1FormTxTbl[];
extern const device_trx_form Scl1FormRxTbl[];
extern const device_trx_configure1 Scl2ConfigTbl[];
extern uint32_t  const Scl2ConfigTblNum;
extern uint16_t  Scl2led_num;
extern uint8_t   Version;
// ****************************************************************************************
#endif
