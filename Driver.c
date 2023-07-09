#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"

const char path[] = "C:/ds4Words/dictionary.txt";	//	Dictionary path
// !!!! before running the program change the path of the dcitionary.txt
//      in SpellingCheck function, to your own path !!!!!!


//	Mission functions
int parseWordsToTable(char* path, HashTable* ht);	//	Take words from the file
SpellingSuggestion* spellingCheck(char* text);		//	Check if the word is spelling well

//	Help functions
void printSuggestions(SpellingSuggestion* suggest_list);	//	Print all suggestions

int main()
{
	char text[] = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion* text_suggestions = spellingCheck(text);
	printSuggestions(text_suggestions);
	text_suggestions = FreeSpellSugss(text_suggestions);

	return 0;
}

int parseWordsToTable(char* path, HashTable* ht)	//	Take words from the file
{
	if (path == NULL || ht == NULL)
		return 0;
	char temp[SIZE];
	FILE *words;
	int count = 0;
	words = fopen(path, "r"); // Open dictionary file
	if (words == NULL )
	{//	Check if can open the file
		printf("ERROR! Could not open the file!\n");
		return 0;
	}
	fscanf(words, "%s\n", temp);	//	Take first word
	while (!feof(words))
	{//	Run for every word in the file
		insert(ht, temp);			//	Add him
		fscanf(words, "%s", temp);	//	Next word
		
	}
	fclose(words);	//	Close file
	return 1;
}

SpellingSuggestion* spellingCheck(char * text)
{//	Check if the word is spelling well
	SpellingSuggestion* suggestions = NULL;
	if (!strcmp(text, "") || text == NULL)
		return suggestions;

	HashTable* dictionary = initTable(1000, 3);	//	Create the hash table with function number 3 and 1000 cells
	parseWordsToTable(path, dictionary);		//	Take words from the file

	int i=0,j=0;
	char word[SIZE];
	while (text[i] != '\0')
	{//	Run for the whole text
		while (text[i] != ' ' && text[i] !='\0')
			word[j++] = text[i++];
		word[j] = '\0';
		j = 0;
		if(text[i]!='\0')	//jump, for not taking the spaces
			i++;
		if (!isWordInDictionary(dictionary, word) && !isInSuggestion(suggestions,word))
			//	Check if need a suggestions
			suggestions = addSuggToStart(suggestions, dictionary, word);
	}
	dictionary = FreeHashTable(dictionary);		//	Free the memory allcoatiobns
	return suggestions;
}

void printSuggestions(SpellingSuggestion* suggest_list)
{//	Print all suggestions
	SpellingSuggestion* temp = suggest_list;
	if (temp == NULL)
		printf("The suggestions are empty!\n");
	while (temp != NULL)
	{//	Print the relevant word
		printf("The word \"%s\" was misspeled.", temp->originalWord);
		if (temp->suggestions == NULL)
			//	No suggestions case
			printf(" No suggestions found for this word.\n\n");
		else
		{//	Print relevant suggestions
			printf(" Did you mean:\n");	
			PrintList(temp->suggestions);
		}
		printf(", ");
		temp = temp->next;
	}
}
