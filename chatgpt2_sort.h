#include <stdint.h>
#include <stddef.h>
#include <math.h>

void heapify(uint64_t arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(uint64_t arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}


void introsortUtil(uint64_t arr[], int begin, int end, int depthLimit) {
    int size = end - begin + 1;

    if (size < 16) {
        insertionSort(arr, begin, end);
        return;
    }

    if (depthLimit == 0) {
        heapSort(arr + begin, size);
        return;
    }

    int partitionPoint = partition(arr, begin, end);
    if (partitionPoint - 1 > begin) {
        introsortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
    }
    if (partitionPoint + 1 < end) {
        introsortUtil(arr, partitionPoint + 1, end, depthLimit - 1);
    }
}

void introsort(uint64_t arr[], int n) {
    int depthLimit = 2 * log(n) / log(2);
    introsortUtil(arr, 0, n - 1, depthLimit);
}

void chatgpt2_sort(uint64_t *arr, size_t length) {
    introsort(arr, length);
}

