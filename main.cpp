#include <Servo.h>
#define LED 13
#define LED2 12
#define echoPin 2 
#define trigPin 3 
#define echoPin2 4 
#define trigPin2 5 
#define buzzer 7 


Servo servoMotor;
long duration;
long duration2;
int distance; 
int distance2;

void setup() {
  servoMotor.attach(5);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); 
  Serial.println("with Arduino UNO R3");
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
void loop() {
  servoMotor.write(0);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  distance = duration * 0.034 / 2; 
  distance2 = duration2 *0.034 /2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print(" Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  
  
  if(distance2<10){
    digitalWrite(LED2, HIGH);   
  	delay(100);                      
  	digitalWrite(LED2, LOW);
    tone(buzzer, 1000); // Send 1KHz sound signal...
  	delay(1000);        // ...for 1 sec
  	noTone(buzzer);     // Stop sound...
  	delay(1000);
    Serial.println("The dustbin is full. Please Empty it to Use Again.");
    servoMotor.write(0);
    digitalWrite(LED, LOW);
   }
   else{
     digitalWrite(LED2, LOW);  
     
     if(distance<30)
  {
    servoMotor.write(180);  
    digitalWrite(LED, HIGH);   
  	delay(500);                       
  	digitalWrite(LED, LOW);   
    delay(3000);
    
  }
   else{
     servoMotor.write(0);
     digitalWrite(LED, LOW);    
     delay(50);
   };
     delay(50);
   }
}
