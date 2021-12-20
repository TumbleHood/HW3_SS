#include "my_mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD 30
#define TEXT 1024
#define true 1
#define false 0

void readWord(char* word){
    //reads user input into the word variable
    char c;
    int i = 0;

    // if the word doesn't contain a blank character, and if it doesn't surpass the word length limit.
    while((c = getchar()) != ' ' && c != '\t' && c != '\n' && i < WORD)
        word[i++] = c;

}

void readText(char* text){
    //reads user input into the text variable
    char c;
    int i = 0;

    //continue reading until the user inputted "~" or if we surpassed the text length limit
    while((c = getchar()) != '~' && i < TEXT)
        text[i++] = c;

}

int calcGematria(char str[]){
    //calculates the gematria value of a string
    int value = 0;

    for(int i = 0; i < strlen(str); i++){
        if((int)str[i] >= (int)'a' && (int)str[i] <= (int)'z'){//if the current char is between lowercase a and z
            value += (int)str[i] - (int)'a' + 1;
        }
        else if((int)str[i] >= (int)'A' && (int)str[i] <= (int)'Z'){//if the current char is between uppercase a and z
            value += (int)str[i] - (int)'A' + 1;
        }
    }
    
    return value;
}

void calcAtbash(char* str, char* dest){
    //puts the word in atbash at variable "dest" from the word in "str"
    for(int i = 0; i < strlen(str); i++){
        if ((int)str[i] >= (int)'a' && (int)str[i] <= (int)'z'){//if the current char is between lowercase a and z
            dest[i] = (char)((int)'z' - (int)str[i] + (int)'a');// atbash lowercase characted = z - char + a
        }
        else if((int)str[i] >= (int)'A' && (int)str[i] <= (int)'Z'){//if the current char is between uppercase a and z
            dest[i] = (char)((int)'Z' - (int)str[i] + (int)'A');// atbash uppercase character = Z - char + A
        }
    }
    dest[strlen(str)] = '\0';
}

int calcContaintsAtbash(char a[], char b[]){
    //checks if string "a" contains string "b"
    int ctr = 0;
    
    //count how many non-blank characted are in string "a"
    for(int i = 0; i < strlen(a); i++){
        if(a[i] != ' ' && a[i] != '\t' && a[i] != '\n')
            ctr++;
    }

    //create a new string only from the non-blank characters in "a"
    char temp[ctr];

    ctr = 0;
    for(int i = 0; i < strlen(a); i++){
        if(a[i] != ' ' && a[i] != '\t' && a[i] != '\n')
            temp[ctr++] = a[i];
    }
    temp[ctr] = '\0';

    //if the length of the strings is not equal, "a" cant contain "b"
    if(strlen(temp) != strlen(b)){
        return false;
    }

    int canBeForwards = true;
    //check if the string "a" is equal to "b" forwards
    for(int i = 0; i < strlen(temp) && canBeForwards; i++){
        if(temp[i] !=  b[i])
            canBeForwards = false;
    }

    if(canBeForwards)
        return true;

    //if "a" is not equal to "b" forwards, check backwards
    for(int i = 0; i < strlen(temp); i++){
        if(temp[i] !=  b[strlen(b)-1 -i ])
            return false;
    }

    return true;
}

int isMinimalGematria(char str[]){
    //check if the string starts and ends or a letter
    if((((int)str[0] >= (int)'a' && (int)str[0] <= (int)'z') || ((int)str[0] >= (int)'a' && (int)str[0] <= (int)'z')) &&
    (((int)str[strlen(str)-1] >= (int)'a' && (int)str[strlen(str)-1] <= (int)'z') || ((int)str[strlen(str)-1] >= (int)'a' && (int)str[strlen(str)-1] <= (int)'z')))
        return true;
    return false;
}

int isMinimal(char str[]){
    //checks if the string doesn't start or end in a blank character
    if(str[0] != ' ' && str[0] != '\t' && str[0] != '\n' && str[strlen(str)-1] != ' ' && str[strlen(str)-1] != '\t' && str[strlen(str)-1] != '\n')
        return true;
    return false;
}

int isAnagram(char a[], char b[]){
    //checks if string "a" is an anagram of string "b"
    int ctr = 0;
    
    for(int i = 0; i < strlen(a); i++){
        if(a[i] != ' ' && a[i] != '\t' && a[i] != '\n')
            ctr++;
    }

    //createa new string only from the non-blank characters in string "a"
    char temp[ctr];

    ctr = 0;
    for(int i = 0; i < strlen(a); i++){
        if(a[i] != ' ' && a[i] != '\t' && a[i] != '\n')
            temp[ctr++] = a[i];
    }
    temp[ctr] = '\0';

    //if the length of temp is different from the length of b, they can't be anagrams of each other
    if(strlen(temp) != strlen(b)){
        return false;
    }

    //there are 256 different characters. if the amount of appearances of each character in the strings is equal, they are anagrams of each other
    int aChars[256] = {0}, bChars[256] = {0};

    for(int i = 0; i < strlen(b); i++){
        aChars[(int)temp[i]]++;
        bChars[(int)b[i]]++;
    }

    //check if the amounts are equal
    for(int i = 0; i < 256; i++){
        if(aChars[i] != bChars[i])
            return false;
    }
    
    return true;
}

void printGematria(char* word, char* text){
    //goes over all possible substrings in the text and prints the ones that their gematria value is equal to the gematria value of the word
    int value = calcGematria(word);
    int isFirst = true;

    for(long i = 0; i < strlen(text); i++){
        for(long j = 0; j < strlen(text); j++){
            char temp[strlen(text)];
            memcpy(temp, text + i, sizeof(char) * (j + 1));
            temp[j+1] = '\0';
            if(isMinimalGematria(temp) && calcGematria(temp) == value){
                if(isFirst){
                    printf("%s", temp);
                    isFirst = false;
                }
                else{
                    printf("~%s", temp);
                }
            }
        }
    }
}

void printAtbash(char* word, char* text){
    //goes over all possible substrings in the text and prints the ones that contains the word in atbash, forwards or backwards
    char atbash[strlen(word)];
    calcAtbash(word, atbash);

    int isFirst = true;

    for(long i = 0; i < strlen(text); i++){
        for(long j = 0; j < strlen(text); j++){
            char temp[strlen(text)];
            memcpy(temp, text + i, sizeof(char) * (j + 1));
            temp[j+1] = '\0';
            if(isMinimal(temp) && calcContaintsAtbash(temp, atbash)){

                if(isFirst){
                    printf("%s", temp);
                    isFirst = false;
                }
                else{
                    printf("~%s", temp);
                }
            }
        }
    }
}

void printAnagram(char* word, char* text){
    //goes over all possible substrings in the text and prints the ones that are an anagram of the word
    int isFirst = true;

    for(long i = 0; i < strlen(text); i++){
        for(long j = 0; j < strlen(text); j++){
            char temp[strlen(text)];
            memcpy(temp, text + i, sizeof(char) * (j + 1));
            temp[j+1] = '\0';
            if(isMinimal(temp) && isAnagram(temp, word)){

                if(isFirst){
                    printf("%s", temp);
                    isFirst = false;
                }
                else{
                    printf("~%s", temp);
                }
            }
        }
    }
}