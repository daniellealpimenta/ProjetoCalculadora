#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "calculadora.h"
#include "calculadora.c"


int main() {
// Exemplo de expressão em notação pós-fixada: “2 4 + 5 *“
const char *expressao = "7 2 * 4 +";
double resultado = avaliarExpressaoPosfixada(expressao);
printf("Resultado: %f\n", resultado);
return 0;
}
