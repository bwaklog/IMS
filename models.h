#define MAX_PRODUCTS 50
#define MAX_SUPPLIERS 50
#define MAX_TRANSACTIONS 100


/* Class Enum : Prod, Supplier & Transaction*/
typedef enum CLASS {
    PRODUCT,
    SUPPLIER,
    TRANSACTION
} CLASS;

/* Product Structure */
typedef struct ProductNode {
  int productID;
  char productName[1024];
  float productPrice;
  int productQuantity;
  struct ProductNode *next;
} ProductNode;

/* Supplier Structure */
typedef struct SupplierNode {
  int supplierID;
  char supplierName[1024];
  char supplierAddress[1024];
  struct SupplierNode *next;
} SupplierNode;

/* Transaction Structure */
typedef struct TransactionNode {
  int transactionID;
  int productID;
  int quantity;
  char transactionDate[1024];
  struct TransactionNode *next;
} TransactionNode;
