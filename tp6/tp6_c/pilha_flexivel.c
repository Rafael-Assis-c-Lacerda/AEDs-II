#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo 'bool'
#include <ctype.h>   // Para usar a função isspace

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
void imprimir(Game* game); // <--- ALTERADO
void imprimirArray(char** array, int n); // <-- ADICIONADO


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


void imprimirArray(char** array, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (array[i] != NULL) {
            int start = 0;
            // Replica a lógica do Code B de remover espaços em branco no início ANTES de imprimir
            while(array[i][start] != '\0' && isspace((unsigned char)array[i][start])) {
                start++;
            }
            printf("%s", array[i] + start);
        }
        if (i < n - 1) printf(", ");
    }
    printf("]");
}


void imprimir(Game *game) {
    char dateStr[11]; // "DD/MM/YYYY\0"
    // Formata a data (lógica movida para cá)
    sprintf(dateStr, "%02d/%02d/%04d", game->date.dia, game->date.mes, game->date.ano);

    // Impressão principal (baseada no Code B)
    printf("=> %d ## %s ## %s ## %d ## ",
           game->id,
           game->name,      // Campo do Code A
           dateStr,         // Data formatada
           game->jogadores
    );

    // Lógica de impressão do PREÇO (do Code B)
    if (game->preco == 0.0f) {
        printf("0.0 ## ");
    } else {
        printf("%g ## ", game->preco); // %g remove zeros desnecessários
    }

    imprimirArray(game->linguas, game->numLinguas);
    
    printf(" ## %d ## %.1f ## %d ## ",
           game->notaEspecial,
           game->notaUsuario,
           game->conquistas
    );
    
    imprimirArray(game->publishers, game->numPublishers);
    printf(" ## ");
    imprimirArray(game->developers, game->numDevelopers);
    printf(" ## ");
    imprimirArray(game->categorias, game->numCategorias);
    printf(" ## ");
    imprimirArray(game->generos, game->numGeneros);
    printf(" ## ");
    imprimirArray(game->tags, game->numTags);
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


// Estrutura da Célula (nó da lista)
typedef struct Celula {
    Game* elemento;      // Armazena um ponteiro para o Game
    struct Celula* prox;
} Celula;

// Estrutura da Lista
typedef struct{
    Celula* primeiro;
    Celula* ultimo;
} Lista;

// Função para criar uma nova célula (nó)
Celula* newCelula(Game* game) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->elemento = game;
    nova->prox = NULL;
    return nova;
}

// Construtor da lista: cria uma lista com um nó cabeça (sentinela)
Lista* newLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    // O elemento do nó cabeça é NULL
    lista->primeiro = newCelula(NULL);
    lista->ultimo = lista->primeiro;
    return lista;
}

// Insere um elemento no fim da lista
void inserirFim(Lista* lista, Game* game) {
    lista->ultimo->prox = newCelula(game);
    lista->ultimo = lista->ultimo->prox;
}

// Insere um elemento no início da lista
void inserirInicio(Lista* lista, Game* game) {
    Celula* tmp = newCelula(game);
    tmp->prox = lista->primeiro->prox;
    lista->primeiro->prox = tmp;
    if (lista->primeiro == lista->ultimo) {
        lista->ultimo = tmp;
    }
}

// Retorna o tamanho da lista
int tamanho(Lista* lista) {
    int tam = 0;
    for (Celula* i = lista->primeiro->prox; i != NULL; i = i->prox, tam++);
    return tam;
}

// Remove um elemento do início da lista
Game* removerInicio(Lista* lista) {
    if (lista->primeiro == lista->ultimo) {
        printf("Erro ao remover: lista vazia!\n");
        return NULL;
    }
    Celula* tmp = lista->primeiro->prox;
    lista->primeiro->prox = tmp->prox;
    if (tmp == lista->ultimo) { // Se a lista tinha um só elemento
        lista->ultimo = lista->primeiro;
    }
    Game* resp = tmp->elemento;
    tmp->prox = NULL;
    free(tmp);
    return resp;
}

// Remove um elemento do fim da lista
Game* removerFim(Lista* lista) {
    if (lista->primeiro == lista->ultimo) {
        printf("Erro ao remover: lista vazia!\n");
        return NULL;
    }
    Celula* i;
    for (i = lista->primeiro; i->prox != lista->ultimo; i = i->prox);
    Game* resp = lista->ultimo->elemento;
    free(lista->ultimo);
    lista->ultimo = i;
    lista->ultimo->prox = NULL;
    return resp;
}

// Libera toda a memória alocada para a lista
void freeLista(Lista* lista) {
    Celula* atual = lista->primeiro;
    while (atual != NULL) {
        Celula* tmp = atual;
        atual = atual->prox;
        // Se a célula tem um elemento, libera o Game
        if (tmp->elemento != NULL) {
            freeGame(tmp->elemento);
            free(tmp->elemento);
        }
        // Libera a própria célula
        free(tmp);
    }
    free(lista);
}

// Função auxiliar para encontrar um jogo por ID na lista principal
Game* findGameById(Lista* lista, int id) {
    for (Celula* i = lista->primeiro->prox; i != NULL; i = i->prox) {
        if (i->elemento->id == id) {
            return i->elemento;
        }
    }
    return NULL;
}

