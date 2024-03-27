#ifndef HELPER_H
#define HELPER_H

#define MAX_STR_LEN 1024
#define MAX 5
#define clear() printf("\x1b[H\x1b[J")

void remove_newlien_char(char *str);
int check_existing(int pid, int id_array[], int max_count);

#endif
