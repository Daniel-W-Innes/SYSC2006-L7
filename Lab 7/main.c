/* main.c - SYSC 2006 Winter 2018 Lab 7 Test Harness 
 *
 * Do not modify any code in this file.
 *
 * Tests last revised March 3, 2018.
 */

#include <stdlib.h> // exit, malloc, free
#include <stdio.h> // printf
#include "sput.h"

#include "array_list.h"

/* By default, Pelles C generates "warning #2154: Unreachable code"
 and "warning #2130: Result of comparison is constant" when the
 macros in sput.h are used. The following pragma directive disables the
 generation of these warnings.
 */
#pragma warn(disable: 2130 2154)

static _Bool compare_arrays(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i = i + 1) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

static void _print_bool(_Bool b) {
    if (b)
        printf("true");
    else
        printf("false");
}

static void _print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);

        /* Print a space after all but the last element. */
        if (i < n - 1) {
            printf(" ");
        } else {
            printf("]");
        }
    }
}

static void test_intlist_construct(void) {
    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    sput_fail_unless(list->capacity == 10, "Checking list->capacity");
    printf("Expected: 10, actual: %d\n", list->capacity);
    sput_fail_unless(list->size == 0, "Checking list->size");
    printf("Expected: 0, actual: %d\n", list->size);
    sput_fail_unless(list->elems != NULL, "Checking list->elems");
    printf("Expected: a non-NULL pointer, actual: %p\n", list->elems);

    intlist_destroy(list);
}

static void test_intlist_print(void) {
    intlist_t *list = intlist_construct(4);

    /* Print [] */

    // list->size = 0;

    /* We can't assume that intlist_print is working, so we can't call it
    * to display the expected output!
    */
    printf("Constructing an empty list, calling intlist_print()\n");
    printf("Expected output: []\n");
    printf("Actual output: ");
    intlist_print(list);
    printf("\n\n");

    /* Print [1] */

    /* We can't assume intlist_append is working, so we have to initialize
    * the list ourselves.
    */
    list->elems[0] = 1;
    list->size = 1;

    printf("Initializing list to [1], calling calling intlist_print()\n");
    printf("Expected output: [1]\n");
    printf("Actual output: ");
    intlist_print(list);
    printf("\n\n");

    /* Print [1, 5, -3, 9] */

    list->elems[0] = 1;
    list->elems[1] = 5;
    list->elems[2] = -3;
    list->elems[3] = 9;
    list->size = 4;

    printf("Initializing list to [1 5 -3 9], calling calling intlist_print()\n");
    printf("Expected output: [1 5 -3 9]\n");
    printf("Actual output: ");
    intlist_print(list);
    printf("\n");

    intlist_destroy(list);
}

