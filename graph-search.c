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
int isEmpty(Graph *graph);
void printGraph(Graph *graph);


int main() {

  Graph* graph;
  char command;
  int from, to;

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
  if ((graph->num) + 1 > MAX_VERTEX) {
    printf("최대 vertex 수 초과\n");
    return;
  }
  graph->num++;
}

void insertEdge(Graph *graph, int v1, int v2) {
  if (v1 >= graph->num || v2 >= graph->num) {
    printf("해당 vertex가 존재하지 않습니다.\n");
    return;
  }
  Node *node = (Node *)malloc(sizeof(Node));
  node->vertex = v2;
  node->next = graph->adj_list[v1];
  graph->adj_list[v1] = node;
}

void printGraph(Graph *graph) {
  for (int i = 0; i < graph->num; i++) {
    Node *node = graph->adj_list[i];
    printf("vertex %d의 인접리스트: ", i);
    while (node != NULL) {
      printf("%d -> ", node->vertex);
      node = node->next;
    }
    printf("\n");
  }
}

int isEmpty(Graph *graph) {
  return graph->num == 0;
}
