#include "Air_Quality_Sensor.h"
#include <Wire.h>
 
AirQualitySensor sensor(A0);
#define SensorPin 2          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
int soundPin = 13;


 
void setup()
{
  pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Ready");    //Test the serial monitor
  pinMode(1, INPUT);

  
}
void loop()
{
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  detectSound();
  detectAirQuality();
  distanceSensor();
  Serial.println("------");
  delay(1000);
 
}

void detectSound(void) {
  if (digitalRead(soundPin) == HIGH) {
    Serial.println("Loud noise detected!");
  } else {
    Serial.println("It's quiet");
  }
}

void detectAirQuality(void) {
  int quality = sensor.slope();
  Serial.print("Sensor value: ");
  Serial.println(sensor.getValue());

    if (quality == AirQualitySensor::FORCE_SIGNAL) {
        Serial.println("High pollution! Force signal active.");
    } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
        Serial.println("High pollution!");
    } else if (quality == AirQualitySensor::LOW_POLLUTION) {
        Serial.println("Low pollution!");
    } else if (quality == AirQualitySensor::FRESH_AIR) {
        Serial.println("Fresh air.");
    }

    delay(1000);
}

void distanceSensor(void) {
    if(digitalRead(10)==LOW){
      Serial.println("NOTHING DETECTED");
      delay(10);
    }
    else{
      Serial.println("OBJECT DETECTED");
      delay(10);
    }
}
