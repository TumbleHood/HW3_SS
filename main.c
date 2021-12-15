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

    printf("Gematria Squence: ");
    printGematria(word, text);
    printf("\nAtbash Sequence: ");
    printAtbash(word, text);
    printf("\nAnagram Seqcuence: ");
    printAnagram(word, text);

    return 0;
}