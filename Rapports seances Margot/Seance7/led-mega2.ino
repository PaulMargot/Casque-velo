#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(61, PIN, NEO_GRB + NEO_KHZ800); //61:nb de LEDs

int i=0;
int compteur=0;


// Clignotants
char message = "";
char clignotant = "";
char ancien_clignotant = "";


// Feu luminosite
const int sensorPin = A0;   


// Feu accelerometre
char feu = "";


// Phare
char ancien_etat = "";
char etat = "";


void setup() {

  Serial3.begin(38400);
  Serial.begin(9600);

  strip.begin();
  strip.show();
  
}

void loop() {

// Clingotants
  if(Serial3.available()){
    message = Serial3.read();
    Serial.println(message);
  }


// Feu/Phare luminosite

  int valeur = analogRead(sensorPin); 
  //Serial.println(valeur);


  ancien_etat = etat;

  if(valeur<=700){  
    etat = 'n'; 
  }

  else{
     etat = 'j';  
  }

  if(ancien_etat!=etat){  
    //Serial.println(etat);
    Serial3.write(etat);  
  }

  ancien_clignotant = clignotant;

  if(message == 'e'){   
    clignotant = 'e';
  }

  else if(message == 'g'){ 
    clignotant = 'g';
  }

  else if(message == 'd'){  
    clignotant = 'd';
  }


// Feu accelerometre
  else if(message == 'f'){   
    feu = 'f';
  }

  else if(message == 'a'){  
    feu = 'a';
  }


/*********Traitement cas jour*********/

  if(etat=='j'){
    
    if(feu=='a'){
      
      if(clignotant=='e' || ancien_clignotant!=clignotant){
        for(i=0; i<27; i++){
          strip.setPixelColor(i,0,0,0);
        }
      strip.show();
      }
    
    if(clignotant=='g'){
      if(compteur<100){
        strip.setPixelColor(0,255,75,0);
        strip.setPixelColor(1,255,75,0);
        strip.setPixelColor(2,255,75,0);
        strip.setPixelColor(3,255,75,0);
        strip.setPixelColor(4,255,75,0);
        strip.setPixelColor(5,255,75,0);
        strip.setPixelColor(6,255,75,0);
        strip.setPixelColor(7,255,75,0);
        strip.setPixelColor(8,255,75,0);
        strip.show(); 
      }
      if(100<=compteur && compteur<200){
        strip.setPixelColor(0,0,0,0);
        strip.setPixelColor(1,0,0,0);
        strip.setPixelColor(2,0,0,0);
        strip.setPixelColor(3,0,0,0);
        strip.setPixelColor(4,0,0,0);
        strip.setPixelColor(5,0,0,0);
        strip.setPixelColor(6,0,0,0);
        strip.setPixelColor(7,0,0,0);
        strip.setPixelColor(8,0,0,0);
        strip.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        strip.setPixelColor(18,255,75,0);
        strip.setPixelColor(19,255,75,0);
        strip.setPixelColor(20,255,75,0);
        strip.setPixelColor(21,255,75,0);
        strip.setPixelColor(22,255,75,0);
        strip.setPixelColor(23,255,75,0);
        strip.setPixelColor(24,255,75,0);
        strip.setPixelColor(25,255,75,0);
        strip.setPixelColor(26,255,75,0);
        strip.show(); 
      }
      if(100<=compteur && compteur<200){
        strip.setPixelColor(18,0,0,0);
        strip.setPixelColor(19,0,0,0);
        strip.setPixelColor(20,0,0,0);
        strip.setPixelColor(21,0,0,0);
        strip.setPixelColor(22,0,0,0);
        strip.setPixelColor(23,0,0,0);
        strip.setPixelColor(24,0,0,0);
        strip.setPixelColor(25,0,0,0);
        strip.setPixelColor(26,0,0,0);
        strip.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    }

    if(feu=='f'){
      
      if(clignotant=='e' || ancien_clignotant!=clignotant){
        for(i=0; i<27; i++){
          strip.setPixelColor(i,255,0,0);
        }
      strip.show();
      }
    
    if(clignotant=='g'){
      if(compteur<100){
        strip.setPixelColor(0,255,75,0);
        strip.setPixelColor(1,255,75,0);
        strip.setPixelColor(2,255,75,0);
        strip.setPixelColor(3,255,75,0);
        strip.setPixelColor(4,255,75,0);
        strip.setPixelColor(5,255,75,0);
        strip.setPixelColor(6,255,75,0);
        strip.setPixelColor(7,255,75,0);
        strip.setPixelColor(8,255,75,0);
        strip.show(); 
      }
      if(100<=compteur && compteur<200){
        strip.setPixelColor(0,255,0,0);
        strip.setPixelColor(1,255,0,0);
        strip.setPixelColor(2,255,0,0);
        strip.setPixelColor(3,255,0,0);
        strip.setPixelColor(4,255,0,0);
        strip.setPixelColor(5,255,0,0);
        strip.setPixelColor(6,255,0,0);
        strip.setPixelColor(7,255,0,0);
        strip.setPixelColor(8,255,0,0);
        strip.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        strip.setPixelColor(18,255,75,0);
        strip.setPixelColor(19,255,75,0);
        strip.setPixelColor(20,255,75,0);
        strip.setPixelColor(21,255,75,0);
        strip.setPixelColor(22,255,75,0);
        strip.setPixelColor(23,255,75,0);
        strip.setPixelColor(24,255,75,0);
        strip.setPixelColor(25,255,75,0);
        strip.setPixelColor(26,255,75,0);
        strip.show(); 
      }
      if(100<=compteur && compteur<200){
        strip.setPixelColor(18,255,0,0);
        strip.setPixelColor(19,255,0,0);
        strip.setPixelColor(20,255,0,0);
        strip.setPixelColor(21,255,0,0);
        strip.setPixelColor(22,255,0,0);
        strip.setPixelColor(23,255,0,0);
        strip.setPixelColor(24,255,0,0);
        strip.setPixelColor(25,255,0,0);
        strip.setPixelColor(26,255,0,0);
        strip.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    }
    
  }


/*********Traitement cas nuit*********/

  if(etat=='n'){
    
    if(feu=='a'){
    }

    if(feu=='f'){
    }

    if(clignotant=='e' || ancien_clignotant!=clignotant){
        for(i=0; i<27; i++){
          strip.setPixelColor(i,255,0,0);
        }
      strip.show();
      }
    
    if(clignotant=='g'){
      if(compteur<100){
        strip.setPixelColor(0,255,75,0);
        strip.setPixelColor(1,255,75,0);
        strip.setPixelColor(2,255,75,0);
        strip.setPixelColor(3,255,75,0);
        strip.setPixelColor(4,255,75,0);
        strip.setPixelColor(5,255,75,0);
        strip.setPixelColor(6,255,75,0);
        strip.setPixelColor(7,255,75,0);
        strip.setPixelColor(8,255,75,0);
        strip.show(); 
      }
      if(100<=compteur && compteur<200){
        strip.setPixelColor(0,255,0,0);
        strip.setPixelColor(1,255,0,0);
        strip.setPixelColor(2,255,0,0);
        strip.setPixelColor(3,255,0,0);
        strip.setPixelColor(4,255,0,0);
        strip.setPixelColor(5,255,0,0);
        strip.setPixelColor(6,255,0,0);
        strip.setPixelColor(7,255,0,0);
        strip.setPixelColor(8,255,0,0);
        strip.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }

    if(clignotant=='d'){
      if(compteur<100){
        strip.setPixelColor(18,255,75,0);
        strip.setPixelColor(19,255,75,0);
        strip.setPixelColor(20,255,75,0);
        strip.setPixelColor(21,255,75,0);
        strip.setPixelColor(22,255,75,0);
        strip.setPixelColor(23,255,75,0);
        strip.setPixelColor(24,255,75,0);
        strip.setPixelColor(25,255,75,0);
        strip.setPixelColor(26,255,75,0);
        strip.show(); 
      }
      if(100<=compteur && compteur<200){
        strip.setPixelColor(18,255,0,0);
        strip.setPixelColor(19,255,0,0);
        strip.setPixelColor(20,255,0,0);
        strip.setPixelColor(21,255,0,0);
        strip.setPixelColor(22,255,0,0);
        strip.setPixelColor(23,255,0,0);
        strip.setPixelColor(24,255,0,0);
        strip.setPixelColor(25,255,0,0);
        strip.setPixelColor(26,255,0,0);
        strip.show();
      }
      if(compteur==200){
        compteur=0;
      }
      compteur++;
    }
    
  }
  

}
