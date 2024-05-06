#ifndef DATA_H
#define DATA_H
#include "../../helper/helper.h"
#include <stdbool.h>

#define MAX_LINE_LEN 1000

typedef enum OPCODE { OPADD, OPSET, OPDEL} OPCODE;

typedef struct Log {
  // this represents a line in the log file
  int id;           // operations arranged in ascending order of ids
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
void reconstruct_logfile(char *log_filepath);
void AOF_append(char *log_filepath, Node *n, OPCODE op);

#endif
