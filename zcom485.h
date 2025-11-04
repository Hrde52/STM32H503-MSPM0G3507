#ifndef __zcom485_h__
#define __zcom485_h__

#include "typdef.h"
#include "define.h"
#include "stdlib.h"
#include "zscl_logic.h"
#include "string.h"
#include <stdio.h>

#define VERSION      "V1.0.0" //"V1.0.0.1"

#define COMM_VERSION    1
#define ENCRY_VERSION   2

#define COM_FRAME_REC_HEAD 0x8A
#define COM_FRAME_SEND_HEAD 0xA8
#define COM_HEARTBEAT_CMD 0
#define COM_SHAKEHAND_CMD 0x02
#define COM_SETUP_CONFIG_CMD 0x03
#define COM_TEST_END_CMD 0x04
#define COM_TEST_RESULT_CMD 0x05
#define COM_SET_CODE_CMD 0x06
#define COM_AUTHORIZATION_CMD 0x08
#define COM_SEND_VER_ID_CMD 0x0A
#define COM_REQEST_CERT_CMD 0x0B
#define COM_SEND_CERT_CMD 0x0C
#define COM_ERROR_REPLAY_CMD 0x07

#define ProjectKeyString "c80823a34726f978e2fadc57eaa4b4c8"
#define CONFIG_ID_LIC_PATH "/userdata/config"

#define TEST_FRAME_HEAD 0x9A
#define TEST_SCL_HEAD 0x31
#define TEST_CAN_ID 0x41
#define TEST_485A_HEAD1 0x51
#define TEST_485A_HEAD 0x61
#define TEST_485B_HEAD 0x62

#define BIT(x)                       ((uint8_t)((uint8_t)0x01U<<(x)))

static const uint8_t TxRand[16] =
{  
   10,9,0,31,28,27,24,3,7,25,14,19,6,23,16,5
};
static const uint8_t RxRand[16] =
{   
    25,20,17,1,14,10,13,4,3,2,19,15,18,9,12,16
};

static const unsigned char TxLicRand[16] =
{  
    17,1,14,8,30,5,31,12,16,28,18,13,26,7,29,25
};

static const unsigned char RxLicRand[16] =
{
    3,7,25,23,16,14,22,28,29,20,8,31,30,4,19,2  
};
static const uint8_t ProjNameBuf[8] = 
{
  0x02, 0x04, 0x02,  0x02, 0x00, 0x01, 0x00, 0x00
    //0x02, 0x02, 0x00,  0x03, 0x00, 0x00, 0x00, 0x02
};

static const uint8_t ProjNameBuf_B[8] = 
{
    0x02, 0x02, 0x00,  0x03, 0x00, 0x00, 0x00, 0x03
};

enum TestState { READY = 0, START, AUTHOR, RESULT, END };
enum boardTS { RS485A_STEP = 0, SCL_STEP,CAN_STEP, RS485B_STEP,IO_IN_STEP, IO_OUT_STEP,IO_OUT_STEP1,TEST_DONE };

typedef struct
{
    uint8_t mFrHead;
    uint8_t mLenh;     /*from ver*/
    uint8_t mLenl;     
    uint8_t mVer;
    uint8_t mBk[2];
    uint8_t mCmd;
    uint8_t nData[64];
    uint8_t mxor;
    uint16_t msum;
    uint8_t msendData[64];
}ComMsgData;

typedef struct 
{
	uint8_t empty;
	uint8_t data[4];
}id_code;

typedef struct
{
  uint8_t B_version;
  uint8_t finish;
  uint8_t test_step;
  uint8_t rxd_flag;
  uint8_t scl_check;
  uint8_t can_flag;
  uint8_t can_check;  
  uint8_t rs485a_flag;
  uint8_t rs485a_check;    
  uint8_t rs485b_flag;
  uint8_t rs485b_check;    
  uint8_t io_value; 
  uint8_t timer_cnt;
  uint8_t mFrHead;
  uint8_t mxor;
  uint16_t msum;
  uint8_t msendData[64];
}TestMsg;

