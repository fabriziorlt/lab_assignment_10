#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie
{
    struct Trie* children[ALPHABET_SIZE];
    int count;
};

// Initializes a trie structure
struct Trie *createTrie() 
{
    struct Trie* node = malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) 
{
    struct Trie* crawl = pTrie;
    while (*word) {
        int index = *word - 'a';
        if (!crawl->children[index]) {
            crawl->children[index] = createTrie();
        }
        crawl = crawl->children[index];
        word++;
    }
    crawl->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* crawl = pTrie;
    while (*word) {
        int index = *word - 'a';
        if (!crawl->children[index]) {
            return 0;
        }
        crawl = crawl->children[index];
        word++;
    }
    return crawl->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie *pTrie)
{
    if (pTrie) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (pTrie->children[i]) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
        return NULL;
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        return 0;
    }

    int numWords;
    fscanf(file, "%d", &numWords);

    for (int i = 0; i < numWords; i++) {
        pInWords[i] = malloc(100 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char* inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
