#include <Adafruit_NeoPixel.h>
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(61, PIN, NEO_GRB + NEO_KHZ800); //61:nb de LEDs

int i=0;
int j=0;


void setup() {
  
  strip.begin();
  strip.show(); //initialise les pixels en off
  
}



void loop() {

 if( i < 8 ){
    j=8-i;
    strip.setPixelColor(i,255,75,0);
    strip.setPixelColor(j,255,75,0); 
    strip.show();
    delay(150);   //allumage des LEDs les unes apres les autres
  }
 
  if( 8 < i ){
    if( i < 18 ){
      strip.setPixelColor(i,255,0,0);
      strip.show();
    }
  }

  if( 18 <= i ){
    if( i < 27){
      j=44-i;
      strip.setPixelColor(i,255,75,0);
      strip.setPixelColor(j,255,75,0); 
      strip.show();
      delay(150);
    }
  }

  if( 27 <= i){
    if( i < 36 ){
      strip.setPixelColor(i,255,0,0);
      strip.show();
    }
  }

  i++;

}





  
