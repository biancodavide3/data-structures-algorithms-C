// primo problema
// un grafo e' aciclico se e solo se nella dfs non troviamo archi di tipo BACK
// questo non ci fa pero' trovare effettivamente quali siano i cicli

// secondo problema
// identificare le componenti connesse in un grafo non orientato
// uso un vettore cc dove l'indice indica quale vertice e il valore a quale componente connessa appartiene (opportunamente numerate da 0 come 0,1,2...)
// sfrutto la dfs perche' ogni albero di essa e' una componente connessa
// nel codice della dfs ignoro l'etichettatura e pre e post...
// uso solo cc[v] = id all'inizio della funzione ricorsiva
// dove id viene incrementato all'interno della chiamata dalla wrapper alla funzione ricorsiva
// e quindi se ho fatto delle iterazioni del famoso for per garantire l'esplorazione di tutto l'albero allora
// significa che ho cambiato componente connessa cioe' albero nella dfs

// terzo problema
// connettivita' se elimino ponte (arco che disconnette il grafo se lo tolgo)
// se elimino punto di articolazione (vertice e quindi tutti gli archi che vi insistono che disconnette il grafo se lo tolgo)
// punto di articolazione
// v e' un punto di articolazione se e' la radice e ha almeno due figli nell'abero della dfs
// v e' un punto di arcolazione se ha un figlio s tale che da lui o un suo discendente non vi sia alcun
// arco di tipo back a un antenato proprio di v // todo fare esercizi su questo concetto vedi video al minuto 14
// bridge
// un arco puo' essere o back o tree nei grafi non connessi
// un arco di tipo back non puo' essere un bridge perche' esiste sicuro un cammino formato da archi tree
// un arco di tipo tree (v, w) e' bridge se e solo se non esistono archi di tipo back tra un
// discendente di w e un antenato di v
// algoritmo banale togliere vertice o archi e riverificare la connettivita'

// DAG directed acyclic graph (grafo orientato non aciclo)
// nodi sorgente e nodi scolo
// ordinamento topologico tutti gli archi puntano verso destra
// ordinamento topologico inverso tutti gli archi puntano verso sinistra
// l'ordinamento topologico e' unico se e solo esiste un cammino di hamilton orientato
// ossia un cammino semplice che tocca tutti i vertici
// todo funzione ordinamento topologico inverso

// componenti fortemente connesse (grafi orientati)
// algoritmo di kosaraju
// trasporre il grafo
// eseguire dfs sul grafo trasposto calcolando tempi di scoperta e fine elaborazione
// eseguire dfs sul grafo originale per tempi di fine descrescenti
// gli alberi dell'ultima dfs sono le componenti formente connesse
// todo funzione algoritmo di kosaraju


