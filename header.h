#ifndef header_h
#define header_h
#include <Arduino.h>
#include <math.h>


// coil mold specifications: diameter, lenght, area.

float CM1D = .0099; // unit in mm.
float CM1l = .0165; // unit in mm.
float CM1A = ((CM1D/2)*(CM1D/2))*3.14159;
float CM1lmm = 16.5;



byte StepPinOne = 2;
byte DirPinOne = 3;

byte StepPinTwo = 4;
byte DirPinTwo = 5;

byte switchPin = 7;

long stepsPerRotation = 3200;
int stepsPerMM = 400;

byte slowStart = 5; // numer of turns to start slow
byte SlowEnd = 5;

// enter any different wire gauges you use here
// the values are slightly bigger than the wire diameter to ensure the winder 
// doesn't wind over previous windings
float AWGThirtyTwo = .21;
float AWGThirtyOne = .28;
float AWGThirty = .3;
float AWGTwentyThree = .6;
float AWGSevenTeen = 1.24;


#endif
