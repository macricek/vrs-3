/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "assignment.h"

uint8_t minula = 0;
uint8_t akt = 1;
uint8_t current_state = 0;

int main(void)
{
  /*
   *  DO NOT WRITE TO THE WHOLE REGISTER!!!
   *  Write to the bits, that are meant for change.
   */


  /*
   * TASK - configure MCU peripherals so that button state can be read and LED will blink.
   * Button must be connected to the GPIO port A and its pin 3.
   * LED must be connected to the GPIO port A and its pin 4.
   *
   * In header file "assignment.h" define macros for MCU registers access and LED blink application.
   * Code in this file must use these macros for the peripherals setup.
   * Code of the LED blink application is already given so just the macros used in the application must be defined.
   */


	/* Enable clock for GPIO port A*/

			RCC_AHBENR_REG |= (uint32_t)(1 << 17);


		//type your code for GPIOA clock enable here:


	  /* GPIOA pin 3 and 4 setup */
		  //pin 3 tlacidlo 00 je rdy na Input
			GPIOA_MODER_REG	 &= ~(uint32_t)(0x3 << 6); //vyresetujem

			GPIOA_MODER_REG	 &= ~(uint32_t)(0x3 << 8); //vyresetujem 4 pin pre istotu
			GPIOA_MODER_REG	 |= (uint32_t)(1 << 8);	//zapisem 1 aby bolo 01 general purpose output mode


		   /*GPIO OTYPER register*/
			GPIOA_OTYPER_REG &= ~(1 << 4);

		   /*GPIO OSPEEDR register*/
		       //Set Low speed for GPIOA pin 4
			GPIOA_OSPEEDER_REG &= ~(0x3 << 8);

		     /*GPIO PUPDR register, reset*/
		       //Set pull up for GPIOB pin 3 (input)
			GPIOA_PUPDR_REG	 |= (1 << 6);
		       //Set no pull for GPIOB pin 4
			GPIOA_PUPDR_REG	 &= ~(0x3 << 8);

		   //    LL_Init1msTick(SystemCoreClock);  // nastavenie INIT ticku...podla frekvencie procesora

		 enum EDGE_TYPE edge_type;

		       while (1)
	  {
		    	  uint8_t pomocny_stav= BUTTON_GET_STATE;

		    	  edge_type = edgeDetect(pomocny_stav,8);

		    	  uint8_t pomocna =LED_STATUS;

		    	  if(edge_type == RISE)
		    	  {
		    		  if (LED_STATUS == 16) // 2 na 4tu
		    		  {
		    			  LED_OFF;
		    		  }else{
		    			LED_ON;
		    		  }
		    	  }
		    	  minula = pomocny_stav;		//potrebujem si ukladat predchadzajucu
		    	  /* if(BUTTON_GET_STATE)
		    	   	  {
		    	   		  // 0.25s delay
		    	   		  LL_mDelay(250);
		    	   		  LED_ON;
		    	   		  // 0.25s delay
		    	   		  LL_mDelay(250);
		    	   		  LED_OFF;
		    	   	  }
		    	   	  else
		    	   	  {
		    	   		  // 1s delay
		    	   		  LL_mDelay(1000);
		    	   		  LED_ON;
		    	   		  // 1s delay
		    	   		  LL_mDelay(1000);
		    	   		  LED_OFF;
		    	   	  } */
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

	  /* USER CODE END Error_Handler_Debug */
	}

	uint8_t pocet_vzoriek_za_sebou(uint8_t akt, uint8_t pin_state, uint8_t pin_state_before)	// fcn pocitadlo
	{
		if (pin_state == pin_state_before)												// ak je dodrzana sekvencia incrementujeme
		{
			akt++;
		}
		else																			// ak nieje dodrzana sekvencia returnem 1 ku
		{
			akt=1;
		}
		return akt;
	}

	enum EDGE_TYPE edgeDetect(uint8_t pin_state, uint8_t samples)
	{
		akt = pocet_vzoriek_za_sebou(akt, pin_state, minula);		//aktualny pocet rovnakych vzoriek za sebou
			if (akt == samples)										//ak je to tolko, co potrebujeme, tak potencialny check pre rise a fall
			{
				if (pin_state == 1 && current_state == 0)			//ak je na vstupe 1 a aktualny stav je 0, prepni stav a daj RISE
				{
					current_state = 1;
					return RISE;
				}
				else if (pin_state == 0 && current_state == 1)		//ak je na vstupe 0 a aktualny stav je 1, prepni stav a daj FALL
				{
					current_state = 0;
					return FALL;
				}
			}
			return NONE;										//ak nic, tak return NONE;
	}

	#ifdef  USE_FULL_ASSERT
	/**
	  * @brief  Reports the name of the source file and the source line number
	  *         where the assert_param error has occurred.
	  * @param  file: pointer to the source file name
	  * @param  line: assert_param error line source number
	  * @retval None
	  */
	void assert_failed(char *file, uint32_t line)
	{
	  /* USER CODE BEGIN 6 */
	  /* User can add his own implementation to report the file name and line number,
	     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	  /* USER CODE END 6 */
	}
	#endif /* USE_FULL_ASSERT */

	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
