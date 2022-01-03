#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "graph.h"
#include "node.h"

void print_graph(pnode *head) {
    pnode temp = *head;
    while (temp != NULL) {
        printf("node id: %d, node dist: %d ", temp -> id, temp -> dist);
        pedge edge = temp -> edges;
        while (edge != NULL) {
            printf("dest: %d, ", edge -> endpoint);
            printf("w: %d ", edge -> weight);
            edge = edge -> next;
        }
        temp = temp -> next;
        printf("\n");
    }
}

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
        new_node -> edges = NULL;
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
        n1 -> edges = NULL;
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
        new_node -> edges =NULL;
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
        if (c == 'n') {
            insert_node_cmd(head);
            i++;
        }    
    }
}