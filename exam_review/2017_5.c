#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int vLabel;
    struct Node *lChild;
    struct node *rChild;
};

struct Data
{
    struct Node *n;
    int mark;
};

struct Stack *initStack();
void push(struct Stack *s, struct Data d);
struct Data pop(struct Stack *s);
int isEmpty(struct Stack *s);
void deleteStack(struct Stack *s);

void inOrderTraversal(struct Node *root)
{
    // no recursion
    // essentially dfs (stack)
    Stack *s = initStack();

    // traverse left subtree
    push(s, root->lChild);

    while (!isEmpty(s))
    {
        struct Data curr = pop(s);

        // left
        if (curr->n->lChild != NULL)
        {
            push(s, curr->n->lChild);
        }
        // curr
        printf("%d\n", curr->n->vLabel);
        // right
        if (curr->n->rChild != NULL)
        {
            push(s, curr->n->rChild);
        }
    }

    // traverse current node
    printf("%d\n", root->vLabel);

    // traverse right subtree
    deleteStack(s);
    Stack *s = initStack();

    push(s, root->rChild);

    while (!isEmpty(s))
    {
        struct Data curr = pop(s);

        // left
        if (curr->n->lChild != NULL)
        {
            push(s, curr->n->lChild);
        }
        // curr
        printf("%d\n", curr->n->vLabel);
        // right
        if (curr->n->rChild != NULL)
        {
            push(s, curr->n->rChild);
        }
    }
}

int main()
{
    return 0;
}