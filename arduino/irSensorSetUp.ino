// Code orginally developed by Lee Curiosity.
// Modified by Austin Dalley.
// - Whitespace rearranged.

#include <IRremote.h>

const int RemotePin = 8;
IRrecv irrecv(RemotePin);
decode_results results;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    irrecv.enableIRIn();
}

void loop() {
    // put your main code here, to run repeatedly:
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        delay(200);
        irrecv.resume();
    }
}