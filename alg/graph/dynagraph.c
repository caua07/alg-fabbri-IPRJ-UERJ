/*
 * =====================================================================================
 * 
 *        Filename:  dynagraph.c
 * 
 *     Description:  exercise on completely dynamic graph representation
 * 
 *         Version:  1.0
 *         Created:  jun/2019
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  Ricardo Fabbri (rfabbri), rfabbri.github.io
 *         Company:  IPRJ/UERJ
 * 
 * =====================================================================================
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct lista *lista_ptr; 
typedef struct no *no_ptr;

// Guarda uma conexao com peso 'peso' ao no 'no'
typedef struct lista { 
  no_ptr no; 
  int peso; 
  struct lista *next; 
} lista;

typedef struct no { 
  char nome[32]; 
  lista *conexoes; 
} no;

// Insere conexao para no na lista de conexoes lst,
// onde a conexao tem peso "peso"
void insere(lista **lst, no_ptr no, int peso) {
   lista *conexao = (lista *) malloc(sizeof(lista));
   conexao->peso = peso; 
   conexao->no = no;     // diz que conexao vai pra B
   conexao->next = *lst; // insere conexao na lista de conexcoes de A
   *lst = conexao;
}
void liga(no_ptr a, no_ptr b, int p) { 
  insere(&a->conexoes, b, p); 
  insere(&b->conexoes, a, p); 
}

int remove_string(char* arr[], int* size, int index_to_remove){
  if (index_to_remove < 0 || index_to_remove >= *size) {
    printf("Error: index %d is out of bounds ", index_to_remove);
    return 0;
  }
  int el_to_move = *size - index_to_remove - 1;
  if (el_to_move > 0) {
    char** src = arr + index_to_remove;
    char** dest = arr + index_to_remove + 1;
    size_t bytes_to_move = el_to_move * sizeof(char*);

    memmove(dest, src, bytes_to_move);
  }

  (*size)--;
  arr[*size] = NULL;

  return 1;
}

int
remove_nos(int index, int* size, no* nos)
{
  int el_to_move = (*size) - 1 - index;

  if ( el_to_move > 0) {
    no* dest = nos + index;
    no* src = nos + index + 1;
    size_t byte_size = sizeof(no) * el_to_move;
    memmove(dest, src, byte_size);
  }
  (*size)--;

  memset(&nos[*size], 0, sizeof(no));
  return 1;
}


#define MAX_NUM_NOS 1000   // maximo numero de nos para componente conexo
int componente_conexo(no_ptr r, int max_conexao, no_ptr nos[], int *n_nos);
int componente_conexo_sem_maximo(no_ptr r, no_ptr nos[], int *n_nos);
void renomeia_friburgo(const no *p_petro);
void deleta_no_grafo(no_ptr r);
void export_graph_to_json(no *nos, int num_nos, const char* filename);

int main(void) { // monta um grafo e testa
  int len = 5;
  no nos[5]; char *nomes[5] = {"Petropolis", "Teresopolis", "Niteroi", "Rio", "Friburgo"};
  for (int i = 0; i < 5; ++i) { 
    strcpy(nos[i].nome, nomes[i]);
    nos[i].conexoes = NULL;
 }
    
  liga(nos+0, nos+1, 50);
  liga(nos+0, nos+3, 65);
  liga(nos+1, nos+3, 100);
  liga(nos+1, nos+4, 75);

  
  liga(nos+2, nos+3, 15);
  liga(nos+2, nos+4, 120);
  liga(nos+3, nos+4, 140);

 
  no_ptr nos_componente[MAX_NUM_NOS];

  int n_nos = 0, peso_total;

  if ((peso_total = componente_conexo(nos+3, 100, nos_componente, &n_nos)) == -1 )
    return 1;
/*  if ((peso_total = componente_conexo_sem_maximo(nos+3, nos_componente, &n_nos)) == -1 ) return 1;*/

  printf("Componente de %s tem %d nos e peso total %d\n", nos[3].nome, n_nos, peso_total);
  for (int i = 0; i < n_nos; ++i) printf("%s\n", nos_componente[i]->nome);

  // Export the complete graph to JSON for web visualization
  export_graph_to_json(nos, len, "dataStructures/graph_data.json");

  return 0;
}

// -----------------------------------------------------------------------------
// renomeia_friburgo : altera nome de Friburgo para Nova Friburgo, dado um ponteiro
// para Petropolis

void
renomeia_friburgo(const no *p_petro)
{
  strcpy(p_petro->conexoes->no->conexoes->next->no->nome,"Nova Friburgo");
}

void remove_conexao(lista_ptr *h, const no_ptr r);
// 
// -----------------------------------------------------------------------------
// Remove no
void
deleta_no_grafo(no_ptr r)
{
  // remove todas as conexoes ida e volta
  lista_ptr v = r->conexoes;
  while (v != NULL) {
    lista_ptr aux = v;
    v = v->next;  // Save next pointer BEFORE calling remove_conexao
    remove_conexao(&(aux->no->conexoes), r);  // Remove back-reference
    free(aux);  // Free the connection from r to other node
  }
  r->conexoes = NULL;  // Clear the connections list
  // nao faz "free" no no em si - deixa o "caller" dar free se quiser
}


