#ifndef BT_H
#define BT_H

#include "../item.h"

typedef struct node* link;
typedef struct binarytree* BT;

BT BTcreate();
void BTdestroy(BT bt);
int BTcount(BT bt);
int BTheight(BT bt);
void BTpreOrder(BT bt);
void BTinOrder(BT bt);
void BTpostOrder(BT bt);
int BTisFull(BT bt);
int BTisPerfect(BT bt);
int BTisComplete(BT bt);
int BTisDegenerate(BT bt);
// add more...

#endif