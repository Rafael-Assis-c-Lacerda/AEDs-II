#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo 'bool'
#include <ctype.h>   // Para usar a função isspace

#define MAX_LINE_SIZE 4096
#define MAX_FIELD_SIZE 1024
#define MAX_GAMES 2000
#define MAX_INPUT_SIZE 256

// Definição da struct para armazenar os dados do jogo
typedef struct {
    int id;
    char* name;
    char* date;
    int jogadores;
    float preco;
    char** linguas;
    int numLinguas;
    int notaEspecial;
    float notaUsuario;
    int conquistas;
    char** publishers;
    int numPublishers;
    char** developers;
    int numDevelopers;
    char** categorias;
    int numCategorias;
    char** generos;
    int numGeneros;
    char** tags;
    int numTags;
} Game;

// Protótipos das funções
char** formatar(const char* entrada, int tipo, int* count);
void printElementosMultiplos(char** array, int size, int aux);
bool compare(const char* str1, const char* str2);
char** removerEspacosIniciais(char** array, int size);
void freeGame(Game* game);


// "Métodos" set (funções para popular a struct)
void setId(Game* game, const char* id) {
    game->id = atoi(id); // atoi converte string para inteiro
}

void setNome(Game* game, const char* name) {
    if (game->name) free(game->name);
    game->name = strdup(name); // strdup aloca memória e copia a string
}

void setData(Game* game, const char* data) {
    char mesStr[4] = {0};
    char diaStr[3] = {0};
    char anoStr[5] = {0};
    char mesNum[3] = {0};
    char resp[11];

    strncpy(mesStr, data, 3);

    if (data[5] == ',') {
        diaStr[0] = '0';
        diaStr[1] = data[4];
        strcpy(anoStr, data + 7);
    } else {
        strncpy(diaStr, data + 4, 2);
        strcpy(anoStr, data + 8);
    }

    if (strcmp(mesStr, "Jan") == 0) strcpy(mesNum, "01");
    else if (strcmp(mesStr, "Feb") == 0) strcpy(mesNum, "02");
    else if (strcmp(mesStr, "Mar") == 0) strcpy(mesNum, "03");
    else if (strcmp(mesStr, "Apr") == 0) strcpy(mesNum, "04");
    else if (strcmp(mesStr, "May") == 0) strcpy(mesNum, "05");
    else if (strcmp(mesStr, "Jun") == 0) strcpy(mesNum, "06");
    else if (strcmp(mesStr, "Jul") == 0) strcpy(mesNum, "07");
    else if (strcmp(mesStr, "Aug") == 0) strcpy(mesNum, "08");
    else if (strcmp(mesStr, "Sep") == 0) strcpy(mesNum, "09");
    else if (strcmp(mesStr, "Oct") == 0) strcpy(mesNum, "10");
    else if (strcmp(mesStr, "Nov") == 0) strcpy(mesNum, "11");
    else if (strcmp(mesStr, "Dec") == 0) strcpy(mesNum, "12");
    else strcpy(mesNum, "01");

    sprintf(resp, "%s/%s/%s", diaStr, mesNum, anoStr);
    if (game->date) free(game->date);
    game->date = strdup(resp);
}

void setJogadores(Game* game, const char* jogadores) {
    char aux[MAX_FIELD_SIZE] = {0};
    int j = 0;
    for (int i = 0; i < strlen(jogadores); i++) {
        if (jogadores[i] >= '0' && jogadores[i] <= '9') {
            aux[j++] = jogadores[i];
        }
    }
    aux[j] = '\0';
    game->jogadores = atoi(aux);
}

void setPreco(Game* game, const char* preco) {
    if (compare(preco, "Free to play")) {
        game->preco = 0.0f;
    } else {
        game->preco = atof(preco); // atof converte string para float
    }
}

void setLinguas(Game* game, const char* linguas) {
    game->linguas = formatar(linguas, 0, &game->numLinguas);
}

