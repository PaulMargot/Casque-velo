#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel contour = Adafruit_NeoPixel(34, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rappel_gauche = Adafruit_NeoPixel(4, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rappel_droite = Adafruit_NeoPixel(4, PIN4, NEO_GRB + NEO_KHZ800);

int i=0;
int j=33;
int compteur=0;
char message = "";
char clignotant = "";
char ancien_clignotant = "";

void setup() {
  Serial3.begin(38400);
  contour.begin();
  rappel_gauche.begin();
  rappel_droite.begin();
  contour.show();
  rappel_gauche.show();
  rappel_droite.show();
}

void loop() {
  if (Serial3.available()) {
    message = Serial3.read();
    Serial.println(message);   
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

  /////Jour/////
  if (etat == 'j') {
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
          }
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,0,0,0);
            contour.setPixelColor(j-i,0,0,0);                     
          }
          contour.show();
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
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=13; i<21; i++) {
            contour.setPixelColor(i,0,0,0);                    
          }
          contour.show();
        }
        if(compteur==200){
          compteur=0;
        }
        compteur++;
      }
    }
    
    if(feu=='f'){
      if(clignotant=='g'){
        if(compteur<100){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,255,75,0);
            contour.setPixelColor(j-i,255,75,0);                     
          }
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,255,0,0);
            contour.setPixelColor(j-i,255,0,0);                     
          }
          contour.show();
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
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=13; i<21; i++) {
            contour.setPixelColor(i,255,0,0);                    
          }
          contour.show();
        }
        if(compteur==200){
          compteur=0;
        }
        compteur++;
      }
    }    
  }

/////Nuit/////
  if (etat == 'n') {
    if(feu=='a'){
      if(clignotant=='g'){
        if(compteur<100){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,255,75,0);
            contour.setPixelColor(j-i,255,75,0);                     
          }
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,0,0,0);
            contour.setPixelColor(j-i,0,0,0);                     
          }
          contour.show();
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
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=13; i<21; i++) {
            contour.setPixelColor(i,0,0,0);                    
          }
          contour.show();
        }
        if(compteur==200){
          compteur=0;
        }
        compteur++;
      }
    }

    if(feu=='f'){
      if(clignotant=='g'){
        if(compteur<100){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,255,75,0);
            contour.setPixelColor(j-i,255,75,0);                     
          }
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=0; i<4; i++) {
            contour.setPixelColor(i,255,0,0);
            contour.setPixelColor(j-i,255,0,0);                     
          }
          contour.show();
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
          contour.show(); 
        }
        if(100<=compteur && compteur<200){
          for (i=13; i<21; i++) {
            contour.setPixelColor(i,255,0,0);                    
          }
          contour.show();
        }
        if(compteur==200){
          compteur=0;
        }
        compteur++;
      }
    }  
  }
}
