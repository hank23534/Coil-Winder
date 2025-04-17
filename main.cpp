#include "header.h"
#include "keypad.h" 
#include "lcd.h" 
#include <math.h> 




/*
A small program for a coil winder that uses an Arduino Mega 2560 and has the following features:
- Ability to calulate turns from H
- Ability to find at an angle theta 
- Ability to support several coil molds aswell as custom coils
- Ability to interface to keypad & LCD (terminal is functional however it has very few functions)
- currently air core coils are supported however in version 2 the ability to choose different core materials will be added
*/



// 400 steps per mm
// set of variables for calculating coil turns from inductance
double D;
double L;
double l;
double A;
const double MC= .00000125663706; // for air 
double T;
double lmm;


char cmt; // coil mold type
int turns; // number of turns
int theta; // angle to wind wire at
int guid_distance; // distance of wire guid from coil mold
char unit = 'U'; // could be U  = micro, M = milli, N = Nano
bool windatangle = false; 
bool needtocalc = true;
bool ableangle = false;
byte AWG = 32; // wire gauge in AWG (defualt 32 for testing)
float spoolmuilpyler;

//wind will wind a striaght coil 
//windTheta will wind a coil with an angle of Theta

void home(){
  digitalWrite(DirPinTwo, HIGH);
  lcd_clear();
  lcd_print("Homing....");
  while (digitalRead(switchPin) == HIGH)
  {
    digitalWrite(StepPinTwo, HIGH);
    delayMicroseconds(30);
    digitalWrite(StepPinTwo, LOW);
    delayMicroseconds(30);
  }
  lcd_clear();
  lcd_print("Homed");
  delay(2000);
  digitalWrite(DirPinTwo, LOW);
  
}

void windTheta(int turns, float D, byte AWG){
  float theta_rad = (theta*(3.1459/180)); // covert from degree to RAD
  int length = (D * tan(theta_rad))*stepsPerMM; //do trig to find length to move spool then multiply by steps
  int k=0;
  int j=0;
  int h = 0;
  long a =0;
  byte stepdelay = 100;
  int ratio = (stepsPerRotation/length);
  long steps = (stepsPerRotation * turns);
 for (int i = 0; i < steps; i++){
  j++;
  h++;
  if(i == (slowStart*stepsPerRotation)){
    stepdelay = 40;
  }

  if(i == (steps-(SlowEnd*stepsPerRotation))){
    stepdelay = 100;
  }
  if(j >= stepsPerRotation){
    lcd_clear();
    lcd_print("req turns: "+ String(turns));
    setcursor(1,0);
    k++;
    j=0;
    lcd_print("cmpt turns: "+ String(k));
  } 
  
 digitalWrite(StepPinOne, HIGH);
 delayMicroseconds(stepdelay);
 digitalWrite(StepPinOne, LOW);
 delayMicroseconds(stepdelay);
 if(h == ratio){
 digitalWrite(StepPinTwo, HIGH);
 delayMicroseconds(stepdelay);
 digitalWrite(StepPinTwo, LOW);
 delayMicroseconds(stepdelay);
 h=0;
 a++;

 if(a == stepsPerMM*lmm){
  a=0;
 
  if(digitalRead(DirPinTwo) == HIGH){
  digitalWrite(DirPinTwo, LOW);
  }
  else{
    digitalWrite(DirPinTwo, HIGH);
  }
 }
 }
 

}

    
  
  
  lcd_clear();
  lcd_print("finished");
  delay(2000);
  lcd_clear();
  setup();
  



}