static void test_intlist_append(void) {
    _Bool appended;
    int expected[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    appended = intlist_append(list, 1);
    sput_fail_unless(appended == true,
                     "appended = intlist_append(list, 1); checking appended");
    printf("Expected: true, actual: ");
    _print_bool(appended);
    printf("\n");

    sput_fail_unless(list->capacity == 10, "Checking list->capacity");
    printf("Expected: 10, actual: %d\n", list->capacity);
    sput_fail_unless(list->size == 1, "Checking list->size");
    printf("Expected: 1, actual: %d\n", list->size);
    sput_fail_unless(compare_arrays(list->elems, expected, 1),
                     "Checking backing array");
    printf("Expected: [1], actual: ");
    _print_array(list->elems, 1);
    printf("\n\n");

    appended = intlist_append(list, 3);
    sput_fail_unless(appended == true,
                     "appended = intlist_append(list, 3); checking appended");
    printf("Expected: true, actual: ");
    _print_bool(appended);
    printf("\n");

    sput_fail_unless(list->capacity == 10, "Checking list->capacity");
    printf("Expected: 10, actual: %d\n", list->capacity);
    sput_fail_unless(list->size == 2, "Checking list->size");
    printf("Expected: 2, actual: %d\n", list->size);
    sput_fail_unless(compare_arrays(list->elems, expected, 2),
                     "Checking backing array");
    printf("Expected: [1 3], actual: ");
    _print_array(list->elems, 2);
    printf("\n\n");

    intlist_destroy(list);

    printf("Creating an empty list: list = intlist_construct(10);\n");
    list = intlist_construct(10);
    printf("Initializing list to [1 3 5 7 9 11 13 15 17]\n");
    for (int i = 0; i < 9; i++) {
        appended = intlist_append(list, 2 * i + 1);
    }

    /* The list should now be [1, 3, 5, ..., 17], size == 9, capacity == 10 */

    appended = intlist_append(list, 19);
    sput_fail_unless(appended == true,
                     "appended = intlist_append(list, 19); checking appended");
    printf("Expected: true, actual: ");
    _print_bool(appended);
    printf("\n");

    sput_fail_unless(list->capacity == 10, "Checking list->capacity");
    printf("Expected: 10, actual: %d\n", list->capacity);
    sput_fail_unless(list->size == 10, "Checking list->size");
    printf("Expected: 10, actual: %d\n", list->size);
    sput_fail_unless(compare_arrays(list->elems, expected, 10),
                     "Checking backing array");
    printf("Expected: [1 3 5 7 9 11 13 15 17 19], actual: ");
    _print_array(list->elems, 10);
    printf("\n\n");

#ifdef notdef
    /* These tests assume that intlist_append doesn't increase
    * the capacity of a full list. Don't run these tests.
    */

    /* Now attempt to append an integer to a full list.*/

    appended = intlist_append(list, 21);
    sput_fail_unless(appended == false,
    "list is full, appended = intlist_append(list, 21); checking appended");
    printf("Expected: false, actual: ");
    _print_bool(appended);
    printf("\n");

    sput_fail_unless(list->capacity == 10, "Checking list->capacity");
    printf("Expected: 10, actual: %d\n", list->capacity);
    sput_fail_unless(list->size == 10, "Checking list->size");
    printf("Expected: 10, actual: %d\n", list->size);
    sput_fail_unless(compare_arrays(list->elems, expected, 10),
    "Checking backing array");
    printf("Expected: [1 3 5 7 9 11 13 15 17 19], actual: ");
    _print_array(list->elems, 10);
    printf("\n\n");
#endif

    intlist_destroy(list);
}

static void test_intlist_capacity(void) {
    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n\n", intlist_capacity(list));


    /* Initialize list to [0, 2, 4, 6, 8] */
    printf("Initializing list to [0 2 4 6 8]\n");

    for (int i = 0; i < 5; i++) {
        intlist_append(list, 2 * i);
    }

    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));

    intlist_destroy(list);
}

static void test_intlist_size(void) {
    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    sput_fail_unless(intlist_size(list) == 0, "intlist_size(list)");
    printf("Expected: 0, actual: %d\n\n", intlist_size(list));

    /* Initialize list to [0, 2, 4, 6, 8] */
    printf("Initializing list to [0 2 4 6 8]\n");

    for (int i = 0; i < 5; i++) {
        intlist_append(list, 2 * i);
    }

    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));

    intlist_destroy(list);
}

