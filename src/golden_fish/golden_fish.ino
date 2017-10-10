#include <Arduino_FreeRTOS.h>

//Forward task functions declarations
void TaskDisplayAndButtons(void *pvParameters);
void TaskSensorsRead(void *pvParameters);
void TaskFeed(void *pvParameters);
void TaskLights(void *pvParameters);
void TaskLWater(void *pvParameters);


void setup()
{
  //Hardware init if needed global and comments about task reserved hardware:
  

  //Tasks init:
  xTaskCreate(TaskDisplayAndButtons, (const portCHAR *)"DisplayAndButtons", 128, NULL, 2, NULL);
  xTaskCreate(TaskSensorsRead, (const portCHAR *)"SensorRead", 128, NULL, 1, NULL);
  xTaskCreate(TaskFeed, (const portCHAR *)"Feed", 128, NULL, 3, NULL);
  xTaskCreate(TaskLights, (const portCHAR *)"Lights", 128, NULL, 1, NULL);
  xTaskCreate(TaskWater, (const portCHAR *)"Water", 128, NULL, 3, NULL);
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
    //@TODO read pin state (all buttons are on one pin) and implement DEBOUNCE
    //Find a way to check is message is correctly displayed
    //Implement a menu (via a state machine) with "screens" navigable, has a selectable luminosity and a 'feed now'
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

