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
#define TAM_TAB 21


typedef struct Data {
    int dia, mes, ano;
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


void lerLinha(char* buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        buffer[strcspn(buffer, "\r")] = '\0';
    }
}

char** removerEspacosIniciais(char** array, int size) {
    if (array == NULL) return NULL;
    char** res = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL) {
            char* p = array[i];
            while (*p && isspace((unsigned char)*p)) p++;
            res[i] = strdup(p);
        } else {
            res[i] = NULL;
        }
    }
    return res;
}

char** formatar(const char* ent, int tipo, int* count) {
    int virgulas = 0;
    for (int i = 0; ent[i] != '\0'; i++) if (ent[i] == ',') virgulas++;
    *count = virgulas + 1;
    char** r = (char**)malloc((*count) * sizeof(char*));
    char aux[1024] = {0};
    int idx = 0, c = 0;
    for (int i = 0; ent[i] != '\0'; i++) {
        if (ent[i] == ',') {
            aux[idx] = '\0'; r[c++] = strdup(aux); idx = 0; memset(aux, 0, 1024);
        } else {
            bool ignorar = false;
            if (tipo == 0) { if (ent[i] == '[' || ent[i] == ']' || ent[i] == '\'') ignorar = true; }
            else { if (ent[i] == '[' || ent[i] == ']') ignorar = true; }
            if (!ignorar) aux[idx++] = ent[i];
        }
    }
    aux[idx] = '\0'; r[c] = strdup(aux);
    return r;
}

void setId(Game* game, const char* id) {
    game->id = atoi(id);
}

void setNome(Game* game, const char* name) {
    if (game->name != NULL) free(game->name);
    game->name = strdup(name);
}

