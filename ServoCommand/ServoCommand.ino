// Servo  initialiser a 90 et apres +- 25° de débatement
// marche arriere 25 max a 70 min
// marche avant  150 max a 115 min

#include <Servo.h>
#include <Wire.h>

Servo myservo;  // create servo object to control a servo
int ANGLE_MIN=-20;
int ANGLE_MAX=20;
Servo mymotor;
int REAR_MIN =70;
int REAR_MAX =25;
int FRONT_MIN =115;
int FRONT_MAX =150;

//données I2C
char c ='z';
int x = 0;

int cons_vitesse=0; 
int cons_angle=0; 

void setup() {
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  mymotor.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
  Serial.begin(9600);
  Serial.println("Serial OK");

  //attente init controleur
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);                      
  digitalWrite(LED_BUILTIN, LOW);    

  //I2C
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
delay(10);

  if (c =='v'){cons_vitesse=map(x,0,254,REAR_MAX,FRONT_MAX); c ='z';
    Serial.print("cons Speed = "); Serial.println(cons_vitesse);
    //Serial.print(" et cons teta = "); Serial.println(cons_angle);
    mymotor.write(cons_vitesse);}
  else if (c == 'a' ){cons_angle=map(x,0,254,ANGLE_MIN,ANGLE_MAX); c ='z';
    //Serial.print("cons Speed = "); Serial.print(cons_vitesse);
    Serial.print(" et cons teta = "); Serial.println(cons_angle);
    myservo.write(90+cons_angle);  }




//      if (cons_vitesse==0) {vitesse=0;}
//      else if (cons_vitesse<0){vitesse = int(70+ cons_vitesse*40/100);}
//      else if (cons_vitesse>0){vitesse = int (110+cons_vitesse*30/100);}
//      mymotor.write(vitesse); 
//      Serial.print("Speed = "); Serial.println(vitesse);
//      if (cons_angle>25) {angle=25;}
//      else if (cons_angle<-25) {angle=-25;}
//      else {angle=cons_angle;} 
//      myservo.write(90+angle);    
//      Serial.print("teta = "); Serial.println(angle);             
//       }
//  delay(20);

}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    //Serial.println(c);       // print the character
  }
  x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer
}
