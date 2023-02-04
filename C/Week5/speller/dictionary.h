// Implement a program that describes dictionary' functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Set the value for the maximum length a given word can have
#define LENGTH 45

// Include the prototypes for the functions implemented in dictionary.c
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H