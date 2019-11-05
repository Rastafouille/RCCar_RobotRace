#include <Servo.h>
#include <Wire.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

// Buffer qui va contenir la trame série
#define TAILLE_MAX 32
// Buffer qui va contenir le texte (taille du buffer / 2, oui j'ai mis ça au pif)
char texte[TAILLE_MAX];
// Données utiles extraites
int cons_vitesse,cons_angle,angle;
float vitesse;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  mymotor.attach(6);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.println("Serial");
  Wire.begin();
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);  // waits for the servo to get there



  // Récupération d'une trame + parsing
  if(recupInfo(texte,&cons_vitesse,&cons_angle)==1) {Serial.println("Erreur de trame 1!");}
  if(recupInfo(texte,&cons_vitesse,&cons_angle)==2) {Serial.println("Erreur de trame 2!");}  
  else {
  cons_vitesse = map(cons_vitesse, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  mymotor.write(cons_vitesse);                  // sets the servo position according to the scaled value
  cons_angle = map(cons_angle, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(cons_angle);                  // sets the servo position according to the scaled value
  
  }

}

int recupInfo(char *texte, int *cons_vitesse,int *cons_angle) {
  char c, buf[TAILLE_MAX + 1];
  unsigned char i = 0;
  if(Serial.available() > 1){/* Attente de 2 char sur le port série */
      while(Serial.read() != '~' && Serial.read() != 'X'); /* Tant que chaine != ~X -> boucle */
      /* Remplissage du buffer */
      do{
        if(i == (TAILLE_MAX + 1)) /* Si la chaine a dépassé la taille max du buffer*/
        return 1;/* retourne 1 -> erreur */
        while(Serial.available() < 1); /* Attente d'un char sur le port série */ 
        } 
      while((buf[i++] = Serial.read()) != '#'); /* Tant que char != # (fléche) -> boucle */
       /* Copie le texte au début de buf[] dans texte[] */
      i = 0;
      while((texte[i] = buf[i]) != '#') i++;
      texte[i] = '\0';
      /* Parse la chaine de caractères et extrait les champs */
      Serial.println(texte);
      if(sscanf(texte, "X;%d;%d;",cons_vitesse,cons_angle) != 2)
      {//Serial.print("test");Serial.print(*cons_vitesse);Serial.println(*cons_angle);
        return 2;} /* Si sscanf n'as pas pu extraire les 2 champs -> erreur*/
  return 0;/* retourne 0 -> pas d'erreur */
}
}
