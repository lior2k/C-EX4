#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "graph.h"
#define Max_Value 999999999
#define Black 1
#define White 0
#define Gray -1
int TSP_ANS = Max_Value;


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
        printf("Dijsktra shortest path: -1 \n");
    } else {
        printf("Dijsktra shortest path: %d \n", dist);
    }  
}

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
        printf("TSP shortest path: -1 \n");
    } else {
        printf("TSP shortest path: %d \n", TSP_ANS);
    }
}
