#include "zcom485.h"
#include "stdlib.h"
#include "zscl_logic.h"
extern void SCL1_TXEN(uint8_t * src,uint8_t TxLength);
extern void SCL2_TXEN(uint8_t TxLength,uint8_t * src);
extern void SCL3_TXEN(uint8_t TxLength,uint8_t * src);
extern void can_txd_start(unsigned char tx[],unsigned char p_StdId);
extern rxd_uart_TypeDef rxd_uart2;
void board_test(void);

ComMsgData m_p_msg;
ComMsgData pData;
TestMsg  mtestmsg;
IO_TS_BITS io_test_bit;
IO_TS_BITS io_in_bit;
SIG_ERR_BITS  board_err;
YOUT_ERR_BIT  yo_err_bit;
id_code m_id_code;
uint8_t m_bk[2];
uint8_t m_test_state = 0;
uint16_t m_send_shake_hand_times = 0;
uint16_t m_send_times = 0;
uint16_t m_send_heart_beat_times = 0;

uint8_t cal_xor_value(const uint8_t *p_data, const uint16_t m_len)
{
  uint8_t m_xor = 0;
  uint8_t mValue = 0;
  
  for (uint16_t k = 0; k < m_len; k++)
  {
    mValue = *p_data++;
    
    m_xor = m_xor ^ mValue;
  }
  return m_xor;
}

uint16_t cal_sum_value(const uint8_t *p_data, const uint16_t m_len)
{
  uint16_t m_sum = 0;
  
  uint8_t mValue = 0;
  
  for (uint16_t k = 0; k < m_len; k++)
  {
    mValue = *p_data++;
    m_sum = m_sum + mValue;
  }
  return m_sum;
}



void send_shake_hand(void)
{
  m_p_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_p_msg.mVer = COMM_VERSION;
  
  m_p_msg.mBk[0] = rand() % 9 + 1;
  m_p_msg.mBk[1] = rand() % 9 + 1;
  
  m_p_msg.mLenl = 13;
  m_p_msg.mLenh = 0;
  m_p_msg.mCmd = COM_SHAKEHAND_CMD;
  m_p_msg.nData[0] = 8;
  if(mtestmsg.B_version==0)
  {
    mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&ProjNameBuf, 8);
  }
  else
  {
    mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&ProjNameBuf_B, 8);
  }
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff;
  
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);
}

void send_heart_beat(void)
{
  m_p_msg.mFrHead = COM_FRAME_REC_HEAD;
  m_p_msg.mLenl = 6;
  m_p_msg.mLenh = 0;
  m_p_msg.mVer = COMM_VERSION;
  m_p_msg.mBk[0] = m_bk[0];
  m_p_msg.mBk[1] = m_bk[1];
  
  m_p_msg.mCmd = COM_HEARTBEAT_CMD;
  m_p_msg.nData[0] = 1;
  m_p_msg.nData[1] = 0xAC;
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff;  
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);
}

void send_test_end(void)
{
  m_p_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_p_msg.mVer = COMM_VERSION;
  
  m_p_msg.mBk[0] = m_bk[0];
  m_p_msg.mBk[1] = m_bk[1];
  
  m_p_msg.mLenl = 13;
  m_p_msg.mLenh = 0;
  
  m_p_msg.mCmd = COM_TEST_END_CMD;
  m_p_msg.nData[0] = 8;
  if(mtestmsg.B_version==0)
  {
    mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&ProjNameBuf, 8);
  }
  else
  {
    mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&ProjNameBuf_B, 8);
  }  
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff; 
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);  
  
}

void send_test_result(const bool mState)
{
  m_p_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_p_msg.mVer = COMM_VERSION;
  m_p_msg.mBk[0] = m_bk[0];
  m_p_msg.mBk[1] = m_bk[1];
  
  m_p_msg.mLenl = 29;
  m_p_msg.mLenh = 0;
  m_p_msg.mCmd = COM_TEST_RESULT_CMD;
  m_p_msg.nData[0] = 1;
  if (mState)
  {
    m_p_msg.nData[1] = 1;
  }
  else
  {
    m_p_msg.nData[1] = 0;
  }
  /*L2*/
  m_p_msg.nData[2] = 1;
  m_p_msg.nData[3] = 1;
  
  /*L3 */
  m_p_msg.nData[4] = 4;
  mem_copy((uint8_t *)&m_p_msg.nData[5], 0, 4);
  m_p_msg.nData[8] = board_err.all&0x00ff;
  m_p_msg.nData[7] = (board_err.all&0xff00)>>8;
  m_p_msg.nData[6] = yo_err_bit.all;
   
  /*L4*/
  m_p_msg.nData[9] = 1;
  m_p_msg.nData[10] = 0;
  
  /*L5*/
  m_p_msg.nData[11] = 4;
  mem_copy((uint8_t *)&m_p_msg.nData[12], m_id_code.data, 4);
  
  /*L6*/
  m_p_msg.nData[16] = 8;
  mem_copy((uint8_t *)&m_p_msg.nData[17], VERSION, sizeof(VERSION));
  
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff;  
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);
}

