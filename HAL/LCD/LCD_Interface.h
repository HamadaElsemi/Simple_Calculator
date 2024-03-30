#ifndef LCD_INT_H
#define LCD_INT_H

void LCD_vid_SendData(u8 Copy_u8Data);

void LCD_vid_SendCmd(u8 Copy_u8Cmd);

void LCD_Vid_Init(void);

void LCD_vid_DisplayClear();

void LCD_vid_GoTo(u8 Copy_u8X,u8 Copy_u8Y);

void LCD_VidSendSpecaialChar(u8 *Pattern,u8 Pattern_Num,u8 Copy_u8XPos,u8 Copy_u8YPos);

void LCD_vid_SendInt(u32 Copy_u8Number);

void LCD_vid_SendString(const s8 *Copy_ps8string);


void LCD_VidSendIntNumber(s64 Copy_u64Number);

#endif
