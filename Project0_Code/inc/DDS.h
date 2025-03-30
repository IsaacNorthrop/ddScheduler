#ifndef DDS_H
#define DDS_H

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

extern uint32_t SystemCoreClock;

struct ListGroup {
	struct taskListNode* activeHead;
	struct taskListNode* completedHead;
	struct taskListNode* overdueHead;
};

void checkOverdue(struct taskListNode** active, struct taskListNode** overdue);

int msToTicks(int ms);

#endif
