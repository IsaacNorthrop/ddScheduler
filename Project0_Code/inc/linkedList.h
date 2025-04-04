/**
 * @file linkedList.h
 * @author Isaac Northrop and Liam Tanner
 * @brief Standard definitions and data structures to support 
 * the linked list data structure.
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief taskListNode data structure including all necessary
 * parameters.
 * 
 */

struct taskListNode {
    int execution_time;
    int period;
    int deadline;
    int release_time;
    int task_id;
    int completion_time;
    TaskHandle_t task; 
    struct taskListNode* next;
};

struct taskListNode* createNode(TaskHandle_t task, int execution_time, int period, int id);
void insertAtFirst(struct taskListNode** head, struct taskListNode* node);
void insertAtEnd(struct taskListNode** head, struct taskListNode* node);
void insertAtPosition(struct taskListNode** head, struct taskListNode* node, int position);
void deleteFromFirst(struct taskListNode** head);
void deleteFromEnd(struct taskListNode** head);
void deleteAtPosition(struct taskListNode** head, int position);
int count(struct taskListNode* head);
void print(struct taskListNode* head);

#endif

