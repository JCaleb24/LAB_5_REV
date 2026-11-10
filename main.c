/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile uint8_t st;
volatile uint8_t inicio;
volatile uint8_t juegoact;
volatile uint8_t verdeact;
volatile uint8_t cont1 = 0;
volatile uint8_t cont2 = 0;
volatile uint32_t ant1;
volatile uint32_t ant2;
volatile uint8_t gana;
volatile uint8_t reportar;
char buffer[50]; //buffer para guardar y transmitir el mensaje

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &st, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (inicio){  // fase inicial
		  inicio = 0;
		  juegoact = 0;
		  cont1 = 0;
		  cont2 = 0;  //reiniciar todas las variables


		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 0);
		  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 0);
		  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 0);
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 0);   // Apagar todas las leds
		  HAL_GPIO_WritePin(luz1_GPIO_Port, luz1_Pin, 0);
		  HAL_GPIO_WritePin(luz2_GPIO_Port, luz2_Pin, 0);
		  HAL_GPIO_WritePin(luz3_GPIO_Port, luz3_Pin, 0);
		  HAL_GPIO_WritePin(luz4_GPIO_Port, luz4_Pin, 0);

		  HAL_GPIO_WritePin(verde_GPIO_Port, verde_Pin, 0);
		  HAL_GPIO_WritePin(amarillo_GPIO_Port, amarillo_Pin, 0);
		  HAL_GPIO_WritePin(rojo_GPIO_Port, rojo_Pin, 1);
		  HAL_Delay(1000);
		  HAL_GPIO_WritePin(verde_GPIO_Port, verde_Pin, 0);          // semaforo con 1 segundo de cambio
		  HAL_GPIO_WritePin(amarillo_GPIO_Port, amarillo_Pin, 1);
		  HAL_GPIO_WritePin(rojo_GPIO_Port, rojo_Pin, 0);
		  HAL_Delay(1000);
		  HAL_GPIO_WritePin(verde_GPIO_Port, verde_Pin, 1);
		  HAL_GPIO_WritePin(amarillo_GPIO_Port, amarillo_Pin, 0);
		  HAL_GPIO_WritePin(rojo_GPIO_Port, rojo_Pin, 0);


		  juegoact = 1;    // Permiso para iniciar con los contadores de decadas
	  }

	  switch (cont1){    // Contador de decadas del jugador 1
	  case 0:
		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 0);
		  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 0);
		  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 0);
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 0);

		  break;
	  case 1:
		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 1);
		  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 0);
		  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 0);
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 0);

		  break;
	  case 2:
		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 0);
		  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 1);
		  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 0);
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 0);

		  break;
	  case 3:
		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 0);
		  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 0);
		  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 1);
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 0);

		  break;
	  case 4:
		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, 0);
		  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, 0);
		  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, 0);
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, 1);

		  break;
	  }

	  switch (cont2) {  // contador de decadas del jugador 2
	  case 0:
		  HAL_GPIO_WritePin(luz1_GPIO_Port, luz1_Pin, 0);
		  HAL_GPIO_WritePin(luz2_GPIO_Port, luz2_Pin, 0);
		  HAL_GPIO_WritePin(luz3_GPIO_Port, luz3_Pin, 0);
		  HAL_GPIO_WritePin(luz4_GPIO_Port, luz4_Pin, 0);

		  break;
	  case 1:
		  HAL_GPIO_WritePin(luz1_GPIO_Port, luz1_Pin, 1);
		  HAL_GPIO_WritePin(luz2_GPIO_Port, luz2_Pin, 0);
		  HAL_GPIO_WritePin(luz3_GPIO_Port, luz3_Pin, 0);
		  HAL_GPIO_WritePin(luz4_GPIO_Port, luz4_Pin, 0);

		  break;
	  case 2:
		  HAL_GPIO_WritePin(luz1_GPIO_Port, luz1_Pin, 0);
		  HAL_GPIO_WritePin(luz2_GPIO_Port, luz2_Pin, 1);
		  HAL_GPIO_WritePin(luz3_GPIO_Port, luz3_Pin, 0);
		  HAL_GPIO_WritePin(luz4_GPIO_Port, luz4_Pin, 0);

		  break;
	  case 3:
		  HAL_GPIO_WritePin(luz1_GPIO_Port, luz1_Pin, 0);
		  HAL_GPIO_WritePin(luz2_GPIO_Port, luz2_Pin, 0);
		  HAL_GPIO_WritePin(luz3_GPIO_Port, luz3_Pin, 1);
		  HAL_GPIO_WritePin(luz4_GPIO_Port, luz4_Pin, 0);

		  break;
	  case 4:
		  HAL_GPIO_WritePin(luz1_GPIO_Port, luz1_Pin, 0);
		  HAL_GPIO_WritePin(luz2_GPIO_Port, luz2_Pin, 0);
		  HAL_GPIO_WritePin(luz3_GPIO_Port, luz3_Pin, 0);
		  HAL_GPIO_WritePin(luz4_GPIO_Port, luz4_Pin, 1);

		  break;
	  }

	  if (reportar)  // reportar el ganador del juego
	  {
	    reportar = 0;

	    if (gana == 1){
	    	sprintf(buffer, "Gano el jugador 1\r\n");  //escribir en el buffer ganador 1
	    }
	    else{
	    	sprintf(buffer, "Gano el jugador 2\r\n");  //escribir en el buffer ganador 2
	    }

	    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100); //Transmitir mensaje por UART
	    // se usa strlen() para recorre hasta que termine el mensaje y no recorra el tamaño completo del buffer
	  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, luz4_Pin|luz3_Pin|rojo_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, luz1_Pin|LD2_Pin|led3_Pin|led4_Pin
                          |verde_Pin|amarillo_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, luz2_Pin|led1_Pin|led2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : luz4_Pin luz3_Pin rojo_Pin */
  GPIO_InitStruct.Pin = luz4_Pin|luz3_Pin|rojo_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : luz1_Pin LD2_Pin led3_Pin led4_Pin
                           verde_Pin amarillo_Pin */
  GPIO_InitStruct.Pin = luz1_Pin|LD2_Pin|led3_Pin|led4_Pin
                          |verde_Pin|amarillo_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : luz2_Pin led1_Pin led2_Pin */
  GPIO_InitStruct.Pin = luz2_Pin|led1_Pin|led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : boton2_Pin boton1_Pin */
  GPIO_InitStruct.Pin = boton2_Pin|boton1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //Callback del UART
{


	 if (huart->Instance == USART2){  //Identificar el UART/USART del ISR
		 if (st=='s'){
			 inicio = 1;

		 }
		 HAL_UART_Receive_IT(&huart2, &st, 1); // volver a llamr la función
	 }


}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){  //Callback EXTI

//	if (GPIO_Pin == boton1_Pin){
//		HAL_UART_Transmit(&huart2, (uint8_t*)"B1\r\n", 4, 100);
//	}																//Verificación de que los botones estan funcionando
//	else if (GPIO_Pin == boton2_Pin){
//		HAL_UART_Transmit(&huart2, (uint8_t*)"B2\r\n", 4, 100);
//	}
	if (juegoact) {			//Corre solamente si jueagoact esta activado

		if (GPIO_Pin == boton1_Pin){   //Identificar que boton provoca la interrupción

			if (HAL_GetTick() - ant1 > 200){  //Antirrebote, GetTick es como un timer que corre desde la ejecución
												//Por lo tanto el contador a vanza cuando ya pasaron 2ms desde el ultimo flaco

				ant1 = HAL_GetTick();
				cont1++;
			}
		}
		else if (GPIO_Pin == boton2_Pin){
			if (HAL_GetTick() - ant2 > 200) {      //anterebote boton2
				ant2 = HAL_GetTick();
				cont2++;
			}
		}

		if (cont1 >= 4){     //instrucciones cuando alguien ya gano y llego a 4
			juegoact = 0;
			gana = 1;
			reportar = 1;
		}
		else if (cont2 >= 4){
			juegoact = 0;
			gana = 2;
			reportar = 1;
		}
	  }

	}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
