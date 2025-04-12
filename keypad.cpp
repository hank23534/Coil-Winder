#include "keypad.h"



byte R1 = 45;
byte R2 = 43;
byte R3 = 41;
byte R4 = 39;

byte C1 = 47;
byte C2 = 49;
byte C3 = 51;
byte C4 = 53;
byte colums[4] = {47, 49, 51, 53};
byte highColum;
byte highRow;
char key[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


void keypad_init(){
    pinMode(R1, INPUT_PULLUP);
    pinMode(R2, INPUT_PULLUP);
    pinMode(R3, INPUT_PULLUP);
    pinMode(R4, INPUT_PULLUP);

    pinMode(C1, OUTPUT);
    pinMode(C2, OUTPUT);
    pinMode(C3, OUTPUT);
    pinMode(C4, OUTPUT);



}


char waitkey(){
    bool i = true;
    int k=1;

    while(i == true){

       
            switch(k){
                case 1:
                highColum = 1;
                digitalWrite(C1, LOW);
                digitalWrite(C2, HIGH);
                digitalWrite(C3, HIGH);
                digitalWrite(C4, HIGH);
                
                if (digitalRead(R1) == LOW)
                {
                 highRow = 1;
                 i = false;
                }
                if (digitalRead(R2) == LOW)
                {
                 highRow = 2;
                 i = false;
                }
                if (digitalRead(R3) == LOW)
                {
                 highRow = 3;
                 i = false;
                }
                if (digitalRead(R4) == LOW)
                {
                 highRow = 4;
                 i = false;
                }
               
                break;

                case 2:
                highColum = 2;
                digitalWrite(C1, HIGH);
                digitalWrite(C2, LOW);
                digitalWrite(C3, HIGH);
                digitalWrite(C4, HIGH);
                
                if (digitalRead(R1) == LOW)
                {
                 highRow = 1;
                 i = false;
                }
                if (digitalRead(R2) == LOW)
                {
                 highRow = 2;
                 i = false;
                }
                if (digitalRead(R3) == LOW)
                {
                 highRow = 3;
                 i = false;
                }
                if (digitalRead(R4) == LOW)
                {
                 highRow = 4;
                 i = false;

                }

                break;

                case 3:
                highColum = 3;
                digitalWrite(C1, HIGH);
                digitalWrite(C2, HIGH);
                digitalWrite(C3, LOW);
                digitalWrite(C4, HIGH);
                
                if (digitalRead(R1) == LOW)
                {
                 highRow = 1;
                 i = false;
                }
                if (digitalRead(R2) == LOW)
                {
                 highRow = 2;
                 i = false;
                }
                if (digitalRead(R3) == LOW)
                {
                 highRow = 3;
                 i = false;
                }
                if (digitalRead(R4) == LOW)
                {
                 highRow = 4;
                 i = false;

                }

                break;

                case 4:
                highColum = 4;
                digitalWrite(C1, HIGH);
                digitalWrite(C2, HIGH);
                digitalWrite(C3, HIGH);
                digitalWrite(C4, LOW);
                
                if (digitalRead(R1) == LOW)
                {
                 highRow = 1;
                 i = false;
                }
                if (digitalRead(R2) == LOW)
                {
                 highRow = 2;
                 i = false;
                }
                if (digitalRead(R3) == LOW)
                {
                 highRow = 3;
                 i = false;
                }
                if (digitalRead(R4) == LOW)
                {
                 highRow = 4;
                 i = false;

                }

                break;

                default:
                break;
                
            }

        
        if(k == 4){
            k=0;
        }

        k++;
    }
    
        Serial.print(highColum);
        Serial.print(" ");
        Serial.println(highRow);
    char rkey = key[highRow-1][highColum-1];
    delay(200);

    return rkey;

}