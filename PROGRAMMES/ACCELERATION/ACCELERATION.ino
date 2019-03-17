#include <SoftwareSerial.h>
#include <Wire.h>

//***** BLUETOOTH *****
#define TX A2
#define RX A1

SoftwareSerial hc05(TX,RX);

//***** LEDS *****
#define led_frein 4 //OUTPUT & GND

//***** ACCELEROMETRE *****
const int MPU_addr = 0x68;
float Angle_Velo = 0.0;
float Corr_Acc_X = 0.0;
float Corr_Acc_Z = 0.0;
const int range_2g = 0x00;
const int range_4g = 0x08;
const int range_8g = 0x10;
const int diviseur_2g = (pow(2,16) / 4); //pleine échelle pour +- 2g
const int diviseur_4g = (pow(2,16) / 8); //pleine échelle pour +- 4g
const int diviseur_8g = (pow(2,16) / 16); //pleine échelle pour +- 8g

//***** GYROSCOPE *****
const int range_250ds = 0x00; // Pleine échelle à 250°/s
const int diviseur_250ds = (pow(2,16) / 500); //pleine échelle pour +- 250°/s
int Signe_Angle = 0;
float Anc_Gyr_Y = 0.0;
float Gyr_Y = 0.0;
float Angle_Y = 0.0;
long Anc_Temps = 0.0;
long Temps = 0.0;

const int Nb_Pts_Flt = 10;
float Acq_Acc_X[Nb_Pts_Flt];
float Acq_Acc_Y[Nb_Pts_Flt];
float Acq_Acc_Z[Nb_Pts_Flt];
float Acq_Gyr_Y = 0.0;
float Flt_Acc_X = 0.0;
float Flt_Acc_Z = 0.0;

int i = 0;
float Total_Acc_X =0.0;
float Total_Acc_Z = 0.0;

float Acc_Velo = 0.0;

float Offset_X = -0.019;
float Offset_Z = -0.015;
float FE_X = 0.985;
float FE_Z = 1.044;
float Acc_Zmax = -0.8;
float Acc_Zmin = -1.0;
float Acc_Zangle0 = -0.99;
boolean Feu_Stop = 0;

//***** PARAMETRES ACCELERATION *****
const float Seuil_Dec = -0.15; // seuil en g
const float Seuil_Acc = -0.05;

void setup() {
  
  //***** LEDS *****
  pinMode(led_frein, OUTPUT);
  digitalWrite(led_frein, LOW);

  //***** BLUETOOTH *****
  hc05.begin(38400);

  //***** ACCELERO / GYRO *****
  Wire.begin();
  //Reveil liaison I2C
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(false);
  
  //Initialisation accelero à échelle +-2g
  Wire.write(0x1c);
  Wire.write(range_2g);
  Wire.endTransmission();  

  //Initialisation accelero à échelle +-250°/s
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1b);
  Wire.write(range_250ds);
  Wire.endTransmission();
  
  //Initialisation moyenne glissante
  for (int j = 0; j < Nb_Pts_Flt; j++) {
    Acq_Acc_X[j] = 0.0;
    Acq_Acc_Z[j] = 0.0;
  }
}

void loop() {
  
  //***** ACCELEROMETRE *****
  
  //***** CALCUL DE L'ACCELERATION *****
 
  // Initialisation pour la moyenne glissante
  Total_Acc_X = Total_Acc_X - Acq_Acc_X[i];
  Total_Acc_Z = Total_Acc_Z - Acq_Acc_Z[i];

  //Acquisition des acceleromètres
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);
  
  Acq_Acc_X[i] = - (float) (Wire.read() << 8 | Wire.read()) / diviseur_2g; // 0x3B & 0x3C
  Acq_Acc_Y[i] = (float) (Wire.read() << 8 | Wire.read()) / diviseur_2g; // 0x3D & 0x3E
  Acq_Acc_Z[i] = (float) (Wire.read() << 8 | Wire.read()) / diviseur_2g; // 0x3F & 0x40

  //Acquisition du gyroscope Y
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x45);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 2, true);

  Acq_Gyr_Y = (float) ((Wire.read() << 8 | Wire.read())/ diviseur_250ds);
  
  //Filtrage des accelérations X & Z
  Total_Acc_X = Total_Acc_X + Acq_Acc_X[i];
  Total_Acc_Z = Total_Acc_Z + Acq_Acc_Z[i];

  i = i+1;
  if (i >= Nb_Pts_Flt) {
    i = 0;
  }
  
  Flt_Acc_X = Total_Acc_X / Nb_Pts_Flt;
  Flt_Acc_Z = Total_Acc_Z / Nb_Pts_Flt;
   
  //Correction FE & Offset
  Corr_Acc_X = (Flt_Acc_X - Offset_X) / FE_X;
  Corr_Acc_Z = (Flt_Acc_Z - Offset_Z) / FE_Z;    

  //Détermination du signe de l'angle du vélo

  if (Corr_Acc_Z > Acc_Zangle0)  {
    if (Signe_Angle == 0) {
      if (Acq_Gyr_Y < 0) {
        Signe_Angle = -1;
      }
      else  {
        Signe_Angle = 1;
      }
    }
  }
  else  {
    Signe_Angle = 0;
  }
  
  //Test Corr_Acc_Z & Calcul de Angle_Velo
  if (Corr_Acc_Z < Acc_Zmax && Corr_Acc_Z > Acc_Zmin) {
    Angle_Velo = Signe_Angle * (PI - acos(Corr_Acc_Z));
  } 
    
  //Calcul de Acc_Velo
  Acc_Velo = Corr_Acc_X + sin(Angle_Velo);

  //*** EVALUATION DE L'ACCELERATION ***
  //Test Acceleration
  if (Acc_Velo > Seuil_Acc) {
    if (Feu_Stop == 1) {
      Feu_Stop = 0;
      digitalWrite(led_frein, LOW);
      hc05.write("a");   
    }
  }
  else {
    if (Acc_Velo < Seuil_Dec) {
      if (Feu_Stop == 0) {
        Feu_Stop = 1;
        digitalWrite(led_frein, HIGH);
        hc05.write("f");
      }
    }      
  }

  delay(50);
}
