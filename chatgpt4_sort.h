#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function to find the maximum value in the array
static uint64_t findMax(uint64_t arr[], int n) {
    uint64_t max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Counting sort function
static void countingSort(uint64_t arr[], int n) {
    uint64_t max = findMax(arr, n);
    uint64_t* count = (uint64_t*) calloc(max + 1, sizeof(uint64_t));
    
    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Store the cummulative count of each array
    for (uint64_t i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    uint64_t* output = (uint64_t*) malloc(n * sizeof(uint64_t));
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
    free(count);
}

// Wrapper function to sort
static void chatgpt4_sort(uint64_t *arr, size_t length) {
    countingSort(arr, length);
}

