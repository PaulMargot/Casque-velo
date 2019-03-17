char message = "";
char clignotant = "";
char feu = 'a';
char phare = "";


void setup() {
  Serial.begin(9600);
  Serial3.begin(38400);
}


void loop() {
  
  if (Serial3.available()) {
    message = Serial3.read();
    Serial.println(message);   
  }
  
  if(message == 'e'){   
    clignotant = 'e';
  }

  else if(message == 'g'){ 
    clignotant = 'g';
  }

  else if(message == 'd'){  
    clignotant = 'd';
  }

  else if(message == 'f'){   
    feu = 'f';
  }

  else if(message == 'a'){  
    feu = 'a';
  }

  else if (message == 'p') {
    phare = 'p';
  }

  else if (message == 'q') {
    phare = 'q';
  }

}
