//include bibiotecas padrão c e booleano
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int stringInteiro(char str []){
    int resultado = 0;
    int sinal = 1;
    int i = 0;

    // Verifica sinal negativo
    if (str[0] == '-') {
        sinal = -1;
        i++;
    }

    // Converte cada caractere
    while (str[i] != '\0') {
        resultado = resultado * 10 + (str[i] - '0');
        i++;
    }

    return resultado * sinal;
}

int somaDigitos(int num){ //função que soma os digitos
    int resultado = 0;

    while(num>0){
        resultado = resultado + (num%10); //pega o resto e identifica o valor de 1 digito
        num = num/10; //remove esse 1 digito
    }

    return resultado;
}

bool compare(char str1[], char str2[]){ //função que compara duas strings e retorna verdadeiro ou falso

    int i = 0;
    bool resposta = true;

// Percorre ambas as strings até encontrar um caractere nulo
    while (str1[i] != '\0' && str2[i] != '\0' && resposta) {
        // Se os caracteres forem diferentes, resposta é false
        if (str1[i] != str2[i]) {
            resposta = false;
        }
        i++;
    }

    // Verifica se ambas as strings terminaram ao mesmo tempo
    if (resposta && (str1[i] != '\0' || str2[i] != '\0')) {
        resposta = false;
    }

    return resposta;
}

int main()
{
    char linha[1000]; //string analisada

    char flag [] = "FIM"; //string de termino

    bool continuar = true; //flag booleana

    while (continuar) { //loop para continuar até encontrar o FIM
        scanf(" %[^\n]",linha);

        if (compare(linha, flag)) { //verifica ocorrencia do FIM e decide se o programa continuara ou não
            continuar = false;
        }else{
            int resultado = somaDigitos(stringInteiro(linha)); //calcula resposta

            printf("%d\n",resultado); //printa resultado
        }
    }
    return 0;
}
