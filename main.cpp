#include "sort_algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <cmath>

#define DataType int

template<typename T>// funckja do wsywietlania tablicy tab - wyswietlana tablica, n - ilosc elementow w tablicy
void print_table(T *tab, int n)
{
    for (int i = 0; i < n; i++) std::cout << tab[i] << " ";
}

template<typename T>//tworzy dynamiczna tablice i zwraca wskaznik miejsca gdzie zostala utworzona
T *create_table(int n)
{
	return new T[n];
}

template<typename T>
void remove_table(T *table)
{
	delete[] table;
}

//wypelnia tabele przypadkowymi elementami
//przy uzyciu zakresu liczba 1-100 000
template<typename T>
void fill_random(T *tab, int n)
{
	for (int i = 0; i < n; i++) tab[i] = rand() % 100000 + 1;// losujemy wartośći z zakresu 1-100001
}

//sortuje okreœlony procent elementów w tabeli(od pierwszego elementu)
template<typename T>
void sort_percent(T *tab, int n, double percent)//sortuje pewien procent elementow tablicy
{
    if (percent == 100) //nastêpnie sortuje cala tabelê w odwrotnej kolejnoœci
    {
        std::sort(tab, tab + n, std::greater<T>());// sort - pierwszy parametr to poczatek tablicy, drugi to koniec tablicy, wybieramy funkcje porzadkujaca
        return;
    }
	std::sort(tab, tab + (int)((n*percent) / 100));// zamieniamy double na int
}

template<typename T>
void check_if_sorted(T *tab, int n)// sprawdzanie poprawnosci sortowania
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            std::cout << "Tablica nieposortowana, zamkniecie porgramu";
            std::cin.get();
            exit(1);
        }
    }
}

void check_if_open (std::ofstream &file)
{
    if (!file.is_open())
     {
        std::cout << "Plik nie jest otwarty";
        std::cin.get();
        exit(1);
     }
}

int main()
{
    std::ofstream file("Results.txt");
    check_if_open(file);

    srand(time(NULL));

	int ilosc_tablic = 1; //liczba tabel, które bêd¹ posortowane dla ka¿dej konfiguracji
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000}; //rozmiary tabel
	double percenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100 };


 /*
  * Sortowanie szybkie
  */
 	double licznik = 0;
    std::cout << "QUCIK_SORT" << std::endl;
    file<<"QUCIK_SORT"<<"\t\t\n";
    for (double percent : percenttab)
    {
        for (int n : ntab)
        {
            DataType *tab = create_table<DataType>(n);

            for (int i = 0; i < ilosc_tablic; i++) //sortuj okreslona liczbe tablic
            {
                fill_random<DataType>(tab, n);
                sort_percent<DataType>(tab, n, percent);

                auto t_start = std::chrono::high_resolution_clock::now(); //start clock
                quicksort(tab, 0, n-1); // tablica, numer pierwszego elementu, numer ostatniego elementu tablicy
                auto t_end = std::chrono::high_resolution_clock::now(); //stop clock
                licznik += std::chrono::duration<double, std::milli>(t_end - t_start).count(); //zwraca czas w milisekundach

                check_if_sorted<DataType>(tab, n);

                std::cout << i << "%" << "\r";//wyświetl procentowe wykonanie pętli
            }
            remove_table<DataType>(tab);

            std::cout << n << " Tablica posortowana!" << std::endl;

            file << percent<<";"<<n<<";"<<licznik / ilosc_tablic << "\n"; //zapisuje srednie czas poswiecony na sortowanie tablicy

            licznik = 0;
        }
        std::cout << percent << " % posortowane!" << std::endl;
    }
    file << "\r\n";

 /*
  * Sortowanie przez scalanie
  */
    licznik = 0;
    std::cout << "MERGE_SORT" << std::endl;
    file<<"MERGE_SORT"<<"\t\t\n";
    for (double percent : percenttab)
    {
        for (int n : ntab)
        {
            DataType *tab = create_table<DataType>(n);
            DataType *tmp = create_table<DataType>(n);

            for (int i = 0; i < ilosc_tablic; i++)
            {
                fill_random<DataType>(tab, n);
                sort_percent<DataType>(tab, n, percent);

                auto t_start = std::chrono::high_resolution_clock::now();
                mergesort(tab, tmp, 0, n-1);
                auto t_end = std::chrono::high_resolution_clock::now();
                licznik += std::chrono::duration<double, std::milli>(t_end - t_start).count();

                check_if_sorted<DataType>(tab, n);

                std::cout << i << "%" << "\r";
            }
            remove_table<DataType>(tab);
            remove_table<DataType>(tmp);

            std::cout << n << " Tablica posortowana!" << std::endl;

           file << percent<<";"<<n<<";"<<licznik / ilosc_tablic << "\n";

            licznik = 0;
        }
        std::cout << percent << " % posortowane!" << std::endl;
    }
    file << "\r\n";

  /*
  * Sortowanie introspektywne
  */
    licznik = 0;
    std::cout << "INTRO_SORT" << std::endl;
    file<<"INTRO_SORT"<<"\n";
    for (double percent : percenttab)
    {
        for (int n : ntab)
        {
            DataType *tab = create_table<DataType>(n);


            for (int i = 0; i < ilosc_tablic; i++)
            {
                fill_random<DataType>(tab, n);
                sort_percent<DataType>(tab, n, percent);

                auto t_start = std::chrono::high_resolution_clock::now();
                introsort(tab, tab, tab + n-1 , log(n) * 2);
                auto t_end = std::chrono::high_resolution_clock::now();
                licznik += std::chrono::duration<double, std::milli>(t_end - t_start).count();

                check_if_sorted<DataType>(tab, n);

                std::cout << i << "%" << "\r";
            }
            remove_table<DataType>(tab);

            std::cout << n << " Tablica posortowana!" << std::endl;

            file << percent<<";"<<n<<";"<<licznik / ilosc_tablic << "\n";

            licznik = 0;
        }
        std::cout << percent << " % posortowane!" << std::endl;
    }
    file << "\r\n";

    std::cout << "Koniec sortowania!";
	std::cin.get();
	file.close();

	return 0;
}

