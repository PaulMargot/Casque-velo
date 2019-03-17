#include <SoftwareSerial.h>

//***** BLUETOOTH *****
#define TX A2
#define RX A1

SoftwareSerial hc05(TX,RX);

//***** BOUTONS *****
#define btn_cligno_gauche  7 //INPUT_PULLUP & GND
#define btn_cligno_droite  8 //INPUT_PULLUP & GND
#define btn_phare 11 //INPUT_PULLUP & GND
#define btn_cod 10 //INPUT_PULLUP & GND
#define btn_appel_phare 12 //INPUT_PULLUP & GND
char ancien_val_btn = 'e';
char val_btn = 'e';
int etat_btn_cligno_gauche;
int etat_btn_cligno_droite;
int etat_btn_phare;
int etat_btn_appel_phare;
char mess_envoi;

//***** LEDS *****
#define led_cligno 3 //OUTPUT & GND
#define led_phare 2 //OUTPUT & GND
int compteur = 0; //faire clignoter les LEDs

//***** PHARE *****
char message;

void setup() {
  
  //***** BOUTON *****
  pinMode(btn_cligno_gauche, INPUT_PULLUP);
  pinMode(btn_cligno_droite, INPUT_PULLUP);
  pinMode(btn_phare, INPUT_PULLUP);
  pinMode(btn_appel_phare, INPUT_PULLUP);
  pinMode(btn_cod, INPUT_PULLUP);

  //***** LEDS *****
  pinMode(led_cligno, OUTPUT);
  pinMode(led_phare, OUTPUT);
  digitalWrite(led_phare, LOW);
  digitalWrite(led_cligno, LOW); 

  //***** BLUETOOTH *****
  hc05.begin(38400);
}

void loop() {

  //***** PHARE *****
  if (hc05.available()) {
    message = hc05.read();
    Serial.println(message);
  }
  if (message == 'n') {
    digitalWrite(led_phare, HIGH);    
  }
  if (message == 'j') {
    digitalWrite(led_phare, LOW);    
  }
  
  //***** LECTURE DES BOUTONS *****
  etat_btn_cligno_gauche = digitalRead(btn_cligno_gauche);
  etat_btn_cligno_droite = digitalRead(btn_cligno_droite);
  etat_btn_phare = digitalRead(btn_phare);
  etat_btn_appel_phare = digitalRead(btn_appel_phare);
  ancien_val_btn = val_btn;

  //***** TESTS POUR LES CLIGNOTANTS *****  
  if (etat_btn_cligno_droite ==1 && etat_btn_cligno_gauche == 0) {
    if (compteur < 5) {
      digitalWrite(led_cligno, HIGH);
      compteur = compteur + 1;         
    }
    else if (compteur >= 5 && compteur < 10) {
      digitalWrite(led_cligno, LOW);
      compteur = compteur + 1;                
    }
    else {
      compteur = 0;
    }
    val_btn = 'g';      
   }      
   else if (etat_btn_cligno_droite == 0 && etat_btn_cligno_gauche == 1) {
     if (compteur < 5) {
       digitalWrite(led_cligno, HIGH);
       compteur = compteur + 1;         
     }
     else if (compteur >= 5 && compteur < 10) {
       digitalWrite(led_cligno, LOW);
       compteur = compteur + 1;                
     }
     else {
       compteur = 0;
     }
     val_btn = 'd';      
   }
   else if (etat_btn_cligno_gauche == 1 && etat_btn_cligno_droite == 1) {
     digitalWrite(led_cligno, LOW);
     val_btn = 'e';      
   }

   //***** TRANSMISSION DES COMMANDES POUR LES CLIGNOTANTS ****
   if (val_btn != ancien_val_btn) {
     hc05.write(val_btn);
   }
    
   //***** TESTS POUR LE PHARE ***** 
   if (etat_btn_phare == 0) {
     digitalWrite(led_phare, HIGH);
     mess_envoi = 'p';
   }
   else if (etat_btn_phare == 0 && message == 'j'){
     digitalWrite(led_phare, HIGH);
     mess_envoi = 'p';      
   }
   else if (etat_btn_phare == 1 && message == 'n'){
     digitalWrite(led_phare, HIGH);
     mess_envoi = 'p';        
   }
   else {
     digitalWrite(led_phare, LOW);
     mess_envoi = 'q';      
   }
    
   //***** TRANSMISSION DES COMMANDES POUR LE PHARE ****
   hc05.write(mess_envoi);
}
