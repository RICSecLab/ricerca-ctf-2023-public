#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define BOARD_SIZE 3
#define CELL_MAX 16

#define DEF_OP(name, expr)                                                     \
  extern inline int __attribute__((gnu_inline)) name(int a, int b) {                      \
    pid_t pid = fork();                                                        \
    if (pid == 0) {                                                            \
      exit((expr));                                                            \
    } else {                                                                   \
      int status;                                                              \
      wait(&status);                                                           \
      return WEXITSTATUS(status);                                              \
    }                                                                          \
  }

DEF_OP(_add, a + b);
DEF_OP(_sub, a - b);
DEF_OP(_mul, a *b);
DEF_OP(_div, a / b);
DEF_OP(_eq, a == b);

typedef enum {
  NONE = 0x0,
  PLAYER1 = 0x1,
  PLAYER2 = 0x2,
} player_t;

char *player_name(player_t player) {
  if (player & PLAYER1) {
    return "Player 1";
  } else if (player & PLAYER2) {
    return "Player 2";
  } else {
    return "";
  }
}

char player_icon(player_t player) {
  if (player & PLAYER1) {
    return 'o';
  } else if (player & PLAYER2) {
    return 'x';
  } else {
    return ' ';
  }
}

typedef struct {
  int x;
  int y;
} pos_t;

const pos_t INVALID_POS = {-1, -1};

int is_invalid_pos(pos_t pos) {
  return pos.x == INVALID_POS.x && pos.y == INVALID_POS.y;
}

typedef player_t board_t[BOARD_SIZE][BOARD_SIZE];

typedef struct {
  board_t board;
  player_t current_player;
} game_state_t;

game_state_t *initial_state() {
  game_state_t *state = calloc(1, sizeof(game_state_t));
  state->current_player = PLAYER1;
  return state;
}

void clear_screen() {
  printf("\033[2J");
  printf("\033[H");
}

void show_board(game_state_t *state) {
  clear_screen();
  printf("  Tic-Tac-Toe  \n");
  printf("\n");
  printf("  | a | b | c |\n");
  printf("--|---|---|---|\n");

  for (int y = 0; y < 3; y++) {
    printf("%d |", y + 1);
    for (int x = 0; x < 3; x++) {
      printf(" %c |", player_icon(state->board[x][y]));
    }
    printf("\n");
    printf("--|---|---|---|\n");
  }

  printf("\n");
}

pos_t try_read_pos(game_state_t *state) {
  char pos_str[3];
  scanf("%2s", pos_str);

  int x = pos_str[0] - 'a';
  int y = pos_str[1] - '1';

  if (x < 0 || x > 2) {
    return INVALID_POS;
  }

  if (y < 0 || y > 2) {
    return INVALID_POS;
  }

  pos_t pos = {x, y};
  return pos;
}

pos_t read_pos(game_state_t *state) {
  pos_t pos;
  for (;;) {
    printf("Enter position (e.g. a1): ");
    pos = try_read_pos(state);
    if (!is_invalid_pos(pos)) {
      return pos;
    }

    printf("Invalid position.\n");
  }
}

void place_mark(game_state_t *state, pos_t pos) {
  state->board[pos.x][pos.y] += state->current_player;
}

void switch_player(game_state_t *state) {
  player_t next_player;
  switch (state->current_player) {
  case NONE:
    next_player = NONE;
    break;
  case PLAYER1:
    next_player = PLAYER2;
    break;
  case PLAYER2:
    next_player = PLAYER1;
    break;
  }
  state->current_player = next_player;
}

