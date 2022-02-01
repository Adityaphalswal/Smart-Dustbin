#include <stdio.h>
#include <Servo.h>
Servo servoMotor;
#include <LiquidCrystal.h>
#define LEDGreen A1
#define LEDRed A0
#define LEDBlue A2
#define echoPin1 2
#define trigPin1 3
#define echoPin2 A3
#define trigPin2 A4
#define buzzer A5
#define SwitchPin 4
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int SwitchState = 0;
int flag = 0;
int lidOpen = 30;
int fullDustbin = 10;
int halfDustbin = 20;
int emptyDustbin = 60;
bool isBeeping = true;
int duration, distance, FrontSensor, InnerSensor;

void setup()
{
    Serial.begin(9600);
    servoMotor.attach(5);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(LEDRed, OUTPUT);
    pinMode(LEDGreen, OUTPUT);
    pinMode(LEDBlue, OUTPUT);
    pinMode(SwitchPin, INPUT);
    lcd.begin(16, 2);
}
void loop()
{
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

    if (InnerSensor < 5)
    {
        digitalWrite(LEDRed, HIGH);
        while (isBeeping)
        {
            beep();
        }
        lcd.setCursor(0, 0);
        lcd.print("The dustbin is");
        lcd.setCursor(0,1);
        lcd.print("full.");
        delay(1500);
      	lcd.clear();
        SwitchState = digitalRead(SwitchPin);
        while (SwitchState == HIGH)
        {
            offLed();
            servoMotor.write(90);
            digitalWrite(LEDGreen, HIGH);
            SwitchState = digitalRead(SwitchPin);
            offLed();
        }
        digitalWrite(LEDRed, HIGH);
    }
    else
    {
        if (InnerSensor < 60 && InnerSensor > 30)
        {
            offLed();
            digitalWrite(LEDGreen, HIGH);
            if (FrontSensor < lidOpen)
            {
                offLed();
                moveServo();
            }
            else
            {
                digitalWrite(LEDGreen, HIGH);
            }
            lcd.setCursor(0, 0);
            lcd.print("The dustbin is");
          	lcd.setCursor(0, 1);
            lcd.print("empty.");
          	delay(1500);
          	lcd.clear();
        }
        else if (InnerSensor < 30 && InnerSensor > 5)
        {
            offLed();
            digitalWrite(LEDBlue, HIGH);
            if (FrontSensor < lidOpen)
            {
                offLed();
                moveServo();
            }
            else
            {
                digitalWrite(LEDBlue, HIGH);
            }
            lcd.setCursor(0, 0);
            lcd.print("The dustbin is");
          	lcd.setCursor(0, 1);
            lcd.print("nearly full.");
          	delay(1500);
          	lcd.clear();
        }
    }
}

void offLed()
{
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDBlue, LOW);
    digitalWrite(LEDGreen, LOW);
}

void moveServo()
{
    lcd.setCursor(0, 0);
    lcd.print("Lid is Opening...");
    servoMotor.write(90);
    offLed();
    digitalWrite(LEDGreen, HIGH);
    delay(3000);
    digitalWrite(LEDGreen, LOW);
    servoMotor.write(0);
    delay(3000);
    noTone(buzzer);lcd.clear();
}
void beep()
{
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    isBeeping = false;
}
void SonarSensor(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
}

