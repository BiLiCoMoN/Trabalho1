#include <stdio.h>
#include <stdlib.h>
#include "JorgeSantana20241160003.h"
#define TAM 10

// Estrutura auxiliar para armazenar dados
typedef struct {
    int *numeros;
    int tamanho;
    int usados;
} EstruturaAux;

EstruturaAux *vetorPrincipal[TAM];

/* Inicializa o programa */
void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

/* Finaliza o programa */
void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->numeros);
            free(vetorPrincipal[i]);
        }
    }
}

/* Valida se a posição é válida */
int ehPosicaoValida(int posicao) {
    return (posicao >= 1 && posicao <= 10) ? SUCESSO : POSICAO_INVALIDA;
}

/* Cria estrutura auxiliar */
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;
    if (tamanho < 1) return TAMANHO_INVALIDO;

    int index = posicao - 1;
    if (vetorPrincipal[index] != NULL) return JA_TEM_ESTRUTURA_AUXILIAR;

    vetorPrincipal[index] = malloc(sizeof(EstruturaAux));
    if (!vetorPrincipal[index]) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[index]->numeros = malloc(tamanho * sizeof(int));
    if (!vetorPrincipal[index]->numeros) {
        free(vetorPrincipal[index]);
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[index]->tamanho = tamanho;
    vetorPrincipal[index]->usados = 0;
    return SUCESSO;
}

/* Insere número na estrutura auxiliar */
int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;

    int index = posicao - 1;
    if (!vetorPrincipal[index]) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[index]->usados >= vetorPrincipal[index]->tamanho) return SEM_ESPACO;

    vetorPrincipal[index]->numeros[vetorPrincipal[index]->usados++] = valor;
    return SUCESSO;
}

/* Exclui o último número da estrutura auxiliar */
int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;

    int index = posicao - 1;
    if (!vetorPrincipal[index]) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[index]->usados == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[index]->usados--;
    return SUCESSO;
}

/* Exclui um número específico da estrutura auxiliar */
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;

    int index = posicao - 1;
    if (!vetorPrincipal[index]) return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[index]->usados == 0) return ESTRUTURA_AUXILIAR_VAZIA;

    int encontrado = 0;
    for (int i = 0; i < vetorPrincipal[index]->usados; i++) {
        if (vetorPrincipal[index]->numeros[i] == valor) {
            encontrado = 1;
            for (int j = i; j < vetorPrincipal[index]->usados - 1; j++) {
                vetorPrincipal[index]->numeros[j] = vetorPrincipal[index]->numeros[j + 1];
            }
            vetorPrincipal[index]->usados--;
            break;
        }
    }

    return encontrado ? SUCESSO : NUMERO_INEXISTENTE;
}

/* Obtém os números da estrutura auxiliar */
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;

    int index = posicao - 1;
    if (!vetorPrincipal[index]) return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[index]->usados; i++) {
        vetorAux[i] = vetorPrincipal[index]->numeros[i];
    }

    return SUCESSO;
}

/* Obtém os números de forma ordenada */
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno != SUCESSO) return retorno;

    int tamanho = vetorPrincipal[posicao - 1]->usados;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                int temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }

    return SUCESSO;
}

/* Obtém dados de todas as estruturas auxiliares */
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int idx = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL && vetorPrincipal[i]->usados > 0) {
            for (int j = 0; j < vetorPrincipal[i]->usados; j++) {
                vetorAux[idx++] = vetorPrincipal[i]->numeros[j];
            }
        }
    }

    return (idx == 0) ? TODAS_ESTRUTURAS_AUXILIARES_VAZIAS : SUCESSO;
}

/* Obtém dados ordenados de todas as estruturas auxiliares */
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno != SUCESSO) return retorno;

    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            totalElementos += vetorPrincipal[i]->usados;
        }
    }

    for (int i = 0; i < totalElementos - 1; i++) {
        for (int j = 0; j < totalElementos - i - 1; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                int temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }

    return SUCESSO;
}

/* Modifica o tamanho da estrutura auxiliar */
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;

    int index = posicao - 1;
    if (!vetorPrincipal[index]) return SEM_ESTRUTURA_AUXILIAR;

    int tamanhoAtual = vetorPrincipal[index]->tamanho;
    int tamanhoFinal = tamanhoAtual + novoTamanho;

    if (tamanhoFinal < 1) return NOVO_TAMANHO_INVALIDO;

    int *novoArray = realloc(vetorPrincipal[index]->numeros, tamanhoFinal * sizeof(int));
    if (!novoArray) return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[index]->numeros = novoArray;
    vetorPrincipal[index]->tamanho = tamanhoFinal;

    if (vetorPrincipal[index]->usados > tamanhoFinal) {
        vetorPrincipal[index]->usados = tamanhoFinal;
    }

    return SUCESSO;
}

/* Obtém a quantidade de elementos em uma estrutura auxiliar */
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) return POSICAO_INVALIDA;

    int index = posicao - 1;
    if (!vetorPrincipal[index]) return SEM_ESTRUTURA_AUXILIAR;

    return vetorPrincipal[index]->usados;
}

/* Monta lista encadeada com cabeçote */
No *montarListaEncadeadaComCabecote() {
    No *cabecote = malloc(sizeof(No));
    if (!cabecote) return NULL;

    cabecote->prox = NULL;
    No *atual = cabecote;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            for (int j = 0; j < vetorPrincipal[i]->usados; j++) {
                No *novo = malloc(sizeof(No));
                if (!novo) {
                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                novo->conteudo = vetorPrincipal[i]->numeros[j];
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
            }
        }
    }

    return cabecote;
}

/* Obtém dados da lista encadeada com cabeçote */
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    int idx = 0;
    No *atual = inicio->prox;

    while (atual != NULL) {
        vetorAux[idx++] = atual->conteudo;
        atual = atual->prox;
    }
}

/* Destrói a lista encadeada com cabeçote */
void destruirListaEncadeadaComCabecote(No **inicio) {
    No *atual = *inicio;

    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *inicio = NULL;
}
