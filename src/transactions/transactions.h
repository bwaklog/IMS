#pragma once
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "../../helper/helper.h"

#define MAX 5

extern int transaction_count;

extern int transaction_ids[MAX];
extern int transaction_product_ids[MAX];
extern int transactions_quantities[MAX];
extern char transaction_dates[MAX][MAX_STR_LEN];

void append_transaction(void);
void display_transaction(void);
void update_transaction(void);

#endif // !TRANSACTIONS_H
