#ifndef BST_H
#define BST_H

#include "../item.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
Item BSTsearch(BST bst, Key k);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leftR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
void BSTvisit(BST bst, int strategy);

#endif