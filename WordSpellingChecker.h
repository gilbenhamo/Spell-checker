#include "HashTable.h"
#define SIZE 40	//	max size of word

//	Suggestions struct definition
typedef struct SpellingSuggestion SpellingSuggestion;
struct SpellingSuggestion {
	char* originalWord;
	LinkedList  * suggestions;
	SpellingSuggestion* next;
};

// Mission functions
int isWordInDictionary(HashTable* dictionaryTable, char* word);						//	Check if the word is in the dictionary
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word);					//	Check for missing space between two characters
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word);			//	Check if one of the characters is incorrect
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word);			//	Check if there is an unnecessary signal
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word);				//	Check for a missing letter
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word);	//	Swap between any two adjacent characters
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word);				//	Add all the suggestions of the word
//int wordSpellingChecker(HashTable* dictionaryTable);	// Unnecessary

// Help functions
SpellingSuggestion* createSuggestion(HashTable* dictionaryTable, char* word);							//	Create a new suggestion
SpellingSuggestion* addSuggToStart(SpellingSuggestion* head, HashTable* dictionaryTable, char* word);	//	Create a new element and make him the head of the list.
int isInSuggestion(SpellingSuggestion* head, char* word);		//	Check if the suggestion is already inside
SpellingSuggestion* FreeSpellSugss(SpellingSuggestion* head);	//	Free the allocated memory