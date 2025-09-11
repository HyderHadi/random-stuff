#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

struct Board {
  char board[100];
  void (*construct_board)(struct Board *self);
};

void ConstructBoard(struct Board *self) {
  // FILL THE BOARD
  for (int i = 0; i < 100; i++) {
    self->board[i] = i + 1;
  }
  // ALLOCATE SNAKES AND LADDERS
  int NumberOfSnakesAndLadders = 9;
  int GracePeriodTillSnakeOrLadder = 0;
  for (int i = 0; i < 100; i++) {
    int randmoizer = (rand() % 10) + 1;
    if (randmoizer < 3 && (self->board[i] % 10) != 0 &&
        GracePeriodTillSnakeOrLadder > 20 && NumberOfSnakesAndLadders > 0) {
      self->board[i] = 's';
      NumberOfSnakesAndLadders--;
      GracePeriodTillSnakeOrLadder -= 6;
    } else if (randmoizer > 7 && (self->board[i] % 10) != 0 &&
               GracePeriodTillSnakeOrLadder > 20 &&
               NumberOfSnakesAndLadders > 0) {
      self->board[i] = 'l';
      NumberOfSnakesAndLadders--;
      GracePeriodTillSnakeOrLadder -= 6;
    } else {
      GracePeriodTillSnakeOrLadder++;
    }
  }
  // Printing the final board
  for (int i = 0; i < 100; i++) {
    if (self->board[i] == 's' || self->board[i] == 'l') {
      printf(" %c*|", self->board[i]);
    } else if ((self->board[i] % 10) == 0) {
      printf(" %d |\n", self->board[i]);
    } else {
      printf(" %d |", self->board[i]);
    }
  }
}

void InitBoard(struct Board *b) { b->construct_board = ConstructBoard; }

struct Player {
  char player_name[10];
  int current_position;
  void (*dice)(struct Player *self, char *input);
};

void Dice(struct Player *self, char *input) {
  if (strcmp(input, "r") == 0) {
    int diceFaces = (rand() % 6) + 1;
    self->current_position = self->current_position + diceFaces;
  }
}

void InitPlayer(struct Player *P) {
  P->current_position = 0;
  P->dice = Dice;
}

struct Snake {
  int snakes[6];
  void (*snake)(struct Snake *self, struct Board *b, struct Player *p);
};

void Snake(struct Snake *self, struct Board *b, struct Player *p) {
  int tmp = rand() % 6;
  for (int i = 0; i < 100; i++) {
    if (p->current_position == i && b->board[i] == 's') {
      p->current_position = p->current_position - self->snakes[tmp];
    }
  }
}

void InitSnake(struct Snake *s) {
  int values[6] = {6, 10, 17, 27, 9, 18};
  for (int i = 0; i < 6; i++) {
    s->snakes[i] = values[i];
  }
  s->snake = Snake;
}

struct Ladder {
  int ladders[6];
  void (*ladder)(struct Ladder *self, struct Board *b, struct Player *p);
};

void Ladder(struct Ladder *self, struct Board *b, struct Player *p) {
  int tmp = rand() % 6;
  for (int i = 0; i < 100; i++) {
    if (p->current_position == i && b->board[i] == 'l') {
      p->current_position = p->current_position + self->ladders[tmp];
    }
  }
}

void InitLadder(struct Ladder *l) {
  int value[6] = {5, 10, 17, 28, 15, 13};
  for (int i = 0; i < 6; i++) {
    l->ladders[i] = value[i];
  }
  l->ladder = Ladder;
}

int main() {
  srand(time(NULL));
  printf("WELCOME TO SNAKES AND LADDERS\n\n");
  struct Board b0;
  InitBoard(&b0);
  b0.construct_board(&b0);
  struct Player p1;
  InitPlayer(&p1);
  struct Snake s;
  InitSnake(&s);
  struct Ladder l;
  InitLadder(&l);
  struct Player p2;
  InitPlayer(&p2);
  printf("Enter the first player name:\n");
  scanf("%s", p1.player_name);
  printf("Enter the other player name:\n");
  scanf("%s", p2.player_name);
  while (1) {
    char input[10];
    printf("Enter the letter r to ROLL the dice for %s\n", p1.player_name);
    scanf("%s", input);
    p1.dice(&p1, input);
    int tmp = p1.current_position;
    printf("%s position is %d\n", p1.player_name, p1.current_position + 1);
    s.snake(&s, &b0, &p1);
    if (p1.current_position < tmp) {
      printf("The player was swallowed by a snake of length %d, Your current "
             "position is %d\n\n",
             tmp - p1.current_position, p1.current_position + 1);
      printf("The Board; \n\n");

      for (int i = 0; i < 100; i++) {
        if (b0.board[i] == 's' || b0.board[i] == 'l') {
          printf(" %c*|", b0.board[i]);
        } else if ((b0.board[i] % 10) == 0) {
          printf(" %d |\n", b0.board[i]);
        } else {
          printf(" %d |", b0.board[i]);
        }
      }
      printf("\n");
    }
    l.ladder(&l, &b0, &p1);
    int wincheck = p1.current_position;
    if (p1.current_position > tmp) {
      printf("The player was lifted by a ladder of length %d, Your current "
             "position is %d\n\n",
             p1.current_position - tmp, p1.current_position + 1);
      printf("The Board; \n\n");
      for (int i = 0; i < 100; i++) {
        if (b0.board[i] == 's' || b0.board[i] == 'l') {
          printf(" %c*|", b0.board[i]);
        } else if ((b0.board[i] % 10) == 0) {
          printf(" %d |\n", b0.board[i]);
        } else {
          printf(" %d |", b0.board[i]);
        }
      }
      printf("\n");
    }

    if (p1.current_position > 98) {
      printf("The player %s has WOOOON!!!\n", p1.player_name);
      break;
    }

    // The player Two

    char input1[10];
    printf("Enter the letter r to ROLL the dice for %s\n", p2.player_name);
    scanf("%s", input1);
    p2.dice(&p2, input1);
    int tmp1 = p2.current_position;
    printf("%s position is %d\n", p2.player_name, p2.current_position + 1);
    s.snake(&s, &b0, &p2);
    if (p2.current_position < tmp1) {
      printf("The player was swalled by a snake of length %d, Your current "
             "position is %d\n\n",
             tmp1 - p2.current_position, p2.current_position + 1);
      printf("The Board; \n\n");

      for (int i = 0; i < 100; i++) {
        if (b0.board[i] == 's' || b0.board[i] == 'l') {
          printf(" %c*|", b0.board[i]);
        } else if ((b0.board[i] % 10) == 0) {
          printf(" %d |\n", b0.board[i]);
        } else {
          printf(" %d |", b0.board[i]);
        }
      }
      printf("\n");
    }
    l.ladder(&l, &b0, &p2);
    if (p2.current_position > tmp1) {
      printf("The player was lifted by a ladder of length %d, Your current "
             "position is %d\n\n",
             p2.current_position - tmp1, p2.current_position + 1);
      printf("The Board; \n\n");

      for (int i = 0; i < 100; i++) {
        if (b0.board[i] == 's' || b0.board[i] == 'l') {
          printf(" %c*|", b0.board[i]);
        } else if ((b0.board[i] % 10) == 0) {
          printf(" %d |\n", b0.board[i]);
        } else {
          printf(" %d |", b0.board[i]);
        }
      }
      printf("\n");
    }
    if (p2.current_position > 98) {
      printf("The player %s has WOOOON!!!\n", p2.player_name);
      break;
    }
  }
  return 0;
}