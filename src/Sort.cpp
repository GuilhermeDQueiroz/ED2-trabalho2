#include "../include/Sort.h"

//Utilidades
void copyArr(int n, Review* data, Review* rev1, Review* rev2)
{
    //Faz a copia de vetores (amostra)
    for (int i = 0; i < n; i++)
    {
        rev1[i] = data[i];
        rev2[i] = data[i];
    }
}

resultSort Sort::media(resultSort data[], int n_itens)
{
    // Inicia o retorno com valores padrões para evitar bugs de resultado
    resultSort response = {
      tipo: data[0].tipo,
      nCompare : 0,
      nSwap : 0,
      time_spent : duration<double>()
    };

    //Calcula a media dos resultados passados
    for (int i = 0; i < n_itens; i++)
    {
        response.nCompare += data[i].nCompare;
        response.nSwap += data[i].nSwap;
        response.time_spent += data[i].time_spent;
    }

    response.nCompare = response.nCompare / n_itens;
    response.nSwap = response.nSwap / n_itens;
    response.time_spent = response.time_spent / n_itens;

    return response;
}

///// SORT /////

void Sort::selectionSort(Review reviews[], int n, double* nSwap, double* nCompare)
{
    *nSwap = 0;
    *nCompare = 0;

    //Percorre todos os itens
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        //Compara o item de menor indice no momento com os demais de maior indice
        for (int j = i + 1; j < n; j++)
        {

            *nCompare = *nCompare + 1;

            // Compara os valores afim de realizar ou não a troca
            if (reviews[j].upvotes < reviews[minIndex].upvotes)
            {
                minIndex = j;
            }
        }

        swap(&reviews[minIndex], &reviews[i], nSwap);
    }
}

void Sort::swap(Review* item1, Review* item2, double* numSwap)
{
    //Faz a troca dos elementos
    Review aux = *item1;
    *item1 = *item2;
    *item2 = aux;
    *numSwap = *numSwap + 1;
}

/**
Ordenacao dos elementos de um vetor utilizando o QuickSort.
**/
void Sort::quickSort(Review reviews[], int inicio, int fim, double* nSwap, double* nCompare)
{
    if (inicio < fim)
    {

        int divisao = particao(reviews, inicio, fim, nSwap, nCompare);

        quickSort(reviews, inicio, divisao - 1, nSwap, nCompare);
        quickSort(reviews, divisao + 1, fim, nSwap, nCompare);
    }
}

int Sort::particao(Review reviews[], int inicio, int fim, double* nSwap, double* nCompare)
{
    Review pivo = reviews[fim];  // pivo
    int minIndex = (inicio - 1); // Menor indice

    for (int j = inicio; j <= fim - 1; j++)
    {
        *nCompare = *nCompare + 1;
        if (reviews[j].upvotes < pivo.upvotes)
        {
            minIndex++;
            swap(&reviews[minIndex], &reviews[j], nSwap);
        }
    }
    swap(&reviews[minIndex + 1], &reviews[fim], nSwap);
    return (minIndex + 1);
}

void Sort::heapify(Review reviews[], int n, int i, double* nSwap, double* nCompare)
{
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    *nCompare = *nCompare + 1;
    if (esq < n && reviews[esq].upvotes > reviews[maior].upvotes)
    {
        maior = esq;
    }

    *nCompare = *nCompare + 1;
    if (dir < n && reviews[dir].upvotes > reviews[maior].upvotes)
    {
        maior = dir;
    }

    *nCompare = *nCompare + 1;
    if (maior != i)
    {
        swap(&reviews[i], &reviews[maior], nSwap);

        heapify(reviews, n, maior, nSwap, nCompare);
    }
}

void Sort::heapSort(Review reviews[], int n, double* nSwap, double* nCompare)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(reviews, n, i, nSwap, nCompare);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&reviews[0], &reviews[i], nSwap);

        heapify(reviews, i, 0, nSwap, nCompare);
    }
}

resultSort* Sort::ordenacao(int m)
{
    int n = m;
    Timer timer = Timer();
    resultSort* results = new resultSort[4];

    cout << "\nBuscando " << n << " registros" << endl;
    Review* rev1 = Review::readBinaryN(n);
    Review* rev2 = new Review[n];
    Review* rev3 = new Review[n];

    cout << "Copiando amostra" << endl;

    //Copia as amostras para manter a equivalencia dos testes
    copyArr(n, rev1, rev2, rev3);

    cout << "\nIniciando ordenacao:" << endl;
    double nCompare, nSwap;

    //SelectionSort
    cout << "1 - SelectionSort" << endl;
    nCompare = 0;
    nSwap = 0;
    timer.start();
    Sort::selectionSort(rev1, n, &nSwap, &nCompare);
    resultSort result_selectionSort = {
      tipo: "SelectionSort",
      nCompare : nCompare,
      nSwap : nSwap,
      time_spent : timer.stop()
    };

    //HeapSort
    cout << "2 - HeapSort" << endl;
    nCompare = 0;
    nSwap = 0;
    timer.start();
    Sort::heapSort(rev2, n - 1, &nSwap, &nCompare);
    resultSort result_heapSort{
      tipo: "HeapSort",
      nCompare : nCompare,
      nSwap : nSwap,
      time_spent : timer.stop()
    };

    //QuickSort
    cout << "3 - QuickSort" << endl;
    nCompare = 0;
    nSwap = 0;
    timer.start();
    Sort::quickSort(rev3, 0, n - 1, &nSwap, &nCompare);
    resultSort result_quickSort{
      tipo: "QuickSort",
      nCompare : nCompare,
      nSwap : nSwap,
      time_spent : timer.stop()
    };

    //
    results[0] = result_selectionSort;
    results[1] = result_heapSort;
    results[2] = result_quickSort;

    delete[] rev1;
    delete[] rev2;
    delete[] rev3;

    return results;
}