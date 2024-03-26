#include "suppliers.h"
#include "../../helper/helper.h"
#include <stdio.h>
#include <string.h>

void append_supplier(void) {
  if (supplier_count == MAX) {
    printf("supplier limit reached\n");
    return;
  }
  printf("Enter supplier id: ");
  scanf("%d%*c", &supplier_ids[supplier_count]);

  printf("Enter supplier name: ");
  fgets(supplier_names[supplier_count], MAX_STR_LEN, stdin);
  remove_newlien_char(supplier_names[supplier_count]);

  printf("Enter supplier address: ");
  fgets(supplier_address[supplier_count], MAX_STR_LEN, stdin);
  remove_newlien_char(supplier_address[supplier_count]);

  supplier_count++;
}

void display_supplier(void) {
  if (supplier_count == 0) {
    printf("=== NO supplierS ===\n");
    return;
  }
  printf("PID\t\tPNAME\t\tADDRESS\n");
  for (int i = 0; i < supplier_count; i++) {
    printf("%d\t\t%s\t\t%s\n", supplier_ids[i], supplier_names[i],
           supplier_address[i]);
  }
}

void update_supplier(void) {
  int pid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &pid);

  if (pid > supplier_count) {
    printf("=== NO SUCH supplier EXISTS ===\n");
    return;
  }

  for (int i = 0; i < supplier_count; i++) {
    if (supplier_ids[i] == pid) {
      // this is temp storage for each input
      char buff[MAX_STR_LEN];

      printf("Hit Enter to accept current value\n");
      printf("supplier Name(%s): ", supplier_names[i]);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(supplier_names[i], buff);
      }

      printf("supplier address(%s): ", supplier_address[i]);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(supplier_address[i], buff);
      }
    }
  }
}

void remove_supplier(void) {
  // delete element from an array
  int pid;
  printf("Enter PID to delete: ");
  scanf("%d%*c", &pid);

  if (pid > supplier_count) {
    printf("=== NO SUCH supplier EXISTS ===\n");
    return;
  }

  for (int i = 0; i < supplier_count; i++) {
    if (supplier_ids[i] == pid) {
      for (int j = i; j < supplier_count - 1; j++) {
        supplier_ids[j] = supplier_ids[j + 1];
        strcpy(supplier_names[j], supplier_names[j + 1]);
        strcpy(supplier_address[j], supplier_address[j + 1]);
      }
      supplier_count--;
      break;
    }
  }
}
