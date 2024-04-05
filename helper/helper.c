#include "helper.h"
#include <string.h>
#include <stdio.h>

void remove_newlien_char(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

int check_existing(int id, CLASS class_type, int max_count) {
  switch (class_type) {
  case PRODUCT: {
    for (int i = 0; i < max_count; i++) {
      if (product_ds[i].product_id == id) {
        return 1;
      }
    }
    break;
  }
  case SUPPLIER: {
    for (int i = 0; i < max_count; i++) {
      if (supplier_ds[i].supplier_id == id) {
        return 1;
      }
    }
    break;
  }
  case TRANSACTION: {
    for (int i = 0; i < max_count; i++) {
      if (transaction_ds[i].transaction_id == id) {
        return 1;
      }
    }
    break;
  }
  default: {
    printf("Incorrect class type passed\n");
  }
  }
  return 0;
}
