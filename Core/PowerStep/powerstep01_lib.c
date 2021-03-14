/*
 * powerstep_lib.c
 *
 *  Created on: 13 мар. 2021 г.
 *      Author: aleks
 */

#include "powerstep01_lib.h"

__attribute__((weak))uint8_t xfer_byte(uint8_t byte)
{
	return 0;
}

static void set_param8(powerstep01_Registers_t param, uint8_t value)
{
	xfer_byte(POWERSTEP01_SET_PARAM | param);
	xfer_byte(value);
}


static void set_param16(powerstep01_Registers_t param, uint16_t value)
{
	xfer_byte(POWERSTEP01_SET_PARAM | param);
	xfer_byte((uint8_t)((value & 0xff00) >> 8));
	xfer_byte((uint8_t)((value & 0x00ff) >> 0));
}

static void set_param24(powerstep01_Registers_t param, uint32_t value)
{
	xfer_byte(POWERSTEP01_SET_PARAM | param);
	xfer_byte((uint8_t)((value & 0x00ff0000) >> 16));
	xfer_byte((uint8_t)((value & 0x0000ff00) >> 8));
	xfer_byte((uint8_t)((value & 0x000000ff) >> 0));
}

void set_param(powerstep01_Registers_t param, uint32_t value)
{
	switch(param)
	{
		case POWERSTEP01_ABS_POS:
		case POWERSTEP01_SPEED:
		case POWERSTEP01_MARK:
			set_param24(param, value);
			break;

		case POWERSTEP01_EL_POS:
		case POWERSTEP01_ACC:
		case POWERSTEP01_DEC:
		case POWERSTEP01_MAX_SPEED:
		case POWERSTEP01_MIN_SPEED:
		case POWERSTEP01_FS_SPD:
		case POWERSTEP01_INT_SPD:
		case POWERSTEP01_GATECFG1:
		case POWERSTEP01_CONFIG:
			set_param16(param, (uint16_t)value);
			break;

		case POWERSTEP01_KVAL_HOLD:
		case POWERSTEP01_KVAL_RUN:
		case POWERSTEP01_KVAL_ACC:
		case POWERSTEP01_KVAL_DEC:
		case POWERSTEP01_FN_SLP_ACC:
		case POWERSTEP01_FN_SLP_DEC:
		case POWERSTEP01_K_THERM:
		case POWERSTEP01_ADC_OUT:
		case POWERSTEP01_OCD_TH:
		case POWERSTEP01_STALL_TH:
		case POWERSTEP01_ST_SLP:
		case POWERSTEP01_ALARM_EN:
		case POWERSTEP01_GATECFG2:
		case POWERSTEP01_STEP_MODE:
			set_param8(param, (uint8_t)value);
			break;

		default:
			break;
	}

}

void setHardStop(void)
{
	xfer_byte(POWERSTEP01_HARD_STOP);
}

void setSoftStop(void)
{
	xfer_byte(POWERSTEP01_SOFT_STOP);
}

void setHardHiZ(void)
{
	xfer_byte(POWERSTEP01_HARD_HIZ);
}

void setSoftHiZ(void)
{
	xfer_byte(POWERSTEP01_SOFT_HIZ);
}



__attribute__((weak)) void powerstep_reset_state(uint8_t s)
{
//	if(s)
//		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
//	else
//		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
}

void Move(int32_t steps)
{
	//check if steps value exeeds limits
	//send data
	if(steps > 0)
	{
		xfer_byte(POWERSTEP01_MOVE);
	}
	else
	{
		xfer_byte(POWERSTEP01_MOVE | 1);
		steps *= -1;
	}
	xfer_byte((uint8_t)((steps & 0x00ff0000) >> 16) );
	xfer_byte((uint8_t)((steps & 0x0000ff00) >> 8) );
	xfer_byte((uint8_t)((steps & 0x000000ff) >> 0) );
	xfer_byte(0);
}

uint16_t getStatus(void)
{
	uint8_t byte1 = 0;
	uint8_t byte2 = 0;

	xfer_byte(POWERSTEP01_GET_STATUS);

	byte1 = xfer_byte(0);
	byte2 = xfer_byte(0);

	return ((uint16_t)(byte1 << 8)) | byte2;
}

__attribute__((weak)) void init_stepper_motor(void)
{
//	//set overcurrent limit to maximum
//	set_param(POWERSTEP01_OCD_TH, 31);
//	//set overcurrent limit to maximum
//	set_param(POWERSTEP01_STALL_TH, 31);
//	//step mode - full step
//	set_param(POWERSTEP01_STEP_MODE, 0);
//
//	set_param(POWERSTEP01_CONFIG, 0x3e08);
}
