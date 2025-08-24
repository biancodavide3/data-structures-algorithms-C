#include "st.h"
#include <stdlib.h>

// usiamo la strategia open addressing dove non c'e' piu' un vettore di liste
// ma un solo vettore dove memorizziamo tutti gli elementi
// M e' sempre quante caselle sono disponibili nel vettore e
// ovviamente deve essere N <= M

struct symtab { Item *a; int N; int M };

int STsizeSet(int maxN, int alpha);

ST STinit(int maxN, float alpha) {
    int i;
    ST st = malloc(sizeof (*st));
    st->N = 0;
    st->M = STsizeSet(maxN, alpha);
    if (st->M == -1)
        st = NULL;
    else {}
    st->a = malloc(st->M * sizeof(Item));
    for (i = 0; i < st->M; i++)
        st->a[i] = ITEMsetNull();
    return st;
}

// funzioni di probing
// cosa facciamo quando la casella e' gia presa?
// a seconda della strategia di probing ne prendiamo un'altra
// linear probing
// quadratic probing
// double hashing
// un problema dell'open addressing e' il clustering, cioe' il raggruppamento
// di posizione occupate contigue

int hash(Key k, int M);
int hashU(Key k, int M);

static int full(ST st, int i) {
    if (ITEMchecknull(st->a[i]))
        return 0;
    return 1;
}

// semplicemente incremento di 1 e l'indice e rifaccio modulo M
void STinsertlinearprobing(ST st, Item item) {
    int i = hash(KEYget(item), st->M);
    while (full(st, i))
        i = (i+1) % st->M;
    // uso % M per rimanere sempre dentro il vettore
    // es. se mi trovo quasi alla fine del vettore e continuo a scorrere con i = i + 1
    // prima o poi uscirei invece con % M appena supero l'ultimo indice e raggungo la lunghezza
    // i = M allora M % M fa 0 e quindi ritorno all'inizio del vettore
    // suppongo che ci sia spazio nel vettore se no non ha senso
    st->a[i] = item;
    st->N++;
}

Item STsearchlinearprobing(ST st, Key k) {
    int i = hash(k, st->M);
    while (full(st, i))
        if (KEYcompare(KEYget(st->a[i]), k) == 0)
            return st->a[i];
        else
            i = (i + 1) % st->M;
    return ITEMsetNull();
}

// se si vogliono eseguire operazioni di cancellazione di fatto non si usa l'open addressing
// perche' queste romperebbero delle catene di collisioni
// se c'e' stata una collisione in una certa casella ad esempio la 4
// e nella mia ST ho la E in casella 4 e la R in casella 5 (l'hash della sua chiave e' 4
// ma grazie al linear probing viene memorizzata nella casella 5)
// ora cancello la E e quindi la casella 4 e' vuota, se ora cerco la R vado alla casella 4
// senza scorrere alla 5 e di fatto la ricerca fallisce e la R non viene trovata

// si potrebbe realizzare una soluzione dove si cancella l'elemento di interesse e si
// reinseriscono tutti i valori di un cluster (attenzione non faccio un semplice shift del vettore)

// quadratic probing cerca di evitare cluster troppo numerosi
// dove invece di usare un incremento lineare i = (i+1) % M
// si usa un incremento quadratico basato su 2 coefficienti

#define c1 1
#define c2 1

Item STsearchQuadraticProbing(ST st, Key k) {
    int i = 0, start = hash(k, st->M), index = start;
    while(full(st, index))
        if (KEYcompare(k, KEYget(st->a[index])) == 0)
            return st->a[i];
        else {
            i++;
            index = (start + c1 * i + c2 * i * i);
        }
    return ITEMsetNull();
}

// un'altra tecnica per evitare gli effetti del clustering e' il double hashing
// provo in i = h1(k) se e' pieno provo in i = (i + j) % M
// dove j = h2(k) ovviamente bisogna evitare che il nuovo valore di i sia diverso
// da quello precedente perche' altrimenti si entra all'interno di un ciclo infinito
// e per farlo h2 non deve mai ritornare 0 e neaanche h2 % M deve mai ritornare 0



