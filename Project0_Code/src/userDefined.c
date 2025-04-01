/*
 * userDefined.c
 *
 *  Created on: Mar 27, 2025
 *      Author: liamtanner
 */

#include "../inc/userDefined.h"
#include "../inc/linkedList.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "../inc/main.h"

extern xQueueHandle User_Defined_Queue;
extern xQueueHandle Result_Queue;
extern TaskHandle_t DDS;

void User_Defined_Task(void *pvParameters) {

	printf("WE ARE IN USER DEFINED TASK\n");
    struct taskListNode* currentTask;

    while (1) {
        // Wait for task pointer from DDS
        if ( xQueueReceive(User_Defined_Queue,&currentTask,1000)) {

            TickType_t start = xTaskGetTickCount();
            TickType_t duration = pdMS_TO_TICKS(currentTask->execution_time);

            while (xTaskGetTickCount() - start < duration);

            int result = 1; // 1 for success
            xQueueSend(Result_Queue, &result, portMAX_DELAY);
            vTaskResume(DDS);
            vTaskSuspend(currentTask->task);
        }
    }
}
