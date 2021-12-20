#include "../include/Menu.h"

void Menu::iniciar()
{
    int opt;
    system("clear");
menu:
    cout << "\n| ----- Menu Principal ------ |" << endl
        << endl
        << "Selecione uma opção para continuar: " << endl
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
        hash();
        break;

    case 3:
        modTeste();
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
menu:
    cout << "\n| --- Menu de Ordenacao --- |\n\n"
        << "Digite a quantidade de elementos para serem ordenados: \n\n"
        << "1 - 10.000\n2 - 50.000\n3. 100.000\n4 - 500.000\n5 - 1.000.000\n0 - Sair\n\n>> ";
    cin >> opt;

    switch (opt)
    {
    case 1:
        gerenciaOrdenacao(10000);
        break;
    case 2:
        gerenciaOrdenacao(50000);
        break;
    case 3:
        gerenciaOrdenacao(100000);
        break;
    case 4:
        gerenciaOrdenacao(500000);
        break;
    case 5:
        gerenciaOrdenacao(1000000);
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
    //Quantidade de amostras utilizadas para calcular o resultado dos metodos de ordenação
    int M = 3;

    resultSort listResult[3][N_METHODS_SORT];

    for (int i = 0; i < M; i++)
    {
        cout << "\n | Amostra " << i + 1 << "| " << endl;

        //Chama o orquestrador dos métodos de ordenação
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
        cout << "Erro ao abrir arquivo de saída" << endl;
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

            // Calcula a média
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
        cout << "Erro ao abrir arquivo de saída" << endl;
    }
}