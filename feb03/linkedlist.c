#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// print list
void print_list(struct node *head)
{
    while (head != NULL)
    {
        printf("%d --> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

// insert at front
struct node *insert_node(struct node *head, int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = value;
    new_node->next = head;
    head = new_node;

    // in main function:
    // head = insert_node(head, value);
    return head;
}

// indexing/accessing
int search_list(struct node *head, int value)
{
    while (head != NULL)
    {
        if (head->data == value)
        {
            return 1;
        }
        // this "head" is a copy passed to this function
        head = head->next;
    }

    return 0;
}

// deletion
struct node *delete_node(struct node *head, int value)
{
    struct node *curr = head;
    struct node *prev = NULL;

    while (curr != NULL && curr->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        // value not found
        return head;
    }
    else if (prev == NULL)
    {
        // value is at first node
        head = head->next;
    }
    else
    {
        // deleting non-first node
        prev->next = curr->next;
    }

    free(curr);
    return head;
}

// delete list
// double pointer allows us to modify head
void delete_list(struct node **head)
{
    struct node *curr = *head, *prev = curr;

    // curr traverses
    // prev follows and cleans up after curr

    while (curr->next != NULL)
    {
        curr = curr->next;
        free(prev);
        prev->curr;
    }

    free(curr);
    *head = NULL;
    return;
}