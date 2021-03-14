/*
 * powerstep_lib.h
 *
 *  Created on: 13 мар. 2021 г.
 *      Author: aleks
 */

#ifndef POWERSTEP_POWERSTEP01_LIB_H_
#define POWERSTEP_POWERSTEP01_LIB_H_

#include "powerstep01_def.h"
#include <stdint.h>


void set_param(powerstep01_Registers_t param, uint32_t value);

void setHardStop(void);
void setSoftStop(void);
void setHardHiZ(void);
void setSoftHiZ(void);
void Move(int32_t steps);
uint16_t getStatus(void);


#endif /* POWERSTEP_POWERSTEP01_LIB_H_ */
