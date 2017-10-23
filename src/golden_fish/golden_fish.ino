//Hardware init if needed global and comments about task reserved hardware:
//A4 / A5 RTC via i2c
//A0 water lvl sensor
//P13 Feeder (MPP)
//P12 Pump
//P11 / P10 Valve
<<<<<<< HEAD
//P0 / P1 / P2 RTC
//P3
=======
// P9 LED
>>>>>>> master
  
//Libraries
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
#include <stdio.h>
#include <Wire.h>
#include "RTClib.h"

//Global variables
RTC_DS1307 RTC;
DateTime currentTime;

//Forward task functions declarations
void TaskSensorsRead(void *pvParameters);
void TaskFeed(void *pvParameters);
void TaskLWater(void *pvParameters);
void TaskLRTC(void *pvParameters);

//Forward general function declarations
void rtc_set_time();
void rtc_get_time();


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
//  rtc_get_time();
  //Tasks init:
  xTaskCreate(&TaskSensorsRead, (const portCHAR *)"SensorRead", 128, NULL, 1, NULL);
  xTaskCreate(&TaskFeed, (const portCHAR *)"Feed", 128, NULL, 3, NULL);
  xTaskCreate(&TaskWater, (const portCHAR *)"Water", 128, NULL, 3, NULL);
  xTaskCreate(&TaskRTC, (const portCHAR *)"RTC", 128, NULL, 1, NULL);
}

void loop()
{
// DO NOT ADD CODE HERE. Things are done ONYL in Tasks.
}

void TaskSensorsRead(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup

   for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);

    //@TODO one function per sensor to read
    //Introduce Delays in readings, so polling rate is not too high, preferably at the beginning of the for(;;)
    //Set results in gobal variables (as small as possible) so they can be used by other tasks
  }
}

void TaskFeed(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup

   for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);
    //@TODO checks flags set by user or time to feed the fish
  }
}

void TaskWater(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup

   for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);
    //@TODO Move motor to change water, check with sensors to start and stop it, if unsure full stop
  }
}

void TaskRTC(void *pvParameters)
{
  (void) pvParameters;
  for(;;)
  {
    rtc_get_time();
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Functions:

void rtc_get_time()
{
  currentTime = RTC.now();
}

