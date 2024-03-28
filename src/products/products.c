#include "products.h"
#include "../../helper/helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_product_quantity(int pid) {
  for (int i = 0; i < product_count; i++) {
    if (product_ids[i] == pid) {
      return product_quantities[i];
    }
  }
  return 0;
}

void update_stock(int pid, int withdrawn) {
  for (int i = 0; i < product_count; i++) {
    if (product_ids[i] == pid) {
      product_quantities[i] -= withdrawn;
      return;
    }
  }
}

void append_product(void) {
  if (product_count == MAX) {
    printf("Product limit reached\n");
    return;
  }
  printf("Enter product id: ");
  int pid;
  // scanf("%d%*c", &product_ids[product_count]);
  scanf("%d%*c", &pid);

  //  checking for existing id, exit if found
  if (check_existing(pid, product_ids, product_count)) {
    printf("=== PREXISTING ID FOUND ===\n");
    return;
  }
  product_ids[product_count] = pid;

  printf("Enter product name: ");
  scanf("%[^\n]%*c", product_names[product_count]);

  printf("Enter product price: ");
  scanf("%f%*c", &product_prices[product_count]);

  printf("Enter product quantity: ");
  scanf("%d%*c", &product_quantities[product_count]);
  product_count++;
}

void display_product(void) {
  if (product_count == 0) {
    printf("=== NO PRODUCTS ===\n");
    return;
  }

  printf("================================================================="
         "===="
         "===========================\n");
  printf("%-10s\t\t%-20s\t\t%-15s\t\t%-10s\n", "Product ID", "Product Name",
         "Product Price", "Product Quantity");
  printf("====================================================================="
         "===========================\n");

  for (int i = 0; i < product_count; i++) {
    char pname[MAX_STR_LEN];
    strcpy(pname, product_names[i]);
    // truncate the string
    if (strlen(pname) > 20) {
      pname[20] = '\0';
    }
    printf("%-10d\t\t%-20s\t\t%-15.2f\t\t%-10d\n", product_ids[i], pname,
           product_prices[i], product_quantities[i]);
  }
}

void update_product(void) {
  int pid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &pid);

  // check for prexisting id, exit if function returns 0
  if (!check_existing(pid, product_ids, product_count)) {
    printf("=== NO SUCH PRODUCT EXISTS ===\n");
    return;
  }

  for (int i = 0; i < product_count; i++) {
    if (product_ids[i] == pid) {
      // this is temp storage for each input
      char buff[MAX_STR_LEN];

      printf("Hit Enter to accept current value\n");
      printf("Product Name(%s): ", product_names[i]);
      // accept default if enter pressed

      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(product_names[i], buff);
      }

      printf("Product Price(%f): ", product_prices[i]);
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        product_prices[i] = atof(buff);
      }

      printf("Product Count(%d): ", product_quantities[i]);
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        product_prices[i] = atoi(buff);
      }
    }
  }
}

void remove_product(void) {
  // delete element from an array
  int pid;
  printf("Enter PID to delete: ");
  scanf("%d%*c", &pid);

  // check for prexisting id, exit if function returns 0
  if (!check_existing(pid, product_ids, product_count)) {
    printf("=== NO SUCH PRODUCT EXISTS ===\n");
    return;
  }

  for (int i = 0; i < product_count; i++) {
    if (product_ids[i] == pid) {
      for (int j = i; j < product_count - 1; j++) {
        product_ids[j] = product_ids[j + 1];
        strcpy(product_names[j], product_names[j + 1]);
        product_prices[j] = product_prices[j + 1];
        product_quantities[j] = product_quantities[j + 1];
      }
      product_count--;
      break;
    }
  }
}
