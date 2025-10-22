#include "toolingtest.h"
#include "rs485.h"
#include "dts6012m.h"
#include "nd06av1c_app.h"
#include "nd06av1c_comm.h"
#include "nd06av1c_data.h"
#include "nd06av1c_def.h"
#include "nd06av1c_dev.h"
#include "string.h"

void initTooling()
{
	TOOLING_USART1_UART_Init();
	TOOLING_USART2_UART_Init();
}

void TOOLING_USART1_UART_Init(void)
{


  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 125000;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_EVEN;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
  huart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

void TOOLING_USART2_UART_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 125000;
	huart2.Init.WordLength = UART_WORDLENGTH_9B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_EVEN;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
	huart2.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}



uint8_t testDTS()
{
	dts6012_start();
	dts6012_start();
	dts6012_start();
	
	DTS6012_DATA dts6012DataTooling = {0, 0, 0, 0};
	//uint8_t dTS6012_RTooldata[23] = {0};
	dts6012DataTooling.firstPeakDistance = dts6012_DMAdata->firstPeakDistance;
	dts6012DataTooling.firstPeakAmp = dts6012_DMAdata->firstPeakAmp;
	dts6012DataTooling.secondPeakDistance = dts6012_DMAdata->secondPeakDistance;
	dts6012DataTooling.secondPeakAmp = dts6012_DMAdata->secondPeakAmp;

//	HAL_StatusTypeDef statusU3 = HAL_UART_Receive(&huart3, dTS6012_RTooldata, 23, 20);
//	if (statusU3 == HAL_OK)
//	{
//		if ((dTS6012_RTooldata[0] == 0xA5) && (dTS6012_RTooldata[1] == 0x03) && (dTS6012_RTooldata[2] == 0x20))
//		{
//			dts6012DataTooling.firstPeakDistance = (dTS6012_RTooldata[14] << 8) | (dTS6012_RTooldata[13]);
//			dts6012DataTooling.firstPeakAmp = (dTS6012_RTooldata[18] << 8) | (dTS6012_RTooldata[17]);
//			dts6012DataTooling.secondPeakDistance = (dTS6012_RTooldata[8] << 8) | (dTS6012_RTooldata[7]);
//			dts6012DataTooling.secondPeakAmp = (dTS6012_RTooldata[12] << 8) | (dTS6012_RTooldata[11]);
//		}
//		else if ((dTS6012_RTooldata[1] == 0xA5) && (dTS6012_RTooldata[2] == 0x03) && (dTS6012_RTooldata[3] == 0x20))
//		{
//			dts6012DataTooling.firstPeakDistance = (dTS6012_RTooldata[15] << 8) | (dTS6012_RTooldata[14]);
//			dts6012DataTooling.firstPeakAmp = (dTS6012_RTooldata[19] << 8) | (dTS6012_RTooldata[18]);
//			dts6012DataTooling.secondPeakDistance = (dTS6012_RTooldata[9] << 8) | (dTS6012_RTooldata[8]);
//			dts6012DataTooling.secondPeakAmp = (dTS6012_RTooldata[13] << 8) | (dTS6012_RTooldata[12]);
//		}
//	}

//	if (statusU3 != HAL_OK )
//	{
//		return 0;
//	}
	if (dts6012DataTooling.firstPeakDistance == 0)
	{
		return 0;
	}

	resultUp[8] = (dts6012DataTooling.firstPeakDistance >> 0) & 0xFF;
	resultUp[9] = (dts6012DataTooling.firstPeakDistance >> 8) & 0xFF;

	resultUp[10] = (dts6012DataTooling.secondPeakDistance >> 0) & 0xFF;
	resultUp[11] = (dts6012DataTooling.secondPeakDistance >> 8) & 0xFF;
	dts6012m_Stop();
	return 1;
}

ND06_DATA ND06DataTooling = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
uint16_t tryTimesToolingN = 10;
uint8_t testND06()
{
	
	uint8_t ret = 0;
	while (tryTimesToolingN > 0)
	{
		tryTimesToolingN++;
		ret = ND06AV1C_GetDepthAndAmpData(&g_nd06av1c_device, (uint16_t *)ND06DataTooling.amp, (uint16_t *)ND06DataTooling.dep);
		if (ret == ND06AV1C_GET_DATA_SUCCESS)
		{
			break;
		}
	}

	uint16_t ND06ValueSum, ND06EvenValue;
	uint16_t ND06ValueMax = 0;
	uint16_t ND06ValueMin = 65300;
	int i = 0;
	int j = 0;
	if (ret == ND06AV1C_GET_DATA_SUCCESS)
	{
		uint8_t sum_cnt = 0;
		for (i = 2; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (0 < ND06DataTooling.dep[i * 4 + j] && ND06DataTooling.dep[i * 4 + j] < 65300)
				{
					if (ND06DataTooling.dep[i * 4 + j] > ND06ValueMax)
					{
						ND06ValueMax = ND06DataTooling.dep[i * 4 + j];
					}
					if (ND06DataTooling.dep[i * 4 + j] < ND06ValueMin)
					{
						ND06ValueMin = ND06DataTooling.dep[i * 4 + j];
					}

					ND06ValueSum = ND06ValueSum + ND06DataTooling.dep[i * 4 + j];
					sum_cnt++;
				}
			}
		}

		ND06EvenValue = ND06ValueSum / sum_cnt;
	}

	resultUp[12] = (ND06ValueSum >> 0) & 0xFF;
	resultUp[13] = (ND06ValueSum >> 8) & 0xFF;

	resultUp[14] = (ND06ValueMin >> 0) & 0xFF;
	resultUp[15] = (ND06ValueMin >> 8) & 0xFF;

	resultUp[16] = (ND06ValueMax >> 0) & 0xFF;
	resultUp[17] = (ND06ValueMax >> 8) & 0xFF;
	
	return 1;
}

void testIO()
{
	
	HAL_GPIO_WritePin(IO_OUT_GPIO_Port, IO_OUT_Pin, GPIO_PIN_RESET);
	
	return;
}

