#pragma once
#ifndef SUPPLIERS_H
#define SUPPLIERS_H
#include "../../helper/helper.h"

#define MAX 5

extern int supplier_count;

extern int supplier_ids[MAX];
extern char supplier_names[MAX][MAX_STR_LEN];
extern char supplier_address[MAX][MAX_STR_LEN];

void append_supplier(void);
void display_supplier(void);
void update_supplier(void);
void remove_supplier(void);

#endif // !SUPPLIERS_H
