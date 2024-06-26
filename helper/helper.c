#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int generate_hash(int id) { return id % MAPSIZE; }

int append_to_map(Node *n) {
  switch (n->node_class) {
  case PRODUCT: {

    if (check_existing(n->node_data.product.product_id, n->node_class)) {
      printf("[PREXISTING ID FOUND]: %d exists in product map\n",
             n->node_data.product.product_id);
      return 1;
    }

    int hash = generate_hash(n->node_data.product.product_id);
    Node *head = prod_map[hash];
    if (head == NULL) {
      prod_map[hash] = n;
    } else {
      Node *temp = head;
      n->next = temp;
      prod_map[hash] = n;
    }
    product_count++;
    break;
  }
  case SUPPLIER: {

    if (check_existing(n->node_data.supplier.supplier_id, n->node_class)) {
      printf("[PREXISTING ID FOUND]: %d exists in supplier map\n",
             n->node_data.product.product_id);
      return 1;
    }

    int hash = generate_hash(n->node_data.supplier.supplier_id);
    Node *head = sup_map[hash];
    if (head == NULL) {
      sup_map[hash] = n;
    } else {
      Node *temp = head;
      n->next = temp;
      sup_map[hash] = n;
    }
    supplier_count++;
    break;
  }
  case TRANSACTION: {

    if (check_existing(n->node_data.transaction.transaction_id,
                       n->node_class)) {
      printf("[PREXISTING ID FOUND]: %d exists in transaction map\n",
             n->node_data.transaction.transaction_id);
      return 1;
    }

    int hash = generate_hash(n->node_data.transaction.transaction_id);
    Node *head = tran_map[hash];
    if (head == NULL) {
      tran_map[hash] = n;
    } else {
      Node *temp = head;
      n->next = temp;
      tran_map[hash] = n;
    }
    transaction_count++;
    break;
  }
  default:
    break;
  }

  return 0;
}

int remove_from_map(int id, CLASS class_type) {
  switch (class_type) {
  case PRODUCT: {

    int hash = generate_hash(id);

    Node *ptr = prod_map[hash];
    Node *prev = NULL;

    if (ptr == NULL) {
      printf("[NOT FOUND]: %d not found in product map\n", id);
      return 1;
    }

    while (ptr != NULL) {
      if (ptr->node_data.product.product_id == id) {
        printf("[FOUND PRODUCT] DEL %p replace with %p\n", (void *)ptr,
               (void *)ptr->next);
        if (prev == NULL) {
          prod_map[hash] = ptr->next;
        } else {
          prev->next = ptr->next;
          free(ptr);
          product_count--;
          break;
        }

        prev = ptr;
        ptr = ptr->next;
      }
    }

    return 0;
  }
  case SUPPLIER: {
    int hash = generate_hash(id);
    Node *ptr = sup_map[hash];
    Node *prev = NULL;

    if (ptr == NULL) {
      printf("[NOT FOUND]: %d not found in supplier map\n", id);
      return 1;
    }

    while (ptr != NULL) {
      if (ptr->node_data.supplier.supplier_id == id) {
        printf("[FOUND SUPPLIER] DEL %p replace with %p\n", (void *)ptr,
               (void *)ptr->next);
        if (prev == NULL) {
          sup_map[hash] = ptr->next;
        } else {
          prev->next = ptr->next;
          free(ptr);
          supplier_count--;
          break;
        }

        prev = ptr;
        ptr = ptr->next;
      }
    }

    return 0;
  }
  case TRANSACTION: {
    printf("[TRANSACTION] ERR : No remove implementation\n");
    break;
  }
  default: {
    break;
  }
  }

  return 1;
}

int update_node(int id, CLASS class_type, Node *updated_values) {
  Node *n = fetch_map(id, class_type);
  if (n == NULL) {
    return 1;
  }
  switch (class_type) {
  case PRODUCT: {
    n->node_data = updated_values->node_data;
    break;
  }
  case SUPPLIER: {
    n->node_data = updated_values->node_data;
    break;
  }
  case TRANSACTION: {
    n->node_data = updated_values->node_data;
    break;
  }
  default:
    break;
  }

  return 0;
}

void display_fetch(CLASS class, Node *n) {
  switch (class) {
  case PRODUCT: {
    printf("%p > %d|%s|%f|%d\n", (void *)n, n->node_data.product.product_id,
           n->node_data.product.product_name,
           n->node_data.product.product_price,
           n->node_data.product.product_quantity);
    break;
  }
  case SUPPLIER: {
    printf("%p > %d|%s|%s\n", (void *)n, n->node_data.supplier.supplier_id,
           n->node_data.supplier.supplier_name,
           n->node_data.supplier.supplier_addr);
    break;
  }
  case TRANSACTION: {
    printf("%p > %d|%d|%d|%s\n", (void *)n,
           n->node_data.transaction.transaction_id,
           n->node_data.transaction.transaction_product_id,
           n->node_data.transaction.transaction_quantity,
           n->node_data.transaction.transaction_date);
    break;
  }
  }
}

Node *fetch_map(int id, CLASS class) {
  // this function fetches from the map for a
  // specified class
  // eg: GET PRODUCT 1 -> fetch product 1 details
  // it will be accessing in memory data due to
  // performace of inmemory reading operations
  // rather than the disk reading operations

  int hash = generate_hash(id);

  switch (class) {
  case PRODUCT: {
    Node *ptr = prod_map[hash];
    if (ptr == NULL) {
      printf("ERR: No such entry made\n");
      return NULL;
    }
    while (ptr != NULL) {
      if (ptr->node_data.product.product_id == id) {
        return ptr;
      }
      ptr = ptr->next;
    }
    break;
  }
  case SUPPLIER: {
    Node *ptr = sup_map[hash];
    if (ptr == NULL) {
      printf("ERR: No such entry made\n");
      return NULL;
    }
    while (ptr != NULL) {
      if (ptr->node_data.supplier.supplier_id == id) {
        return ptr;
        break;
      }
      ptr = ptr->next;
    }
    break;
  }
  case TRANSACTION: {
    Node *ptr = tran_map[hash];
    if (ptr == NULL) {
      printf("ERR: No such entry made\n");
      return NULL;
    }
    while (ptr != NULL) {
      if (ptr->node_data.transaction.transaction_id == id) {
        return ptr;
        break;
      }
      ptr = ptr->next;
    }
    break;
  }
  default:
    break;
  }
  return NULL;
}

void free_hashmaps(void) {
  // freeing prod_map
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = prod_map[i];
    if (ptr == NULL) {
      // printf("PROD_MAP[%d]: EMPTY\n", i);
      continue;
    } else {
      while (ptr != NULL) {
        Node *temp = ptr;
        ptr = ptr->next;
        free(temp);
        printf("[FREE] PRODUCT %p\n", (void *)temp);
      }
    }
  }

  // freeing sup_map
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = sup_map[i];
    if (ptr == NULL) {
      // printf("SUP_MAP[%d]: EMPTY\n", i);
      continue;
    } else {
      while (ptr != NULL) {
        Node *temp = ptr;
        ptr = ptr->next;
        free(temp);
        printf("[FREE] SUPPLIER %p\n", (void *)temp);
      }
    }
  }

  // freeing tran_map
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = tran_map[i];
    if (ptr == NULL) {
      // printf("TRAN_MAP[%d]: EMPTY\n", i);
      continue;
    } else {
      while (ptr != NULL) {
        Node *temp = ptr;
        ptr = ptr->next;
        free(temp);
        printf("[FREE] TRANSACTION %p\n", (void *)temp);
      }
    }
  }
}
