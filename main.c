#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LEN 50

/// Get secret word from file
int getWord(const char *filename, char *secretWord);
bool isValidWord(const char *word);

int main(void){
    char secretWord[MAX_LEN] = "";
    int gamesWon = 0;
    int gamesLost = 0;
    int wordLen;
    int totalScore = 0;
    int gameNum = 0;

    while(1){
        gameNum++;
    // Welcome to Hangman!
    printf("######## WELCOME TO HANGMAN: METAL EDITION ######## " 
    "\n RULES: \nAll secret phrases are names of famous Metal songs\n" 
    "Phrases will only be one word\nAfter your 5th wrong guess, prepare your finals words, for the 6th will be your last..\n"
    " \n Caution.... \n safety not guaranteed..\n\n");
    printf("Game Number: %d\n", gameNum);
    printf(" %d Metal Heads have survived this trial.. will you?" 
    " \nor will you join the  %d other losers in the grave?\n", gamesWon, gamesLost);

        int correctLetters = 0;
        int wrongGuess = 0;
        // Error check for getting file
        if(!getWord("words.words", secretWord) ){
            perror("Error in main, did not get words.words\n");
        }

        wordLen = strlen(secretWord);
        char guessed[MAX_LEN] = "";
        int attempts = 6 + wordLen;
        for (int i = 0; i < wordLen; i++) {
            guessed[i] = '_'; 
        }
    char letter;
    while (attempts > 0 && correctLetters < wordLen) {

        printf("Secret Word: %s\n", guessed);
        printf("Attempts left: %d\n", attempts);
        printf("Enter guess: \n");

    // Read a character and validate it
    int validGuess = 0;
    while (!validGuess) {
        if (scanf(" %c", &letter) != 1 || !isalpha(letter)) {
            printf("Invalid input. Please enter a single letter: ");
            while (getchar() != '\n') ; // Clear the input buffer
        } else {
            validGuess = 1;
            }
        }
    // Convert the letter to lowercase
    letter = tolower(letter);
      
    //bool correctGuess = false;
        for (int i = 0; i < wordLen; i++) {
            if (secretWord[i] == letter && guessed[i] == '_') {
                guessed[i] = letter;
               // correctGuess = true;
                correctLetters++;
            
            } else {
                wrongGuess++;
            } 
        }
     attempts--;
    } // end of while loop
    if (correctLetters == wordLen) {
        printf("I think you've won\n");
        totalScore += wrongGuess;
        gamesWon++;
        
    } else {
        printf("Either you lost or I'm the dumb one\n");
        gamesLost++;
    }

    // Open the "stats.hangman" file for writing
    FILE *statsFile = fopen("stats.hangman", "a");
    if (statsFile == NULL) {
        perror("Error opening stats.hangman for writing");
        exit(EXIT_FAILURE);
    }

    // Write the statistics to the file
    fprintf(statsFile, "Games won: %d\n", gamesWon);
    fprintf(statsFile, "Games lost: %d\n", gamesLost);
    fprintf(statsFile, "Wrong guesses: %d\n", totalScore);

    // Close the file
    fclose(statsFile);

    // Play again?
     // Prompt for playing again
    char playAgain;
    printf("Play again? (Y/N): ");
    scanf(" %c", &playAgain);

    // Clear the input buffer
    while (getchar() != '\n');
        if (playAgain != 'y' && playAgain != 'Y') {
            printf("Keep rocking!\n");
            break;
        }
    }
    return 0;
}

// Check if a word contains special characters or spaces
bool isValidWord(const char *word) {
    while (*word) {
        if (!isalnum(*word) || isspace(*word)) {
            return false; // Contains a special character or space
        }
        word++;
    }
    return true; // Valid word
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
        words[w_count][strcspn(words[w_count], "\n")] = '\0'; // Remove newline characters
        if (isValidWord(words[w_count])) {
            w_count++;
        }
        } fclose(fp);
    
    if (w_count == 0) {
        perror("No words found\n");
        return 0;
    }
    
    srand(time(NULL));
    int rand_num = rand() % w_count;
    strcpy(secretWord, words[rand_num]);
   // secretWord[strcspn(secretWord, "\n")] = '\0';
    return 0;
}

 