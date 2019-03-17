int lumino;
char ancien_etat = "";
char etat = "";

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  lumino = analogRead(PHOTORES);
  ancien_etat = etat;

  if(lumino<=50){  
    etat = 'n'; 
  }
  if (lumino>=70){
     etat = 'j';  
  }

  if(ancien_etat!=etat){  
    Serial3.write(etat);  
  }
}
