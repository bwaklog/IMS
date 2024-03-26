```text
    ______  ___
   /  _/  |/  /______  _______
   / // /|_/ / ___/ / / / ___/
 _/ // /  / (__  ) /_/ (__  )
/___/_/  /_/____/\__, /____/
                /____/
Inventory Management System written in C
```

> All the below can be found in commit `7a7f3e`

## FUTURE: Structures and storage

We have the following classes that are acceptable as a bucket
1. `PRODUCT`        : value `0`
2. `SUPPLIER`       : value `1`
3. `TRANSACTION`    : value `2`

A Node (or bucket) is a structure type that holds mini columns like a database record. It is limited to integer string and float columns as that covers the requirements of the case study so far. Each of these columns is a strcture in itself. From analysis of the data types, i've created these mini column structures that hold the following properties

**intcol**

```C
typedef struct intcol {
  int pid;
  int quan;
  int supid;
  int transid;
} intcol;
```

**floatcol**

```C
typedef struct floatcol {
    float pprice;
} floatcol;
```

**charcol**

```C
typedef struct charcol {
    char pname[50];
    char supname[50];
    char supadr[50];
    char trandate[50];
} charcol;
```

> `pid` was the only shared field between the structures of PRODUCT and TRANSACTION. So is quantity, but they aren't in relation

To store a bucket inside the databuckets array, call the createBucket
method and that will prompt user with required fields and store

The structure for the following classes outputs that will be stored in
a file in the future are as follows
1. `PRODUCT`        : `class|pid|pname|pprice|quan`
2. `SUPPLIER`       : `class|supid|supname|supadr`
3. `TRANSACTION`    : `class|transid|pid|quan|trandate`

## Todo
- [ ] Querrying from file
- [ ] Storage of buckets
- [ ] Modifying value of buckets
- [ ] Deleting Buckets
- [ ] Implementing a more dynamic Datastructure
