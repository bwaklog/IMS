#include "helper.h"
#include <string.h>

void remove_newlien_char(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

int check_existing(int pid, int id_array[], int max_count) {
  for (int i = 0; i < max_count; i++) {
    if (id_array[i] == pid) {
      return 1;
    }
  }
  return 0;
}
