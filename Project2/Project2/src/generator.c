#include "../inc/testBench.h"         // For TASK_1_EXEC, TASK_1_PERIOD, etc.
#include "../inc/FreeRTOSConfig.h"    // For configMINIMAL_STACK_SIZE (optional if already included in FreeRTOS.h)
#include "../inc/userDefined.h"       // For userTask1, userTask2, userTask3
#include "../inc/linkedList.h"        // For taskListNode and createNode
#include "FreeRTOS.h"                 // For FreeRTOS types like TickType_t
#include "task.h"                     // For xTaskCreate, vTaskSuspend, TaskHandle_t
#include "queue.h"                    // For xQueueSend and QueueHandle_t
#include <stdio.h>                    // For printf
#include <stdlib.h>                   // For malloc/free

void Gen1 (void *taskParamters){

	//Create initial FreeRTOS F-Task
	TaskHandle_t task;
	xTaskCreate(userTask1, "User_Task_1", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority

	if(task == NULL){
		printf("Error: Gen1 task is NULL\n");
		return;
	}

	vTaskSuspend(task);

	//Call to our create dd task function happens here
	createDDTask(task, 1, TASK_1_EXEC, TASK_1_PERIOD);

	vTaskDelay(TASK_1_PERIOD);
}

void Gen2 (void *taskParameters){

	//Create initial FreeRTOS F-Task
	TaskHandle_t task;
	xTaskCreate(userTask2, "User_Task_2", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority

	if(task == NULL){
		printf("Error: Gen2 task is NULL\n");
		return;
	}

	vTaskSuspend(task);

	//Call to our create dd task function happens here
	createDDTask(task, 2, TASK_2_EXEC, TASK_2_PERIOD);

	vTaskDelay(TASK_2_PERIOD);
}

void Gen3 (void *taskParameters){

	//Create initial FreeRTOS F-Task
	TaskHandle_t task;
	xTaskCreate(userTask3, "User_Task_3", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority

	if(task == NULL){
		printf("Error: Gen3 task is NULL\n");
		return;
	}

	vTaskSuspend(task);

	//Call to our create dd task function happens here
	createDDTask(task, 3, TASK_3_EXEC, TASK_3_PERIOD);


	vTaskDelay(TASK_3_PERIOD);
}

void createDDTask (TaskHandle_t task, int executionTime, int period, int id){

	struct taskListNode* newTask = createNode(task, executionTime, period, id);

	if (newTask == NULL){
		printf("createDDTask: Unable to create task: %d\n", id);
	}

	if (xQueueSend(Generator_Queue, &newTask, portMAX_DELAY) != pdPASS) {
		printf("createDDTask: Failed to send task %d to Generator_Queue\n", id);
		free(newTask);  // Only free if it never made it to the DDS
	}

}
