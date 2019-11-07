// Servo  initialiser a 90 et apres +- 25° de débatement
// marche arriere 25 max a 70 min
// marche avant  150 max a 115 min

#include <Servo.h>
#include <Wire.h>

Servo myservo;  // create servo object to control a servo
Servo mymotor;

// Buffer qui va contenir la trame série
#define TAILLE_MAX 32
// Buffer qui va contenir le texte (taille du buffer / 2, oui j'ai mis ça au pif)
char texte[TAILLE_MAX];
// Données utiles extraites
int cons_vitesse; //entre -100 et 100
int cons_angle; // entre -25 et 25
int vitesse=0;
int angle=0;

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
  
}

void loop() {
  // Récupération d'une trame + parsing
  if(recupInfo(texte,&cons_vitesse,&cons_angle)==1) {Serial.println("Erreur de trame 1!");}
  if(recupInfo(texte,&cons_vitesse,&cons_angle)==2) {Serial.println("Erreur de trame 2!");}  
  else {
      if (cons_vitesse==0) {vitesse=0;}
      else if (cons_vitesse<0){vitesse = int(70+ cons_vitesse*40/100);}
      else if (cons_vitesse>0){vitesse = int (110+cons_vitesse*30/100);}
      
      mymotor.write(vitesse); 
      Serial.print("Speed = "); Serial.println(vitesse);
      if (cons_angle>25) {angle=25;}
      else if (cons_angle<-25) {angle=-25;}
      else {angle=cons_angle;} 
      myservo.write(90+angle);    
      Serial.print("teta = "); Serial.println(angle);             
       }
  delay(20);

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
        Serial.print("cons teta = "); Serial.println(*cons_angle);
      Serial.print("cons Speed = "); Serial.println(*cons_vitesse);
  return 0;/* retourne 0 -> pas d'erreur */
}
}
