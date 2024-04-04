#ifndef __MY_SORT__
#define __MY_SORT__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "chatgpt_util.h"

static void my_sort(uint64_t *array, size_t num_elements) {			
	size_t bucket_lengths[256];
	size_t bucket_starts[9][256];
	size_t bucket_ends[9][256];
	size_t next_bucket[2048];
	size_t next_byte[2048];
	size_t buffer_head = 0;
	uint64_t *work_space = (uint64_t*)malloc(sizeof(uint64_t)*num_elements);
	memset(bucket_starts, 0, sizeof(bucket_starts));
	memset(bucket_ends, 0, sizeof(bucket_ends));
	next_byte[buffer_head] = 7;
	next_bucket[buffer_head++] = 0;
	bucket_starts[8][0] = 0;
	bucket_ends[8][0] = num_elements;
	while (buffer_head > 0) {
		size_t byte = next_byte[--buffer_head];
		size_t bucket_index = next_bucket[buffer_head];
		size_t start = bucket_starts[byte+1][bucket_index];
		size_t end = bucket_ends[byte+1][bucket_index];
		if (end - start <= 32) {
			insertionSort(array, start, end-1);
			continue;
		}
		//for (size_t i = 0; i < 256; i++)
		//	bucket_lengths[byte][i] = 0;
		memset(bucket_lengths, 0, sizeof(size_t)*256);
		for (size_t i = start; i < end; i++) {
			size_t j = (array[i]>>(8*byte))&255;
                        bucket_lengths[j]++;
                }
                size_t bstart = start;
		for (size_t i = 0; i < 256; i++) {
			bucket_starts[byte][i] = bstart;
			bucket_ends[byte][i] = bstart;
			bstart+=bucket_lengths[i];
		}
		for (size_t i = start; i < end; i++) { 
			size_t j = (array[i]>>(8*byte))&255;
			size_t k = bucket_ends[byte][j]++;
			work_space[k] = array[i];
		}
		for (size_t i = start; i < end; i++)
			array[i] = work_space[i];
		if (byte == 0)
			continue;
		for (size_t i = 0; i < 256; i++) {
			if (bucket_lengths[i] < 2)
				continue;	
			next_byte[buffer_head] = byte-1;
			next_bucket[buffer_head++] = i;
		}
	}
	free(work_space);
}

#endif
