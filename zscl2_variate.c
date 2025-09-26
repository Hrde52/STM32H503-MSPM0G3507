/*
 * File      : zscl2_variate.c
 *
 * Change Logs:
 *---------------------------------------------------------------------------------------
 * Date         |  Author    |   Notes
 *---------------------------------------------------------------------------------------
 * 2023-11-25   |  ³ÂÐÛÎ°	   |   the first version
 *---------------------------------------------------------------------------------------
 */

#include "zscl2_variate.h"

uint8_t 	Scl2TxBuf[60];
uint8_t 	Scl2RxBuf[60];
uint8_t 	Scl2RxBufx[60];
uint32_t 	Scl2TxPackNo;
uint32_t 	Scl2RxPackNo;
uint8_t  	Scl2RxNum; 
uint8_t  	Scl2TxNum; 
uint8_t  	Scl2DevErrJudge[128];
uint64_t 	Scl2DevComStatusH;
uint64_t 	Scl2DevComStatusL;
uint64_t 	Scl2RxCnt;
uint64_t 	Scl2RxErrCnt;
uint8_t   Scl2RxBufCnt;
uint8_t   Scl2RxBufCntX;
uint16_t  Scl2CommRate[128];
int8_t		Scl2CommOk[128];
uint16_t  Scl2led_num;

const device_trx_configure1 Scl2ConfigTbl[] =
{

};
uint32_t  const Scl2ConfigTblNum =	sizeof(Scl2ConfigTbl) / sizeof(Scl2ConfigTbl[0]);