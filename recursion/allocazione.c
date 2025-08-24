#include <stdlib.h>
#include <stdio.h>

// ci sono due tipi di variabili: globali, generalmente sconsigliate
// in un programma c in quanto rendono meno modulare e di piu' difficile
// comprensione e organizzazione il programma stesso (non si tratta di costanti
// definite attraverso la direttiva #define ma variabili tipo java)
// e locali ossia quelle che sono sempre state dichiarate all'interno di funzioni

// le variabili si classificano in base a visibilita' (le variabili globali
// sono visibili da ogni funzione nel programma c mentre quelle locali solo dalla
// funzione che la ha dichiarate), tempo di vita in memoria (le variabili globali
// rimangono fino al termine dell'esecuzione del programma mentre nel caso di
// variabili locali il programma e' in grado di riconoscere che una certa funzione
// non viene chiamata piu' e che quindi non e' necessario memorizzare ancora
// le variabili da essa utilizzate), e in fine allocazione nella memoria
// (le variabili globali si trovano in una regione della memoria vicina
// a quella delle istruzioni del programma mentre quelle locali sono memorizzate
// nello stack, in un opportuno stack frame ossia una porzione dello stack
// che basta per memorizzare tutte le variabili locali

// sono variabili locali anche i parametri da passare a una funzione

// il compiler e' quel programma che e' in grado di tradurre una serie di istruzioni
// c in un codice macchina che dipende dall'architettura del processore
// (arm vs x86, instruction set computer e il relativo linguaggio assembler)
// il compiler in particolare si occupa di controllare la sintassi del programma,
// se le parole riservate sono scritte correttamente, se le parentesi aperte sono state chiuse
// dopo subentra il linker che e' in grado di risolve i collegamenti a funzioni di libreria
// o altre funzioni da noi create in un programma multi-file e generare l'eseguibile
// infine subentra il loader che e' colui che carica il programma eseguibile generato
// dal linker in memoria principale in modo che esso possa essere eseguito

// static in c limita la visibilita' di una variabile globale al solo file c
// in cui e' stata dichiarata, mentre per una variabile locale
// significa solo che questa esiste in memoria come una qualsiasi variabile globale
// ma rimane visibile solamente all'interno della funzione dove viene dichiarata

// allocazione dinamica ossia esplicita e quindi gestita dal programmatore
// la memoria dinamica si trova nella heap (attenzione a non confonderla con
// l'adt, si tratta proprio di uno spazio di memoria) e per usarla
// bisogna utilizzare i puntatori
// malloc richiede un parametro in size ossia la dimensione in byte da allocare e ritorna
// void* come tipo permette di assegnare questo valore a qualsiasi puntatore
// si usa insieme a sizeof

// regola della differenza di un asterisco tra il cast esplicito,
// non obbligatorio ma consigliato, e l'espressione passata all'interno di
// sizeof (es. int** matrix = (int **) malloc(n *sizeof(int*)); ossia
// un vettore di puntatori di dimensione n)

// dopo aver allocato memoria bisogna usare la free
// che libera tutta la quantita' di memoria allocata a un puntatore
// non e' tanto importante quando termina l'esecuzione del programma
// perche' la memoria sarebbe liberata comunque
// e' cruciale per evitare di avere memory leak (quando rialloco
// una variabile puntatore senza averla prima liberata, allora quella
// memoria risultera' inutilizzata)
// e' importante quando si realizzano programmi dove l'allocazione di memoria
// avviene ad esempio in loop ed e' necessario un continuo riallocamento

// calloc si puo' usare per allocare vettori e richiede una size e un numero n
// che indica quanti elementi contiene il vettore ed ha costo O(n)

// realloc permette di riallocare un puntatore ad una nuova dimensione

// tutte le funzioni di allocazione ritornano NULL se non e' disponibile la memoria richiesta

// passaggio by reference e by pointer
// esempio per una funzione che alloca una matrice dinamica
// (puo' essere gestita come un singolo vettore monodimensione di dimensione nr * nc
// e poi calcoliamo l'indice come nc*i + j tecnica row major, oppure come vettore di puntatori)
// adotto il secondo approccio

// i parametri possono essere passati by value o by reference
// 1) by value e' la pratica piu' utilizzata in cui il valore iniziale
// non viene modificato e se ne ha una copia all'interno della funzione
// che viene modificata
// 2) by reference quando questi cambiamenti all'interno della funzione
// si rispecchiano anche sul valore originale che viene passato come parametro

// l'implementazione effettiva delle due tecniche varia da linguaggio a linguaggio
// ma generalmente in c per passare by value si richiede il valore stesso come parametro
// mentre per passare by reference si richiede un puntatore al valore da modificare
// (quindi possiamo evitare ad esempio di usare return se usiamo il passaggio by reference)

// in python ci sono tipi mutabili come list (by reference) ed altri immutabili come int, str (by value)

// in java si parla di oggetti e quindi il passaggio avviene by value
// posso modificare il valore a cui punta una variabile riassegnandolo con l'operatore new

int **malloc2dByValue(int nr, int nc) {
    int **m, i;
    m = (int **)malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++)
        m[i] = (int *)malloc(nc * sizeof(int));
    return m;
}

void malloc2dByPointer(int ***m, int nr, int nc) {
    int i;
    *(m) = (int **)malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++)
        *(m)[i] = (int *) malloc(nc * sizeof(int));
}

void free2d(int **m, int nr) {
    int i;
    for (i = 0; i < nr; i++)
        free(m[i]);
    free(m);
}

int main() {
    int nr = 5;
    int nc = 4;
    int **mv = malloc2dByValue(nr, nc);
    int **mp;
    malloc2dByPointer(&mp,nr, nc);
    free2d(mp, nr);
    free2d(mv, nr);
    return 0;
}