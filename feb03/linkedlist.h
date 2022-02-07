struct node
{
    int data;
    struct node *next;
};

void print_list(struct node *head);
struct node *insert_node(struct node *head, int value);
int search_list(struct node *head, int value);
struct node *delete_node(struct node *head, int value);