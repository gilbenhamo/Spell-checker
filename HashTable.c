#include "HashTable.h"
#define _CRT_SECURE_NO_WARNINGS

int constantStringHashFunction(char * str)
{//	Return 3 for every input
	return 3;
}

int accumulateStringHashFunction(char * str)
{//	Return sum of acci table values	
	if (str==NULL)
		return 0;
	int sum = 0;
	//	Calculation
	for (int i = 0; str[i] != '\0'; i++)
		sum += (int)str[i];
	return sum;
}

int improvedHashFunction(char* str)
{//	Return ∑(str[𝑖] ∗ 31𝑛−1−𝑖)
	if (str == NULL)
		return 0;
	int size = strlen(str);
	int sum = 0;
	//	Calculation
	for (int i = 0; i < size; i++)
		sum += str[i] * (int)pow(31, size - 1 - i);
	return sum;
}

int hash(char* str, HashTable* ht)
{//	Get the index we want to store the word
	int index, hashRes;
	if (ht->hashFunction == 1)
		hashRes = constantStringHashFunction(str);
	else if (ht->hashFunction == 2)
		hashRes = accumulateStringHashFunction(str);
	else 
		hashRes = improvedHashFunction(str);
	index = abs(hashRes) % ht->tableSize;	//	Get the absulute value
	return index;
}

HashTable* initTable(int tableSize, int hashFunction)
{//	Init the hash table
	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));	//	Allocate memory
	ht->hashFunction = hashFunction;
	ht->tableSize = tableSize;
	ht->hashTable = buildElemArr(tableSize);
	ht->numOfElements = 0;
	ht->cellsTaken = 0;
	return ht;
}

int insert(HashTable* ht, char* str)
{//	Insert the word in the table
	if (str == NULL)
		return 0;
	char *temp = (char*)malloc(strlen(str)+1);	//	Allocate word memory
	strcpy_s(temp, strlen(str) + 1, str);
	int index = hash(temp, ht);
	if(isInList(ht->hashTable[index].chain, temp))	//	Check if the word is already in list
		return 0;
	else
	{
		if(ht->hashTable[index].chain==NULL)
			//	Increase cellsTaken
			ht->cellsTaken++;
		//	Add the word to the table and Increase numOfElement
		ht->hashTable[index].chain = addToStart(ht->hashTable[index].chain, temp);
		ht->numOfElements++;
		return 1;
	}
}

int deleteElement(HashTable * ht, char * str)
{//	Delete specific element from the table
	if (str == NULL)
		return 0;
	int index = hash(str, ht);
	if (!(isInList(ht->hashTable[index].chain, str)))
		//	If the word isn't in the list
		return 0;
	else
	{
		ht->hashTable[index].chain = DeleteElement(ht->hashTable[index].chain, str); //	Delete with capital d is linked list func
		ht->numOfElements--;	//	Decrease numOfElement
		if (ht->hashTable[index].chain == NULL)
			ht->cellsTaken--;	//	Decrease cellsTaken
		return 1;
	}
}

int search(HashTable* ht, char* str)
{//	Search for the word in the table
	if (str == NULL)
		return 0;
	int index = hash(str, ht);
	if (isInList(ht->hashTable[index].chain, str))
		//	Found case
		return 1;
	else
		return 0;
}

//	Help functions
HashTableElement* buildElemArr(int size)
{//	Build a elements arr in the table
	HashTableElement* hte = (HashTableElement*)malloc(size * sizeof(HashTableElement));	//	Allocate memory
	for (int i = 0; i < size; i++)
	{
		hte[i].key = i;
		hte[i].chain = NULL;
	}
	return hte;
}

HashTable* FreeHashTable(HashTable * ht)
{
	//HashTable* temp;
	for (int i = 0; i < ht->tableSize; i++) 
		FreeList(ht->hashTable[i].chain);
	free(ht->hashTable);
	return NULL;
}
