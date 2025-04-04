/**
 * @file userDefined.h
 * @author Isaac Northrop and Liam Tanner
 * @brief Standard definitions for userDefined.c
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef USERDEFINED_H_
#define USERDEFINED_H_

#include "userDefined.h"
#include "linkedList.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "main.h"

void User_Defined_Task(void *pvParameters);

#endif /* USERDEFINED_H_ */
