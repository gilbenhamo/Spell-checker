#include <conio.h>
#include <math.h>
#include "LinkedList.h"
#define _CRT_SECURE_NO_WARNINGS

//	Element struct definition
typedef struct HashTableElement HashTableElement;
struct HashTableElement
{
	int key;
	LinkedList* chain;
};

//	Hash Table struct definition
typedef struct HashTable HashTable;
struct HashTable
{
	HashTableElement* hashTable;
	int hashFunction;
	int tableSize;
	int cellsTaken;
	int numOfElements;
};

//	Mission functions
int constantStringHashFunction(char* str);		//	Return 3 for every input
int accumulateStringHashFunction(char* str);	//	Return sum of acci table values
int improvedHashFunction(char* str);			//	Return Calculation by the formula - (Σstr[𝑖] ∗ 31𝑛−1−𝑖)

int hash(char* str, HashTable* ht);						//	Get the index we want to store the word
HashTable* initTable(int tableSize, int hashFunction);	//	Init the hash table
int insert(HashTable* ht, char* str);					//	Insert the word in the table
int deleteElement(HashTable* ht, char* str);			//	Delete specific element from the table
int search(HashTable* ht, char* str);					//	Search for the word in the table


//	Help functions
HashTableElement* buildElemArr(int size);	//	Build a element in the table
HashTable* FreeHashTable(HashTable* ht); // Free the pointers





























