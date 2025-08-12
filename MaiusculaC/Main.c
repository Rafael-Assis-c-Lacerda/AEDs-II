#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int numeroMaiusculas(char str[]) {
    int contador = 0;

    for(int i = 0; i<strlen(str);i++){
        if (str[i] >= 'A'&& str[i]<='Z') {
            contador++;
        }
    }
    return contador;
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
