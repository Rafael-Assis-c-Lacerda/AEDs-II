//include bibiotecas padrão c e booleano
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool soConsoante(char str []){ //função que retorna se só tem consoante
    int n = strlen(str); //tamnho da string
    bool resposta = true;

    int i = 0;
    while(i<n){ //loop para passar por todos os caracteres
        char c = tolower(str[i]);

        if(c>='a' && c<='z' || c>='A' && c<='Z'){//verifica se não é um numero ou simbolo
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {// Se for vogal, retorna false
                resposta = false;
                i=n;
            }
        }else{
            resposta = false;
            i=n;
        }
        i++;
    }
    return resposta;
}

bool soVogal(char str[]) { //função que retorna se só tem vogal
    int n = strlen(str); //tamnho da string
    bool resposta = true;

    int i = 0;
    while(i<n) { //loop para passar por todos os caracteres
        char c = tolower(str[i]);

        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') { // Se não for vogal, retorna false
            resposta = false;
            i=n;
        }
        i++;
    }
    return resposta;
}

bool soInteiro(char str []){ //função que retorna se só tem inteiro
    int n = strlen(str); //tamnho da string
    bool resposta = true;

    int i = 0;

    if(str[0]==',' || str[0]=='.'){ //se for float retorna false direto
        resposta = false;
    }else{
        while(i<n){ //loop para passar por todos os caracteres
            if(str[i]<'0' || str[i]>'9'){ //se tiver qualquer coisa que não seja numero retorna false
            resposta = false;
            i=n;
        }
        i++;
        }
    }
    return resposta;
}

bool soFloat(char str []){ //função que retorna se só tem numero real
    int n = strlen(str); //tamnho da string
    bool resposta = true;

    int i = 0;

    if(str[0]==',' || str[0]=='.'){ //verifica se é float, se não for ja retorna false
        while(i<n){ //loop para passar por todos os caracteres
            if(str[i]<'0' || str[i]>'9'){ //verifica se o caractere é um numero
            resposta = false;
            i=n;
        }
        i++;
        }

    }else{
        resposta = false;
    }
    return resposta;
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

int main() {
    char linha[1000]; //string analisada

    char flag [] = "FIM"; //string de termino
    bool continuar = true; //flag booleana

    while (continuar) { //loop para continuar até encontrar o FIM

	scanf(" %[^\n]",linha);

        if (compare(linha, flag)) { //verifica ocorrencia do FIM e decide se o programa continuara ou não
            continuar = false;
        }else{
        	if (soVogal(linha)){ //if e else que verifica se so tem vogal
            		printf("SIM ");
        	} else {
            		printf("NAO ");
        	}

        	if (soConsoante(linha)){ //if e else que verifica se so tem Consoante
            		printf("SIM ");
        	} else {
            		printf("NAO ");
        	}

        	if (soInteiro(linha)){ //if e else que verifica se so tem Inteiro
            		printf("SIM ");
        	} else {
            		printf("NAO ");
        	}

        	if (soFloat(linha)){ //if e else que verifica se so tem float
            		printf("SIM\n");
        	} else {
            		printf("NAO\n");
        	}
	}
    }
    return 0;
}
