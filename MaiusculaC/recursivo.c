#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int numeroMaiusculasAuxi(char str[], int i){
    int contador = 0;

    if(str[i]=='\0'){
	return 0;
    }else{
	if(str[i]>='A'&&str[i]<='Z') contador++;
	contador=contador+numeroMaiusculasAuxi(str, i+1);
    }
return contador;
}

int numeroMaiusculas(char str[]){
    return numeroMaiusculasAuxi(str,0);
}

int main() {
    char string[1000];
    int resposta = 0;

    while (1) {
        if (fgets(string, sizeof(string), stdin) == NULL) {
            break;
        }
        string[strcspn(string, "\n")] = '\0';

        if (strcmp(string, "FIM") == 0) {
            break;
        }

        resposta = numeroMaiusculas(string);

        printf("%d\n",resposta);
    }
    return 0;
}
