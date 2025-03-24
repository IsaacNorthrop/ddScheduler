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
	createDDTask(task, 1, xTaskGetTickCount() + TASK_1_PERIOD);

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
	createDDTask(task, 2, TaskGetTickCount() + TASK_2_ERIOD);

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
	createDDTask(task, 3, xTaskGetTickCount() + TASK_3_PERIOD);


	vTaskDelay(TASK_3_PERIOD);
}

void createDDTask (){



}
