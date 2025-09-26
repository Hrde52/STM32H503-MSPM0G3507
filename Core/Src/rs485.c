#include "rs485.h"
//#include "PDA_Communication.h"
#include "main.h"
//#include "sensorAppLogic.h"
//#include "sensorParaTable.h"
#include "string.h"
#include "toolingtest.h"

unsigned char gLookupTableCRC8[256] = {
    /* 0x00 */ 0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75,
    0x0E, 0x9F, 0xED, 0x7C, 0x09, 0x98, 0xEA, 0x7B,
    0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69,
    0x12, 0x83, 0xF1, 0x60, 0x15, 0x84, 0xF6, 0x67,
    0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D,
    0x36, 0xA7, 0xD5, 0x44, 0x31, 0xA0, 0xD2, 0x43,
    0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51,
    0x2A, 0xBB, 0xC9, 0x58, 0x2D, 0xBC, 0xCE, 0x5F,
    /* 0x40 */ 0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05,
    0x7E, 0xEF, 0x9D, 0x0C, 0x79, 0xE8, 0x9A, 0x0B,
    0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19,
    0x62, 0xF3, 0x81, 0x10, 0x65, 0xF4, 0x86, 0x17,
    0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D,
    0x46, 0xD7, 0xA5, 0x34, 0x41, 0xD0, 0xA2, 0x33,
    0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21,
    0x5A, 0xCB, 0xB9, 0x28, 0x5D, 0xCC, 0xBE, 0x2F,
    /* 0x80 */ 0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95,
    0xEE, 0x7F, 0x0D, 0x9C, 0xE9, 0x78, 0x0A, 0x9B,
    0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89,
    0xF2, 0x63, 0x11, 0x80, 0xF5, 0x64, 0x16, 0x87,
    0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD,
    0xD6, 0x47, 0x35, 0xA4, 0xD1, 0x40, 0x32, 0xA3,
    0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1,
    0xCA, 0x5B, 0x29, 0xB8, 0xCD, 0x5C, 0x2E, 0xBF,
    /* 0xC0 */ 0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5,
    0x9E, 0x0F, 0x7D, 0xEC, 0x99, 0x08, 0x7A, 0xEB,
    0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9,
    0x82, 0x13, 0x61, 0xF0, 0x85, 0x14, 0x66, 0xF7,
    0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD,
    0xA6, 0x37, 0x45, 0xD4, 0xA1, 0x30, 0x42, 0xD3,
    0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1,
    0xBA, 0x2B, 0x59, 0xC8, 0xBD, 0x2C, 0x5E, 0xCF};

/*******************************************************************************
 **函数功能：查表法计算CRC
 **参数输入：inBuffer：进行校验的数据块头地址；inSize：数据块大小
 **数据返回：CRC校验码
 *******************************************************************************/
uint8_t CalcCRC8(uint8_t *inBuffer, int inSize)
{
    uint8_t aCRC;
    uint8_t i;
    aCRC = 0xFF; /* Start CRC Remain*/
    for (i = 0; i < (int)inSize; i++)
    {
        aCRC = (aCRC ^ *(inBuffer + i));
        aCRC = gLookupTableCRC8[aCRC];
    }
    aCRC = ~aCRC;
    return (uint8_t)aCRC;
}

uint8_t xor_checkSum(uint8_t *data, uint8_t length)
{
    uint8_t checkSum = 0;
    for (uint8_t i = 0; i < length; i++)
    {
        checkSum ^= data[i];
    }
    return checkSum;
}

ControlSystemPara CSpara = {0, 0, 0, 0, 0};

uint8_t rxDataBuffElevator[1] = {0};
uint8_t rx_data_Elevator[6] = {0, 0, 0, 0, 0, 0};
uint8_t RxDataElevator[6] = {0, 0, 0, 0, 0, 0};
uint8_t rxDataBuffPDA[4] = {0, 0, 0, 0};
uint8_t rs485ElevatorRxCpltFlag = 0;
uint8_t rs485PDARxCpltFlag = 0;

/**rx_data_Elevator
 * @breif   初始化RS485收发器为接收模式，此485用于监听控制系统通信
 * @param   无
 * @retval  无
 * @note    在调用此函数之前，确保已经初始化通信串口和控制GPIO
 */
void RS485_Elevator_Init()
{
    /* 使能串口接收中断 */
    HAL_UART_Receive_IT(&RS485_Elevator_USART, rxDataBuffElevator, 1);

    RS485_Elevator_RX_ENABLE();
}

void RS485_PDA_Init()
{
    /* 使能串口接收中断 */
    HAL_UART_Receive_IT(&RS485_PDA_USART, rxDataBuffPDA, 4);

    RS485_PDA_RX_ENABLE();
}

