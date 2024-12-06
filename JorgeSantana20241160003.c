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

//

#include <stdio.h>
#include "JorgeSantana20241160003.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}


int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
    int datavalida = 1;
    int tamanho = strlen(data);
    int dma[3] = {0};

    // Verifica o formato básico da data e os tamanhos esperados
    if ((tamanho != 8 && tamanho != 10) || (data[2] != '/' || data[5] != '/')) {
        return 0;
    }

    // Verifica se todos os caracteres são válidos (dígitos e barras)
    for (int i = 0; i < tamanho; i++) {
        if (i != 2 && i != 5 && !isdigit(data[i])) {
            return 0;
        }
    }

    // Extrai dia, mês e ano
    dma[0] = (data[0] - '0') * 10 + (data[1] - '0'); // Dia
    dma[1] = (data[3] - '0') * 10 + (data[4] - '0'); // Mês

    // Verifica se o ano tem dois ou quatro dígitos e ajusta o valor
    if (tamanho == 8) {
        dma[2] = (data[6] - '0') * 10 + (data[7] - '0');
        dma[2] += (dma[2] <= 24) ? 2000 : 1900; // Anos até 2024 são tratados como 2000+, o restante como 1900+
    } else {
        dma[2] = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
    }

    // Verifica se dia, mês e ano estão dentro dos limites válidos
    if (dma[0] < 1 || dma[0] > 31 || dma[1] < 1 || dma[1] > 12) {
        return 0;
    }

    // Define o número máximo de dias em cada mês, considerando anos bissextos para fevereiro
    int diasNoMes[] = {0, 31, ehBissexto(dma[2]) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verifica se o dia é válido para o mês
    if (dma[0] > diasNoMes[dma[1]]) {return 0;}
        return datavalida;
    }

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma = {0,0,0,0};
    int dia1, mes1, ano1, dia2, mes2, ano2;


    //calcule os dados e armazene nas três variáveis a seguir
    //DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }
    if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }
      //verifique se a data final não é menor que a data inicial
        // Extrair dia, mês e ano das strings
    sscanf(datainicial, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(datafinal, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 > ano2 || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2)) {
        dma.retorno = 4;
        return dma;
    }

    int diasNoMes[13] = {0}; // Inicializa o array para evitar aviso de não inicialização

    // Calcular a diferença em anos, meses e dias
    dma.qtdAnos = ano2 - ano1;
    dma.qtdMeses = mes2 - mes1;
    dma.qtdDias = dia2 - dia1;

    // Ajustar os dias
    int diasNoMesAtual = ehBissexto(ano1 + dma.qtdAnos) ? 29 : 28;
    if (dma.qtdDias < 0) {
        dma.qtdDias += diasNoMesAtual;
        dma.qtdMeses--;
    }

    // Ajustar os meses
    if (dma.qtdMeses < 0) {
        dma.qtdMeses += 12;
        dma.qtdAnos--;
    }

    dma.retorno = 1;
    return dma;
}


/*
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ehBissexto(ano1)) {
        diasNoMes[2] = 29;
    }

    dma.qtdAnos = ano2 - ano1;
    dma.qtdMeses = mes2 - mes1;
    dma.qtdDias = dia2 - dia1;

    if (dma.qtdDias < 0) {
        dma.qtdDias += diasNoMes[mes1];
        dma.qtdMeses--;
    }
    if (dma.qtdMeses < 0) {
        dma.qtdMeses += 12;
        dma.qtdAnos--;
    }

    dma.retorno = 1;
    return dma;
    }
*/


/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

    char cLower = tolower(c); // converte o caractere para minúsculo

    for (int i = 0; texto[i] != '\0'; i++) {
        char currentChar = texto[i];

        // se for uma pesquisa Case Sensitive, compara diretamente
        if (isCaseSensitive == 1) {
            if (currentChar == c) {
                qtdOcorrencias++;
            }
        }
        // se não for uma pesquisa Case Sensitive, compara em minúsculo
        else {
            if (tolower(currentChar) == cLower) {
                qtdOcorrencias++;
            }
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */



int q4(char *strTexto, char *strBusca, int posicoes[30]) {
    int qtdOcorrencias = 0;
    int lenBusca = strlen(strBusca);
    int index = 0; // Controla o índice do vetor de posições.
    int posicaoTexto = 1; // Posição no texto base em 1-based.

    // Itera sobre o texto.
    for (int i = 0; strTexto[i] != '\0';) {
        // Verifica se o caractere atual é parte de um caractere multibyte (ex: UTF-8).
        if ((unsigned char)strTexto[i] == 0xC3 || (unsigned char)strTexto[i] == 0xC2) {
            i += 2; // Pula os dois bytes do caractere.
            continue;
        }

        // Verifica se há correspondência da substring.
        int match = 1; // Assume que há correspondência.
        for (int j = 0; j < lenBusca; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                match = 0; // Quebra a correspondência.
                break;
            }
        }

        // Se houve correspondência, armazena as posições de início e fim.
        if (match) {
            posicoes[index] = posicaoTexto; // Posição inicial (1-based).
            posicoes[index + 1] = posicaoTexto + lenBusca - 1; // Posição final (1-based).
            index += 2; // Avança no vetor de posições.
            qtdOcorrencias++; // Incrementa o contador de ocorrências.
        }

        // Incrementa a posição no texto e avança o índice.
        posicaoTexto++;
        i++; // Avança o índice principal.
    }

    return qtdOcorrencias;
}


/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0;
    while (num != 0) {
        invertido = invertido * 10 + num % 10;
        num /= 10;
    }
    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */


void intToString(int number, char *str) {
    int i = 0;
    if (number == 0) {
        str[i++] = '0';
    }
    while (number > 0) {
        str[i++] = (number % 10) + '0';
        number /= 10;
    }
    str[i] = '\0'; // Adiciona o terminador nulo para formar uma string válida
    // Inverte a string manualmente, pois a conversão foi feita ao contrário
    for (int j = 0; j < i / 2; ++j) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

int q6(int numerobase, int numerobusca)
{
    char strNumerobase[11]; // Comprimento máximo de um int como string + 1 para o elemento final
    char strNumerobusca[11];
    int qtdOcorrencias = 0;

    // Converte os números para strings
    intToString(numerobase, strNumerobase);
    intToString(numerobusca, strNumerobusca);

    // Encontra o tamanho das strings
    int tamanhoBase = strlen(strNumerobase);
    int tamanhoBusca = strlen(strNumerobusca);

    // Verifica se o número de busca é maior que o número base
    if (tamanhoBusca > tamanhoBase) {
        return 0;
    }

    // Itera sobre a string base para encontrar ocorrências da string de busca
    for (int i = 0; i <= tamanhoBase - tamanhoBusca; ++i) {
        int j;
        for (j = 0; j < tamanhoBusca; ++j) {
            if (strNumerobase[i + j] != strNumerobusca[j]) {
                break;
            }
        }
        if (j == tamanhoBusca) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++){
    sDia[i] = data[i];
  }
  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sDia[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }


  int j = i + 1; //anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++){
    sMes[i] = data[j];
    i++;
  }

  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sMes[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }


  j = j + 1; //anda 1 cada para pular a barra
  i = 0;

  for(; data[j] != '\0'; j++){
    sAno[i] = data[j];
    i++;
  }

  if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}
