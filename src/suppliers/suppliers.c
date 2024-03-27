#include "suppliers.h"
#include "../../helper/helper.h"
#include <stdio.h>
#include <string.h>

void append_supplier(void) {
  if (supplier_count == MAX) {
    printf("supplier limit reached\n");
    return;
  }
  printf("Enter supplier id: ");
  int supid;
  scanf("%d%*c", &supid);

  if (check_existing(supid, supplier_ids, supplier_count)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }
  supplier_ids[supplier_count] = supid;

  printf("Enter supplier name: ");
  fgets(supplier_names[supplier_count], MAX_STR_LEN, stdin);
  remove_newlien_char(supplier_names[supplier_count]);

  printf("Enter supplier address: ");
  fgets(supplier_address[supplier_count], MAX_STR_LEN, stdin);
  remove_newlien_char(supplier_address[supplier_count]);

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
    strcpy(sname, supplier_names[i]);
    strcpy(saddr, supplier_address[i]);
    // truncate the string
    if (strlen(sname) > 20) {
      sname[20] = '\0';
    }
    if (strlen(saddr) > 20) {
      saddr[20] = '\0';
    }
    printf("%-10d\t\t%-20s\t\t%-s\n", supplier_ids[i], sname, saddr);
  }
}

void update_supplier(void) {
  int supid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &supid);

  if (!check_existing(supid, supplier_ids, supplier_count)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  for (int i = 0; i < supplier_count; i++) {
    if (supplier_ids[i] == supid) {
      // this is temp storage for each input
      char buff[MAX_STR_LEN];

      printf("Hit Enter to accept current value\n");
      printf("supplier Name(%s): ", supplier_names[i]);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(supplier_names[i], buff);
      }

      printf("supplier address(%s): ", supplier_address[i]);
      // accept default if enter pressed
      fgets(buff, MAX_STR_LEN, stdin);
      if (buff[0] != '\n') {
        remove_newlien_char(buff);
        printf("%s\n", buff);
        strcpy(supplier_address[i], buff);
      }
    }
  }
}

void remove_supplier(void) {
  // delete element from an array
  int supid;
  printf("Enter PID to update: ");
  scanf("%d%*c", &supid);

  if (!check_existing(supid, supplier_ids, supplier_count)) {
    printf("=== EXISTING SUPPLIER ID FOUND ===\n");
    return;
  }

  for (int i = 0; i < supplier_count; i++) {
    if (supplier_ids[i] == supid) {
      for (int j = i; j < supplier_count - 1; j++) {
        supplier_ids[j] = supplier_ids[j + 1];
        strcpy(supplier_names[j], supplier_names[j + 1]);
        strcpy(supplier_address[j], supplier_address[j + 1]);
      }
      supplier_count--;
      break;
    }
  }
}
