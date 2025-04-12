#include "lcd.h"


int D4 = 30;
int D5 = 28;
int D6 = 26;
int D7 = 24;

int RS = 34;
int E = 32;


// instead of using liquide crystall connect to the LCD directedly and initalize 4 bit 2 line mode 

void lcd_command(char cmd, bool data_mode, bool lcd_clear){
  digitalWrite(RS, data_mode);    
  // get address of cmd then shift X bits and then write data to digital pins 4-7
  // 4 bit mode requers that you pulse E after the first nibble.
  digitalWrite(D4, (cmd & 0b00010000) >> 4);
  digitalWrite(D5, (cmd & 0b00100000) >> 5);
  digitalWrite(D6, (cmd & 0b01000000) >> 6);
  digitalWrite(D7, (cmd & 0b10000000) >> 7);
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(D4, (cmd & 0b00000001) >> 0);
  digitalWrite(D5, (cmd & 0b00000010) >> 1);
  digitalWrite(D6, (cmd & 0b00000100) >> 2);
  digitalWrite(D7, (cmd & 0b00001000) >> 3);
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
  if (lcd_clear == true){
    delayMicroseconds(2000);
  }

}

void lcd_initialize()
{
pinMode(D4,OUTPUT);
pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(RS,OUTPUT);
pinMode(E,OUTPUT);
delay(2000);
  lcd_command(0x33, false, false); //00110111 00110011
  delay(20);
  lcd_command(0x32, false, false); //00110010 00110010
  delay(20);
  lcd_command(0x2C, false, false); //00101100 00100000 0x2c
  delay(20);
  lcd_command(0x01, false, false); //0000001  00001000 clear 
  delay(20);
  lcd_command(0x0c, false, false); //00001110  0000001  displayon blinker off
  delay(20);
  lcd_command(0x06, false, false); //00000110 00000110 increment cursor and shift display
  delay(20);
  lcd_command(0x80, false, false); //10000000 setcursor first line
  delay(20);
  Serial.println("LCD ready");
}


void lcd_print(String cmd){
 char char_data[cmd.length()+1] = {};
 cmd.toCharArray(char_data, cmd.length()+1);   
 for(unsigned int i; i< (sizeof(char_data)-1);i++){
    lcd_command(char_data[i], true, false);
  
  }
  delayMicroseconds(10);
  
}


void setcursor(int row, int col){
  if(row == 0){
    lcd_command(0x80, false, false);
  }
  if(row == 1){
    lcd_command(0xc0, false, false);
  }
  if(row == 2){
    lcd_command(0x94, false, false);
  }
  if(row == 3){
    lcd_command(0xD4, false, false);
  }
  delayMicroseconds(10);
}

void lcd_clear(){
    lcd_command(0x01, false, true);
    delayMicroseconds(10);
}

  

void (* resetFunc) (void)=0;


