#include "../include/Hash.h"

//Inicialização dos atributos 
Hash::Hash(int m1, int m2)
{
	this->m1 = m1;
	this->m2 = m2;
	current_size = 0;

	for (int i = 0; i < m1; i++)
	{
		hashTable item;
		item.app_version = "";
		item.rpt = 0;
		table.push_back(item);
	}
}

//Primeira função hash auxiliar
int Hash::h1(int k)
{
	return k % this->m1;
}

//Segunda função hash auxiliar
int Hash::h2(int k)
{
	return 1 + (k % this->m2);
}

/* Principal função hash: Retorna a posição de inserção para a chave OU -1 caso 
   a chave já exista na tabela, além de acrescentar 1 a repeticao de review
*/
int Hash::h(int int_k, string k)
{
	if (!empty())
	{
		cout << "Tabela Cheia, encerrando Hash..." << endl;
		exit(2);
	}

	int hash1 = h1(int_k);
	int result = hash1;
	int i = 0, verify = 0, count = 0;

	verify = (hash1 + h2(int_k)) % m1;

	while (table[result % m1].app_version != "")
	{
		i++;
		if (table[result % m1].app_version == k)
		{
			table[result % m1].rpt++;
			return -1;
		}

		int hash2 = h2(int_k);
		if (m1 % hash2 == 0)
			break;

		result = hash1 + (i * hash2);
		if (verify == result){
			count++;
			if (count > 2){
				cout << "ERRO! Indices se repetem!" << endl;
			}
		}
	}
	return result % m1;
}

/* Função de inserção principal que decide se a inserção pode acontecer normalmente,
   se charma a função auxiliar de inserção (inserOtherPosition) ou ignora o review (repetido)
*/
void Hash::insert(string k)
{
	int int_k = stringToInt(k);
	int index = h(int_k, k);
	
	if (index == -1)
		return;

	string test = table[index].app_version;

	if (test == "")
	{
		table[index].app_version = k;
		current_size++;
	}
	else
		insertOtherPosition(k);
}

//Função auxiliar de inserção que tenta encontrar uma posição válida na tabela
void Hash::insertOtherPosition(string k)
{
	int k_int = stringToInt(k);
	int index = 0;
	for (int j = 1; j < 5; j++)
	{
		index = h(k_int / j, k);
		if (index == -1)
			break;

		string test = table[index].app_version;

		if (test == "")
		{
			table[index].app_version = k;
			current_size++;
			j = 5;
		}
	}
}

// Função que verifica o char e o converte de string para inteiro
int Hash::stringToInt(string k)
{
	int k_int = 0;
	k.erase(remove(k.begin(), k.end(), '.'), k.end());
	k_int = stoi(k);
	return k_int;
}


//Função que verifica se a tabela tem espaço para inserção
bool Hash::empty()
{
	if (current_size == m1)
		return false;
	return true;
}

//Função que imprime somente as posições preenchidas, pois a tabela é sempre maior que o número de posições ocupadas
void Hash::print()
{
	for (int i = 0; i < this->m1; i++)
	{
		if (table[i].app_version != "")
			cout << "Linha " << i << " = " << table[i].app_version << endl;
	}
	cout << "current size = " << current_size << endl;
}

//Função que retorna o primeiro número primo no intervalo
int Hash::calcPrime(int min, int max)
{
	int range = max;
	int dividers = 0;
	int value = 0;

	for (value = min; value <= range; value++)
	{
		dividers = 0;

		for (int i = 2; i <= sqrt(value); i++)
		{
			if (value % i == 0)
				dividers++;
		}
		/* value é primo */
		if (dividers == 0)
		{
			break;
		}
	}
	return value;
}

//Função para determinar reviews mais frequentes por meio dos dados separados
void Hash::mostPopularReviews(int M)
{
	vector<hashTable> tableAux;
	tableAux = table;
	sortTable(tableAux, 0, (tableAux.size() - 1));

	for (int i = 0; i < M; i++)
	{
		cout << "As " << M << "versões mais frequentes do aplicativo, em ordem decrescente são: " << endl;
		sortTable(table.app_version, 0, table.size);
		sortTable(table.rpt, 0, table.size);
	}

}

//Função auxiliar de Troca par 2 hashTables
void swap(hashTable* a, hashTable* b)
{
	hashTable t = *a;
	*a = *b;
	*b = t;
}

//Função recursiva que manipula a tabela 
void sortTable(vector<hashTable> table, int beg, int end)
{
	if (beg < end) {

		int pi = repartTab(table, beg, end);

		sortTable(table, beg, pi - 1);
		sortTable(table, pi + 1, end);
	}

}

//Função para particionar uma Tablea Hash
int repartTab(vector<hashTable> sortedTable, int beg, int end)
{
	int pivo = sortedTable[end].rpt; // pivo
	int i = (beg - 1); // Index do menor elemento e indica a posicao correta do pivo atual

	for (int j = beg; j <= end - 1; j++)
	{

		// Se elemento atual menor que pivo
		if (sortedTable[j].rpt > pivo)
		{
			i++; // incrementa index do menor elemento
			swap(&sortedTable[i], &sortedTable[j]);
		}
	}
	swap(&sortedTable[i + 1], &sortedTable[end]);
	return (i + 1);

}