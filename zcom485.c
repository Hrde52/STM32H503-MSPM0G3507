#include "zcom485.h"

extern void SCL1_TXEN(uint8_t * src,uint8_t TxLength);
extern void SCL2_TXEN(uint8_t TxLength,uint8_t * src);
extern void SCL3_TXEN(uint8_t TxLength,uint8_t * src);
extern void can_txd_start(unsigned char tx[],unsigned char p_StdId);
extern rxd_uart_TypeDef rxd_uart2;
void board_test(void);

ComMsgData m_p_msg;
ComMsgData m_pEnd_msg;
ComMsgData m_pResult_msg;
ComMsgData pData;
TestMsg  mtestmsg;
IO_TS_BITS io_test_bit;
IO_TS_BITS io_in_bit;
SIG_ERR_BITS  board_err;

SIG_TERR_BITS  board4_err;

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
    //uint8_t nd06ProjNameBuf[8] = {0x02, 0x04, 0x02,  0x02, 0x00, 0x01, 0x00, 0x00};
    //mem_copy((uint8_t *)&m_p_msg.nData[1], (uint8_t *)&nd06ProjNameBuf, 8);
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
  
  
  //DL_GPIO_clearPins(GPIOB, m485BTE_PIN_10_PIN);//RS485B_RX;
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
  m_pEnd_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_pEnd_msg.mVer = COMM_VERSION;
  
  m_pEnd_msg.mBk[0] = m_bk[0];
  m_pEnd_msg.mBk[1] = m_bk[1];
  
  m_pEnd_msg.mLenl = 13;
  m_pEnd_msg.mLenh = 0;
  
  m_pEnd_msg.mCmd = COM_TEST_END_CMD;
  
  m_pEnd_msg.nData[0] = 8;
  if(mtestmsg.B_version==0)
  {
    mem_copy((uint8_t *)&m_pEnd_msg.nData[1], (uint8_t *)&ProjNameBuf, 8);
  }
  else
  {
    mem_copy((uint8_t *)&m_pEnd_msg.nData[1], (uint8_t *)&ProjNameBuf_B, 8);
  }  
  mem_copy((uint8_t *)&m_pEnd_msg.msendData[0], (uint8_t *)&m_pEnd_msg.mFrHead,m_pEnd_msg.mLenl+3);
  
  m_pEnd_msg.mxor = cal_xor_value((uint8_t *)&m_pEnd_msg.msendData[1],m_pEnd_msg.mLenl+2);
  m_pEnd_msg.msum = cal_sum_value((uint8_t *)&m_pEnd_msg.msendData[1],m_pEnd_msg.mLenl+2);
  
  m_pEnd_msg.msendData[m_pEnd_msg.mLenl+3] = m_pEnd_msg.mxor;
  m_pEnd_msg.msendData[m_pEnd_msg.mLenl+4] = (m_pEnd_msg.msum&0xff00)>>8;
  m_pEnd_msg.msendData[m_pEnd_msg.mLenl+5] = m_pEnd_msg.msum&0x00ff; 
  
  //delay_cycles(100);
  SCL3_TXEN(m_pEnd_msg.mLenl+6,m_pEnd_msg.msendData);  
  
}