void setNotaEspecial(Game* game, const char* notaEspecial) {
    if (notaEspecial == NULL || strlen(notaEspecial) == 0) {
        game->notaEspecial = -1;
    } else {
        game->notaEspecial = atoi(notaEspecial);
    }
}

void setNotaUsuario(Game* game, const char* notaUsuario) {
    if (notaUsuario == NULL || strcmp(notaUsuario, "tbd") == 0 || strlen(notaUsuario) == 0) {
        game->notaUsuario = -1.0f;
    } else {
        game->notaUsuario = atof(notaUsuario);
    }
}

void setConquistas(Game* game, const char* conquistas) {
    if (conquistas == NULL || strlen(conquistas) == 0) {
        game->conquistas = 0;
    } else {
        game->conquistas = atoi(conquistas);
    }
}

void setPublishers(Game* game, const char* publishers) {
    char** temp = formatar(publishers, 0, &game->numPublishers);
    game->publishers = removerEspacosIniciais(temp, game->numPublishers);
    // Libera a memória do array temporário
    for(int i = 0; i < game->numPublishers; i++) free(temp[i]);
    free(temp);
}

void setDevelopers(Game* game, const char* developers) {
    char** temp = formatar(developers, 0, &game->numDevelopers);
    game->developers = removerEspacosIniciais(temp, game->numDevelopers);
    // Libera a memória do array temporário
    for(int i = 0; i < game->numDevelopers; i++) free(temp[i]);
    free(temp);
}

void setCategorias(Game* game, const char* categorias) {
    game->categorias = formatar(categorias, 0, &game->numCategorias);
}

void setGeneros(Game* game, const char* generos) {
    game->generos = formatar(generos, 1, &game->numGeneros);
}

void setTags(Game* game, const char* tags) {
    game->tags = formatar(tags, 1, &game->numTags);
}


// Funções auxiliares
bool compare(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

char** removerEspacosIniciais(char** array, int size) {
    if (array == NULL) {
        return NULL;
    }

    char** resultado = (char**)malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        if (array[i] != NULL) {
            const char* p = array[i];
            while (*p && isspace((unsigned char)*p)) {
                p++;
            }
            resultado[i] = strdup(p);
        } else {
            resultado[i] = NULL;
        }
    }
    return resultado;
}

void printElementosMultiplos(char** array, int size, int aux) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%s", array[i]);
        if (i < size - 1) {
            if (aux == 0) {
                printf(",");
            } else {
                printf(", ");
            }
        }
    }
    printf("]");
}

char** formatar(const char* entrada, int tipo, int* count) {
    int virgulas = 0;
    for (int i = 0; i < strlen(entrada); i++) {
        if (entrada[i] == ',') {
            virgulas++;
        }
    }
    *count = virgulas + 1;
    char** resp = (char**)malloc((*count) * sizeof(char*));

    char aux[MAX_FIELD_SIZE] = {0};
    int contador = 0;
    int aux_idx = 0;

    for (int i = 0; i < strlen(entrada); i++) {
        char c = entrada[i];
        if (c == ',') {
            aux[aux_idx] = '\0';
            resp[contador++] = strdup(aux);
            aux_idx = 0;
            memset(aux, 0, sizeof(aux)); // Limpa o buffer auxiliar
        } else {
            bool ignorar = (tipo == 0) ? (c == '[' || c == ']' || c == '\'') : (c == '[' || c == ']');
            if (!ignorar) {
                aux[aux_idx++] = c;
            }
        }
    }
    aux[aux_idx] = '\0';
    resp[contador] = strdup(aux);

    return resp;
}

void printResultado(Game* game) {
    printf("=> %d ## %s ## %s ## %d ## %.2f ## ", game->id, game->name, game->date, game->jogadores, game->preco);
    printElementosMultiplos(game->linguas, game->numLinguas, 0);
    printf(" ## %d ## %.1f ## %d ## ", game->notaEspecial, game->notaUsuario, game->conquistas);
    printElementosMultiplos(game->publishers, game->numPublishers, 1);
    printf(" ## ");
    printElementosMultiplos(game->developers, game->numDevelopers, 1);
    printf(" ## ");
    printElementosMultiplos(game->categorias, game->numCategorias, 1);
    printf(" ## ");
    printElementosMultiplos(game->generos, game->numGeneros, 1);
    printf(" ## ");
    printElementosMultiplos(game->tags, game->numTags, 1);
    printf(" ##\n");
}

