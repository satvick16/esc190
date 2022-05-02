#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *lChild;
    struct Node *rChild;
};

int sumBST(struct Node *root)
{
    int sum = 0;

    if (root->data > 10)
    {
        sum += root->data;
    }

    if (root->lChild == NULL && root->rChild == NULL)
    {
        return sum;
    }

    if (root->lChild != NULL)
    {
        sum += sumBST(root->lChild);
    }

    if (root->rChild != NULL)
    {
        sum += sumBST(root->rChild);
    }

    return sum;
}

int main()
{
    struct Node *a = (struct Node *)malloc(sizeof(struct Node));
    struct Node *b = (struct Node *)malloc(sizeof(struct Node));
    struct Node *c = (struct Node *)malloc(sizeof(struct Node));
    struct Node *d = (struct Node *)malloc(sizeof(struct Node));
    struct Node *e = (struct Node *)malloc(sizeof(struct Node));

    a->data = 19;
    a->lChild = b;
    a->rChild = c;
    b->data = 5;
    c->data = 20;
    b->lChild = d;
    b->rChild = e;
    d->data = 2;
    e->data = 18;

    printf("%d\n", sumBST(a));

    return 0;
}