void request_set_code(void)
{
  m_p_msg.mFrHead = COM_FRAME_SEND_HEAD;
  
  m_p_msg.mVer = COMM_VERSION;
  
  m_p_msg.mBk[0] = m_bk[0];
  m_p_msg.mBk[1] = m_bk[1];
  
  // m_p_len = m_p_len + 2;
  m_p_msg.mCmd = COM_SET_CODE_CMD;
  m_p_msg.nData[0] = 1;
  /*request id code command   number 1 */
  m_p_msg.nData[1] = 2;
  m_p_msg.nData[2] = 1;
  
  m_id_code.empty = 1;
  
  if (m_id_code.empty)
  {
    m_p_msg.nData[3] = 1; /*system no code id*/
    m_p_msg.mLenl = 8;
    m_p_msg.mLenh = 0;
  }
  else
  {
    m_p_msg.nData[3] = 0;
    m_p_msg.nData[4] = 4;
    mem_copy((uint8_t *)&m_p_msg.nData[5], m_id_code.data, 4);
    m_p_msg.mLenl = 13;
    m_p_msg.mLenh = 0;   
  }
  
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff;
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);
}


void request_authorize_fun(void)
{
  m_p_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_p_msg.mVer = COMM_VERSION;
  m_p_msg.mBk[0] = m_bk[0];
  m_p_msg.mBk[1] = m_bk[1];
  m_p_msg.mLenl = 22;
  m_p_msg.mLenh = 0;
  m_p_msg.mCmd = COM_AUTHORIZATION_CMD;
  m_p_msg.nData[0] = 8;
  //mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&m_p_key.licTxrand, 8);  
  mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&TxLicRand, 8);
  //mem_copy((uint8_t *)&m_p_msg.nData[1], 0, 8);
  m_p_msg.nData[9] = 1;
  m_p_msg.nData[10] = 2; /*条形码1、ID码2*/
  m_p_msg.nData[11] = 1;
  m_p_msg.nData[12] = 1; /*条形码1、ID码2*/
  m_p_msg.nData[13] = 4; /*条形码长度、ID码个数*/
  mem_copy((uint8_t *)&m_p_msg.nData[14], m_id_code.data, 4);
  
  /*   add xor sum value   */
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff; 
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);
}


void send_error_replay(const uint8_t mCode)
{
  m_p_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_p_msg.mVer = COMM_VERSION;
  m_p_msg.mBk[0] = m_bk[0];
  m_p_msg.mBk[1] = m_bk[1];
  
  m_p_msg.mLenl = 6;
  m_p_msg.mLenh = 0;
  m_p_msg.mCmd = COM_ERROR_REPLAY_CMD;
  m_p_msg.nData[0] = 1;
  m_p_msg.nData[0] = mCode;
  
  mem_copy((uint8_t *)&m_p_msg.msendData[0], (uint8_t *)&m_p_msg.mFrHead,m_p_msg.mLenl+3);
  
  m_p_msg.mxor = cal_xor_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  m_p_msg.msum = cal_sum_value((uint8_t *)&m_p_msg.msendData[1],m_p_msg.mLenl+2);
  
  m_p_msg.msendData[m_p_msg.mLenl+3] = m_p_msg.mxor;
  m_p_msg.msendData[m_p_msg.mLenl+4] = (m_p_msg.msum&0xff00)>>8;
  m_p_msg.msendData[m_p_msg.mLenl+5] = m_p_msg.msum&0x00ff;   
  SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);    
  
}


