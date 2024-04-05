#pragma once
#ifndef PRODUCTS_H
#define PRODUCTS_H
#include "../../helper/helper.h"

extern int product_count;

// helper functions
int get_product_quantity(int pid);
void update_stock(int pid, int withdrawn);

void append_product(void);
void display_product(void);
void update_product(void);
void remove_product(void);

#endif // !PRODUCTS_H
