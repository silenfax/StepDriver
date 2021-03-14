# powerstep01
bring up nucleo motor control board
There is PowerStep folder, that contains powerstep01 control library.
Library will not work until 3 weak functions will not realized.
xfer_byte wrap spi send and read byte
```C
uint8_t xfer_byte(uint8_t byte)
{
	uint8_t tx = byte;
	uint8_t rx = 0;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 1000);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
	return rx;
}
```
powerstep_reset_state wrap rst/stby pin control
```C
void powerstep_reset_state(uint8_t s)
{
if(s)
		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
}

```

init_stepper_motor sets limit for stall, overcurrent event, step mode and any other settings that powerstep01 ic can manage.

```C
void init_stepper_motor(void)
{
	set_param(POWERSTEP01_KVAL_HOLD, 64);
	set_param(POWERSTEP01_KVAL_RUN, 64);
	set_param(POWERSTEP01_KVAL_ACC, 64);
	set_param(POWERSTEP01_KVAL_DEC, 64);
	set_param(POWERSTEP01_OCD_TH, 31);
	set_param(POWERSTEP01_STALL_TH, 31);
	set_param(POWERSTEP01_STEP_MODE, 0);
	set_param(POWERSTEP01_CONFIG, 0x3e08);
}
```

Motion control commands. 
Move command rotates the motor by the specified number of steps, the direction depends on the sign.
There are 4 stopping commands, "HiZ" switch bridges to high impedance state, so you can rotate shaft manually, "Stop" commands 
hold the shaft with a force given by parameter KVAL_HOLD. Soft and Hard types differ in the moment of triggering and it is described in datasheet.

```
void setHardStop(void);
void setSoftStop(void);
void setHardHiZ(void);
void setSoftHiZ(void);
void Move(int32_t steps);
```

Status of a driver can be read by function 
```
uint16_t getStatus(void);
```

