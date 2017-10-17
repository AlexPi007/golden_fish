//Hardware init if needed global and comments about task reserved hardware:
//LCD reserved pins: 4;5;6;7;8;9
//Button read pin: A0
//A1 water lvl sensor
//A2 / A3 FotoRez
//P13 Feeder (MPP)
//P12 Pump
//P11 / P10 Valve
//P0 / P1 / P2 RTC
// P3 LED
  
//Libraries
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>

//LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Defines:
#define b_Select 0
#define b_Left 1
#define b_Right 2
#define b_Up 3
#define b_Down 4
#define b_ERROR 5
#define TRUE 1
#define FALASE 0

//Forward task functions declarations
void TaskDisplayAndButtons(void *pvParameters);
void TaskSensorsRead(void *pvParameters);
void TaskFeed(void *pvParameters);
void TaskLights(void *pvParameters);
void TaskLWater(void *pvParameters);

//Forward general function declarations
int button_read();


void setup()
{
  //Tasks init:
  xTaskCreate(&TaskDisplayAndButtons, (const portCHAR *)"DisplayAndButtons", 128, NULL, 2, NULL);
  xTaskCreate(&TaskSensorsRead, (const portCHAR *)"SensorRead", 128, NULL, 1, NULL);
  xTaskCreate(&TaskFeed, (const portCHAR *)"Feed", 128, NULL, 3, NULL);
  xTaskCreate(&TaskLights, (const portCHAR *)"Lights", 128, NULL, 1, NULL);
  xTaskCreate(&TaskWater, (const portCHAR *)"Water", 128, NULL, 3, NULL);
}

void loop()
{
// DO NOT ADD CODE HERE. Things are done ONYL in Tasks.
}

void TaskDisplayAndButtons(void *pvParameters)
{
  (void) pvParameters;
  //@TODO Add initial task setup
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TaskDnB set.");
  uint16_t iterator = 0;
  
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


//Functions:
int button_read()
{
  /*On Arduino UNO can't implement an interrupt on A0 pin, therefore polling is required.*/
  
  volatile uint8_t readA0;
  readA0 = analogRead(0);
  vTaskDelay(5 / portTICK_PERIOD_MS);
  
  if (readA0 < 50)
  {
    return b_Right;  
  }
  if (readA0 < 195)
  {
    return b_Up; 
  }
  if (readA0 < 380)
  {
    return b_Down; 
  }
  if (readA0 < 555)
  {
    return b_Left; 
  }
  if (readA0 < 790)
  {
    return b_Select;   
  }
  //If none of the above is true, means an error has occured.
  return b_ERROR;
}
