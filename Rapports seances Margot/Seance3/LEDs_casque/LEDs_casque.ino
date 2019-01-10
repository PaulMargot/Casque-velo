#include <SoftwareSerial.h>
SoftwareSerial hc06(10,11);

// Clignotants
const int led_D1=4;
const int led_D2=5;
const int led_D3=6;

const int led_G1=7;
const int led_G2=8;
const int led_G3=9;

char message = "";
char clignotant = "";


// Feu luminosite
const int led_rouge = 3 ;
const int sensorPin = A0;   //sortie analogique car nous allons lire la tension en sortie de la photoresistance


// Feu accelerometre
char feu = "";


// Phare
const int led_verte = 2 ;
char ancien_etat = "";
char etat = "";


void setup() {

// Clignotants
  pinMode(led_D1,OUTPUT);
  pinMode(led_D2,OUTPUT);
  pinMode(led_D3,OUTPUT);
  pinMode(led_G1,OUTPUT);
  pinMode(led_G2,OUTPUT);
  pinMode(led_G3,OUTPUT);

  Serial.begin(9600);
  hc06.begin(38400);


//Feu luminosite
  pinMode(led_rouge,OUTPUT);


// Phare 
  pinMode(led_verte,OUTPUT);
  
}


void loop() {

// Clingotants
  if(hc06.available()){
    message = hc06.read();
    //Serial.println(message);
  }


  if(message == 'e'){   //'e':eteint
    clignotant = 'e';
  }

  else if(message == 'w'){  //'w':warning
    clignotant = 'w';
  }

  else if(message == 'g'){  //'g':gauche
    clignotant = 'g';
  }

  else if(message == 'd'){  //'d':droite
    clignotant = 'd';
  }



  if(clignotant=='e'){
    digitalWrite(led_D1,LOW);
    digitalWrite(led_D2,LOW);
    digitalWrite(led_D3,LOW);
    digitalWrite(led_G1,LOW);
    digitalWrite(led_G2,LOW);
    digitalWrite(led_G3,LOW);
  }
  
  else if(clignotant=='w'){
    digitalWrite(led_D1,HIGH);
    digitalWrite(led_D2,HIGH);
    digitalWrite(led_D3,HIGH);
    digitalWrite(led_G1,HIGH);
    digitalWrite(led_G2,HIGH);
    digitalWrite(led_G3,HIGH);
    delay(500);
    digitalWrite(led_D1,LOW);
    digitalWrite(led_D2,LOW);
    digitalWrite(led_D3,LOW);
    digitalWrite(led_G1,LOW);
    digitalWrite(led_G2,LOW);
    digitalWrite(led_G3,LOW);
    delay(500);
  }

  else if(clignotant=='g'){
    digitalWrite(led_D1,LOW);
    digitalWrite(led_D2,LOW);
    digitalWrite(led_D3,LOW);
    digitalWrite(led_G1,HIGH);
    digitalWrite(led_G2,HIGH);
    digitalWrite(led_G3,HIGH);
    delay(500);
    digitalWrite(led_G1,LOW);
    digitalWrite(led_G2,LOW);
    digitalWrite(led_G3,LOW);
    delay(500);
  }

  else if(clignotant=='d'){
    digitalWrite(led_G1,LOW);
    digitalWrite(led_G2,LOW);
    digitalWrite(led_G3,LOW);
    digitalWrite(led_D1,HIGH);
    digitalWrite(led_D2,HIGH);
    digitalWrite(led_D3,HIGH);
    delay(500);
    digitalWrite(led_D1,LOW);
    digitalWrite(led_D2,LOW);
    digitalWrite(led_D3,LOW);
    delay(500);
  }


// Feu/Phare luminosite
  int valeur = analogRead(sensorPin); //lecture de la tension en sortie du photorecepteur allant de 0 a 1023 et variant en fonction de la luminosite

  //Serial.println(valeur);

  ancien_etat = etat;

  if(valeur<=750){  //si luminosité trop faible on allume les LEDs verte et rouge (phare et feu)
    digitalWrite(led_rouge,HIGH);
    digitalWrite(led_verte,HIGH);
    etat = 'n'; //on suppose qu'on est de nuit, donc etat correspond a 'n'
  }

  else{
     digitalWrite(led_rouge,LOW);
     digitalWrite(led_verte,LOW);
     etat = 'j';  //on suppose qu'on est de jour, donc etat correspond a 'j'
  }

  if(ancien_etat!=etat){  //detecte uniquement les changements d'etat, n'envoie pas en continu 'n' ou 'j'
    //Serial.println(etat);
    hc06.write(etat);  //envoie a l'hc05 l'etat actuel
  }
  

// Feu accelerometre
  if(message == 'f'){   //'f':freine
    feu = 'f';
  }

  else if(message == 'a'){  //'a':accelere
    feu = 'a';
  }


  if(feu=='f'){   // si l'hc05 envoie 'f' c'est qu'on freine donc on allume la led rouge (le feu)
    digitalWrite(led_rouge,HIGH);
  }

  else if(feu=='a'){  //si on reçoit 'a', on l'éteint
    digitalWrite(led_rouge,LOW);
  }
   

}
