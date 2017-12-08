#include "Arduino.h"
#include <SoftwareSerial.h>
char var;
String inString = "";
bool M = 1; //marcha
int rpm = 0;
int rpm_rueda = 0;
int buttonstate;
const int boton = 4;

void setup()
{
  Serial.begin(9600);
  delay(3000);
  pinMode(boton,INPUT);
}

void loop()
 {
    buttonstate=digitalRead(boton);
    if(buttonstate == HIGH){
          Serial.println("A1");
    }
    else{
        Serial.println("A0");
    }  
    
  if (Serial.available()>0 )
  {
    var = Serial.read();
    if(var == 'R')
    {
      while (Serial.available() > 0) {
        int var = Serial.read();
        if (isDigit(var)) {
            inString += (char)var;
        }
      }
    rpm = inString.toInt();
    }
    if (rpm > 2000)
    {
      if(M < 4){
          M = M + 1;
      }
      else{
          M = 4;
      }
        
      Serial.println('M',M);
    }
    if(rpm < 750)
    {
      if(M > 0)
      {
          M = M - 1;
      }
      else{
        M = 0;
      }
      Serial.println('M',M);
    }     
  }
}

