#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_SIZE 4096
#define MAX_FIELD_SIZE 1024
#define MAX_GAMES 2000
#define MAX_INPUT_SIZE 256

int compara = 0;

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

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

char** formatar(const char* entrada, int tipo, int* count);
bool compare(const char* str1, const char* str2);
char** removerEspacosIniciais(char** array, int size);
void freeGame(Game* game);
void imprimir(Game* game);
void imprimirArray(char** array, int n);

// sets
void setId(Game* game, const char* id) {
    game->id = atoi(id);
}

void setNome(Game* game, const char* name) {
    if (game->name) free(game->name);
    game->name = strdup(name);
}

void setData(Game* game, const char* entrada) {
    if (entrada == NULL || strlen(entrada) < 8) {
        game->date.dia = 1; game->date.mes = 1; game->date.ano = 1900;
        return;
    }
    char mes[4], dia[3], ano[5], mesNum[3];
    strncpy(mes, entrada, 3); mes[3] = '\0';
    if (strlen(entrada) == 8 && entrada[3] == ' ') {
        dia[0] = '0'; dia[1] = '1'; dia[2] = '\0'; strcpy(ano, entrada + 4);
    } else if (entrada[5] == ',') {
        dia[0] = '0'; dia[1] = entrada[4]; dia[2] = '\0'; strcpy(ano, entrada + 7);
    } else {
        dia[0] = entrada[4]; dia[1] = entrada[5]; dia[2] = '\0'; strcpy(ano, entrada + 8);
    }
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
    game->date.dia = atoi(dia); game->date.mes = atoi(mesNum); game->date.ano = atoi(ano);
}

void setJogadores(Game* game, const char* jogadores) {
    char aux[MAX_FIELD_SIZE] = {0};
    int j = 0;
    for (size_t i = 0; i < strlen(jogadores); i++) {
        if (jogadores[i] >= '0' && jogadores[i] <= '9') aux[j++] = jogadores[i];
    }
    aux[j] = '\0';
    game->jogadores = atoi(aux);
}

void setPreco(Game* game, const char* preco) {
    if (compare(preco, "Free to play")) game->preco = 0.0f;
    else game->preco = atof(preco);
}

void setLinguas(Game* game, const char* linguas) {
    game->linguas = formatar(linguas, 0, &game->numLinguas);
}

void setNotaEspecial(Game* game, const char* notaEspecial) {
    if (notaEspecial == NULL || strlen(notaEspecial) == 0) game->notaEspecial = -1;
    else game->notaEspecial = atoi(notaEspecial);
}

void setNotaUsuario(Game* game, const char* notaUsuario) {
    if (notaUsuario == NULL || strcmp(notaUsuario, "tbd") == 0 || strlen(notaUsuario) == 0) game->notaUsuario = -1.0f;
    else game->notaUsuario = atof(notaUsuario);
}

void setConquistas(Game* game, const char* conquistas) {
    if (conquistas == NULL || strlen(conquistas) == 0) game->conquistas = 0;
    else game->conquistas = atoi(conquistas);
}

void setPublishers(Game* game, const char* publishers) {
    char** temp = formatar(publishers, 0, &game->numPublishers);
    game->publishers = removerEspacosIniciais(temp, game->numPublishers);
    for(int i = 0; i < game->numPublishers; i++) free(temp[i]);
    free(temp);
}

void setDevelopers(Game* game, const char* developers) {
    char** temp = formatar(developers, 0, &game->numDevelopers);
    game->developers = removerEspacosIniciais(temp, game->numDevelopers);
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

// --- Helpers ---
bool compare(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

char** removerEspacosIniciais(char** array, int size) {
    if (array == NULL) return NULL;
    char** resultado = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL) {
            const char* p = array[i];
            while (*p && isspace((unsigned char)*p)) p++;
            resultado[i] = strdup(p);
        } else {
            resultado[i] = NULL;
        }
    }
    return resultado;
}

