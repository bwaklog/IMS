#pragma once
#ifndef PRODUCTS_H
#define PRODUCTS_H
#include "../../helper/helper.h"

extern int product_count;

// helper functions
int get_product_quantity(int pid);
void update_stock(int pid, int withdrawn);

extern int product_ids[MAX];
extern char product_names[MAX][MAX_STR_LEN];
extern float product_prices[MAX];
extern int product_quantities[MAX];

void append_product(void);
void display_product(void);
void update_product(void);
void remove_product(void);

#endif // !PRODUCTS_H
