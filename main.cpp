#include <Arduino.h>

int val1, val2, val3, val4;
int stage, switchPin = 7;

bool valChanged(int pin, int val);
void reset();

void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(switchPin, INPUT);
  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(13, HIGH);

  stage = 0;

  Serial.begin(9600);
}

void loop() {
  
Serial.println(analogRead(A0));

if(stage == 0){
  digitalWrite(13, HIGH);
}else{
  digitalWrite(13, LOW);
}

if(digitalRead(switchPin) == HIGH && stage == 0){
  val1 = analogRead(A0);
  val2 = analogRead(A1);
  val3 = analogRead(A2);
  val4 = analogRead(A3);
  digitalWrite(2, HIGH);
  stage = 1;
  Serial.println(analogRead(A0));
  Serial.println("button pressed");
}

if(valChanged(A0, val1) && stage == 1){
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  stage = 2;
  Serial.println(analogRead(A0));
  Serial.println("coil 1 off");
}

if(valChanged(A1, val2) && stage == 2){
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  stage = 3;
  Serial.println("coil 2 off");
}

if(valChanged(A2, val3) && stage == 3){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  stage = 4;
  Serial.println("coil 3 off");
}

if(valChanged(A3, val4) && stage == 4){
  digitalWrite(5, LOW);
  stage = 0;
  
  Serial.println("coil 4 off");
  Serial.end();

  while(digitalRead(switchPin) != 0){
    delay(1);
  }
  
  reset();
}

}

bool valChanged(int pin, int val){
  int bias = 4;
  int detected = 0;

  for(int i = 0; i < 3; i++){
    if(analogRead(pin) <= val - bias){
       detected++;
    }
  }

  if(detected == 3){
    return true;
  }

  return false;
}

void(* resetFunc) (void) = 0;
void reset(){
  resetFunc();
}