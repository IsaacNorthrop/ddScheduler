/**
 * @file linkedList.c
 * @author Isaac Northrop and Liam Tanner
 * @brief Definitions for linked list data structure.
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../inc/linkedList.h"

/**
 * @brief Create a Node object.
 * 
 * @param task 
 * @param execution_time 
 * @param period 
 * @param id 
 * @return struct taskListNode* 
 */

struct taskListNode* createNode(TaskHandle_t task, int execution_time, int period, int id) {
    struct taskListNode* newNode = (struct taskListNode*)malloc(sizeof(struct taskListNode));
    newNode->execution_time = execution_time;
    newNode->period = period;
    newNode->next = NULL;
    newNode->release_time = 0;
    newNode->task_id = id;
    newNode->task = task;
    return newNode;
}

/**
 * @brief Insert node at the front of a list.
 * 
 * @param head 
 * @param node 
 */

void insertAtFirst(struct taskListNode** head, struct taskListNode* node) {
    node->next = *head;
    *head = node;
}

/**
 * @brief Insert node at the end of a list.
 * 
 * @param head 
 * @param node 
 */

void insertAtEnd(struct taskListNode** head, struct taskListNode* node) {
	node->next = NULL;
    if (*head == NULL) {
        insertAtFirst(head, node);
        return;
    }
    struct taskListNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

/**
 * @brief Insert node at some specified position in a list.
 * 
 * @param head 
 * @param node 
 * @param position 
 */

void insertAtPosition(struct taskListNode** head, struct taskListNode* node, int position) {
    if (position == 0) {
        insertAtFirst(head, node);
        return;
    }
    struct taskListNode* temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }
    node->next = temp->next;
    temp->next = node;
}

/**
 * @brief Delete first item in a list.
 * 
 * @param head 
 */

void deleteFromFirst(struct taskListNode** head) {
    if (*head == NULL) {
        return;
    }
    struct taskListNode* temp = *head;
    *head = temp->next;
}

/**
 * @brief Delete last item in a list.
 * 
 * @param head 
 */

void deleteFromEnd(struct taskListNode** head) {
    if (*head == NULL) {
        return;
    }
    struct taskListNode* temp = *head;
    if (temp->next == NULL) {
        free(temp);
        *head = NULL;
        return;
    }
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

/**
 * @brief Delete item from some position in some list.
 * 
 * @param head 
 * @param position 
 */

void deleteAtPosition(struct taskListNode** head, int position) {
    if (*head == NULL) {
        return;
    }
    struct taskListNode* temp = *head;
    if (position == 0) {
        deleteFromFirst(head);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range\n");
        return;
    }
    struct taskListNode* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

/**
 * @brief Count the items in some list.
 * 
 * @param head 
 * @return int 
 */

int count(struct taskListNode* head){
	int count = 0;
    struct taskListNode* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
	return count;
}

/**
 * @brief Print the items in some list to the SVW Console.
 * 
 * @param head 
 */

void print(struct taskListNode* head) {
	if(head == NULL)
		return;
	struct taskListNode* temp = head;
    while (temp != NULL) {
        printf("Task %d: Completed Time: %d, Expected Time: %d", temp->task_id, temp->completion_time, temp->period+temp->release_time);
        temp = temp->next;
    }
    printf("\n");
}


