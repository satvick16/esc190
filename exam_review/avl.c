#include <stdio.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

void right_rotate(struct Node *node_to_rotate, struct Node *parent)
{
    if (parent->left == node_to_rotate)
    {
        struct Node *temp = node_to_rotate->left;
        node_to_rotate->left = temp->right;
        temp->right = NULL;
        parent->left = temp;
    }
    else
    {
        struct Node *temp = node_to_rotate->left;
        node_to_rotate->left = temp->right;
        temp->right = NULL;
        parent->right = temp;
    }
}

int main()
{
    return 0;
}