/*******************************************************************************
 *  IMS - Inventory Management System
 *
 *  Repository: github.com/bwaklog/ims.git
 *  LICENSE: MIT
 *
 *  Version: 1.0
 *  Author: Aditya Hegde
 *
 *  This program is part of the course (UE23CS151B) case study assignment. Scope
 *  is to produce an application to manage inventory of a store and maintain
 *  records related to the products, suppliers and transactions.
 * *****************************************************************************/

#include "data/data.h"
#include "products/products.h"
#include "suppliers/suppliers.h"
#include "transactions/transactions.h"
#include <stdio.h>
#include <stdlib.h>

// DEFINE: Counters for product, supplier and transactions arrays
int product_count = 0;
int supplier_count = 0;
int transaction_count = 0;

Node *prod_map[MAPSIZE];
Node *sup_map[MAPSIZE];
Node *tran_map[MAPSIZE];

// Main function
int main(void) {

  reconstruct_data("store.csv");

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
      putchar('\n');
      switch (subchoice) {
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
             "Display Suppliers\n5. Display Bangalore Suppliers\n6. Bubble "
             "sort suppliers\nq. Exit Supplier Mode\n(1/2/3/4/q): ");
      scanf("%c", &subchoice);
      getchar();
      putchar('\n');
      switch (subchoice) {
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
      case '5':
        clear();
        addr_filter("bangalore");
        break;
      case '6':
        clear();
        bubble_sort_suppliers();
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
             "3. Display Products\n4. Less than 3 quan\n5. Transactions in "
             "May\nq. "
             "Exit Transaction Mode\n(1/2/3/q): ");
      scanf("%c", &subchoice);
      getchar();
      putchar('\n');
      switch (subchoice) {
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
      case '4':
        clear();
        display_low_stock();
        break;
      case '5':
        clear();
        month_filter();
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
      free_hashmaps();
      break;
    default:
      clear();
      printf("~ INVALID ~\n");
    }
  }
  return EXIT_SUCCESS; // EXIT_SUCCESS = 0
}
