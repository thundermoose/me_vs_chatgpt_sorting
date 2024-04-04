#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "my_sort.h"
#include "libc_sort.h"
#include "chatgpt_sort.h"
#include "chatgpt2_sort.h"
#include "chatgpt3_sort.h"
#include "chatgpt4_sort.h"

#define swap(a,b){\
	typeof(a) tmp = a; \
	a = b; \
	b = tmp; \
}

typedef void (*sort_t)(uint64_t *array, size_t num_elements);

const size_t NUM_ELEMENTS = 100000000;

uint64_t *random_array(size_t num_elements) {
	uint64_t *array = (uint64_t*)malloc(num_elements*sizeof(uint64_t));
	for (uint64_t i = 0; i < num_elements; i++)
		array[i] = i+1;
	srand(time(0));
	for (size_t i = 0; i < num_elements/2; i++) {
		size_t left = rand()%num_elements;
		size_t right = rand()%num_elements;
		swap(array[left], array[right]);
	}
	return array;
}

uint64_t *copy_array(uint64_t *array, size_t num_elements) {
	uint64_t *dst = (uint64_t*)malloc(num_elements*sizeof(uint64_t));	
	memcpy(dst, array, sizeof(uint64_t)*num_elements);
	return dst;
}

double time_sort(sort_t sort_func, uint64_t *array, size_t num_elements) {
	struct timespec t_start, t_end;
	clock_gettime(CLOCK_REALTIME, &t_start);
	sort_func(array, num_elements);
	clock_gettime(CLOCK_REALTIME, &t_end);
	return (t_end.tv_sec - t_start.tv_sec)*1.0e6 + 
		(t_end.tv_nsec - t_start.tv_nsec)*1.0e-3;
}

void validate(uint64_t *left_array, uint64_t *right_array, size_t num_elements) {
	for (size_t i = 0; i < num_elements; i++) {
		if (left_array[i] != right_array[i]) {
			printf("Element %lu differ\n", i);
			__builtin_trap();
		}
	}
}

int main() {
	uint64_t *original_array = random_array(NUM_ELEMENTS);
	uint64_t *my_copy = copy_array(original_array, NUM_ELEMENTS);
	uint64_t *libc_copy = copy_array(original_array, NUM_ELEMENTS);
	uint64_t *chatgpt1_copy = copy_array(original_array, NUM_ELEMENTS);
	uint64_t *chatgpt2_copy = copy_array(original_array, NUM_ELEMENTS);
	uint64_t *chatgpt3_copy = copy_array(original_array, NUM_ELEMENTS);
	uint64_t *chatgpt4_copy = copy_array(original_array, NUM_ELEMENTS);
	
	double my_time = time_sort(my_sort, my_copy, NUM_ELEMENTS);
	double libc_time = time_sort(libc_sort, libc_copy, NUM_ELEMENTS);
	double chatgpt1_time = time_sort(chatgpt1_sort, chatgpt1_copy, NUM_ELEMENTS);
	double chatgpt2_time = time_sort(chatgpt2_sort, chatgpt2_copy, NUM_ELEMENTS);
	double chatgpt3_time = time_sort(chatgpt3_sort, chatgpt3_copy, NUM_ELEMENTS);
	double chatgpt4_time = time_sort(chatgpt4_sort, chatgpt4_copy, NUM_ELEMENTS);
	validate(my_copy, libc_copy, NUM_ELEMENTS);
	validate(chatgpt1_copy, libc_copy, NUM_ELEMENTS);
	validate(chatgpt2_copy, libc_copy, NUM_ELEMENTS);
	validate(chatgpt3_copy, libc_copy, NUM_ELEMENTS);
	validate(chatgpt4_copy, libc_copy, NUM_ELEMENTS);
	printf("My time: %lg micro seconds\n", my_time);
	printf("LibC time: %lg micro seconds\n", libc_time);
	printf("ChatGPT1 time: %lg micro seconds\n", chatgpt1_time);
	printf("ChatGPT2 time: %lg micro seconds\n", chatgpt2_time);
	printf("ChatGPT3 time: %lg micro seconds\n", chatgpt3_time);
	printf("ChatGPT4 time: %lg micro seconds\n", chatgpt4_time);
	free(my_copy);
	free(libc_copy);
	free(chatgpt1_copy);
	free(chatgpt2_copy);
	free(chatgpt3_copy);
	free(chatgpt4_copy);
}
