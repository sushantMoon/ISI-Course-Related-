#ifndef SORT_GENERIC_H
#define SORT_GENERIC_H

void swapemp(void *a, void *b, int elemSize);
void inPlaceSort(void *arr, int elemCount, int elemSize, int (*comparator) (void *, void *));

#endif
