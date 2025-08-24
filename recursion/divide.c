#include <stdlib.h>
#include <stdio.h>

// divide et impera
// esplorazione dello spazio possibile delle soluzioni
// si tratta di problemi di ricerca o di ottimizzazione
// ricerca dove tra tutte le soluzioni vogliamo sapere quante sono ed elencarle
// ottimizzazione tutte le soluzioni vanno bene ma dobbiamo scegliere quelle ottime
// secondo una determinata funzione
// usiamo la ricorsione perche' lo spazio delle soluzioni puo' essere descritto da
// un albero dove il numero di scelte ad ogni passaggio e' un livello
// il numero di questi livelli e' l'altezza dell'albero e le foglie sono tutte le
// possibili soluzioni

// quando la struttura dati su cui operiamo e' una coda (FIFO) la ricerca e' in ampiezza (breadth-first),
// una pila (LIFO) la ricerca e' in profondita'
// una coda a priorita' la ricerca e' best-first

typedef struct {
    int* scelte;
    int num_scelte;
} Livello;

// val e' la rappresentazione dell'albero
// sol e' il vettore che contiene la soluzione
// pos indica a che livello siamo nell'albero
// n e' il totale di livelli dell'albero
// cnt e' il contatore del numero di soluzioni trovate
int princ_mult(Livello *val, int *sol, int pos, int n, int cnt) {
    int i;
    // condizione di terminazione printo le soluzioni e incremento
    if (pos >= n) {
        for (i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt +1;
    }
    // per ogni scelta possibile la memorizzo e passo con la ricorsione al livello successivo
    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] = val[pos].scelte[i];
        // la chiamata ricorsiva ritorna cnt che viene aggiornato ogni volta che siamo in un caso terminale
        // qui tutte le soluzioni vanno bene
        cnt = princ_mult(val, sol, pos+1, n, cnt);
    }
    // ritorno del conto finale alla chiamata originale della funzione
    return cnt;
}

// backtracking quando una delle scelte si rivela essere scorretta
// utilizzo di un vettore mark i cui elementi assumono 0 o 1 a seconda se
// l'elemento i-esimo e' stato gia' considerato
// disposizioni semplici, n cardinalita' di sol e mark, k cardinalita' di val (altezza dell'albero)
// da ora in poi val per semplicita' e' un vettore di interi evitando la complessita' relativa alla struct
// per le permutazioni con ripetzione mark assume un ruolo diverso: registra quanti occorrenze
// dell'elemento i-esimo sono rimaste e ogni volta che se ne prende una mark[i]--
// in fase di backtracking mark[i]++
int disp(int *val, int *sol, int *mark, int n, int k, int pos, int cnt) {
    int i;
    // terminazione
    if (pos >= k) {
        for (i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt +1;
    }
    // esplorazione
    for (i = 0; i < k; i++) {
        // se la scelta non e' stata fatta
        if (mark[i] == 0) {
            // registriamo la soluzione e markiamo come fatta
            sol[pos] = val[i];
            mark[i] = 1;
            cnt = disp(val, sol, mark, n, k, pos+1, cnt);
            // se non abbiamo raggiunto un caso terminale devo smarcare la scelta (backtracking)
            mark[i] = 0;
        }
    }
    return cnt;
}

// non uso piu' il vettore mark
int disp_rip(int *val, int *sol, int n, int k, int pos, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt +1;
    }
    for (i = 0; i < n; i++) {
        sol[pos] = val[i];
        cnt = disp_rip(val, sol, n, k, pos+1, cnt);
    }
    return cnt;
}

// caso particolare delle disposizioni dove n = k
int perm(int *val, int *sol, int *mark, int n, int pos, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt +1;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] == 0) {
            sol[pos] = val[i];
            mark[i] = 1;
            cnt = perm(val, sol, mark, n, pos+1, cnt);
            mark[i] = 0;
        }
    }
    return cnt;
}

// mark memorizza il numero di occorrenze rimaste per ogni elemento distinto di dist_val
int perm_rip(int *dist_val, int *sol, int *mark, int n, int pos, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            cnt = perm_rip(dist_val, sol, mark, n, pos+1, cnt);
            mark[i]++;
        }
    }
    return cnt;
}

