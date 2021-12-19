#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <time.h>

#include "../include/Review.h"
//#include "../include/Hash.h"
#include "../include/Menu.h"
#include "../include/Sort.h"

using namespace std;

int menu();
bool verificaBinario(string nome);

/* Vetores da classe vector para representar as reviews dos usuarios (dataReview) */
vector<Review> dataReview;

/* Arquivo de saida */
ofstream arqSaida;

/* String que representa o caminho da pasta com os arquivos .csv */
string pathCsv;


int main(int argc, char* argv[])
{
    srand(time(NULL));

    cout << "Trabalho de ED II (Parte 1)" << endl;
    cout << "Leitura Iniciada!" << endl
        << endl;

    // Verifica se foi passado o caminho da pasta onde possui os arquivos .csv.
    // Caso nao tenha, considera vazio.
    if (argv[1])
    {
        pathCsv = argv[1];
        //pathCsv = pathCsv + "/";
    }
    else
    {
        pathCsv = "";
    }

    dataReview = Review::readCsv(pathCsv);
    Review::writeBinary(dataReview.data(), dataReview.size());

    Menu::iniciar();

    return 0;
}


bool verificaBinario(string nome)
{
    string path = "./bin/" + nome;
    fstream arq(path);
    if (arq.is_open())
    {
        arq.close();
        return true;
    }
    return false;
}