#ifndef _LCD_H_
#define _LCD_H_
#include<Arduino.h>


void lcd_print(String cmd);
void lcd_clear();
void setcursor(int row, int colum);
void lcd_initialize();




#endif