void send_test_result(const bool mState)
{
  m_pResult_msg.mFrHead = COM_FRAME_SEND_HEAD;
  m_pResult_msg.mVer = COMM_VERSION;
  
  m_pResult_msg.mBk[0] = m_bk[0];
  m_pResult_msg.mBk[1] = m_bk[1];
  
  m_pResult_msg.mLenl = 0x23;  //  低位 SCL3_TXEN(m_p_msg.mLenl+6,m_p_msg.msendData);  29+6 = 35
  m_pResult_msg.mLenh = 0;    // 高位
  
  m_pResult_msg.mCmd = COM_TEST_RESULT_CMD;
  
  m_pResult_msg.nData[0] = 1; // L1
  
  // DATA1
  if (mState)
  {
    m_pResult_msg.nData[1] = 1;   // 测试成功
  }
  else
  {
    m_pResult_msg.nData[1] = 0;
  }
  
  /*L2*/
  m_pResult_msg.nData[2] = 1;  // L2
  m_pResult_msg.nData[3] = 1;  // DATA2,按位解析
  
  /*L3 */
  m_pResult_msg.nData[4] = 4; // L3,默认4个bites 5 6 7 8
  mem_copy((uint8_t *)&m_pResult_msg.nData[5], 0, 4);
/*  
  m_p_msg.nData[8] = board_err.all&0x00ff;
  m_p_msg.nData[7] = (board_err.all&0xff00)>>8;
  m_p_msg.nData[6] = yo_err_bit.all;
*/
  m_pResult_msg.nData[8] = board4_err.all&0x00ff;
  m_pResult_msg.nData[7] = (board4_err.all&0xff00)>>8;
  //
   
  /*L4条形码*/
  m_pResult_msg.nData[9] = 1; 
  m_pResult_msg.nData[10] = 0;
  
  /*L5 ID*/
  m_pResult_msg.nData[11] = 4;
  mem_copy((uint8_t *)&m_pResult_msg.nData[12], m_id_code.data, 4);
  
  /*L6 软件版本*/
  m_pResult_msg.nData[16] = 8;  //16 17181920 21222324
  uint8_t indexNDdata = 17;
  mem_copy((uint8_t *)&m_pResult_msg.nData[17], VERSION, sizeof(VERSION));
  indexNDdata= 25;
  
  
  /*L7 ND测距信息*/
  m_pResult_msg.nData[indexNDdata++] = 2;
  
  m_pResult_msg.nData[indexNDdata++] = rxBuffT[14];   //15
  m_pResult_msg.nData[indexNDdata++] = rxBuffT[13];  // 14

  /*L8 DTS6012测距信息*/
  m_pResult_msg.nData[indexNDdata++] = 2;
  m_pResult_msg.nData[indexNDdata++] = rxBuffT[9]; 
  m_pResult_msg.nData[indexNDdata++] = rxBuffT[8];
 
  memset(rxBuffT, 0, 20);
  
  mem_copy((uint8_t *)&m_pResult_msg.msendData[0], (uint8_t *)&m_pResult_msg.mFrHead,m_pResult_msg.mLenl+3);

  m_pResult_msg.mxor = cal_xor_value((uint8_t *)&m_pResult_msg.msendData[1],m_pResult_msg.mLenl+2);
  m_pResult_msg.msum = cal_sum_value((uint8_t *)&m_pResult_msg.msendData[1],m_pResult_msg.mLenl+2);
  
  m_pResult_msg.msendData[m_pResult_msg.mLenl+3] = m_pResult_msg.mxor;
  m_pResult_msg.msendData[m_pResult_msg.mLenl+4] = (m_pResult_msg.msum&0xff00)>>8;
  m_pResult_msg.msendData[m_pResult_msg.mLenl+5] = m_pResult_msg.msum&0x00ff;  
  
  delay_cycles(100);
  SCL3_TXEN(m_pResult_msg.mLenl+6,m_pResult_msg.msendData);
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
  
//  switch (pData.mCmd)
//  {
//  case COM_SHAKEHAND_CMD:
//    {
//      m_test_state = START;
//      m_bk[0] = pData.mBk[0];
//      m_bk[1] = pData.mBk[1];
//      res = true;
////      request_set_code();
//      break;
//    }
//  case COM_SETUP_CONFIG_CMD:
//    res = true;
//    break;
//  case COM_TEST_END_CMD:
//    {
//      m_test_state = END;    
//      res = true;
//      break;
//    }
//  case COM_TEST_RESULT_CMD:
//    {
//      m_test_state = RESULT;
//      res = true;
////      send_test_end();
//      break;
//    }
//  case COM_SET_CODE_CMD:
//    {       
//      //m_id_code = std::string((char *)&pData.nData[5], 4);
//      //write_file_code(ID_CODE_NAME_PATH, m_id_code.data());
//      mem_copy((uint8_t *)&m_id_code.data[0], (uint8_t *)&pData.nData[5],4);
//      //request_authorize_fun();
//      m_test_state = AUTHOR;
//      res = true;
//      break;
//    }
//  case COM_AUTHORIZATION_CMD:
//    {   
//      m_test_state = AUTHOR;
//      res = true;
//      //write_file_code(LICESE_NAME_PATH, "COM_AUTHORIZATION");
//      //m_send_heart_beat_times = 0;
//      break;
//    }
//  case COM_SEND_VER_ID_CMD:
//    res = true;
//    break;
//  case COM_REQEST_CERT_CMD:
//    res = true;
//    break;
//  case COM_SEND_CERT_CMD:
//    res = true;
//    break;
//  default:
//    res = true;
//    break;
//  }
//  
  return res;
}