// Protótipos das funções da lista
Lista* newLista();
void inserirFim(Lista* lista, Game* game);
void inserirInicio(Lista* lista, Game* game);
Game* removerFim(Lista* lista);
Game* removerInicio(Lista* lista);
int tamanho(Lista* lista);
void freeLista(Lista* lista);
Game* findGameById(Lista* lista, int id);

typedef struct {
    Celula* topo;
} Pilha;

// Construtor da Pilha (sem sentinela)
Pilha* newPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

// Insere
void inserir(Pilha* p, Game* game) {
     Celula* tmp = newCelula(game);
    tmp->prox = p->topo;
    p->topo = tmp;
}

// Remove
Game* remover(Pilha* p) {
    if (p->topo == NULL) {
        printf("Erro ao remover: pilha vazia!\n");
        return NULL;
    }
    Game* resp = p->topo->elemento;
    Celula* tmp = p->topo;
    p->topo = p->topo->prox;
    tmp->prox = NULL;
    free(tmp);
    return resp;
}

// Função auxiliar recursiva para mostrar a pilha da base para o topo
void mostrarPilhaRecursivo(Celula* i, int* j) {
    if (i != NULL) {
        mostrarPilhaRecursivo(i->prox, j); // Vai até a base
        // Imprime na volta (da base para o topo)
        printf("[%d] ", (*j)++); 
        imprimir(i->elemento);
    }
}

// Libera a memória da pilha (apenas as células, não os Games)
void freePilha(Pilha* p) {
    Celula* atual = p->topo;
    while (atual != NULL) {
        Celula* tmp = atual;
        atual = atual->prox;
        // NÃO libera tmp->elemento, pois ele pertence a 'todosOsGames'
        free(tmp);
    }
    free(p);
}

// Protótipos da Pilha
Pilha* newPilha();
void inserir(Pilha* p, Game* game);
Game* remover(Pilha* p);
void freePilha(Pilha* p);
void mostrarPilhaRecursivo(Celula* i, int* j);

int main() {
    FILE* arq = fopen("/tmp/games.csv", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo games.csv");
        return 1;
    }

    // Cria a LISTA principal para armazenar todos os jogos do CSV
    Lista* todosOsGames = newLista();
    char linha[MAX_LINE_SIZE];

    fgets(linha, MAX_LINE_SIZE, arq); // Pular o cabeçalho

    // Loop de leitura do CSV (sem mudanças)
    while (fgets(linha, MAX_LINE_SIZE, arq)) {
        linha[strcspn(linha, "\n\r")] = 0;
        char* array[14];
        char aux[MAX_FIELD_SIZE] = {0};
        int contador = 0, aux_idx = 0;
        bool aspas = false;
        for (size_t i = 0; i < strlen(linha); i++) {
            char c = linha[i];
            if (c == '"') { aspas = !aspas; } 
            else if (c == ',' && !aspas) { array[contador++] = strdup(aux); aux_idx = 0; memset(aux, 0, sizeof(aux)); }
            else { if (aux_idx < MAX_FIELD_SIZE - 1) { aux[aux_idx++] = c; } }
        }
        array[contador] = strdup(aux);
        Game* novoGame = (Game*)malloc(sizeof(Game));
        memset(novoGame, 0, sizeof(Game));
        sets(novoGame, array);
        inserirFim(todosOsGames, novoGame); // Insere na LISTA 'todosOsGames'
        for (int i = 0; i <= contador; i++) free(array[i]);
    }
    fclose(arq);
    
    // Cria a PILHA de pesquisa
    Pilha* pesquisa = newPilha();
    char busca[MAX_INPUT_SIZE];
    
    // 1. Popula a PILHA 'pesquisa' com os IDs iniciais
    while (fgets(busca, MAX_INPUT_SIZE, stdin) && !compare(busca, "FIM\n")) {
        busca[strcspn(busca, "\n\r")] = 0;
        int buscaId = atoi(busca);
        Game* gameEncontrado = findGameById(todosOsGames, buscaId);
        if (gameEncontrado) {
            inserir(pesquisa, gameEncontrado);
        }
    }

    int n;
    scanf("%d", &n);
    getchar(); // Consumir o \n 

    // Loop de operações na PILHA
    for(int i = 0; i < n; i++) {
        char comando_linha[MAX_INPUT_SIZE];
        fgets(comando_linha, MAX_INPUT_SIZE, stdin);
        comando_linha[strcspn(comando_linha, "\n\r")] = 0;

        Game* gameRemovido = NULL;

        if (comando_linha[0] == 'I') { // Verifica SÓ o primeiro caractere
            int id = atoi(comando_linha + 2); // Pula o 'I' e o ' '
            Game* gameEncontrado = findGameById(todosOsGames, id);
            if(gameEncontrado) inserir(pesquisa, gameEncontrado);

        } else if (comando_linha[0] == 'R') { // Verifica SÓ o primeiro caractere
            gameRemovido = remover(pesquisa);
            if(gameRemovido) printf("(R) %s\n", gameRemovido->name);
            
        } else {
            printf("Erro: Comando desconhecido!\n");
        }
    }

    // Impressão final (da base para o topo)
    int j = 0;
    mostrarPilhaRecursivo(pesquisa->topo, &j);

    // Libera a pilha (apenas as células)
    freePilha(pesquisa);
    
    // Libera a lista principal e TODOS os jogos que foram alocados
    freeLista(todosOsGames);

    return 0;
}