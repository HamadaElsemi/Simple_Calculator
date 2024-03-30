#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include <util/delay.h>
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"



void LCD_vid_SendData(u8 Copy_u8Data){

	DIO_Vid_SetPinValue(CONTROL_PORT, RS_PIN,PinHigh);    //RS=1        DATA SHEAT
	DIO_Vid_SetPinValue(CONTROL_PORT, RW_PIN,PinLow);     //RW=0
	DIO_Vid_SetPortValue(DATA_PORT, Copy_u8Data);
	DIO_Vid_SetPinValue(CONTROL_PORT, E_PIN,PinHigh);     //E=1&0
	_delay_ms(3);
	DIO_Vid_SetPinValue(CONTROL_PORT, E_PIN,PinLow);

}

void LCD_vid_SendCmd(u8 Copy_u8Cmd){

	DIO_Vid_SetPinValue(CONTROL_PORT, RS_PIN,PinLow);   //RS=0        DATA SHEAT
	DIO_Vid_SetPinValue(CONTROL_PORT, RW_PIN,PinLow);   //RW=0
	DIO_Vid_SetPortValue(DATA_PORT, Copy_u8Cmd);
	DIO_Vid_SetPinValue(CONTROL_PORT, E_PIN,PinHigh);    //E=1&0
	_delay_ms(3);
	DIO_Vid_SetPinValue(CONTROL_PORT, E_PIN,PinLow);

}

void LCD_Vid_Init(void){

	_delay_ms(40);
	LCD_vid_SendCmd(0b00111100);
	_delay_ms(1);

	LCD_vid_SendCmd(0b00001100);

	LCD_vid_SendCmd(1);

}

void LCD_vid_DisplayClear(){
	LCD_vid_SendCmd(1);
}
void LCD_vid_GoTo(u8 Copy_u8X,u8 Copy_u8Y){

	if(Copy_u8X==1){
		Copy_u8Y +=0x40;
	}

	LCD_vid_SendCmd(Copy_u8Y+0b10000000);       //the place which i want go to in DDRAM//
}

//x=0for first line and 1 for secondline
//y=0--->16
void LCD_VidSendSpecaialChar(u8 *Pattern,u8 Pattern_Num,u8 Copy_u8XPos,u8 Copy_u8YPos){

u8 Local_Adress=8*Pattern_Num;
LCD_vid_SendCmd(0b01000000+Local_Adress);
for(u8 i=0;i<8;i++){
	LCD_vid_SendData(Pattern[i]);
}
LCD_vid_GoTo(Copy_u8XPos,Copy_u8YPos);
LCD_vid_SendData(Pattern_Num);
}


void LCD_vid_SendInt(u32 Copy_u8Number){

	if(Copy_u8Number!=0){
		LCD_vid_SendInt(Copy_u8Number/10);
		LCD_vid_SendData((Copy_u8Number%10)+48);


	}
}

// LCD Function Send Integer Number
void LCD_VidSendIntNumber(s64 Copy_u64Number){

	static u8 i=0;
	if(Copy_u64Number < 0){
		LCD_vid_SendData('-');
		Copy_u64Number = Copy_u64Number*(-1);
	}
	if(Copy_u64Number !=0 )
	{   i=1;
		LCD_VidSendIntNumber(Copy_u64Number/10);
		LCD_vid_SendData((Copy_u64Number%10) +'0');
		i=0;
	}
	else if((Copy_u64Number == 0)&&(i == 0)){
		LCD_vid_SendData('0');
	}

}


void LCD_vid_SendString(const s8 *Copy_ps8string){

	while(*Copy_ps8string!='\0'){

		LCD_vid_SendData(*Copy_ps8string);
		Copy_ps8string++;
	}


}



