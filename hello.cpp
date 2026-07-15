#include <Arduino.h>


void setup()
{
    pinMode(13, OUTPUT);

    int status = 13;
    digitalWrite(status, HIGH);
    delay(1000);
    digitalWrite(status, LOW);
}

void loop()
{
}
