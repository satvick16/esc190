#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

float averageLinkedList(struct Node *L, int *n)
{
    (*n)++;

    if (L->next == NULL)
    {
        return (float)(L->data) / (float)(*n);
    }

    L->next->data += L->data;

    return averageLinkedList(L->next, n);
}

int main()
{
    struct Node *a = (struct Node *)malloc(sizeof(struct Node));
    struct Node *b = (struct Node *)malloc(sizeof(struct Node));
    struct Node *c = (struct Node *)malloc(sizeof(struct Node));
    struct Node *d = (struct Node *)malloc(sizeof(struct Node));
    struct Node *e = (struct Node *)malloc(sizeof(struct Node));
    struct Node *f = (struct Node *)malloc(sizeof(struct Node));
    struct Node *g = (struct Node *)malloc(sizeof(struct Node));
    struct Node *h = (struct Node *)malloc(sizeof(struct Node));

    a->data = 1;
    b->data = 2;
    c->data = 2;
    d->data = 4;
    e->data = 5;
    f->data = 7;
    g->data = 6;
    h->data = 3;

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    f->next = g;
    g->next = h;
    h->next = NULL;

    int *n = (int *)malloc(sizeof(int));
    *n = 0;

    printf("%f\n", averageLinkedList(a, n));

    return 0;
}