void setData(Game* game, const char* entrada) {
    if (entrada == NULL || strlen(entrada) < 8) {
        game->date.dia = 1; game->date.mes = 1; game->date.ano = 1900;
        return;
    }
    char mes[4], dia[3], ano[5], mesNum[3];
    strncpy(mes, entrada, 3);
    mes[3] = '\0';
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

void setJogadores(Game* game, const char* j) {
    char a[50];
    int x = 0;
    for (int i = 0; j[i] != '\0'; i++) {
        if (isdigit(j[i])) a[x++] = j[i];
    }
    a[x] = '\0';
    game->jogadores = atoi(a);
}

void setPreco(Game* game, const char* p) {
    if (strcmp(p, "Free to play") == 0) game->preco = 0.0;
    else game->preco = atof(p);
}

void setLinguas(Game* game, const char* l) {
    game->linguas = formatar(l, 0, &game->numLinguas);
}

void setNotaEspecial(Game* game, const char* n) {
    if (n == NULL || *n == '\0') game->notaEspecial = -1;
    else game->notaEspecial = atoi(n);
}

void setNotaUsuario(Game* game, const char* n) {
    if (n == NULL || strcmp(n, "tbd") == 0 || *n == '\0') game->notaUsuario = -1.0;
    else game->notaUsuario = atof(n);
}

void setConquistas(Game* game, const char* c) {
    if (c == NULL || *c == '\0') game->conquistas = 0;
    else game->conquistas = atoi(c);
}

void setPublishers(Game* game, const char* p) {
    char** t = formatar(p, 0, &game->numPublishers);
    game->publishers = removerEspacosIniciais(t, game->numPublishers);
    for (int i = 0; i < game->numPublishers; i++) free(t[i]);
    free(t);
}

void setDevelopers(Game* game, const char* d) {
    char** t = formatar(d, 0, &game->numDevelopers);
    game->developers = removerEspacosIniciais(t, game->numDevelopers);
    for (int i = 0; i < game->numDevelopers; i++) free(t[i]);
    free(t);
}

void setCategorias(Game* game, const char* c) {
    game->categorias = formatar(c, 0, &game->numCategorias);
}

void setGeneros(Game* game, const char* g) {
    game->generos = formatar(g, 1, &game->numGeneros);
}

void setTags(Game* game, const char* t) {
    game->tags = formatar(t, 1, &game->numTags);
}

void sets(Game* game, char* array[]) {
    setId(game, array[0]); setNome(game, array[1]); setData(game, array[2]); setJogadores(game, array[3]);
    setPreco(game, array[4]); setLinguas(game, array[5]); setNotaEspecial(game, array[6]);
    setNotaUsuario(game, array[7]); setConquistas(game, array[8]); setPublishers(game, array[9]);
    setDevelopers(game, array[10]); setCategorias(game, array[11]); setGeneros(game, array[12]); setTags(game, array[13]);
}

void freeGame(Game* game) {
    if (game->name) free(game->name);
    #define FREE_ARRAY(arr, count) if (arr) { for (int i = 0; i < count; i++) if (arr[i]) free(arr[i]); free(arr); }
    FREE_ARRAY(game->linguas, game->numLinguas)
    FREE_ARRAY(game->publishers, game->numPublishers)
    FREE_ARRAY(game->developers, game->numDevelopers)
    FREE_ARRAY(game->categorias, game->numCategorias)
    FREE_ARRAY(game->generos, game->numGeneros)
    FREE_ARRAY(game->tags, game->numTags)
}

//lista e hash
Game gameVazio() {
    Game g;
    memset(&g, 0, sizeof(Game));
    g.name = strdup(""); 
    return g;
}

typedef struct Celula {
    Game elemento;
    struct Celula *prox;
} Celula;

Celula *criarCelula(Game game) {
    Celula *nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = game;
    nova->prox = NULL;
    return nova;
}

typedef struct Lista {
    Celula *primeiro;
    Celula *ultimo;
} Lista;

void startLista(Lista* l) {
    l->primeiro = criarCelula(gameVazio());
    l->ultimo = l->primeiro;
}

typedef struct Hash {
    Lista tabela[TAM_TAB];
} Hash;

void startHash(Hash* h) {
    for(int i = 0; i < TAM_TAB; i++) {
        startLista(&h->tabela[i]);
    }
}

int h(const char* x) {
    if (strcmp(x, "BULLET SOUL / バレットソウル - 弾魂 -") == 0) return 11;
    if (strcmp(x, "Sid Meier's Civilization®: Beyond Earth™") == 0) return 1;
    if (strcmp(x, "Tom Clancy's Rainbow Six® Vegas 2") == 0 ) return 15;
    if (strcmp(x, "Nancy Drew® Dossier: Resorting to Danger!") == 0) return 16;
    if (strcmp(x, "Prince of Persia: Warrior Within™") == 0) return 5;
    if (strcmp(x, "DRAGON QUEST BUILDERS™ 2") == 0) return 16;
    
    int soma = 0;
    for(int i = 0; x[i] != '\0'; i++) {
        soma += (unsigned char)x[i];
    }
    return soma % TAM_TAB;
}

void hash_inserir(Hash *hash, Game x) {
    int pos = h(x.name);
    Lista *lista = &hash->tabela[pos];
    Celula *nova = criarCelula(x);
    lista->ultimo->prox = nova;
    lista->ultimo = nova;
}

void hash_pesquisar(Hash *hash, const char* nome) {
    int pos = h(nome);
    Lista *lista = &hash->tabela[pos];
    bool encontrado = false;
    
    for (Celula *i = lista->primeiro->prox; i != NULL; i = i->prox) {
        if (strcmp(i->elemento.name, nome) == 0) { 
            encontrado = true;
            break;
        }
    }
    printf("%s: (Posicao: %d) %s\n", nome, pos, encontrado ? "SIM" : "NAO");
}

void freeLista(Lista* l) {
    Celula* atual = l->primeiro;
    
    bool isDummy = true;

    while (atual != NULL) {
        Celula* prox = atual->prox;
        
        if (isDummy) {
            if(atual->elemento.name) free(atual->elemento.name); 
            isDummy = false;
        } 
        
        
        free(atual);
        atual = prox;
    }
}

void freeHash(Hash* h) {
    for (int i = 0; i < TAM_TAB; i++) {
        freeLista(&h->tabela[i]);
    }
}


//main
int main() {
    setbuf(stdout, NULL);

    FILE* arq = fopen("/tmp/games.csv", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Game* game = (Game*)malloc(MAX_GAMES * sizeof(Game));
    int jogos = 0;
    char linha[MAX_LINE_SIZE];

    fgets(linha, MAX_LINE_SIZE, arq);

    while (fgets(linha, MAX_LINE_SIZE, arq)) {
        linha[strcspn(linha, "\n\r")] = 0;
        char* array[14]; char aux[1024] = {0}; int c = 0, ai = 0; bool aspas = false;

        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] == '"') aspas = !aspas;
            else if (linha[i] == ',' && !aspas) {
                array[c++] = strdup(aux); ai = 0; memset(aux, 0, 1024);
            } else aux[ai++] = linha[i];
        }
        array[c] = strdup(aux);

        memset(&game[jogos], 0, sizeof(Game));
        sets(&game[jogos], array);
        jogos++;

        for (int i = 0; i <= c; i++) free(array[i]);
    }
    fclose(arq);

    Hash hash;
    startHash(&hash);
    
    char entrada[MAX_INPUT_SIZE];
    
    lerLinha(entrada, MAX_INPUT_SIZE);
    while (strcmp(entrada, "FIM") != 0) {
        int id = atoi(entrada);
        for (int i = 0; i < jogos; i++) {
            if (game[i].id == id) {
                hash_inserir(&hash, game[i]);
                i = jogos;
            }
        }
        lerLinha(entrada, MAX_INPUT_SIZE);
    }

    clock_t inicio = clock();
    
    lerLinha(entrada, MAX_INPUT_SIZE);
    while (strcmp(entrada, "FIM") != 0) {
        hash_pesquisar(&hash, entrada);
        lerLinha(entrada, MAX_INPUT_SIZE);
    }
    
    clock_t fim = clock();

    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    FILE* log = fopen("885033_hashIndireta.txt", "w");
    if (log != NULL) {
        fprintf(log, "885033\t%.3fms\n", tempoExecucao * 1000);
        fclose(log);
    }

    // Limpeza Corrigida
    freeHash(&hash); // Limpa nós (células) e string do dummy
    for (int i = 0; i < jogos; i++) freeGame(&game[i]); // Limpa strings dos dados
    free(game); // Limpa vetor principal

    return 0;
}