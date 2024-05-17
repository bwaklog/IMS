#pragma once
#ifndef SUPPLIERS_H
#define SUPPLIERS_H
#include "../../helper/helper.h"

extern int supplier_count;

void append_supplier(void);
void display_supplier(void);
void update_supplier(void);
void remove_supplier(void);


void addr_filter(char *addr);
void bubble_sort_suppliers(void);

#endif // !SUPPLIERS_H
