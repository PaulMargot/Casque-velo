#include <Adafruit_NeoPixel.h>

#define PIN1 6

Adafruit_NeoPixel contour = Adafruit_NeoPixel(34, PIN1, NEO_GRB + NEO_KHZ800);

int i=0;
int j=33;
char etat = "";
char feu = 'a';


void setup() {
  contour.begin();
  contour.show();
}


void loop() {
  
  if (etat == 'j') {
    if(feu=='a'){
      for(i=0; i<34; i++){
        contour.setPixelColor(i,0,0,0);
      }
      contour.show();
    }
    if(feu=='f'){
      for(i=0; i<34; i++){
        contour.setPixelColor(i,255,0,0);
      }
      contour.show(); 
    }
  }

  if (etat == 'n') {
    if(feu=='a'){
      for(i=0; i<34; i++){
        contour.setPixelColor(i,0,0,0);
      }
      contour.show();
    }
    if(feu=='f'){
      for(i=0; i<34; i++){
        contour.setPixelColor(i,255,0,0);
      }
      contour.show();
    }
  }     
}
