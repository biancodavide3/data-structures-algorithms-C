#include "person.h"
#include <stdio.h>

int main(void) {
    Person david = newPerson(1, "david", 20);
    printf("%d\n", getKey(david));
    sayHello(david);
    happyBirthday(david);
    freePerson(david);
    return 0;
}