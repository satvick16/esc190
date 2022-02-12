#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void enqueue(struct node **front, struct node **back, int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = NULL;

    if (*front == NULL)
    {
        *front = new_node;
        *back = new_node;
    }
    else
    {
        (*back)->next = new_node;
        *back = new_node;
    }
}

void dequeue(struct node **front, struct node **back, int value)
{
    if ((*front) == NULL)
    {
        return;
    }

    struct node *bye_node = *front;
    *front = (*front)->next;
    free(bye_node);

    if ((*front) == NULL)
    {
        *back = NULL;
    }
}

int main()
{
    // queues
    // store pointer to end node to make enqueue operations O(1)
}