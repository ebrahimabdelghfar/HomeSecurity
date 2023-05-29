#include <wiringPi.h>
#include <iostream>

const int NUM_OF_ROOMS = 11;

/*Define pins numbers*/

#define PIN_BATH 1
#define PIN_TEST_LED 7

int main (int argc, char **argv)
{
    // Setup WiringPi library
    wiringPiSetup() ;
    // Setup Mode for all defined pins
    pinMode(PIN_BATH, INPUT);
    pinMode(PIN_TEST_LED, OUTPUT);
    // check state of each pin
    /*for (;;){
	if(digitalRead(PIN_BATH==HIGH){
	    std::cout << "Bath door is open: pin number 4\n";
	    digitalWrite(PIN_TEST_LED, HIGH);
	}
    }*/
    std::cout << "Compiled Fine!!\n";
    return 0 ;
}
