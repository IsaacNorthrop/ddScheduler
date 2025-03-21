#include ../inc/testBench.h
#include ../inc/FreeRTOSConfig.h
#include userDefined.h

void Gen1 (void *taskParamters){

	//Create initial FreeRTOS F-Task
	taskHandle_t task;
	xTaskCreate(userTask1, "User_Task_1", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority

	if(task == NULL){
		printf("Error: Gen1 task is NULL\n");
		return;
	}

	vTaskSuspend(task);

	//Call to our create dd task function happens here

	vTaskDelay(TASK_1_PERIOD);
}

void Gen2 (void *taskParameters){

	//Create initial FreeRTOS F-Task
	taskHandle_t task;
	xTaskCreate(userTask2, "User_Task_2", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority

	if(task == NULL){
		printf("Error: Gen2 task is NULL\n");
		return;
	}

	vTaskSuspend(task);

	//Call to our create dd task function happens here

	vTaskDelay(TASK_2_PERIOD);
}

void Gen3 (void *taskParameters){

	//Create initial FreeRTOS F-Task
	taskHandle_t task;
	xTaskCreate(userTask3, "User_Task_3", configMINIMAL_STACK_SIZE, NULL, 1, &task); // Create task with placeholder priority

	if(task == NULL){
		printf("Error: Gen3 task is NULL\n");
		return;
	}

	vTaskSuspend(task);

	//Call to our create dd task function happens here

	vTaskDelay(TASK_3_PERIOD);
}
