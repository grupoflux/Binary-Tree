#include <stdio.h>
#include <stdlib.h>

struct folha{
    int valor;
    struct folha *esq;
    struct folha *dir;
};

void inserir(struct folha **arvore, int valor){
    struct folha *atual = *arvore;
    if (atual == NULL){
        struct folha *nova_folha = malloc(sizeof(struct folha));
        nova_folha -> valor = valor;
        nova_folha -> esq = NULL;
        nova_folha -> dir = NULL;

        *arvore = nova_folha;
    }
    else{
        if (valor < atual -> valor)
            inserir(&(atual -> esq), valor);
        else
            inserir(&(atual -> dir), valor);
    }
}

void imprimir (struct folha *arvore){
    struct folha* atual = arvore;
    if (atual != NULL){
        imprimir(atual -> dir);
        printf("%d", atual -> valor);
        imprimir(atual -> esq);
    }
}

int tamanho(struct folha *arvore){
    int contador = 0;
    struct folha *atual = arvore;
    if (tamanho != NULL){
        contador += tamanho(atual -> esq);
        contador++;
        contador += tamanho (atual -> dir);
    } return contador;
}

int main(){
    struct folha* raiz = NULL;

    inserir(&raiz, 10);
    inserir(&raiz, 25);
    inserir(&raiz, 67);
    inserir(&raiz, 50);
    inserir(&raiz, 2);
    /*int num_entrada, valores[10], i;
    scanf("%d", &num_entrada);
    for (i=0; i<= num_entrada; i++){
        scanf("%d", &valores[i]);
        inserir(&raiz, valores[i]);
    }*/
    imprimir(raiz);
    printf("tamanho:%d", tamanho(raiz));
    return(EXIT_SUCCESS);


    return 0;
}
