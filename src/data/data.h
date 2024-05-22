#ifndef DATA_H
#define DATA_H
#include "../../helper/helper.h"
#include <stdbool.h>

#define MAX_LINE_LEN 1000

typedef enum OPCODE { OPADD, OPSET, OPDEL } OPCODE;

typedef struct Log {
  // this represents a line in the log file
  CLASS class_type; // product, supplier or transaction

  union data {
    Product product;
    Supplier supplier;
    Transaction transaction;
  } data;

  OPCODE op;

  bool valid;
} Log;

extern int latest_log_id;

Log parse_log_hr(char *log_line);
void reconstruct_data(char *store_filepath);
void store_to_file(char *filename, Node *n, OPCODE op);

#endif
