// #include "models.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTALBUCKETS 1024

typedef enum CLASS { PRODUCT, SUPPLIER, TRANSACTION } CLASS;

typedef struct intcol {
  int pid;
  int quan;
  int supid;
  int transid;
} intcol;

typedef struct charcol {
  char pname[50];
  char supname[50];
  char supadr[50];
  char trandate[50];
} charcol;

typedef struct floatcol {
  float pprice;
} floatcol;

typedef struct Node {
  CLASS class;
  intcol intcol;
  charcol charcol;
  floatcol floatcol;
} Node;

Node *DATABUCKETS[TOTALBUCKETS];
int ELEMENTS = 0;

void addNode(CLASS class, intcol intcol, charcol charcol, floatcol floatcol) {
  Node *n = (Node *)malloc(sizeof(Node));
  n->class = class;
  n->intcol = intcol;
  n->charcol = charcol;
  n->floatcol = floatcol;

  DATABUCKETS[ELEMENTS] = n;
  ELEMENTS++;
}

void addAllocatedNode(CLASS class, Node *n) {
  DATABUCKETS[ELEMENTS] = n;
  ELEMENTS++;
}

void removedNewLine(char *str) {
    if ((strlen(str) > 0) && (str[strlen(str) - 1] == '\n')) {
        str[strlen(str) - 1] = '\0';
    }
}

void createBucket(CLASS class) {
  Node *n = malloc(sizeof(Node));
  switch (class) {
  case PRODUCT: {
    n->class = PRODUCT;
    printf("PID: ");
    scanf("%d%*c", &n->intcol.pid);

    printf("PNAME: ");
    fgets(n->charcol.pname, 50, stdin);
    removedNewLine(n->charcol.pname);

    printf("PPRICE: ");
    scanf("%f", &n->floatcol.pprice);

    printf("QUAN: ");
    scanf("%d", &n->intcol.quan);

    addAllocatedNode(PRODUCT, n);
    putchar('\n');
    break;
  }
  case SUPPLIER: {
    n->class = SUPPLIER;
    printf("SUPID: ");
    scanf("%d%*c", &n->intcol.supid);

    printf("SUPNAME: ");
    fgets(n->charcol.supname, 50, stdin);
    removedNewLine(n->charcol.supname);

    printf("SUPADR: ");
    fgets(n->charcol.supadr, 50, stdin);
    removedNewLine(n->charcol.supadr);

    addAllocatedNode(SUPPLIER, n);
    putchar('\n');
    break;
  }
  case TRANSACTION: {
    n->class = TRANSACTION;
    printf("TRANSID: ");
    scanf("%d", &n->intcol.transid);

    printf("PID: ");
    scanf("%d", &n->intcol.pid);

    printf("QUAN: ");
    scanf("%d%*c", &n->intcol.quan);

    scanf("TRANDATE: ");
    fgets(n->charcol.trandate, 50, stdin);
    removedNewLine(n->charcol.trandate);

    addAllocatedNode(TRANSACTION, n);
    putchar('\n');
    break;
  }
  default:
    printf("huh\n");
  }
}

int main() {
  /*
   * Mini documentation
   * we have the following classes that are acceptable as a bucket
   * 1. PRODUCT => value 0
   * 2. SUPPLIER => value 1
   * 3. TRANSACTION => value 2
   *
   * To store a bucket inside the databuckets array, call the createBucket
   * method and that will prompt user with required fields and store
   *
   * The structure for the following classes outputs that will be stored in
   * a file in the future are as follows
   * 1. PRODUCT     => class|pid|pname|pprice|quan
   * 2. SUPPLIER    => class|supid|supname|supadr
   * 3. TRANSACTION => class|transid|pid|quan|trandate
   * */

  createBucket(SUPPLIER);
  createBucket(PRODUCT);

  for (int i = 0; i < ELEMENTS; i++) {
    Node *n = DATABUCKETS[i];
    switch (n->class) {
    case PRODUCT: {
      printf("%d|%d|%s|%f|%d\n", n->class, n->intcol.pid, n->charcol.pname,
             n->floatcol.pprice, n->intcol.quan);
      break;
    }
    case TRANSACTION: {
      printf("%d|%d|%d|%d|%s\n", n->class, n->intcol.transid, n->intcol.pid,
             n->intcol.quan, n->charcol.trandate);
      break;
    }

    case SUPPLIER: {
      printf("%d|%d|%s|%s\n", n->class, n->intcol.supid, n->charcol.supname,
             n->charcol.supadr);
      break;
    }

    default:
      printf("huh\n");
    }
  }

  return EXIT_SUCCESS;
}