/*check received frame data */
bool handle_com_data()
{
  bool res = false;
  
  uint8_t mXor = 0;
  uint16_t mSum = 0;
  uint16_t mLen = rxd_uart2.rxd_uart_cnt;
  
  if (mLen < 5)
  {
    res = false;
    return res;
  }
  
  pData.mFrHead = rxd_uart2.rxd_uart_data[0];
  pData.mLenh = rxd_uart2.rxd_uart_data[1];
  pData.mLenl = rxd_uart2.rxd_uart_data[2];
  pData.mVer = rxd_uart2.rxd_uart_data[3];
  pData.mBk[0] = rxd_uart2.rxd_uart_data[4];
  pData.mBk[1] = rxd_uart2.rxd_uart_data[5];
  pData.mCmd = rxd_uart2.rxd_uart_data[6];
  
  mem_copy((uint8_t *)&pData.nData[0], &rxd_uart2.rxd_uart_data[7],9);
  
  pData.mxor = rxd_uart2.rxd_uart_data[mLen-3];
  pData.msum = (uint16_t)(rxd_uart2.rxd_uart_data[mLen-2]<<8)+rxd_uart2.rxd_uart_data[mLen-1];
  
  if (COM_FRAME_REC_HEAD != pData.mFrHead)
  {
    res = false;
    return res;
  }
  
  mXor = cal_xor_value((uint8_t *)&rxd_uart2.rxd_uart_data[1],mLen-4);
  mSum = cal_sum_value((uint8_t *)&rxd_uart2.rxd_uart_data[1],mLen-4);
  
  if ((mXor != pData.mxor) || (mSum != pData.msum))
  { 
    res = false;
    return res;
  }
  
  switch (pData.mCmd)
  {
  case COM_SHAKEHAND_CMD:
    {
      m_test_state = START;
      m_bk[0] = pData.mBk[0];
      m_bk[1] = pData.mBk[1];
      res = true;
      request_set_code();
      break;
    }
  case COM_SETUP_CONFIG_CMD:
    res = true;
    break;
  case COM_TEST_END_CMD:
    {
      m_test_state = END;    
      res = true;
      break;
    }
  case COM_TEST_RESULT_CMD:
    {
      m_test_state = RESULT;
      res = true;
      send_test_end();
      break;
    }
  case COM_SET_CODE_CMD:
    {       
      //m_id_code = std::string((char *)&pData.nData[5], 4);
      //write_file_code(ID_CODE_NAME_PATH, m_id_code.data());
      mem_copy((uint8_t *)&m_id_code.data[0], (uint8_t *)&pData.nData[5],4);
      //request_authorize_fun();
      m_test_state = AUTHOR;
      res = true;
      break;
    }
  case COM_AUTHORIZATION_CMD:
    {   
      m_test_state = AUTHOR;
      res = true;
      //write_file_code(LICESE_NAME_PATH, "COM_AUTHORIZATION");
      //m_send_heart_beat_times = 0;
      break;
    }
  case COM_SEND_VER_ID_CMD:
    res = true;
    break;
  case COM_REQEST_CERT_CMD:
    res = true;
    break;
  case COM_SEND_CERT_CMD:
    res = true;
    break;
  default:
    res = true;
    break;
  }
  
  return res;
}



void boardtest_loop_process()
{
  if ((m_send_shake_hand_times < 3) && (m_test_state == READY))
  {
    board_IX5 = DL_GPIO_readPins(IX5_PORT,IX5_PIN_14_PIN);
    board_IX6 = DL_GPIO_readPins(IX6_PORT,IX6_PIN_15_PIN);
    if(board_IX6==0)
    {
      mtestmsg.B_version = 1;
    }
      
    m_send_times++;
    if ((0 == (m_send_times % 10)) && (m_send_times > 40))
    {
      send_shake_hand();
      m_send_shake_hand_times++;
    }
  }
//  if(m_test_state == READY)
//  {
//    send_shake_hand();
//  }
  if (m_test_state == AUTHOR)
  {
    if( mtestmsg.finish==0)
    {
      if(0 == (m_send_times++ % 5))
      {
        send_heart_beat();
      }
      board_test();
    }
    else
    {
      bool rep = true;
      if(board_err.all==0)
      {
        rep = true;
      }
      else
      {
        rep = false;
      }
      
      send_test_result(rep);
    }
  }
}

  uint32_t io4_read;
