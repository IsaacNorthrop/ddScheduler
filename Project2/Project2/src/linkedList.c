#include "../inc/linkedList.h"

// Function to create a new node 
struct taskListNode* createNode(int execution_time, int period) {
    struct taskListNode* newNode = (struct taskListNode*)malloc(sizeof(struct taskListNode));
    newNode->execution_time = execution_time;
    newNode->period = period;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new element at the beginning of the singly linked list
void insertAtFirst(struct taskListNode** head, int execution_time, int period) {
    struct taskListNode* newNode = createNode(execution_time, period);
    newNode->next = *head;
    *head = newNode;
}

// Function to insert a new element at the end of the singly linked list
void insertAtEnd(struct taskListNode** head, int execution_time, int period) {
    struct taskListNode* newNode = createNode(execution_time, period);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct taskListNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to insert a new element at a specific position in the singly linked list
void insertAtPosition(struct taskListNode** head, int execution_time, int period, int position) {
    struct taskListNode* newNode = createNode(execution_time, period);
    if (position == 0) {
        insertAtFirst(head,execution_time,period);
        return;
    }
    struct taskListNode* temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of range\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
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
        printf("%d -> ", temp->deadline);
        temp = temp->next;
    }
    printf("NULL\n");
}
