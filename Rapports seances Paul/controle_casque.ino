#include <SoftwareSerial.h>
#include <Wire.h>

//***** BLUETOOTH *****
#define TX 10
#define RX 11

SoftwareSerial hc05(TX,RX);

//***** BOUTON *****
int switch_gauche = 2; //INPUT_PULLUP & GND
int switch_droite = 3; //INPUT_PULLUP & GND
char ancien_val_btn = 'e';
char val_btn = 'e';
int etat_switch_gauche = 1;
int etat_switch_droite = 1;
int led_gauche = 5; //OUTPUT & GND
int led_droite = 6; //OUTPUT & GND

//***** ACCELEROMETRE *****
int led_frein = 4; //OUTPUT & GND
const int MPU_addr = 0x68;
float Acc_X = 0;
float Acc_Y = 0;
float Acc_Z = 0;
float angle_X = 0;
float Acc_X_corrige = 0;
const int range_2g = 0x00;
const int range_4g = 0x08;
const int range_8g = 0x10;
const int diviseur_2g = (pow(2,16) / 4); //pleine échelle pour +- 2g
const int diviseur_4g = (pow(2,16) / 8); //pleine échelle pour +- 4g
const int diviseur_8g = (pow(2,16) / 16); //pleine échelle pour +- 8g
boolean deceleration = 0;

int filtre_deceleration = 0;
int filtre_acceleration = 0;

//***** PARAMETRES ACCELERATION *****
const float seuil_deceleration = 0.01; // seuil en g
const float seuil_acceleration = 0.05;

const int seuil_flt_deceleration = 3; // niveau de filtrage
const int seuil_flt_acceleration = 3;

//***** PHARE *****
char message;
int led_phare = 7; //OUTPUT & GND


void setup() {
  //***** BOUTON *****
  pinMode(switch_gauche, INPUT_PULLUP);
  pinMode(switch_droite, INPUT_PULLUP);
  pinMode(led_gauche, OUTPUT);
  pinMode(led_droite, OUTPUT);
  
  //***** BLUETOOTH *****
  hc05.begin(38400);

  //***** MONITEUR *****
  Serial.begin(9600);

  //***** ACCELEROMETRE *****
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission();

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1c);
  Wire.write(range_4g);
  Wire.endTransmission();
  pinMode(led_frein, OUTPUT);

  //***** PHARE *****
  pinMode(led_phare, OUTPUT);
  digitalWrite(led_phare, LOW);
}

void loop() {
  //***** BOUTON *****
  etat_switch_gauche = digitalRead(switch_gauche);
  etat_switch_droite = digitalRead(switch_droite);
  ancien_val_btn = val_btn;
  
    if (etat_switch_gauche == 0 && etat_switch_droite == 0) {
      digitalWrite(led_gauche, HIGH);
      digitalWrite(led_droite, HIGH);
      val_btn = 'w';      
    }
    else if (etat_switch_gauche == 0 && etat_switch_droite == 1) {
      digitalWrite(led_gauche, HIGH);
      digitalWrite(led_droite, LOW);
      val_btn = 'g';      
    }      
    else if (etat_switch_droite == 0 && etat_switch_gauche == 1) {
      digitalWrite(led_gauche, LOW);
      digitalWrite(led_droite, HIGH);
      val_btn = 'd';      
    }
    else {
      digitalWrite(led_gauche, LOW);
      digitalWrite(led_droite, LOW);
      val_btn = 'e';      
    }

    if (val_btn != ancien_val_btn) {
      Serial.println(val_btn);
      hc05.write(val_btn);
    }

  //***** ACCELEROMETRE *****
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);
 
  Acc_X = (float) (Wire.read() << 8 | Wire.read()) / diviseur_4g;
  Acc_Y = (float) (Wire.read() << 8 | Wire.read()) / diviseur_4g;
  Acc_Z = (float) (Wire.read() << 8 | Wire.read()) / diviseur_4g;


  angle_X = atan(Acc_X / sqrt(pow(Acc_Y,2) + pow(Acc_Z,2)));
  Acc_X_corrige = Acc_X - sin(angle_X);

  //Affichage();

  if (deceleration == 0) {
    if (Acc_X_corrige < seuil_deceleration) {
      filtre_deceleration = filtre_deceleration +1;
      // Affichage();
      if (filtre_deceleration == seuil_flt_deceleration) {
        digitalWrite(led_frein, LOW);
        hc05.write("a");
        delay(100);
        
        deceleration = 1;
        
        Serial.println("------------------------------------------------------------------------------------------------------------------------------");
        Serial.println("Décélération:       ");
        Affichage();
        
        filtre_deceleration = 0;
      }
    }
  else {
    filtre_deceleration = 0;
  }
}


  if (deceleration == 1) {
    if (Acc_X_corrige > seuil_acceleration) {
      filtre_acceleration = filtre_acceleration +1;
      // Affichage();
      if (filtre_acceleration == seuil_flt_acceleration) {
        digitalWrite(led_frein, HIGH);
        hc05.write("f");
        delay(100);
                
        deceleration = 0;


        Serial.println("Fin de décélération:");
        Affichage();
        Serial.println("------------------------------------------------------------------------------------------------------------------------------");

        filtre_acceleration = 0;
      }
    }
    else {
      filtre_acceleration = 0;
    }
  }

  //***** PHARE *****
  if (hc05.available()) {
    message = hc05.read();
  }
  if (message == 'n') {
    digitalWrite(led_phare, HIGH);    
  }
  if (message == 'j') {
    digitalWrite(led_phare, LOW);    
  }

    
}

void Affichage()
{
  Serial.print("  | Acc_X = ");
  Serial.print(Acc_X);
  Serial.print("  | Acc_Y = ");
  Serial.print(Acc_Y);
  Serial.print("  | Acc_Z = ");
  Serial.print(Acc_Z);
  Serial.print("  | Angle de correction = ");
  Serial.print(angle_X*180/3.1416);
  Serial.print("  | Acc_X corrigée = ");
  Serial.print(Acc_X_corrige);
  Serial.print("  | Flt decelaration = ");
  Serial.print(filtre_deceleration);
  Serial.print("  | Flt_acceleration = ");
  Serial.println(filtre_acceleration);
}
