//include bibiotecas padrão c e booleano
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int length(char str[]){ //função para ver tamanho da string
	int i = 0;

	//loop que conta os caracteres até o fim da string
	while(str[i] != '\0'){
		i++;
	}
return i;
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

bool ehPalindromoAuxi(char str[], int i, int j){ //função recursiva que de fato confere se é palindromo
    bool resposta = true;

    if(i>=j){ //caso base
	resposta = true;
    }else if(str[i]!=str[j]){ //caso quando ja reconhece que não é palindromo
	resposta=false;
    }else{ //caso geral
	resposta = ehPalindromoAuxi(str,i+1, j-1);
    }
return resposta;
}

bool ehPalindromo(char str[]) { //função auxi, será chamada e adicionara o i e o j
	return ehPalindromoAuxi(str, 0, length(str)-1);
}

int main() {
    char linha[1000]; //string analisada

    char flag [] = "FIM"; //string de termino
    bool continuar = true; //flag booleana

    while (continuar) { //loop para continuar até encontrar o FIM

	scanf(" %[^\n]",linha);

        if (compare(linha, flag)) { //verifica ocorrencia do FIM e decide se o programa continuara ou não
            continuar = false;
        }else{
        	if (ehPalindromo(linha)) { //if e else que verifica se é palindromo e printa resposta
            		printf("SIM\n");
        	} else {
            		printf("NAO\n");
        	}
	}
    }
    return 0;
}
