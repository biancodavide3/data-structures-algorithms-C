#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Key KEYget(Item val) {
    return val.key;
}

Key KEYscan() {
    Key k;
    printf("Enter key: ");
    scanf("%d", &k);
    return k;
}

int KEYcompare(Key k1, Key k2) {
    return (k1 > k2) - (k1 < k2);
}

Item ITEMnew() {
    Item val;
    val.key = -1;
    val.name = NULL;
    return val;
}

void ITEMfree(Item val) {
    free(val.name);
}

Item ITEMscan() {
    Item val;
    val.key = KEYscan();
    val.name = (char *)malloc(100 * sizeof(char));
    if (val.name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter name: ");
    scanf("%99s", val.name);
    return val;
}

void ITEMshow(Item val) {
    printf("Key: %d, Name: %s\n", val.key, val.name);
}

int ITEMless(Item val1, Item val2) {
    return val1.key < val2.key;
}

int ITEMgreater(Item val1, Item val2) {
    return val1.key > val2.key;
}

int ITEMcheckvoid(Item val) {
    return val.key == -1 && val.name == NULL;
}

int ITEMchecknull(Item val) {
    return val.name == NULL;
}

Item ITEMsetvoid() {
    return ITEMnew();
}

Item ITEMsetNull() {
    Item val;
    val.key = -1;
    val.name = NULL;
    return val;
}

void swap(Item *A, int i, int j) {
    Item temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int NAMEcmp(char *n1, char *n2) {
    return strcmp(n1, n2);
}

char* NAMEget(Item* val) {
    return val->name;
}
