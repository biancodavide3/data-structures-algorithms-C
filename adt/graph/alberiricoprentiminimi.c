// albero ricoprente minimo = albero estratto da un grafo pesato non orientato che tocca
// tutti i vertici con archi di peso minimo

// rappresentare un MST (minimum spanning tree)
// vettore dei padri st e vettore dei pesi wt dove il vertice e' indicato dall'indice

// posso usare calcolo combinatorio -> complessita esponenziale

// approccio greedy la cui soluzione e' comunque ottima (garantito)

// taglio e' una partizione dell'insieme di vertici V in S e V-S
// quindi ci sono degli archi che attraversano questo taglio
// e l'arco a peso minimo tra questi si dice leggero

// teorema archi sicuri (usato per algoritmo di prim)
// A sottoinsieme di E e' contenuto in un qualche albero ricoprente minimo, inizialmente A e' vuoto
// S e V-S e' un taglio che rispetta A
// (u,v) e' un arco leggero
// allora (u,v) e' un arco sicuro per A

// corollario (usato per algoritmo di kruskal)
// considero la foresta di alberi inizialmente formata da ogni vertice del grafo
// se l'arco leggero (u,v) connette un albero C a un altro albero della foresta
// allora (u,v) e' un arco sicuro per A

// algoritmo di kruskal
// facile dal punto di vista teorico basta considerare gli archi partendo da peso crescente
// e mano a mano connettere la foresta inizialmente composta da alberi dove ogni albero e' un singolo vertice del grafo
// fino a quando non e' tutto connesso
// todo codice realizzato grazie a adt union find

// algoritmo di prim
// si basa sul teorema
// vettore fr frangia?