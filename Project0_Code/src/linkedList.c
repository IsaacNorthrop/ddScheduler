#include "../inc/linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

// Function to create a new node
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

// Function to insert a new element at the beginning of the singly linked list
void insertAtFirst(struct taskListNode** head, struct taskListNode* node) {
    node->next = *head;
    *head = node;
}

// Function to insert a new element at the end of the singly linked list
void insertAtEnd(struct taskListNode** head, struct taskListNode* node) {
    if (*head == NULL) {
        *head = node;
        return;
    }
    struct taskListNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

// Function to insert a new element at a specific position in the singly linked list
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

// Function to delete the first node of the singly linked list
void deleteFromFirst(struct taskListNode** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct taskListNode* temp = *head;
    *head = temp->next;
    free(temp);
}

// Function to delete the last node of the singly linked list
void deleteFromEnd(struct taskListNode** head) {
    if (*head == NULL) {
        printf("List is empty\n");
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

// Function to delete a node at a specific position in the singly linked list
void deleteAtPosition(struct taskListNode** head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
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

// Function to print the LinkedList
void print(struct taskListNode* head) {
    struct taskListNode* temp = head;
    while (temp != NULL) {
        printf("Task ID: %d, Deadline %d\n", temp->task_id, temp->deadline);
        temp = temp->next;
    }
    printf("\n");
}

