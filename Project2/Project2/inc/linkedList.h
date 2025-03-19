#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

struct taskListNode {
    int data;
    struct taskListNode* next;
};

struct taskListNode* createNode(int data);
void insertAtFirst(struct taskListNode** head, int data);
void insertAtEnd(struct taskListNode** head, int data);
void insertAtPosition(struct taskListNode** head, int data, int position);
void deleteFromFirst(struct taskListNode** head);
void deleteFromEnd(struct taskListNode** head);
void deleteAtPosition(struct taskListNode** head, int position);
void print(struct taskListNode* head);

#endif