void sets(Game* game, char* array[]) {
    setId(game, array[0]);
    setNome(game, array[1]);
    setData(game, array[2]);
    setJogadores(game, array[3]);
    setPreco(game, array[4]);
    setLinguas(game, array[5]);
    setNotaEspecial(game, array[6]);
    setNotaUsuario(game, array[7]);
    setConquistas(game, array[8]);
    setPublishers(game, array[9]);
    setDevelopers(game, array[10]);
    setCategorias(game, array[11]);
    setGeneros(game, array[12]);
    setTags(game, array[13]);
}

// Função para liberar toda a memória alocada para um jogo
void freeGame(Game* game) {
    free(game->name);
    free(game->date);
    for (int i = 0; i < game->numLinguas; i++) free(game->linguas[i]);
    free(game->linguas);
    for (int i = 0; i < game->numPublishers; i++) free(game->publishers[i]);
    free(game->publishers);
    for (int i = 0; i < game->numDevelopers; i++) free(game->developers[i]);
    free(game->developers);
    for (int i = 0; i < game->numCategorias; i++) free(game->categorias[i]);
    free(game->categorias);
    for (int i = 0; i < game->numGeneros; i++) free(game->generos[i]);
    free(game->generos);
    for (int i = 0; i < game->numTags; i++) free(game->tags[i]);
    free(game->tags);
}


int main() {
    FILE* arq = fopen("games.csv", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo games.csv");
        return 1;
    }

    Game games[MAX_GAMES];
    int jogos = 0;
    char linha[MAX_LINE_SIZE];

    // Pular o cabeçalho
    fgets(linha, MAX_LINE_SIZE, arq);

    while (fgets(linha, MAX_LINE_SIZE, arq) && jogos < MAX_GAMES) {
        // Remove a quebra de linha do final, se houver
        linha[strcspn(linha, "\n")] = 0;

        char* array[14];
        char aux[MAX_FIELD_SIZE] = {0};
        int contador = 0;
        int aux_idx = 0;
        bool aspas = false;

        for (int i = 0; i < strlen(linha); i++) {
            char c = linha[i];
            if (c == '"') {
                aspas = !aspas;
            } else if (c == ',' && !aspas) {
                aux[aux_idx] = '\0';
                array[contador++] = strdup(aux);
                aux_idx = 0;
                memset(aux, 0, sizeof(aux)); // Limpa o buffer
            } else {
                if (aux_idx < MAX_FIELD_SIZE -1) {
                    aux[aux_idx++] = c;
                }
            }
        }
        aux[aux_idx] = '\0';
        array[contador] = strdup(aux);

        // Inicializa a struct para evitar ponteiros inválidos
        memset(&games[jogos], 0, sizeof(Game));

        // Popula a struct
        sets(&games[jogos], array);
        jogos++;

        // Libera a memória alocada para os campos da linha atual
        for (int i = 0; i <= contador; i++) {
            free(array[i]);
        }
    }
    fclose(arq);

    const char* flag = "FIM";
    char busca[MAX_INPUT_SIZE];

    while (true) {
        if (fgets(busca, MAX_INPUT_SIZE, stdin) == NULL) {
            break; // Fim da entrada
        }
        // Remove a quebra de linha
        busca[strcspn(busca, "\n")] = 0;

        if (compare(busca, flag)) {
            break;
        } else {
            int buscaId = atoi(busca);
            for (int i = 0; i < jogos; i++) {
                if (buscaId == games[i].id) {
                    printResultado(&games[i]);
                    i = jogos; // Para o loop interno
                }
            }
        }
    }

    // Libera toda a memória alocada para os jogos
    for (int i = 0; i < jogos; i++) {
        freeGame(&games[i]);
    }

    return 0;
}
