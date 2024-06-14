#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// Definição da estrutura da pilha
typedef struct No
{
    double dado;
    struct No *proximo;
} No;
typedef struct
{
    No *topo;
} Pilha;

// Função para inicializar a pilha
void inicializar(Pilha *pilha)
{
    pilha->topo = NULL;
}
// Função para empilhar um valor na pilha
void empilhar(Pilha *pilha, double valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Função para desempilhar um valor da pilha
double desempilhar(Pilha *pilha)
{
    if (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

// Função principal para avaliar uma expressão em notação pós-fixada
double avaliarExpressaoPosfixada(const char *expressao)
{
    Pilha pilha;
    inicializar(&pilha);
    for (int i = 0; expressao[i] != '\0'; ++i)
    {
        if (isdigit(expressao[i]))
        {
            // Se for um dígito, converte para double e empilha
            empilhar(&pilha, (double)(expressao[i] - '0'));
        }
        else if (expressao[i] == ' ' || expressao[i] == '\t')
        {
            // Ignora espaços em branco
            continue;
        }
        else
        {
            // Se for um operador, ...
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);
            switch (expressao[i])
            {
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
                if (operando2 != 0.0)
                {
                    empilhar(&pilha, operando1 / operando2);
                }
                else
                {
                    printf("Erro: Divisão por zero\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                printf("Erro: Operador inválido\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    // O resultado final estará no topo da pilha
    return desempilhar(&pilha);
}
