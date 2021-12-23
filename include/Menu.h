#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <string>
#include <vector>

#include "Review.h"
#include "Timer.h"
#include "Sort.h"
#include "Hash.h"

using namespace std;
using namespace chrono;

//Constantes
int const N_METHODS_SORT = 3;
int const M_NUMBER = 3;
string const ARQ_SAIDA = "saida.txt";

class Menu
{
public:
	Menu() {};
	~Menu() {};

	void static repeticaoMenu();
	int static menu();
	void static selecionaChave(int chave);
	void static menuOrdenacao();
	static void iniciar();
	int static readDat(string pathDat, int l);

private:
	//void static hash();
	//void static modTeste();
	static void writeOrdenacaoTxt(string arquivo, resultSort data[][N_METHODS_SORT], int n, int m);
	static void writeMediaTxt(resultSort data[][N_METHODS_SORT]);
	static void gerenciaOrdenacao(int chave_n);
};

#endif // MENU_H