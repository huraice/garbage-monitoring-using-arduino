long duration; // variable for the duration of sound wave travel
int distance;
#define echoPin 2 
#define trigPin 3
int i=0;
//gsm setup
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);  //Connect Rx, Tx (10,11) Pins to GSM module TX and RX
//int b;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");// print some text in Serial Monitor

}

void loop() {
  //checkdis( b);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  if(distance<10){
    Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(i==0){
    SendSMS();
  }
  i++;
  }
  // put your main code here, to run repeatedly:

}

void SendSMS()
{
  
  Serial.println("Setting the GSM in text mode");
  
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Garbage is filled");// The SMS text you want to send
  
  delay(100);
  int Distance=50-distance;
  mySerial.print(Distance);
  mySerial.print("cm");
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