void board_test(void)
{
  uint8_t i;
  uint8_t io4_readtmp;
  uint8_t io4_readtmp2;
  io4_read = DL_GPIO_readPins(IX4_PORT,IX4_PIN_13_PIN);
  switch(mtestmsg.test_step)
  {
  case RS485A_STEP:
    {
      mtestmsg.timer_cnt++;
      if(mtestmsg.timer_cnt%2)
      {
        mtestmsg.msendData[0] = TEST_FRAME_HEAD;
        mtestmsg.msendData[1] = TEST_485A_HEAD1;
        mtestmsg.msendData[2] = mtestmsg.timer_cnt;
        mtestmsg.msendData[3] = xor_check_sum(0,2,mtestmsg.msendData);
      }
      else
      {
        mtestmsg.msendData[0] = TEST_FRAME_HEAD;
        mtestmsg.msendData[1] = TEST_485A_HEAD;
        mtestmsg.msendData[2] = mtestmsg.timer_cnt;
        mtestmsg.msendData[3] = xor_check_sum(0,2,mtestmsg.msendData);        
      }
      SCL2_TXEN(4,mtestmsg.msendData);
      
      if(mtestmsg.rs485a_flag==1)
      {
      	mtestmsg.rs485a_flag = 0;
      	mtestmsg.rs485a_check = 1;
      }
      if(mtestmsg.timer_cnt==100)
      {
        mtestmsg.test_step = SCL_STEP;
        mtestmsg.timer_cnt = 0;
      }
      
      break;  		
    }
    
  case SCL_STEP:
    {
      io4_readtmp = DL_GPIO_readPins(IX4_PORT,IX4_PIN_13_PIN)>0? 1:0;
      mtestmsg.timer_cnt++;
      mtestmsg.msendData[0] = TEST_FRAME_HEAD;
      mtestmsg.msendData[1] = TEST_SCL_HEAD;
      mtestmsg.msendData[2] = mtestmsg.timer_cnt;
      mtestmsg.msendData[3] = xor_check_sum(0,2,mtestmsg.msendData);
      SCL1_TXEN(mtestmsg.msendData,4);
      
      if(mtestmsg.rxd_flag==1)
      {
      	mtestmsg.rxd_flag = 0;
      	mtestmsg.scl_check = 1;
      }
      
      if(mtestmsg.timer_cnt==50)
      {
        mtestmsg.test_step = CAN_STEP;
        mtestmsg.timer_cnt = 0;
      }
      
      break;
    }
  case CAN_STEP:
    {
      io4_readtmp = DL_GPIO_readPins(IX4_PORT,IX4_PIN_13_PIN)>0? 1:0;
      mtestmsg.timer_cnt++;
      Can_tx_boardtest.StdId = TEST_CAN_ID;
      for(i=0;i<8;i++)
      {
        Can_tx_boardtest.Data[i] = i;
      }
      can_txd_start(Can_tx_boardtest.Data,(unsigned char)Can_tx_boardtest.StdId);
      Can_tx_boardtest.StdId = 0;
      
      if(mtestmsg.can_flag==1)
      {
        mtestmsg.can_flag	=	0;
        mtestmsg.can_check = 1;
      }
      
      if(mtestmsg.timer_cnt==50)
      {
        mtestmsg.test_step = RS485B_STEP;
        mtestmsg.timer_cnt = 0;
      }
      break;
    }

  case RS485B_STEP:
    {
      ROUT(ROUT_Y0_PIN_20_PIN,1);
      mtestmsg.timer_cnt++;
      mtestmsg.msendData[0] = TEST_FRAME_HEAD;
      mtestmsg.msendData[1] = TEST_485B_HEAD;
      mtestmsg.msendData[2] = mtestmsg.timer_cnt;
      mtestmsg.msendData[3] = xor_check_sum(0,2,mtestmsg.msendData);
      SCL2_TXEN(4,mtestmsg.msendData);
      
      if(mtestmsg.rs485b_flag==1)
      {
      	mtestmsg.rs485b_flag = 0;
      	mtestmsg.rs485b_check = 1;
      }
      if(mtestmsg.timer_cnt==50)
      {
        mtestmsg.test_step = IO_IN_STEP;
        mtestmsg.timer_cnt = 0;
      }
      
      break;  		
    }  	
  case IO_IN_STEP:
    {
      io_test_bit.all = mtestmsg.io_value;
      mtestmsg.test_step = IO_OUT_STEP;
      break;  		
    } 
    
  case IO_OUT_STEP:
    {
      ROUT(ROUT_Y3_PIN_6_PIN,1);
      
      io_in_bit.bit.X0_bit = DL_GPIO_readPins(IX0_PORT,IX0_PIN_9_PIN)>0? 1:0;
      io_in_bit.bit.X1_bit = DL_GPIO_readPins(IX1_PORT,IX1_PIN_10_PIN)>0? 1:0;
      io_in_bit.bit.X2_bit = DL_GPIO_readPins(IX2_PORT,IX2_PIN_11_PIN)>0? 1:0;
      io_in_bit.bit.X3_bit = DL_GPIO_readPins(IX3_PORT,IX3_PIN_12_PIN)>0? 1:0;
      io_in_bit.bit.X7_bit = DL_GPIO_readPins(IX7_PORT,IX7_PIN_16_PIN)>0? 1:0;  
      
      yo_err_bit.bit.y0_err = ~io_in_bit.bit.X1_bit;
      yo_err_bit.bit.y1_err = io_in_bit.bit.X2_bit&(~io_in_bit.bit.X3_bit);
      yo_err_bit.bit.y2_err  =  io_in_bit.bit.X7_bit;
      
//      yo_err_bit.bit.y0_err = io_in_bit.bit.X1_bit;  //低 Y0
//      yo_err_bit.bit.y1ON_err = io_in_bit.bit.X2_bit;  //高 Y1
//      yo_err_bit.bit.y1CL_err = io_in_bit.bit.X3_bit;  //低 Y1
//      yo_err_bit.bit.y2_err = io_in_bit.bit.X7_bit;  //高 Y2
      
      
      mtestmsg.timer_cnt++;
      if(mtestmsg.timer_cnt==5)
      {
        mtestmsg.timer_cnt = 0;
        mtestmsg.test_step = IO_OUT_STEP1;
      }
      
      break;  		
    }  
    
  case IO_OUT_STEP1:
    {
      ROUT(ROUT_Y3_PIN_6_PIN,0);
      
      io_in_bit.bit.X1_bit = DL_GPIO_readPins(IX1_PORT,IX1_PIN_10_PIN)>0? 1:0;
      io_in_bit.bit.X2_bit = DL_GPIO_readPins(IX2_PORT,IX2_PIN_11_PIN)>0? 1:0;
      io_in_bit.bit.X3_bit = DL_GPIO_readPins(IX3_PORT,IX3_PIN_12_PIN)>0? 1:0;
      io_in_bit.bit.X7_bit = DL_GPIO_readPins(IX7_PORT,IX7_PIN_16_PIN)>0? 1:0;  
      
      mtestmsg.timer_cnt++;
      if(mtestmsg.timer_cnt==5)
      {
        mtestmsg.timer_cnt = 0;
        mtestmsg.test_step = TEST_DONE;
      }
      
      break;  		
    }     
    
  case TEST_DONE:
    {
      io4_readtmp2 = DL_GPIO_readPins(IX4_PORT,IX4_PIN_13_PIN)>0? 1:0;
      
      if(mtestmsg.B_version==0)
      {
      if(mtestmsg.scl_check==0)
      {
        board_err.bit.scl_err = 1;
      }  
      else
      {
        board_err.bit.scl_err = 0;
      }
      }
      if(mtestmsg.can_check==0)
      {
        board_err.bit.can_err = 1;
      }  
      else
      {
        board_err.bit.can_err = 0;
      }
      
      if(mtestmsg.rs485a_check==0)
      {
        board_err.bit.rs485a_err = 1;
      }  
      else
      {
        board_err.bit.rs485a_err = 0;
      }
      
      if(mtestmsg.rs485b_check==0)
      {
        board_err.bit.rs485b_err = 1;
      }   
      else
      {
        board_err.bit.rs485b_err = 0;
      }
      
      if(mtestmsg.B_version==0)
      {
        
      io_test_bit.all = mtestmsg.io_value;
      board_err.bit.ix0_err = io_test_bit.bit.X0_bit;
      board_err.bit.ix1_err = io_test_bit.bit.X1_bit;
      board_err.bit.ix2_err = io_test_bit.bit.X2_bit;
      board_err.bit.ix3_err = io_test_bit.bit.X3_bit;           
      board_err.bit.ix4_err = io_test_bit.bit.X4_bit;;
      board_err.bit.ix5_err = io_test_bit.bit.X5_bit;
      board_err.bit.ix6_err = io_test_bit.bit.X6_bit;
      board_err.bit.ix7_err = io_test_bit.bit.X7_bit;   
      
      board_err.bit.y3_err = io_in_bit.bit.X1_bit;
      board_err.bit.y4_err = io_in_bit.bit.X2_bit;
      board_err.bit.y5_err = io_in_bit.bit.X3_bit;
      board_err.bit.y6_err = io_in_bit.bit.X7_bit;   
      
      if((io4_readtmp==0)&&(io4_readtmp2==1))
      {
        yo_err_bit.bit.power_err  = 0;
      }
      else
      {
        yo_err_bit.bit.power_err = 1;
      }
      
      }
      
      mtestmsg.finish = 1;
      
      
      break;  		
    }   	  
  }
}