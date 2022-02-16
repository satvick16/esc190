#include "lab3.h"

// Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta)
{
    if (strcmp(item, "IDE") == 0)
    {
        return -1;
    }

    struct party_node *new_node = (struct party_node *)malloc(sizeof(struct party_node));

    new_node->item = (char *)malloc(strlen(item) + 1);
    // new_node->item = item;
    strcpy(new_node->item, item);

    new_node->price = price;

    new_node->ta = (char *)malloc(strlen(ta) + 1);
    // new_node->ta = ta;
    strcpy(new_node->ta, ta);

    new_node->next = *head;
    *head = new_node;

    return 0;
}

// Remove the last item added
void remove_request(struct party_node **head)
{
    if (*head == NULL)
    {
        return;
    }

    struct party_node *temp = *head;
    *head = temp->next;

    free(temp->item);
    free(temp->ta);
    free(temp);
}

// Sort party item requests - in place?
void make_sorted(struct party_node **head)
{
    int len = 0;
    struct party_node *temp = *head;

    while (temp != NULL)
    {
        len++;
        temp = temp->next;
    }

    temp = *head;
    struct party_node *prev = NULL;
    struct party_node *mem = NULL;

    for (int i = 0; i <= len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (temp->price < temp->next->price)
            {
                if (temp == *head)
                {
                    mem = temp->next;
                    temp->next = temp->next->next;
                    mem->next = temp;
                    *head = mem;
                    prev = mem;
                }
                else
                {
                    mem = temp->next;
                    prev->next = temp->next;
                    temp->next = temp->next->next;
                    mem->next = temp;
                    prev = mem;
                }
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }

        temp = *head;
    }
}

// Trim list to fit the budget
double finalize_list(struct party_node **head, double budget)
{
    struct party_node *curr = *head;
    struct party_node *prev = NULL;
    double leftover = budget;

    while (curr != NULL)
    {
        if (curr->price <= leftover)
        {
            leftover -= curr->price;
            prev = curr;
            curr = curr->next;
        }
        else
        {
            if (prev == NULL)
            {
                free(curr->item);
                free(curr->ta);
                struct party_node *temp = curr->next;
                free(curr);
                curr = temp;
                *head = temp;
            }
            else
            {
                prev->next = curr->next;
                free(curr->item);
                free(curr->ta);
                free(curr);
                curr = prev->next;
            }
        }
    }

    return leftover;
}

// Print the current list - hope this is helpful!
void print_list(struct party_node *head)
{
    int count = 1;
    printf("The current list contains:\n");
    while (head != NULL)
    {
        printf("Item %d: %s, %.2lf, requested by %s\n",
               count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}