#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
// Created by hanam on 2022-04-04.
//

#define MAX_LEN 20 // max length for a vertex name

typedef struct Enode
{                         // edge node struct
    char vertex[MAX_LEN]; // destination vertex name
    int weight;           // edge weight
    struct Enode *next;   // next edge node
} Enode;

typedef struct Vnode
{                          // vertex node struct
    char station[MAX_LEN]; // station name
    Enode *edges;          // pointer to first edge
    int cost;              // optional for you to use
    int visited;           // optional for you to use
    struct Vnode *prev;    // optional for you to use
} Vnode;

typedef struct Graph
{                     // graph struct
    Vnode **adj_list; // pointer to array of vertex pointers
    int count;        // number of vertices in the graph
} Graph;

// lab5.c
char **plan_route(Graph *gr, char *start, char *dest);
void add(Graph *gr, char *station);
void update(Graph *gr, char *start, char *dest, int weight);
void disrupt(Graph *gr, char *station);

// extras.c
Graph *initialize_graph();
void print_gr(Graph *gr);
void free_gr(Graph *gr);
void print_route(char **route, char *start);

// char **plan_route(Graph *gr, char *start, char *dest){
// }

void add(Graph *gr, char *station)
{
    // first check if the station already exists
    if (gr->adj_list != NULL)
    {
        for (int i = 0; i < gr->count; i++)
        {
            if (strcmp((gr->adj_list)[i]->station, station) == 0)
            {
                return;
            }
        }
    }
    // otherwise, you are adding the station
    gr->adj_list = realloc(gr->adj_list, ((gr->count) + 1) * sizeof(Vnode *)); // reallocates size
    gr->adj_list[gr->count] = (Vnode *)malloc(sizeof(Vnode));
    strcpy(gr->adj_list[gr->count]->station, station);
    gr->adj_list[gr->count]->edges = NULL;
    gr->count++; // update number of nodes
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    int star = 0;
    int end = 0;
    int start_index = 0;
    int end_index = 0;
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp(gr->adj_list[i]->station, start) == 0)
        {
            star = 1;
            start_index = i;
        }
        if (strcmp(gr->adj_list[i]->station, dest) == 0)
        {
            end = 1;
            end_index = i;
        }
    }

    // if beginning doesn't exist
    if (star == 0)
    {
        add(gr, start);
        start_index = gr->count;
    }
    if (end == 0)
    {
        add(gr, dest);
        end_index = gr->count;
    }

    // if the vertex doesn't exist
    Enode *curr = ((gr->adj_list)[start_index])->edges;
    Enode *prev = NULL;
    int i = 0;
    while (curr != NULL)
    {
        if (strcmp(curr->vertex, dest) == 0)
        {
            i = 1;
        }
        curr = curr->next;
    }

    if (i == 0 && weight != 0)
    { // the edge does not exist
        Enode *newNode = (Enode *)malloc(sizeof(Enode));
        strcpy(newNode->vertex, dest);
        newNode->weight = weight;
        newNode->next = NULL;
        Enode *curr = gr->adj_list[start_index]->edges;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    else
    {
        if (weight == 0)
        {
            Enode *curr = gr->adj_list[start_index]->edges;
            Enode *prev = NULL;
            while (curr != NULL)
            {
                if (strcmp(curr->vertex, dest) == 0 && curr->weight != 0)
                { // youve found the vertex and want to remove it
                    if (prev == NULL)
                    { // its the first node
                        gr->adj_list[start_index]->edges = curr->next;
                        free(curr);
                        break;
                    }
                    else if (prev != NULL && curr->next != NULL)
                    {
                        prev->next = curr->next;
                        free(curr);
                        break;
                    }
                    else
                    {
                        prev->next = NULL;
                        free(curr);
                        break;
                    }
                }
                prev = curr;
                curr = curr->next;
            }
        }
        else
        { // weight does not equal zero
            Enode *curr = gr->adj_list[start_index]->edges;
            Enode *prev = NULL;
            while (curr != NULL)
            {
                if (strcmp(curr->vertex, dest) == 0)
                {
                    curr->weight = weight;
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

Graph *initialize_graph()
{
    Graph *g = malloc(sizeof(Graph));
    g->adj_list = NULL;
    g->count = 0;
    return g;
}

void print_gr(Graph *gr)
{
    Enode *curr = NULL;
    printf("Printing the graph with count %d...\n", gr->count);
    for (int i = 0; i < gr->count; i++)
    {
        printf("%s station: ", gr->adj_list[i]->station);
        curr = gr->adj_list[i]->edges;
        while (curr != NULL)
        {
            printf("%s(%d) ", curr->vertex, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    // Building the graph in Figure 1
    Graph *gr = initialize_graph();
    add(gr, "Kipling");
    add(gr, "Spadina");
    add(gr, "Yorkdale");

    update(gr, "Kipling", "Spadina", 12);
    // update(gr, "Spadina", "Yorkdale", 8);
    // update(gr, "Spadina", "Bay", 2);
    // update(gr, "Spadina", "Union", 4);
    // update(gr, "Bay", "Bloor-Yonge", 1);
    // update(gr, "Union", "Bloor-Yonge", 3);
    // update(gr, "Bloor-Yonge", "Kennedy", 14);
    // update(gr, "Bloor-Yonge", "Sheppard-Yonge", 11);
    // update(gr, "Sheppard-Yonge", "Finch", 3);
    // update(gr, "Sheppard-Yonge", "Don Mills", 6);

    //
    // //char **r = plan_route(gr, "Kipling", "Don Mills");
    // //print_route(r, "Kipling");

    // //Bye bye Bay!
    // disrupt(gr, "Bay");
    // print_gr(gr);
    // //r = plan_route(gr, "Kipling", "Don Mills");
    // //print_route(r, "Kipling");

    // //Hello new stations
    // update(gr, "Yorkdale", "Sheppard West", 5);
    // update(gr, "Sheppard West", "Sheppard-Yonge", 4);
    // print_gr(gr);
    // //r = plan_route(gr, "Kipling", "Don Mills");
    // //print_route(r, "Kipling");

    return 0;
}