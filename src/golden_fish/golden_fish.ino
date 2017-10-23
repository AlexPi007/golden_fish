//Hardware init if needed global and comments about task reserved hardware:
//A4 / A5 RTC via i2c
//A0 water lvl sensor
//P13 Feeder (MPP)
//P12 Pump
//P11 / P10 Valve
// P9 LED
  
//Libraries
#include <Arduino_FreeRTOS.h>
#include <event_groups.h>
//#include <event_groups.c>
#include <FreeRTOSConfig.h>
#include <stdio.h>
#include <Wire.h>
#include "RTClib.h"

//Global variables
RTC_DS1307 RTC;
DateTime currentTime;
  
EventGroupHandle_t rtc_event_group;
int LIGHT = (1 << 0);
int FEED = (1 << 1);
int DRAIN = (1 << 2);
int SENSOR = (1 << 3);

//Forward task functions declarations
void TaskSensorsRead(void *pvParameters);
void TaskFeed(void *pvParameters);
void TaskLWater(void *pvParameters);
void TaskLRTC(void *pvParameters);

//Forward general function declarations
void rtc_get_time();


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  if (!RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  rtc_event_group = xEventGroupCreate();
  //portMAX_DELAY makes a mutex wait forever
  if( rtc_event_group == NULL )
  {
      /* The event group was not created because there was insufficient
      FreeRTOS heap available. */
      Serial.println("Problem");
  }

  
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
    xEventGroupWaitBits(rtc_event_group, FEED, pdTRUE, pdTRUE, portMAX_DELAY);
    Serial.println("FEED");
    vTaskDelay(3000 / portTICK_PERIOD_MS);
//    xEventGroupClearBits(rtc_event_group, FEED);
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
  uint8_t lastMinute = 100; //Sets up an impossible value so at first run it will run correctly
  
  for(;;)
  {
    rtc_get_time();

    if(currentTime.minute() != lastMinute)
    {
      if(lastMinute != 100)
      {
        xEventGroupSetBits(rtc_event_group, FEED);
      }
      lastMinute = currentTime.minute(); 
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

//Functions:

void rtc_get_time()
{
  //Update time inside the global variable currentTime
  currentTime = RTC.now();
}

