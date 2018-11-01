#include "WiFi.h"
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  1800       /* 1800 = 30 mins Time ESP32 will go to sleep (in seconds) */
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

RTC_DATA_ATTR int bootCount = 0;

int TargetBoots = 48; // 2= 1h  48 = 24h

void setup() {
  WiFi.disconnect(true); 
  delay(100); 
  // disable WIFI altogether for power saving
  WiFi.mode(WIFI_OFF); 
  delay(100);
  btStop();  //turn off bluetooth for power saving

  Serial.begin(115200);
  delay(10);
  myservo.attach(33);
  myservo.detach();


  if (bootCount == 0) //Run this only the first time
  {

    Serial.println("Boot Count = ");
    Serial.print(bootCount);
    Serial.println();
    Serial.println();
    //prime feeder
    myservo.attach(33);
    myservo.write(0);
    delay(5000);
    //servo runs for 5s to prime feeder then is stopped
    myservo.detach();
    bootCount = bootCount + 1;
    delay(500);

  } else   {

    if (bootCount >= TargetBoots) {
      Serial.println("Boot Count = ");
      Serial.print(bootCount);
      Serial.println();
      Serial.println("Feeding Fish");

      myservo.attach(33);
      myservo.write(0);
      delay(3000);  //run the servo for 3s to deliver daily feed - customise to your needs
      myservo.detach();

      delay(1000);
      bootCount = 1;

    } else {

      Serial.println("Boot Count = ");
      Serial.print(bootCount);
      Serial.println();
      bootCount = bootCount + 1;
      delay(500);
    }

  }

  delay(1000);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() {
}

