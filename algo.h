#include "graph.h"
#include "node.h"

void reset_dists_and_tags(pnode *head);
pnode get_min_dist_node(pnode *head);
int dijkstra(pnode *head, int src_index, int dest_index);
void shortsPath_cmd(pnode *head);
void swap(int *x, int *y);
void TSP_calc_path(pnode *head, int *p_int_cities, int cities_len);
void permute(int *a, int l, int r, pnode *head);
void TSP_cmd(pnode *head);

