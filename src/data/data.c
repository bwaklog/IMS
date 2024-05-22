#include "data.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/stat.h>

int latest_log_id = 0;

Log parse_log_hr(char *log_line) {

  char *token = strtok(log_line, "|");

  if (token == NULL) {
    return (Log){.valid = false};
  }

  Log log;

  // order of operations
  // Operation Type | Operation Class Type | Operation data
  log.op = (OPCODE)atoi(token);

  token = strtok(NULL, "|");
  log.class_type = (CLASS)atoi(token);
  token = strtok(NULL, "|");

  switch (log.class_type) {
  case PRODUCT: {
    char operation[MAX_LINE_LEN];
    strcpy(operation, token);

    char *opr_token = strtok(operation, ",");
    // structure for Product
    // ID,Name,Price,Quantity
    log.data.product.product_id = atoi(opr_token);

    opr_token = strtok(NULL, ",");
    strcpy(log.data.product.product_name, opr_token);

    opr_token = strtok(NULL, ",");
    log.data.product.product_price = atof(opr_token);

    opr_token = strtok(NULL, ",");
    log.data.product.product_quantity = atoi(opr_token);

    log.valid = true;

    return log;
  }
  case SUPPLIER: {
    char *opr_token = strtok(token, ",");
    log.data.supplier.supplier_id = atoi(opr_token);

    opr_token = strtok(NULL, ",");
    strcpy(log.data.supplier.supplier_name, opr_token);

    opr_token = strtok(NULL, ",");
    strcpy(log.data.supplier.supplier_addr, opr_token);

    log.valid = true;
    return log;
  }
  case TRANSACTION: {

    char *opr_token = strtok(token, ",");
    log.data.transaction.transaction_id = atoi(opr_token);

    opr_token = strtok(NULL, ",");
    log.data.transaction.transaction_product_id = atoi(opr_token);

    opr_token = strtok(NULL, ",");
    log.data.transaction.transaction_quantity = atoi(opr_token);

    opr_token = strtok(NULL, ",");
    strcpy(log.data.transaction.transaction_date, opr_token);

    log.valid = true;
    return log;
  }
  default:
    break;
  }

  return (Log){.valid = false};
}

char *translate_OPCODE(OPCODE op) {
  switch (op) {
  case OPADD: {
    return "ADD";
  }
  case OPSET: {
    return "UPDATE";
  }
  case OPDEL: {
    return "DELETE";
  }
  default: {
    return "INVALID";
  }
  }
}

void reconstruct_data(char *store_filepath) {
  FILE *store_file = fopen(store_filepath, "r");

  if (store_file == NULL) {
    // create file store_filepath

    store_file = fopen(store_filepath, "w");
    if (store_file == NULL) {
      perror("Error in reading file");
      return;
    }

    fclose(store_file);

    store_file = fopen(store_filepath, "r");
    if (store_file == NULL) {
      perror("Error in opening file\n");
      return;
    }
  }

  char line[MAX_STR_LEN];

  // while (fgets(line, MAX_STR_LEN, store_file) != NULL) {
  while (fgets(line, MAX_STR_LEN, store_file)) {

    Node *n = (Node *)malloc(sizeof(Node));
    Log log = parse_log_hr(line);

    switch (log.class_type) {
    case PRODUCT: {
      printf("PRODUCT %s: %d | %s | %f | %d\n", translate_OPCODE(log.op),
             log.data.product.product_id, log.data.product.product_name,
             log.data.product.product_price, log.data.product.product_quantity);
      n->node_data.product = log.data.product;
      n->node_class = PRODUCT;
      break;
    }
    case SUPPLIER: {
      printf("SUPPLIER %s: %d | %s | %s\n", translate_OPCODE(log.op),
             log.data.supplier.supplier_id, log.data.supplier.supplier_name,
             log.data.supplier.supplier_addr);
      n->node_data.supplier = log.data.supplier;
      n->node_class = SUPPLIER;
      break;
    }
    case TRANSACTION: {
      printf("TRANSACTION %s: %d | %d | %d | %s\n", translate_OPCODE(log.op),
             log.data.transaction.transaction_id,
             log.data.transaction.transaction_product_id,
             log.data.transaction.transaction_quantity,
             log.data.transaction.transaction_date);
      n->node_data.transaction = log.data.transaction;
      n->node_class = TRANSACTION;
      break;
    }
    }

    switch (log.op) {
    case OPADD: {
      append_to_map(n);
      break;
    }
    case OPDEL: {
      switch (n->node_class) {
      case PRODUCT: {
        remove_from_map(n->node_data.product.product_id, PRODUCT);
        break;
      }
      case SUPPLIER: {
        remove_from_map(n->node_data.supplier.supplier_id, SUPPLIER);
        break;
      }
      case TRANSACTION: {
        remove_from_map(n->node_data.transaction.transaction_id, TRANSACTION);
        break;
      }
      default:
        break;
      }
      break;
    case OPSET: {
      switch (n->node_class) {
      case PRODUCT: {
        update_node(n->node_data.product.product_id, PRODUCT, n);
        break;
      }
      case SUPPLIER: {
        update_node(n->node_data.supplier.supplier_id, SUPPLIER, n);
        break;
      }
      case TRANSACTION: {
        update_node(n->node_data.transaction.transaction_product_id,
                    TRANSACTION, n);
        break;
      }
      default:
        break;
      }

      break;
    }
    default:
      break;
    }
    }
  }
  fclose(store_file);
}

// Operation id | Operation Class type | Operation data
// write data to file in this manner
void store_to_file(char *filename, Node *n, OPCODE op) {
  FILE *store_file = fopen(filename, "a+");
  if (store_file == NULL) {
    printf("[ERR] Store file %s provided is faulty\n", filename);
    perror("Error in opening file\n");
    exit(1);
  }
  switch (n->node_class) {
  case PRODUCT: {
    fprintf(store_file, "%d|%d|%d,%s,%f,%d\n", op, PRODUCT,
            n->node_data.product.product_id, n->node_data.product.product_name,
            n->node_data.product.product_price,
            n->node_data.product.product_quantity);
    break;
  }
  case SUPPLIER: {
    fprintf(store_file, "%d|%d|%d,%s,%s\n", op, SUPPLIER,
            n->node_data.supplier.supplier_id,
            n->node_data.supplier.supplier_name,
            n->node_data.supplier.supplier_addr);
    break;
  }
  case TRANSACTION: {
    fprintf(store_file, "%d|%d|%d,%d,%d,%s\n", op, TRANSACTION,
            n->node_data.transaction.transaction_id,
            n->node_data.transaction.transaction_product_id,
            n->node_data.transaction.transaction_quantity,
            n->node_data.transaction.transaction_date);
    break;
  }
  default: {
    break;
  }
  }

  fclose(store_file);
}
