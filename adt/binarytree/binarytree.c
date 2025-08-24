#include "binarytree.h"
#include <stdlib.h>
#include <stdio.h>

struct node {
    Item val;
    link left;
    link right;
};

struct binarytree {
    link root;
};

BT BTcreate() {
    BT bt;
    bt = malloc(sizeof(struct binarytree));
    bt->root = NULL;
    return bt;
}

static void destroy(link root) {
    if (root == NULL) 
        return;
    destroy(root->left);
    destroy(root->right);
    free(root);
}

void BTdestroy(BT bt) {
    destroy(bt->root);
    free(bt);
}

static int count(link root) {
    if (root == NULL)
        return 0;
    return count(root->left) + count(root->right) + 1;
}

int BTcount(BT bt) {
    return count(bt->root);  
}

static int height(link root) {
    int u, v;
    if (root == NULL) 
        return -1;
    u = height(root->left);
    v = height(root->right);
    if (u > v)  // return the height of the right child tree in case they are the same
        return u + 1;
    return v + 1;
}

int BTheight(BT bt) {
    return height(bt->root);  
}

// tree traversal with recursion can suffer of stack overflow if there are too many
// recursion calls, this problem can be solved with iterative traversal with stack
// R for recursive
static void preR(link root) {
    if (root == NULL)
        return;
    ITEMshow(root->val);
    pre(root->left);
    pre(root->right);
}

// I for iterativate
// pop from stack and push right child first
static void preI(link root) {
    if (root == NULL) 
        return;

    link stack[100], curr;    
    int top = -1;   

    stack[++top] = root; 

    while(top >= 0) {
        curr = stack[top--];
        ITEMshow(curr->val);
        if (curr->right)
            stack[++top] = curr->right;
        if (curr->left)
            stack[++top] = curr->left;
    }

}

// Print the nodes of the binary tree in pre-order traversal
void BTpreOrder(BT bt) {
    pre(bt->root);
}

static void inR(link root) {
    if (root == NULL)
        return;
    in(root->left);
    ITEMshow(root->val);
    in(root->right);
}

// push entire left tree first then pop then move to right child
static void inI(link root) {
    if (root == NULL)
        return;

    link stack[100], curr;
    int top = -1;

    stack[++top] = root;

    while (curr != NULL || top >= 0) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        curr = stack[top--];
        ITEMshow(curr->val);
        curr = curr->right;
    }
}

// Print the nodes of the binary tree in in-order traversal
void BTinOrder(BT bt) {
    in(bt->root);
}

static void postR(link root) {
    if (root == NULL)
        return;
    post(root->left);
    post(root->right);
    ITEMshow(root->val);
}

// use 2 stacks
// pop from first and push into second
// push left child and right child into first again (opposite order to pre)
// iterate second stack at the end
static int postI(link root) {
    if (root == NULL)
        return;

    link stack1[100], stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        link node = stack1[top1--];
        stack2[++top2] = node;
        if (node->left)
            stack1[++top] = node->left;
        if (node->right)
            stack2[++top] = node->right;
    }

    while (top2 >= 0) {
        ITEMshow(stack[top2--]->val)
    }
}   


void BTpostOrder(BT bt) {
    post(bt->root);
}

// look for a single case that violates the rule
// recombine the result accordingly
static int full(link root) {
    if (root == NULL)
        return 1;

    link l, r;
    l = root->left;
    r = root->right;

    if ((l == NULL && r != NULL) || (l != NULL && r == NULL))
        return 0;

    return full(root->left) && full(root->right);
}

// a BT is full if every node has 0 or 2 children (no node has only 1 child)
int BTisFull(BT bt) {
    return full(bt->root); 
}

// use height pointer to return by reference 
// in proper return value if the subtree is perfect or not
static int perfect(link root, int *height) {
    // height of a NULL tree is 0 and is a perfect tree
    if (root == NULL) {
        *height = 0;
        return 1;
    }

    // heights of left and right subtree local variables where the value is returned via pointer
    int lh = 0, rh = 0;
    int isLeftPerfect, isRightPerfect;
    
    // the return via pointer
    isLeftPerfect = perfect(root->left, &lh);
    isRightPerfect = perfect(root->right, &rh);

    // return height to caller
    *height = lh + 1;

    // check the heights returned and the condition for a full tree
    if (lh != rh)
        return 0;
    if ((root->left == NULL) != (root->right == NULL))
        return 0;

    return isLeftPerfect && isRightPerfect;
}

// a BT is perfect if it is full and all leaves are on the same level
int BTisPerfect(BT bt) {
    int height = 0;
    return perfect(bt->root, &height);
}

static int completeR(link root, int index, int count) {
    if (root == NULL)
        return 1;
    if (index >= count)
        return 0;
    return complete(root->left, index*2 + 1, count) &&
        complete (root->right, index*2 + 2, count); 
}

// a BT is complete all levels are full except for the last one where nodes are missing
// only starting from the right with no gaps (functional property of the heap)
// indeed use the relations
// LEFT(i) = i*2 + 1
// RIGHT(i) = i*2 + 2
// if the index is out of bounds it's not complete
int BTisComplete(BT bt) {
    int count = BTcount(bt);
    return complete(bt->root, 0, count);
}

static int degenerate(link root) {
    if (root == NULL)
        return 1;
    
    if (root->left != NULL && root->right != NULL)
        return 0;

    return degenerate(root->left) && degenerate(root->right);
}

// a BT is degenerate if it is basically a list
int BTisDegenerate(BT bt) {
    return degenerate(bt->root);
}