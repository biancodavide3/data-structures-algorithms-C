#ifndef PERSON_H
#define PERSON_H

// sto dichiarando solo un puntatore
// a struct person rinominandolo Person
// in modo che si tratti di un adt di prima classe
// devo usare la memoria dinamica

typedef struct person* Person;
typedef int Key;

Person newPerson(Key k, char* name, int age);
void freePerson(Person p);

Key getKey(Person p);
int compareKeys(Key k1, Key k2);

void sayHello(Person p);
void happyBirthday(Person p);
void changeName(Person* p, char *newName);
#endif