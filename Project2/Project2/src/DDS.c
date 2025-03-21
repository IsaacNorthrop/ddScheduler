#include "../inc/DDS.h"

void checkOverdue(struct taskListNode** active, struct taskListNode** overdue){
    if (*head == NULL)
        return;

    struct taskListNode* temp = *active;
    while (temp->next != NULL) {
    	int current_time = xTaskGetTickCount();
    	if(current_time > temp->deadline)
    		insertAtEnd(overdue, &temp);
        temp = temp->next;
    }
    return;
}
