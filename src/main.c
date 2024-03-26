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
  printf("IMS\n");
  char choice = '\0';
  char subchoice = '\0';

  while (choice != 'q') {
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
      printf("1. Add Products\n2. Update Product\n3. Delete Product\n4. "
             "Display Products\nq. Exit Product Mode\n(1/2/3/4/q): ");
      scanf("%c", &subchoice);
      getchar();
      switch (subchoice) {
        putchar('\n');
      case '1':
        printf("adding product\n");
        append_product();
        break;
      case '2':
        printf("update product\n");
        update_product();
        break;
      case '3':
        printf("delete product\n");
        remove_product();
        break;
      case '4':
        printf("display product\n");
        display_product();
        break;
      case 'q':
        printf("exiting product mode\n");
        break;
      default:
        printf("invalid product mode operation\n");
      }
      putchar('\n');
      break;

    // Below switch cases handle for supplier mode
    case '2':
      printf("1. Add Supplier\n2. Update Supplier Details\n3. Delete Supplier "
             "Details\n4. "
             "Display Suppliers\nq. Exit Supplier Mode\n(1/2/3/4/q): ");
      scanf("%c", &subchoice);
      getchar();
      switch (subchoice) {
        putchar('\n');
      case '1':
        printf("adding product\n");
        append_supplier();
        break;
      case '2':
        printf("update supplier\n");
        update_supplier();
        break;
      case '3':
        printf("delete supplier\n");
        remove_supplier();
        break;
      case '4':
        printf("display supplier\n");
        display_supplier();
        break;
      case 'q':
        printf("exiting supplier mode\n");
        break;
      default:
        printf("invalid supplier mode operation\n");
      }
      putchar('\n');

      break;

    // Below switch cases handle for transaction mode
    case '3':
      printf("1. Add Transaction\n2. Update Transaction\n"
             "3. Display Products\nq. Exit Transaction Mode\n(1/2/3/q): ");
      scanf("%c", &subchoice);
      getchar();
      switch (subchoice) {
        putchar('\n');
      case '1':
        printf("adding transaction\n");
        append_transaction();
        break;
      case '2':
        printf("update transaction\n");
        update_transaction();
        break;
      case '3':
        printf("display transaction\n");
        display_transaction();
        break;
      case 'q':
        printf("exiting transaction mode\n");
        break;
      default:
        printf("invalid transaction mode operation\n");
      }
      putchar('\n');

      break;

    // Below switch cases handle for transaction mode
    case 'q':
      printf("exiting\n");
      break;
    default:
      printf("invlalid\n");
    }
  }
  return EXIT_SUCCESS; // EXIT_SUCCESS = 0
}
