#include "data.h"
#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>

Log parse_log(char *log_line) {

  char *token = strtok(log_line, "|");

  if (token == NULL) {
    return (Log){.valid = false};
  }

  Log log;

  // order of operations
  // Operation id | Operation Class type | Operation data

  log.id = atoi(token);
  latest_log_id = log.id;

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

void reconstruct_logfile(char *log_filepath) {
  FILE *log_file = fopen(log_filepath, "r");
  if (log_file == NULL) {
    printf("Log file provided [%s] is faulty\n", log_filepath);
    exit(1);
  }

  char log_line[MAX_LINE_LEN];

  while (fgets(log_line, MAX_LINE_LEN, log_file)) {
    Log log = parse_log(log_line);

    switch (log.class_type) {
    case PRODUCT: {
      printf("[%d]PRODUCT: %d | %s | %f | %d\n", log.id,
             log.data.product.product_id, log.data.product.product_name,
             log.data.product.product_price, log.data.product.product_quantity);
      break;
    }
    case SUPPLIER: {
      printf("[%d] SUPPLIER: %d | %s | %s\n", log.id,
             log.data.supplier.supplier_id, log.data.supplier.supplier_name,
             log.data.supplier.supplier_addr);
      break;
    }
    case TRANSACTION: {
      printf("[%d] TRANSACTION: %d | %d | %d | %s\n", log.id,
          log.data.transaction.transaction_id,
          log.data.transaction.transaction_product_id,
          log.data.transaction.transaction_quantity,
          log.data.transaction.transaction_date);
      break;
    }
    }
  }

  fclose(log_file);
}

void AOF_append(char *log_filepath, Node *n) {
    FILE *log_file = fopen(log_filepath, "a+");
    if (log_file == NULL) {
        printf("Log file provided [%s] is faulty\n", log_filepath);
        exit(1);
    }

    Log log;
    log.class_type = n->node_class;

    switch (log.class_type) {
        case PRODUCT: {
            log.data.product = n->node_data.product;
            break;
        }
        case SUPPLIER: {
            log.data.supplier = n->node_data.supplier;
            break;
        }
        case TRANSACTION: {
            log.data.transaction = n->node_data.transaction;
            break;
        }
        default:
            break;
    }

    // get latest id
    log.id = latest_log_id + 1;
    log.valid = true;

    // append the struct to the file
    fwrite(&log, sizeof(Log), 1, log_file);
    fclose(log_file);

}