// nelle combinazioni uso un indice start per forzare un ordinamento nella ricorsione
int comb(int *val, int *sol, int start, int n, int k, int pos, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = comb(val, sol, i+1, n, k, pos+1, cnt);
    }
    return cnt;
}
// il powerset puo' essere realizzato con le disposizioni ripetute o combinazioni semplici
// qui il modello realizzato con le disposizioni ripetute con due rami di ricorsione
// dove in uno includiamo l'elemento corrente e nell'altro no
// non c'e' il vettore val perche' genero un vettore di dimensione n
// dove ogni elemento e' 0 o 1, a questo punto utilizzando una corrispondenza per indice
// con un altro vettore di dimensione n ottengo tutti i sottoinsiemi (0 indica che l'elemento
// non appartiene mentre 1 si)
int powerset_disp_r(int *sol, int n, int pos, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt +1;
    }
    // includo l'elemento
    sol[pos] = 1;
    cnt = powerset_disp_r(sol, n, pos+1, cnt);
    // back track, non includo l'elemento
    sol[pos] = 0;
    cnt = powerset_disp_r(sol, n, pos+1, cnt);
    return cnt;
}

// nelle combinazioni con ripetizione incremento start al ritorno
int comb_r(int *val, int *sol, int start, int n, int k, int pos, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++)
            printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = comb(val, sol, start, n, k, pos+1, cnt);
        start++;
    }
    return cnt;
}

// algoritmo di er per il calcolo di partizioni
// nel vettore sol all'elemento i-esimo corrisponde il numero del blocco a cui appartiene
// es. sol = {0, 0, 1} l'elemento il primo e il secondo elemento appartengono al blocco 0 mentre
// il terzo elemento appartiene al blocco 1
// m # di blocchi in cui partizionare
void er(int *sol, int *val, int pos, int n, int m) {
    int i, j;
    if (pos >= n) {
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                if (sol[j] == i)    // per ogni blocco tra 0 e m-1 se l'elemento appartiene a quel blocco
                    // (corrispondenza dell'elemento j-esimo del vettore sol con l'indice del blocco allora stampo
                    printf("%d ", sol[j]);
        printf("\n");
        return;
    }
    // due rami di ricorsione
    for (i = 0; i < m; i++) {
        // qui attribuiamo il blocco i-esimo con 0 <= i < m all'elemento in posizione pos e passiamo avanti
        sol[pos] = i;
        er(sol, val, pos+1, n, m);
    }
    // al ritorno attribuiamo anche il blocco m-esimo e ricorriamo di nuovo
    sol[pos] = m;
    er(sol, val, pos+1, n, m);
}

// ma cosa succede se lo spazio delle soluzioni e' troppo grande per essere esplorato
// interamente e quindi non posso permettermi di controllare se la soluzione e'
// corretta nella terminazione come nel problema di einstein
// ((5!)^5 ~ 25 miliardi di casi?)
// posso eseguire pruning e quindi potare lo spazio delle soluzioni rimuovendo
// anticipatamente soluzioni che sono sicuro non possano essere corrette
// non esiste una metodologia generale ma poso basarmi su un approccio basato su
// 1) un filtro statico che non dipende dalle scelte precedenti
// 2) un filtro dinamico che dipende dalle scelte precedenti
// 3) validazione di una soluzione parziale nella speranza di comprendere che non possa
// essere valida


int main() {
    int n = 3, *sol, i, j;
    Livello *val;

    val = malloc(n * sizeof(Livello));
    val[0].num_scelte = 2;
    val[1].num_scelte = 3;
    val[2].num_scelte = 2;
    for (i = 0; i < n; i++)
        val[i].scelte = malloc(val[i].num_scelte * sizeof(int));
    sol = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < val[i].num_scelte; j++)
            val[i].scelte[j] = j;
    printf("Il numero di soluzioni per questo esempio e' %d",
           princ_mult(val, sol, 0, n, 0));

    for (i = 0; i < n; i++)
        free(val[i].scelte);
    free(val);
    free(sol);
    return 0;
}