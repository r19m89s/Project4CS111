#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <math.h>

unsigned int from_hex (char *hex_str) {

  unsigned int hex_num;
  sscanf (hex_str, "%x", &hex_num);
  return hex_num;

}

int main (int argc, char **argv) {

  if (argc != 4) {
    printf ("arguments incorrect\n");
    exit (1);
  }

  char e_or_d = argv[1][0];
  char *key = argv[2];
  char *filename = argv[3];

  struct stat file_info;
  stat (filename, &file_info);

  unsigned int perms = file_info.st_mode;

  if ((perms & 0x200) == 0) {
    printf ("sticky bit not set\n");
    exit(1);
  }

  /* Get integers from key string */
  assert (strlen (key) == 16);
  char high_bits[9];
  char low_bits[9];
  int i;
  for (i = 0; i < 8; ++i) {
    high_bits[i] = key[i];
  }
  for (i = 8; i < 16; ++i) {
    low_bits[i-8] = key[i];
  }

  unsigned int k0 = from_hex (high_bits);
  unsigned int k1 = from_hex (low_bits);

  return 0;
}
