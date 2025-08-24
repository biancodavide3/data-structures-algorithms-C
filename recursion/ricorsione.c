#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// T(n) = D(n) + aT(n/b) + C(n)
// T(1) = 1

// T(n) e' il costo che poi esprimo come O grande o theta grande
// n e' la dimensione del problema che voglio ridurre
// D(n) e' il costo della divisione
// a il numero di sottoproblemi
// T(n/b) il costo del sottoproblema (assumendo sia divide and conquer e che il fattore b sia costante)
// C(n) il costo della ricombinazione

// sviluppo unfolding
// scrivo alcuni passi della T(n) finche' non trovo un pattern che si ripete
// lo esprimo come sommatoria (es. somma di potenze del 2, somma di 1...)
// i cui estremi vanno da 0 al numero di passi che mi servono per arrivare al caso unitario (T(1) = 1)
// (es. divide and conquer, b = 2 -> n / (2^i) = 1 risolvo per i per sapere quanti passi)
// infine uso la formula della progressione geometrica per trovare un'espressione analitica
// sommatoria(x^i con i da 0 a k) = (x^(k+1) - 1) / (x - 1)

// albero della ricorsione
// le chiamate ricorsive ritornano quando raggiungono la condizione di terminazione
// divide (decrease) and conquer divido il problema in sottoproblemi piu' semplici
// dal caso elementare ricombino verso l'alto con una formula che mi permette di risolvere il problema
// esempio (confronto di massimo >)
// funzioni tail recursive (ultima operazione da eseguire e' la chiamata ricorsiva)
// vs funzioni non tail recursive, le prime sono preferibili perche' non usano la stack
// che memorizza i parametri delle chiamate di ogni funzioni che se sono troppi causano stack overflow
// inoltre funzioni tail recursive direttamente trasformabili ad iterative mentre invece
// non tail recursive richiedono la gestione manuale dello stack come struttura dati astratta (ADT)

// immagine le chiamate
// show(x, 0, 3) -> {show(x, 0, 1) -> [show(x, 0, 0) show(x, 1, 1)] show(x, 2, 3) ->
// [show(x, 2, 2) show(x, 3, 3]}... nei vari casi a volte complicato puo' aiutare un disegno
// a = 2 (2 sottoproblemi) divide and conquer di fattore b = 2 nessuna ricombinazione, non tail recursive
void show(int x[], int l, int r) {
    if (l >= r)
        return;
    int m = (l + r) / 2;
    show(x, l, m);
    //show(x, m+1, r);
    printf("xl = ");
    for (int i = l; i <= m; i++)
        printf("%d ", x[i]);
    printf("\n");
    show (x, m+1, r);
    printf("xr = ");
    for (int i = m+1; i <= r; i++)
        printf("%d ", x[i]);
    printf("\n");
}

// a = 2, b = 2 costo di ricombinazione unitario, non tail recursive
int max(int x[], int l, int r) {
    int u, v, m;
    if (l == r)
        return x[l];
    m = (l + r) / 2;
    u = max(x, l, m);
    v = max(x, m + 1, r);
    if (u > v)
        return u;
    return v;
}

// decrease and conquer di fattore b = 1, a = 1 nessuna ricombinazione, non tail recursive
void reverse(char *s) {
    if (*s != '\0') {
        reverse(s + 1);
        putchar(*s);
    }
}

// divide and conquer b = 2, nonostante cio' a = 1, tail recursive
int binSearch(int a[], int l, int r, int x) {
    if (l >= r)
        return -1;
    int m = (l+r) / 2;
    if (a[m] == x)
        return m;
    if (x > a[m])
        return binSearch(a, m+1, r, x);
    return binSearch(a, l, m, x);
}

unsigned long factTail(int n, unsigned long t) {
    if (n == 0)
        return t;
    return factTail(n-1, n*t);
}

unsigned long factNonTail(int n) {
    if (n == 0)
        return 1;
    return n * factNonTail(n-1);
}

// nell'ordinamento usiamo una struct item generica
// qui per semplicita' corrisponde a un int
typedef int Item;
int itemLeq(Item a, Item b) {
    return a <= b;
}
int itemLt(Item a, Item b) {
    return a < b;
}
int itemGt(Item a, Item b) {
    return a > b;
}
// prototipi
void mergeSort(Item a[], Item b[], int n);
void mergeSortR(Item a[], Item b[], int l, int r);
void merge(Item a[], Item b[], int l, int q, int r);

