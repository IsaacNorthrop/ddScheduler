#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

struct taskListNode {
    int execution_time;
    int period;
    int deadline;
    int release_time;
    struct taskListNode* next;
};

struct taskListNode* createNode(int execution_time, int period);
void insertAtFirst(struct taskListNode** head, struct taskListNode* node);
void insertAtEnd(struct taskListNode** head, struct taskListNode* node);
void insertAtPosition(struct taskListNode** head, struct taskListNode* node, int position);
void deleteFromFirst(struct taskListNode** head);
void deleteFromEnd(struct taskListNode** head);
void deleteAtPosition(struct taskListNode** head, int position);
void print(struct taskListNode* head);

#endif
