/**
 * @file DDS.h
 * @author Isaac Northrop and Liam Tanner
 * @brief Standard definitions and structures to assist DDS.c
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DDS_H
#define DDS_H

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

struct ListGroup {
	struct taskListNode* activeHead;
	struct taskListNode* completedHead;
	struct taskListNode* overdueHead;
};

#endif
