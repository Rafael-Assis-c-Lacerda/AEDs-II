#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct{

}Name;

int main()
{
    char string [200];
    fgets(string,sizeof(string),stdin);
    string[strcspn(string, "\n")] = '\0';

    int n = strlen(string);
    if(strcmp(string, "FIM")==0){

    }
    printf("Hello world!\n");
    return 0;
}
