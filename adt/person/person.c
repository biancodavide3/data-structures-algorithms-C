#include "person.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct person {
    Key key;
    char* name;
    int age;
};

Person newPerson(Key k, char* name, int age) {
    Person p = malloc(sizeof(*Person));
    p->key = k;
    p->name = malloc(strlen(name) + 1);
    strcpy(p->name, name);
    p->age = age;
    return p;
}

void freePerson(Person p) {
    free(p->name);
    free(p);
}

Key getKey(Person p) {
    return p->key;
}

int compareKeys(Key k1, Key k2) {
    if (k1 > k2)
        return 1;
    else if(k1 < k2)
        return -1;
    else
        return 0;
}

void sayHello(Person p) {
    printf("Hello, my name is %s and I am %d years old",
           p->name, p->age);
}

void happyBirthday(Person p) {
    (p->age)++;
    printf("Happy birthday %s! You are now %d years old",
           p->name, p->age);
}

void changeName(Person *p, char *newName) {
    free((*p)->name);
    (*p)->name = malloc(strlen(newName) + 1);
    strcpy((*p)->name, newName);
}