#include <wiringPi.h>
#include <string>

const int NUM_OF_ROOMS = 11;

const int HALL=0, BATH=1;

enum pin {
    HALL = 0,
    BATH = 1
};

int main (void)
{
    wiringPiSetup() ;
    pinMode(GPIO_PIN, OUTPUT);
    // Create an a list of all rooms
    pin Pin;
    Pin = HALL;
    int 
    for(int i=0; i < NUM_OF_ROOMS; ++i){
        
    }
    for (;;){
        digitalWrite (0, HIGH) ; delay (500) ;
        digitalWrite (0,  LOW) ; delay (500) ;
    }
    return 0 ;
}