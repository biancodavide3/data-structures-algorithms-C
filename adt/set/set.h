#include "../item.h"

// can be implemented as ordered/unordered list/array
// list dimension can virtually grow to infinity, while array must be resized if necessary
// complexity of SETsearch
    // ordered array -> binary search -> O(log(N))
    // unordered array -> linear search -> O(N)
    // list (ordered/unordered) -> linear search -> O(N)
// complexity of SETunion and SETintersection
    // array/list ordered -> O(N)
    // array/list unordered -> O(N^2)

// insertion, deletion, allocation, freeing functions
// are given for granted as they were covered in arraylist.c and linkedlist.c

void SETsearch(SET s, Key k);
SET SETunion(SET s1, SET s2);
SET SETintersection(SET s1, SET s2);