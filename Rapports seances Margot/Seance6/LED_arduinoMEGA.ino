#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(61, PIN, NEO_GRB + NEO_KHZ800); //61:nb de LEDs

int i=0;
int j=0;


// Clignotants
char message = "";
char clignotant = "";


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
  


  if(message == 'e'){   
    clignotant = 'e';
  }

  else if(message == 'g'){ 
    clignotant = 'g';
  }

  else if(message == 'd'){  
    clignotant = 'd';
  }


//Cas nuit:

  if(clignotant=='e' && etat=='n'){
    strip.setPixelColor(i,255,0,0);
    strip.show();
    i++;
    if(i==60){  //reinitialisation de i a 0 pour pouvoir remplir les autres conditions
      i=0;
    }
  }


  if(clignotant=='g' && etat=='n'){
    if( i < 8 ){
      j=8-i;
      strip.setPixelColor(i,255,75,0);
      strip.setPixelColor(j,255,75,0);
      strip.show(); 
      delay(150);
    }
    else{
      strip.setPixelColor(i,255,0,0);
      strip.show();
    }
    i++;
    if(i==60){
      i=0;
    }
  }

  if(clignotant=='d' && etat=='n'){
    if( 18 <= i && i < 27){
        j=44-i;
        strip.setPixelColor(i,255,75,0);
        strip.setPixelColor(j,255,75,0); 
        strip.show();
        delay(150);
    }
    else{
      strip.setPixelColor(i,255,0,0);
      strip.show();
    }
    i++;
    if(i==60){
      i=0;
    }
  }



// Feu accelerometre
  if(message == 'f'){   
    feu = 'f';
  }

  else if(message == 'a'){  
    feu = 'a';
  }


  if(feu=='f'){   // si l'hc05 envoie 'f' c'est qu'on freine donc on allume la led rouge (le feu)
    strip.setPixelColor(i,255,0,0);
    strip.show();
    i++;
  }

  else if(feu=='a'){  //si on reçoit 'a', on l'éteint
  }
   

}
