// todo: esercitarsi su qualche problema di ottimizzazione
// nei problemi di ottimizzazione oltre a fare una ricerca
// ci vogliamo assicurare che la soluzione sia ottima rispetto
// a una certa funzione di massimo, minimo o un criterio da rispettare

// esempio del conto corrente
// abbiamo una lista di movimenti memorizzata come vettore di interi
// se l'intero e' positivo si tratta di un'entrata altrimenti di un'uscita
// il conto parte da 0
// trovare l'ordinamento per il vettore dei movimenti tale che la differenza tra
// la cifra massima mai avuta sul conto e quella minima mai avuta sul conto sia minima
// nota: qualsiasi sia l'ordinamento alla fine ci sara' sempre la stessa cifra sul conto
// soluzione: permutazioni semplici per ottenere tutti gli ordinamenti
//  e usare una variabile per tenere traccia del valore corrente della differenza da
//  minimizzare e aggiornarla solo se ci troviamo in un caso migliore del precedente


// esempio dello zaino
// uno zaino ha un peso massimo
// abbiamo un vettore di oggetti dove per ognuno e' specificato il peso e il valore
// vogliamo trovare la combinazione di oggetti da mettere nello zaino la cui somma dei
// pesi sia minore del peso massimo dello zaino ma che abbia valore complessivo maggiore
// soluzione: powerset e un'altra funzione per verificare se abbiamo migliorato il
//  valore precedente o no
// si potrebbe applicare pruning in questo problema perche' se supero la capacita' massima
// tutte le ricorsioni successive a quel passo sarebbero inutili

// alcuni problemi di ottimizzazione possono essere risolti utilizzando la programmazione dinamica
// il requisito per applicarla e' che la struttura della soluzione al problema sia ottima e cioe'
// che tutti i sottoproblemi siano risolti in maniera ottima fino al raggiungimento della soluzione
// la programmazione dinamica opera bottom up (a differenza della ricorsione top down) ma anche top down
// con memorizzazione della soluzione parziale (memoization)
// si usa una soluzione ricorsiva con i modelli del calcolo combinatorio
// a cui ispirarsi per costruire la soluzione bottom up
// la programmazione dinamica risolve un problema fondamentale della ricorsione
// ossia il fatto che questa assume tutti i sotto problemi indipendenti tra di loro
// ad esempio nel calcolo dei numeri di fibonacci

// esempio catena di montaggio
// ci sono 2 catene di montaggio 0 e 1 lunghe n stazioni
// l'obiettivo e' raggiungere la fine della catena con il costo minore possibile
// tenendo conto che sono noti il costo di lavorazione in ogni stazione,
// quello per cambiare stazione e quello per continuare sulla stessa catena e' nullo
// notiamo innanzi tutto che esplorando lo spazio delle soluzioni con semplice ricorsione
// si tratta solo di verificare se il cammino svolto alla fine sia migliore di quello precedente
// ma la complessita' e' esponenziale...
// possiamo applicare la programmazione dinamica perche' ad ogni stazione possiamo supporre
// di essere arrivati in modo ottimo o dalla stessa catena in cui ci troviamo o dall'altra
// costruire quindi innanzi tutto il valore della soluzione e un vettore ausiliario
// che ad ogni passaggio ci dice da quale stazione proveniamo
// successivamente grazie a questo vettore possiamo ricostruire la soluzione ottima
// ossia l'insieme di stazioni che ci porta a pagare il costo minimo
// si tratta quindi di un algoritmo di complessita' lineare in quanto c'e' un solo for loop

// esempio prodotto tra matrici
// trovare la parantizzazione per cui il costo di eseguire la moltiplicazione
// per di un numero n di matrici di dimensioni diverse ma sempre compatibili sia minimo

// esistono problemi dove la programmazione dinamica non e' applicabile come ad esempio
// il problema dei cammini massimi (non e' detto che per andare dal noto u al nodo v,
// passando dal nodo u al nodo w il cammino sia massimo) quindi questo problema non
// presenta una sottostruttura ottima, si tratta infatti di uno dei problemi np (Non Polinomiale) completo
// se si riuscisse a trovare una soluzione polinomiale ad uno di questi problemi
// allora lo so riuscirebbe a fare anche per tutti gli altri problemi np
// il problema dei cammini minimi presenta invece una sottostruttura ottima

// la programmazione dinamica deve anche essere conveniente da applicare
// perche' il numero di sottoproblemi generati e' generalmente polinomiale
// e questi sottoproblemi devono anch'essi essere risolti in tempo ragionevole
// ad esempio nel problema della longest increasing sequence
// si genera un numero polinomiale di sottoproblemi ognuno dei quali si risolve
// con complessita' anch'essa polinomiale e quindi la complessita' totale e' O(n^2)
// interessante vedere come a partire dal vettore P che memorizza l'indice
// dell'elemento precedente nella LIS si usi una funzione ricorsiva per ricostruire la
// soluzione LISprint(int *val, int *p, int i) che viene chiamata per la prima volta con il valore last
// per il parametro i e che printa in ordine corretto il risultato della soluzione
// c'e' anche un vettore L che memorizza la lunghezza massima della LIS
// per ogni prefisso i del vettore (si scandisce con due for loop 0 < i < n e 0 < j < i)

// ultimo esempio longest common subsequence
// (basi di ACGT del dna)