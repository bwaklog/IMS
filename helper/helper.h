#ifndef HELPER_H
#define HELPER_H

#define MAX_STR_LEN 1024
#define MAX 5
#define MAPSIZE 10
#define clear() printf("\x1b[H\x1b[J")
//#define clear()

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

typedef struct Node {
  CLASS node_class;

  union node_data {
    Product product;
    Supplier supplier;
    Transaction transaction;
  } node_data;

  struct Node *next;
} Node;

Node *prod_map[MAPSIZE];
Node *sup_map[MAPSIZE];
Node *tran_map[MAPSIZE];

void remove_newlien_char(char *str);
int check_existing(int id, CLASS class_type);
int generate_hash(int id);

void free_hashmaps(void);

#endif
