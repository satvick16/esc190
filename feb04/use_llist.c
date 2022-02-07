#include <stdio.h>
#include "linkedlist.h"

int main()
{
    struct node *head = NULL;
    insert_node(&head, 4);
    insert_node(&head, 3);
    insert_node(&head, 2);
    insert_node(&head, 1);

    print_list(head);

    reverse(&head);

    print_list(head);

    insert_at_end(&head, 5);

    print_list(head);

    return 0;
}