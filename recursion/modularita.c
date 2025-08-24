// composizione
// effettuo una composizione quando un componente
// e' proprieta' di un altro e lo possiede, in questo modo
// i componenti sono riutilizzabili e si concentrano
// a svolgere un compito specifico, il componente di livello piu' alto
// cioe' che contiene gli altri e' quello a coordinare tutte le operazioni
// possiamo infatti passare semplicemente un riferimento a questo componente
// per ottenere tutti gli altri
// (es. posizione della creatura in un videogioco, implemento con una struct creatura
// con dentro una struct posizione)
// il componente di alto livello e' anche responsabile di creazione e distruzione
// dei suoi sottocomponenti

// aggregazione
// si tratta di una composizione senza possesso
// dove un componente contiene semplicemente un riferimento ad un altro
// e non e' responsabile di questo, non si tratta quindi di una' proprieta' specifica
// dell'oggetto
// (es. dipendenti di un'azienda, perche' loro esistono al di fuori del contesto
// dell'azienda, implementerei con una struct azienda con dentro un puntatore a una lista
// di dipendenti)

// strutture dati contenitore
// un contenitore e' involucro che permette di aggiungere e rimuovere dati omogenei
// una lista o un vettore allocato dinamicamente sono contenitori
// in questo contesto esiste il wrapper ossia una struct che ingloba il contenitore
// e la dimensione del contenitore quindi a tutte le funzioni che utilizzano
// il contenitore basta passare semplicemente questa struct

// programmazione multifile
// file .c, .h (header), .obj .o .exe
// vantaggi di minor tempo di compilazione, facilita' di collaborazione,
// information hiding per rendere lo sviluppo piu' rapido
// 1.c deve includere 1.h e se vuole altri .h
// 1.h puo' includere 2.h se vuole che quando viene incluso venga automaticamente
// includo il 2.h che ha incluso
// architettura a layer:
// 1) il client include creatura.h che include punto.h
// cosi' facendo il client non vede il modulo punto
// 2) il client include creatura.h e punto.h cosi' puo' vedere e chiamare
// funzioni di entrambi i moduli (soluzione preferibile, creatura.h include punto.h)
// #include usa "" invece <> se si tratta di un modulo creato da noi
// #define DBG, #if, #endif compilazione condizionale

// NOTA: static permette di rendere visibile una funzione o variabile globale
// solamente nel file che e' stata definita anche se un client include il suo header

// header guard
// #ifndef _HEADER1
// #define _HEADER1
// ... istruzioni
// #endif
// serve ad evitare che un modulo venga incluso piu' volte

// gcc -c files - usa il compilatore e genera i .o
// gcc files.o - usa il linker e genera un eseguibile (-o per specificare il nome)
// gcc files.c fa tutto insieme (-o per specificare il nome)

