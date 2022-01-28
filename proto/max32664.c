/* max32664.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "sensor.h"
#include "cli/cli.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "max32664_io.h"

#define SPO2_I2C_ADDR        (0x55)
#define DISABLE                0x00
#define ENABLE                 0x01
#define ALGO_DATA 0x02

static I2C_HandleTypeDef * hi2c1 = NULL;
static 

// message types: family, index byte stored in flash
static const HostCmdType cmd_get_status = {0x00, 0x00};


static int sensorProbe(uint16_t addr)
{
	HAL_StatusTypeDef ret;

	// TODO: see if device(s) are ready; add a retry mechanism
	ret = HAL_I2C_IsDeviceReady (hi2c1, (addr<<1) , 3, HAL_MAX_DELAY);
	/*
	  HAL_OK       = 0x00U,
	  HAL_ERROR    = 0x01U,
	  HAL_BUSY     = 0x02U,
	  HAL_TIMEOUT  = 0x03U
	*/

	return (int)ret;
}

static uint8_t issueHostCmd(HostCmdType cmd)
{
	// send family, index, data...
	// read status byte
	// return status byte 
}

static uint8_t getStatus(void)
{
	return issue_host_command(cmd_get_status);
}

int max32664Init(I2C_HandleTypeDef * i2cDev, void * resetGpio, void * mfioGpio)
{
  /* 
  digitalWrite(_mfioPin, HIGH);
  digitalWrite(_resetPin, LOW);
  delay(10);
  digitalWrite(_resetPin, HIGH);
  delay(1000);
  pinMode(_mfioPin, INPUT_PULLUP); // To be used as an interrupt later

  uint8_t responseByte = readByte(READ_DEVICE_MODE, 0x00); // 0x00 only possible Index Byte.
  return responseByte;
  */	
}

int max32664Attach()
{
  uint8_t ret = 0;

  statusChauf = setOutputMode(ALGO_DATA); // Just the data
  if( ret != SUCCESS )
    return ret;

  ret = setFifoThreshold(0x01); // One sample before interrupt is fired.
  if( ret != SUCCESS )
    return ret;

  ret = agcAlgoControl(ENABLE); // One sample before interrupt is fired.
  if( ret != SUCCESS )
    return ret;

  ret = max30101Control(ENABLE);
  if( ret != SUCCESS )
    return ret;

  ret = maximFastAlgoControl(mode);
  if( ret != SUCCESS )
    return ret;

  _userSelectedMode = mode;
  _sampleRate = readAlgoSamples();

  delay(1000);
  return SUCCESS;

}


// Family Byte: ENABLE_ALGORITHM (0x52), Index Byte:
// ENABLE_WHRM_ALGO (0x02)
// This function enables (one) or disables (zero) the wrist heart rate monitor
// algorithm.
uint8_t SparkFun_Bio_Sensor_Hub::maximFastAlgoControl(uint8_t mode) {

  if( mode == 0 || mode == 1 || mode == 2) {}
  else
    return INCORR_PARAM;

  uint8_t statusByte = enableWrite(ENABLE_ALGORITHM, ENABLE_WHRM_ALGO, mode);
  if (statusByte != SUCCESS)
    return statusByte;
  else
    return SUCCESS;

}

// Family Byte: READ_ALGORITHM_CONFIG (0x51), Index Byte:
// READ_AGC_NUM_SAMPLES (0x00), Write Byte: READ_AGC_NUM_SAMPLES_ID (0x03)
// This function changes the number of samples that are averaged.
// It takes a paramater of zero to 255.
uint8_t SparkFun_Bio_Sensor_Hub::readAlgoSamples() {

  uint8_t samples = readByte(READ_ALGORITHM_CONFIG, READ_AGC_NUM_SAMPLES, READ_AGC_NUM_SAMPLES_ID );
  return samples;

}

// Family Byte: OUTPUT_MODE (0x10), Index Byte: SET_FORMAT (0x00),
// Write Byte : outputType (Parameter values in OUTPUT_MODE_WRITE_BYTE)
uint8_t SparkFun_Bio_Sensor_Hub::setOutputMode(uint8_t outputType) {

  if ( outputType > SENSOR_ALGO_COUNTER ) // Bytes between 0x00 and 0x07
    return INCORR_PARAM;

  // Check that communication was successful, not that the IC is outputting
  // correct format.
  uint8_t statusByte = writeByte(OUTPUT_MODE, SET_FORMAT, outputType);
  if( statusByte != SUCCESS)
    return statusByte;
  else
    return SUCCESS;
