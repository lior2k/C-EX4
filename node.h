#include "graph.h"

void delete_in_edge(pnode temp_node, int src);
void free_node_edges(pnode temp_node);
void build_graph_cmd(pnode *head);
void free_graph(pnode *head);
void insert_node_cmd(pnode *head);
void insert_new_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
pnode get_node(pnode *head, int id);
pnode get_last_node(pnode *head);
void print_graph(pnode *head);