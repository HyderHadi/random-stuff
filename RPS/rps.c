#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Game {
    int wins;
    int losses;
    int draws;
    void (*conclusion)(struct Game *self, int decider, char *user_input);
    void (*showScore)(struct Game *self);
};

void Conclusion(struct Game *self, int decider, char *user_input) {
    if (decider >= 1 && decider <= 34) {
        printf("Rock is picked by computer\n");
        if (strcmp(user_input, "paper") == 0) {
           printf("You win!\n");
           self->wins++;
        }
        else if (strcmp(user_input, "scissor") == 0) {
           printf("You lose!\n");
           self->losses++;
        }
        else if (strcmp(user_input, "rock") == 0) {
            printf("Draw\n");
            self->draws++;
        }
        else {
            printf("Invalid input\n");
        }
    }
    else if (decider >= 35 && decider <= 66) {
       printf("Paper is picked by computer\n");
        if (strcmp(user_input, "paper") == 0) {
           printf("Draw\n");
           self->draws++;
        }
        else if (strcmp(user_input, "scissor") == 0) {
           printf("You win!\n");
           self->wins++;
        }
        else if (strcmp(user_input, "rock") == 0) {
            printf("You lose\n");
            self->losses++;
        }
        else {
            printf("Invalid input\n");
        }
    }
    else if (decider >= 67 && decider <= 100) {
       printf("Scissor is picked by computer\n");
        if (strcmp(user_input, "paper") == 0){
           printf("You lose!\n");
           self->losses++;
        }
        else if (strcmp(user_input, "scissor") == 0) {
           printf("Draw\n");
           self->draws++;
        }
        else if (strcmp(user_input, "rock") == 0) {
            printf("You win!\n");
            self->wins++;
        }
        else {
            printf("Invalid input\n");
        }
    }
}

void Show_Score(struct Game *self) {
    printf("Wins: %d | Losses: %d | Draws: %d\n", self->wins, self->losses, self->draws);
}

void Game_init(struct Game *game) {
    game->conclusion = Conclusion;
    game->wins = 0;
    game->showScore = Show_Score;
    game->losses = 0;
    game->draws = 0;
}



int main()
{
    struct Game mygame;
    Game_init(&mygame);
    srand(time(NULL));
    char user_input[10];
    printf("Pick Rock, Paper Or Scissor... (write Exit to quit, Score to see score)\n");
    while (fgets(user_input, sizeof(user_input), stdin) != NULL) {
        user_input[strcspn(user_input, "\n")] = '\0';
        for (int i = 0;user_input[i] != '\0';i++) {
            user_input[i] = tolower(user_input[i]);
        }
        if (strcmp(user_input, "exit") == 0) {
            printf("Exited\n");
            mygame.showScore(&mygame);
            break;
        }
        else if (strcmp(user_input, "score") == 0) {
            mygame.showScore(&mygame);
            continue;
        }
        printf("YOU PICKED: %s\n", user_input);
        mygame.conclusion(&mygame, rand() % 100, user_input);
    }
    return 0;
}