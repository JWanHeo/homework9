#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10

typedef struct node {
  int vertex;
  struct node *next;
} Node;

typedef struct {
  int num;
  Node *adjList[MAX_VERTEX];
} Graph;

typedef struct {
  int vertices[MAX_VERTEX];
  int front;
  int rear;
} Queue;


int visited[MAX_VERTEX];

Graph *create();
void insertVertex(Graph *graph);
void insertEdge(Graph *graph, int v1, int v2);
int isEmpty(Graph *graph);
void printGraph(Graph *graph);
void dfs(Graph *graph, int v);
void bfs(Graph *graph, int v);  
void resetVisited(Graph *graph);
Queue* createQueue();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);

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
      insertVertex(graph);
			break;
		case 'd': case 'D':
      printf("from: ");
      scanf("%d", &from);
			dfs(graph, from);
      resetVisited(graph);
			break;
		case 'p': case 'P':
			printGraph(graph);
			break;
		case 'e': case 'E':
      printf("from = ");
      scanf("%d", &from);
      printf("to = ");
      scanf("%d", &to);
      insertEdge(graph, from, to);
			break;
		case 'b': case 'B':
      printf("from: ");
      scanf("%d", &from);
			bfs(graph, from);
      resetVisited(graph);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while(command != 'q' && command != 'Q');

  return 0;
}

 /* 새로운 그래프 생성 */
Graph *create() {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->num = 0;

  for (int i = 0; i < MAX_VERTEX; i++) {
    graph->adjList[i] = NULL;
  }
  return graph;
}

 /* 새로운 vertex 삽입*/
void insertVertex(Graph *graph) {
  if ((graph->num) + 1 > MAX_VERTEX) {
    printf("최대 vertex 수 초과\n");
    return;
  }
  graph->num++;
}

 /* vertex간 새로운 edge 삽입*/
void insertEdge(Graph *graph, int from, int to) {
  if (from >= graph->num || to >= graph->num) { // vertex가 존재하지 않는 경우
    printf("해당 vertex가 존재하지 않습니다.\n");
    return;
  }

  Node* temp = graph->adjList[from];
  Node* prev = NULL;

  while (temp && temp->vertex < to) { // 인접리스트를 순회하며 정렬된 위치 찾기
    prev = temp;
    temp = temp->next;
  }

  while (temp) { // 이미 edge가 존재하는 경우 확인
    if (temp->vertex == to) {
      printf("이미 존재하는 edge입니다.\n");
      return;
    }
    temp = temp->next;
  }

  Node *node = (Node *)malloc(sizeof(Node));
  node->vertex = to;

  // 새로운 노드를 정렬된 위치에 삽입
  if (prev == NULL) { // 첫 노드인 경우
    node->next = graph->adjList[from];
    graph->adjList[from] = node;
  } else { // 아닌 경우
    node->next = prev->next;
    prev->next = node;
  }
}

/*그래프 출력*/
void printGraph(Graph *graph) {
  for (int i = 0; i < graph->num; i++) {
    Node *node = graph->adjList[i];

    printf("vertex %d의 인접리스트: ", i);

    while (node != NULL) {
      printf("%d -> ", node->vertex);
      node = node->next;
    }
    printf("\n");
  }
}

/*그래프가 비어있는지 확인*/
int isEmpty(Graph *graph) {
  return graph->num == 0;
}

/*깊이 우선 탐색*/
void dfs(Graph *graph, int v) {
  Node* adjList = graph->adjList[v];
  Node* temp = adjList;

  visited[v] = 1; // 방문한 vertex 표시
  printf("%d -> ", v);

  while (temp != NULL) { // 인접 vertex 탐색
    int connectedV = temp->vertex;

    if (visited[connectedV] == 0) { // 방문하지 않은 vertex인 경우
      dfs(graph, connectedV);  // recursive 탐색
    }
    temp = temp->next;
  }
}

/*너비 우선 탐색*/
void bfs(Graph *graph, int v) {
  int visited[MAX_VERTEX] = {0};

  Queue* q = createQueue();

  visited[v] = 1;
  enqueue(q, v);

  while (!(q->rear == -1)) {
    int currentV = dequeue(q);
    printf("%d -> ", currentV);

    Node* temp = graph->adjList[currentV];

    while (temp) {
      int adjV = temp->vertex;

      if (visited[adjV] == 0) {
        visited[adjV] = 1;
        enqueue(q, adjV);
      }
      temp = temp->next;
    }
  }
}

/*방문한 vertex 초기화*/
void resetVisited(Graph *graph) {
  for (int i = 0; i < graph->num; i++) {
    visited[i] = 0;
  }
}

Queue* createQueue() {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

void enqueue(Queue* q, int value) {
  if (q->rear == MAX_VERTEX - 1) {
    printf("\nQueue is Full!!");
  } else {
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->vertices[q->rear] = value;
  }
}

int dequeue(Queue* q) {
  int item;

  if (q->rear == -1) {
    printf("Queue가 비어있습니다.\n");
    item = -1;
  } else {
    item = q->vertices[q->front];
    q->front++;

    if (q->front > q->rear) {
      q->front = q->rear = -1;
    }
  }
  return item;
}
