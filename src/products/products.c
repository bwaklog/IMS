#include "products.h"
#include "../../helper/helper.h"
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>

int get_product_quantity(int pid) {
    int hash = generate_hash(pid);
    Node *ptr = prod_map[hash];

    while (ptr != NULL) {
        if (ptr->node_data.product.product_id == pid) {
            return ptr->node_data.product.product_quantity;
        }
        ptr = ptr->next;
    }

    return 0;
}

void update_stock(int pid, int withdrawn) {

    int hash = generate_hash(pid);
    Node *ptr = prod_map[hash];

    while (ptr != NULL) {
        if (ptr->node_data.product.product_id == pid) {
            ptr->node_data.product.product_quantity -= withdrawn;
            return;
        }
        ptr = ptr->next;
    }
}

void append_product(void) {
    if (product_count == MAX) {
        printf("Product limit reached\n");
        return;
    }

    Node *pnode = (Node *)malloc(sizeof(Node));

    if (pnode == NULL) {
        printf("FAILED: memory allocation\n");
        return;
    }

    printf("Enter product id: ");
    int pid;
    scanf("%d%*c", &pid);

    //  checking for existing id, exit if found
    if (check_existing(pid, PRODUCT)) {
        printf("=== PREXISTING ID FOUND ===\n");
        return;
    }

    pnode->node_data.product.product_id = pid;

    printf("Enter product name: ");
    scanf("%[^\n]%*c", pnode->node_data.product.product_name);

    printf("Enter product price: ");
    scanf("%f%*c", &pnode->node_data.product.product_price);

    printf("Enter product quantity: ");
    scanf("%d%*c", &pnode->node_data.product.product_quantity);

    int hash = generate_hash(pnode->node_data.product.product_id);

    Node *head = prod_map[hash];

    if (head == NULL) {
        prod_map[hash] = pnode;
    } else {
        Node *temp = head;
        pnode->next = temp;
        prod_map[hash] = pnode;
    }

    product_count++;
}

void display_product(void) {

    if (product_count == 0) {
        printf("=== NO PRODUCTS ===\n");
        return;
    }

    for (int i = 0; i < MAPSIZE; i++) {
        Node *ptr = prod_map[i];

        if (ptr == NULL) {
            continue;
        }
        while (ptr != NULL) {
            printf("%p > %d|%s|%f|%d\n", (void *)ptr, ptr->node_data.product.product_id,
                   ptr->node_data.product.product_name,
                   ptr->node_data.product.product_price,
                   ptr->node_data.product.product_quantity);

            ptr = ptr->next;
        }
    }
}

void update_product(void) {
    int pid;
    printf("Enter PID to update: ");
    scanf("%d%*c", &pid);

    // check for prexisting id, exit if function returns 0
    if (!check_existing(pid, PRODUCT)) {
        printf("=== NO SUCH PRODUCT EXISTS ===\n");
        return;
    }

    Node *ptr = prod_map[generate_hash(pid)];

    if (ptr == NULL) {
        printf("Empty\n");
        return;
    }

    while (ptr != NULL) {
        if (ptr->node_data.product.product_id == pid) {
            char buff[MAX_STR_LEN];

            printf("Hit Enter to accept current value\n");
            printf("Product Name(%s): ", ptr->node_data.product.product_name);
            // accept default if enter pressed

            fgets(buff, MAX_STR_LEN, stdin);
            if (buff[0] != '\n') {
                remove_newlien_char(buff);
                printf("%s\n", buff);
                strcpy(ptr->node_data.product.product_name, buff);
            }

            printf("Product Price(%f): ", ptr->node_data.product.product_price);
            fgets(buff, MAX_STR_LEN, stdin);
            if (buff[0] != '\n') {
                remove_newlien_char(buff);
                ptr->node_data.product.product_price = atof(buff);
            }

            printf("Product Count(%d): ", ptr->node_data.product.product_quantity);
            fgets(buff, MAX_STR_LEN, stdin);
            if (buff[0] != '\n') {
                remove_newlien_char(buff);
                ptr->node_data.product.product_quantity = atoi(buff);
            }

            return;
        }
    }
}

void remove_product(void) {
    // delete element from an array
    int pid;
    printf("Enter PID to delete: ");
    scanf("%d%*c", &pid);

    // check for prexisting id, exit if function returns 0
    if (!check_existing(pid, PRODUCT)) {
        printf("=== NO SUCH PRODUCT EXISTS ===\n");
        return;
    }

    int hash = generate_hash(pid);

    Node *ptr = prod_map[hash];
    Node *prev = NULL;

    if (ptr == NULL) {
        printf("No such product\n");
    }

    while (ptr != NULL) {
        if (ptr->node_data.product.product_id == pid) {
            printf("Product found at %p, replacing with %p\n", (void *)ptr, (void *)ptr->next);
            if (prev == NULL) {
                prod_map[hash] = ptr->next;
            } else {
                prev->next = ptr->next;
            }
            free(ptr);
            product_count--;
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}
