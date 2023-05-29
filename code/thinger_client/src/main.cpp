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
#define USER_ID             "Ahmedsecurity"
#define DEVICE_ID           "TestRaspberry"
#define DEVICE_CREDENTIAL   "h6PGGctC1zQTsrtP"

/* Define Pins */
#define PIN_TEST_LED    7
#define PIN_BATH    1


int main(int argc, char *argv[])
{
    // initialize thinger.io library
    thinger_device thing(USER_ID, DEVICE_ID, DEVICE_CREDENTIAL);
    // Setup WiringPi library
    wiringPiSetup();
    // Setup Mode for all defined pins
    pinMode(PIN_TEST_LED, OUTPUT);
    pinMode(PIN_BATH, INPUT);

    // check state of each pin
    thing["BathDoor"] << [](pson &in){
        digitalRead(PIN_BATH);
    };

    thing.start();
    return 0;
}