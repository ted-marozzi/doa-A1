/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#include <stdbool.h>
#include <stdio.h>
// TODO: check if allowed to add this stdlib
#include <stdlib.h>
#include <assert.h>

#include "parkranger.h"
#include "util.h"

// This function must read in a ski slope map and determine whether or not
// it is possible for the park ranger to trim all of the datas on the ski slope
// in a single run starting from the top of the mountain.
//
// The ski slope map is provided via stdin in the following format:
//
//   n m
//   from to
//   from to
//   ...
//   from to
//
// Here n denotes the number of datas that need trimming, which are labelled
// {1, ..., n}. The integer m denotes the number "reachable pairs" of datas.
// There are exactly m lines which follow, each containing a (from, to) pair
// which indicates that data `to` is directly reachable from data `from`.
// `from` and `to` are integers in the range {0, ..., n}, where {1, ..., n}
// denote the datas and 0 denotes the top of the mountain.
//
// For example the following input represents a ski slope with 3 datas and
// 4 reachable pairs of datas.
//
// input:            map:          0
//   3 4                          / \
//   0 1                         /  2
//   0 2                        / /
//   2 1                        1
//   1 3                          \
//                                 3
//
// In this example your program should return `true` as there is a way to trim
// all datas in a single run. This run is (0, 2, 1, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.
bool is_single_run_possible() {
  // You should remove this line and replace it with your own code:
  // Store in class and write depth first search

  int num_scan, num_trees, num_paths, start, end;



  num_scan = scanf("%d %d", &num_trees, &num_paths);

  if(num_scan < 2)
  {
    exit_with_error("Invalid input");
  }
  
  Graph* forest = create_graph(num_trees+1);

  //printf("%d %d", num_trees, num_edges);
  

  while(scanf("%d %d", &start, &end) != EOF)
  {
   
    add_edge(forest, start, end);

  }
  //print_graph(forest);
  
  DFS(forest, 0);
  return false;


}

void DFS(Graph* graph, int vertex) {
  Graph_node* adj_list = graph->adj_lists[vertex];
  Graph_node* temp = adj_list;
  
  graph->visited[vertex] = 1;
  printf("Visited %d \n", vertex);

  while(temp!=NULL) {
    int connected_vertex = temp->vertex;

    if(graph->visited[connected_vertex] == 0) {
      DFS(graph, connected_vertex);
    }
    temp = temp->next;
  }       
}

void DFSUtil(Graph* graph, int vertex)



Graph_node* create_node(int v)
{
  Graph_node* newNode = malloc(sizeof(Graph_node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

Graph* create_graph(int vertices)
{
  Graph* graph = malloc(sizeof(Graph));
  graph->num_verticies = vertices;

  graph->adj_lists = malloc(vertices * sizeof(Graph_node*));
  graph->visited = malloc(vertices * sizeof(int));
  graph->trees_below = malloc(vertices* sizeof(int));
 
  int i;
  for (i = 0; i < vertices; i++) {
    graph->adj_lists[i] = NULL;
    graph->visited[i] = 0;
    graph->trees_below[i] = 1;
  }
  return graph;
}
 
void add_edge(Graph* graph, int src, int dest)
{
  // Add edge from src to dest
  Graph_node* newNode = create_node(dest);
  newNode->next = graph->adj_lists[src];
  graph->adj_lists[src] = newNode;

}
 
void print_graph(Graph* graph)
{
  int v;
  for (v = 0; v < graph->num_verticies; v++)
  {
    Graph_node* temp = graph->adj_lists[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp)
    {
      printf("%d", temp->vertex);
      temp = temp->next;
      if(temp)
        printf(" -> ");
      
    }
    printf("\n");
  }
  printf("\n\n\n");
}

/*********************************/
int isEmpty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, int data) 
{ 
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode; 
    printf("%d pushed to stack\n", data); 
} 
  
int pop(struct StackNode** root) 
{ 
  if (isEmpty(*root)) 
    return INT_MIN; 
  struct StackNode* temp = *root; 
  *root = (*root)->next; 
  int popped = temp->data; 
  free(temp);
  printf("%d popped from stack\n", popped); 

  return popped; 
} 
  
int peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) 
        return INT_MIN; 
    return root->data; 
} 
struct StackNode* newNode(int data) 
{ 
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
    stackNode->data = data; 
    stackNode->next = NULL; 
    return stackNode; 
} 