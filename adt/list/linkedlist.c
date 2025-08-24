#include "list.h"
#include "../item.h"
#include <stdlib.h>

// We can implement an unordered list or an ordered list
// while considering different complexities:
// Ordered -> Insertion O(n), deletion and search O(log n) using binary search
// Unordered -> Insertion O(1) using a tail link, deletion, and search O(n)

// The following list is unordered meaning we don't mantain order while inserting.
// It is also implemented as a linked list, not as an array-based list,
// which could be used when the size is known in advance and we don't plan on 
// modifying the list (by adding and removing elements) often but just consult it
// The functions also allow maintaining order if necessary.

typedef struct node* link;

struct node {
    Item val;
    link next;
    // There could also be a link to the previous node
};

struct list {
    link head;
    link tail;
    int N; // Current size of the list
};

// Initializes the default values of the list struct
LIST LISTinit() {
    LIST l;
    l = malloc(sizeof(*l));
    l->head = l->tail = NULL;
    l->N = 0;
    return l;
}

static link newNode(Item val, link next) {
    link x;
    x = (struct node*) malloc(sizeof (struct node));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

// Inserts at the head using newNode internally
void LISTinsHead(LIST list, Item val) {
    if (list->head == NULL) // If the list is empty
        list->head = list->tail = newNode(val, NULL);
    else
        list->head = newNode(val, list->head);
    list->N++;
}

// Inserts at the tail (simulating the case where list->tail is not used)
void LISTinsTail(LIST list, Item val) {
    list->N++;
    if (list->head == NULL) {
        list->head = list->tail = newNode(val, NULL);
        return;
    }   
    for (link t = list->head; t->next != NULL; t = t->next);
    t->next = newNode(val, NULL);
}

// Fast insertion at the tail using the tail pointer
void LISTinsTailFast(LIST list, Item val) {
    list->N++;
    if (list->head == NULL) {
        list->head = list->tail = newNode(val, NULL);
        return;
    }
    link x = newNode(val, NULL);
    list->tail->next = x;
    list->tail = x;
}

// Searches for an element in the list
Item LISTsearch(LIST list, Key key) {
    for (link x = list->head; x != NULL; x = x->next)
        if (KEYcompare(KEYget(x->val), key) == 0)
            return x->val;
    return ITEMsetvoid();
}

// Deletes the head node (works for both ordered and unordered lists)
void LISTdelHead(LIST list) {
    if (list->head == NULL)
        return; 
    link t = list->head;
    list->head = t->next;
    if (list->N > 0)
        list->N--;
    if (list->head == NULL)
        list->tail = NULL;
    free(t);
}

// Deletes a node with the specified value from the list
void LISTdelNode(LIST list, Item val) {
    link p, t;
    p = NULL;
    t = list->head;
    for (; t != NULL; p = t, t = t->next) {
        if (KEYcompare(KEYget(t->val), KEYget(val)) == 0) {
            if (p == NULL) {
                list->head = t->next;
                if (list->head == NULL)
                    list->tail = NULL; // Update tail if the list is now empty
            } else {
                p->next = t->next;
                if (t == list->tail)
                    list->tail = p; // Update tail if the deleted node was the tail
            }
            free(t);
            return;
        }
    }
}

// Retrieves the element at the specified index (random access)
// it is more efficient in the array list version
Item LISTget(LIST list, int index) {
    if (index < 0 || index >= list->N) {
        // Handle out-of-bounds access (you can return a null item or handle it as needed)
        return ITEMsetvoid();
    }
    
    link t = list->head;
    for (int i = 0; i < index; i++) {
        t = t->next;
    }
    return t->val;
}

// Modifies the element at the specified index
// it is more efficient in the array list version
void LISTset(LIST list, int index, Item val) {
    if (index < 0 || index >= list->N) {
        // Handle out-of-bounds access (you can throw an error or return)
        return;
    }
    
    link t = list->head;
    for (int i = 0; i < index; i++) {
        t = t->next;
    }
    t->val = val;
}

// Returns the number of elements in the list
int LISTsize(LIST list) {
    return list->N;
}

// Checks if an item exists in the list
int LISTcontains(LIST list, Item val) {
    for (link t = list->head; t != NULL; t = t->next) {
        if (KEYcompare(KEYget(t->val), KEYget(val)) == 0) {
            return 1; // Found the item
        }
    }
    return 0; // Item not found
}

// Clears all elements in the list
void LISTclear(LIST list) {
    while (list->head != NULL) {
        LISTdelHead(list);
    }
}

// Returns an array with all elements in the list
Item* LISTtoArray(LIST list) {
    Item* arr = malloc(list->N * sizeof(Item));
    if (arr == NULL)
        return NULL;
    
    link t = list->head;
    for (int i = 0; t != NULL; t = t->next, i++) {
        arr[i] = t->val;
    }
    return arr;
}
