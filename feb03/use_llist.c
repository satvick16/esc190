#include <stdio.h>
#include "linkedlist.h"

int main()
{
    struct node *head = NULL;
    head = insert_node(head, 4);
    head = insert_node(head, 3);
    head = insert_node(head, 2);
    head = insert_node(head, 1);
    print_list(head);

    return 0;
}