int is_finished(game_state_t *state) {
  return ((state->board[0][0] & 0x3) != NONE &&
          (state->board[0][0] & 0x3) == (state->board[1][1] & 0x3) &&
          (state->board[0][0] & 0x3) == (state->board[0][2] & 0x3)) ||
         ((state->board[1][0] & 0x3) != NONE &&
          (state->board[1][0] & 0x3) == (state->board[1][1] & 0x3) &&
          (state->board[1][0] & 0x3) == (state->board[1][2] & 0x3)) ||
         ((state->board[2][0] & 0x3) != NONE &&
          (state->board[2][0] & 0x3) == (state->board[2][1] & 0x3) &&
          (state->board[2][0] & 0x3) == (state->board[2][2] & 0x3)) ||
         ((state->board[0][0] & 0x3) != NONE &&
          (state->board[0][0] & 0x3) == (state->board[1][0] & 0x3) &&
          (state->board[0][0] & 0x3) == (state->board[2][0] & 0x3)) ||
         ((state->board[0][1] & 0x3) != NONE &&
          (state->board[0][1] & 0x3) == (state->board[1][1] & 0x3) &&
          (state->board[0][1] & 0x3) == (state->board[2][1] & 0x3)) ||
         ((state->board[0][2] & 0x3) != NONE &&
          (state->board[0][2] & 0x3) == (state->board[1][2] & 0x3) &&
          (state->board[0][2] & 0x3) == (state->board[2][2] & 0x3)) ||
         ((state->board[0][0] & 0x3) != NONE &&
          (state->board[0][0] & 0x3) == (state->board[1][1] & 0x3) &&
          (state->board[0][0] & 0x3) == (state->board[2][2] & 0x3)) ||
         ((state->board[0][2] & 0x3) != NONE &&
          (state->board[0][2] & 0x3) == (state->board[1][1] & 0x3) &&
          (state->board[0][2] & 0x3) == (state->board[2][0] & 0x3));
}

int validate_board(game_state_t *state) {
  return (_eq(_add(state->board[0][0], state->board[1][0]), 19) &&
          _eq(_sub(state->board[1][0], state->board[2][0]), -9 + 256) &&
          _eq(_div(state->board[2][0], state->board[0][1]), 4) &&
          _eq(_add(state->board[0][1], state->board[1][1]), 9) &&
          _eq(_mul(state->board[1][1], state->board[2][1]), 54) &&
          _eq(_mul(state->board[2][1], state->board[0][2]), 0) &&
          _eq(_sub(state->board[0][2], state->board[1][2]), -14 + 256) &&
          _eq(_sub(state->board[1][2], state->board[2][2]), 5) &&
          _eq(_div(state->board[2][2], state->board[0][0]), 0) &&
          _eq(_sub(state->board[0][0], state->board[2][0]), 4) &&
          _eq(_mul(state->board[1][0], state->board[0][1]), 9) &&
          _eq(_add(state->board[2][0], state->board[1][1]), 18) &&
          _eq(_add(state->board[0][1], state->board[2][1]), 12) &&
          _eq(_sub(state->board[1][1], state->board[0][2]), 6) &&
          _eq(_div(state->board[2][1], state->board[1][2]), 0) &&
          _eq(_mul(state->board[0][2], state->board[2][2]), 0) &&
          _eq(_add(state->board[1][2], state->board[0][0]), 30) &&
          _eq(_sub(state->board[2][2], state->board[1][0]), 6));
}

char rand_table[BOARD_SIZE][BOARD_SIZE][CELL_MAX + 1];

void init_rand_hash() {
  srand(0xdeadbeef);

  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      for (int i = 0; i < CELL_MAX + 1; i++) {
        rand_table[x][y][i] = rand() & 0xff;
      }
    }
  }
}

char encoded[] = {
    0x76, 0x4d, 0x47, 0x77, 0x41, 0x47, 0xc9, 0xc6, 0x83, 0xd1, 0xed, 0xc6,
    0x86, 0xd1, 0xed, 0xc6, 0xf9, 0xfa, 0x5f, 0xb9, 0xfb, 0xd7, 0x87, 0xcc,
    0x85, 0xc0, 0x85, 0xfb, 0x19, 0x21, 0x19, 0x4a, 0x13, 0x4d, 0x3,  0x7e,
};

void show_flag(game_state_t *state) {
  int cnt = 0;
  int encoded_len = sizeof(encoded) / sizeof(char);
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      for (int i = 0; i < state->board[x][y]; i++) {
        encoded[cnt] =
            cnt ^ encoded[cnt] ^ rand_table[x][y][state->board[x][y]];
        cnt = (cnt + 1) % encoded_len;
      }
    }
  }

  printf("Congrats!\n");
  puts((char *)encoded);
  exit(0);
}

void game_end(game_state_t *state) {
  show_board(state);
  printf("%s win!\n", player_name(state->current_player));
  exit(0);
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);

  game_state_t *state = initial_state();
  init_rand_hash();

  for (;;) {
    show_board(state);
    printf("%s's turn.\n", player_name(state->current_player));
    pos_t pos = read_pos(state);
    place_mark(state, pos);
    if (is_finished(state)) {
      game_end(state);
    } else if (validate_board(state)) {
      show_flag(state);
    }
    switch_player(state);
  }

  return 0;
}
