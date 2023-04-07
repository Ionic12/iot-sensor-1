#include "DHT.h"
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define LDR A0
#define DHTPIN D7
#define DHTTYPE DHT22
#define GREEN D0
#define BLUE D3
#define RED D5
#define trigPin D6
#define echoPin D8
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  dht.begin();
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print(F("\nHumidity : "));
  Serial.print(h);
  Serial.print(F("\nTemperature : "));
  Serial.print(t);
  Serial.print("\n");

  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd.print(F("Humidity   : "));
  lcd.print(h);
  lcd.print(F("%"));
  lcd.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd.print(F("Temperatur : "));
  lcd.print(t); 
  lcd.print(F("C"));

  // put your main code here, to run repeatedly:
  long duration, jarak;

  digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   jarak = duration * 0.034 / 2;
   Serial.print(jarak);
   Serial.println(" cm");
   delay(3000);

   int nilaiSensor;
   Serial.println("Contoh Penggunaan Sensor LDR");
    nilaiSensor = analogRead(LDR);
    Serial.print("Nilai Sensor : ");
    Serial.println(nilaiSensor);
    delay(3000);

  if(nilaiSensor >= 100 && t <= 18){
    // terang dan dingin
    digitalWrite(BLUE, HIGH);
  }
  else if(nilaiSensor <= 99 && t >= 30){
    // terang dan panas
    digitalWrite(RED, HIGH);
  }
  else if(jarak <= 10){
    //dekat
    digitalWrite(RED, HIGH);
  }
  else if(jarak >= 11 && jarak <= 20){
    //tengah
    digitalWrite(BLUE, HIGH);
  }
  else if(jarak >= 21 && jarak <= 30){
    //jauh
    digitalWrite(GREEN, HIGH);
  }
  else{
    digitalWrite(GREEN, HIGH);
    delay(100);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    delay(100);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, HIGH);
    delay(100);
    digitalWrite(BLUE, LOW);
  }
}