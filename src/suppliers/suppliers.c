#include "suppliers.h"
#include "../../helper/helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_supplier(void) {
  if (supplier_count == MAX) {
    printf("supplier limit reached\n");
    return;
  }
  printf("Enter supplier id: ");
  int supid;
  scanf("%d%*c", &supid);

  if (check_existing(supid, SUPPLIER, supplier_count)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  supplier_ds = realloc(supplier_ds, supplier_count + 1);

  supplier_ds[supplier_count].supplier_id = supid;

  printf("Enter supplier name: ");
  scanf("%[^\n]%*c", supplier_ds[supplier_count].supplier_name);

  printf("Enter supplier address: ");
  scanf("%[^\n]%*c", supplier_ds[supplier_count].supplier_addr);

  supplier_count++;
}

void display_supplier(void) {
  if (supplier_count == 0) {
    printf("=== NO supplierS ===\n");
    return;
  }

  printf("====================================================================="
         "=======\n");
  printf("%-10s\t\t%-20s\t\t%-20s\n", "Supplier ID", "Supplier Name",
         "Supplier Address");
  printf("====================================================================="
         "=======\n");

  for (int i = 0; i < supplier_count; i++) {
    char sname[MAX_STR_LEN];
    char saddr[MAX_STR_LEN];
    strcpy(sname, supplier_ds[i].supplier_name);
    strcpy(saddr, supplier_ds[i].supplier_addr);
    // truncate the string
    if (strlen(sname) > 20) {
      sname[20] = '\0';
    }
    if (strlen(saddr) > 20) {
      saddr[20] = '\0';
    }
    printf("%-10d\t\t%-20s\t\t%-s\n", supplier_ds[i].supplier_id,
           supplier_ds[i].supplier_name, supplier_ds[i].supplier_addr);
  }
}

void update_supplier(void) {
  int supid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &supid);

  if (!check_existing(supid, SUPPLIER, supplier_count)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  for (int i = 0; i < supplier_count; i++) {
    if (supplier_ds[i].supplier_id == supid) {
      // this is temp storage for each input
      char buff[MAX_STR_LEN];

      printf("Hit Enter to accept current value\n");
      printf("supplier Name(%s): ", supplier_ds[i].supplier_name);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(supplier_ds[i].supplier_name, buff);
      }

      printf("supplier address(%s): ", supplier_ds[i].supplier_name);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(supplier_ds[i].supplier_name, buff);
      }
    }
  }
}

void remove_supplier(void) {
  // delete element from an array
  int supid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &supid);

  if (!check_existing(supid, SUPPLIER, supplier_count)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  for (int i = 0; i < supplier_count; i++) {
    if (supplier_ds[i].supplier_id == supid) {
      for (int j = i; j < supplier_count - 1; j++) {
        supplier_ds[j] = supplier_ds[j + 1];
      }
      supplier_count--;
      supplier_ds = realloc(supplier_ds, supplier_count);
      break;
    }
  }
}
