#ifndef ITEM_H
#define ITEM_H

typedef int Key;

typedef struct item {
    Key key;
    char *name;
} Item;

Key KEYget(Item val);
Key KEYscan();
int KEYcompare(Key k1, Key k2);

Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan();
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2);
int ITEMgreater(Item val1, Item val2);
int ITEMcheckvoid(Item val);
int ITEMchecknull(Item val);
Item ITEMsetvoid();
Item ITEMsetNull();

void swap(Item *A, int i, int j);

int NAMEcmp(char *n1, char *n2);
char* NAMEget(Item* val);

#endif // ITEM_H
