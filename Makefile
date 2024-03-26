mainfile = "src/main.c"
helperfile = "helper/helper.c"
products = "src/products/products.c"
transactions = "src/transactions/transactions.c"
suppliers = "src/suppliers/suppliers.c"


all:
	gcc ${helperfile} ${products} ${transactions} ${suppliers} ${mainfile} -o main
