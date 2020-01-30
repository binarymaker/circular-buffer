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
CIRCULAR_BUFFER_Init(circularBuffer_st * self, void * buffer_ptr, 
                     uint32_t data_size_u8,uint32_t size_u8)
{
  self->buffer_ptr   = buffer_ptr;
  self->data_size_u8 = data_size_u8;
  self->size_u8      = size_u8 ;
  self->head_u8      = 0u;
  self->tail_u8      = 0u;
}

void
CIRCULAR_BUFFER_Write(circularBuffer_st * self, void * data_ptr)
{
  uint8_t * data_u8ptr = (uint8_t *) data_ptr;
  uint8_t * buffer_u8ptr = (uint8_t *) self->buffer_ptr;

  if (CIRCULAR_BUFFER_Available(self) == (self->size_u8 - 1u))
  {
    self->tail_u8 = (self->tail_u8 + 1u) % self->size_u8;
  }

  uint8_t start_u8 = self->head_u8 * self->data_size_u8;

  for(uint8_t i_u8 = 0; i_u8 < self->data_size_u8; i_u8++)
  {
    uint8_t mem_loc_u8 = start_u8 + i_u8;
    buffer_u8ptr[mem_loc_u8] = data_u8ptr[i_u8];
  }

  self->head_u8 = (self->head_u8 + 1u) % self->size_u8;
}

void
CIRCULAR_BUFFER_Read(circularBuffer_st * self, void * data_ptr)
{
  uint8_t * data_u8ptr = (uint8_t *) data_ptr;
  uint8_t * buffer_u8ptr = (uint8_t *) self->buffer_ptr;

  while(CIRCULAR_BUFFER_Available(self) == 0u)
  {
    // TODO timeout
  }

  uint8_t start_u8 = self->tail_u8 * self->data_size_u8;

  for(uint8_t i_u8 = 0; i_u8 < self->data_size_u8; i_u8++)
  {
    data_u8ptr[i_u8] = buffer_u8ptr[start_u8 + i_u8];
  }

  self->tail_u8 = (self->tail_u8 + 1u) % self->size_u8;
}

uint32_t
CIRCULAR_BUFFER_Available(circularBuffer_st * self)
{
  uint32_t len_u8;

  len_u8 = (self->size_u8 + self->head_u8 - self->tail_u8) % self->size_u8;

  return (len_u8);
}

void
CIRCULAR_BUFFER_Flush(circularBuffer_st * self)
{
  self->head_u8 = 0u;
  self->tail_u8 = 0u;
}