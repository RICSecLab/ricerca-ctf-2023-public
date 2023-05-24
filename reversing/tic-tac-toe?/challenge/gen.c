#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  char flag[] = "RicSec{t1c_t4c_t03_1s_3x1t1ng_g4m3}\0";
  int val[3][3] = {16, 3, 0, 3, 6, 14, 12, 9, 9};

  srand(0xdeadbeef);
  char rand_table[3][3][17];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 17; k++) {
        rand_table[i][j][k] = rand() & 0xff;
      }
    }
  }

  int flag_len = strlen(flag) + 1;

  int cnt = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < val[i][j]; k++) {
        flag[cnt] = cnt ^ flag[cnt] ^ rand_table[i][j][val[i][j]];
        cnt = (cnt + 1) % flag_len;
      }
    }
  }

  printf("{");
  for (int i = 0; i < flag_len; i++) {
    printf("0x%x, ", flag[i] & 0xff);
  }
  printf("}\n");

  return 0;
}
