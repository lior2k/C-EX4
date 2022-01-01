#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "graph.h"
#define n 110
#define Max_Value 999999999
#define Black 1
#define White 0
#define Gray -1
int TSP_ANS = Max_Value;
//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
//A 3 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
//A 3 n 0 1 2 2 2 n 1 2 2 n 2 sp - 0 -> 2 w =2
//A 4 n 0 1 1 3 2 n 1 2 2 n 2 3 3 n 3 sp - 0 -> 3 w=2   


//used to delete node, input a node from our list and an endpoint, if the node contains an edge with the same endpoint, delete that edge.
void delete_in_edge(pnode temp_node, int src) {
    pedge edge = temp_node -> edges;
    pedge prev_edge = NULL;
    while (edge != NULL) {
        pedge temp = edge;
        if (temp -> endpoint == src) {
            if (prev_edge == NULL) { //indicates first iteration (src node = head node)
                temp_node -> edges = temp -> next;
                free(edge);
                break;
            }
            prev_edge -> next = temp -> next; 
            free(edge);
            break;
        }
        prev_edge = edge;
        edge = edge -> next;
    }
}

void free_node_edges(pnode temp_node) {
    pedge edge = temp_node -> edges;
    while (edge != NULL) {
        pedge temp = edge;
        edge = edge -> next;
        free(temp);
    }
    temp_node -> edges = NULL;
}

//C cmd
void delete_node_cmd(pnode *head) {
    int src;
    scanf("%d", &src);
    pnode runner = *head;
    pnode temp;
    pnode temp2;
    pnode prev = NULL;
    while (runner != NULL) {
        pnode node = runner;
        if (node -> id != src) {
            delete_in_edge(node, src);
        } else {
            temp = node;
            temp2 = prev;
            free_node_edges(node);
        }
        prev = node;
        runner = runner -> next;
    }
    if (temp == *head) {
        *head = temp -> next;
        free(temp);
    } else {
        temp2 -> next = temp -> next;
        free(temp); 
    }       
}

//find node function - return node pointer or null if no such node
pnode get_node(pnode *head, int id) {
    pnode temp_node = *head;
    while (temp_node != NULL) {
        if (temp_node -> id == id) {
            return temp_node;
        }
        temp_node = temp_node -> next;
    }
    return NULL;
}

//set all nodes distaces and tags
void reset_dists_and_tags(pnode *head) {
    pnode temp_node = *head;
    while (temp_node != NULL) {
        temp_node -> dist = Max_Value; 
        temp_node -> tag = White;
        temp_node = temp_node -> next;
    }
}

//traverse the nodes and return the node with the minimal distance out of the unvisited nodes
pnode get_min_dist_node(pnode *head) {
    int min_dist = Max_Value;
    pnode runner = *head;
    pnode ans = NULL;
    while (runner != NULL) {
        if ((runner -> dist) < min_dist && (runner -> tag) != Black) {
            min_dist = runner -> dist;
            ans = runner;
        }
        runner = runner -> next;
    }
    return ans;
}

int dijkstra(pnode *head, int src_index, int dest_index) {
    pnode src_node = get_node(head, src_index);
    pnode dest_node = get_node(head, dest_index);
    if (src_node == NULL || dest_node == NULL) {
        return -1;
    }
    reset_dists_and_tags(head);
    src_node -> dist = 0;
    while (1) {
        pnode u = get_min_dist_node(head); 
        if (u == NULL) {
            return (dest_node -> dist);
        } else {
            u -> tag = Black;
            pedge edge = u -> edges;
            while (edge != NULL) {
                int endpoint = edge -> endpoint;
                pnode v = get_node(head, endpoint);
                int distance = (u -> dist) + (edge -> weight);
                if (distance < (v -> dist)) {
                    v -> dist = distance;
                }
                edge = edge -> next;
            }
        }
    }
    return dest_node -> dist;
}

//S cmd
void shortsPath_cmd(pnode *head) {
    int src_index, dest_index;
    scanf("%d%d", &src_index, &dest_index);
    int dist = dijkstra(head, src_index, dest_index);
    if (dist == Max_Value) {
        printf("Dijsktra shortest path: -1");
    } else {
        printf("Dijsktra shortest path: %d", dist);
    }  
}

// pnode get_first_white_node(pnode *cities, int cities_len) {
//     for (int i = 0; i < cities_len; i++) {
//         if (cities[i] -> info == White) {
//             return cities[i];
//         }
//     }
//     return NULL;
// }

// pnode get_first_non_black(pnode *cities, int cities_len) {
//     for (int i = 0; i < cities_len; i++) {
//         if (cities[i] -> info != Black) {
//             return cities[i];
//         }
//     }
//     return NULL;
// }

// int count_grays_nodes(pnode *cities, int cities_len) {
//     int counter = 0;
//     for (int i = 0; i < cities_len; i++) {
//         if (cities[i] -> info == Gray) {
//             counter++;
//         }
//     }
//     return counter;
// }

// int count_blacks_nodes(pnode *cities, int cities_len) {
//     int counter = 0;
//     for (int i = 0; i < cities_len; i++) {
//         if (cities[i] -> info == Black) {
//             counter++;
//         }
//     }
//     return counter;
// }