static void test_intlist_get(void) {
    int expected[] = {0, 2, 4, 6, 8};

    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    /* Initialize list to [0, 2, 4, 6, 8] */
    printf("Initializing list to [0 2 4 6 8]\n");

    for (int i = 0; i < 5; i++) {
        intlist_append(list, 2 * i);
    }

    /* In addition to verifying that get returns the expected value,
    we also verify that it doesn't modify the list's size,
    capacity or backing array.
    */

    sput_fail_unless(intlist_get(list, 0) == 0, "intlist_get(list, 0)");
    printf("Expected: 0, actual: %d\n", intlist_get(list, 0));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected, 5),
                     "Checking backing array");
    printf("Expected: [0 2 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    sput_fail_unless(intlist_get(list, 1) == 2, "intlist_get(list, 1)");
    printf("Expected: 2, actual: %d\n", intlist_get(list, 1));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected, 5),
                     "Checking backing array");
    printf("Expected: [0 2 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    sput_fail_unless(intlist_get(list, 2) == 4, "intlist_get(list, 2)");
    printf("Expected: 4, actual: %d\n", intlist_get(list, 2));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected, 5),
                     "Checking backing array");
    printf("Expected: [0 2 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    sput_fail_unless(intlist_get(list, 3) == 6, "intlist_get(list, 3)");
    printf("Expected: 6, actual: %d\n", intlist_get(list, 3));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected, 5),
                     "Checking backing array");
    printf("Expected: [0 2 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    sput_fail_unless(intlist_get(list, 4) == 8, "intlist_get(list, 4)");
    printf("Expected: 8, actual: %d\n", intlist_get(list, 4));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected, 5),
                     "Checking backing array");
    printf("Expected: [0 2 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n");

    intlist_destroy(list);
}

static void test_intlist_set(void) {
    int expected1[] = {1, 2, 4, 6, 8};
    int expected2[] = {1, 3, 4, 6, 8};
    int expected3[] = {1, 3, 5, 6, 8};
    int expected4[] = {1, 3, 5, 7, 8};
    int expected5[] = {1, 3, 5, 7, 9};

    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    /* Initialize list to [0, 2, 4, 6, 8] */
    printf("Initializing list to [0 2 4 6 8]\n");

    for (int i = 0; i < 5; i++) {
        intlist_append(list, 2 * i);
    }

    /* In addition to verifying that set returns the expected value,
    we also verify that it modifies only the specified location in
    the backing array, and doesn't modify the list's size or capacity.
    */

    int previous;

    previous = intlist_set(list, 0, 1);
    sput_fail_unless(previous == 0, "previous = intlist_set(list, 0, 1); checking previous");
    printf("Expected: 0, actual: %d\n", previous);
// sput_fail_unless(intlist_get(list, 0) == 1, "intlist_get(list, 0)");
// printf("Expected: 1, actual: %d\n", intlist_get(list, 0));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected1, 5),
                     "Checking backing array");
    printf("Expected: [1 2 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    previous = intlist_set(list, 1, 3);
    sput_fail_unless(previous == 2, "previous = intlist_set(list, 1, 3); checking previous");
    printf("Expected: 2, actual: %d\n", previous);
// sput_fail_unless(intlist_get(list, 1) == 3, "intlist_get(list, 1)");
// printf("Expected: 3, actual: %d\n", intlist_get(list, 1));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected2, 5),
                     "Checking backing array");
    printf("Expected: [1 3 4 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    previous = intlist_set(list, 2, 5);
    sput_fail_unless(previous == 4, "previous = intlist_set(list, 2, 5); checking previous");
    printf("Expected: 4, actual: %d\n", previous);
// sput_fail_unless(intlist_get(list, 2) == 5, "intlist_get(list, 2)");
// printf("Expected: 5, actual: %d\n", intlist_get(list, 2));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected3, 5),
                     "Checking backing array");
    printf("Expected: [1 3 5 6 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    previous = intlist_set(list, 3, 7);
    sput_fail_unless(previous == 6, "previous = intlist_set(list, 3, 7); checking previous");
    printf("Expected: 6, actual: %d\n", previous);
// sput_fail_unless(intlist_get(list, 3) == 7, "intlist_get(list, 3)");
// printf("Expected: 7, actual: %d\n", intlist_get(list, 3));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected4, 5),
                     "Checking backing array");
    printf("Expected: [1 3 5 7 8], actual: ");
    _print_array(list->elems, 5);
    printf("\n\n");

    previous = intlist_set(list, 4, 9);
    sput_fail_unless(previous == 8, "previous = intlist_set(list, 4, 9); checking previous");
    printf("Expected: 8, actual: %d\n", previous);
