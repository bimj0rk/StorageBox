#include <Servo.h>
#include "SR04.h"
#include "IRremote.h"
#define TRIG_PIN 12
#define ECHO_PIN 11

int activeBuzzer = 13; //buzzer-ul este conectat pe pinul 13

Servo servoMotor; //initializez servo-ul
int position = 0; //pozitia initiala: 0


//initializez senzorul ultrasonic
SR04 ultrasonicSensor = SR04(ECHO_PIN, TRIG_PIN);
long distance;


//initializez senzorul IR
int reciever = 9;
IRrecv irrecv(reciever);
decode_results results;
int remoteButton;

void setup(){
  Serial.begin(9600); 
  pinMode(activeBuzzer, OUTPUT); //activez buzzer-ul ca output */
  servoMotor.attach(10); //servo-ul este conectat pe pinul 10
  irrecv.enableIRIn(); //activez reciever-ul IR
}

//traducerea butoanelor folosite de pe telecomanda IR
void translateIR(){
  switch(results.value){
    case 0xFF629D: //butonul CH de pe telecomanda, va fi folosit pentru modul autonom
      autonomousMode();
      break;
      
    case 0xFFA857: //butonul + de pe telecomanda, va fi folosit pentru deschiderea manuala
      manualOverrideOpen();
      break;

    case 0xFFE01F: //butonul - de pe telecomanda, va fi folosit pentru inchiderea manuala
      manualOverrideClose();
      break;

    default:
      Serial.println("Button not found");
  }
}

void autonomousMode(){
  Serial.println("Autonomous mode");
  //servo-ul va deschide usor capacul
  for(position = 0; position <= 115; position++){ 
      servoMotor.write(position);            
      delay(15);
  }

  delay(8000); //timp de asteptate: 8 secunde

  //sunet de avertizare
  digitalWrite(activeBuzzer, HIGH);
  delay(1);
  digitalWrite(activeBuzzer, LOW);

   //timp de asteptare: 2 secunde
  delay(2000);

  //servo-ul inchide capacul
  servoMotor.write(20);

  Serial.println("Autonomous mode ended");
}

void manualOverrideOpen(){
  Serial.println("Manual open");

  //sunet de avertizare
  digitalWrite(activeBuzzer, HIGH);
  delay(1);
  digitalWrite(activeBuzzer, LOW);
  delay(1000);

  //servo-ul va deschide usor capacul
  for(int position = 0; position <= 115; position++){
      servoMotor.write(position);            
      delay(15);
  }

  //sunet de avertizare
  digitalWrite(activeBuzzer, HIGH);
  delay(1);
  digitalWrite(activeBuzzer, LOW);
  delay(1);

  Serial.println("Manual open ended");
}

void manualOverrideClose(){
  Serial.println("Manual close");

  //sunet de avertizare
  digitalWrite(activeBuzzer, HIGH);
  delay(1);
  digitalWrite(activeBuzzer, LOW);
  delay(1000);

  //servo-ul inchide capacul
  servoMotor.write(20);

  //sunet de avertizare
  digitalWrite(activeBuzzer, HIGH);
  delay(1);
  digitalWrite(activeBuzzer, LOW);
  delay(1);

  Serial.println("Manual close ended");
}

void loop(){
  distance = ultrasonicSensor.Distance(); 

  if(irrecv.decode(&results)){
    translateIR();
    irrecv.resume();
  }

  if(distance <= 4) autonomousMode(); //daca mana trece la mai putin de 4cm, se porneste modul autonom

}