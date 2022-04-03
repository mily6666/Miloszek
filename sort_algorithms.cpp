#include "sort_algorithms.h"


// MERGE SORT //
template<typename T>
void merge(T *tab, T *tmp, int left, int midd, int right) //tmp pomocnicza tablica
{
	for (int i = left; i <= right; i++) tmp[i] = tab[i];

	int i = left;
	int j = midd + 1;
	int q = left;

	while (i <= midd && j <= right)
	{
		if (tmp[i] < tmp[j]) tab[q++] = tmp[i++];
		else tab[q++] = tmp[j++];
	}
	while (i <= midd) tab[q++] = tmp[i++];
}


template<typename T>
void mergesort(T *tab, T *tmp, int left, int right)
{
	if (left < right)
	{
		int midd = (left + right) / 2;
		mergesort(tab, tmp, left, midd);
		mergesort(tab, tmp, midd + 1, right);
		merge(tab, tmp, left, midd, right);
	}
}



// QUCIK SORT //
template<typename T>
int partition(T *tab, int left, int right)
{
    int pivot = tab[(left + right) / 2], i = left, j = right;

    while (true)
    {
        while (tab[j] > pivot) j--;//szukam elementu mniejszego lub rownego pivot stojacego
		//po lewej stronie wartosci pivot

        while (tab[i] < pivot) i++;//szukam elementu wiekszego lub rownego piwot stojacego
		//po prawej stronie wartosci pivot

        if (i < j)  std::swap(tab[i++], tab[j--]);//jesli liczniki sie nie minely to zamieñ elementy ze soba
		//stojace po niewlasciwej stronie elementu pivot
		//funkcja swap zamienia wartosciami tab[i] z tab[j]
        else return j;
    }
}


template<typename T>
void quicksort(T *tab, int left, int right)
{
    if (left < right)
    {
        int q = partition(tab, left, right); //q - wartosc srodkowa
        quicksort(tab, left, q);
        quicksort(tab, q + 1, right);
    }
}



// INSERTION SORT //
template<typename T>
void insertionsort(T *tab, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = tab[i];
		int j = i;

		while (j > left && tab[j - 1] > key)
        {
            tab[j] = tab[j - 1];
            j--;
        }
		tab[j] = key;
	}
}


// HEAP SORT //
template<typename T>
void heapsort(T *left, T *right)
{
	std::make_heap(left, right);
	std::sort_heap(left, right);
}


// INTRO SORT //
template<typename T>
void introsort(T *tab, T *left, T *right, int maxdepth)
{
	if ((right - left) < 16) insertionsort(tab, left - tab, right - tab);
	else if (maxdepth == 0) heapsort(left, right + 1);
	else
    {
		int pivot = partition(tab, left - tab, right - tab);
		introsort(tab, left, tab + pivot, maxdepth - 1);
		introsort(tab, tab + pivot + 1, right, maxdepth - 1);
    }
}

template void introsort<int>(int*, int*, int*, int);
template void mergesort<int>(int*, int*, int, int);
template void quicksort<int>(int*, int, int);
