#include <SoftwareSerial.h>


SoftwareSerial Serial1(2,3);  //serial communication between ESP01 and Arduino UNO

int light;//variable to store light values

#define LDR A0 //pin for analog LDR input

void setup(){
        Serial.begin(115200);
        Serial1.begin(115200); //serial communication at 115200 baud rate
        pinMode(LDR,INPUT); //declaring LDR as input pin
        delay(500);
}
void loop()
{
        light= analogRead(LDR);  //analog read
        Serial.print(" light: ");
        Serial.println(light);
        Serial1.write(light);
        delay(3000);
}
