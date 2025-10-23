#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo 'bool'
#include <ctype.h>   // Para usar a função isspace
#include <time.h>

int swaps = 0;
int comparacoes = 0;

#define MAX_LINE_SIZE 4096
#define MAX_FIELD_SIZE 1024
#define MAX_GAMES 2000
#define MAX_INPUT_SIZE 256

typedef struct Data{
    int dia;
    int mes;
    int ano;
} Data;

// Definição da struct para armazenar os dados do jogo
typedef struct {
    int id;
    char* name;
    Data date;
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
bool compare(const char* str1, const char* str2);
char** removerEspacosIniciais(char** array, int size);
void freeGame(Game* game);
void printResultadoFormatado(Game* game); // Nova função de impressão
void formatarArrayParaString(char** array, int count, char* resultado); // Nova função auxiliar


// "Métodos" set (funções para popular a struct)
void setId(Game* game, const char* id) {
    game->id = atoi(id); // atoi converte string para inteiro
}

void setNome(Game* game, const char* name) {
    if (game->name) free(game->name);
    game->name = strdup(name); // strdup aloca memória e copia a string
}


void setData(Game* game, const char* entrada) {
    // Tratamento de data inválida ou muito curta
    if (entrada == NULL || strlen(entrada) < 8) { 
        game->date.dia = 1;
        game->date.mes = 1;
        game->date.ano = 1900; // Um padrão qualquer
        return;
    }

    char mes[4], dia[3], ano[5], mesNum[3];
    
    // Extrai o Mês (primeiras 3 letras)
    strncpy(mes, entrada, 3);
    mes[3] = '\0';

    // Lógica de parsing idêntica à 'setDataFormatada' do segundo código
    if (strlen(entrada) == 8 && entrada[3] == ' ') { // Ex: "May 2020"
        dia[0] = '0';
        dia[1] = '1';
        dia[2] = '\0';
        strcpy(ano, entrada + 4);
    } else if (entrada[5] == ',') { // Ex: "May 5, 2020"
        dia[0] = '0';
        dia[1] = entrada[4];
        dia[2] = '\0';
        strcpy(ano, entrada + 7);
    } else { // Ex: "May 15, 2020"
        dia[0] = entrada[4];
        dia[1] = entrada[5];
        dia[2] = '\0';
        strcpy(ano, entrada + 8);
    }

    // Converte o nome do mês para número
    if (strcmp(mes, "Jan") == 0) strcpy(mesNum, "01");
    else if (strcmp(mes, "Feb") == 0) strcpy(mesNum, "02");
    else if (strcmp(mes, "Mar") == 0) strcpy(mesNum, "03");
    else if (strcmp(mes, "Apr") == 0) strcpy(mesNum, "04");
    else if (strcmp(mes, "May") == 0) strcpy(mesNum, "05");
    else if (strcmp(mes, "Jun") == 0) strcpy(mesNum, "06");
    else if (strcmp(mes, "Jul") == 0) strcpy(mesNum, "07");
    else if (strcmp(mes, "Aug") == 0) strcpy(mesNum, "08");
    else if (strcmp(mes, "Sep") == 0) strcpy(mesNum, "09");
    else if (strcmp(mes, "Oct") == 0) strcpy(mesNum, "10");
    else if (strcmp(mes, "Nov") == 0) strcpy(mesNum, "11");
    else if (strcmp(mes, "Dec") == 0) strcpy(mesNum, "12");
    else strcpy(mesNum, "01");

    game->date.dia = atoi(dia);
    game->date.mes = atoi(mesNum);
    game->date.ano = atoi(ano);
}

void setJogadores(Game* game, const char* jogadores) {
    char aux[MAX_FIELD_SIZE] = {0};
    int j = 0;
    for (size_t i = 0; i < strlen(jogadores); i++) {
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
    // Libera a memória do array temporário original (não a do resultado)
    for(int i = 0; i < game->numPublishers; i++) free(temp[i]);
    free(temp);
}

void setDevelopers(Game* game, const char* developers) {
    char** temp = formatar(developers, 0, &game->numDevelopers);
    game->developers = removerEspacosIniciais(temp, game->numDevelopers);
    // Libera a memória do array temporário original
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


char** formatar(const char* entrada, int tipo, int* count) {
    int virgulas = 0;
    for (size_t i = 0; i < strlen(entrada); i++) {
        if (entrada[i] == ',') {
            virgulas++;
        }
    }
    *count = virgulas + 1;
    char** resp = (char**)malloc((*count) * sizeof(char*));
    
    char aux[MAX_FIELD_SIZE] = {0};
    int contador = 0;
    int aux_idx = 0;

    for (size_t i = 0; i < strlen(entrada); i++) {
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

// NOVA FUNÇÃO AUXILIAR - Para formatar arrays para impressão
void formatarArrayParaString(char** array, int count, char* resultado) {
    resultado[0] = '\0';
    
    if (count == 0 || array == NULL) {
        strcpy(resultado, "[]");
        return;
    }
    
    strcpy(resultado, "[");
    for (int i = 0; i < count; i++) {
        strcat(resultado, array[i]);
        if (i < count - 1) {
            strcat(resultado, ", "); // Adiciona sempre ", "
        }
    }
    strcat(resultado, "]");
}


void printResultadoFormatado(Game* game) {
    char linguasStr[MAX_FIELD_SIZE] = "[]";
    char publishersStr[MAX_FIELD_SIZE] = "[]";
    char developersStr[MAX_FIELD_SIZE] = "[]";
    char categoriasStr[MAX_FIELD_SIZE] = "[]";
    char generosStr[MAX_FIELD_SIZE] = "[]";
    char tagsStr[MAX_FIELD_SIZE] = "[]";

    char dateStr[11]; // "DD/MM/YYYY\0"
    sprintf(dateStr, "%02d/%02d/%04d", game->date.dia, game->date.mes, game->date.ano);

    // Formata cada array para uma string única
    formatarArrayParaString(game->linguas, game->numLinguas, linguasStr);
    formatarArrayParaString(game->publishers, game->numPublishers, publishersStr);
    formatarArrayParaString(game->developers, game->numDevelopers, developersStr);
    formatarArrayParaString(game->categorias, game->numCategorias, categoriasStr);
    formatarArrayParaString(game->generos, game->numGeneros, generosStr);
    formatarArrayParaString(game->tags, game->numTags, tagsStr);

    // Lógica de formatação do preço do segundo código
    char precoStr[50];
    if (game->preco == 0.0f) {
        strcpy(precoStr, "0.0");
    } else {
        sprintf(precoStr, "%.2f", game->preco);
        char *dot = strchr(precoStr, '.');
        if (dot != NULL) {
            char *p = precoStr + strlen(precoStr) - 1;
            // Remove zeros à direita
            while (p > dot && *p == '0') {
                *p = '\0';
                p--;
            }
            // Se só sobrou o ponto, remove o ponto também
            if (p == dot) {
                *dot = '\0';
            }
        }
    }

    // Imprime tudo de uma vez com o formato final
    printf("=> %d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %d ## %s ## %s ## %s ## %s ## %s ##\n",
           game->id,
           game->name,
           dateStr,
           game->jogadores,
           precoStr,
           linguasStr,
           game->notaEspecial,
           game->notaUsuario,
           game->conquistas,
           publishersStr,
           developersStr,
           categoriasStr,
           generosStr,
           tagsStr);
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
    if(game->name) free(game->name);

    #define FREE_ARRAY(arr, count) \
        if (arr) { \
            for (int i = 0; i < count; i++) if (arr[i]) free(arr[i]); \
            free(arr); \
        }
    
    FREE_ARRAY(game->linguas, game->numLinguas)
    FREE_ARRAY(game->publishers, game->numPublishers)
    FREE_ARRAY(game->developers, game->numDevelopers)
    FREE_ARRAY(game->categorias, game->numCategorias)
    FREE_ARRAY(game->generos, game->numGeneros)
    FREE_ARRAY(game->tags, game->numTags)
}

void swap(Game *game, int i, int j) {
    Game temp = game[i];
    game[i] = game[j];
    game[j] = temp;
    swaps += 3;
}

void quicksort(Game *game, int esq, int dir) {
    int i = esq, j = dir;
    int pivoAno = game[(esq + dir) / 2].date.ano;
    int pivoMes = game[(esq + dir) / 2].date.mes;
    int pivoDia = game[(esq + dir) / 2].date.dia;
    int pivoId = game[(esq + dir) / 2].id;
    while(i <= j) {
        comparacoes++;
        while((game[i].date.ano < pivoAno) || 
            (game[i].date.ano == pivoAno && game[i].date.mes < pivoMes) ||
            (game[i].date.ano == pivoAno && game[i].date.mes == pivoMes && game[i].date.dia < pivoDia) ||
            (game[i].date.ano == pivoAno && game[i].date.mes == pivoMes && game[i].date.dia == pivoDia && game[i].id < pivoId)) {
            i++;
            comparacoes++; 
        }
        comparacoes++;
        while((game[j].date.ano > pivoAno) || 
            (game[j].date.ano == pivoAno && game[j].date.mes > pivoMes) ||
            (game[j].date.ano == pivoAno && game[j].date.mes == pivoMes && game[j].date.dia > pivoDia) ||
            (game[j].date.ano == pivoAno && game[j].date.mes == pivoMes && game[j].date.dia == pivoDia && game[j].id > pivoId)) {
            j--;
            comparacoes++; 
        }
        if(i <= j) {
            swap(game, i, j);
            i++;
            j--;
        }
    }
    if(esq < j) quicksort(game, esq, j);
    if(i < dir) quicksort(game, i, dir);
}

int main() {
    clock_t inicio = clock();
    FILE* arq = fopen("/tmp/games.csv", "r");
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
        linha[strcspn(linha, "\n\r")] = 0;
        
        char* array[14];
        char aux[MAX_FIELD_SIZE] = {0};
        int contador = 0;
        int aux_idx = 0;
        bool aspas = false;

        for (size_t i = 0; i < strlen(linha); i++) {
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

    Game ordenados [2000];
    int n = 0;
    
    while (true) {
        if (fgets(busca, MAX_INPUT_SIZE, stdin) == NULL) {
            break; // Fim da entrada
        }
        // Remove a quebra de linha
        busca[strcspn(busca, "\n\r")] = 0; 
        
        if (compare(busca, flag)) {
            break;
        } else {
            int buscaId = atoi(busca);
            for (int i = 0; i < jogos; i++) {
                if (buscaId == games[i].id) {
                    ordenados[n]=games[i];
                    n++;
                    break; // Para o loop interno
                }
            }
        }
    }

    quicksort(ordenados, 0,n-1);

    for(int i = 0; i<n;i++){
        printResultadoFormatado(&ordenados[i]);
    }

    // Libera toda a memória alocada para os jogos
    for (int i = 0; i < jogos; i++) {
        freeGame(&games[i]);
    }

    clock_t fim = clock();
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    FILE* log = fopen("885033_quicksort.txt", "w");
    if (log != NULL) {
        fprintf(log, "885033\t%d\t%d\t%.6f\n",  comparacoes, swaps ,tempoExecucao);
        fclose(log);
    } else {
        printf("Erro ao criar arquivo de log.\n");
    }

    return 0;
}