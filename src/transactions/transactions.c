#include "transactions.h"
#include "../../helper/helper.h"
#include "../products/products.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_transaction(void) {

  if (transaction_count == MAX) {
    printf("transaction limit reached\n");
    return;
  }

  Node *tnode = (Node *)malloc(sizeof(Node));

  printf("Enter transaction id: ");

  int transid;
  scanf("%d%*c", &transid);

  if (check_existing(transid, TRANSACTION)) {
    printf("=== TRANSACTION WITH ID %d ALREADY EXISTS ===\n", transid);
    return;
  }

  tnode->node_data.transaction.transaction_id = transid;

  printf("Enter transaction product id: ");
  int pid;
  scanf("%d%*c", &pid);

  if (!check_existing(pid, PRODUCT)) {
    printf("=== PRODUCT WITH ID %d DOES NOT EXIST ===\n", pid);
    return;
  }
  tnode->node_data.transaction.transaction_product_id = pid;

  printf("Enter transaction quantity: ");
  int quantity;
  scanf("%d%*c", &quantity);
  int available = get_product_quantity(pid);
  if (quantity > available) {
    printf("=== QUANTITY EXCEEDS AVAILABLE STOCK ===\n");
    return;
  }

  update_stock(pid, quantity);
  tnode->node_data.transaction.transaction_quantity = quantity;

  printf("Enter transaction date: ");
  scanf("%[^\n]%*c", tnode->node_data.transaction.transaction_date);

  int hash = generate_hash(tnode->node_data.transaction.transaction_id);
  Node *head = tran_map[hash];

  if (head == NULL) {
      tran_map[hash] = tnode;
  } else {
      tnode->next = head;
      tran_map[hash] = tnode;
  }


  transaction_count++;
}

void display_transaction(void) {
  if (transaction_count == 0) {
    printf("=== NO transactionS ===\n");
    return;
  }
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = tran_map[i];

    if (ptr == NULL) {
      continue;
    }
    while (ptr != NULL) {
      printf("%d|%d|%d|%s\n", ptr->node_data.transaction.transaction_id,
             ptr->node_data.transaction.transaction_product_id,
             ptr->node_data.transaction.transaction_quantity,
             ptr->node_data.transaction.transaction_date);

      ptr = ptr->next;
    }
  }
}

void update_transaction(void) {
  int transid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &transid);

  if (check_existing(transid, TRANSACTION)) {
    printf("=== TRANSACTION WITH ID %d ALREADY EXISTS ===\n", transid);
    return;
  }

  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = prod_map[i];

    if (ptr == NULL) {
      printf("Emptry index\n");
      continue;
    }

    while (ptr != NULL) {
      if (ptr->node_data.product.product_id == transid) {
        char buff[MAX_STR_LEN];

        printf("Hit Enter to accept current value\n");
        printf("Transaction Date(%s): ",
               ptr->node_data.transaction.transaction_date);

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
          update_stock(ptr->node_data.transaction.transaction_product_id, diff);

          ptr->node_data.transaction.transaction_quantity = atoi(buff);
        }
      }
    }
  }
}
