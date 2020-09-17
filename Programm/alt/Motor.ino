/*-> Bedienung <-  
  1.hellster Wert im rechten Opto einstellen
    2.dunkelster Wert im linken Opto eintstellen
    3.Knopf 1 sek. drücken(licht blinkt)
    4.Und los gehts :).*/

int state=0;

//Anschlüsse:
const int plusMotorRechts=10;
const int minusMotorRechts=11;
const int plusMotorLinks=6;
const int minusMotorLinks=5;
const int rechtsOpto=A5;
const int linksOpto=A4;
const int button=12;
const int licht=13;
//normale Variablen:
int optoR;
int optoL;
int optoW;
int optoS;
int push;

void setup(){
  pinMode(licht,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(rechtsOpto,INPUT);
  pinMode(linksOpto,INPUT);
  Serial.begin(9600);
  
}


void loop(){
  
  if (state==0)color();
  
  motor();
  digitalWrite(licht,1);
  Serial.println(optoW);
  
} 


void color(){
  
  while(digitalRead(button)==0){}
  while(digitalRead(button)==1){}
    digitalWrite(licht,1);
    delay(500);
    digitalWrite(licht,0);
    delay(500);
    scan();
    optoW=analogRead(rechtsOpto);
    optoS=analogRead(linksOpto);
  
  state++;
}


void scan(){//scan vom Optokoppler
  optoR=analogRead(rechtsOpto);
  optoL=analogRead(linksOpto);
}


void motor(){//Stellt die Motoren ein
  
  
  scan();
  //motorrechts
  if(optoR!=optoS){
    analogWrite(plusMotorRechts,255);
    analogWrite(minusMotorRechts,0);
  }else if(optoR==optoS){
    analogWrite(plusMotorRechts,100);
    analogWrite(minusMotorRechts,0);
  }
  //motorlinks
  if(optoL!=optoS){
    analogWrite(plusMotorLinks,255);
    analogWrite(minusMotorLinks,0);
  }else if(optoL==optoS){
    analogWrite(plusMotorLinks,100);
    analogWrite(minusMotorLinks,0);
  } 
  
  
}



  
