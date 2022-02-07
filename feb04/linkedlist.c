#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// when inserting/deleting head node,
// and we used struct node *head (single ptr),
// we needed to use odd code: head = insert(...)
// we can avoid this by using:
// struct node **head

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
void insert_node(struct node **head, int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
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

void reverse(struct node **head)
{
    struct node *curr = *head;
    struct node *prev = NULL;
    struct node *second = NULL;

    while (curr != NULL)
    {
        second = curr->next;

        if (prev == NULL)
        {
            curr->next = NULL;
        }
        else
        {
            curr->next = prev;
        }

        prev = curr;
        curr = second;
    }

    *head = prev;
}

void insert_at_end(struct node **head, int value)
{
    struct node *curr = *head;

    // go to end
    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    // create and add new node
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    curr->next = new_node;
    new_node->data = value;
    new_node->next = NULL;
}

// deletion
int delete_node(struct node **head, int value)
{
    struct node *curr = *head;
    struct node *prev = NULL;

    while (curr != NULL && curr->data != value)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        // value not found
        return -1;
    }
    else if (prev == NULL)
    {
        // value is at first node
        *head = (*head)->next;
    }
    else
    {
        // deleting non-first node
        prev->next = curr->next;
    }

    int data_save = curr->data;
    free(curr);
    return data_save;
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
        prev = curr;
    }

    free(curr);
    *head = NULL;
    return;
}