/**
 * @breif   控制RS485收发器发送数据
 * @param   data 要发送的数据
 * @param   len  要发送数据的长度
 * @retval  0 - 发送成功，-1 = 发送失败
 */
int RS485_Elevator_Transmit(uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef status;

    RS485_Elevator_TX_ENABLE();

    status = HAL_UART_Transmit(&RS485_Elevator_USART, data, len, 1);

    // HAL_Delay(1);

    RS485_Elevator_RX_ENABLE();
    rs485ElevatorRxCpltFlag = 0;

    return status == HAL_OK ? 0 : -1;
}

int RS485_PDA_Transmit(uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef status;

    RS485_PDA_TX_ENABLE();

    status = HAL_UART_Transmit(&RS485_PDA_USART, data, len, 1);

    // HAL_Delay(1);

    RS485_PDA_RX_ENABLE();
    rs485PDARxCpltFlag = 0;

    return status == HAL_OK ? 0 : -1;
}

/**
 * @brief   串口中断回调函数
 * @note    此函数属于弱定义函数的重新实现，HAL库会自动调用
 */
uint16_t RxElevatorCnt = 0;
uint16_t headerIsFoundFlag = 0;
uint16_t rxSize = 6;
bool isSixBytes = true; // true表示监控对象为主控发送的6个字节，false表示监控对象HCB板回复的4个字节
bool isFixBytes = false;

uint8_t testArr[100];
uint16_t testii = 0;
uint8_t testArr2[100];
uint16_t testii2 = 0;
// uint32_t sensorADDR = 0X52;

uint16_t rxIndex = 0;
uint16_t total_len = 0;
uint8_t rxDBuffPDA[MAX_RX_LEN]; // 有字头判断
uint8_t iindex = 0;
uint8_t rx_DBuffPDA[MAX_RX_LEN];   // 无字头判断
SensorProtocol *global_pkt = NULL; // 全局变量，用于监视 pkt

uint16_t rxIndexTooling = 0;
uint16_t rxLenTooling = 0;
uint8_t rxDBuffTooling[10]; // 有字头判断

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t crcValue = 0;
    /* 判断是哪个串口触发的中断 */
    if (huart->Instance == USART1)
    {
				if (rxIndexTooling == 0 && rxDBuffTooling[0] != 0XCC) //(HEADER & 0xFF)
				{
						rxIndexTooling = 0;
						HAL_UART_Receive_IT(&huart1, &rxDBuffTooling[rxIndexTooling], 1);
						return;
				}
				if (rxIndexTooling > 9)
				{
						ProcessTooling(rxDBuffTooling);

						rxIndexTooling = 0;
						memset(rxDBuffTooling, 0, sizeof(rxDBuffTooling));

						HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET);
						HAL_Delay(100);
						HAL_UART_Receive_IT(&huart1, &rxDBuffTooling[rxIndexTooling], 1);
						return;
				}

				rxIndexTooling++;

				if (rxIndexTooling > 10)
				{
						rxIndexTooling = 0;
				}
				HAL_UART_Receive_IT(&huart1, &rxDBuffTooling[rxIndexTooling], 1);
        

    }

    else if (huart->Instance == USART2)
    {
				if (rxIndexTooling == 0 && rxDBuffTooling[0] != 0XCC) //(HEADER & 0xFF)
				{
						rxIndexTooling = 0;
						HAL_UART_Receive_IT(&huart2, &rxDBuffTooling[rxIndexTooling], 1);
						return;
				}
				if (rxIndexTooling > 9)
				{
						ProcessTooling(rxDBuffTooling);

						rxIndexTooling = 0;
						memset(rxDBuffTooling, 0, sizeof(rxDBuffTooling));

						HAL_GPIO_WritePin(RS485_GHP_EN_GPIO_Port, RS485_GHP_EN_Pin, GPIO_PIN_RESET);
						// HAL_Delay(100);
						HAL_UART_Receive_IT(&huart2, &rxDBuffTooling[rxIndexTooling], 1);
						return;
				}

				rxIndexTooling++;

				if (rxIndexTooling > 10)
				{
						rxIndexTooling = 0;
				}
				HAL_UART_Receive_IT(&huart2, &rxDBuffTooling[rxIndexTooling], 1);
        
     }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET);
        delay_10us(1);
        HAL_UART_Receive_IT(&RS485_Elevator_USART, rxDataBuffElevator, 1);
    }
}

uint8_t res1 = 0;
uint8_t res2 = 0;
void ProcessTooling(const uint8_t *data)
{
    uint8_t xorResult = xor_checkSum(data, 9);
    if (data[9] == xorResult)
    {
    }
    res1 = testDTS();

    res2 = testND06();

    // testIO();

    if (res1 && res2)
    {
        isToolingTest = 0;

        HAL_NVIC_SystemReset();
    }

    return;
}

// END
