// The MIT License (MIT)
//
// Copyright (c) 2015 THINGER LTD
// Author: alvarolb@gmail.com (Alvaro Luis Bustamante)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "thinger/thinger.h"
//#include <wiringPi.h>
#include <iostream>


/* User Credentials */
#define USER_ID             "Ahmedsecurity"
#define DEVICE_ID           "TestPC"
#define DEVICE_CREDENTIAL   "TNer1ANe2RYT5Dih"
#define EMAIL_ENDPOINT_ID   "email"

/* Define Pins */
#define PIN_TEST_LED    3
#define PIN_REED    2

/* Define State variables */
bool SENS_STATE = false; // LED switch state
bool DASH_STATE = false; // Dashboard switch state
int ANY_SENS = 0; // check if any sensor is on
bool SENT_EMAILS = false; // check if any email was sent

int main(int argc, char *argv[])
{
    // initialize thinger.io library
    thinger_device thing(USER_ID, DEVICE_ID, DEVICE_CREDENTIAL);
    /* WIRING PI PART
    // Setup WiringPi library
    wiringPiSetup();
    // Setup Mode for all defined pins
    pinMode(PIN_TEST_LED, OUTPUT);
    pinMode(PIN_REED, INPUT);
    pullUpDnControl(PIN_REED, PUD_UP);

    // check state of each pin
    thing["reed_switch"] >> [](pson &out){
        out = bool(digitalRead(PIN_REED));
    };
    thing["led"] << [](pson &in){
        if(in.is_empty()){
            // We send back the pin value to thinger platform
            in = STATE;
        }   
        else{
            // This code is called whenever the "led" resource change
            STATE = in;
            digitalWrite(PIN_TEST_LED, STATE);
        }
    };
    */

    //
    thing["AnySensor"] << [](pson &in){
        if(in.is_empty()){
            // We send back the pin value to thinger platform
            in = SENS_STATE;
        } 
        else{
            // This code is called whenever the "led" resource change
            SENS_STATE = in;
            if(SENS_STATE){
                ANY_SENS++;
            }
            else{
                ANY_SENS--;
            }   
        }
        //
        std::cout << "Any Sensor is: " << ANY_SENS << std::endl;
    };

    // SIREN PART
   thing["siren"] << [](pson &in){
        if(in.is_empty()){
            // We send back the pin value to thinger platform
            in = DASH_STATE;
        } 
        else{
            // This code is called whenever the "led" resource change
            DASH_STATE = in;
            if(DASH_STATE && ANY_SENS){
                std::cout << "Siren is ON: WIWAWIWAWIWA" << std::endl;
            }
            else{
                std::cout << "Siren is OFF: ZZZZZZZZZ" << std::endl;
            }
        }
    };
    /*------------------*/
    /* End of Resources */
   /*------------------*/

   /*MAIL PART*/
    while(true){
        thing.handle();
        std::cout << "DASH STATE: " << DASH_STATE << " || " << "ANY SENSOR STATE: " << ANY_SENS << std::endl;
        if(DASH_STATE && ANY_SENS){
            if(!SENT_EMAILS){
                pson data;
                thing.call_endpoint(EMAIL_ENDPOINT_ID, data);
                SENT_EMAILS = true;
            }  
        }
        else{
            SENT_EMAILS = false;
        }
    }
    return 0;
}
