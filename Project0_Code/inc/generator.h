/**
 * @file generator.h
 * @author Isaac Northrop and Liam Tanner
 * @brief Standard definitions for generator.c
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "testBench.h"
#include "FreeRTOSConfig.h"
#include "userDefined.h"
#include "FreeRTOSConfig.h"
#include "linkedList.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"

extern xQueueHandle Generator_Queue;

void Gen1_Task(void *taskParameters);
void Gen2_Task(void *taskParameters);
void Gen3_Task(void *taskParameters);

void createDDTask (TaskHandle_t task, int id, int executionTime, int period);

#endif /* GENERATOR_H_ */
