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
        /* code */
        gerenciaOrdenacao(10000);
        break;
    case 2:
        /* code */
        gerenciaOrdenacao(50000);
        break;
    case 3:
        /* code */
        gerenciaOrdenacao(100000);
        break;
    case 4:
        /* code */
        gerenciaOrdenacao(500000);
        break;
    case 5:
        /* code */
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
/*
void Menu::hash()
{
    // numero de musicas
    int N = 10000;

    int m = Hash::calcPrime((N * 1.5), (N * 2));
    Hash hash(m, m - (N * 0.1));
    Track* dataHash = Track::readBinaryN(N);

    for (int j = 0; j < N; j++)
        hash.insert(dataHash[j].id_artists);

    //hash.print();
    cout << "insercoes no hash ->" << hash.current_size << endl
        << endl;

    //Artistas mais frequentes e suas músicas 
    int M = 0;

    cout << "Digite M para imprimir os artistas mais frequentes: ";
    cin >> M;
    Artist* frequents = hash.artistsMostFrequent(M);
    hash.popularTracks(frequents, M);

    // usar ordenação para o vector hash.table na variável hash.table.at(i).repeat 

    // data -> vetor de Artist -> Hash::artistsMostFrequent(Artist *data) 

    // imprimir os M artistas com maior repeat de data 
}

void Menu::modTeste()
{
    //Define o tamanho do teste de ordenação
    int n = 100;
    system("clear");
    cout << "\n--- Modulo de teste ---" << endl
        << endl;

    //Realiza a ordenação
    resultSort* results = Sort::ordenacao(n);

    //Monta o dataset do resultado
    resultSort data[1][N_METHODS_SORT] = { results[0], results[1], results[2] };

    //Escreve o reultado no txt de teste
    writeOrdenacaoTxt("Teste.txt", data, 1, n);

    cout << "Os teste dos metodos de ordenacao foram realizados\n"
        << endl;

    ofstream arqSaida;
    arqSaida.open("Teste.txt", ios::app);

    if (arqSaida.is_open())
    {

        int N = 1000;
        int m = Hash::calcPrime((N * 1.5), (N * 2));
        Hash hash(m, m - (N * 0.1));
        Track* dataHash = Track::readBinaryN(N);

        for (int j = 0; j < N; j++)
            hash.insert(dataHash[j].id_artists);

        //hash.print();
        arqSaida << "insercoes no hash ->" << hash.current_size << endl
            << endl;

        // busca os 10 artistas mais frequentes 
        Artist* txtFrequent = hash.artistsMostFrequent(20);

        // busca os 10 artistas mais frequentes 
        arqSaida << "Os 20 artistas mais frequentes: " << endl;

        for (int i = 0; i < 20; i++)
            arqSaida << "nome: " << txtFrequent[i].name << endl;
    }*/
//}