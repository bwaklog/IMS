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

  printf("Enter transaction id: ");
  int transid;
  scanf("%d%*c", &transid);

  if (check_existing(transid, transaction_ids, transaction_count)) {
    printf("=== TRANSACTION WITH ID %d ALREADY EXISTS ===\n", transid);
    return;
  }
  transaction_ids[transaction_count] = transid;

  printf("Enter transaction product id: ");
  int pid;
  scanf("%d%*c", &pid);

  if (!check_existing(pid, product_ids, product_count)) {
    printf("=== PRODUCT WITH ID %d DOES NOT EXIST ===\n", pid);
    return;
  }
  transaction_product_ids[transaction_count] = pid;

  printf("Enter transaction quantity: ");
  int quantity;
  scanf("%d%*c", &quantity);
  int available = get_product_quantity(pid);
  if (quantity > available) {
    printf("=== QUANTITY EXCEEDS AVAILABLE STOCK ===\n");
    return;
  }

  update_stock(pid, quantity);

  printf("Enter transaction date: ");
  fgets(transaction_dates[transaction_count], MAX_STR_LEN, stdin);
  scanf("%[^\n]%*c", transaction_dates[transaction_count]);

  transaction_count++;
}

void display_transaction(void) {
  if (transaction_count == 0) {
    printf("=== NO transactionS ===\n");
    return;
  }

  printf("====================================================================="
         "===========================\n");
  printf("%-10s\t\t%-10s\t\t%-10s\t\t%-10s\n", "Transaction ID", "Product ID",
         "Transaction Quantity", "Transaction Date");
  printf("====================================================================="
         "===========================\n");

  for (int i = 0; i < transaction_count; i++) {
    char tdate[MAX_STR_LEN];
    strcpy(tdate, transaction_dates[i]);
    // truncate the string
    if (strlen(tdate) > 20) {
      tdate[20] = '\0';
    }
    printf("%-10d\t\t%-10d\t\t%-10d\t\t%-20s\n", transaction_ids[i],
           transaction_product_ids[i], transactions_quantities[i],
           transaction_dates[i]);
  }
}
void update_transaction(void) {
  int transid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &transid);

  if (check_existing(transid, transaction_ids, transaction_count)) {
    printf("=== TRANSACTION WITH ID %d ALREADY EXISTS ===\n", transid);
    return;
  }

  for (int i = 0; i < transaction_count; i++) {
    if (transaction_ids[i] == transid) {
      // this is temp storage for each input
      char buff[MAX_STR_LEN];

      printf("Hit Enter to accept current value\n");
      printf("transaction PID(%d): ", transaction_product_ids[i]);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        transaction_product_ids[i] = atoi(buff);
      }

      printf("transaction quantity(%d): ", transactions_quantities[i]);
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        transactions_quantities[i] = atoi(buff);
      }

      printf("transaction Date(%s): ", transaction_dates[i]);
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        strcpy(transaction_dates[i], buff);
      }
    }
  }
}
