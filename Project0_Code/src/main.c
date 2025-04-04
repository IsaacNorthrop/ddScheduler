/**
 * @file main.c
 * @author Isaac Northrop and Liam Tanner
 * @brief Main task function definitions and hardware hooks.
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../inc/main.h"

/*-----------------------------------------------------------*/

int main(void)
{

	prvSetupHardware();

	/* Create each queue to be used in the scheduler. */

	Generator_Queue = xQueueCreate(mainQUEUE_LENGTH, sizeof(struct taskListNode *));

	User_Defined_Queue = xQueueCreate(mainQUEUE_LENGTH, sizeof(struct taskListNode *));

	Monitor_Queue = xQueueCreate(mainQUEUE_LENGTH, sizeof(struct ListGroup));

	Result_Queue = xQueueCreate(mainQUEUE_LENGTH, sizeof(int));

	/* Add queues to the registry, for the benefit of kernel aware debugging. */

	vQueueAddToRegistry(Generator_Queue, "Generator_Queue");
	vQueueAddToRegistry(User_Defined_Queue, "User_Defined_Queue");
	vQueueAddToRegistry(Monitor_Queue, "Monitor_Queue");
	vQueueAddToRegistry(Result_Queue, "Result_Queue");

	/* Create tasks associated with their task handle. */

	xTaskCreate(DDS_Task, "DDS", configMINIMAL_STACK_SIZE, NULL, 2, &DDS);
	xTaskCreate(Gen1_Task, "Gen1", configMINIMAL_STACK_SIZE, NULL, 2, &Gen1);
	xTaskCreate(Gen2_Task, "Gen2", configMINIMAL_STACK_SIZE, NULL, 2, &Gen2);
	xTaskCreate(Gen3_Task, "Gen3", configMINIMAL_STACK_SIZE, NULL, 2, &Gen3);
	xTaskCreate(Monitor_Task, "Monitor", configMINIMAL_STACK_SIZE, NULL, 2, &Monitor);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	return 0;
}

/*-----------------------------------------------------------*/

/**
 * @brief Task function for DDS Task. Schedules and sorts tasks.
 *
 * @param pvParameters
 */

static void DDS_Task(void *pvParameters)
{
	int start_time = xTaskGetTickCount();
	struct taskListNode *activeHead = NULL;
	struct taskListNode *completedHead = NULL;
	struct taskListNode *overdueHead = NULL;
	monitorSemaphore = xSemaphoreCreateBinary();
	int result;

	while (1)
	{
		struct taskListNode *temp_node;
		int elapsed_time = xTaskGetTickCount() - start_time;
		if (elapsed_time >= pdMS_TO_TICKS(1500))
		{
			/* Reset start time for another hyper period. */
			start_time = xTaskGetTickCount();
			struct ListGroup lists;
			lists.activeHead = activeHead;
			lists.completedHead = completedHead;
			lists.overdueHead = overdueHead;
			/* Send lists to monitor. */
			if (xQueueSend(Monitor_Queue, &lists, 1000))
				xSemaphoreGive(monitorSemaphore);
		}
		/* Get all available queues from the generator. */
		while (xQueueReceive(Generator_Queue, &temp_node, 1) == pdTRUE)
		{
			temp_node->deadline = temp_node->release_time + temp_node->period;
			/* Add generated tasks to active lists. */
			insertAtEnd(&activeHead, temp_node);
		}
		/* Sort active tasks. */
		if (activeHead != NULL && activeHead->next != NULL)
		{
			activeHead = MergeSort(activeHead);
		}
		else if (activeHead == NULL)
		{
			continue;
		}
		if (activeHead != NULL)
		{
			/* Send highest priority task to user defined. */
			if (xQueueSend(User_Defined_Queue, &activeHead, 1000))
			{
				vTaskResume(activeHead->task);
				vTaskSuspend(DDS);
			}
			/* Check if task successfully executes. */
			if (xQueueReceive(Result_Queue, &result, 1000))
			{
				if (result)
				{
					struct taskListNode *temp = activeHead;
					activeHead = activeHead->next;
					temp->next = NULL;
					/* Check if task is overdue. */
					if (temp->completion_time <= temp->deadline)
					{
						insertAtFirst(&completedHead, temp);
					}
					else
					{
						insertAtFirst(&overdueHead, temp);
					}
				}
			}
		}
		result = 0;
	}
}

/**
 * @brief Task function for Monitor Task. Prints task summary lists.
 * 
 * @param pvParameters 
 */

static void Monitor_Task(void *pvParameters)
{
	struct ListGroup lists;
	while (1)
	{
		/* Wait for signal from DDS. */
		if (xSemaphoreTake(monitorSemaphore, portMAX_DELAY) == pdTRUE)
		{
			/* Print result lists. */
			if (xQueueReceive(Monitor_Queue, &lists, 1000))
			{
				printf("Active Tasks: %d\n", count(lists.activeHead));
				printf("Completed Tasks: %d\n", count(lists.completedHead));
				printf("Overdue Tasks: %d\n", count(lists.overdueHead));
			}
		}
	}

	return;
}

/*-----------------------------------------------------------*/

/**
 * @brief Hook that handles failing malloc.
 * 
 */

void vApplicationMallocFailedHook(void)
{
	/* The malloc failed hook is enabled by setting
	configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

	Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for (;;)
		;
}
/*-----------------------------------------------------------*/

/**
 * @brief Hook that handles stack overflow.
 * 
 * @param pxTask 
 * @param pcTaskName 
 */

void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
	(void)pcTaskName;
	(void)pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  pxCurrentTCB can be
	inspected in the debugger if the task name passed into this function is
	corrupt. */
	for (;;)
		;
}
/*-----------------------------------------------------------*/

/**
 * @brief Hook that handles task idle.
 * 
 */

void vApplicationIdleHook(void)
{
	volatile size_t xFreeStackSpace;

	/* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
	FreeRTOSConfig.h.

	This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if (xFreeStackSpace > 100)
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}
/*-----------------------------------------------------------*/

/**
 * @brief Hook that sets up STM hardware.
 * 
 */

static void prvSetupHardware(void)
{
	/* Ensure all priority bits are assigned as preemption priority bits.
	http://www.freertos.org/RTOS-Cortex-M3-M4.html */
	NVIC_SetPriorityGrouping(0);

	/* TODO: Setup the clocks, etc. here, if they were not configured before
	main() was called. */
}
