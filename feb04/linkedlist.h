struct node
{
    int data;
    struct node *next;
};

void print_list(struct node *head);
void insert_node(struct node **head, int value);
int search_list(struct node *head, int value);
int delete_node(struct node **head, int value);
void reverse(struct node **head);
void insert_at_end(struct node **head, int value);