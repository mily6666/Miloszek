#pragma once

#include <algorithm>

template<typename T>
void introsort(T *tab, T *left, T *right, int maxdepth);

template<typename T>
void quicksort(T *tab, int left, int right);

template<typename T>
void mergesort(T *tab, T *tmp, int left, int right);
