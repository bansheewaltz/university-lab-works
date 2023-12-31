#include "dijkstra_algorithm.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "graph.h"
#include "utils.h"

static int get_min_dist_v(bool const visited[], uint64_t const dist[],
                          int n_vertices) {
  int min_dist_v = 1;

  for (int i = 1; i <= n_vertices; ++i) {
    if (!visited[i]) {
      min_dist_v = i;
      break;
    }
  }

  for (int i = min_dist_v; i <= n_vertices; ++i) {
    if (!visited[i] && dist[i] < dist[min_dist_v]) {
      min_dist_v = i;
    }
  }

  return min_dist_v;
}

static void relaxate_lists(Graph *graph, uint64_t dist[], bool const visited[],
                           int previous_v[], int min_dist_v) {
  assert(graph->adj_lists != NULL);

  AdjListNode *neighbour = graph->adj_lists[min_dist_v];

  while (neighbour != NULL) {
    if (!visited[neighbour->dst]) {
      int neighbour_v = neighbour->dst;
      int rel_dist_to_neighbour = neighbour->length;
      uint64_t calculated_distance = dist[min_dist_v] + rel_dist_to_neighbour;

      if (calculated_distance < dist[neighbour_v]) {
        dist[neighbour_v] = calculated_distance;
        previous_v[neighbour_v] = min_dist_v;
      }
    }
    neighbour = neighbour->next;
  }
}

static void relaxate_matrix(Graph *graph, uint64_t dist[], bool const visited[],
                            int previous_v[], int min_dist_v) {
  assert(graph->adj_matrix != NULL);

  for (int c = 1; c <= graph->n_vertices; ++c) {
    if (!visited[c] && is_matrix_neighbour(graph, min_dist_v, c)) {
      int rel_dist_to_neighbour = get_adj_matrix_entry(graph, min_dist_v, c);
      uint64_t calculated_distance = dist[min_dist_v] + rel_dist_to_neighbour;

      if (calculated_distance < dist[c]) {
        dist[c] = calculated_distance;
        previous_v[c] = min_dist_v;
      }
    }
  }
}

static void relaxate_neighbours(Graph *graph, uint64_t dist[],
                                bool const visited[], int previous_v[],
                                int min_dist_v) {
  assert(graph != NULL);

  if (graph->representation == ADJACENCY_LIST) {
    relaxate_lists(graph, dist, visited, previous_v, min_dist_v);
  }

  if (graph->representation == ADJACENCY_MATRIX) {
    relaxate_matrix(graph, dist, visited, previous_v, min_dist_v);
  }
}

PathInfo find_shortest_path_dijkstra_naive(Graph *graph, int src, int dst) {
  assert(graph != NULL);

  int n_vertices = graph->n_vertices;
  int arr_size = n_vertices + 1;
  bool *visited = (bool *)calloc(arr_size, sizeof(bool));
  uint64_t *dist = (uint64_t *)malloc(sizeof(uint64_t) * arr_size);
  int *previous_v = (int *)malloc(sizeof(int) * arr_size);

  if_fail(visited == NULL, __FILE__, __LINE__ - 4);
  if_fail(dist == NULL, __FILE__, __LINE__ - 4);
  if_fail(previous_v == NULL, __FILE__, __LINE__ - 4);

  for (int i = 0; i <= n_vertices; ++i) {
    dist[i] = INFINITY_LENGTH;
    previous_v[i] = UNDEFINED_NEIGHBOUR;
  }
  dist[src] = 0;

  for (int n_visited = 0; n_visited < n_vertices; ++n_visited) {
    int min_dist_v = get_min_dist_v(visited, dist, n_vertices);
    if (dist[min_dist_v] == INFINITY_LENGTH) {
      break;
    }

    visited[min_dist_v] = true;
    relaxate_neighbours(graph, dist, visited, previous_v, min_dist_v);
  }

  free(visited);
  return (PathInfo){src, dst, dist, previous_v, n_vertices};
}
