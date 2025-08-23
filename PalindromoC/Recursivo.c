#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool ehPalindromoAuxi(char str[], int i){
    bool resposta = true;
    int j = strlen(str)-1-i;

    if(i>=j){
	resposta = true;
    }else if(str[i]!=str[j]){
	resposta=false;
    }else{
	ehPalindromoAuxi(str,i+1);
    }
return resposta;
}

bool ehPalindromo(char str[]) {
    int i = 0;
    int j = strlen(str) - 1;
    bool resposta = true;

    while (i < j) {
        if (str[i] != str[j]) {
            resposta = false;
            i = j;
        }
        i++;
        j--;
    }
    return resposta;
}


int main() {
    char linha[1000];

    while (1) {
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;
        }
        linha[strcspn(linha, "\n")] = '\0';

        if (strcmp(linha, "FIM") == 0) {
            break;
        }

        if (ehPalindromo(linha)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
    }
    return 0;
}
