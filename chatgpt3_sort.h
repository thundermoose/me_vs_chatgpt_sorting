#include <stdint.h>
#include <stdlib.h>

// A utility function to get the maximum value in arr[]
static uint64_t getMax(uint64_t arr[], int n) {
    uint64_t mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to the digit represented by exp.
static void countSort(uint64_t arr[], int n, uint64_t exp) {
    uint64_t *output = (uint64_t*)malloc(n * sizeof(uint64_t)); // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

// The main function to that sorts arr[] of size n using Radix Sort
static void radixSort(uint64_t arr[], int n) {
    // Find the maximum number to know the number of digits
    uint64_t m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead of passing digit number, exp is passed.
    // exp is 10^i where i is current digit number
    for (uint64_t exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// Wrapper function to sort
static void chatgpt3_sort(uint64_t *arr, size_t length) {
    radixSort(arr, length);
}

