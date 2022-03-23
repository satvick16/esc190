#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void add_to_front(struct node **head, int val)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = val;
    new->next = *head;
    *head = new;
}

void add_to_end(struct node *head, int val)
{
    struct node *curr = head;

    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = val;
    new->next = NULL;

    curr->next = new;
}

void remove_from_front(struct node **head)
{
    struct node *temp = (*head)->next;
    free(*head);
    *head = temp;
}

void remove_from_end(struct node *head)
{
    struct node *curr = head;

    while (curr->next->next != NULL)
    {
        curr = curr->next;
    }

    free(curr->next);
    curr->next = NULL;
}

void reverse(struct node **head)
{
    struct node *curr = *head;
    struct node *left = NULL;
    struct node *right = NULL;

    while (curr != NULL)
    {
        right = curr->next;

        curr->next = left;

        left = curr;
        curr = right;
    }

    *head = left;
}

void bubble_sort(struct node **head)
{
    // get length of list
    int len = 0;

    struct node *temp = *head;

    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }

    // sort
    struct node *curr = *head;
    struct node *right = NULL;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            right = curr->next;

            if (curr->data < right->data)
            {
                if (curr == *head)
                {
                    struct node *temp = curr->next->next;
                    curr->next->next = curr;
                    curr->next = temp;
                    *head = curr;
                    right = 
                }
                else
                {
                    struct node *temp = curr->next->next;
                    curr->next->next = curr;
                    curr->next = temp;
                }
            }
            else
            {
                curr = right;
                right = right->next;
            }
        }
    }
}

void print_list(struct node *head)
{
    struct node *curr = head;

    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }

    printf("\n");
}

int main()
{
    struct node *head = NULL;
    add_to_front(&head, 1);
    add_to_end(head, 8);
    add_to_end(head, 2);
    add_to_end(head, 5);

    print_list(head);

    add_to_front(&head, 0);
    add_to_end(head, 5);

    print_list(head);

    remove_from_front(&head);
    remove_from_end(head);

    print_list(head);

    reverse(&head);

    print_list(head);

    bubble_sort(&head);

    print_list(head);

    return 0;
}