#pragma once
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "../../helper/helper.h"

#define MAX 5

extern int transaction_count;

void append_transaction(void);
void display_transaction(void);
void update_transaction(void);

#endif // !TRANSACTIONS_H
