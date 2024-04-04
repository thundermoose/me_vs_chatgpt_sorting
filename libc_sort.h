#ifndef __LIBC_SORT__
#define __LIBC_SORT__

#include <stdlib.h>
#include <stdint.h>

static int compare_uint64(uint64_t *left, uint64_t *right) {
	if (*left < *right)
		return -1;
	else if (*left > *right)
		return 1;
	else
		return 0;
}

static void libc_sort(uint64_t *array, size_t length) {
	qsort(array, 
		  length, 
		  sizeof(uint64_t), 
		  (__compar_fn_t)compare_uint64);
}

#endif
