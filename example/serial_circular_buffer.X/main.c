/**\cond
  ******************************************************************************
  * ______  _                             ___  ___        _               
  * | ___ \(_)                            |  \/  |       | |              
  * | |_/ / _  _ __    __ _  _ __  _   _  | .  . |  __ _ | | __ ___  _ __ 
  * | ___ \| || '_ \  / _` || '__|| | | | | |\/| | / _` || |/ // _ \| '__|
  * | |_/ /| || | | || (_| || |   | |_| | | |  | || (_| ||   <|  __/| |   
  * \____/ |_||_| |_| \__,_||_|    \__, | \_|  |_/ \__,_||_|\_\\___||_|   
  *                                 __/ |                                 
  *                                |___/                                  
  *                                                                       
  * Copyright (C) 2020 Binary Maker - All Rights Reserved
  *
  * This program and the accompanying materials are made available
  * under the terms described in the LICENSE file which accompanies
  * this distribution.
  * Written by Binary Maker <https://github.com/binarymaker>
  ******************************************************************************
  \endcond*/

/* Includes ------------------------------------------------------------------*/
#include "mcu.h"
#include "circular-buffer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static circularBuffer_st cirbuf_rx_sv;
static uint8_t usart_buffer_u8arr[32];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int
main()
{
  MCU_Init();
  CIRCULAR_BUFFER_Init(&cirbuf_rx_sv, usart_buffer_u8arr, 32); // TODO config
  USART_BufferLink(&cirbuf_rx_sv);

  MCU_INTERRUPT_ENABLE();
  while(1)
  {
    USART_Printf("Available %d \n\r", CIRCULAR_BUFFER_Available(&cirbuf_rx_sv));
    if (CIRCULAR_BUFFER_Available(&cirbuf_rx_sv) > 5 - 1)
    {
      while (CIRCULAR_BUFFER_Available(&cirbuf_rx_sv))
      {
        USART_Write(CIRCULAR_BUFFER_Read(&cirbuf_rx_sv));
      }
      USART_Printf("\n\r");
    }
    DELAY_ms(1000);
  }
}