void mergeSort(Item a[], Item b[], int n) {
    int l, r;
    l = 0;
    r = n - 1;
    mergeSortR(a, b, l, r);
}

// non in loco usa un vettore b, stabile
void mergeSortR(Item a[], Item b[], int l, int r) {
    // divide et impera
    if (l >= r)
        return;
    int q = (l + r)/2;
    // applico il merge sort al sottovettore sx e dx
    mergeSortR(a, b, l, q);
    mergeSortR(a, b, q+1, r);
    // ricombino eseguendo la merge
    merge(a, b, l, q, r);
}

void merge(Item a[], Item b[], int l, int q, int r) {
    // il risultato sara' un vettore di doppia dimensione rispetto a quella di un sottovettore
    // i indice che tiene conto della posizione nel sottovettore sx
    // j indice che tiene conto della posizione nel sottovettore dx
    // k indice che tiene conto della posizione nel vettore risultato b
    int i, j, k;
    i = l;
    j = q+1;
    for (k = i; k <= r; k++)
        if (i > q)  // esaurito vettore sx
            b[k] = a[j++];
        else if (j > r)     // esaurito vettore dx
            b[k] = a[i++];
        // less equal garantisce la stabilita' dell'algoritmo
        else if (itemLeq(a[i], a[j]))   // confronto elemento indice i minore di quello a j
            b[k] = a[i++];
        else
            b[k] = a[j++];  // confronto opposto restante
    // copio b in a
    for (k = l; k <= r; k++)
        a[k] = b[k];
}

void quickSort(Item a[], int n);
void quickSortR(Item a[], int l, int r);
int partition(Item a[], int l, int r);
void swap(Item a[], int i, int j);

// stabile, non in loco
void quickSort(Item a[], int n) {
    int l, r;
    l = 0;
    r = n -1;
    quickSortR(a, l, r);
}

void quickSortR(Item a[], int l, int r) {
    // divide et impera pero' il pivot q viene calcolato
    // ad ogni passaggio per sottovettore destro e sinistro
    int q;
    if (l >= r)
        return;
    q = partition(a, l, r);
    quickSortR(a, l, q-1);
    quickSortR(a, q+1, r);
    // no ricombinazione
}

int partition(Item a[], int l, int r) { // a' la haere
    int i, j;
    i = l -1;   // i e' prima del primo elemento
    j = r;
    Item x = a[r];  // pivot
    for (;;) {  // non strutturato, usciamo quando i >= j
        while (itemLt(a[++i], x));
        // scorro i finche' non punta a un elemento maggiore del pivot
        // significa che il while va avanti finche' gli elementi sono minori del pivot
        // e quindi in posizione corretta... appena il while si esaurisce il preincremento garantisce
        // che puntiamo sempre a quell'elemento e non al successivo
            // nota che itemLt fallisce automaticamente quando i punta all'ultimo elemento perche' e' minore stretto
        while (itemGt(a[--j], x))
            // scorro j finche' non punta a un elemento minore del pivot
            // pero' qui devo controllare che j non esca fuori dall'array (a differenza di prima che era
            // una proprita' intrinseca del confronto nel while)
            if (j == l)
                break;
        if (i >= j) // i j si scambiano abbiamo esaurito i sotto vettori e passiamo alla prossima chiamata
            break;
        swap(a, i, j);  // scambio gli elementi fuori posto ad ogni iterazione
    }
    swap(a, i, r);  // scambio l'elemento a posizione i con il pivot
    return i;   // i sara' il nuovo pivot
}

void swap(Item a[], int i, int j) {
    Item temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void print(int a[]) {
    for (int i = 0; i < 8; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void) {
//    int x[] = {1, 2, 3, 4};
//    int l = 0;
//    int r = 3;
//    show(x, l, r);
//    printf("il max e' %d\n", max(x, l, r));
//    char s[] = "Hello World";
//    char *scpy = malloc(sizeof (char) * strlen(s));
//    strcpy(scpy, s);
//    reverse(scpy);
//    printf("\n");
//    free(scpy);
//    printf("L'indice di 3 e' %d\n", binSearch(x, l, r, 3));
//    printf("%lu", factTail(65, 1));
    int a[] = {4, 3, 1, 9, 8, 5, 7, 4};
    int b[8];
    quickSort(a, 8);
    print(a);
    return 0;
}




