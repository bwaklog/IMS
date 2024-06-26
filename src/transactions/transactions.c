#include "transactions.h"
#include "../../helper/helper.h"
#include "../data/data.h"
#include "../products/products.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_transaction(void) {

  // if (transaction_count == MAX) {
  //   printf("transaction limit reached\n");
  //   return;
  // }

  Node *tnode = (Node *)malloc(sizeof(Node));
  tnode->node_class = TRANSACTION;

  if (tnode == NULL) {
    printf("[ERR] TRANSACTION: memory allocation\n");
    return;
  }

  printf("Enter transaction id: ");
  int transid;
  scanf("%d%*c", &transid);

  if (check_existing(transid, TRANSACTION)) {
    printf("[ERR] TRANSACTION: %d ID already exists\n", transid);
    free(tnode);
    return;
  }

  tnode->node_data.transaction.transaction_id = transid;

  printf("Enter transaction product id: ");
  int pid;
  scanf("%d%*c", &pid);

  if (check_existing(pid, PRODUCT) != 1) {
    printf("[ERR] TRANSACTION: ID %d does not exist\n", pid);
    free(tnode);
    return;
  }
  tnode->node_data.transaction.transaction_product_id = pid;

  printf("Enter transaction quantity: ");
  int quantity;
  scanf("%d%*c", &quantity);

  int available = get_product_quantity(pid);
  if (quantity > available) {
    printf("[ERR] TRANSACTION: Insufficient stock\n");
    return;
  }

  update_stock(pid, quantity);
  tnode->node_data.transaction.transaction_quantity = quantity;

  printf("Enter transaction date: ");
  scanf("%[^\n]%*c", tnode->node_data.transaction.transaction_date);

  append_to_map(tnode);
  store_to_file("store.csv", tnode, OPADD);
}

void display_transaction(void) {
  if (transaction_count == 0) {
    printf("[ERR] TRANSACTION: No transactions\n");
    return;
  }
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = tran_map[i];

    if (ptr == NULL) {
      continue;
    }
    while (ptr != NULL) {
      printf("%p > %d|%d|%d|%s\n", (void *)ptr,
             ptr->node_data.transaction.transaction_id,
             ptr->node_data.transaction.transaction_product_id,
             ptr->node_data.transaction.transaction_quantity,
             ptr->node_data.transaction.transaction_date);

      ptr = ptr->next;
    }
  }
}

void update_transaction(void) {
  int transid;
  printf("Enter TID to update: ");
  scanf("%d%*c", &transid);

  if (!check_existing(transid, TRANSACTION)) {
    printf("[ERR] TRANSACTION: No such transaction exists\n");
    return;
  }

  Node *ptr = fetch_map(transid, TRANSACTION);
  char buff[MAX_STR_LEN];

  printf("Hit Enter to accept current value\n");
  printf("Transaction Date(%s): ", ptr->node_data.transaction.transaction_date);

  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    printf("%s\n", buff);
    strcpy(ptr->node_data.transaction.transaction_date, buff);
  }

  printf("Transaction Product ID(%d): ",
         ptr->node_data.transaction.transaction_product_id);
  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    ptr->node_data.transaction.transaction_product_id = atoi(buff);
  }

  printf("Transaction quantity(%d): ",
         ptr->node_data.transaction.transaction_quantity);
  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);

    int old_quan = ptr->node_data.transaction.transaction_quantity;
    int diff = atoi(buff) - old_quan;

    if (fetch_map(ptr->node_data.transaction.transaction_product_id, PRODUCT)
                ->node_data.product.product_quantity -
            diff <
        0) {
      printf("[ERR] TRANSACTION: Insufficient stock\n");
      return;
    }

    update_stock(ptr->node_data.transaction.transaction_product_id, diff);

    ptr->node_data.transaction.transaction_quantity = atoi(buff);
  }

  store_to_file("store.csv", ptr, OPSET);
}

// 1. display transactions where quantity is less than 3
void display_low_stock(void) {
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = tran_map[i];

    if (ptr == NULL) {
      continue;
    }

    while (ptr != NULL) {
      if (ptr->node_data.transaction.transaction_quantity < 3) {
        printf("%p > %d|%d|%d|%s\n", (void *)ptr,
               ptr->node_data.transaction.transaction_id,
               ptr->node_data.transaction.transaction_product_id,
               ptr->node_data.transaction.transaction_quantity,
               ptr->node_data.transaction.transaction_date);
      }
      ptr = ptr->next;
    }
  }
}

// 2. display all transactions where month is may
// format of month is DD-MM-YR
void month_filter(void) {
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = tran_map[i];

    if (ptr == NULL) {
      continue;
    }

    while (ptr != NULL) {

      char date[MAX_STR_LEN];
      strcpy(date, ptr->node_data.transaction.transaction_date);

      char *tok = strtok(date, "-");
      tok = strtok(NULL, "-");
      int month = atoi(tok);

      if (month == 5) {
        printf("%d|%d|%d|%s\n", ptr->node_data.transaction.transaction_id,
               ptr->node_data.transaction.transaction_product_id,
               ptr->node_data.transaction.transaction_quantity,
               ptr->node_data.transaction.transaction_date);
      }
      ptr = ptr->next;
    }
  }
}