// sput_fail_unless(intlist_get(list, 4) == 9, "intlist_get(list, 4)");
// printf("Expected: 9, actual: %d\n", intlist_get(list, 4));
    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));
    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));
    sput_fail_unless(compare_arrays(list->elems, expected5, 5),
                     "Checking backing array");
    printf("Expected: [1 3 5 7 9], actual: ");
    _print_array(list->elems, 5);
    printf("\n");

    intlist_destroy(list);
}

static void test_intlist_removeall(void) {
    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);


    /* Initialize list to [0 2 4 6 8] */
    printf("Initializing list to [0 2 4 6 8]\n");

    for (int i = 0; i < 5; i++) {
        intlist_append(list, 2 * i);
    }

    printf("Calling intlist_removeall(list);\n");
    intlist_removeall(list);

    sput_fail_unless(intlist_size(list) == 0, "intlist_size(list)");
    printf("Expected: 0, actual: %d\n", intlist_size(list));

    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));

    sput_fail_unless(list->elems != NULL, "Checking list->elems");
    printf("Expected: a non-NULL pointer, actual: %p\n", list->elems);

    intlist_destroy(list);
}

/*****************************************************************
 * Tests for the functions written in Lab 7 are below this line.
 */

/* Use global variables, so we don't have to pass all of these pointers 
 * to a bunch of test functions.
 */
intlist_t *list1, *list2, *list3, *list4, *list5, *list6, *list7, *list8;

static void setup(void) {
    // Empty list, [].
    list1 = intlist_construct(1);

    // [5]
    list2 = intlist_construct(1);
    intlist_append(list2, 5);

    // [7]
    list3 = intlist_construct(1);
    intlist_append(list3, 7);

    // [5, 3, 2]
    list4 = intlist_construct(3);
    intlist_append(list4, 5);
    intlist_append(list4, 3);
    intlist_append(list4, 2);

    // [3, 2, 5]
    list5 = intlist_construct(3);
    intlist_append(list5, 3);
    intlist_append(list5, 2);
    intlist_append(list5, 5);

    // [7, 5, 2]
    list6 = intlist_construct(3);
    intlist_append(list6, 7);
    intlist_append(list6, 5);
    intlist_append(list6, 2);

    // [3, 8, 6]
    list7 = intlist_construct(3);
    intlist_append(list7, 3);
    intlist_append(list7, 8);
    intlist_append(list7, 6);

    // [7, 5, 3, 6, 5, 2]
    list8 = intlist_construct(6);
    intlist_append(list8, 7);
    intlist_append(list8, 5);
    intlist_append(list8, 3);
    intlist_append(list8, 6);
    intlist_append(list8, 5);
    intlist_append(list8, 2);
}

static void teardown(void) {
    intlist_destroy(list1);
    intlist_destroy(list2);
    intlist_destroy(list3);
    intlist_destroy(list4);
    intlist_destroy(list5);
    intlist_destroy(list6);
    intlist_destroy(list7);
    intlist_destroy(list8);
}

static void test_intlist_index(void) {
    setup();

    printf("list1 = []\n");
    sput_fail_unless(intlist_index(list1, 5) == -1, "intlist_index(list1, 5)");
    printf("Expected: -1, actual: %d\n\n", intlist_index(list1, 5));

    printf("list2 = [5]\n");
    sput_fail_unless(intlist_index(list2, 5) == 0, "intlist_index(list2, 5)");
    printf("Expected: 0, actual: %d\n\n", intlist_index(list2, 5));

    printf("list3 = [7]\n");
    sput_fail_unless(intlist_index(list3, 5) == -1, "intlist_index(list3, 5)");
    printf("Expected: -1, actual: %d\n\n", intlist_index(list3, 5));

    printf("list4 = [5 3 2]\n");
    sput_fail_unless(intlist_index(list4, 5) == 0, "intlist_index(list4, 5)");
    printf("Expected: 0, actual: %d\n\n", intlist_index(list4, 5));

    printf("list5 = [3 2 5]\n");
    sput_fail_unless(intlist_index(list5, 5) == 2, "intlist_index(list5, 5)");
    printf("Expected: 2, actual: %d\n\n", intlist_index(list5, 5));

    printf("list6 = [7 5 2]\n");
    sput_fail_unless(intlist_index(list6, 5) == 1, "intlist_index(list6, 5))");
    printf("Expected: 1, actual: %d\n\n", intlist_index(list6, 5));

    printf("list7 = [3 8 6]\n");
    sput_fail_unless(intlist_index(list7, 5) == -1, "intlist_index(list7, 5)");
    printf("Expected: -1, actual: %d\n\n", intlist_index(list7, 5));

    printf("list8 = [7 5 3 6 5 2]\n");
    sput_fail_unless(intlist_index(list8, 5) == 1, "intlist_index(list8, 5)");
    printf("Expected: 1, actual: %d\n", intlist_index(list8, 5));

    teardown();
}

