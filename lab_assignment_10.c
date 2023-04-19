#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In this lab, you are going to implement a trie data structure to count the number of occurrences of a word if it exists in the dictionary. Words will always be in lowercase.
// Please apply the following signatures:

// void insert(struct Trie **ppTrie, char *word);
// int numberOfOccurances(struct Trie *pTrie, char *word);
// struct Trie *deallocateTrie(struct Trie *pTrie);

struct Trie 
{
    int wordCount;
    struct Trie *next[26];
};

void insert(struct Trie **ppTrie, char *word)
{
    if (ppTrie == NULL || word == NULL)
        return;
        
    if (*ppTrie == NULL)
    {
        // Create new Trie if none exist
        struct Trie *newTrie = malloc(sizeof(struct Trie));
        newTrie->wordCount = 0;

        for (int i = 0; i < 26; i++)
            newTrie->next[i] = NULL;

        *ppTrie = newTrie;
    }

    struct Trie *cur = *ppTrie;

    // Insert word into trie
    for (int i = 0; i < strlen(word); i++)
    {
        // If character is not initialized, create new sub trie
        if (cur == NULL || cur->next[word[i] - 'a'] == NULL)
        {
            // Create new Trie and initialize values
            struct Trie *childTrie = malloc(sizeof(struct Trie));
            childTrie->wordCount = 0;
            for (int i = 0; i < 26; i++)
                childTrie->next[i] = NULL;

            cur->next[word[i] - 'a'] = childTrie;
        }
        cur = cur->next[word[i] - 'a'];
    }

    // If last character add one to word count
    cur->wordCount++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL || word == NULL)
        return 0;

    struct Trie *cur = pTrie;

    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        
        if (cur->next[index] == NULL)
            return 0;
        cur = cur->next[index];
    }
    return cur->wordCount;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; i++)
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);
    
    free(pTrie);
    return NULL;
}

int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    struct Trie *trie = NULL;
    int wordsLen = 5;

    for (int i=0;i<wordsLen;i++)
        insert(&trie, pWords[i]);

    for (int i=0;i<wordsLen;i++)
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    
    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}