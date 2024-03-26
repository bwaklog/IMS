#pragma once
#ifndef PRODUCTS_H
#define PRODUCTS_H
#include "../../helper/helper.h"

#define MAX 5

extern int product_count;

extern int product_ids[MAX];
extern char product_names[MAX][MAX_STR_LEN];
extern float product_prices[MAX];
extern int product_quantities[MAX];

void append_product();
void display_product();
void update_product();
void remove_product();

#endif // !PRODUCTS_H
