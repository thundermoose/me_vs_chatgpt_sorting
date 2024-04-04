#ifndef __CHATGPT_SORT__
#define __CHATGPT_SORT__
#include <stdint.h>
#include <stddef.h>
#include "chatgpt_util.h"

// Quick sort function
static void quickSort(uint64_t arr[], int low, int high) {
    if (low < high) {
        // If the size of the array is small, use insertion sort for optimization
        if (high - low < 10) {
            insertionSort(arr, low, high);
        } else {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}

// Function to sort the array
static void chatgpt1_sort(uint64_t *arr, size_t length) {
    quickSort(arr, 0, length - 1);
}

#endif
