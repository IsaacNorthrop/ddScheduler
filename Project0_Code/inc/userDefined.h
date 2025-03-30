/*
 * userDefined.h
 *
 *  Created on: Mar 27, 2025
 *      Author: liamtanner
 */

#ifndef USERDEFINED_H_
#define USERDEFINED_H_

#include "FreeRTOS.h"
#include "task.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"

void User_Defined_Task(void *pvParameters);

#endif /* USERDEFINED_H_ */
