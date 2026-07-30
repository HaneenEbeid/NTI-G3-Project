/*
 * GIE_program.c


 *
 *  Created on: Oct 3, 2024
 *      Author: omarf
 */

#include "../../MCL/STD_TYPES.h"
#include "../../MCL/BIT_MATH.h"

#include "GIE_config.h"
#include "GIE_interface.h"
#include "GIE_register.h"


void GIE_voidEnable(void) {
	SET_BIT(SREG, 7);
}


void GIE_voidDisable(void) {
	CLR_BIT(SREG, 7);
}
