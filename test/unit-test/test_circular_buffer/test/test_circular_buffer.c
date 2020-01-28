/**
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
  * Copyright (C) 2019 Binary Maker - All Rights Reserved
  *
  * This program and the accompanying materials are made available
  * under the terms described in the LICENSE file which accompanies
  * this distribution.
  * Written by Binary Maker <https://github.com/binarymaker>
  ******************************************************************************
  */

#include "unity.h"
#include "circular-buffer.h"

void
setUp()
{

}

void
tearDown()
{

}

void
test_circular_buffer_write_read_should_update_buffer_uint16()
{
  circularBuffer_st data_buffer;
  uint16_t data_u16arr[16];
  const uint8_t data_arrsize = 10u;
  uint16_t num_u16arr[10] = { 1987, 1985, 1983, 
                              1922, 1935, 1947, 
                              1955, 2000, 2015, 
                              2020
                            };

/* ############################### BUFFER INIT ############################## */

  CIRCULAR_BUFFER_Init(&data_buffer, data_u16arr, sizeof(uint16_t), 16u);

  TEST_ASSERT_EQUAL(0u, data_buffer.head_u32);
  TEST_ASSERT_EQUAL(0u, data_buffer.tail_u32);
  TEST_ASSERT_EQUAL(16u, data_buffer.size_u32);
  TEST_ASSERT_EQUAL(sizeof(uint16_t), data_buffer.data_size_u32);
  TEST_ASSERT_EQUAL(data_u16arr, data_buffer.buffer_ptr);
  
/* ######################### BUFFER WRITE OPERATION ######################### */

  for (uint8_t i_u8 = 0; i_u8 < data_arrsize; i_u8++)
  {
    CIRCULAR_BUFFER_Write(&data_buffer, (void *)&num_u16arr[i_u8]);
  }

  TEST_ASSERT_EQUAL(data_arrsize, CIRCULAR_BUFFER_Available(&data_buffer));

/* ########################## BUFFER READ OPERATION ######################### */
  uint16_t pop_date_u16;

  for (uint8_t i_u8 = 0; i_u8 < data_arrsize; i_u8++)
  {
    CIRCULAR_BUFFER_Read(&data_buffer, (void *)&pop_date_u16);
    TEST_ASSERT_EQUAL(num_u16arr[i_u8], pop_date_u16);
  }
  
  TEST_ASSERT_EQUAL(0u, CIRCULAR_BUFFER_Available(&data_buffer));

/* ######################## 2ND TIME WRITE OPERATION ######################## */

/* ######################### BUFFER WRITE OPERATION ######################### */

  for (uint8_t i_u8 = 0; i_u8 < data_arrsize; i_u8++)
  {
    CIRCULAR_BUFFER_Write(&data_buffer, (void *)&num_u16arr[i_u8]);
  }

  TEST_ASSERT_EQUAL(data_arrsize, CIRCULAR_BUFFER_Available(&data_buffer));
 
/* ########################## BUFFER READ OPERATION ######################### */

  for (uint8_t i_u8 = 0; i_u8 < data_arrsize; i_u8++)
  {
    CIRCULAR_BUFFER_Read(&data_buffer, (void *)&pop_date_u16);
    TEST_ASSERT_EQUAL(num_u16arr[i_u8], pop_date_u16);
  }

  TEST_ASSERT_EQUAL(0u, CIRCULAR_BUFFER_Available(&data_buffer));
}