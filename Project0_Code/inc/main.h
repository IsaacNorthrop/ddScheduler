#ifndef MAIN_H_
#define MAIN_H_

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4_discovery.h"
/* Kernel includes. */
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
/* Local includes. */
#include "../inc/DDS.h"
#include "../inc/linkedList.h"
#include "../inc/DDS.h"
#include "../inc/mergeSort.h"
#include "../inc/generator.h"

#define mainQUEUE_LENGTH 100

static void prvSetupHardware( void );

static void DDS_Task( void *pvParameters );
static void Generator_Task( void *pvParameters );
static void Monitor_Task( void *pvParameters );

xQueueHandle Generator_Queue;
xQueueHandle User_Defined_Queue;
xQueueHandle Monitor_Queue;
xQueueHandle Result_Queue;

TaskHandle_t DDS;
TaskHandle_t Gen1;
TaskHandle_t Gen2;
TaskHandle_t Gen3;
TaskHandle_t Monitor;

int main(void);

static void DDS_Task( void *pvParameters );


static void Monitor_Task( void *pvParameters );

void vApplicationMallocFailedHook( void );

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName );
void vApplicationIdleHook( void );
static void prvSetupHardware( void );

#endif