static void test_intlist_count(void) {
    setup();

    printf("list1 = []\n");
    sput_fail_unless(intlist_count(list1, 5) == 0, "intlist_count(list1, 5)");
    printf("Expected: 0, actual: %d\n\n", intlist_count(list1, 5));

    printf("list2 = [5]\n");
    sput_fail_unless(intlist_count(list2, 5) == 1, "intlist_count(list2, 5)");
    printf("Expected: 1, actual: %d\n\n", intlist_count(list2, 5));

    printf("list3 = [7]\n");
    sput_fail_unless(intlist_count(list3, 5) == 0, "intlist_count(list3, 5)");
    printf("Expected: 0, actual: %d\n\n", intlist_count(list3, 5));

    printf("list4 = [5 3 2]\n");
    sput_fail_unless(intlist_count(list4, 5) == 1, "intlist_count(list4, 5)");
    printf("Expected: 1, actual: %d\n\n", intlist_count(list4, 5));

    printf("list5 = [3 2 5]\n");
    sput_fail_unless(intlist_count(list5, 5) == 1, "intlist_count(list5, 5)");
    printf("Expected: 1, actual: %d\n\n", intlist_count(list5, 5));

    printf("list6 = [7 5 2]\n");
    sput_fail_unless(intlist_count(list6, 5) == 1, "intlist_count(list6, 5))");
    printf("Expected: 1, actual: %d\n\n", intlist_count(list6, 5));

    printf("list7 = [3 8 6]\n");
    sput_fail_unless(intlist_count(list7, 5) == 0, "intlist_count(list7, 5)");
    printf("Expected: 0, actual: %d\n\n", intlist_count(list7, 5));

    printf("list8 = [7 5 3 6 5 2]\n");
    sput_fail_unless(intlist_count(list8, 5) == 2, "intlist_count(list8, 5)");
    printf("Expected: 2, actual: %d\n\n", intlist_count(list8, 5));

    teardown();
}

static void test_intlist_contains(void) {
    setup();

    printf("list1 = []\n");
    sput_fail_unless(intlist_contains(list1, 5) == false, "intlist_contains(list1, 5)");
    printf("Expected: false, actual: ");
    _print_bool(intlist_contains(list1, 5));
    printf("\n\n");

    printf("list2 = [5]\n");
    sput_fail_unless(intlist_contains(list2, 5) == true, "intlist_contains(list2, 5)");
    printf("Expected: true, actual: ");
    _print_bool(intlist_contains(list2, 5));
    printf("\n\n");

    printf("list3 = [7]\n");
    sput_fail_unless(intlist_contains(list3, 5) == 0, "intlist_contains(list3, 5)");
    printf("Expected: false, actual: ");
    _print_bool(intlist_contains(list3, 5));
    printf("\n\n");

    printf("list4 = [5 3 2]\n");
    sput_fail_unless(intlist_contains(list4, 5) == true, "intlist_contains(list4, 5)");
    printf("Expected: true, actual: ");
    _print_bool(intlist_contains(list4, 5));
    printf("\n\n");

    printf("list5 = [3 2 5]\n");
    sput_fail_unless(intlist_contains(list5, 5) == true, "intlist_contains(list5, 5)");
    printf("Expected: true, actual: ");
    _print_bool(intlist_contains(list5, 5));
    printf("\n\n");

    printf("list6 = [7 5 2]\n");
    sput_fail_unless(intlist_contains(list6, 5) == true, "intlist_contains(list6, 5))");
    printf("Expected: true, actual: ");
    _print_bool(intlist_contains(list6, 5));
    printf("\n\n");;

    printf("list7 = [3 8 6]\n");
    sput_fail_unless(intlist_contains(list7, 5) == false, "intlist_contains(list7, 5)");
    printf("Expected: false, actual: ");
    _print_bool(intlist_contains(list7, 5));
    printf("\n\n");

    printf("list8 = [7 5 3 6 5 2]\n");
    sput_fail_unless(intlist_contains(list8, 5) == true, "intlist_contains(list8, 5)");
    printf("Expected: true, actual: ");
    _print_bool(intlist_contains(list8, 5));
    printf("\n");

    teardown();
}

