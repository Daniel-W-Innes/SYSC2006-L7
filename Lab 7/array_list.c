/* SYSC 2006 Winter 2018 Lab 6
 *
 * array_list.c 
 *
 * Prototype of a dynamically allocated, fixed-capacity list that supports a 
 * subset of the operations provided by Python's list class.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array_list.h"

/* Construct a new, empty list, and return a pointer to it
 * Parameter capacity is the # of elements that can be stored in the list.
 * Terminate the program via assert if capacity is <= 0.
 * Terminate the program via assert if memory for the list cannot be 
 * allocated from the heap.
 */
intlist_t *intlist_construct(int capacity) {
	// Note - this is an incomplete function definition.
	// You must modify the function so that it correctly implements all
	// of the requirements listed in the header comment.
	assert(capacity > 0);
	intlist_t *list = malloc(sizeof(intlist_t));
	assert(list != NULL);
	list->capacity = capacity;
	list->size = 0;
	list->elems = malloc(sizeof(int) * capacity);
	assert(list->elems != NULL);
	return list;
}

/* Destroy the list pointed to by parameter list, deallocating all memory 
 * that was allocated from the heap.
 * Terminate the program via assert if list is NULL.
 */
void intlist_destroy(intlist_t *list) {
	assert(list != NULL);
	free(list->elems); /* Return the array to the heap. */
	free(list); /* Return the structure to the heap. */
}

/* Print the list pointed to by parameter list to the console.
 * Terminate the program via assert if list is NULL.
 */
void intlist_print(const intlist_t *list) {
	assert(list != NULL);
	if (list->size - 1 >= 0) {
		printf("[%d", list->elems[0]);
	} else {
		printf("[");
	}
	for (int i = 1; i <= list->size - 1; i++)
		printf(" %d", list->elems[i]);
	printf("]");
}

/* Insert element at the end of the list pointed to by parameter
* list, and return true.
* If the list is full, double the list's capacity before inserting
* the element.
* Terminate the program via assert if list is NULL.
*/
_Bool intlist_append(intlist_t *list, int element) {
	assert(list != NULL);
	if (list->size >= list->capacity)
		increase_capacity(list, 2 * list->capacity);
	list->elems[list->size] = element;
	list->size++;
	return true;
}

/* Return the maximum number of integers that can be stored in the list 
 * pointed to by parameter list.
 * Terminate the program via assert if list is NULL.
 */
int intlist_capacity(const intlist_t *list) {
	assert(list != NULL);
	return list->capacity;
}

/* Return the number of integers in the list pointed to by parameter list.
 * Terminate the program via assert if list is NULL.
 */
int intlist_size(const intlist_t *list) {
	assert(list != NULL);
	return list->size;
}

/* Return the element located at the specified index, in the list
 * pointed to by parameter list. 
 * Terminate the program via assert if list is NULL, 
 * or if index is not in the range 0 .. intlist_size() - 1.
 */
int intlist_get(const intlist_t *list, int index) {
	assert(list != NULL);
	return list->elems[index];
}

/* Store element at the specified index, in the list pointed to by 
 * parameter list. Return the integer that was previously 
 * stored at that index.
 * Terminate the program via assert if list is NULL, 
 * or if index is not in the range 0 .. intlist_size() - 1.
 */
int intlist_set(intlist_t *list, int index, int element) {
	assert(list != NULL);
	assert(index >= 0 && index <= intlist_size(list) - 1);
	int last = list->elems[index];
	list->elems[index] = element;
	return last;
}

/* Empty the list pointed to by parameter list.
 * Memory allocated to the list is not freed, so the emptied list can 
 * continue to be used.
 * Terminate the program via assert if list is NULL.
 */
void intlist_removeall(intlist_t *list) {
	list->size = 0;
	for (int i = 0; i < list->size - 1; i++)
		list->elems[i] = 0;
}

/* SYSC 2006 Winter 2018 Lab 7
 *
 * additional_functions.c
 */

/* Return the index (position) of the first occurrence of an integer
 * equal to target in the list pointed to by parameter list.
 * Return -1 if target is not in the list.
 * Terminate the program via assert if list is NULL.
 */
int intlist_index(const intlist_t *list, int target) {
	assert(list != NULL);
	for (int i = 0; i < list->size; i++)
		if (list->elems[i] == target)
			return i;
	return -1;
}

/* Count the number of integers that are equal to target, in the list
 * pointed to by parameter list, and return that number.
 * Terminate the program via assert if list is NULL.
 */
int intlist_count(const intlist_t *list, int target) {
	assert(list != NULL);
	int count = 0;
	for (int i = 0; i < list->size; i++)
		if (list->elems[i] == target)
			count++;
	return count;
}

/* Determine if an integer in the list pointed to by parameter list
 * is equal to target.
 * Return true if target is in the list, otherwise return false.
 * Terminate the program via assert if list is NULL.
 */
_Bool intlist_contains(const intlist_t *list, int target) {
	assert(list != NULL);
	if (intlist_index(list, target) != -1)
		return true;
	return false;
}

/* Increase the capacity of the list pointed to by parameter list to
 * the specified new capacity.
 * Terminate the program via assert if new_capacity is not greater than the
 * list's current capacity, or if the memory required to increase the
 * list's capacity cannot be allocated.
 */
void increase_capacity(intlist_t *list, int new_capacity) {
	assert(list != NULL);
	assert(new_capacity > list->capacity);
	int *newArray = malloc(new_capacity * sizeof(int));
	assert(newArray != NULL);
	for (int i = 0; i < list->size; i++)
		newArray[i] = list->elems[i];
	free(list->elems);
	list->elems = newArray;
	list->capacity = new_capacity;
}

/* Delete the integer at the specified position in the list pointed
 * to by parameter list.
 * Parameter index is the position of the integer that should be removed.
 * Terminate the program via assert if list is NULL, or if index
 * is not in the range 0 .. intlist_size() - 1.
 */
void intlist_delete(intlist_t *list, int index) {
	assert(list != NULL && index >= 0 && index <= list->size - 1);
	list->size = list->size - 1;
	for (int i = index; i < list->size; i++)
		list->elems[i] = list->elems[i + 1];
	list->elems[list->size] = 0;
}