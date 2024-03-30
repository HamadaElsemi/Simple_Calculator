/*
 * KPD_Prog.c
 *
 *  Created on: Mar 20, 2024
 *      Author: Eng Hamada Ahmed
 */
/***********************************LIB***********************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/***********************************HAL***********************************/
#include "KPD_Config.h"
#include "KPD_Interface.h"
#include "KPD_Private.h"
/************************************MCAL*********************************/
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Config.h"
#include "../../MCAL/DIO/DIO_Private.h"
/*************************************DELAY*******************************/
#include <util/delay.h>



void Keypad_Init() {
    DDRB |= 0x0F;    // PB 0-3 output for columns.
    DDRB &= 0xF0;    // PB 4-7 input for Rows.
    PORTB |= 0xF0;   // PB 4-7 pull up for Rows
}

u8 Keypad_u8GetPressedKey(){
		u8 Keypad_Arr[4][4]={ {'7','8','9','/'} ,{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'} };
		u8 PressedKey;
		u8 DataInput,Col,Row;
		              /*set one of cols to gnd */


	 for(Col=0;Col<4;Col++)
		 {   DIO_Vid_SetPinValue(KEYPAD_COL_PORT, Col_Arr[Col],PinLow);
		/*check the input of rows pins if one of key was pressed while col(0)is ground then the input value will be gnd */
		    for(Row=0;Row<4;Row++)
		    {
		      DIO_Vid_GetPinValue(KEYPAD_ROW_PORT,Row_Arr[Row],&DataInput);
		      /*check pin value equal to zero or not */
		      if(DataInput==0)
		        {  /* store the asci value of pressed key */
		    	  _delay_ms(200);
		    	PressedKey=Keypad_Arr[Row][Col];

		      /* keep storing the asci value of pressed key if the key was still pressing */
		      while(DataInput==0)
		           {
		    	  DIO_Vid_GetPinValue(KEYPAD_ROW_PORT,Row_Arr[Row],&DataInput);   /* return the pressed key value to be displayed on lcd or stored*/
		           }

		      return PressedKey;
		        }
		    }
		    DIO_Vid_SetPinValue(KEYPAD_COL_PORT, Col_Arr[Col],PinHigh);
		 }
		/* if there is no key is pressed return message '101'return '0';*/
	return 101;
	// return PressedKey;
	  }



