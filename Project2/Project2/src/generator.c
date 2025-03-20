#include ../inc/testBench.h
#include ../inc/FreeRTOSConfig.h

void Gen1 (void *taskParamters){

	taskHandle_t task;
	xTaskCreate(userTask1, "User_Task_1", configMINIMAL_STACK_SIZE, NULL, )


	vTaskDelay(TASK_1_PERIOD);
}

void Gen2 (void *taskParameters){

}

void Gen3 (void *taskParameters){

}
