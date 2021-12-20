#include "../include/Hash.h"

//Inicializa��o dos atributos 
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

//Primeira fun��o hash auxiliar
int Hash::h1(int k)
{
	return k % this->m1;
}

//Segunda fun��o hash auxiliar
int Hash::h2(int k)
{
	return 1 + (k % this->m2);
}

/* Principal fun��o hash: Retorna a posi��o de inser��o para a chave OU -1 caso 
   a chave j� exista na tabela, al�m de acrescentar 1 a repeticao de review
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

/* Fun��o de inser��o principal que decide se a inser��o pode acontecer normalmente,
   se charma a fun��o auxiliar de inser��o (inserOtherPosition) ou ignora o review (repetido)
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

//Fun��o auxiliar de inser��o que tenta encontrar uma posi��o v�lida na tabela
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

// Fun��o que verifica o char e o converte de string para inteiro
int Hash::stringToInt(string k)
{
	int k_int = 0;
	k.erase(remove(k.begin(), k.end(), '.'), k.end());
	k_int = stoi(k);
	return k_int;
}


//Fun��o que verifica se a tabela tem espa�o para inser��o
bool Hash::empty()
{
	if (current_size == m1)
		return false;
	return true;
}

//Fun��o que imprime somente as posi��es preenchidas, pois a tabela � sempre maior que o n�mero de posi��es ocupadas
void Hash::print()
{
	for (int i = 0; i < this->m1; i++)
	{
		if (table[i].app_version != "")
			cout << "Linha " << i << " = " << table[i].app_version << endl;
	}
	cout << "current size = " << current_size << endl;
}

//Fun��o que retorna o primeiro n�mero primo no intervalo
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
		/* value � primo */
		if (dividers == 0)
		{
			break;
		}
	}
	return value;
}

//Fun��o para determinar reviews mais frequentes por meio dos dados separados
void Hash::mostPopularReviews(int M)
{
	vector<hashTable> tableAux;
	tableAux = table;
	sortTable(tableAux, 0, (tableAux.size() - 1));

	for (int i = 0; i < M; i++)
	{
		cout << "As " << M << "vers�es mais frequentes do aplicativo, em ordem decrescente s�o: " << endl;
		sortTable(table.app_version, 0, table.size);
		sortTable(table.rpt, 0, table.size);
	}

}

//Fun��o auxiliar de Troca par 2 hashTables
void swap(hashTable* a, hashTable* b)
{
	hashTable t = *a;
	*a = *b;
	*b = t;
}

//Fun��o recursiva que manipula a tabela 
void sortTable(vector<hashTable> table, int beg, int end)
{
	if (beg < end) {

		int pi = repartTab(table, beg, end);

		sortTable(table, beg, pi - 1);
		sortTable(table, pi + 1, end);
	}

}

//Fun��o para particionar uma Tablea Hash
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