// void reset_info(pnode *head) {
//     pnode temp_node = *head;
//     while (temp_node != NULL) {
//         temp_node -> info = 0;
//         temp_node = temp_node -> next;
//     }
// }

void swap(int *x, int *y) { 
    int temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void TSP_calc_path(pnode *head, int *p_int_cities, int cities_len) {
    int total_dist = 0;
    int i = 0;
    while (i < cities_len -1) {
        int dist = dijkstra(head, p_int_cities[i], p_int_cities[i+1]);
        if (dist == -1) {
            return;
        }
        total_dist += dist;
        i++;
    }
    if (total_dist < TSP_ANS && total_dist > 0) {
        TSP_ANS = total_dist;
    }
}

void permute(int *a, int l, int r, pnode *head) {
    int i; 
    if (l == r) {
        int cities[r+1];
        for(int k = 0; k <= r; k++) {
            cities[k] = a[k];
        }
        int *p = cities;
        TSP_calc_path(head, p, r+1);
    }  else { 
        for (i = l; i <= r; i++) {
            swap((a + l), (a + i)); 
            permute(a, l+1, r, head); 
            swap((a + l), (a + i)); 
        } 
    } 
}

void TSP_cmd(pnode *head) {
    TSP_ANS = Max_Value;
    int cities_len;
    scanf("%d", &cities_len);
    int int_cities[cities_len];
    int *p_int_cities = int_cities;
    int i = 0;
    int city;
    while (i < cities_len) {
        scanf("%d", &city);
        p_int_cities[i] = city; 
        i++;
    }
    permute(int_cities, 0, cities_len-1, head);
    if (TSP_ANS == Max_Value) {
        printf("TSP shortest path: -1\n");
    } else {
        printf("TSP shortest path: %d\n", TSP_ANS);
    }
}

pnode get_last_node(pnode *head) {
    pnode runner = *head;
    while (runner -> next != NULL) {
        runner = runner -> next;
    }
    return runner;
}

//B cmd
void insert_new_node_cmd(pnode *head) {
    int id;
    pnode new_node;
    pedge new_edge;
    int endpoint;
    int weight;
    scanf("%d", &id);
    pnode temp_node = get_node(head, id);
    pnode last_node = get_last_node(head);
    if (temp_node == NULL) {
        new_node = (pnode) malloc (sizeof(node));
        new_node -> id = id;
        new_node -> next = NULL;
        last_node -> next = new_node;
    } else {
        free_node_edges(temp_node);
        new_node = temp_node;
    }
    while (scanf("%d", &endpoint)) {
        scanf("%d", &weight);
        new_edge = (pedge) malloc(sizeof(edge));
        new_edge -> endpoint = endpoint;
        new_edge -> weight = weight;
        new_edge ->next = NULL;
        if (new_node -> edges == NULL) {
            new_node -> edges = new_edge;
        } 
        else {
            pedge last_edge = new_node -> edges;
            while (last_edge -> next != NULL) {
                last_edge = last_edge -> next;
                printf("%p\n" , last_edge);
            }
            last_edge -> next = new_edge;
        }
    }
    
}

//used for build graph
void insert_node_cmd(pnode *head) {
    int id;
    pnode new_node;
    pedge new_edge;
    int endpoint;
    int weight;
    scanf("%d", &id);
    if (*head == NULL) {
        pnode n1 = (pnode) malloc (sizeof(node));
        *head = n1;
        n1 -> id = id;
        n1 -> next = NULL;
        while (scanf("%d", &endpoint)) {
            scanf("%d", &weight);
            new_edge = (pedge) malloc(sizeof(edge));
            new_edge -> endpoint = endpoint;
            new_edge -> weight = weight;
            new_edge -> next = NULL;
            if (n1 -> edges == NULL) {
                n1 -> edges = new_edge;          
            } else {
                pedge last_edge = n1 -> edges;
                while (last_edge ->next != NULL) {
                    last_edge = last_edge ->next;
                }
                last_edge ->next = new_edge;
            }  
        }
    } else {
        new_node = (pnode) malloc (sizeof(node));
        new_node -> id = id;
        new_node -> next = NULL;
        pnode last_node = *head;
        while (last_node -> next != NULL) {
            last_node = last_node -> next;
        }
        last_node -> next = new_node;
        while (scanf("%d", &endpoint)) {
            scanf("%d", &weight);
            new_edge = (pedge) malloc(sizeof(edge));
            new_edge -> endpoint = endpoint;
            new_edge -> weight = weight;
            new_edge -> next = NULL;
            if (new_node -> edges == NULL) {
                new_node -> edges = new_edge;
            } else {
                pedge last_edge = new_node -> edges;
                while (last_edge ->next != NULL) {
                    last_edge = last_edge ->next;
                }
                last_edge ->next = new_edge;
            } 
        }
    }
}

void free_graph(pnode *head) {
    pnode node = *head;
    pnode prev;
    while (node != NULL) {
        prev = node;
        node = node -> next;
        free_node_edges(prev);
        free(prev);
    }
    *head = NULL;
}

void build_graph_cmd(pnode *head) {
    if (*head != NULL) {
        free_graph(head);
    }
    int vertices;
    scanf("%d", &vertices);
    char c;
    int i = 0;
    while (i < vertices) {
        scanf("%c", &c);
        if (c == n) {
            insert_node_cmd(head);
            i++;
        }    
    }
}
