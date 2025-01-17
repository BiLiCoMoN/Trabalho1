//
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Jorge Dário Costa de Santana
//  email: jorgehp1@gmail.com / 20241160003@ifba.edu.br
//  Matrícula: 20241160003
//  Semestre: 2º

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// Q8 - Batalha Naval

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAMANHO_TABULEIRO 10
#define NUM_NAVIOS_MINIMO 5
#define NUM_NAVIOS_MAXIMO 10

typedef struct {
    int tamanho;
    int x; // Linha (0-9)
    char y; // Coluna ('A'-'J')
    char orientacao; // 'H' para horizontal, 'V' para vertical
} Navio;

typedef struct {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Navio navios[NUM_NAVIOS_MAXIMO];
} Jogador;

void inicializarTabuleiro(Jogador *jogador) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            jogador->tabuleiro[i][j] = ' ';
        }
    }
}

void imprimirTabuleiro(Jogador jogador) {
    printf("   ");
    for (char i = 'A'; i < 'A' + TAMANHO_TABULEIRO; i++) {
        printf("%c ", i);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%c ", jogador.tabuleiro[i][j]);
        }
        printf("\n");
    }
}

bool podePosicionarNavio(Jogador jogador, Navio navio) {
    int x = navio.x;
    int y = navio.y - 'A'; // Converter letra para índice de array (0-based)
    int tamanho = navio.tamanho;
    char orientacao = navio.orientacao;

    if (orientacao == 'H') {
        if (y + tamanho > TAMANHO_TABULEIRO) return false;
        for (int i = 0; i < tamanho; i++) {
            if (jogador.tabuleiro[x][y + i] != ' ') return false;
        }
    } else if (orientacao == 'V') {
        if (x + tamanho > TAMANHO_TABULEIRO) return false;
        for (int i = 0; i < tamanho; i++) {
            if (jogador.tabuleiro[x + i][y] != ' ') return false;
        }
    } else {
        return false;
    }
    return true;
}

void posicionarNavio(Jogador *jogador, Navio navio) {
    int x = navio.x;
    int y = navio.y - 'A'; // Converter letra para índice de array (0-based)
    int tamanho = navio.tamanho;
    char orientacao = navio.orientacao;

    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++) {
            jogador->tabuleiro[x][y + i] = 'N';
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < tamanho; i++) {
            jogador->tabuleiro[x + i][y] = 'N';
        }
    }
}

bool atirar(Jogador *jogador, char x, int y) {
    int linha = x - 'A';
    int coluna = y - 1;

    if (jogador->tabuleiro[linha][coluna] == 'N') {
        jogador->tabuleiro[linha][coluna] = 'X'; // Marca o navio como atingido
        return true; // Um navio foi atingido
    } else {
        jogador->tabuleiro[linha][coluna] = 'O'; // Marca o tiro como água
        return false; // Não atingiu um navio
    }
}

bool todosNaviosAtingidos(Jogador jogador) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (jogador.tabuleiro[i][j] == 'N') return false; // Ainda há navios não atingidos
        }
    }
    return true; // Todos os navios foram atingidos
}

void posicionarNavios(Jogador *jogador) {
    int numNaviosPosicionados = 0;

    fflush(stdin);
    printf("Formato de entrada: LINHA COLUNA [H/V]\n"
           "Onde LINHA é um número de 1 a %d, COLUNA é uma letra de A a J, "
           "e [H/V] indica a orientação do navio (H para horizontal, V para vertical).\n",
           TAMANHO_TABULEIRO);

    while (numNaviosPosicionados < NUM_NAVIOS_MINIMO) {
        // Imprime o tabuleiro atual para o jogador ver
        imprimirTabuleiro(*jogador);

        fflush(stdin);

        printf("Posicione o navio %d (tamanho %d): ", numNaviosPosicionados + 1, numNaviosPosicionados + 1);
        int x;
        char y, orientacao;

        // Lê a entrada do usuário
        scanf("%d %c %c", &x, &y, &orientacao);
        x--; // Ajustar para o índice de array (0-based)
        y = toupper(y) - 'A'; // Converter letra para índice de array (0-based)

        Navio navio = {
            .tamanho = numNaviosPosicionados + 1,
            .x = x,
            .y = y,
            .orientacao = toupper(orientacao)
        };

        if (podePosicionarNavio(*jogador, navio)) {
            posicionarNavio(jogador, navio);
            numNaviosPosicionados++;
        } else {
            printf("Posicionamento inválido. Tente novamente.\n");
        }
    }
}

int main() {
    Jogador jogador1, jogador2;
    inicializarTabuleiro(&jogador1);
    inicializarTabuleiro(&jogador2);

    posicionarNavios(&jogador1);
    posicionarNavios(&jogador2);

    // Loop do jogo
    bool jogoTerminado = false;
    while (!jogoTerminado) {
        // Turno do jogador 1
        printf("Jogador 1, é a sua vez!\n");
        printf("Atire em uma coordenada: ");
        char linha;
        int coluna;
        scanf("%c %d", &linha, &coluna);
        linha = toupper(linha) - 'A'; // Converter letra para índice de array (0-based)
        coluna--;

        if (atirar(&jogador2, linha, coluna)) {
            printf("Você atingiu um navio!\n");
            if (todosNaviosAtingidos(jogador2)) {
                printf("Parabéns, Jogador 1! Você venceu o jogo!\n");
                jogoTerminado = true;
            }
        } else {
            printf("Água! Tente novamente.\n");
        }

        // Verifica se o jogo terminou
        if (jogoTerminado) continue;

        // Turno do jogador 2
        printf("Jogador 2, é a sua vez!\n");
        printf("Atire em uma coordenada: ");
        scanf("%c %d", &linha, &coluna);
        linha = toupper(linha) - 'A'; // Converter letra para índice de array (0-based)
        coluna--;

        if (atirar(&jogador1, linha, coluna)) {
            printf("Você atingiu um navio!\n");
            if (todosNaviosAtingidos(jogador1)) {
                printf("Parabéns, Jogador 2! Você venceu o jogo!\n");
                jogoTerminado = true;
            }
        } else {
            printf("Água! Tente novamente.\n");
        }
    }

    return 0;
}
