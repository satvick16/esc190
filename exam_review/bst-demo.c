#include <stdio.h>
#include <stdlib.h>

// BST node struct
typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// Function prototypes to declare our functions
void insert_helper(Node **root, Node *new_node);
void insert_BST(Node **root, int value);
void delete_BST(Node **root, int search_value);
Node *get_successor(Node *root);
void print_preorder(Node *root);

void insert_BST(Node **root, int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    // Empty tree case
    if (*root == NULL)
    {
        (*root) = new_node;
    }

    // Use a helper function to recurse (only allocate memory once, above)
    else if ((*root)->value > new_node->value)
    {
        insert_helper(&((*root)->left), new_node);
    }
    else
    {
        insert_helper(&((*root)->right), new_node);
    }
    return;
}

// Insert helper function for recursion
void insert_helper(Node **root, Node *new_node)
{
    if (*root == NULL)
    { // found a spot to insert
        (*root) = new_node;
    }
    else if ((*root)->value > new_node->value)
    {
        insert_helper(&((*root)->left), new_node);
    }
    else
    {
        insert_helper(&((*root)->right), new_node);
    }
    return;
}

void delete_BST(Node **root, int search_value)
{
    if ((*root) == NULL)
    { // value not found, no deletion
        return;
    }
    // Three cases when deleting (value found)
    if ((*root)->value == search_value)
    {
        // Case 1: no children
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            free(*root);
            *root = NULL;
            return;
        }
        // Case 2: one child
        else if ((*root)->left != NULL && (*root)->right == NULL)
        {
            Node *temp = (*root)->left;
            free(*root);
            *root = temp;
            return;
        }
        else if ((*root)->left == NULL && (*root)->right != NULL)
        {
            Node *temp = (*root)->right;
            free(*root);
            *root = temp;
            return;
        }
        // Case 3: two children (two sub-cases)
        else
        {
            // Helper function to find replacement (successor)
            Node *successor = get_successor((*root)->right);
            // Sub-case 1: successor is immediate right child
            if ((*root)->right == successor)
            {
                successor->left = (*root)->left;
                free(*root);
                *root = successor;
                return;
            }
            else
            { // Sub-case 2: successor is not the immediate right
                // copy successor value to root
                (*root)->value = successor->value;
                // delete successor from root's right-subtree
                delete_BST(&((*root)->right), successor->value);
                return;
            }
        }
    }
    // Recursion if we haven't found the value or reached NULL
    if ((*root)->value < search_value)
    {
        delete_BST(&((*root)->right), search_value);
    }
    else
    {
        delete_BST(&((*root)->left), search_value);
    }
}

// Helper function, note the first right was taken in delete_BST()
//   Here, we only move to the left
Node *get_successor(Node *root)
{
    if (root->left == NULL)
    {
        return root;
    }
    else
    {
        return get_successor(root->left);
    }
}

// Traversal
void print_preorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->value);  // current
    print_preorder(root->left);  // recurse left
    print_preorder(root->right); // recurse right
    // swap the above three lines for the other traversals
    // post-order: recurse(left), recurse(right), print(root)
    // in-order: recurse(left), print(root), recurse(right)
    return;
}

int main()
{
    Node *root = NULL;
    // Building partial tree from Lecture 22, Slide 11
    int values[] = {5, 2, 7, 1, 3, 6, 12};
    for (int i = 0; i < 7; i++)
    {
        insert_BST(&root, values[i]);
    }
    print_preorder(root);
    printf("\n");

    // Delete all nodes, printing between deletions
    for (int i = 0; i < 7; i++)
    {
        printf("Deleting %d:\n", values[i]);
        delete_BST(&root, values[i]);
        print_preorder(root);
        printf("\n");
    }
    return 0;
}