/**
 * @file generator.c
 * @author Isaac Northrop and Liam Tanner
 * @brief Task functions for each of the three generator tasks.
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../inc/generator.h"

/**
 * @brief Generates task 1 from test bench
 * 
 * @param taskParamters 
 */

void Gen1_Task (void *taskParamters){
	TaskHandle_t task1;
	xTaskCreate(User_Defined_Task, "User_Defined_Task1", configMINIMAL_STACK_SIZE, NULL, 1, &task1);
	vTaskSuspend(task1);
	while (1){
		createDDTask(task1, 1, TASK_1_EXEC, TASK_1_PERIOD);
		/* Delay for specified period. */
		vTaskDelay(pdMS_TO_TICKS(TASK_1_PERIOD));
	}
}

/**
 * @brief Generates task 2 from test bench.
 * 
 * @param taskParamters 
 */

void Gen2_Task (void *taskParamters){
	TaskHandle_t task2;
	xTaskCreate(User_Defined_Task, "User_Defined_Task2", configMINIMAL_STACK_SIZE, NULL, 1, &task2);
	vTaskSuspend(task2);
	while (1){
		createDDTask(task2, 2, TASK_2_EXEC, TASK_2_PERIOD);
		vTaskDelay(pdMS_TO_TICKS(TASK_2_PERIOD));
	}
}

/**
 * @brief Generates task 3 from test bench.
 * 
 * @param taskParamters 
 */

void Gen3_Task (void *taskParamters){
	TaskHandle_t task3;
	xTaskCreate(User_Defined_Task, "User_Defined_Task3", configMINIMAL_STACK_SIZE, NULL, 1, &task3);
	vTaskSuspend(task3);
	while (1){
		createDDTask(task3, 3, TASK_3_EXEC, TASK_3_PERIOD);
		vTaskDelay(pdMS_TO_TICKS(TASK_3_PERIOD));
	}
}

/**
 * @brief Generates taskListNode for generated task with appriopriate
 * parameters.
 * 
 * @param task 
 * @param id 
 * @param executionTime 
 * @param period 
 */

void createDDTask (TaskHandle_t task, int id, int executionTime, int period){

	/* Create node and assign release_time and deadline. */
	struct taskListNode* newTask = createNode(task, executionTime, period, id);
	newTask->release_time = pdTICKS_TO_MS(xTaskGetTickCount());
	newTask->deadline = newTask->release_time + newTask->period;

	if (newTask == NULL){
		printf("createDDTask: Unable to create task: %d\n", id);
	}

	/* Send the task to the generator task queue */
	if (!xQueueSend(Generator_Queue, &newTask, 1000)) {
		printf("createDDTask: Failed to send task %d to Generator Queue\n", id);
		free(newTask);
	}
}

