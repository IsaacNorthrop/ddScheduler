/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wwrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*
FreeRTOS is a market leading RTOS from Real Time Engineers Ltd. that supports
31 architectures and receives 77500 downloads a year. It is professionally
developed, strictly quality controlled, robust, supported, and free to use in
commercial products without any requirement to expose your proprietary source
code.

This simple FreeRTOS demo does not make use of any IO ports, so will execute on
any Cortex-M3 of Cortex-M4 hardware.  Look for TODO markers in the code for
locations that may require tailoring to, for example, include a manufacturer
specific header file.

This is a starter project, so only a subset of the RTOS features are
demonstrated.  Ample source comments are provided, along with web links to
relevant pages on the http://www.FreeRTOS.org site.

Here is a description of the project's functionality:

The main() Function:
main() creates the tasks and software timers described in this section, before
starting the scheduler.

The Queue Send Task:
The queue send task is implemented by the prvQueueSendTask() function.
The task uses the FreeRTOS vTaskDelayUntil() and xQueueSend() API functions to
periodically send the number 100 on a queue.  The period is set to 200ms.  See
the comments in the function for more details.
http://www.freertos.org/vtaskdelayuntil.html
http://www.freertos.org/a00117.html

The Queue Receive Task:
The queue receive task is implemented by the prvQueueReceiveTask() function.
The task uses the FreeRTOS xQueueReceive() API function to receive values from
a queue.  The values received are those sent by the queue send task.  The queue
receive task increments the ulCountOfItemsReceivedOnQueue variable each time it
receives the value 100.  Therefore, as values are sent to the queue every 200ms,
the value of ulCountOfItemsReceivedOnQueue will increase by 5 every second.
http://www.freertos.org/a00118.html

An example software timer:
A software timer is created with an auto reloading period of 1000ms.  The
timer's callback function increments the ulCountOfTimerCallbackExecutions
variable each time it is called.  Therefore the value of
ulCountOfTimerCallbackExecutions will count seconds.
http://www.freertos.org/RTOS-software-timer.html

The FreeRTOS RTOS tick hook (or callback) function:
The tick hook function executes in the context of the FreeRTOS tick interrupt.
The function 'gives' a semaphore every 500th time it executes.  The semaphore
is used to synchronise with the event semaphore task, which is described next.

The event semaphore task:
The event semaphore task uses the FreeRTOS xSemaphoreTake() API function to
wait for the semaphore that is given by the RTOS tick hook function.  The task
increments the ulCountOfReceivedSemaphores variable each time the semaphore is
received.  As the semaphore is given every 500ms (assuming a tick frequency of
1KHz), the value of ulCountOfReceivedSemaphores will increase by 2 each second.

The idle hook (or callback) function:
The idle hook function queries the amount of free FreeRTOS heap space available.
See vApplicationIdleHook().

The malloc failed and stack overflow hook (or callback) functions:
These two hook functions are provided as examples, but do not contain any
functionality.
*/

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4_discovery.h"
/* Kernel includes. */
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
/* Local includes. */
#include "../inc/DDS.h"
#include "../inc/linkedList.h"
#include "../inc/DDS.h"



/*-----------------------------------------------------------*/
#define mainQUEUE_LENGTH 100

/*
 * TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware( void );

/*
 * The queue send and receive tasks as described in the comments at the top of
 * this file.
 */
static void DDS_Task( void *pvParameters );
static void Generator_Task( void *pvParameters );
static void User_Defined_Task( void *pvParameters );
static void Monitor_Task( void *pvParameters );

xQueueHandle Generator_Queue = 0;
xQueueHandle User_Defined_Queue = 0;
xQueueHandle Monitor_Queue = 0;

TaskHandle_t DDS;
TaskHandle_t Generator;
TaskHandle_t User_Defined;
TaskHandle_t Monitor;


/*-----------------------------------------------------------*/

