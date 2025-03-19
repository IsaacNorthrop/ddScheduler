#include "mergeSort.h"
#include "linkedList.h"

// Function to split the singly linked list into two halves
struct taskListNode* split(struct taskListNode* head) {
    struct taskListNode* fast = head;
    struct taskListNode* slow = head;

    // Move fast pointer two steps and slow pointer
    // one step until fast reaches the end
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL) {
            slow = slow->next;
        }
    }

    // Split the list into two halves
    struct taskListNode* temp = slow->next;
    slow->next = NULL;
    return temp;
}

// Function to merge two sorted singly linked lists
struct taskListNode* merge(struct taskListNode* first, struct taskListnode* second) {
  
    // If either list is empty, return the other list
    if (first == NULL) return second;
    if (second == NULL) return first;

    // Pick the smaller value between first and second nodes
    if (first->data < second->data) {
        // Recursively merge the rest of the lists and
        // link the result to the current node
        first->next = merge(first->next, second);
        return first;
    }
    else {
        // Recursively merge the rest of the lists
        // and link the result to the current node
        second->next = merge(first, second->next);
        return second;
    }
}

// Function to perform merge sort on a singly linked list
struct taskListNode* MergeSort(struct taskListNode* head) {
  
    // Base case: if the list is empty or has only one node, 
    // it's already sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves
    struct taskLisNode* second = split(head);

    // Recursively sort each half
    head = MergeSort(head);
    second = MergeSort(second);

    // Merge the two sorted halves
    return merge(head, second);
}

void printList(struct taskListNode* head) {
    struct taskListNode* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Function to create a new node
struct taskListNode* createNode(int x) {
    struct taskListNode* newNode = 
      (struct taskListNode*)malloc(sizeof(struct taskListNode));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}
