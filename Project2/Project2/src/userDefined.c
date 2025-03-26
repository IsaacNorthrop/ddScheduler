#include "../inc/userDefined.h"
#include "../inc/linkedList.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

extern QueueHandle_t User_Defined_Queue;
extern QueueHandle_t DDS_Queue;  // If needed to send result back

void User_Defined_Task(void *pvParameters) {
    struct taskListNode* currentTask;

    while (1) {
        // Wait for task pointer from DDS
        if (xQueueReceive(User_Defined_Queue, &currentTask, portMAX_DELAY) == pdPASS) {
            printf("User Defined Task: Executing task %d\n", currentTask->task_id);

            TickType_t start = xTaskGetTickCount();
            TickType_t now;
            TickType_t duration = currentTask->execution_time / portTICK_PERIOD_MS;

            while ((now = xTaskGetTickCount()) - start < duration) {
                // Simulate execution
            }

            // Optionally send a result back to DDS (e.g., success or overdue)
            int result = 1; // 1 for success
            xQueueSend(DDS_Queue, &result, portMAX_DELAY);

            printf("User Defined Task: Completed task %d\n", currentTask->task_id);
        }
    }
}