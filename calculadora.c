#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calculadora.h"

// Definição da estrutura da pilha
typedef struct No {
	double dado;
	struct No *proximo;
} No;
typedef struct {
	No *topo;
} Pilha;

// Função para inicializar a pilha
void inicializar(Pilha *pilha) {
	pilha->topo = NULL;
}

// Função para empilhar um valor na pilha
void empilhar(Pilha *pilha, double valor) {
	No *novoNo = (No *)malloc(sizeof(No));
	if (novoNo == NULL) {
		printf("Erro: Falha na alocação de memória\n");
		exit(EXIT_FAILURE);
	}
	novoNo->dado = valor;
	novoNo->proximo = pilha->topo;
	pilha->topo = novoNo;
}

// Função para desempilhar um valor da pilha
double desempilhar(Pilha *pilha) {
	if (pilha->topo != NULL) {
		No *temp = pilha->topo;
		double valor = temp->dado;
		pilha->topo = temp->proximo;
		free(temp);
		return valor;
	} else {
		printf("Erro: Pilha vazia\n");
		exit(EXIT_FAILURE);
	}
}

// Função principal para avaliar uma expressão em notação pós-fixada
double avaliarExpressaoPosfixada(const char *expressao) {
	Pilha pilha;
	inicializar(&pilha);
	char buffer[100]; // Buffer para armazenar números temporariamente
	int j = 0; // Índice para o buffer

	for (int i = 0; expressao[i] != '\0'; ++i) {
		if (isdigit(expressao[i]) || expressao[i] == '.') {
			// Se for um dígito ou ponto decimal, armazena no buffer
			buffer[j++] = expressao[i];
		} else if (expressao[i] == ' ' || expressao[i] == '\t') {
			// Se for um espaço, converte o buffer para double e empilha
			if (j > 0) {
				buffer[j] = '\0'; // Termina a string
				empilhar(&pilha, strtod(buffer, NULL));
				j = 0; // Reseta o índice do buffer
			}
		} else {
			// Se for um operador, reseta o buffer e empilha o número
			if (j > 0) {
				buffer[j] = '\0';
				empilhar(&pilha, strtod(buffer, NULL));
				j = 0;
			}

			// Se for um operador, desempilha os operandos necessários e realiza a operação
			double operando1, operando2;
			double valor = 0;

			if (strncmp(&expressao[i], "log", 3) == 0) {
				operando1 = desempilhar(&pilha);
				valor = log10(operando1);
				empilhar(&pilha, valor);
				i += 2; // Pula sobre 'log'
			} else if (strncmp(&expressao[i], "sen", 3) == 0) {
				operando1 = desempilhar(&pilha) * 0.0174444444444444;
				valor = sin(operando1);
				empilhar(&pilha, valor);
				i += 2; // Pula sobre 'sen'
			} else if (strncmp(&expressao[i], "cos", 3) == 0) {
				operando1 = desempilhar(&pilha) * 0.0174444444444444;
				valor = cos(operando1);
				empilhar(&pilha, valor);
				i += 2; // Pula sobre 'cos'
			} else {
				operando2 = desempilhar(&pilha);
				operando1 = desempilhar(&pilha);

				switch (expressao[i]) {
					case '+':
						empilhar(&pilha, operando1 + operando2);
						break;
					case '-':
						empilhar(&pilha, operando1 - operando2);
						break;
					case '*':
						empilhar(&pilha, operando1 * operando2);
						break;
					case '/':
						if (operando2 != 0.0) {
							empilhar(&pilha, operando1 / operando2);
						} else {
							printf("Erro: Divisão por zero\n");
							exit(EXIT_FAILURE);
						}
						break;
					case '^':
						valor =  pow(operando1, operando2);
						empilhar(&pilha, valor);
						break;
					default:
						printf("Erro: Operador inválido\n");
						exit(EXIT_FAILURE);
				}
			}
		}
	}
	// O resultado final estará no topo da pilha
	return desempilhar(&pilha);
}

