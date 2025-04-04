/**
 * @file userDefined.c
 * @author Isaac Northrop and Liam Tanner
 * @brief Handles execution time of current task.
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../inc/userDefined.h"

extern xQueueHandle User_Defined_Queue;
extern xQueueHandle Result_Queue;
extern TaskHandle_t DDS;

/**
 * @brief Simulate execution time of each DD-Task.
 * 
 * @param pvParameters 
 */

void User_Defined_Task(void *pvParameters) {

    struct taskListNode* currentTask;
    int result;

    while (1) {
        /* Wait for task pointer from DDS. */
    	result = 0;
        if ( xQueueReceive(User_Defined_Queue,&currentTask,1000)) {

            TickType_t start = xTaskGetTickCount();
            TickType_t duration = pdMS_TO_TICKS(currentTask->execution_time);

            vTaskDelayUntil(&start, duration);

            result = 1;
            xQueueSend(Result_Queue, &result, portMAX_DELAY);
            currentTask->completion_time = pdMS_TO_TICKS(xTaskGetTickCount());
            vTaskResume(DDS);
            vTaskSuspend(currentTask->task);
        }
    }
}
