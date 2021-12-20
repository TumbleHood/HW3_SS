#include "my_mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD 30
#define TEXT 1024

int main(void){

    char text[TEXT];
    char word[WORD];
    readWord(word);
    readText(text);

    printf("Gematria Squences: ");
    printGematria(word, text);
    printf("\nAtbash Sequences: ");
    printAtbash(word, text);
    printf("\nAnagram Seqcuences: ");
    printAnagram(word, text);

    return 0;
}
