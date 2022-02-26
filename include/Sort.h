#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

#include "Review.h"
#include "Timer.h"

using namespace std;
using namespace chrono;

// Estrutura para representar o resultado estatistico do metodo de ordenação
struct resultSort
{
	string tipo;
	double nCompare;
	double nSwap;
	duration<double> time_spent;

	resultSort(string tipo, double nCompare, double nSwap, duration<double> time){
		this->tipo = tipo;
		this->nCompare = nCompare;
		this->nSwap = nSwap;
		this->time_spent = time;
	}

	resultSort(){}
};

class Sort
{
public:
	Sort() {};
	~Sort() {};

	void static selectionSort(Review reviews[], int n, double* nSwap, double* nCompare);
	void static quickSort(Review reviews[], int inicio, int fim, double* nSwap, double* nCompare);
	void static heapSort(Review rev[], int n, double* nSwap, double* nCompare);
	static resultSort *ordenacao(int m);
	static resultSort media(resultSort data[], int n_itens);
	static Review medianaDeTres(Review* v, int ini, int fim);
	void static troca(Review& v, Review& n);

private:
	void static swap(Review* item1, Review* item2, double* numSwap);
	int static particao(Review reviews[], int inicio, int fim, double* nSwap, double* nCompare);
	void static heapify(Review reviews[], int n, int i, double* nSwap, double* nCompare);
};

#endif // SORT_H