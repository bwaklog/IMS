#include "products.h"
#include "../../helper/helper.h"
#include "../data/data.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>

int get_product_quantity(int pid) {
  // int hash = generate_hash(pid);
  Node *ptr = fetch_map(pid, PRODUCT);

  if (ptr == NULL) {
      return -1;
  }
  // while (ptr != NULL) {
  //   if (ptr->node_data.product.product_id == pid) {
  //     return ptr->node_data.product.product_quantity;
  //   }
  //   ptr = ptr->next;
  // }
  return ptr->node_data.product.product_quantity;
}

void update_stock(int pid, int withdrawn) {
  Node *ptr = fetch_map(pid, PRODUCT);
  ptr->node_data.product.product_quantity -= withdrawn;
  AOF_append("log.dat", ptr, OPSET);
}

void append_product(void) {
  // if (product_count == MAX) {
  //   printf("Product limit reached\n");
  //   return;
  // }

  Node *pnode = (Node *)malloc(sizeof(Node));
  pnode->node_class = PRODUCT;

  if (pnode == NULL) {
    printf("[ERR] PRODUCT: failed memory allocation\n");
    return;
  }

  printf("Enter product id: ");
  int pid;
  scanf("%d%*c", &pid);

  //  checking for existing id, exit if found
  if (check_existing(pid, PRODUCT)) {
    printf("[ERR] PRODUCT: Existing ID found\n");
    free(pnode);
    return;
  }

  pnode->node_data.product.product_id = pid;

  printf("Enter product name: ");
  scanf("%[^\n]%*c", pnode->node_data.product.product_name);

  printf("Enter product price: ");
  scanf("%f%*c", &pnode->node_data.product.product_price);

  printf("Enter product quantity: ");
  scanf("%d%*c", &pnode->node_data.product.product_quantity);

  append_to_map(pnode);
  AOF_append("log.dat", pnode, OPADD);
}

void display_product(void) {

  if (product_count == 0) {
    printf("=== NO PRODUCTS ===\n");
    return;
  }

  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = prod_map[i];

    if (ptr == NULL) {
      continue;
    }
    while (ptr != NULL) {
      printf("%p > %d|%s|%f|%d\n", (void *)ptr,
             ptr->node_data.product.product_id,
             ptr->node_data.product.product_name,
             ptr->node_data.product.product_price,
             ptr->node_data.product.product_quantity);

      ptr = ptr->next;
    }
  }
}

void update_product(void) {
  int pid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &pid);

  // check for prexisting id, exit if function returns 0
  if (!check_existing(pid, PRODUCT)) {
    printf("[ERR] PRODUCT: No such product exists\n");
    return;
  }

  // Node *ptr = prod_map[generate_hash(pid)];
  Node *ptr = fetch_map(pid, PRODUCT);

  if (ptr == NULL) {
    printf("Empty\n");
    return;
  }

  char buff[MAX_STR_LEN];

  printf("Hit Enter to accept current value\n");
  printf("Product Name(%s): ", ptr->node_data.product.product_name);
  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    printf("%s\n", buff);
    strcpy(ptr->node_data.product.product_name, buff);
  }

  printf("Product Price(%f): ", ptr->node_data.product.product_price);
  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    ptr->node_data.product.product_price = atof(buff);
  }

  printf("Product Count(%d): ", ptr->node_data.product.product_quantity);
  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    ptr->node_data.product.product_quantity = atoi(buff);
  }

  // update_node(pid, PRODUCT, ptr);
  AOF_append("log.dat", ptr, OPSET);

}

void remove_product(void) {
  // delete element from an array
  int pid;
  printf("Enter PID to delete: ");
  scanf("%d%*c", &pid);

  // check for prexisting id, exit if function returns 0
  if (!check_existing(pid, PRODUCT)) {
    printf("=== NO SUCH PRODUCT EXISTS ===\n");
    return;
  }

  Node *n = fetch_map(pid, PRODUCT);
  remove_from_map(pid, PRODUCT);
  AOF_append("log.dat", n, OPDEL);
}
