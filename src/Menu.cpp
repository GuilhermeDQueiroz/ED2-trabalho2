#include "../include/Menu.h"

void Menu::iniciar()
{
    int opt;
    system("clear");
menu:
    cout << "\n| ----- Menu Principal ------ |" << endl
        << endl
        << "Selecione uma opcao para continuar: " << endl
        << "1 - Ordenacao\n2 - Hash\n3 - Modulo de Teste\n0 - Sair" << endl
        << endl
        << ">> ";

    cin >> opt;

    switch (opt)
    {
    case 1:
        
        menuOrdenacao();
        break;

    case 2:
        //hash();
        break;

    case 3:
        //modTeste();
        break;

    case 0:
        return;
        break;

    default:
        goto menu;
        break;
    }
    goto menu;
}

void Menu::menuOrdenacao()
{
    int opt;
    string pathDat = "";
    int s = 0;
menu:
    cout << "\n| --- Menu de Ordenacao --- |\n\n"
        << "Digite a quantidade de elementos para serem ordenados: \n\n"
        << "1 - 10.000\n2 - 50.000\n3 - 100.000\n4 - 500.000\n5 - 1.000.000\n0 - Sair\n\n>> ";
    cin >> opt;
    
    switch (opt)
    {
    case 1:
        s = readDat(pathDat, 1);
        gerenciaOrdenacao(s);
        break;
    case 2:
        s = readDat(pathDat, 2);
        gerenciaOrdenacao(s);
        break;
    case 3:
        s = readDat(pathDat, 3);
        gerenciaOrdenacao(s);
        break;
    case 4:
        s = readDat(pathDat, 4);
        gerenciaOrdenacao(s);
        break;
    case 5:
        s = readDat(pathDat, 5);
        gerenciaOrdenacao(s);
        break;
    case 0:
        return;
        break;
    default:
        goto menu;
        break;
    }
    return;
}

void Menu::gerenciaOrdenacao(int n)
{
    //Quantidade de amostras utilizadas para calcular o resultado dos metodos de ordena��o
    int M = 3;

    resultSort listResult[3][N_METHODS_SORT];

    for (int i = 0; i < M; i++)
    {
        cout << "\n | Amostra " << i + 1 << "| " << endl;

        //Chama o orquestrador dos m�todos de ordena��o
        resultSort* results = Sort::ordenacao(n);

        //Monta o dataset de resultados
        listResult[i][0] = results[0];
        listResult[i][1] = results[1];
        listResult[i][2] = results[2];
    }

    // Escreve os resultados no txt
    writeOrdenacaoTxt(ARQ_SAIDA, listResult, M, n);

    // Escreve os resultados da media no txt
    writeMediaTxt(listResult);
}

void Menu::writeOrdenacaoTxt(string arquivo, resultSort data[][N_METHODS_SORT], int n, int m)
{

    ofstream arqSaida;
    arqSaida.open(arquivo, ios::app);

    if (arqSaida.is_open())
    {
        arqSaida << "Estatisticas dos metodos de ordenacao com " << m << " elementos:" << endl
            << endl;

        // Percorre amostra por amostra
        for (int i = 0; i < n; i++)
        {
            arqSaida << "Amostra " << i + 1 << ": " << endl;

            // Percorre cada metodo dentro de uma amostra
            for (int j = 0; j < N_METHODS_SORT; j++)
            {
                arqSaida << i + 1 << ". "
                    << data[i][j].tipo << ": "
                    << "Tempo de Execucao: "
                    << data[i][j].time_spent.count()
                    << "s - Numero de Comparacoes: "
                    << data[i][j].nCompare
                    << " - Numero de Trocas: "
                    << data[i][j].nSwap << endl;
            }

            arqSaida << endl;
        }

        arqSaida.close();
    }
    else
    {
        cout << "Erro ao abrir arquivo de sa�da!" << endl;
    }
}

void Menu::writeMediaTxt(resultSort data[][N_METHODS_SORT])
{
    ofstream arqSaida;
    arqSaida.open(ARQ_SAIDA, ios::app);

    if (arqSaida.is_open())
    {
        arqSaida << endl
            << "Media dos resultados:" << endl;

        for (int j = 0; j < N_METHODS_SORT; j++)
        {
            //Monta um vetor com os valores de um mesmo metodo
            resultSort data_type[3] = { data[0][j], data[1][j], data[2][j] };

            // Calcula a m�dia
            resultSort med = Sort::media(data_type, 3);
            arqSaida << j + 1 << ". "
                << med.tipo << ": "
                << "Tempo de Execucao: "
                << med.time_spent.count()
                << "s - Numero de Comparacoes: "
                << med.nCompare
                << " - Numero de Trocas: "
                << med.nSwap << endl;
        }

        arqSaida << endl;

        arqSaida.close();
    }
    else
    {
        cout << "Erro ao abrir arquivo de sa�da!" << endl;
    }
}

int Menu::readDat(string pathDat, int l){
    string line = "";
    string arquivo = pathDat + "input.dat";
    fstream arq;

    arq.open(arquivo, ios::out);
    
    int nDat = 0;

    if (arq.is_open())
    {
        arq.seekg(std::ios::beg);
        for(int i=0; i < l - 1; ++i){
            arq.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        getline(arq, line);
    }

    arq.close();
    
    return stoi(line);
}