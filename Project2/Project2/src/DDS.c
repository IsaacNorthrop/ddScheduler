#include "../inc/DDS.h"

void checkOverdue(struct taskListNode** active, struct taskListNode** overdue){
    if (*head == NULL)
        return;
    int position = 0;
    struct taskListNode* temp = *active;
    while (temp->next != NULL) {
    	int current_time = xTaskGetTickCount();
    	if(current_time > temp->deadline){
            insertAtEnd(overdue, &temp);
            deletefromPosition(active, position);
        }
    	position++;
        temp = temp->next;
    }
    return;
}