int main(void)
{

	/* Configure the system ready to run the demo.  The clock configuration
	can be done here if it was not done before main() was called. */
	prvSetupHardware();


	/* Create the queue used by the queue send and queue receive tasks.
	http://www.freertos.org/a00116.html */

	// size of each item needs to be adjusted

	Generator_Queue = xQueueCreate( 	mainQUEUE_LENGTH,		/* The number of items the queue can hold. */
							sizeof( uint16_t ) );	/* The size of each item the queue holds. */

	User_Defined_Queue = xQueueCreate( 	mainQUEUE_LENGTH, sizeof( uint16_t ) );

	Monitor_Queue = xQueueCreate( 	mainQUEUE_LENGTH, sizeof( uint16_t ) );

	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry( Generator_Queue, "Generator_Queue" );
	vQueueAddToRegistry( User_Defined_Queue, "User_Defined_Queue" );
	vQueueAddToRegistry( Monitor_Queue, "Monitor_Queue" );

	xTaskCreate( DDS_Task, "DDS", configMINIMAL_STACK_SIZE, NULL, 2, &DDS);
	xTaskCreate( Generator_Task, "Generator", configMINIMAL_STACK_SIZE, NULL, 2, &Generator);
	xTaskCreate( User_Defined_Task, "User_Defined", configMINIMAL_STACK_SIZE, NULL, 2, &User_Defined);
	xTaskCreate( Monitor_Task, "Monitor", configMINIMAL_STACK_SIZE, NULL, 2, &Monitor);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	return 0;
}

/*-----------------------------------------------------------*/

static void DDS_Task( void *pvParameters )
{
	int start_time = xTaskGetTickCount();
	struct taskListNode* activeHead = NULL;
	struct taskListNode* completedHead = NULL;
	struct taskListNode* overdueHead = NULL;
	int current_hyper = start_time;

	struct taskListNode* temp_node;
	int temp_execution;
	int result;
	vTaskSuspend(Monitor);
	vTaskSuspend(User_Defined);

	while(1)
	{
		if(current_hyper + 1500 < xTaskGetTickCount()){
			current_hyper = xTaskGetTickCount();
			struct taskListNode*** lists = {&activeHead, &completedHead, &overdueHead};
			if(xQueueSend(Monitor_Queue, &lists, 1000)){
				vTaskResume(Monitor);
				vTaskSuspend(DDS);
			}
			vTaskSuspend(Monitor);
		}
		if( xQueueReceive(Generator_Queue,&temp_node,1000))
		{
			temp_node->release_time = xTaskGetTickCount();
			temp_node->deadline = release_time + temp_node->period;
			insertAtEnd(activeHead, temp_node);
		}
		else
		{
			printf("Manager Failed!\n");
		}
		if(activeHead){
			activeHead = MergeSort(&activeHead);
		}
		checkOverdue(&activeHead, &overdueHead);
		temp_node* = activeHead->next; // pointers may be wrong here
		deleteFromFirst(&activeHead);
		if(xQueueSend(User_Defined_Queue, &temp_node, 1000)){ // sending node to user defined task
			int temp = 0;
		}
		vTaskResume(User_Defined);
		vTaskSuspend(DDS_Task);
		if(xQueueReceive(User_Defined_Queue, &result, 1000)){
			if(result)
				insertAtEnd(completedHead, 0, 0);
			else
				insertAtEnd(overdueHead, 0, 0);
		}
		vTaskDelay(1000);
	}
}

static void Generator_Task( void *pvParameters )
{

	char*  tx_data = "fuck";

	while(1)
	{

		if( xQueueSend(Generator_Queue,&tx_data,1000))
		{
			printf("successfully sent\n");
			vTaskDelay(1000);
		}
	}
}

static void User_Defined_Task( void *pvParameters )
{
	return;
}

static void Monitor_Task( void *pvParameters )
{
	struct taskListNode*** lists = {NULL, NULL, NULL};
	while(1){
		vTaskSuspend(Monitor);
		if(xQueueReceive(Monitor_Queue, &lists, 1000)){
			for(int i = 0; i<3; i++)
				print(&lists[i]);
		}
		vTaskResume(DDS);
	}
	
	return;
}


/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* The malloc failed hook is enabled by setting
	configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

	Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software 
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  pxCurrentTCB can be
	inspected in the debugger if the task name passed into this function is
	corrupt. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
	FreeRTOSConfig.h.

	This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Ensure all priority bits are assigned as preemption priority bits.
	http://www.freertos.org/RTOS-Cortex-M3-M4.html */
	NVIC_SetPriorityGrouping( 0 );

	/* TODO: Setup the clocks, etc. here, if they were not configured before
	main() was called. */
}
