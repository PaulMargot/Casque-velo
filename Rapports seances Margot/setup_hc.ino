#include<SoftwareSerial.h>
#define TX 10
#define RX 11
SoftwareSerial BlueT(TX,RX);

void setup(){
Serial.begin(9600);
delay(500);
Serial.println("Bonjour -Pret pour les commandes AT");
BlueT.begin(38400);
delay(500);}

void loop(){
while (BlueT.available()) {
Serial.print(char(BlueT.read())); }
while (Serial.available()) {
BlueT.write(char(Serial.read())); }
}
