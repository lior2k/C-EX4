#include <stdio.h>
#include "graph.h"
#include "node.h"
#include "algo.h"
#include <stdlib.h>
#define backslashn 10


int main() {
    pnode temp_p = NULL;
    pnode *head = &temp_p;
    char x = 0;
    while (x != backslashn) {
        x = getc(stdin);
        if (x == 'A') {

            build_graph_cmd(head);

        } else if (x == 'B') {

            insert_new_node_cmd(head);

        } else if (x == 'D') {

            delete_node_cmd(head);

        } else if (x == 'S') {

            shortsPath_cmd(head);

        } else if (x == 'T') {
            
            TSP_cmd(head);

        } else if (x == 'P') {

            print_graph(head);

        }
    }
    free_graph(head);
}