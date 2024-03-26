#pragma once
#ifndef SUPPLIERS_H
#define SUPPLIERS_H
#include "../../helper/helper.h"

#define MAX 5

extern int supplier_count;

extern int supplier_ids[MAX];
extern char supplier_names[MAX][MAX_STR_LEN];
extern char supplier_address[MAX][MAX_STR_LEN];

void append_supplier();
void display_supplier();
void update_supplier();
void remove_supplier();

#endif // !SUPPLIERS_H
