#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>

typedef struct pix{
    unsigned int r,g,b;
}Pixel;

typedef struct no{
    int tam;
    Pixel **color;
    struct no *prox;
}No;

No *alocaNo(int k);

void insereInicio(No **prim, int k);

void desaloca(No **prim);

int main(){
    int num, i, k, l;
    double ti,tf,tempo, tempo1, tempo2;
    struct timeval tempo_inicio,tempo_fim;

    printf("\nEscreva a quantidade de matrizes: ");
    scanf("%d", &num);
    int tam[num];

    FILE *file = fopen("tempos.csv", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    No *prim=NULL;

    srand(time(NULL));
    for(i=0;i<num;i++){
        tam[i]=rand()%5001+5000;
        printf("\nValor %d gerado: %d", i, tam[i]);
        insereInicio(&prim, tam[i]);
    }

    No *aux=prim;
    while(aux!=NULL){
        ti = tf = tempo = 0;
        gettimeofday(&tempo_inicio,NULL);

        for(k=0;k<aux->tam;k++){
            for(l=0;l<aux->tam;l++){ 
                aux->color[k][l].r=(
                    aux->color[k][l].r+
                    aux->color[k][l].g+
                    aux->color[k][l].b
                )/3;
            }
        }

        gettimeofday(&tempo_fim,NULL);
        tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (10000000.0));
        ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (10000000.0));
        tempo = (tf - ti) / 1000;
        printf("\nTempo gasto em milissegundos com o tamanho %d no programa 1: %.3f\n", aux->tam,tempo);

        tempo1 = tempo;

        ti = tf = tempo = 0;
        gettimeofday(&tempo_inicio,NULL); 

        for(k=0;k<aux->tam;k++){
            for(l=0;l<aux->tam;l++){ 
                aux->color[l][k].r=(
                    aux->color[l][k].r+
                    aux->color[l][k].g+
                    aux->color[l][k].b
                )/3;
            }
        }

        gettimeofday(&tempo_fim,NULL);
        tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (10000000.0));
        ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (10000000.0));
        tempo = (tf - ti) / 1000;
        printf("Tempo gasto em milissegundos com o tamanho %d no programa 2: %.3f\n", aux->tam,tempo);
        
        tempo2=tempo;

        fprintf(file, "Tamanho\tTempo1\tTempo2\n");
        fprintf(file, "%d\t%.3f\t%.3f\n\n", aux->tam, tempo1, tempo2);

        aux=aux->prox;
    }

    fclose(file);

    desaloca(&prim);

    return 0;
}

No *alocaNo(int k){
    No *no;
    no = (No*)malloc(sizeof(No));
    if(no==NULL) return NULL;
    no->tam=k;
    no->color=(Pixel**)malloc(k*sizeof(Pixel*));
    for(int i=0; i<k;i++){
        no->color[i]=(Pixel*)malloc(k*sizeof(Pixel));
    }
    no->prox=NULL;
    return no;
}

void insereInicio(No **prim, int k){
    assert(prim);
    No *noAux=alocaNo(k);
    if (noAux==NULL) return NULL;
    noAux->prox = *prim;
    *prim = noAux;
}

void desaloca(No **prim){
    while(*prim){
        assert(prim);
        No *aux=*prim;
        for(int i=0;i<aux->tam;i++){
            free(aux->color[i]);
        }
        free(aux->color);
        *prim=(*prim)->prox;
        free(aux);
    }
}