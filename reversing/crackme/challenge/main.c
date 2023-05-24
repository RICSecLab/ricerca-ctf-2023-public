#include <byteswap.h>
#include <stdio.h>
#include <string.h>

char enc[] = {
  32, 229, 109, 93, 105, 21, 207, 199, 153, 68, 219, 146, 255, 181,
  246, 197, 122, 147, 153, 124, 24, 207, 79, 221, 126, 111, 95, 0
};

void print_flag(unsigned char *password) {
  for (int i = 0; i < sizeof(enc) / sizeof(char) - 1; i++) {
    unsigned char c = password[i];
    c = (c & 0xf0) >> 4 | (c & 0x0f) << 4;
    c = (c & 0xcc) >> 2 | (c & 0x33) << 2;
    c = (c & 0xaa) >> 1 | (c & 0x55) << 1;
    enc[i] ^= c;
  }
  printf("The flag is \"%s\"\n", enc);
}

int main() {
  unsigned char password[100];
  printf("Password: ");
  memset(password, 0, sizeof(password));
  if (scanf("%99s", password) != 1) return 1;
  if (strcmp(password, "N1pp0n-Ich!_s3cuR3_p45$w0rD") == 0) {
    puts("[+] Authenticated");
    print_flag(password);
    return 0;
  } else {
    puts("[-] Permission denied");
    return 1;
  }
}
