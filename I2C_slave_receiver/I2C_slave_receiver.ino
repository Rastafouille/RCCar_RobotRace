
#include <Wire.h>

int cons_vitesse; //entre -100 et 100
int cons_angle; // entre -25 et 25

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveI2C); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveI2C(int howMany) {
  while (1 < Wire.available()) 
  {char c = Wire.read();Serial.print(c);}
  int x = Wire.read();Serial.println(x);
  if (c=="v"){cons_vitesse=x; Serial.print("cons Speed = "); Serial.println(cons_vitesse);}
  else if (c=="a"){cons_angle=x;Serial.print("cons teta = "); Serial.println(cons_angle);} 
  }
