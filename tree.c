# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct folha{
    int valor;
    int identidade[80];
    struct folha *cima;
    struct folha *baixo;
};

void inserir(struct folha **arvore, int id, int pontos) {
    struct folha *atual = arvore;

    if (atual == NULL){
        struct folha *nova_folha = malloc(sizeof(struct folha));
        nova_folha -> identidade[len(atual -> identidade)+1] = id; //trabalhar nessa expressão
        nova_folha -> valor = pontos;
        nova_folha -> cima = NULL;
        nova_folha -> baixo = NULL;

        *arvore = nova_folha;
    }
    else{
        if (pontos < atual -> valor)
            inserir(&(atual -> baixo), id, pontos);
        else if (pontos < atual -> valor)
            inserir(&(atual -> cima), id, pontos);
        else if (pontos == atual -> valor)
            inserir(&(atual -> cima), id, pontos);
    }
}

void imprimir (struct folha *arvore){
    struct folha* atual = arvore;
    if (atual != NULL){
        imprimir(atual -> cima);
        printf("%d", atual -> valor);
        imprimir(atual -> baixo);
    }
}

int tamanho(struct folha *arvore){
    int contador = 0;
    struct folha *atual = arvore;
    if (tamanho != NULL){
        contador += tamanho(atual -> baixo);
        contador++;
        contador += tamanho (atual -> cima);
    } return contador;
}

int main(){
    struct folha* raiz = NULL;
    int id, pontos, qtd_consumida, pontos_produto;
    char nome[80], produto[80];
    FILE *f;

    f = fopen("ds.csv", "r");
    // lendo os valores inteiros da pontuação
        
    while (!EOF) {
        fscanf(f, "%d %s %s", &id, nome, produto);

        char delim[] = ":";
        char *ptr = strtok(produto, delim);

        pontos = pontos_produto * Atoi(ptr); // pontos = pontos_produto * qtd_consumida

        inserir(&raiz, id, pontos);

    }
    /*
    inserir(&raiz, 10);
    inserir(&raiz, 25);
    inserir(&raiz, 67);
    inserir(&raiz, 50);
    inserir(&raiz, 2);
    */
    /*int num_entrada, valores[10], i;
    scanf("%d", &num_entrada);
    for (i=0; i<= num_entrada; i++){
        scanf("%d", &valores[i]);
        inserir(&raiz, valores[i]);
    }*/
    imprimir(raiz);
    printf("tamanho:%d", tamanho(raiz));
    return(EXIT_SUCCESS);

    fclose(f);
    return 0;
}
