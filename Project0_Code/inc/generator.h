/*
 * generator.h
 *
 *  Created on: Mar 27, 2025
 *      Author: liamtanner
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "testBench.h"
#include "FreeRTOSConfig.h"
#include "userDefined.h"


void Gen1_Task(void *taskParameters);
void Gen2_Task(void *taskParameters);
void Gen3_Task(void *taskParameters);

void createDDTask (TaskHandle_t task, int id, int executionTime, int period);

#endif /* GENERATOR_H_ */
