/*************************************************************************************************************
* In questo file verranno incluse le funzioni necessarie a costruire un albero binario, e gestirlo tramite
* i puntatori che ogni radice ha verso il figlio destro e il figlio sinistro.
* L'interfaccia è abbastanza semplice, una volta avviato si arriva ad un menu.
* Si consiglia per compilarlo sotto *nix di usare "gcc -o btree binarytree.c" , 
* Per avviarlo invece, come suggerisce l'ERRORE di parametri
* sarà utile seguire la forma ./btree <nomefile>, in cui nomefile può anche contenere il path completo.
* i dati presenti in nomefile devono essere degli interi separati da spazi.
**************************************************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *intfile;

typedef struct T{			//Comincio a definire la struttura che mi servirà
    int value;				//Come posso notare ho il valore attuale e due puntatori: uno al figlio sinistro
    struct T *T_l, *T_r; 	//E l'altro al figlio destro
}*tree, dim;

tree mergetree(int el, tree t1, tree t2){  //Mergetree unisce due alberi
    tree t0 = (tree)malloc(sizeof(dim));
    t0->T_l = t1;
    t0->T_r = t2;
    t0->value = el;
    return(t0);
}

tree createleaf(int el){
    return mergetree(el, NULL, NULL);  //Ogni foglia è formata da un valore e due puntatori nulli
}

int isvoidtree(tree t){  //Verifico che un albero sia vuoto
    return (t == NULL);  //Se non c'è nulla è ovvio che è un albero vuoto...
}

tree leftchild(tree t){  //Restituisce il figlio sinistro accedendo alla struttura tree
    return t->T_l;
}

tree rightchild(tree t){  //Restituisce il figlio destro, accedendo alla struttura tree
    return t->T_r;
}

int root(tree t){  //Restituisce la radice, sempre facendo accesso alla struttura
    return t->value;
}

tree insert(int el, tree t) //Si inserisce un intero el, nell'albero t
{ 
    if(isvoidtree(t)){	//Se l'albero è vuoto, allora verrà creata una foglia
        return createleaf(el);
    }

    if (root(t) >= el){  //Altrimenti si procede da direttive, ovvero se il valore della radice è >= dell'elemento
        return mergetree(root(t), insert(el, leftchild(t)), rightchild(t));  //Andrà a sinistra
    }

    if (root(t) < el) //Se la radice è invece minore dell'elemento, verrà inserita a destra.
        return mergetree(root(t), leftchild(t), insert(el, rightchild(t)));
    else
        return t;
}

int mintree(tree t) //Trovo il minimo per dicotomia: sapendo che più mi muovo in basso
{
    if(isvoidtree(leftchild(t))){
        return root(t);  //Ed a sinistra, più ho un numero piccolo.
    }else{
        return mintree(leftchild(t));  //Ripeto la procedura ricorsivamente.
    }
}

int maxtree(tree t)
{
    if(isvoidtree(rightchild(t))){
        return root(t);  //Come per il minimo, solo che in questo caso
    }else{
        return maxtree(rightchild(t));  //Mi muovo in basso a destra
    }
}

void showtree(tree t)
{
    int i;
    
    if(isvoidtree(t) == false)
    {
        showtree(leftchild(t));
        printf("%d ", root(t));
        showtree(rightchild(t));
    }
}

int n_node(tree t)
{
    if (isvoidtree(t))
        return 0;
    return (n_node(leftchild(t)) + n_node(rightchild(t)) + 1);
}

int height(tree t)
{
    if (isvoidtree(t))
        return 0;
    int left_height = height(leftchild(t));
    int right_height = height(rightchild(t));
    return (1 + std::max(right_height, left_height));
}

int main(int argc, char *argv[])
{
    if(argc<2){  //Controllo che ci siano tutti i parametri
        printf("ERRORE: Per avviare il programma la sintassi è ./btree <file>\n");
        return(1);
    }
    
    if((intfile = fopen(argv[1], "r")) == NULL){  //Apro il file che mi serve
        printf("ERRORE: Non riesco ad aprire il file %s\n", argv[1]);
        return(2);
    }
    
    printf("*Ho aperto il file %s.\n", argv[1]);
    
    int num; //Scansiono il file di interi
    tree albero = NULL;  //Inizializzo l'albero vuoto
    
    while (fscanf(intfile, "%d", &num) != EOF)
        albero = insert(num, albero);

    printf("*Ho costruito l'albero binario\n\n");
    printf("Cosa vuoi fare adesso?\n");
    printf("s: stampare l'albero\n");
    printf("m: cercare il minimo\n");
    printf("M: cercare il Massimo\n");
    printf("n: numero dei nodi\n");
    printf("h: altezza\n");
    printf("u: uscire.\n\n");
    
    char tmp;
    printf(">");
    
    while((tmp = getchar()) != 'u')
    {
        switch (tmp)
        {
            case 's':  //Serve a mostrare l'albero
                 showtree(albero);
                 printf("\n");
            break;
            
            case 'm':  //Stampa a video il valore minimo
                 printf("Il valore minimo dell'albero binario è %d\n", mintree(albero));
            break;
            
            case 'M':  //Stampa a video il valore massimo
                 printf("Il valore massimo dell'albero binario è %d\n", maxtree(albero));
            break;

            case 'n':  //Stampa a video il numero dei nodi
                 printf("I nodi sono %d\n", n_node(albero));
            break;

            case 'h':  //Stampa a video il numero dei nodi
                 printf("Láltezza é %d\n", height(albero));
            
            default:
                printf(">");
            break;
        }
    }
    fclose(intfile);
    
    return(0);
}