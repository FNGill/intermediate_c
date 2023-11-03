#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 50

/// Get secret word from file
int getWord(const char *filename, char *secretWord);


int main(void){
    char secretWord[MAX_LEN];
    
    int correctLetters = 0;
    // Error check for getting file
    if(!getWord("words.words", secretWord)){
        perror("Error in main, did not get words.words\n");
    }

    int wordLen = strlen(secretWord);
    char guessed[wordLen];
    int attempts = 6 + wordLen;
    for (int i =0; i < wordLen; i++) {
        guessed[i] = '_'; 
    }
    char letter;
    while (attempts > 0 && correctLetters < wordLen) {
        printf("Secret Word: %s\n", guessed);
        printf("Attempts left: %d\n", attempts);
        printf("Enter guess: \n");
        scanf(" %c", &letter);

   
    //bool correctGuess = false;
        for (int i = 0; i < wordLen; i++) {
            if (secretWord[i] == letter && guessed[i] == '_') {
                guessed[i] = letter;
               // correctGuess = true;
                correctLetters++;
            
            } 
        }
     attempts--;
    } // end of while loop
    if (correctLetters == wordLen) {
        printf("I think you've won\n");
    } else {
        printf("Either you lost or I'm the dumb one\n");
    }
    return 0;
}

/// Get secret word from file
int getWord(const char *filename, char *secretWord){
    FILE *fp = fopen(filename, "r");
        if(!fp){
            perror("File did not open in getWord func.\n");
            exit(EXIT_FAILURE);
        }
// Count num of words for error handlings
    int w_count = 0;
    char words[MAX_LEN][MAX_LEN];
        while (fgets(words[w_count], MAX_LEN, fp) != NULL) {
            w_count++;
        } fclose(fp);
    
    if (w_count == 0) {
        perror("No words found\n");
        return 0;
    }
    
    srand(time(NULL));
    int rand_num = rand() % w_count;
    strcpy(secretWord, words[rand_num]);
    secretWord[strcspn(secretWord, "\n")] = '\0';
    return 0;
}

 
