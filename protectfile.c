#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <skeylib.h>
#include <math.h>

unsigned int from_hex (char *hex_str) {

  unsigned int hex_num;
  sscanf (hex_str, "%x", &hex_num);
  return hex_num;

}

int main (int argc, char **argv) {

  if (argc != 4) {
    printf ("Standard for main arguments:[-d/-e] [hex #] [filename]\n");
    exit (1);
  }

  char e_or_d = argv[1][0];
  char *key = argv[2];
  char *filename = argv[3];

  struct stat file_info;
  stat (filename, &file_info);

  unsigned int perms = file_info.st_mode;

  if (e_or_d != 'c' && e_or_d != 'd') {
    printf ("first arg must be 'e' or 'd'\n");
    exit (1);
  }
  if ((perms & 0x200) == 0) {
    printf ("sticky bit not set\n");
    exit (1);
  }

  /* Get integers from key string */
  if (strlen (key) != 16){
  	printf("The key you have provided isn't long enough.\n");
  	return (-1);
  }
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

  int setkeyval = setkey (k0, k1);

  if (setkeyval == 2) {
    printf ("keys not matched\n");
    exit (1);
  }
  if (setkeyval == 1 && e_or_d == 'd') {
    printf ("decrypting unencrypted file\n");
    exit (1);
  }

  return 0;
}
