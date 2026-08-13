/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

//Variables: Se definen las variables a utilizar en la aplicacion.
//tiempo: se toma una copia del reloj del sistema para usos practicos y definir ventanas de lectura
uint32_t tiempo_parpadeo=500;
uint8_t estado=0;
static uint32_t tiempo=HAL_GetTick;
uint8_t contador=0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
// Se definen las interrupciones y lo que debe realizar el sistema al tenerlas,como definir valores a las variables anteriormente definidas
// Utilizamos 2 botones Izquierda-Derecha,a los cuales les asignamos unas funcionalidades en caso,
//de que ocurran, del mismo modo se transmite un mensaje a travez de la UART que indica que boton se presiono
	 if(GPIO_Pin==Izquierda_Pin)
		  {HAL_UART_Transmit(&huart2, "d_izquierda\r\n", 13, 10);
		  HAL_GPIO_WritePin(LD_GPIO_Port, LI_Pin, 0);
		  estado=1;
		  contador =3;
		 }
	 if(GPIO_Pin==Derecha_Pin)
		   {HAL_UART_Transmit(&huart2, "d_derecha\r\n", 13, 10);
		    HAL_GPIO_WritePin(LD_GPIO_Port, LD_Pin, 0);
		   estado=2;
		   contador =3;
		   }


//Filtro para evitar los rebotes al momento de presionar los botones y que el sistema no los tome
// En las mismas lineas de codigo de implementa el que si se presiona 2 veces en menos de 500 ms,
//la luz parpadee indefinidamente.

	 if (GPIO_Pin == Izquierda_Pin) {

		if ((HAL_GetTick() < (tiempo + 500))&&(HAL_GetTick() > (tiempo + 150))) { //se define una ventana de 150 ms donde el sistema no lea el boton
					contador = 0xFFFFFF; // contador con un numero exageradamente grande para el parpadeo
				} else {
					contador = 5;
				}
				tiempo = HAL_GetTick();
			}
	if (GPIO_Pin == Derecha_Pin) {
				if ((HAL_GetTick() < (tiempo + 500))&&(HAL_GetTick() > (tiempo + 150))) { //
					contador = 0xFFFFFF;
				} else {
					contador = 5;
				}
				tiempo = HAL_GetTick();

			}
}

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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

	//Al ocurrir alguna de las 2 posiboles interrupciones en el sistema ,el sistema nos redirige a 2 posibles estados a aplicar,
	//donde si se presiona el boton Derecha(S3) entraremos al estado 1 o el boton Izquierda(S1) ,donde en cualquiera de los 2
	// se realiza un bucle para que las luces cambien su estado el numero de veces que la variable contador nos lo indique,
	// del mismo modo aseguramos el correcto funcionamiento del codigo apagando los otros componentes que no se utilizaran en ese momento


	  if (estado==2){//estado correspondiente a presionar el boton Derecha(s1)
	  	   		if((HAL_GetTick()-tiempo)>tiempo_parpadeo){
	  	   			HAL_GPIO_WritePin(LI_GPIO_Port, LI_Pin, 1);//Apagala luz izquierda
	  	   			HAL_UART_Transmit(&huart2, "d_derecha\r\n", 13, 10);//transmite la informacion de que se esta girando a la derecha
	  	   			HAL_GPIO_TogglePin(LD_GPIO_Port, LD_Pin);//cambia el estado de la luz derecha
	  	   			tiempo=HAL_GetTick();
	  	   			contador--;
	  	   			if ((contador==0)){
	  	   				estado=0;
	  	   			 HAL_GPIO_WritePin(LD_GPIO_Port, LD_Pin, 1);

	  	   			}

	  	   		}
	  	   		}

	  	if (estado==1){//estado correspondiente a presionar el boton Izquierda(s3)
	  		if((HAL_GetTick()-tiempo)>tiempo_parpadeo){
	  			HAL_UART_Transmit(&huart2, "d_izquierda\r\n", 13, 10);//transmite la informacion de que se esta girando a la izquierda
	  			HAL_GPIO_WritePin(LD_GPIO_Port, LD_Pin, 1);//Apagala luz derecha
	  			HAL_GPIO_TogglePin(LI_GPIO_Port, LI_Pin);//cambia el estado de la luz derecha
	  			tiempo=HAL_GetTick();
	  			contador--;
	  			if ((contador==0)){
	  				estado=0;
	  				  HAL_GPIO_WritePin(GPIOA, LI_Pin, 1);

	  			}

	  		 }
	  	   }
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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

#ifdef  USE_FULL_ASSERT
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
