#include <SoftwareSerial.h>
#include <Servo.h> 

SoftwareSerial SIM900(3, 4);
String textForSMS;

int flamesensor = 10;
int buzzer = 2;
int relay = 8;
int green =6;
int servoPin = 12;
Servo Servo1;


void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM900.begin(9600); // original 19200. while enter 9600 for sim900A
  Serial.println("logging time completed!");

  pinMode(flamesensor, INPUT);
  Servo1.attach(servoPin); 
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
  digitalWrite(green, LOW);

}

void loop() {
  {
   for(int i=0;i<=180;i=i+5)
   {
    Servo1.write(i);
    delay(100);
    if ( digitalRead(flamesensor) == HIGH) //

  {
    textForSMS =  " ALERT!! FIRE IN THE FOREST .";
    tone(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    digitalWrite(green, LOW);
    //sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent."); 
    delay(10000);
    ;
  }
   else
 {
    
    digitalWrite(relay, LOW);
    noTone(buzzer);
//    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");

  };
    }
    for(int i=180;i>=0;i=i-5)
   {
    Servo1.write(i);
    delay(100);
    if ( digitalRead(flamesensor) == HIGH) //

  {
    textForSMS =  " ALERT!! FIRE IN THE forest .";
    tone(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    digitalWrite(green, LOW);
    //sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");
    delay(10000);
  }
   else
 {
   
    digitalWrite(relay, LOW);
    noTone(buzzer);
//    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");

  };
    }
   }
  }
  void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(500);
  SIM900.println("AT + CMGS = \"+917386144664\"");  // recipient's mobile number, in international format

  delay(500);
  SIM900.println(message);                         // message to send

  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(500);
  SIM900.println();
  // give module time to send SMS

}
