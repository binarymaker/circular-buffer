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

#ifndef CIRCULAR_BUFFER_db7f0a9a_368a_11ea_94b0_705a0f25cb51
#define CIRCULAR_BUFFER_db7f0a9a_368a_11ea_94b0_705a0f25cb51

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * \brief Source file version tag
 *        
 *        version info: [15:8] main [7:0] beta
 */
#define __CIRCULAR_BUFFER_VERSION      (0x0001u)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------------*/
typedef struct circularBuffer_s
{
  void * buffer_ptr;
  uint8_t data_size_u8;
  uint8_t size_u8;
  uint8_t head_u8;
  uint8_t tail_u8;
} circularBuffer_st;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


void
CIRCULAR_BUFFER_Init(circularBuffer_st * self, void * buffer_ptr, 
                     uint32_t data_size_u8,uint32_t size_u8);

void
CIRCULAR_BUFFER_Write(circularBuffer_st * self, void * data_ptr);

void
CIRCULAR_BUFFER_Read(circularBuffer_st * self, void * data_ptr);

uint8_t
CIRCULAR_BUFFER_Available(circularBuffer_st * self);

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_db7f0a9a_368a_11ea_94b0_705a0f25cb51 */

