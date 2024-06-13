#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10

typedef struct node {
  int vertex;
  struct node *next;
} Node;

typedef struct {
  int num;
  Node *adj_list[MAX_VERTEX];
} Graph;

Graph *create();
void insertVertex(Graph *graph, int v);
void insertEdge(Graph *graph, int v1, int v2);
void DeleteVertex(Graph *graph, int v);
void DeleteEdge(Graph *graph, int v1, int v2);
int isEmpty(Graph *graph);
void printGraph(Graph *graph);


int main() {

  Graph* graph = create();
  char command;
  int src, dest;

  do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
    printf(" Initialize Graph     = z                                       \n");
		printf(" Insert  Vertex       = v      Insert Edge               = e    \n");
		printf(" Depth First Search   = d      Breath First Search       = b    \n");
		printf(" Print Graph          = p      Quit                      = q    \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			graph = create();
			break;
		case 'q': case 'Q':
			free(graph);
			break;
		case 'v': case 'V':
      printf("Your Vertex = ");
      scanf("%d", &src);
      insertVertex(graph, src);
			break;
		case 'd': case 'D':
			
			break;
		case 'p': case 'P':
			printGraph(graph);
			break;
		case 'e': case 'E':
      printf("Your Source Vertex = ");
      scanf("%d", &src);
      printf("Your Destination Vertex = ");
      scanf("%d", &dest);
      insertEdge(graph, src, dest);
			break;
		case 'b': case 'B':
			
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while(command != 'q' && command != 'Q');

  return 0;
}

Graph *create() {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->num = 0;
  for (int i = 0; i < MAX_VERTEX; i++) {
    graph->adj_list[i] = NULL;
  }
  return graph;
}

void insertVertex(Graph *graph, int v) {
  if (graph->num >= MAX_VERTEX) {
    printf("Graph is full.\n");
    return;
  }
  graph->num++;
}

void insertEdge(Graph *graph, int v1, int v2) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->vertex = v2;
  node->next = graph->adj_list[v1];
  graph->adj_list[v1] = node;

  node = (Node *)malloc(sizeof(Node));
  node->vertex = v1;
  node->next = graph->adj_list[v2];
  graph->adj_list[v2] = node;
}

void DeleteVertex(Graph *graph, int v) {
  Node *node = graph->adj_list[v];
  Node *temp;
  while (node != NULL) {
    temp = node;
    node = node->next;
    free(temp);
  }
  graph->adj_list[v] = NULL;
}

void DeleteEdge(Graph *graph, int v1, int v2) {
  Node *node = graph->adj_list[v1];
  Node *prev = NULL;
  while (node != NULL) {
    if (node->vertex == v2) {
      if (prev == NULL) {
        graph->adj_list[v1] = node->next;
      } else {
        prev->next = node->next;
      }
      free(node);
      break;
    }
    prev = node;
    node = node->next;
  }

  node = graph->adj_list[v2];
  prev = NULL;
  while (node != NULL) {
    if (node->vertex == v1) {
      if (prev == NULL) {
        graph->adj_list[v2] = node->next;
      } else {
        prev->next = node->next;
      }
      free(node);
      break;
    }
    prev = node;
    node = node->next;
  }
}

int isEmpty(Graph *graph) {
  return graph->num == 0;
}

void printGraph(Graph *graph) {
  for (int i = 0; i < MAX_VERTEX; i++) {
    Node *node = graph->adj_list[i];
    printf("Vertex %d: ", i);
    while (node != NULL) {
      printf("%d ", node->vertex);
      node = node->next;
    }
    printf("\n");
  }
}
