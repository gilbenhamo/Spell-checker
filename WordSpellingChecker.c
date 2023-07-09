#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"


int isWordInDictionary(HashTable* dictionaryTable, char* word)
{	// Check if the word is in the dictionary
	if (word == NULL || dictionaryTable==NULL)
		return 0;
	if (search(dictionaryTable, word))	// True if the word is in the table
		return 1;
	return 0;
}

LinkedList * addSpaceCheck(HashTable * dictionaryTable, char * word)
{// Check for missing space between two characters
	LinkedList* newSuggs = NULL;
	if (dictionaryTable == NULL || word == NULL)
		return newSuggs;
	char word1[SIZE], word2[SIZE], f_word[SIZE], spc[]=" ";
	int i, j, k;
	for (i = 1; i < strlen(word); i++)	// Run for all middle characters
	{
		// Create first and second word
		for (j = 0; j < i; j++)
			word1[j] = word[j];
		word1[j] = '\0';
		for (j = 0, k = i; j < strlen(word); j++,k++)
			word2[j] = word[k];
		word2[j] = '\0';
		//	Check if first word and second word are in the dictionary
		if (isWordInDictionary(dictionaryTable, word1) && isWordInDictionary(dictionaryTable, word2))
		{
			//	Add suggesion
			strcpy(f_word, word1);
			strcat(f_word, spc);
			strcat(f_word, word2);
			newSuggs = addToStart(newSuggs, f_word);
		}
	}
	return newSuggs;
}

LinkedList * replaceCharacterCheck(HashTable* dictionaryTable, char* word)
{// Check if one of the characters is incorrect
	LinkedList* newSuggs = NULL;
	if (dictionaryTable == NULL || word == NULL)
		return newSuggs;
	char temp[SIZE];
	strcpy(temp, word);
	for (int i = 0; i < strlen(temp); i++)	// Run for every letter
	{
		strcpy(temp, word);
		char r = 'a';	//first letter
		//	Switch every letter and check if in the dictionary
		for (int j = 0; j < 26; j++)
		{
			temp[i] = r;
			r++;
			if (isWordInDictionary(dictionaryTable, temp) && strcmp(temp,word)!=0)
				//	Add to suggestions
				newSuggs = addToStart(newSuggs, temp);
		}
		r = 'a';
	}
	return newSuggs;
}

LinkedList * deleteCharacterCheck(HashTable * dictionaryTable, char * word)
{// Check if there is an unnecessary signal
	LinkedList* newSuggs = NULL;
	if (dictionaryTable == NULL || word == NULL)
		return newSuggs;
	char deleted_word[SIZE];
	int i, j, k;
	for (i = 0; i < strlen(word); i++)
	{
		for (j = 0; j < i; j++) //	Copy charcaters until the charachter we want to delete
			deleted_word[j] = word[j];
		for (k = i+1; j < strlen(word);k++)// Copy characters afte the character we want to delete
			deleted_word[j++] = word[k];
		deleted_word[j] = '\0';
		if(isWordInDictionary(dictionaryTable, deleted_word))	//	Check if the word exsist in the dict
			newSuggs = addToStart(newSuggs, deleted_word);	// Add word to suggestions
	}
	return newSuggs;
}

LinkedList * addCharacterCheck(HashTable * dictionaryTable, char * word)
{// Check for a missing letter
	LinkedList* newSuggs = NULL;
	if (dictionaryTable == NULL || word == NULL)
		return newSuggs;
	char temp[SIZE];
	int i, j, k;
	for (i = 0; i < strlen(word)+1; i++)
	{
		strcpy(temp, word);	// Copy the original word
		char r = 'a';
		//	Run for every letter option
		while (r<='z')
		{
			for (j = 0; j < i; j++)	//	Run until the charachter we want to add
				temp[j] = word[j];
			temp[j++] = r;
			for (k = i; j < strlen(word)+1; k++)	// Run after the character we want to add
				temp[j++] = word[k];
			temp[j] = '\0';
			if (isWordInDictionary(dictionaryTable, temp))	//	Check if the word exsist in the dict
				newSuggs = addToStart(newSuggs, temp);		// Add word to suggestions
			r++;	//	Next letter
		}
	}
	return newSuggs;
}

LinkedList* switchAdjacentCharacterCheck(HashTable * dictionaryTable, char * word) //	Swap between any two adjacent characters 
{
	char temp[SIZE], c;
	int i;
	LinkedList* newSuggs = NULL;
	for (i = 0; i < strlen(word)-1; i++)	//	Run for every character except the last
	{	//	Swap current letter and next
		strcpy(temp, word);
		c = temp[i];
		temp[i] = temp[i + 1];
		temp[i + 1] = c;
		//	Check if the word exsist in the dictionary
		if (isWordInDictionary(dictionaryTable, temp) && strcmp(temp, word) != 0)
			newSuggs = addToStart(newSuggs, temp);
	}
	return newSuggs;
}

LinkedList* getWordSuggestions(HashTable * dictionaryTable, char * word)	
{//	Add all the suggestions of the word
	if (dictionaryTable == NULL || !strcmp(word, ""))	//	Emptey word or dictionary case
		return NULL;
	LinkedList* suggsList = NULL;
	suggsList = link_lists(suggsList, addSpaceCheck(dictionaryTable,word));
	suggsList = link_lists(suggsList, replaceCharacterCheck(dictionaryTable, word));
	suggsList = link_lists(suggsList, deleteCharacterCheck(dictionaryTable, word));
	suggsList = link_lists(suggsList, addCharacterCheck(dictionaryTable, word));
	suggsList = link_lists(suggsList, switchAdjacentCharacterCheck(dictionaryTable, word));
	suggsList = delete_doubles(suggsList);
	return suggsList;
}

SpellingSuggestion* createSuggestion(HashTable* dictionaryTable, char* word)
{//	Create a new suggestion
	SpellingSuggestion* node = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
	node->originalWord = (char*)malloc(strlen(word)+1);	//	Allocate memory
	strcpy(node->originalWord, word);	//	fill originalWord field
	node->suggestions = getWordSuggestions(dictionaryTable, word);	//	fill suggestions field
	node->next = NULL;
	return node;
}

SpellingSuggestion* addSuggToStart(SpellingSuggestion* head,HashTable* dictionaryTable, char* word)
{//	Create a new element and make him the head of the list.
	SpellingSuggestion* new_elem = createSuggestion(dictionaryTable,word);
	new_elem->next = head;
	return new_elem;
}

int isInSuggestion(SpellingSuggestion* head, char* word)
{//	Check if the suggestion is already inside
	SpellingSuggestion* temp = head;
	while (temp != NULL)
	{	//	Check if suggestion is already inside
		if (strcmp(temp->originalWord, word) == 0)
			return 1;
		temp = temp->next;
	}
	//	Not inside case
	return 0;
}

SpellingSuggestion * FreeSpellSugss(SpellingSuggestion * head)	//free the memory
{
	SpellingSuggestion *temp;
	while (head != NULL)
	{	//	Free every element
		free(head->originalWord);
		FreeList(head->suggestions);
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}
