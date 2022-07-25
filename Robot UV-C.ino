#define m1 3
#define m2 5
#define m3 9
#define m4 10
#include <SoftwareSerial.h> //bluetooth library
SoftwareSerial module_bluetooth(0, 1); // pin RX | TX
#include <NewPing.h> //Utrasonic sensor library 
#define trig_pin A3 //analog input 1
#define echo_pin A2 //analog input 2

char data = 0;    
int arrow =0;
int a=0;
int b=0;
void setup() {

pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m4,OUTPUT);
pinMode(12,INPUT);
pinMode(13,INPUT);
//Serial.begin(9600);
Serial.begin(115200);         
pinMode(trig_pin,OUTPUT);
pinMode(echo_pin,INPUT);
pinMode(7, OUTPUT);  //PIN 7 Menjadi Output
digitalWrite(7, HIGH); // awal dibuat high supaya relay mati (karena modul relay aktif low)
}

void loop() {
// Sensor Ultrasonic  
  long duration, distance;
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration/2)/29.1;
  Serial.println(distance);

  if(distance <= 20){
    motorOut(0,80,2);
  }
  
// Bluetooth control
  if(Serial.available() > 0)  
  {
    data = Serial.read(); //Kirim data      
    if(data == '1'){
    digitalWrite(7, HIGH); //Hidupkan Lampu 1
    }
    else if(data == '2'){      
    digitalWrite(7, LOW); //Matian Lampu 1
    }
  } 
// dynamic line follower code
 
  int lsensor=digitalRead(12);
  int rsensor=digitalRead(13);


  if((lsensor == LOW)&&(rsensor== HIGH))
  {
// belok kanan
    motorOut(30,15,2);
    a=1;
  }
  if((lsensor== HIGH)&&(rsensor== LOW))
  {
//belok kiri
    motorOut(15,30,2);
    a=2;
  } 
//Lurus
if((lsensor==HIGH)&&(rsensor== HIGH))
{
 motorOut(30,30,2);
 
//maju
} 
if((lsensor== LOW)&&(rsensor==LOW)) 
{
 if(a==1){
 motorOut(30,0,2);}
 if(a==2){
 motorOut(0,30,2);}
} 
}
void motorOut(unsigned char lpwm, unsigned char rpwm, int arrow){
  //arrow =1 mundur, 2 maju, 
  if(arrow==1){
    digitalWrite(m3,HIGH);
    digitalWrite(m1,LOW);
    analogWrite(m4,255-lpwm);
    analogWrite(m2,rpwm);
  }
  else if (arrow==2)
  {
    digitalWrite(m3,LOW);
    digitalWrite(m1,HIGH);
    analogWrite(m4,lpwm);
    analogWrite(m2,255-rpwm);
  }
  
}