static void test_increase_capacity(void) {
    printf("Creating list with capacity 5, list = [4 7 3 -2 9]\n");
    intlist_t *list = intlist_construct(5);
    intlist_append(list, 4);
    intlist_append(list, 7);
    intlist_append(list, 3);
    intlist_append(list, -2);
    intlist_append(list, 9);

    int *old_array = list->elems;

    printf("Calling increase_capacity(list, 10;)\n");
    increase_capacity(list, 10);

    sput_fail_unless(intlist_capacity(list) == 10, "intlist_capacity(list)");
    printf("Expected: 10, actual: %d\n", intlist_capacity(list));

    sput_fail_unless(intlist_size(list) == 5, "intlist_size(list)");
    printf("Expected: 5, actual: %d\n", intlist_size(list));

    printf("Verifying that increase_capacity allocated a new array\n");
    sput_fail_unless(list->elems != old_array, "list->elems != address of old_array");
    printf("expected: true, actual: ");
    _print_bool(list->elems != old_array);
    printf("\n");

    int expected[] = {4, 7, 3, -2, 9};
    sput_fail_unless(compare_arrays(list->elems, expected, 5),
                     "Checking backing array");
    printf("Expected: [4 7 3 -2 9], actual: ");
    _print_array(list->elems, 5);
    printf("\n");

    intlist_destroy(list);
}

