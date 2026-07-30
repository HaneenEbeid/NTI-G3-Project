/*
 * KPD_config.h
 *
 *  Created on: Sep 20, 2024
 *      Author: elwady
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT			DIO_u8PORTB

#define KPD_ROWS_NUMBER         4
#define KPD_COLS_NUMBER         4


#define KPD_R1_PIN              DIO_u8PIN4
#define KPD_R2_PIN              DIO_u8PIN5
#define KPD_R3_PIN              DIO_u8PIN6
#define KPD_R4_PIN              DIO_u8PIN7
#define KPD_C1_PIN              DIO_u8PIN0
#define KPD_C2_PIN              DIO_u8PIN1
#define KPD_C3_PIN              DIO_u8PIN2
#define KPD_C4_PIN              DIO_u8PIN3


#define KPD_SHAPE               {{'7','8','9','/'}, \
                                {'4','5','6','*'}, \
                                {'1','2','3','-'}, \
                                {'C','0','=','+'}}

#endif /* KPD_CONFIG_H_ */
