#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    int endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int id;
    int dist;
    int tag; // 1 / 0 / -1 = black / white / gray (used for shortestPath)
    int info; // 1 / 0 / - 1 = black / white / gray (used for TSP)
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode *head);
void TSP_cmd(pnode *head);
void insert_new_node_cmd(pnode *head);
void free_graph(pnode *head);
int dijkstra(pnode *head, int src_index, int dest_index);
pnode get_min_dist_node(pnode *head);
pnode get_node(pnode *head, int id);
void reset_dists_and_tags(pnode *head);

#endif