void wind(int turns, byte AWG){
  int j =0;

  byte stepdelay= 100;
  int k=0;
  long a=0;
  int spool_steps;
  spool_steps=spoolmuilpyler*stepsPerMM;

  int ratio = (stepsPerRotation/spool_steps);
  long h=0;
  long steps = (stepsPerRotation)*turns;
  long i=0;
 while(i != steps){
  j++;
  h++;
  if(i == (slowStart*stepsPerRotation)){
 
    stepdelay = 40;
    
  }

  if(i == (steps-(SlowEnd*stepsPerRotation))){
    stepdelay = 100;
  }
  
  if(j >= stepsPerRotation){
    lcd_clear();
    lcd_print("req turns: "+ String(turns));
    setcursor(1,0);
    k++;
    j=0;
    lcd_print("cmpt turns: "+ String(k));
  } 

 digitalWrite(StepPinOne, HIGH);
 delayMicroseconds(stepdelay);
 digitalWrite(StepPinOne, LOW);
 delayMicroseconds(stepdelay);
 
 if(h >= ratio){
 a++;
 
 digitalWrite(StepPinTwo, HIGH);
 delayMicroseconds(30);
 digitalWrite(StepPinTwo, LOW);
 delayMicroseconds(30);
 if(a == stepsPerMM*lmm){
  a=0;

  if(digitalRead(DirPinTwo) == HIGH){
  digitalWrite(DirPinTwo, LOW);
  }
  else{
    digitalWrite(DirPinTwo, HIGH);
  }
 }
 h=0;
 }
 i++;
}



  
  lcd_clear();
  lcd_print("Finished ");
  delay(2000);
  lcd_clear();
  setup();
}

void calculate(){


switch(unit){
  case 'M':
    L *= .001;
    break;

  case 'U':
    L *= .000001;
    break;

  case 'N':
    L *= .000000001;
    break;
  default:
    break;

}

switch (cmt)
{
case '1':
  D = CM1D;
  l = CM1l;
  A = CM1A;
  lmm = CM1lmm;
  break;
  case '2':
  D = CM2D;
  l = CM2l;
  A = CM2A;
  lmm = CM2lmm;
  break;
  case '3':
  D = CM3D;
  l = CM3l;
  A = CM3A;
  lmm = CM3lmm;
  break;
case 'C':
  A = ((D/2)*(D/2))*3.14159;

default:
  break;
}
switch (AWG)
{
case 32:
  spoolmuilpyler = AWGThirtyTwo;
  break;
case 31:
  spoolmuilpyler = AWGThirtyOne;
  break;
case 30:
  spoolmuilpyler = AWGThirty;
  break;

case 23:
  spoolmuilpyler = AWGTwentyThree;

default:
  spoolmuilpyler = AWGThirtyTwo; // default 32
  break;
}
if(needtocalc == true){
Serial.print(D, 10);
Serial.println(" Diameter");
Serial.print(l, 10);
Serial.println(" Length");
Serial.print(A, 10);
Serial.println(" Area");
Serial.print(MC, 10);
Serial.println(" MF");
Serial.print(L, 10);
Serial.println(" H");

T = sqrt((L * l)/(A * MC));
Serial.print(T);
Serial.println(" Turns");
T = int(T);
lcd_print("req turns: "+ String(T));
  turns = T;
}

}

void input(){
// the input function has no where near the level of depth as the Keyget fucntion
byte lp = true;
String cmd;
Serial.print("Please enter coil mold type (1, 2, C): ");
  while(lp == true){
    while(Serial.available()) {
    cmd = Serial.readString();// read the incoming data as string
    cmd.trim();
    lp = false;
    
    }
  }
Serial.print("Please enter desired L in Henrys: ");
lp = true;
  while(lp == true){
    while(Serial.available()) {
    String data = Serial.readString();// read the incoming data as string
    data.trim();
    
    L = data.toFloat();
    
 
    lp = false;
    
    }
  }

}

