#include <stdio.h>
#include <stdlib.h>

#define NODES 6;

struct adjMat
{
    int matrix[NODES][NODES];
    int vNodes[NODES];
};

struct Data
{
    int value;
};

struct Stack *initStack();
void push(struct Stack *s, struct Data d);
struct Data pop(struct Stack *s);
int isEmpty(struct Stack *s);
void deleteStack(struct Stack *s);

void dfTraversal(struct adjMat *aM, int n)
{
    struct Stack *s = *initStack();
    push(s, n);

    int visited[NODES];

    for (int i = 0; i < NODES; i++)
    {
        visited[i] = 0;
    }

    visited[n] = 1;

    while (!isEmpty(s))
    {
        struct Data d = pop(s);
        printf("%d\n", d->data);
        visited[d->data] = 1;

        for (int i = 0; i < NODES; i++)
        {
            if (aM[d][i] && !visited[i])
            {
                struct Data temp;
                temp->value = i;

                push(s, temp);
            }
        }
    }

    deleteStack(s);
}

int main()
{
    return 0;
}