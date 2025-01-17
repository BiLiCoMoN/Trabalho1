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

// Q7 - Jogo da Velha

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h> // para a função tolower

// Definição do tabuleiro como uma matriz 3x3
char tabuleiro[3][3] = {{ '-', '-', '-' },
                        { '-', '-', '-' },
                        { '-', '-', '-' } };

// Função para imprimir o tabuleiro
void imprimirTabuleiro() {
    printf("   1   2   3\n");
    char coluna[3] = {'A', 'B', 'C'};
    for (int i = 0; i < 3; i++) {
        printf("%c  %c | %c | %c\n", coluna[i], tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i != 2) printf("   ---------\n");
    }
}

// Função para verificar se uma célula é válida
bool ehMovimentoValido(char linha, int coluna) {
    int indiceLinha = tolower(linha) - 'a';
    return (indiceLinha >= 0 && indiceLinha < 3 && coluna >= 1 && coluna <= 3 && tabuleiro[indiceLinha][coluna - 1] == '-');
}

// Função para fazer uma jogada
void realizarJogada(char linha, int coluna, char jogador) {
    int indiceLinha = tolower(linha) - 'a';
    tabuleiro[indiceLinha][coluna - 1] = jogador;
}

// Função para verificar se há um vencedor
bool verificarVencedor(char jogador) {
    // Verifica linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) return true;
    }
    // Verifica colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) return true;
    }
    // Verifica diagonais
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) return true;
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) return true;

    return false;
}

// Função para verificar se o jogo empatou
bool verificarEmpate() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == '-') return false;
        }
    }
    return true;
}

int main() {
    char jogador = 'X';
    char linha;
    int coluna;

    while (true) {
        imprimirTabuleiro();
        printf("Jogador %c, informe sua jogada (ex: A1): ", jogador);

        // Lê a jogada do jogador
        scanf("%c %d", &linha, &coluna);

        // Converte a linha para minúscula
        linha = tolower(linha);

        // Verifica se a jogada é válida
        if (ehMovimentoValido(linha, coluna)) {
            realizarJogada(linha, coluna, jogador);

            // Verifica se há um vencedor
            if (verificarVencedor(jogador)) {
                imprimirTabuleiro();
                printf("Jogador %c venceu!\n", jogador);
                break;
            }

            // Verifica se o jogo empatou
            if (verificarEmpate()) {
                imprimirTabuleiro();
                printf("Empate!\n");
                break;
            }

            // Alterna o jogador
            jogador = (jogador == 'X') ? 'O' : 'X';
        } else {
            printf("Jogada inválida. Tente novamente.\n");
        }
    }

    return 0;
}