typedef union 
{
  struct
  {    
    uint8_t X0_bit:1;  
    uint8_t X1_bit:1;  
    uint8_t X2_bit:1; 
    uint8_t X3_bit:1;
    uint8_t X4_bit:1;
    uint8_t X5_bit:1;
    uint8_t X6_bit:1;
    uint8_t X7_bit:1;
  }bit;
  uint8_t all;
}IO_TS_BITS;


typedef union 
{
  struct
  {    
    uint16_t scl_err:1;  
    uint16_t can_err:1;  
    uint16_t rs485a_err:1; 
    uint16_t rs485b_err:1;
    uint16_t ix0_err:1;
    uint16_t ix1_err:1;
    uint16_t ix2_err:1;
    uint16_t ix3_err:1;
    uint16_t ix4_err:1;
    uint16_t ix5_err:1;
    uint16_t ix6_err:1;
    uint16_t ix7_err:1;   
    uint16_t y3_err:1;   
    uint16_t y4_err:1; 
    uint16_t y5_err:1;  
    uint16_t y6_err:1;  
  }bit;
  uint16_t all;
}SIG_ERR_BITS;

// TFD板卡数据结构（6个检测点）
typedef struct {
    uint8_t board_id;    // 板卡ID: 1或2
    uint8_t status[6];   // 6个检测点状态，0=正常，1=异常
} TFD_BOARD_DATA;

// ND06板卡数据结构（2个检测点）  
typedef struct {
    uint8_t board_id;    // 板卡ID: 1或2
    uint8_t status[2];   // 2个检测点状态，0=正常，1=异常
} ND06_BOARD_DATA;


typedef union 
{
  struct
  {    
    uint16_t TFD1_485_1:1;  
    uint16_t TFD1_485_2:1;  
    uint16_t TFD1_DTS6012:1; 
    uint16_t TFD1_ND06:1;
    uint16_t TFD1_IO:1;
    uint16_t TFD1_X:1;
    
    uint16_t TFD2_485_1:1;  
    uint16_t TFD2_485_2:1;  
    uint16_t TFD2_DTS6012:1; 
    uint16_t TFD2_ND06:1;
    uint16_t TFD2_IO:1;
    uint16_t TFD2_X:1;
      
    uint16_t ND06_1:1;   
    //uint16_t ND06LED_1:1; 
    
    uint16_t ND06_2:1;   
    //uint16_t ND06LED_2:1;  
  }bit;
  uint16_t all;
}SIG_TERR_BITS;

// 整合TFD板卡错误状态
void integrate_tfd_error(const TFD_BOARD_DATA* tfd_data);
// 整合ND06板卡错误状态
void integrate_nd06_error(const ND06_BOARD_DATA* nd06_data);

typedef union 
{
  struct
  {    
    uint8_t y0_err:1;  
    uint8_t y1_err:1; 
    uint8_t y2_err:1; 
    uint8_t power_err:1; 
    uint8_t rsd:4;
  }bit;
  uint8_t all;
}YOUT_ERR_BIT;

extern TestMsg  mtestmsg;
extern IO_TS_BITS io_test_bit;
extern IO_TS_BITS io_in_bit;
extern SIG_ERR_BITS  board_err;
extern SIG_TERR_BITS  board4_err;
extern YOUT_ERR_BIT  yo_err_bit;

extern uint8_t homework_switch1;
extern uint8_t homework_switch2;
extern uint8_t homework_switch3;

extern uint16_t m_send_message_times1;
extern uint16_t m_send_message_times2;
extern uint16_t in_times;
extern uint16_t in2_times;
extern uint8_t getRspHSTFD1;
extern uint8_t getRspHSTFD2;
extern uint8_t getRspNd061;
extern uint8_t getRspNd062;
extern uint8_t getRspTFD11;
extern uint8_t getRspTFD12;
extern uint8_t getRspTFD21;
extern uint8_t getRspTFD22;


extern uint8_t rxTFD1[15] ;  
extern uint8_t rxTFD2[15] ;
extern uint8_t rxND1[6] ;
extern uint8_t rxND2[6] ;
extern uint8_t rxBuffT[20];

extern uint8_t selectTFD ;

void send_test_end(void);
void send_test_result(const bool mState);
// ****************************************************************************************
#endif