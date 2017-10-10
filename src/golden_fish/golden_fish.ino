#include <Arduino_FreeRTOS.h>

//Forward task functions declarations
void TaskDisplayAndButtons(void *pvParameters);
void TaskSensorsRead(void *pvParameters);
void TaskMotor(void *pvParameters);
void TaskLights(void *pvParameters);


void setup()
{
  //Hardware init:
  

  //Tasks init:
  xTaskCreate(TaskDisplayAndButtons, (const portCHAR *)"DisplayAndButtons", 128, NULL, 3, NULL);
  xTaskCreate(TaskSensorsRead, (const portCHAR *)"SensorRead", 128, NULL, 1, NULL);
  xTaskCreate(TaskMotor, (const portCHAR *)"Motor", 128, NULL, 3, NULL);
  xTaskCreate(TaskLights, (const portCHAR *)"Lights", 128, NULL, 1, NULL);
}

void loop()
{
// DO NOT ADD CODE HERE. Things are done ONYL in Tasks.
}

void TaskDisplayAndButtons(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup
  
  for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void TaskSensorsRead(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup

   for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void TaskMotor(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup

   for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void TaskLights(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup

   for (;;)
  {
    //@TODO Add continous functionality
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

