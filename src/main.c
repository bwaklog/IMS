#include "products/products.h"
#include "suppliers/suppliers.h"
#include "transactions/transactions.h"
#include <stdio.h>
#include <stdlib.h>

// DEFINE: Product Arrays
int product_ids[MAX];
char product_names[MAX][MAX_STR_LEN];
float product_prices[MAX];
int product_quantities[MAX];

// DEFINE: Supplier Arrays
int supplier_ids[MAX];
char supplier_names[MAX][MAX_STR_LEN];
char supplier_address[MAX][MAX_STR_LEN];

// DEFINE: Transaction Arrays
int transaction_ids[MAX];
int transaction_product_ids[MAX];
int transactions_quantities[MAX];
char transaction_dates[MAX][MAX_STR_LEN];

// DEFINE: Counters for product, supplier and transactions arrays
int product_count = 0;
int supplier_count = 0;
int transaction_count = 0;

// Main function
int main(void) {
  char choice = '\0';
  char subchoice = '\0';

  while (choice != 'q') {
    printf("=== INVENTORY MANAGEMENT SYSTEM ===\n");
    printf("1.Product Mode\n2. Supplier Mode\n3. Transaction Mode\nq. "
           "Quit\n(1/2/3/q): ");
    scanf("%c", &choice);
    getchar(); // remove the new line character after input

    switch (choice) {
      // 1 -> products
      // 2 -> supplier
      // 3 -> transaction
      // anything -> invalid

    // Below switch cases handle for product mode
    case '1':
      clear();
      printf("1. Add Products\n2. Update Product\n3. Delete Product\n4. "
             "Display Products\nq. Exit Product Mode\n(1/2/3/4/q): ");
      scanf("%c", &subchoice);
      getchar();
      switch (subchoice) {
        putchar('\n');
      case '1':
        clear();
        printf("adding product\n");
        clear();
        append_product();
        break;
      case '2':
        clear();
        printf("update product\n");
        clear();
        update_product();
        break;
      case '3':
        clear();
        printf("delete product\n");
        remove_product();
        clear();
        break;
      case '4':
        clear();
        printf("~ PRODUCT TABLE ~\n");
        display_product();
        break;
      case 'q':
        clear();
        printf("exiting product mode\n");
        break;
      default:
        printf("invalid product mode operation\n");
      }
      putchar('\n');
      break;

    // Below switch cases handle for supplier mode
    case '2':
      clear();
      printf("1. Add Supplier\n2. Update Supplier Details\n3. Delete Supplier "
             "Details\n4. "
             "Display Suppliers\nq. Exit Supplier Mode\n(1/2/3/4/q): ");
      scanf("%c", &subchoice);
      getchar();
      switch (subchoice) {
        putchar('\n');
      case '1':
        clear();
        printf("adding product\n");
        clear();
        append_supplier();
        break;
      case '2':
        clear();
        printf("update supplier\n");
        clear();
        update_supplier();
        break;
      case '3':
        clear();
        printf("delete supplier\n");
        clear();
        remove_supplier();
        break;
      case '4':
        clear();
        printf("display supplier\n");
        display_supplier();
        break;
      case 'q':
        clear();
        printf("exiting supplier mode\n");
        break;
      default:
        printf("invalid supplier mode operation\n");
      }
      putchar('\n');

      break;

    // Below switch cases handle for transaction mode
    case '3':
      clear();
      printf("1. Add Transaction\n2. Update Transaction\n"
             "3. Display Products\nq. Exit Transaction Mode\n(1/2/3/q): ");
      scanf("%c", &subchoice);
      getchar();
      switch (subchoice) {
        putchar('\n');
      case '1':
        clear();
        printf("adding transaction\n");
        clear();
        append_transaction();
        break;
      case '2':
        clear();
        printf("update transaction\n");
        clear();
        update_transaction();
        break;
      case '3':
        clear();
        printf("display transaction\n");
        display_transaction();
        break;
      case 'q':
        clear();
        printf("exiting transaction mode\n");
        break;
      default:
        clear();
        printf("invalid transaction mode operation\n");
      }
      putchar('\n');

      break;

    // Below switch cases handle for transaction mode
    case 'q':
      clear();
      printf("~ EXITTING IMS ~\n");
      break;
    default:
      clear();
      printf("~ INVALID ~\n");
    }
  }
  return EXIT_SUCCESS; // EXIT_SUCCESS = 0
}
