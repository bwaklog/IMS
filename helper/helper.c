#include "helper.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_newlien_char(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

int check_existing(int id, CLASS class_type) {
  switch (class_type) {
  case PRODUCT: {
    for (int i = 0; i < MAPSIZE; i++) {
      Node *ptr = prod_map[i];

      while (ptr != NULL) {
        if (ptr->node_data.product.product_id == id) {
          return 1;
        }
        ptr = ptr->next;
      }
    }
    break;
  }
  case SUPPLIER: {
    for (int i = 0; i < MAPSIZE; i++) {
      Node *ptr = sup_map[i];

      while (ptr != NULL) {
        if (ptr->node_data.supplier.supplier_id == id) {
          return 1;
        }
        ptr = ptr->next;
      }
    }
    break;
  }
  case TRANSACTION: {
    for (int i = 0; i < MAPSIZE; i++) {
      Node *ptr = tran_map[i];

      while (ptr != NULL) {
        if (ptr->node_data.transaction.transaction_id == id) {
          return 1;
        }
        ptr = ptr->next;
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

int generate_hash(int id) {
    return id % MAPSIZE;
}

void free_hashmaps(void) {
    // freeing prod_map
    for (int i = 0; i < MAPSIZE; i++) {
        Node *ptr = prod_map[i];
        if (ptr == NULL) {
            printf("PROD_MAP[%d]: EMPTY\n", i);
        } else {
            while (ptr != NULL) {
                Node *temp = ptr;
                ptr = ptr->next;
                printf("SUP_MAP[%d]: %d freed\n", i, temp->node_data.product.product_id);
                free(temp);
            }
        }
    }

    // freeing sup_map
    for (int i = 0; i < MAPSIZE; i++) {
        Node *ptr = sup_map[i];
        if (ptr == NULL) {
            printf("SUP_MAP[%d]: EMPTY\n", i);
        } else {
            while (ptr != NULL) {
                Node *temp = ptr;
                ptr = ptr->next;
                printf("SUP_MAP[%d]: %d freed\n", i, temp->node_data.supplier.supplier_id);
                free(temp);
            }
        }
    }

    // freeing tran_map
    for (int i = 0; i < MAPSIZE; i++) {
        Node *ptr = tran_map[i];
        if (ptr == NULL) {
            printf("TRAN_MAP[%d]: EMPTY\n", i);
        } else {
            while (ptr != NULL) {
                Node *temp = ptr;
                ptr = ptr->next;
                printf("TRAN_MAP[%d]: %d freed\n", i, temp->node_data.transaction.transaction_id);
                free(temp);
            }
        }
    }

}