uint8_t homework_switch1 = 0;
uint8_t homework_switch2 = 0;
uint8_t homework_switch3= 0;

uint8_t testNd061[10] = {0XBD, 0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x1f};
uint8_t testNd062[10] = {0XCD, 0x22, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x2f};

uint8_t testTFD11[10] = {0XAC, 0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x1f};
uint8_t testTFD12[10] = {0XAC, 0x22, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x2f};//Y5开启，测试485
uint8_t handTFD1[10] = {0XAC, 0x01, 0x12,  0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89};

uint8_t testTFD21[10] = {0XAC, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x1f};
uint8_t testTFD22[10] = {0XAC, 0x22, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x2f};//Y5开启，测试485

uint16_t in_times = 0;
uint16_t in2_times = 0;
uint16_t nd_times = 0;
uint16_t m_send_message_times1 = 0;
uint16_t m_send_message_times2 = 0;
uint16_t m_send_message_times3 = 0;
uint16_t m_send_message_times4 = 0;

uint8_t getRspHSTFD1 = 0;
uint8_t getRspHSTFD2 = 0;

uint8_t getRspNd061= 0;
uint8_t getRspNd062= 0;
uint8_t getRspTFD11= 0;
uint8_t getRspTFD12= 0;
uint8_t getRspTFD21= 0;
uint8_t getRspTFD22= 0;
uint8_t selectTFD = 0;

uint8_t TFD1Pass= 0;
uint8_t TFD2Pass= 0;
uint8_t ND1Pass= 0;
uint8_t ND2Pass= 0;

//uint8_t Y0OF = 0;
//uint8_t Y1OF= 0;



void turnOnTFD1()
{
  DL_GPIO_clearPins(ROUT_Y1_PORT,ROUT_Y1_PIN_4_PIN); // Y1clear TFD1上电 同时X有输出
  DL_GPIO_clearPins(ROUT_Y0_PORT,ROUT_Y0_PIN_20_PIN); //
}

void turnOnTFD2()
{
  DL_GPIO_setPins(ROUT_Y1_PORT,ROUT_Y1_PIN_4_PIN); // Y1clear TFD1上电 同时X有输出
  DL_GPIO_setPins(ROUT_Y0_PORT,ROUT_Y0_PIN_20_PIN); //
}

void testTFDX()
{
  DL_GPIO_setPins(ROUT_Y3_PORT,ROUT_Y3_PIN_6_PIN); // Y3测试输入X0
}