void getKeyinput(){
  
  char key;
  int index;
  String respL = "";
  bool i =true;
  lcd_clear();
  lcd_print("H or T (A/D) : ");
  delay(200);
  key = waitkey();
  if(key == 'A'){
    needtocalc=true;
    ableangle = false;


 
 
  while(i == true){
    lcd_clear();
    lcd_print("Enter Inductance: ");
    setcursor(1,0);
    lcd_print(String(unit)+ "H: "+respL+" ");


    key = waitkey();
    
    switch(key){
      case '#':
          i = false;
          L = respL.toDouble();
          break;
        
      case 'A':
        unit = 'M';
        Serial.println(unit);
        break;
      case 'B':
        unit = 'U';
        Serial.println(unit);
        break;
      case 'C':
        unit = 'N';
        Serial.println(unit);
        break;
      case '*':
        index = respL.length() - 1;
        respL.remove(index);
        break;

      default:
        respL += key;
   
    }
  }
  
  
  }
  else{
    needtocalc = false;
    ableangle = true;
    String input_turns="";
    while (i == true)
    {
      lcd_clear();
      delay(200);
      lcd_print("turns: " + input_turns);
      Serial.println(input_turns);
      key = waitkey();
      switch(key){
        case '*':
            index = input_turns.length() - 1;
            input_turns.remove(index);
            break;
        case '#':
            i =false;
            turns = input_turns.toInt();
            break;
        default:
            input_turns += key;
            break;
      }

 

      

    }
    
  }

 
  lcd_clear();
  lcd_print("Enter CM Type: ");
  cmt = waitkey();
  lcd_print(String(cmt));
  delay(500);
  lcd_clear();
  String input_length;
  String input_diameter;

  if(cmt == 'C'){
    int i = true;
    while(i == true){
    lcd_clear();
    lcd_print("Length MM: ");
    lcd_print(input_length);
    key = waitkey();
    switch(key){
      case '#':
        i = false;
        l = ((input_length.toDouble())/1000);
        break;
      case '*':
        index =input_length.length() - 1;
        input_length.remove(index);
        break;
      default:
        input_length += key;  
        break;
    }
    }

    i = true;
    while(i == true){
    lcd_clear();
    lcd_print("Diameter MM: ");
    lcd_print(input_diameter);
    key = waitkey();
    switch(key){
      case '#':
        i = false;
        D = ((input_diameter.toDouble())/1000);
        break;
      case '*':
        index =input_diameter.length() - 1;
        input_diameter.remove(index);
        break;
      default:
        input_diameter += key;
        break;
       
    }


    }

  }
  if(ableangle == true){
  lcd_clear();
  lcd_print("Wind agl(A/D): ");
  key= waitkey();
  if(key == 'A'){
    windatangle = true;
  }
  else{
    windatangle = false;
  }
  lcd_print(String(key));
  delay(500);
  lcd_clear();
  if(windatangle == true){
    String input_theta = "";
    int i = true;
    while (i == true)
    {
      lcd_clear();
      lcd_print("winding angle ");
      setcursor(1,0);
      lcd_print("Degrees: " + input_theta);
      key = waitkey();
      switch(key){
        case '*':
            index = input_theta.length() - 1;
            input_theta.remove(index);
            break;
        case '#':
            i =false;
            theta = input_theta.toInt();
            break;
        default:
            input_theta += key;
            break;
      }


    }
    theta = input_theta.toInt();

    i = true;
    String input_distance;

    while (i == true)
    {
      lcd_clear();
      lcd_print("enter D: "); // enter distance between coil guid and end of coil needed for trig
      lcd_print(input_distance);
      key = waitkey();
      switch(key){
        case '*':
            index = input_distance.length() - 1;
            input_distance.remove(index);
            break;
        case '#':
            i =false;
            guid_distance = input_distance.toInt();
            break;
        default:
            input_distance += key;
            break;
      }
    }
    

    
  }
  }


  i = true;
  String input_awg = "";
  while(i == true){
  lcd_clear();
  lcd_print("enter AWG: ");
  lcd_print(input_awg);

  key = waitkey();

      switch(key){
        case '*':
            index = input_awg.length() - 1;
            input_awg.remove(index);
            break;
        case '#':
            i =false;
            AWG = input_awg.toInt();
            break;
        default:
            input_awg += key;
            break;
      }

  }
  lcd_clear();
  
  Serial.println(respL + " input H");
  Serial.println(String(AWG) + " AWG");
  Serial.println(unit);
  Serial.println(cmt);
  Serial.println(String(turns) + " turns");
  Serial.println(String(guid_distance) + " guide distance");
  Serial.print(l ,10);
  Serial.println(" Length");
  Serial.print(D,10);
  Serial.println(" Diameter");

}

void setup() {
Serial.begin(9600);
lcd_initialize();
keypad_init();
Serial.println("Tacha Technology & Robotics Coil Winder");
lcd_print("TTR Coil Winder");
pinMode(StepPinOne, OUTPUT);
pinMode(DirPinOne, OUTPUT);
pinMode(StepPinTwo, OUTPUT);
pinMode(DirPinTwo, OUTPUT);
pinMode(switchPin, INPUT);
Serial.println("startup complete.");
delay(1000);
lcd_clear();
getKeyinput(); // can use terminal input instead however, it has less features
home();
calculate();


if(windatangle == true){
    windTheta(turns, guid_distance, AWG);

}
else{
  wind(turns, AWG);
}
  
}

void loop() {
  //nothing runs in loop
}
