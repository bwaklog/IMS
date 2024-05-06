CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g

DEPS = helper/helper.c src/data/data.c src/products/products.c src/transactions/transactions.c src/suppliers/suppliers.c
SRC = "src/main.c"


all:
	gcc ${CFLAGS} ${DEPS} ${SRC} -o main
