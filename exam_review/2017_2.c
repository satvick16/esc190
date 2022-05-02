#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

float averageLinkedList(struct Node *L, int n)
{
    printf("%d\n", L->data);

    if (L->next == NULL)
    {
        return (float)(L->data) / (n + 1);
    }
    else
    {
        L->next->data += L->data;
        averageLinkedList(L->next, n + 1);
    }
}

int main()
{
    struct Node *a = (struct Node *)malloc(sizeof(struct Node));
    struct Node *b = (struct Node *)malloc(sizeof(struct Node));
    struct Node *c = (struct Node *)malloc(sizeof(struct Node));
    struct Node *d = (struct Node *)malloc(sizeof(struct Node));
    struct Node *e = (struct Node *)malloc(sizeof(struct Node));

    a->data = 1;
    a->next = b;

    b->data = 5;
    b->next = c;

    c->data = 1;
    c->next = d;

    d->data = 1;
    d->next = e;

    e->data = 1;
    e->next = NULL;

    printf("%f\n", averageLinkedList(a, 0));

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);

    return 0;
}