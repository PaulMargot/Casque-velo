#include <Adafruit_NeoPixel.h>
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(61, PIN, NEO_GRB + NEO_KHZ800); //61:nb de LEDs

void setup() {
  strip.begin();
  strip.show(); //initialise les pixels en off
}

void loop() {

  //cligno gauche
  for(int i = 0; i < 9; i++ ) {  //boucle permettant d'allumer les LEDs les unes apres les autres
    strip.setPixelColor(i,255,75,0); //allume les 9 premieres LEDs en orange
  }
  strip.show(); // on affiche 
  delay(100);
  

  //bas feu
  for(int i = 9; i < 18; i++ ) {  /
    strip.setPixelColor(i,255,0,0); //allume les 9 suivantes en rouge
  }
  strip.show(); // on affiche 
  delay(100);
  

  //cligno droit
  for(int i = 18; i < 27; i++ ) {  
    strip.setPixelColor(i,255,75,0); 
  }
  strip.show(); // on affiche 
  delay(100);
  

  //haut feu
  for(int i = 27; i < 36; i++ ) {  
    strip.setPixelColor(i,255,0,0);
  }
  strip.show(); // on affiche 
  delay(100);

}
