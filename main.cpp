#include <Servo.h>
#define LED A1
#define LED2 A0
#define LED3 A2
#define echoPin1 2 
#define trigPin1 3 
#define echoPin2 A3 
#define trigPin2 A4 
#define buzzer A5 
#define SwitchPin 4

Servo servoMotor;
int SwitchState = 0;
int flag=0;
int lidOpen=30;
int fullDustbin=10;
bool isBeeping=true;
long duration, distance, FrontSensor,InnerSensor;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(5);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); 
  Serial.println("with Arduino UNO R3");
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SwitchPin, INPUT);
}
void loop() {
  servoMotor.write(0);
  SonarSensor(trigPin1, echoPin1);
  FrontSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  InnerSensor = distance;
  Serial.print("Distance: ");
  Serial.print(FrontSensor);
  Serial.println(" cm");
  Serial.print(" Distance2: ");
  Serial.print(InnerSensor);
  Serial.println(" cm");
  SwitchState = digitalRead(SwitchPin);
  

  if((InnerSensor)<fullDustbin){
    digitalWrite(LED2, HIGH); 
    if(isBeeping){
      tone(buzzer, 1000); 
  	delay(1000); 
      noTone(buzzer);
    }else{
     noTone(buzzer);
      digitalWrite(LED2, LOW);
    }
    digitalWrite(LED2, LOW);
    delay(1000);
    Serial.println("The dustbin is full. Please Empty it to Use Again.");
    SwitchState = digitalRead(SwitchPin);
  	Serial.println(SwitchState);
    isBeeping=false;
    while (SwitchState == HIGH) {
    digitalWrite(13, HIGH);
    servoMotor.write(90);
    digitalWrite(LED2, LOW);
  	noTone(buzzer);
    SwitchState = digitalRead(SwitchPin);
  		} 
    //else {
    		digitalWrite(13, LOW);
  	//}
  }
   else{
     digitalWrite(LED2, LOW);  
     
     if(FrontSensor<lidOpen)
  {
    servoMotor.write(90);  
    digitalWrite(LED, HIGH);   
  	delay(3000);                       
  	digitalWrite(LED, LOW);
    servoMotor.write(0);
    delay(3000);
  }   else{
     servoMotor.write(0);
     digitalWrite(LED, LOW);    
   };
   }
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 /2;

}
