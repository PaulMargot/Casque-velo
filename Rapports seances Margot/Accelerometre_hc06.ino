#include <SoftwareSerial.h>
SoftwareSerial hc06(10,11);

const int led_rouge=3;

char message = "";

float acc = 0;
float ancienne_acc = 0;



void setup() {
  
  pinMode(led_rouge,OUTPUT);
  Serial.begin(9600);
  hc06.begin(38400);

}



void loop() {
  
  if(hc06.available()){
    message = hc06.read();
    Serial.println(message);
  }
  
  acc = message;
  if(ancienne_acc>acc){
    digitalWrite(led_rouge,HIGH);
  }
  else{
    digitalWrite(led_rouge,LOW);
  }
  ancienne_acc = acc;
}