// busca por conexao ao no r e deleta da lista
void
remove_conexao(lista_ptr *h, const no_ptr r)
{
  lista_ptr l = *h, prev = l;
  for (; l != NULL && l->no != r; prev = l, l = l->next);
  if (!l) return;
  if (prev != l) // middle or last element
    prev->next = l->next;
  else // first or one element
    *h = l->next;
  free(l);
}

// -----------------------------------------------------------------------------
int
componente_conexo_sem_maximo(no_ptr r, no_ptr nos[], int *n_nos)
{
  int peso_total = 0;
  if (*n_nos > MAX_NUM_NOS)  { fprintf(stderr,"ERRO"); return -1; }
  nos[(*n_nos)++] = r;
  for (lista_ptr v = r->conexoes; v != NULL; v = v->next) {
    int i = 0;
    for (; i < *n_nos; ++i)
      if (nos[i] == v->no)
        break;
    if (i == *n_nos)  // neighboring node v->no not visited, insert
      peso_total += v->peso + componente_conexo_sem_maximo(v->no, nos, n_nos);
  }
  // peso total apenas de uma arvore que mantem os nos conexos
  // se quiser peso total com ciclos, pode simplesmente usar as conexoes no grafo original.
  // ambas solucoes serao tidas como corretas
  return peso_total;
}

//------------------------------------------------------------------------------
int
componente_conexo(no_ptr r, int max_conexao, no_ptr nos[], int *n_nos)
{
  int peso_total = 0;
  if (*n_nos > MAX_NUM_NOS)  {
    fprintf(stderr,"ERRO");
    return -1;
  }
  nos[(*n_nos)++] = r;
  for (lista_ptr v = r->conexoes; v != NULL; v = v->next) {
    if (v->peso >= max_conexao)
      continue;
    int i = 0;
    for (; i < *n_nos; ++i)
      if (nos[i] == v->no)
        break;
    if (i == *n_nos)  // neighboring node v->no not visited, insert
      peso_total += v->peso + componente_conexo(v->no, max_conexao, nos, n_nos);
  }
  return peso_total;
}

//------------------------------------------------------------------------------
// Export graph data to JSON format for web visualization
void export_graph_to_json(no *nos, int num_nos, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", filename);
        return;
    }
    
    fprintf(file, "{\n");
    fprintf(file, "  \"nodes\": [\n");
    
    // Export nodes
    int valid_node_count = 0;
    for (int i = 0; i < num_nos; i++) {
      // Skip empty nodes (nodes with empty nome)
      if (nos[i].nome[0] == '\0') continue;
      
      if (valid_node_count > 0) fprintf(file, ",\n");
      fprintf(file, "    {\n");
      fprintf(file, "      \"id\": \"%s\",\n", nos[i].nome);
      fprintf(file, "      \"label\": \"%s\"\n", nos[i].nome);
      fprintf(file, "    }");
      valid_node_count++;
    }
    fprintf(file, "\n");
    
    fprintf(file, "  ],\n");
    fprintf(file, "  \"edges\": [\n");
    
    // Export edges (avoid duplicates by only processing each edge once)
    int edge_count = 0;
    for (int i = 0; i < num_nos; i++) {
        // Skip empty nodes
        if (nos[i].nome[0] == '\0') continue;
        
        lista_ptr conexao = nos[i].conexoes;
        while (conexao != NULL) {
            // Skip edges to empty nodes
            if (conexao->no->nome[0] == '\0') {
                conexao = conexao->next;
                continue;
            }
            
            // Only add edge if current node comes before the connected node alphabetically
            // This prevents duplicate edges in undirected graph
            if (strcmp(nos[i].nome, conexao->no->nome) < 0) {
                if (edge_count > 0) fprintf(file, ",\n");
                fprintf(file, "    {\n");
                fprintf(file, "      \"from\": \"%s\",\n", nos[i].nome);
                fprintf(file, "      \"to\": \"%s\",\n", conexao->no->nome);
                fprintf(file, "      \"weight\": %d,\n", conexao->peso);
                fprintf(file, "      \"label\": \"%d\"\n", conexao->peso);
                fprintf(file, "    }");
                edge_count++;
            }
            conexao = conexao->next;
        }
    }
    
    fprintf(file, "\n  ],\n");
    fprintf(file, "  \"metadata\": {\n");
    fprintf(file, "    \"nodeCount\": %d,\n", valid_node_count);
    fprintf(file, "    \"edgeCount\": %d,\n", edge_count);
    fprintf(file, "    \"generated\": \"dynagraph.c\",\n");
    fprintf(file, "    \"timestamp\": %ld\n", (long)time(NULL));
    fprintf(file, "  }\n");
    fprintf(file, "}\n");
    
    fclose(file);
    printf("Graph data exported to %s\n", filename);
}

//------------------------------------------------------------------------------
// Outros exercicios:
//    imprime_grafo
//    componentes_conexos
//    converte para matriz de adjacencias
//    busca elemento
//    deletar elemento na mao - assumir grafo sempre nao-direcionado - ida e volta
//    funcao para deletar elemento
