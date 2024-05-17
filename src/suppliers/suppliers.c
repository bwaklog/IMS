#include "suppliers.h"
#include "../../helper/helper.h"
#include "../data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_supplier(void) {
  // if (supplier_count == MAX) {
  //   printf("supplier limit reached\n");
  //   return;
  // }

  Node *snode = (Node *)malloc(sizeof(Node));
  snode->node_class = SUPPLIER;

  printf("Enter supplier id: ");
  int supid;
  scanf("%d%*c", &supid);

  if (check_existing(supid, SUPPLIER)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  snode->node_data.supplier.supplier_id = supid;

  printf("Enter supplier name: ");
  scanf("%[^\n]%*c", snode->node_data.supplier.supplier_name);

  printf("Enter supplier address: ");
  scanf("%[^\n]%*c", snode->node_data.supplier.supplier_addr);

  append_to_map(snode);
  AOF_append("log.dat", snode, OPADD);
}

void display_supplier(void) {
  if (supplier_count == 0) {
    printf("=== NO SUPPLIERS ===\n");
    return;
  }
  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = sup_map[i];

    if (ptr == NULL) {
      continue;
    }
    while (ptr != NULL) {
      printf("%p > %d|%s|%s\n", (void *)ptr,
             ptr->node_data.supplier.supplier_id,
             ptr->node_data.supplier.supplier_name,
             ptr->node_data.supplier.supplier_addr);

      ptr = ptr->next;
    }
  }
}

void update_supplier(void) {
  int supid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &supid);

  if (!check_existing(supid, SUPPLIER)) {
    printf("[ERR] SUPPLIER: No such supplier\n");
    return;
  }

  Node *ptr = fetch_map(supid, SUPPLIER);

  if (ptr == NULL) {
    printf("Emptry index\n");
    return;
  }

  char buff[MAX_STR_LEN];

  printf("Hit Enter to accept current value\n");
  printf("Supplier Name(%s): ", ptr->node_data.supplier.supplier_name);

  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    printf("%s\n", buff);
    strcpy(ptr->node_data.supplier.supplier_name, buff);
  }

  printf("Supplier Addr(%s): ", ptr->node_data.supplier.supplier_addr);

  fgets(buff, MAX_STR_LEN, stdin);
  if (buff[0] != '\n') {
    remove_newlien_char(buff);
    printf("%s\n", buff);
    strcpy(ptr->node_data.supplier.supplier_addr, buff);
  }

  ptr = fetch_map(supid, SUPPLIER);
  AOF_append("log.dat", ptr, OPSET);
}

void remove_supplier(void) {
  // delete element from an array
  int supid;
  printf("Enter PID to update: ");

  scanf("%d%*c", &supid);

  if (check_existing(supid, SUPPLIER) != 1) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  Node *n = fetch_map(supid, SUPPLIER);
  AOF_append("log.dat", n, OPDEL);
  remove_from_map(supid, SUPPLIER);
}

void addr_filter(char *addr) {

  bool found = false;

  for (int i = 0; i < MAPSIZE; i++) {
    Node *ptr = sup_map[i];

    if (ptr == NULL) {
      continue;
    }

    while (ptr != NULL) {
      if (strcasecmp(addr, ptr->node_data.supplier.supplier_addr) == 0) {
        printf("%d|%s|%s\n", ptr->node_data.supplier.supplier_id,
               ptr->node_data.supplier.supplier_name,
               ptr->node_data.supplier.supplier_addr);
      }
      found = true;
      ptr = ptr->next;
    }
  }

  if (!found) {
      printf("No supplier with address %s\n", addr);
  }
}

void bubble_sort_suppliers(void) {

    // first filling an array with the supplier

    Node *suppliers[supplier_count];

    int i = 0;

    for (int j = 0; j < MAPSIZE; j++) {
        Node *ptr = sup_map[j];

        if (ptr == NULL) {
            continue;
        }

        while (ptr != NULL) {
            suppliers[i] = ptr;
            i++;
            ptr = ptr->next;
        }
    }
    printf("Hello\n");

    // bubble sorting the array
    for (int m = 0; m < supplier_count; m++) {
        for (int n = m; n < supplier_count; n++) {
            // sort on name
            if (strcasecmp(suppliers[m]->node_data.supplier.supplier_name, suppliers[n]->node_data.supplier.supplier_name) > 0) {
                Node *temp = suppliers[m];
                suppliers[m] = suppliers[n];
                suppliers[n] = temp;
            }
        }
    }

    for (int a = 0; a < supplier_count; a++) {
        printf("%d|%s|%s\n", suppliers[a]->node_data.supplier.supplier_id,
               suppliers[a]->node_data.supplier.supplier_name,
               suppliers[a]->node_data.supplier.supplier_addr);
    }
}
