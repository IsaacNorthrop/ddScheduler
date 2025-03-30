/*
 * generator.c
 *
 *  Created on: Mar 27, 2025
 *      Author: liamtanner
 */

#include "../inc/testBench.h"
#include "FreeRTOSConfig.h"
#include "../inc/userDefined.h"
#include "../inc/linkedList.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/main.h"

extern xQueueHandle Generator_Queue;


void Gen1_Task (void *taskParamters){
	TaskHandle_t task1;
	xTaskCreate(User_Defined_Task, "User_Defined_Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1); // Create task with placeholder priority
	vTaskSuspend(task1);
	while (1){
		createDDTask(task1, 1, TASK_1_EXEC, TASK_1_PERIOD);
		vTaskDelay(TASK_1_PERIOD);
	}
}

void Gen2_Task (void *taskParameters){
	while (1){
		// Create initial FreeRTOS F-Task
		TaskHandle_t task;
		xTaskCreate(User_Defined_Task, "User_Defined_Task", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority
		//vTaskSuspend(task);

		// Call to our create dd task function happens here
		createDDTask(task, 2, TASK_2_EXEC, TASK_2_PERIOD);

		vTaskDelay(TASK_2_PERIOD);
	}
}

void Gen3_Task (void *taskParameters){
	while(1){
		// Create initial FreeRTOS F-Task
		TaskHandle_t task;
		xTaskCreate(User_Defined_Task, "User_Defined_Task", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority
		//vTaskSuspend(task);

		// Call to our create dd task function happens here
		createDDTask(task, 3, TASK_3_EXEC, TASK_3_PERIOD);

		vTaskDelay(TASK_3_PERIOD);
	}
}

void createDDTask (TaskHandle_t task, int id, int executionTime, int period){

	struct taskListNode* newTask = createNode(task, executionTime, period, id);

	if (newTask == NULL){
		printf("createDDTask: Unable to create task: %d\n", id);
	}

	// Send the task to the user-defined task queue
	if (!xQueueSend(Generator_Queue, &newTask, 1000)) {
		printf("createDDTask: Failed to send task %d to User_Defined_Queue\n", id);
		free(newTask);  // Only free if it never made it to the user-defined task
	}
}

