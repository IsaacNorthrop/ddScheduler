#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

struct taskListNode {
    int execution_time;
    int period;
    int deadline;
    int release_time;
    int task_id;
    TaskHandle_t task;  // Handle to the task
    struct taskListNode* next;  // Pointer to the next node
};

// Function to create a new node
struct taskListNode* createNode(TaskHandle_t task, int execution_time, int period, int id);

// Functions for inserting nodes at various positions
void insertAtFirst(struct taskListNode** head, struct taskListNode* node);
void insertAtEnd(struct taskListNode** head, struct taskListNode* node);
void insertAtPosition(struct taskListNode** head, struct taskListNode* node, int position);

// Functions for deleting nodes at various positions
void deleteFromFirst(struct taskListNode** head);
void deleteFromEnd(struct taskListNode** head);
void deleteAtPosition(struct taskListNode** head, int position);

// Function to print the linked list
void print(struct taskListNode* head);

#endif

