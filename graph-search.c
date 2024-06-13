#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

typedef struct {
  int vertex;
  Node *next;
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

  while (1) {
    printf("\nGraph Searches\n");
    printf("Initialize Graph = z\n");
    printf("Insert Vertex = v\n");
    printf("Insert Edge = e\n");
    printf("Depth First Search = d\n");
    printf("Breadth First Search = b\n");
    printf("Print Graph = p\n");
    printf("Quit = q\n");
    printf("Enter command: ");
    scanf(" %c", &command);

    switch (command) {
      case 'z':
        free(graph);
        graph = create();
        printf("Graph initialized.\n");
        break;
      case 'v':
        addVertex(graph);
        break;
      case 'e':
        printf("Enter source and destination vertex: ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
          break;
      case 'd':
        resetVisited(graph);
        printf("Enter start vertex: ");
        scanf("%d", &src);
        printf("DFS starting from vertex %d: ", src);
        DFS(graph, src);
        printf("\n");
        break;
      case 'b':
        resetVisited(graph);
        printf("Enter start vertex: ");
        scanf("%d", &src);
        printf("BFS starting from vertex %d: ", src);
        BFS(graph, src);
        printf("\n");
        break;
      case 'p':
        printGraph(graph);
        break;
      case 'q':
        free(graph);
        printf("Exiting program.\n");
        return 0;
      default:
        printf("Invalid command.\n");
    }
  }

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
