#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

void push(struct node *head, int value)
{
    struct node *temp = head;

    while (temp != NULL)
    {
        temp = temp->next;
    }

    struct node *new = (struct node *)malloc(sizeof(struct node));
    temp->next = new;
    new->data = value;
    new->next = NULL;
}

int main()
{
    return 0;
}