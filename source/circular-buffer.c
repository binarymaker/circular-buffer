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
#include "circular-buffer.h"
#include "circular-buffer-cfg.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void
CIRCULAR_BUFFER_Init(circularBuffer_st * self_sv, uint8_t * buffer_u8ptr, 
                      uint16_t size_u16)
{
  self_sv->size_u16 = size_u16;
  self_sv->buffer_u8ptr = buffer_u8ptr;
  self_sv->head_u16 = 0;
  self_sv->tail_u16 = 0;
}


void
CIRCULAR_BUFFER_Write(circularBuffer_st * self_sv, uint8_t data_u8)
{
  if (CIRCULAR_BUFFER_Available(self_sv) == self_sv->size_u16 - 1)
  {
    self_sv->tail_u16 = (self_sv->tail_u16 + 1) % self_sv->tail_u16;
  }

  self_sv->buffer_u8ptr[self_sv->head_u16] = data_u8;
  self_sv->head_u16 = (self_sv->head_u16 + 1) % self_sv->size_u16;
}

uint8_t
CIRCULAR_BUFFER_Read(circularBuffer_st * self_sv)
{
  uint8_t data_u8;

  while(CIRCULAR_BUFFER_Available(self_sv) <= 0); // TODO timeout
  data_u8 = self_sv->buffer_u8ptr[self_sv->tail_u16];
  self_sv->tail_u16 = (self_sv->tail_u16 + 1) % self_sv->size_u16;

  return data_u8;
}

uint16_t
CIRCULAR_BUFFER_Available(circularBuffer_st * self_sv)
{
  uint16_t len_u16;

  len_u16 = (self_sv->size_u16 + self_sv->head_u16 - self_sv->tail_u16) % 
            self_sv->size_u16;

  return (len_u16);
}
