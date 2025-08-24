// la funzione di hash e' una funzione U -> {0, 1, ..., M-1}
// che associa ad alcune chiavi K dell'insieme universo U un indice compreso tra 0 e
// M-1, indice del vettore con il quale realizziamo la tabella di simboli
// NOTA: usando chiavi ad accesso diretto dove il vettore ha cardinalita' U
// questo e' impossibile ma siccome molto spesso |K| << |U| questa
// implementazione risulterebbe in un notevole spreco di memoria

// per gestire le collisioni idealmente vorremmo una funzione di hashing
// uniforme semplice che garantirebbe il fatto che le chiavi k sono tutte equiprobabili
// e quindi anche i valori h(k) ma di fatto non si puo' realizzare
// quindi si cerca di scorrelare il piu' possibile h(ki) e h(kj)
// e distribuire tutti gli h(k) in modo uniforme

// di fatto le collisioni sono inevitabili

// esempio di funzione di hash: metodo moltiplicativo
// chiavi: numeri in virgola mobile in un intervallo prefissato s <= k < t
int hash(float k, int M, float s, float t) {
    return ((k-s)/(t-s))*M;
}

// secondo esempio: metodo modulare
// chiavi: numeri interi; M numero primo
int hash2(int k, int M) {
    return (k%M);
}
// il metodo modulare puo' essere utilizzato anche per stringhe
// moltiplichiamo ogni carattere per una potenza di una certa base e sommiamo
// ma questo numero e' enorme:
// es. now = 'n' * 128^2 + 'o' * 128 + 'w' = 1816567
// quindi k = 1816567
// scelgo M = 19
// h(k) = k % M = 15
// NOTA: in applicazioni reali M dovrebbe essere molto grande
// ma noi usiamo valori piccoli per rappresentare esempi (se M fosse piccolo)
// tanto vale non usare neanche la tabella di simboli e fare ricerche lineari)

// possiamo usare anche il metodo di horner che si dimostra essere piu' efficiente
// che consiste nel raccogliere il polinomio in modo da ridurre il numero di moltiplicazioni
// necessarie per calcolare l'hash e poi dopo ovviamente effettuiamo l'operazione modulo M
// per ottenere il valore h(k)

// il metodo modulare risulta fattibile per chiavi di dimensione ridotta ma sembra impossibile
// nel caso di chiavi molto lunghe perche' il numero non e' rappresentabile su un numero ragionevole
// di bit
// si puo' eliminare ad ogni passo i multipli di M anziche' farlo dopo in fase di applicazione del metodo modulare
int hash3(char *v, int M) {
    int h = 0, base = 128;
    for (; *v != '\0'; v++)
        h = (base * h + *v) % M;
    return h;
}

// il ruolo di % M e' molto importante perche' riporta sempre all'interno delle
// dimensioni della tabella di hash (M = dimensione della tabella)