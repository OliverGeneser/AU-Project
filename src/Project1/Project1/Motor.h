/*
 * Motor.h
 *
 * Created: 5/3/2022 8:52:04 AM
 *  Author: Algorithm (Oliver G.)
 */ 
#include <stdbool.h>

//Functions
void initMotor();
void setSpeed(unsigned char speed, bool smooth);
void switchDirection();
void testMotor();