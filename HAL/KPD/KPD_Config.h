/*
 * KPD_Config.h
 *
 *  Created on: Mar 20, 2024
 *      Author: Eng Hamada Ahmed
 */

#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_

#include "../../MCAL/DIO/DIO_Interface.h"
u8 Col_Arr[4]={pin0,pin1,pin2,pin3}; // cols pins start from col 1 to col 4 as shown on keypad bcp

u8 Row_Arr[4]={pin0,pin1,pin2,pin3};// rows pins start from row 1 to row 4 as shown on keypad bcp

#define KEYPAD_COL_PORT   Port_B  // the first half of port D was connected to cols as output height
#define KEYPAD_ROW_PORT   Port_A  // the first half of port D was connected to cols as input pull up


#endif /* HAL_KPD_KPD_CONFIG_H_ */