static void test_modified_intlist_append(void) {
    _Bool appended;
    int expected[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    printf("Creating an empty list: list = intlist_construct(10);\n");
    intlist_t *list = intlist_construct(10);

    printf("Initializing list to [0 2 4 6 8 10 12 14 16 18]\n");
    for (int i = 0; i < 10; i += 1) {
        appended = intlist_append(list, i * 2);
    }

    appended = intlist_append(list, 20);
    sput_fail_unless(appended == true,
                     "appended = intlist_append(list, 20); checking appended");
    printf("Expected: true, actual: ");
    _print_bool(appended);
    printf("\n");

    sput_fail_unless(intlist_capacity(list) == 20, "intlist_capacity(list)");
    printf("Expected: 20, actual: %d\n", intlist_capacity(list));

    sput_fail_unless(intlist_size(list) == 11, "intlist_size(list)");
    printf("Expected: 11, actual: %d\n", intlist_size(list));

    sput_fail_unless(compare_arrays(list->elems, expected, 11),
                     "Checking backing array");
    printf("Expected: [0 2 4 6 8 10 12 14 16 18 20], actual: ");
    _print_array(list->elems, 11);
    printf("\n");

    intlist_destroy(list);
}

static void test_intlist_delete(void) {
    setup();

    printf("list2 = [5]\n");

    /* Delete the integer @ index 0 in this list: [5]
    * list should become []
    */
    printf("Calling intlist_delete(list2, 0)\n");
    intlist_delete(list2, 0);
    sput_fail_unless(intlist_size(list2) == 0, "intlist_size(list2)");
    printf("Expected: 0, actual: %d\n\n", intlist_size(list2));

    printf("list4 = [5 3 2]\n");

    /* Delete the integer @ index 0 in this list: [5 3 2]
    * list should become [3, 2]
    */
    printf("Calling intlist_delete(list4, 0)\n:");
    intlist_delete(list4, 0);
    sput_fail_unless(intlist_size(list4) == 2, "intlist_size(list4)");
    printf("Expected: 2, actual: %d\n", intlist_size(list4));

    int expected1[] = {3, 2};
    sput_fail_unless(compare_arrays(list4->elems, expected1, 2), "Checking backing array");
    printf("Expected: [3 2], actual: ");
    _print_array(list4->elems, 2);
    printf("\n\n");

    teardown();
    setup();

    printf("list4 = [5 3 2]\n");

    /* Delete the integer @ index 1 in this list: [5, 3, 2]
    * list should become [5, 2]
    */
    printf("Calling intlist_delete(list4, 1)\n:");
    intlist_delete(list4, 1);
    sput_fail_unless(intlist_size(list4) == 2, "intlist_size(list4)");
    printf("Expected: 2, actual: %d\n", intlist_size(list4));

    int expected2[] = {5, 2};
    sput_fail_unless(compare_arrays(list4->elems, expected2, 2), "Checking backing array");
    printf("Expected: [5 2], actual: ");
    _print_array(list4->elems, 2);
    printf("\n\n");

    teardown();
    setup();

    printf("list4 = [5 3 2]\n");

    /* Delete the integer @ index 2 in this list: [5, 3, 2]
    * list should become [5, 3]
    */
    printf("Calling intlist_delete(list4, 2);\n");
    intlist_delete(list4, 2);
    sput_fail_unless(intlist_size(list4) == 2, "intlist_size(list4)");
    printf("Expected: 2, actual: %d\n", intlist_size(list4));

    int expected3[] = {5, 3};
    sput_fail_unless(compare_arrays(list4->elems, expected3, 2), "Checking backing array");
    printf("Expected: [5 3], actual: ");
    _print_array(list4->elems, 2);
    printf("\n");

    teardown();
}

int main(void) {
    printf("Running test harness for SYSC 2006 Winter 2018 Lab 6\n");

    sput_start_testing();

    sput_enter_suite("Lab 6, Exercise 1: intlist_construct()");
    sput_run_test(test_intlist_construct);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intnode_construct "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 6, Exercise 2: intlist_print()");
    sput_run_test(test_intlist_print);

    sput_enter_suite("Lab 6, Exercise 3: intlist_append()");
    sput_run_test(test_intlist_append);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intnode_append "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 6, Exercise 4: intlist_capacity()");
    sput_run_test(test_intlist_capacity);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intnode_capacity "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 6, Exercise 5: intlist_size()");
    sput_run_test(test_intlist_size);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intnode_size "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 6, Exercise 6: intlist_get()");
    sput_run_test(test_intlist_get);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intnode_get "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 6, Exercise 7: intlist_set()");
    sput_run_test(test_intlist_set);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intnode_set "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 6, Exercise 8: intlist_removeall()");
    sput_run_test(test_intlist_removeall);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intlist_removeall "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 7, Exercise 1: intlist_index()");
    sput_run_test(test_intlist_index);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intlist_index "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 7, Exercise 2: intlist_count()");
    sput_run_test(test_intlist_count);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intlist_count "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 7, Exercise 3: intlist_contains()");
    sput_run_test(test_intlist_contains);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intlist_contains "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 7, Exercise 4: increase_capacity()");
    sput_run_test(test_increase_capacity);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until increase_capacity "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 7, Exercise 5: modified intlist_append()");
    sput_run_test(test_modified_intlist_append);
    sput_leave_suite();

    if (sput_get_return_value() == EXIT_FAILURE) {
        printf("Remaining tests won't be run until intlist_append "
                       "passes all tests.\n");
        sput_finish_testing();
        return sput_get_return_value();
    }

    sput_enter_suite("Lab 7, Exercise 6: intlist_delete()");
    sput_run_test(test_intlist_delete);

    sput_finish_testing();
    return sput_get_return_value();
}
