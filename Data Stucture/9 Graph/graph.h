#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include "simple_queue.h"

// A structure to represent an adjacency list node
struct AdjListNode {
  int id;
  struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList {
  struct AdjListNode *head;  // pointer to head node of list
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph {
  int V;
  struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int id) {
  struct AdjListNode* newNode =
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
  newNode->id = id;
  newNode->next = NULL;
  return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V) {
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
  graph->V = V;

  // Create an array of adjacency lists.  Size of array will be V
  graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

  // Initialize each adjacency list as empty by making head as NULL
  int i;
  for (i = 0; i < V; ++i)
    graph->array[i].head = NULL;

  return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
  // Add an edge from src to dest.  A new node is added to the adjacency
  // list of src.  The node is added at the begining
  struct AdjListNode* newNode = newAdjListNode(dest);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  // Since graph is undirected, add an edge from dest to src also
  newNode = newAdjListNode(src);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;
}

// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->V; ++v)
  {
    struct AdjListNode* pCrawl = graph->array[v].head;
    printf("\n Adjacency list of vertex %d\n head ", v);
    while (pCrawl)
    {
      printf("-> %d", pCrawl->id);
      pCrawl = pCrawl->next;
    }
    printf("\n");
  }
}

// Inner function for DFS
void _DFSInner(struct Graph* graph, int v_id, bool *visited) {
  struct AdjListNode* child_node;
  if (graph->array[v_id].head == NULL) {
    return;
  }
  visited[v_id] = true;
  printf("%d ", v_id);
  child_node = graph->array[v_id].head;
  while (child_node) {
    v_id = child_node->id;
    if (!visited[v_id]) {
      _DFSInner(graph, v_id, visited);
    }
    child_node = child_node->next;
  }
}

// Print the graph using DFS
void DFS(struct Graph* graph, int root_vid) {
  int i;
  bool* visited = (bool*) malloc(sizeof(bool) * graph->V);
  printf("Begin DFS:\n");
  for (i = 0; i < graph->V; ++i) {
    visited[i] = false;
  }
  _DFSInner(graph, root_vid, visited);
  printf("\n");
}

// Print the graph using BFS
void BFS(struct Graph* graph, int root_vid) {
  int i, v_id;
  struct AdjListNode* child_node;
  bool* visited = (bool*)malloc(sizeof(bool) * graph->V);
  printf("Begin BFS:\n");
  for (i = 0; i < graph->V; ++i) {
    visited[i] = false;
  }
  struct SimpleQueue* queue = create_queue();
  queue_push(queue, root_vid);
  visited[root_vid] = true;
  while (!is_queue_empty(queue)) {
    v_id = queue_pop(queue);
    printf("%d ", v_id);
    child_node = graph->array[v_id].head;
    while (child_node) {
      v_id = child_node->id;
      if (!visited[v_id]) {
        visited[v_id] = true;
        queue_push(queue, v_id);
      }
      child_node = child_node->next;
    }
  }
  printf("\n");
}

#endif