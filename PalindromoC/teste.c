#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool ehPalindromo(char string[]) {
    int i = 0;
    int j = strlen(string) - 1;
    
    while (i < j) {
        // Ignora caracteres não-letras
        while (i < j && !isalpha(string[i])) i++;
        while (i < j && !isalpha(string[j])) j--;
        
        // Comparação case-insensitive
        if (tolower(string[i]) != tolower(string[j])) {
            return false;
        }
        
        i++;
        j--;
    }
    return true;
}

int main() {
    char string[200];
    
    while (1) {
        fgets(string, sizeof(string), stdin);
        string[strcspn(string, "\n")] = '\0';
        
        if (strcmp(string, "FIM") == 0) {
            break;
        }
        
        printf("%s\n", ehPalindromo(string) ? "SIM" : "NAO");
    }
    
    return 0;
}
