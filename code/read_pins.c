#include <wiringPi.h>
#include <stdio.h>
const int NUM_OF_ROOMS = 11;
const int HALL=0, BATH=1;

int main (void)
{
    wiringPiSetup() ;
    pinMode(BATH, INPUT);
    // Create a list of all rooms
    int Pin = HALL;
    /*for (;;){
        digitalWrite (0, HIGH) ; delay (500) ;
        digitalWrite (0,  LOW) ; delay (500) ;
    }*/
    printf("Compiled Fine!!!");
    return 0 ;
}
