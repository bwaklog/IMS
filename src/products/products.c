#include "products.h"
#include "../../helper/helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_product() {
  if (product_count == MAX) {
    printf("Product limit reached\n");
    return;
  }
  printf("Enter product id: ");
  scanf("%d%*c", &product_ids[product_count]);

  printf("Enter product name: ");
  fgets(product_names[product_count], MAX_STR_LEN, stdin);
  remove_newlien_char(product_names[product_count]);

  printf("Enter product price: ");
  scanf("%f%*c", &product_prices[product_count]);

  printf("Enter product quantity: ");
  scanf("%d%*c", &product_quantities[product_count]);
  product_count++;
}

void display_product() {
  if (product_count == 0) {
    printf("=== NO PRODUCTS ===\n");
    return;
  }
  printf("PID\t\tPNAME\t\tPRICE\t\tQUANTITY\n");
  for (int i = 0; i < product_count; i++) {
    printf("%d\t\t%s\t\t%f\t\t%d\n", product_ids[i], product_names[i],
           product_prices[i], product_quantities[i]);
  }
}
void update_product() {
  int pid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &pid);

  if (pid > product_count) {
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
void remove_product() {
  // delete element from an array
  int pid;
  printf("Enter PID to delete: ");
  scanf("%d%*c", &pid);

  if (pid > product_count) {
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
