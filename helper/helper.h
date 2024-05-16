#ifndef HELPER_H
#define HELPER_H

#define MAX_STR_LEN 1024
#define MAX 100
#define MAPSIZE 10
// #define clear() printf("\x1b[H\x1b[J")
#define clear()

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

typedef enum PRODFIELD { PNAME, PRICE, QUANTITY } PRODFIELD;
typedef enum SUPPFIELD { SNAME, ADDR } SUPPFIELD;
typedef enum TRANFIELD { PID, QTY, DATE } TRANFIELD;

typedef struct Node {
  CLASS node_class;

  union node_data {
    Product product;
    Supplier supplier;
    Transaction transaction;
  } node_data;

  struct Node *next;
} Node;

extern Node *prod_map[MAPSIZE];
extern Node *sup_map[MAPSIZE];
extern Node *tran_map[MAPSIZE];

extern int product_count;
extern int supplier_count;
extern int transaction_count;

void remove_newlien_char(char *str);
int check_existing(int id, CLASS class_type);
int generate_hash(int id);

int append_to_map(Node *n);
int remove_from_map(int id, CLASS class_type);
int update_node(int id, CLASS class_type, Node *updated_values);
void display_fetch(CLASS, Node *n);
Node *fetch_map(int id, CLASS);

void free_hashmaps(void);

#endif
