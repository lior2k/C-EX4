#include <stdio.h>
#include "graph.h"
#define backslashn 10

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

int main() {
    pnode temp_p = NULL;
    pnode *head = &temp_p;
    char x = 0;
    int flag = 0;
    while (x != backslashn) {
        x = getc(stdin);
        if (x == 'A') {

            build_graph_cmd(head);

        } else if (x == 'B') {

            insert_new_node_cmd(head);

        } else if (x == 'D') {

            delete_node_cmd(head);

        } else if (x == 'S') {
            // if (flag == 0) {
            //     shortsPath_cmd(head);
            //     flag = 1;
            // } else {
            //     flag = 1;
            //     printf("\n");
                shortsPath_cmd(head);
            // }
            

        } else if (x == 'T') {
            
            // if (flag == 0) {
            //     TSP_cmd(head);
            //     flag = 1;
            // } else {
            //     flag = 1;
            //     printf("\n");
                TSP_cmd(head);
            // }
            

        } else if (x == 'P') {

            print_graph(head);

        }
    }
}