

// nella risoluzione di problemi di ottimizzazione
// il paradigma greedy, a differenza della programmazione dinamica e il divide et impera,
// e' molto piu' facile da realizzare e porta a soluzioni con complessita' decisamente
// inferiore, lo svantaggio e' che queste soluzioni non sono sempre ottime
// si basa sul principio di fare scelte che sono localmente ottime, senza preoccuparsi
// di backtrack e percio' non e' detto che queste portino a una soluzione globalmente
// ottima a causa della mancata esplorazione esaustiva delle soluzioni
// e' necessario scegliere una funzione di appetibilita' sulla base della quale operare
// per ogni problema ossia un criterio su cui ordinare i dati di ingresso
// questa funzione di appetibilita' puo' essere costante oppure variare
// ci sono casi dove si riesce comunque a dimostrare che la programmazione
// greedy porta ad una soluzione ottima come nell'esempio della selezione di attivita'

// in questo esempio ogni attivita' si svolge nelle intervallo
// [si, fi) aperto a sinistra e chiuso a destra
// e dobbiamo trovare il massimo numero di attivita' compatibili
// si puo dimostrare che ordinando per tempo di fine fi le
// varie attivita' possiano risolvere il problema con la programmazione greedy
// quindi scegliamo sempre la prima attivita' perche' tanto toglierei la scelta
// ad altre attivita' che vi si sovrappongono e poi scelgo le attivita' tali che
// sj > fi e cosi' via fino ad esaurimento del vettorej, l'appetibilita' e' il
// tempo di fine

// ci sono casi dove la programmazione greedy non porta ad una soluzione ottima
// ad esempio nel problema del cambia monete
// in questo problema dobbiamo ritornare il resto e abbiamo un certo sistema
// di monete (quindi ad esempio monete che valgono 50, 25, 10, 5, 1... etc)
// dobbiamo utilizzare il numero minimo di monete quindi posso pensare
// che sia ragionevole usare ogni volta la moneta di valore maggiore
// purche' sia minore della somma da ritornare (es. devo ritornare 110, posso usare
// 2 monete da 50 e ora mi resta da ritornare solo 10 e quindi ritorno 10, si tratta
// di una soluzione ottima, ma non e' sempre cosi') per fare cio'
// allora mi basta ordinare in maniera descrescente il vettore che contiene
// il valore delle mie monete e poi iterarlo da 0 a n e modificare il valore da
// ritornare ad ogni passo, l'appetibilita' e' il valore delle monete

// ci sono esempi dove l'appetibilita' potrebbe essere piu complessa
// ad esempio nel problema dello zaino discreto non e' ne' il peso
// ne' il valore bensi il rapporto valore-peso e quindi posso ordinare il vettore
// di oggetti in maniera descrescente rispetto a questo valore specifico
// in ogni caso la soluzione non sarebbe comunque ottima
// mentre invece se consideriamo il problema dello ziano continuo e quindi
// il fatto che possiamo prendere anche una frazione propria dell'oggetto
// allora la funzione di appetibilit' del valore specifico ci porta
// effettivamente ad una soluzione ottima anche molto facilmente realizzabile
// dal punto di vista del codice

// ci sono casi dove la funzione di appetibilita' non e' costante ma variabile
// esempio nei codici di huffman
// si tratta di codici di lunghezza appunto variabile che permettono di
// codificare simboli a frequenza maggiore con una codifica di un numero minore di bit
// rispetto a simboli di frequenza minore (es. la e dell'alfabeto inglese la codifichiamo con 1 bit
// ragionevolmente in quanto e' la lettera piu' frequente) questo approccio rende si' piu' complicata
// la decodifica (per la codifica si tratta semplicemente della giustapposizione dei vari codici)
// rispetto a codici di lunghezza fissa ma permette di risparmiare in spazio di archiviazione
// e soprattuto tempo di trasmissione
// il principio piu' importante dei codici a lunghezza variabile e' il fatto che nessun codice
// sia un prefisso di un altro codice (una regola che non viene rispettata ad esempio nel codice
// morse dove punto linea e' la a mentre punto linea linea e' la w, e per ovviare a questo problema
// durante la trasmissione vengono introdotte delle pause)
// se questo principio viene rispettato allora possiamo realizzare i codici di huffman
// per una qualsiasi codifica grazie alla costruzione di un albero binario
// dove i simboli sono le foglie e abbiamo una serie di aggregati intermedi
// la struttura dati per realizzare praticamente questo albero e' la coda a priorita'
// che puo' essere realizzata da vettore ordinato in maniera crescente
// lista oppure heap, nell'esempio utilizziamo il vettore ordinato
// e prendiamo ad ogni passo i due aggregati (o elementi se si tratta di foglie)
// con frequenza minore e realizziamo graficamente un nuovo aggregato che ha come frequenza
// la somma delle frequenze dei suoi nodi figli la cui codifica viene realizzata
// da uno 0 a sinistra e un 1 a destra, a questo punto reinseriamo l'aggregato
// nel vettore ordinato e procediamo nuovamente fino a che non si esaurisce il vettore
// in questo modo abbiamo realizzato una codifica dove i simboli a priorita' maggiore hanno una codifica
// minore in numero di bit

int main() {
    return 0;
}