char** formatar(const char* entrada, int tipo, int* count) {
    int virgulas = 0;
    for (size_t i = 0; i < strlen(entrada); i++) if (entrada[i] == ',') virgulas++;
    *count = virgulas + 1;
    char** resp = (char**)malloc((*count) * sizeof(char*));
    char aux[MAX_FIELD_SIZE] = {0};
    int contador = 0, aux_idx = 0;
    for (size_t i = 0; i < strlen(entrada); i++) {
        char c = entrada[i];
        if (c == ',') {
            aux[aux_idx] = '\0';
            resp[contador++] = strdup(aux);
            aux_idx = 0; memset(aux, 0, sizeof(aux));
        } else {
            bool ignorar = (tipo == 0) ? (c == '[' || c == ']' || c == '\'') : (c == '[' || c == ']');
            if (!ignorar) aux[aux_idx++] = c;
        }
    }
    aux[aux_idx] = '\0';
    resp[contador] = strdup(aux);
    return resp;
}

void imprimirArray(char** array, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (array[i] != NULL) {
            int start = 0;
            while(array[i][start] != '\0' && isspace((unsigned char)array[i][start])) start++;
            printf("%s", array[i] + start);
        }
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

void imprimir(Game *game) {
    char dateStr[11];
    sprintf(dateStr, "%02d/%02d/%04d", game->date.dia, game->date.mes, game->date.ano);
    printf("=> %d ## %s ## %s ## %d ## ", game->id, game->name, dateStr, game->jogadores);
    if (game->preco == 0.0f) printf("0.0 ## "); else printf("%g ## ", game->preco);
    imprimirArray(game->linguas, game->numLinguas);
    printf(" ## %d ## %.1f ## %d ## ", game->notaEspecial, game->notaUsuario, game->conquistas);
    imprimirArray(game->publishers, game->numPublishers); printf(" ## ");
    imprimirArray(game->developers, game->numDevelopers); printf(" ## ");
    imprimirArray(game->categorias, game->numCategorias); printf(" ## ");
    imprimirArray(game->generos, game->numGeneros); printf(" ## ");
    imprimirArray(game->tags, game->numTags); printf(" ##\n");
}

void freeGame(Game* game) {
    if(game->name) free(game->name);
    #define FREE_ARRAY(arr, count) if (arr) { for (int i = 0; i < count; i++) if (arr[i]) free(arr[i]); free(arr); }
    FREE_ARRAY(game->linguas, game->numLinguas)
    FREE_ARRAY(game->publishers, game->numPublishers)
    FREE_ARRAY(game->developers, game->numDevelopers)
    FREE_ARRAY(game->categorias, game->numCategorias)
    FREE_ARRAY(game->generos, game->numGeneros)
    FREE_ARRAY(game->tags, game->numTags)
}

// --- AVL ---
typedef struct No {
    Game elemento;
    struct No *esq, *dir;
    int nivel;
} No;

No *criarNo(Game game) {
    No *nova = (No*)malloc(sizeof(No));
    nova->elemento = game;
    nova->esq = nova->dir = NULL;
    nova->nivel = 1;
    return nova;
}

typedef struct ArvoreAVL {
    No *raiz;
} ArvoreAVL;

ArvoreAVL *criarArvore() {
    ArvoreAVL *nova = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
    nova->raiz = NULL;
    return nova;
}

int getNivel(No *no) { if(no == NULL) return 0; else return no->nivel; }
void setNivel(No *no) {
    if(getNivel(no->esq) > getNivel(no->dir)) no->nivel = 1 + getNivel(no->esq);
    else no->nivel = 1 + getNivel(no->dir);
}
int getFator(No *no) { return getNivel(no->dir) - getNivel(no->esq); }

No *rotacionarDir(No *no) {
    No *noEsq = no->esq;
    No *noEsqDir = noEsq->dir;
    noEsq->dir = no;
    no->esq = noEsqDir;
    setNivel(no); setNivel(noEsq);
    return noEsq;
}

No *rotacionarEsq(No *no) {
    No *noDir = no->dir;
    No *noDirEsq = noDir->esq;
    noDir->esq = no;
    no->dir = noDirEsq;
    setNivel(no); setNivel(noDir);
    return noDir;
}

No *balancear(No *no) {
    if(no != NULL) {
        setNivel(no);
        int fator = getFator(no);
        if(fator == 2) {
            int fatorDir = getFator(no->dir);
            if(fatorDir == -1) no->dir = rotacionarDir(no->dir);
            return rotacionarEsq(no);
        } else if(fator == -2) {
            int fatorEsq = getFator(no->esq);
            if(fatorEsq == 1) no->esq = rotacionarEsq(no->esq);
            return rotacionarDir(no);
        }
    }
    return no;
}

No *inserirAux(Game x, No *i) {
    if(i == NULL) i = criarNo(x);
    else if(strcmp(x.name, i->elemento.name) > 0) i->dir = inserirAux(x, i->dir);
    else if(strcmp(x.name, i->elemento.name) < 0) i->esq = inserirAux(x, i->esq);
    return balancear(i);
}

void inserir(Game x, ArvoreAVL *arvore) {
    arvore->raiz = inserirAux(x, arvore->raiz);
}

bool pesquisarNomeAux(char* str, No *i) {
    bool resp = false;
    while(i != NULL) {
        compara++;
        if(strcmp(str, i->elemento.name) > 0) {
            printf(" dir");
            i = i->dir;
        } else if(strcmp(str, i->elemento.name) < 0) {
            printf(" esq");
            i = i->esq;
        } else {
            resp = true;
            i = NULL;
        }
    }
    return resp;
}

void pesquisarNome(char* str, ArvoreAVL *arvore) {
    printf("%s: raiz", str); 
    
    if(pesquisarNomeAux(str, arvore->raiz)) {
        printf(" SIM\n");
    } else {
        printf(" NAO\n");
    }
}

void freeNo(No* no) {
    if (no == NULL) return;
    freeNo(no->esq);
    freeNo(no->dir);
    free(no);
}

void freeArvore(ArvoreAVL* arvore) {
    if (arvore != NULL) {
        freeNo(arvore->raiz);
        free(arvore);
    }
}

//main
int main() {
    FILE* arq = fopen("/tmp/games.csv", "r");
    if (arq == NULL) { perror("Erro ao abrir o arquivo"); return 1; }

    Game *game = (Game*)malloc(MAX_GAMES * sizeof(Game));
    int jogos = 0;
    char linha[MAX_LINE_SIZE];

    fgets(linha, MAX_LINE_SIZE, arq); 

    while (fgets(linha, MAX_LINE_SIZE, arq)) {
        linha[strcspn(linha, "\n\r")] = 0;
        char* array[14];
        char aux[MAX_FIELD_SIZE] = {0};
        int contador = 0, aux_idx = 0;
        bool aspas = false;

        for (size_t i = 0; i < strlen(linha); i++) {
            char c = linha[i];
            if (c == '"') aspas = !aspas;
            else if (c == ',' && !aspas) {
                array[contador++] = strdup(aux);
                aux_idx = 0; memset(aux, 0, sizeof(aux));
            } else {
                if (aux_idx < MAX_FIELD_SIZE - 1) aux[aux_idx++] = c;
            }
        }
        array[contador] = strdup(aux);

        memset(&game[jogos], 0, sizeof(Game));
        sets(&game[jogos], array);
        jogos++;

        for (int i = 0; i <= contador; i++) free(array[i]);
    }
    fclose(arq);

    ArvoreAVL *arvore = criarArvore();
    
    char buscaId[MAX_INPUT_SIZE];
    scanf("%s", buscaId);
    while(strcmp(buscaId, "FIM") != 0) {
        int idBusca = atoi(buscaId);
        for (int i = 0; i < jogos; i++) {
            if (idBusca == game[i].id) {
                inserir(game[i], arvore);
                i = jogos; 
            }
        }
        scanf("%s", buscaId);
    }

    clock_t inicio = clock();
    
    char buscaNome[MAX_INPUT_SIZE];
    scanf(" %[^\n]", buscaNome); 
    while(strcmp(buscaNome, "FIM") != 0) {
        pesquisarNome(buscaNome, arvore);
        scanf(" %[^\n]", buscaNome);
    }
    
    clock_t fim = clock();

    freeArvore(arvore);
    
    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    FILE *log = fopen("885033_avl.txt", "w");
    if (log != NULL) {
        fprintf(log, "885033\t%.3fms\t%d comparacoes\n", tempoExecucao * 1000, compara);
        fclose(log);
    }
    
    free(game);

    return 0;
}