#include <SoftwareSerial.h>
SoftwareSerial hc06(10,11);

const int led_D1=4;
const int led_D2=5;
const int led_D3=6;

const int led_G1=7;
const int led_G2=8;
const int led_G3=9;

char message = "";
char clignotant = "";



void setup() {

  pinMode(led_D1,OUTPUT);
  pinMode(led_D2,OUTPUT);
  pinMode(led_D3,OUTPUT);
  pinMode(led_G1,OUTPUT);
  pinMode(led_G2,OUTPUT);
  pinMode(led_G3,OUTPUT);

  Serial.begin(9600);
  hc06.begin(38400);

}


void loop() {

  if(hc06.available()){
    message = hc06.read();
  }
  


  if(message == 'e'){
    clignotant = 'e';
  }

  else if(message == 'w'){
    clignotant = 'w';
  }

  else if(message == 'g'){
    clignotant = 'g';
  }

  else if(message == 'd'){
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

   

}