void boardtest_loop_process()
{
  homework_switch1 = DL_GPIO_readPins(IX7_PORT,IX7_PIN_16_PIN)>0? 1:0;
  homework_switch2 = DL_GPIO_readPins(IX6_PORT,IX6_PIN_15_PIN)>0? 1:0;
  homework_switch3 = DL_GPIO_readPins(IX5_PORT,IX5_PIN_14_PIN)>0? 1:0;

//  if(Y0OF)
//  {
//    DL_GPIO_setPins(ROUT_Y0_PORT,ROUT_Y0_PIN_20_PIN); //
//  }
//  else
//  {
//    DL_GPIO_clearPins(ROUT_Y0_PORT,ROUT_Y0_PIN_20_PIN); //
//  }
//  if(Y1OF)
//  {
//    DL_GPIO_setPins(ROUT_Y1_PORT,ROUT_Y1_PIN_4_PIN); //
//  }
//  else
//  {
//    DL_GPIO_clearPins(ROUT_Y1_PORT,ROUT_Y1_PIN_4_PIN); //
//  }  
  
  switch(homework_switch1)
  {
    
    case 0:
    {
      /*
Y5  485
Y0  TFD
Y3  X0
      */
      switch(selectTFD)
      {
        
        case 0:
        {
          turnOnTFD1();            
          testTFDX();
          if(DL_GPIO_readPins(IX0_PORT,IX0_PIN_9_PIN) > 0 )
          {
            board4_err.bit.TFD1_IO =  0;  // 输出
          }
          
          if(in_times == 1 && m_send_message_times1 < 3)
          {
            send_shake_hand();        
          }
          
          in_times++;
          

          if( (in_times > 2) &&(in_times < 100) && (getRspHSTFD1 == 0))
          {
            
            SCL2_TXEN(10, handTFD1);    // 握手
          }
              
          if((in_times == 100) && (getRspHSTFD1 == 0))
          {
            send_test_result(0);
            TFD1Pass = 1;
          }
          
          // ********************************
          
          if(m_send_message_times1< 10 )
          {
            if(in_times >= 105)
            {          
              if((in_times%5) == 0)
              {
                if(getRspTFD11== 0)
                {
                  m_send_message_times1++;
                  SCL2_TXEN(10, testTFD11);
                  if(DL_GPIO_readPins(IX0_PORT,IX0_PIN_9_PIN) > 0 )
                  {
                    board4_err.bit.TFD1_IO =  0;  // 输出
                  }
                }
                else
                {
                  m_send_message_times1= 10;
                  in_times = 155;
                }
              }
            }
            
          }
          else if(m_send_message_times1 >= 10 && m_send_message_times1< 20 )
          {
            if(in_times >= 155)
            {
              //DL_GPIO_setPins(ROUT_Y5_PORT,ROUT_Y5_PIN_8_PIN); // Y5切换485             
              if((in_times%5) == 0)
              {
                if( getRspTFD12== 0 )
                {
                  m_send_message_times1++;
                  SCL2_TXEN(10, testTFD12);
                  if(DL_GPIO_readPins(IX0_PORT,IX0_PIN_9_PIN)>0 )
                    board4_err.bit.TFD1_IO =  0;  // 输出
                }
                else
                {
                  m_send_message_times1= 20;
                  in_times = 0;
                }
              }
            }
            
          }
          else
          {
            if(getRspTFD11 == 0)
            {
              board4_err.bit.TFD1_485_1 = 1;
            }
            
            
            if(getRspTFD12 == 0)
            {
              board4_err.bit.TFD1_485_2 = 1;
            }
            else
            {
              board4_err.bit.TFD1_DTS6012 = (rxTFD1[2] == 0) ? 0 : 1;
              board4_err.bit.TFD1_ND06 = (rxTFD1[3] == 0) ? 0 : 1;
              board4_err.bit.TFD1_X = (rxTFD1[4] == 0) ? 0 : 1;
//              board4_err.bit.TFD1_X = (rxTFD1[4] == 1) ? 0 : 1;
            }
            
            //board4_err.bit.TFD1_IO = 1;          
           
            if(board4_err.all > 0)
            {
               send_test_result(0);
               board4_err.all = 0;
               TFD1Pass = 1;
            }
            else
            {
              send_test_result(1);
               board4_err.all = 0;
              TFD1Pass = 1;
            }
                  
            in_times = 0;
            //m_send_message_times1= 0;
            selectTFD = 1;
            turnOnTFD2();
          }
          
          break;
        }
        case 1:
        {
          turnOnTFD2();

         testTFDX();
         if(DL_GPIO_readPins(IX1_PORT,IX1_PIN_10_PIN)>0)
         {
            board4_err.bit.TFD2_IO = 0;
         }
         
         
          if( (in2_times > 1) &&(in2_times < 100) && (getRspHSTFD2 == 0))
          {
              SCL2_TXEN(10, handTFD1);    // 握手
          }
          
          
          if((in2_times == 100) && (getRspHSTFD2 == 0))
          {
            send_test_result(0);
            TFD2Pass = 1;
          }
         
          in2_times++;
          
          if(m_send_message_times2< 10 )
          {
            if(in2_times >= 105)
            { 
              if((in2_times%5) == 0)
              {
                if(getRspTFD21== 0)
                {
                  m_send_message_times2++;
                  SCL2_TXEN(10, testTFD21);
                  if(DL_GPIO_readPins(IX1_PORT,IX1_PIN_10_PIN)>0)
                    board4_err.bit.TFD2_IO = 0;
                }
                else
                {
                  m_send_message_times2= 10;
                  in2_times = 155;
                }
              }
          }
            
          }
          else if(m_send_message_times2 >= 10 && m_send_message_times2< 20 )
          {
            if(in2_times >= 155)
            {
              DL_GPIO_setPins(ROUT_Y5_PORT,ROUT_Y5_PIN_8_PIN); // 
              
              if((in2_times%5) == 0)
              {
                if( getRspTFD22== 0 )
                {
                  m_send_message_times2++;
                  SCL2_TXEN(10, testTFD22);
                  if(DL_GPIO_readPins(IX1_PORT,IX1_PIN_10_PIN)>0)
                    board4_err.bit.TFD2_IO = 0;
                }
                else
                {
                  m_send_message_times2= 20;
                  in2_times = 0;
                  
                  
                  if(getRspTFD21 == 0)
                  {
                    board4_err.bit.TFD2_485_1 = 1;
                  }
                    
                  if(getRspTFD22 == 0)
                  {
                      board4_err.bit.TFD2_485_2 = 1;
                  }
                  else
                  {
                    board4_err.bit.TFD2_DTS6012 = (rxTFD2[2] == 0) ? 0 : 1;
                    board4_err.bit.TFD2_ND06 = (rxTFD2[3] == 0) ? 0 : 1;
                    board4_err.bit.TFD2_X = (rxTFD2[4] == 0) ? 0 : 1;
//                    board4_err.bit.TFD2_X = (rxTFD2[4] == 1) ? 0 : 1;
                  }
                  
                  if(board4_err.all >= 256)
                  {
                     send_test_result(0);
                     TFD2Pass = 1;

                  }
                  else
                  {
                    send_test_result(1);
                    board4_err.all = 0;
                    TFD2Pass = 1;
                  }
                  
                  
                }
              }
            }
            
          }
          else if(m_send_message_times2 == 20 && in2_times == 10)
          {
            
            send_test_end();
          }
          
          break;
        }
        default:
          break;
      }  // END OF switch(selectTFD)
      
      if(TFD1Pass ==1 && TFD2Pass == 1)
      {
        send_test_end();
      }
      break;
    }
    case 1:
    {
      //DL_GPIO_setPins(ROUT_Y4_PORT,ROUT_Y4_PIN_13_PIN); // Y5切换485
      if(nd_times == 1 && m_send_message_times3 < 3){
        send_shake_hand();
       }
      
      nd_times++;
          
      if(m_send_message_times3< 3 )
      {       
        
        if(nd_times >= 40)
        {
          if((nd_times%5) == 0)
          {
            if(getRspNd061== 0)
            {
              m_send_message_times3++;
              SCL2_TXEN(10, testNd061);
            }
            else
            {
       
              m_send_message_times3= 3;

            }
          }
        }
        
      }
      else if(m_send_message_times3 == 3 )
      {
        m_send_message_times3++;
        if(getRspNd061== 0)
        {
          board4_err.bit.ND06_1 = 1;
          send_test_result(0);
          board4_err.all = 0;
        }
        else
        {
          send_test_result(1);
          board4_err.all = 0;
        
        }
      }
      else if(m_send_message_times3 > 3 && m_send_message_times3< 6 )
      {

       if(nd_times == 81 && m_send_message_times3 == 4)
       {
        send_shake_hand();
       }
        
       if(nd_times >= 85)
       {
        if((nd_times%5) == 0)
        {
          if( getRspNd062== 0 )
          {
            m_send_message_times3++;
            SCL2_TXEN(10, testNd062);
          }
          else
          {
            m_send_message_times3= 6;
            nd_times = 0;
            
          }
        }
      }
        
      }
      else if(m_send_message_times3 == 6)
      {
        m_send_message_times3++;
        nd_times = 0;
        if( getRspNd062 == 0 )
        {
          board4_err.bit.ND06_2 = 1;
          send_test_result(0);
          
        }
        else
        {
          send_test_result(1);
        }    
        
      }
      else if(m_send_message_times3 == 7 && nd_times == 10)
      {
        send_test_end();
      }
      break;
    }
    default:
      break;
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