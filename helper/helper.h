#ifndef HELPER_H
#define HELPER_H

#define MAX_STR_LEN 1024
#define MAX 5
#define clear() printf("\x1b[H\x1b[J")

typedef struct Product {
  int product_id;
  char product_name[MAX_STR_LEN];
  float product_price;
  int product_quantity;
} Product;

typedef struct Supplier {
  int supplier_id;
  char supplier_name[MAX_STR_LEN];
  char supplier_addr[MAX_STR_LEN];
} Supplier;

typedef struct Transaction {
  int transaction_id;
  int transaction_product_id;
  int transaction_quantity;
  char transaction_date[MAX_STR_LEN];
} Transaction;

typedef enum CLASS { PRODUCT, SUPPLIER, TRANSACTION } CLASS;

Product *product_ds;
Supplier *supplier_ds;
Transaction *transaction_ds;


void remove_newlien_char(char *str);
int check_existing(int id, CLASS class_type, int max_count);

#endif
