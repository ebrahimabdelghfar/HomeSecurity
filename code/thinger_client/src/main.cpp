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
#include <wiringPi.h>
#include <iostream>


/* User Credentials */
#define USER_ID             ""
#define DEVICE_ID           ""
#define DEVICE_CREDENTIAL   ""
#define EMAIL_ENDPOINT_ID   "email"

/* Define Pins */
const int PINS_NUM = 12;
// Going Clockwise in the Schematic
#define PIN_SIREN 12

#define PIN_OPE 1
#define PIN_LIVING_AND_NOOK 4
#define PIN_DEN_WIN 5
#define PIN_LAUNDRY_ROOM 0
#define PIN_115_GRR 26
#define PIN_FRONT_GUEST 25
#define PIN_STUDY 23
#define PIN_HALL 2
#define PIN_F_DOOR 21
#define PIN_MASTER_BATH 27

/* Define Pins States */
bool STATE_OPE = false;
bool STATE_LIVING_AND_NOOK = false;
bool STATE_DEN_WIN = false;
bool STATE_LAUNDRY_ROOM = false;
bool STATE_115_GRR = false;
bool STATE_FRONT_GUEST = false;
bool STATE_STUDY = false;
bool STATE_HALL = false;
bool STATE_F_DOOR = false;
bool STATE_MASTER_BATH = false;

/* Define State variables */

bool DASHBOARD_SECURITY_STATE = false; // Dashboard Security Switch State (ON/OFF)
bool SENT_EMAILS = false; // Checks if any email was sent

bool AnySensorOn(){ // Check if any sensor is on
    return (STATE_OPE || STATE_LIVING_AND_NOOK || STATE_DEN_WIN || 
    STATE_LAUNDRY_ROOM || STATE_115_GRR || STATE_FRONT_GUEST ||
    STATE_STUDY || STATE_HALL || STATE_F_DOOR || STATE_MASTER_BATH);
}

int main(int argc, char *argv[])
{
    // initialize thinger.io library
    thinger_device thing(USER_ID, DEVICE_ID, DEVICE_CREDENTIAL);
    // Setup WiringPi library
    wiringPiSetup();
    /*----------------------------------*/

    /* Setup Mode for all defined pins */
    // Siren Pin
    pinMode(PIN_SIREN, OUTPUT);
    // OPE pin
    pinMode(PIN_OPE, INPUT);
    pullUpDnControl(PIN_OPE, PUD_UP);
    // Living and Nook pin
    pinMode(PIN_LIVING_AND_NOOK, INPUT);
    pullUpDnControl(PIN_LIVING_AND_NOOK, PUD_UP);
    // Den Window pin
    pinMode(PIN_DEN_WIN, INPUT);
    pullUpDnControl(PIN_DEN_WIN, PUD_UP);
    // Laundry Room pin
    pinMode(PIN_LAUNDRY_ROOM, INPUT);
    pullUpDnControl(PIN_LAUNDRY_ROOM, PUD_UP);
    // 115 GRR pin
    pinMode(PIN_115_GRR, INPUT);
    pullUpDnControl(PIN_115_GRR, PUD_UP);
    // Front Guest pin
    pinMode(PIN_FRONT_GUEST, INPUT);
    pullUpDnControl(PIN_FRONT_GUEST, PUD_UP);
    // Study pin
    pinMode(PIN_STUDY, INPUT);
    pullUpDnControl(PIN_STUDY, PUD_UP);
    // Hall pin
    pinMode(PIN_HALL, INPUT);
    pullUpDnControl(PIN_HALL, PUD_UP);
    // Front Door pin
    pinMode(PIN_F_DOOR, INPUT);
    pullUpDnControl(PIN_F_DOOR, PUD_UP);
    // Master Bath pin
    pinMode(PIN_MASTER_BATH, INPUT);
    pullUpDnControl(PIN_MASTER_BATH, PUD_UP);
    /*------------------------------------*/

    /* Handle Pins I/O && update dashboard */
    // OPE pin
    thing["ope"] >> [](pson &out){
        // read the pin value
        out = bool(digitalRead(PIN_OPE));
        // update the pin state variable
        (out) ? STATE_OPE = true : STATE_OPE = false;
    };
    // Living and Nook pin
    thing["living_and_nook"] >> [](pson &out){
        out = bool(digitalRead(PIN_LIVING_AND_NOOK));
        (out) ? STATE_LIVING_AND_NOOK = true : STATE_LIVING_AND_NOOK = false;
    };
    // Den Window pin
    thing["den_window"] >> [](pson &out){
        out = bool(digitalRead(PIN_DEN_WIN));
        (out) ? STATE_DEN_WIN = true : STATE_DEN_WIN = false;
    };
    // Laundry Room pin
    thing["laundry_room"] >> [](pson &out){
        out = bool(digitalRead(PIN_LAUNDRY_ROOM));
        (out) ? STATE_LAUNDRY_ROOM = true : STATE_LAUNDRY_ROOM = false;
    };
    // 115 GRR pin
    thing["115_grr"] >> [](pson &out){
        out = bool(digitalRead(PIN_115_GRR));
        (out) ? STATE_115_GRR = true : STATE_115_GRR = false;
    };
    // Front Guest pin
    thing["front_guest"] >> [](pson &out){
        out = bool(digitalRead(PIN_FRONT_GUEST));
        (out) ? STATE_FRONT_GUEST = true : STATE_FRONT_GUEST = false;
    };
    // Study pin
    thing["study"] >> [](pson &out){
        out = bool(digitalRead(PIN_STUDY));
        (out) ? STATE_STUDY = true : STATE_STUDY = false;
    };
    // Hall pin
    thing["hall"] >> [](pson &out){
        out = bool(digitalRead(PIN_HALL));
        (out) ? STATE_HALL = true : STATE_HALL = false;
    };
    // Front Door pin
    thing["front_door"] >> [](pson &out){
        out = bool(digitalRead(PIN_F_DOOR));
        (out) ? STATE_F_DOOR = true : STATE_F_DOOR = false;
    };
    // Master Bath pin
    thing["master_bath"] >> [](pson &out){
        out = bool(digitalRead(PIN_MASTER_BATH));
        (out) ? STATE_MASTER_BATH = true : STATE_MASTER_BATH = false;
    };
    // Siren pin
    thing["siren"] << [](pson &in){
        if(in.is_empty()){
            // We send back the pin value to thinger platform
            in = DASHBOARD_SECURITY_STATE;
        } 
        else{
            // This code is called whenever the "led" resource change
            DASHBOARD_SECURITY_STATE = in;
        }
    };
    /*------------------------------------*/

    /* Handle Email Endpoint*/
    while(true){
        if(DASHBOARD_SECURITY_STATE && AnySensorOn()){
            digitalWrite(PIN_SIREN, HIGH); // Turn on Siren
            if(!SENT_EMAILS){
                pson data;
                bool res = thing.call_endpoint(EMAIL_ENDPOINT_ID, data);
                SENT_EMAILS = true;
            }  
        }
        else{
            digitalWrite(PIN_SIREN, LOW); // Turn off Siren
            SENT_EMAILS = false;
        }
        // handle thinger.io connection
        thing.handle(); 
    }
    /*------------------------------------*/
    return 0;
}
