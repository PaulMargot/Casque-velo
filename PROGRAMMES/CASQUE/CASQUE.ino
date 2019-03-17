#include <Adafruit_NeoPixel.h>

#define PIN1 6
#define PIN2 3
#define PIN3 8
#define PIN4 9
#define PHOTORES 0
#define LED 4

Adafruit_NeoPixel contour = Adafruit_NeoPixel(34, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel centre = Adafruit_NeoPixel(9, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rappel_gauche = Adafruit_NeoPixel(4, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rappel_droite = Adafruit_NeoPixel(4, PIN4, NEO_GRB + NEO_KHZ800);

int i=0;
int j=33;
int lumino;
int compteur=0;
char message = "";
char clignotant = "";
char ancien_clignotant = "";
char feu = 'a';
char ancien_etat = "";
char etat = "";
char phare = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(38400);
  contour.begin();
  centre.begin();
  rappel_gauche.begin();
  rappel_droite.begin();
  contour.show();
  centre.show();
  rappel_gauche.show();
  rappel_droite.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial3.available()) {
    message = Serial3.read();
    Serial.println(message);   
  }

  lumino = analogRead(PHOTORES);
  ancien_etat = etat;

  if(lumino<=50){  
    etat = 'n'; 
  }
  if (lumino>=70){
     etat = 'j';  
  }

  if(ancien_etat!=etat){  
    Serial3.write(etat);  
  }

  if(message == 'e'){   
    clignotant = 'e';
  }

  else if(message == 'g'){ 
    clignotant = 'g';
  }

  else if(message == 'd'){  
    clignotant = 'd';
  }

  else if(message == 'f'){   
    feu = 'f';
  }

  else if(message == 'a'){  
    feu = 'a';
  }

  else if (message == 'p') {
    phare = 'p';
  }

  else if (message == 'q') {
    phare = 'q';
  }


  if (etat == 'j') {
    if (clignotant == 'e') {
      for(i=0; i<4; i++){
          rappel_gauche.setPixelColor(i,0,0,0);
          rappel_droite.setPixelColor(i,0,0,0);
      }
      rappel_gauche.show(); 
      rappel_droite.show();      
    }
    for(i=0; i<9; i++){
          centre.setPixelColor(i,0,0,0);
    }
    centre.show();       
    if (phare == 'p') {
      digitalWrite(LED,HIGH);      
    }
    else {
      digitalWrite(LED,LOW);      
    }
        
    if(feu=='a'){

    for(i=0; i<34; i++){
          contour.setPixelColor(i,0,0,0);
        }
      contour.show();
    
    if(clignotant=='g'){
      if(compteur<100){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,255,75,0);
          contour.setPixelColor(j-i,255,75,0);
          rappel_gauche.setPixelColor(i,255,75,0);
          rappel_droite.setPixelColor(i,0,0,0);                   
        }
        contour.show();
        rappel_gauche.show();
        rappel_droite.show(); 
      }
      if(100<=compteur && compteur<200){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,0,0,0);
          contour.setPixelColor(j-i,0,0,0);
          rappel_gauche.setPixelColor(i,0,0,0);                      
        }
        contour.show();
        rappel_gauche.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,255,75,0);                   
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,255,75,0);
          rappel_gauche.setPixelColor(i,0,0,0);          
        }
        contour.show();
        rappel_droite.show();
        rappel_gauche.show();
      }
      if(100<=compteur && compteur<200){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,0,0,0);                    
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,0,0,0);          
        }
        contour.show();
        rappel_droite.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    }

    if(feu=='f'){
      for(i=0; i<34; i++){
          contour.setPixelColor(i,255,0,0);
        }
      contour.show();     
    
    if(clignotant=='g'){
      if(compteur<100){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,255,75,0);
          contour.setPixelColor(j-i,255,75,0);
          rappel_gauche.setPixelColor(i,255,75,0);
          rappel_droite.setPixelColor(i,0,0,0);                     
        }
        contour.show();
        rappel_gauche.show();
        rappel_droite.show(); 
      }
      if(100<=compteur && compteur<200){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,255,0,0);
          contour.setPixelColor(j-i,255,0,0);
          rappel_gauche.setPixelColor(i,0,0,0);                     
        }
        contour.show();
        rappel_gauche.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,255,75,0);                    
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,255,75,0);
          rappel_gauche.setPixelColor(i,0,0,0);
        }
        contour.show();
        rappel_droite.show();
        rappel_gauche.show(); 
      }
      if(100<=compteur && compteur<200){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,255,0,0);                    
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,0,0,0);
        }
        contour.show();
        rappel_droite.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    }    
  }
  if (etat == 'n') {
    if (clignotant == 'e') {
      for(i=0; i<4; i++){
          rappel_gauche.setPixelColor(i,255,255,255);
          rappel_droite.setPixelColor(i,255,255,255);
      }
      rappel_gauche.show(); 
      rappel_droite.show();      
    }
    for(i=0; i<9; i++){
          centre.setPixelColor(i,255,0,0);
        }
    centre.show();
    digitalWrite(LED,HIGH);
    
    if(feu=='a'){

    for(i=0; i<34; i++){
          contour.setPixelColor(i,0,0,0);
        }
      contour.show();
    
    if(clignotant=='g'){
      if(compteur<100){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,255,75,0);
          contour.setPixelColor(j-i,255,75,0);
          rappel_gauche.setPixelColor(i,255,75,0);
          rappel_droite.setPixelColor(i,255,255,255);                  
        }
        contour.show();
        rappel_gauche.show();
        rappel_droite.show(); 
      }
      if(100<=compteur && compteur<200){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,0,0,0);
          contour.setPixelColor(j-i,0,0,0);
          rappel_gauche.setPixelColor(i,255,255,255);                     
        }
        contour.show();
        rappel_gauche.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,255,75,0);                    
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,255,75,0);
          rappel_gauche.setPixelColor(i,255,255,255);
        }
        contour.show();
        rappel_droite.show();
        rappel_gauche.show(); 
      }
      if(100<=compteur && compteur<200){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,0,0,0);                    
        }
        for(i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,255,255,255);
        }
        contour.show();
        rappel_droite.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    }

    if(feu=='f'){
      for(i=0; i<34; i++){
          contour.setPixelColor(i,255,0,0);
        }
      contour.show();     
    
    if(clignotant=='g'){
      if(compteur<100){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,255,75,0);
          contour.setPixelColor(j-i,255,75,0);
          rappel_gauche.setPixelColor(i,255,75,0);
          rappel_droite.setPixelColor(i,255,255,255);                     
        }
        contour.show();
        rappel_gauche.show(); 
        rappel_droite.show();
      }
      if(100<=compteur && compteur<200){
        for (i=0; i<4; i++) {
          contour.setPixelColor(i,255,0,0);
          contour.setPixelColor(j-i,255,0,0);
          rappel_gauche.setPixelColor(i,255,255,255);                     
        }
        contour.show();
        rappel_gauche.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,255,75,0);                    
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,255,75,0);
          rappel_gauche.setPixelColor(i,255,255,255);                    
        }
        contour.show();
        rappel_droite.show();
        rappel_gauche.show();         
      }
      if(100<=compteur && compteur<200){
        for (i=13; i<21; i++) {
          contour.setPixelColor(i,255,0,0);                    
        }
        for (i=0; i<4; i++) {
          rappel_droite.setPixelColor(i,255,255,255);                    
        }
        contour.show();
        rappel_droite.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    }    
  }
}
