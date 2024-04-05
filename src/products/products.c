#include "products.h"
#include "../../helper/helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_product_quantity(int pid) {
  for (int i = 0; i < product_count; i++) {
    if (product_ds[i].product_id == pid) {
      return product_ds[i].product_quantity;
    }
  }
  return 0;
}

void update_stock(int pid, int withdrawn) {
  for (int i = 0; i < product_count; i++) {
    if (product_ds[i].product_id == pid) {
      product_ds[i].product_quantity -= withdrawn;
      return;
    }
  }
}

void append_product(void) {
  if (product_count == MAX) {
    printf("Product limit reached\n");
    return;
  }
  // realloc size for product_ds
  product_ds = realloc(product_ds, product_count + 1);

  printf("Enter product id: ");
  int pid;
  scanf("%d%*c", &pid);
  product_ds[product_count].product_id = pid;

  //  checking for existing id, exit if found
  if (check_existing(pid, PRODUCT, product_count)) {
    printf("=== PREXISTING ID FOUND ===\n");
    return;
  }
  // product_ids[product_count] = pid;
  product_ds[product_count].product_id = pid;

  printf("Enter product name: ");
  scanf("%[^\n]%*c", product_ds[product_count].product_name);

  printf("Enter product price: ");
  scanf("%f%*c", &product_ds[product_count].product_price);

  printf("Enter product quantity: ");
  scanf("%d%*c", &product_ds[product_count].product_quantity);

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
    strcpy(pname, product_ds[i].product_name);
    // truncate the string
    if (strlen(pname) > 20) {
      pname[20] = '\0';
    }
    printf("%-10d\t\t%-20s\t\t%-15.2f\t\t%-10d\n", product_ds[i].product_id,
           product_ds[i].product_name, product_ds[i].product_price,
           product_ds[i].product_quantity);
  }
}

void update_product(void) {
  int pid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &pid);

  // check for prexisting id, exit if function returns 0
  if (!check_existing(pid, PRODUCT, product_count)) {
    printf("=== NO SUCH PRODUCT EXISTS ===\n");
    return;
  }

  for (int i = 0; i < product_count; i++) {
    if (product_ds[i].product_id == pid) {
      // this is temp storage for each input
      char buff[MAX_STR_LEN];

      printf("Hit Enter to accept current value\n");
      printf("Product Name(%s): ", product_ds[i].product_name);
      // accept default if enter pressed

      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(product_ds[i].product_name, buff);
      }

      printf("Product Price(%f): ", product_ds[i].product_price);
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        product_ds[i].product_price = atof(buff);
      }

      printf("Product Count(%d): ", product_ds[i].product_quantity);
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        product_ds[i].product_quantity = atoi(buff);
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
  if (!check_existing(pid, PRODUCT, product_count)) {
    printf("=== NO SUCH PRODUCT EXISTS ===\n");
    return;
  }

  for (int i = 0; i < product_count; i++) {
    if (product_ds[i].product_id == pid) {
      for (int j = i; j < product_count - 1; j++) {
        product_ds[j] = product_ds[j + 1];
      }
      product_count--;
      product_ds = realloc(product_ds, product_count);
      break;
    }
  }
}
