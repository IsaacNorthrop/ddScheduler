/**
 * @file mergeSort.h
 * @author Isaac Northrop and Liam Tanner
 * @brief Standard definitions for a simple merge sort
 * algorithm.
 * @version 0.1
 * @date 2025-04-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include "linkedList.h"

struct taskListNode* split(struct taskListNode* head);

struct taskListNode* merge(struct taskListNode* first, struct taskListNode* second);

struct taskListNode* MergeSort(struct taskListNode* head);

#endif /* MERGESORT_H_ */
