#include <stddef.h>
#include <stdio.h>

#include "main.h"
#include "toolbox.h"
#include "input.h"

uint *graph_matrix_array_init(int vertices_count)
{
  size_t graph_matrix_size = (size_t)vertices_count * (size_t)vertices_count;
  uint *graph_matrix_array = calloc(graph_matrix_size, sizeof(int));

  if (graph_matrix_array == NULL) {
    return NULL;
  }

  for (int i = 0; i < vertices_count; ++i) {
    for (int j = 0; j < vertices_count; ++j) {
      int idx = i * vertices_count + j;
      if (i == j) {
        graph_matrix_array[idx] = 0;
      } else {
        graph_matrix_array[idx] = INFINITY;
      }
    }
  }

  return graph_matrix_array;
}

Graph *graph_init(int vertices_count, int edges_count)
{
  Graph *graph = malloc(sizeof(Graph));
  uint *graph_matrix_array = graph_matrix_array_init(vertices_count);

  if (graph != NULL && graph_matrix_array != NULL) {
    graph->vertices_count = vertices_count;
    graph->edges_count = edges_count;
    graph->graph_array = graph_matrix_array;
  }

  return graph;
}

void graph_add_edge(Graph *graph, Edge *edge)
{
  uint *graph_array = graph->graph_array;
  int vertices_count = graph->vertices_count;
  int src = edge->src;
  int dst = edge->dst;
  graph_array[(src - 1) * vertices_count + (dst - 1)] = (uint)edge->weight;
  graph_array[(dst - 1) * vertices_count + (src - 1)] = (uint)edge->weight;
}

void graph_free(Graph *graph)
{
  if (graph == NULL) {
    return;
  }
  if (graph->graph_array != NULL) {
    free(graph->graph_array);
  }
  free(graph);
}
