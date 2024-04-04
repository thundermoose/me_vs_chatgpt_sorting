#ifndef __CHATGPT_UTIL__
#define __CHATGPT_UTIL__
#include <stdint.h>

// Function to swap two elements
static void swap(uint64_t* a, uint64_t* b) {
    uint64_t t = *a;
    *a = *b;
    *b = t;
}

// Insertion sort
static void insertionSort(uint64_t arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        uint64_t temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Partition function for quicksort
static int partition(uint64_t arr[], int low, int high) {
    uint64_t pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
#endif
