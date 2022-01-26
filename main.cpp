#include <Servo.h>
#define LED 13
#define LED2 12
#define echoPin1 2 
#define trigPin1 3 
#define echoPin2 4 
#define trigPin2 5 
#define buzzer 7 

Servo servoMotor;
int buttonState = 0;
int flag=0;
long duration, distance, FrontSensor,InnerSensor;
void setup() {
  Serial.begin(9600);
  servoMotor.attach(6);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); 
  Serial.println("with Arduino UNO R3");
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
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
  
  if((InnerSensor)<10){
    digitalWrite(LED2, HIGH);   
    tone(buzzer, 1000); 
  	delay(1000); 
    digitalWrite(LED2, LOW);
  	noTone(buzzer);   
    Serial.println("The dustbin is full. Please Empty it to Use Again.");
   }
   else{
     digitalWrite(LED2, LOW);  
     
     if(FrontSensor<30)
  {
    servoMotor.write(90);  
    digitalWrite(LED, HIGH);   
  	delay(3000);                       
  	digitalWrite(LED, LOW);
    servoMotor.write(0);
    delay(3000);
  }
   else{
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
