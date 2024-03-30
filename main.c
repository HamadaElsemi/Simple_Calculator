/*
 * main.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Eng Hamada Ahmed
 *
 */
/*************************LIB**************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/*************************MCAL*************************/
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/DIO/DIO_Config.h"
#include "MCAL/DIO/DIO_Private.h"

/*************************HAL**************************/
#include"HAL/LCD/LCD_Interface.h"

/*************************Delay*************************/
#include <util/delay.h>

int main(){

		DIO_Vid_SetPortDirection(Port_C,output);
		DIO_Vid_SetPortDirection(Port_D,output);
		LCD_Vid_Init();

		//Keypad_Init();

		DIO_Vid_SetPortDirection(Port_B,output);   //Column output
		DIO_Vid_SetPortDirection(Port_A,input);    //Row input pull up
		DIO_Vid_SetPortValue(Port_A,0b00001111);         //pullup


		s16 Local_s16Num1=0;
		s16 Local_s16Num2=0;
		u8  Local_u8Sign=0;
		s32 Lacal_s32Result=0;
		u8 Local_u8Flag=0;

		u8 Local_KeyPressed;

				LCD_vid_GoTo(0,3);
				LCD_vid_SendString("Welcome !");

				LCD_vid_GoTo(1,0);
				LCD_vid_SendString("MP1:Simple Calc,");
				_delay_ms(3000);
				LCD_vid_DisplayClear();

		while(1){

			Local_KeyPressed=Keypad_u8GetPressedKey();

			if(Local_KeyPressed == 'C'){

				LCD_vid_DisplayClear();
				Local_KeyPressed = 101;
			}

			else{

			              /*(1-NUM1) (2-Sign-->+,-,/,*) (3-NUM2) (4- =) (5- Result) */

		/*(1)*/if(Local_KeyPressed != 101 && Local_KeyPressed != '=' && Local_KeyPressed != '+' && Local_KeyPressed != '-' && Local_KeyPressed != '*'&& Local_KeyPressed != '/' && Local_u8Flag == 0){

					Local_s16Num1 *=10;
					Local_s16Num1 += (Local_KeyPressed-'0');
	/* Local_s16Num1 *=10  : this operation effectively shifts the digits of Local_s16Num1 one place to the left,
	 *  making room for a new digit to be added on the right.
	 *
	 *  Local_s16Num1 += (Local_KeyPressed - '0');: This line takes the current value of Local_s16Num1,
	 *   and adds to it the numeric value corresponding to the character that the user pressed ('0' to '9').
	 *   This operation effectively appends the newly pressed digit to the right of the existing number.
	 *
	      * Ex: If initial number=0,user press (5)
		  *    Local_s16Num1 *=10 --> 0*10=0  (old)
		  *    Local_s16Num1 += (Local_KeyPressed-'0')---> New= 0(old) + 5 - 48(askii of zero)=5
	      *
		  *    after that press (3):
		  *    Local_s16Num1 *=10 --> 5*10=50
		  *    Local_s16Num1 += (Local_KeyPressed-'0')---> New= 50 + 3 - 48(askii of zero)=53-0=53
		  *
		  *    after that press (4)
		  *    Local_s16Num1 *=10 --> 53*10=530
		 *    Local_s16Num1 += (Local_KeyPressed-'0')---> New= 530 + 4 - 48(askii of zero)=534-0=534
					 *    and so on...
					 *  */

					LCD_vid_SendData(Local_KeyPressed);
					Local_KeyPressed=101;   //Not Pressed
			}


	     /*(2)*/else if (Local_KeyPressed != 101  && ( Local_KeyPressed == '+'  ||  Local_KeyPressed == '-'  ||  Local_KeyPressed == '*'  ||  Local_KeyPressed == '/') )
			{
				Local_u8Sign = Local_KeyPressed ;
				Local_u8Flag = 1 ;

				LCD_vid_SendData(Local_KeyPressed);
				Local_KeyPressed=101;
			}

		/*(3)*/	else if (Local_KeyPressed != 101 && Local_KeyPressed != '=' && Local_u8Flag == 1 )
					{
						Local_s16Num2 *= 10 ;
						Local_s16Num2 += (Local_KeyPressed - '0') ;

						LCD_vid_SendData(Local_KeyPressed) ;
						Local_KeyPressed = 101 ;
					}

		/*(4)*/else if (Local_KeyPressed == '=')
					{
						LCD_vid_SendData(Local_KeyPressed) ;

						if (Local_u8Sign == '+')//(5)
						{
							Lacal_s32Result = Local_s16Num1 + Local_s16Num2 ;
						}
						else if (Local_u8Sign == '-')
						{
							Lacal_s32Result = Local_s16Num1 - Local_s16Num2;
						}
						else if (Local_u8Sign == '*')
						{
							Lacal_s32Result = Local_s16Num1 * Local_s16Num2 ;
						}
						else if (Local_u8Sign == '/')
						{
							Lacal_s32Result = Local_s16Num1 / Local_s16Num2 ;
						}

						LCD_VidSendIntNumber(Lacal_s32Result);

						 Local_s16Num1=0;
						 Local_s16Num2=0;
						 Local_u8Sign=0;
						 Lacal_s32Result=0;
						 Local_u8Flag=0;

					}
			}
		}

		return 0;
}

