/*
 * mergeSort.h
 *
 *  Created on: Mar 27, 2025
 *      Author: liamtanner
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include "linkedList.h"

struct taskListNode* split(struct taskListNode* head);

struct taskListNode* merge(struct taskListNode* first, struct taskListNode* second);

struct taskListNode* MergeSort(struct taskListNode* head);

#endif /* MERGESORT_H_ */
