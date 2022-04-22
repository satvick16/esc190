#include "lab5.h"

void reset_gr(Graph *gr)
{
    for (int i = 0; i < gr->count; i++)
    {
        (gr->adj_list)[i]->cost = -1;
        (gr->adj_list)[i]->visited = 0;
        (gr->adj_list)[i]->prev = NULL;
    }
}

int min_dist_from_q(Graph *gr, char **q, int q_size)
{
    int min_dist = 5001;
    int decision = -1;
    int loc = -1;

    // for each node in queue
    for (int i = 0; i < q_size; i++)
    {
        // locate node in graph
        for (int j = 0; j < gr->count; j++)
        {
            if (strcmp(q[i], (gr->adj_list)[j]->station) == 0)
            {
                loc = j;
            }
        }

        // printf("%s, %d\n", q[i], (gr->adj_list)[loc]->cost);

        if ((gr->adj_list)[loc]->cost < min_dist && (gr->adj_list)[loc]->cost != -1)
        {
            min_dist = (gr->adj_list)[loc]->cost;
            decision = i;
        }
    }

    return decision;
}

char **plan_route(Graph *gr, char *start, char *dest)
{
    reset_gr(gr);

    // PRIORITY QUEUE AS DYNAMIC STRING ARRAY
    char **q = (char **)malloc(gr->count * sizeof(char *));

    // add all nodes to queue and set cost of start to 0
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp((gr->adj_list)[i]->station, start) == 0)
        {
            (gr->adj_list)[i]->cost = 0;
        }

        q[i] = (char *)malloc(MAX_LEN);
        strcpy(q[i], (gr->adj_list)[i]->station);
    }

    int q_size = gr->count;

    // for (int i = 0; i < q_size; i++)
    // {
    //     printf("%s\n", q[i]);
    // }

    int head_in_list = 0;

    // find head in adj_list
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp((gr->adj_list)[i]->station, q[0]) == 0)
        {
            head_in_list = 1;
        }
    }

    // if head not in list, don't even bother
    if (!head_in_list)
    {
        // free queue
        for (int i = 0; i < gr->count; i++)
        {
            free(q[i]);
        }
        free(q);

        char **null_ptr = NULL;
        return null_ptr;
    }

    while (q_size > 0)
    {
        // curr = next in queue
        int decision = min_dist_from_q(gr, q, q_size);
        // printf("%d\n", decision);
        char *curr = q[decision];

        // pop from queue
        for (int i = 0; i < q_size - 1; i++)
        {
            if (i >= decision)
            {
                q[i] = q[i + 1];
            }
        }

        q = realloc(q, sizeof(char *) * (q_size - 1));

        q_size--;

        // for (int i = 0; i < q_size; i++)
        // {
        //     printf("%s\n", q[i]);
        // }
        // printf("\n");

        int a = sizeof(q[0]);

        // locate curr in adj_list
        int curr_loc = -1;

        for (int i = 0; i < gr->count; i++)
        {
            if (strcmp((gr->adj_list)[i]->station, curr) == 0)
            {
                curr_loc = i;
                break;
            }
        }

        free(curr);

        // iterate through neighbours
        Enode *neighbour = (gr->adj_list)[curr_loc]->edges;

        while (neighbour != NULL)
        {
            // find the Vnode corresponding to the current Enode
            int neighbour_loc = -1;

            for (int j = 0; j < gr->count; j++)
            {
                if (strcmp((gr->adj_list)[j]->station, neighbour->vertex) == 0)
                {
                    neighbour_loc = j;
                    break;
                }
            }

            int new_cost = (gr->adj_list)[curr_loc]->cost + neighbour->weight;
            int old_cost = (gr->adj_list)[neighbour_loc]->cost;

            if (old_cost == -1 || (new_cost < old_cost))
            {
                // set new prev and cost
                (gr->adj_list)[neighbour_loc]->prev = (gr->adj_list)[curr_loc];
                (gr->adj_list)[neighbour_loc]->cost = new_cost;
            }

            neighbour = neighbour->next;
        }
    }

    free(q);

    // return char** with route from start to dest

    // locate dest in adj_list
    int dest_loc = -1;

    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp((gr->adj_list)[i]->station, dest) == 0)
        {
            dest_loc = i;
        }
    }

    // if dest not in adj_list, don't even bother
    if (dest_loc == -1)
    {
        char **null_ptr = NULL;
        return null_ptr;
    }

    // get the number of edges between dest and start
    Vnode *confirmer = (gr->adj_list)[dest_loc];
    int counting_edges = 0;
    int start_and_dest_are_connected = 0;

    while (confirmer != NULL)
    {
        counting_edges++;

        // printf("%s\n", confirmer->station);

        if (strcmp(confirmer->station, start) == 0)
        {
            start_and_dest_are_connected = 1;
            break;
        }

        confirmer = confirmer->prev;
    }

    // if start and dest aren't connected, don't even bother
    if (!start_and_dest_are_connected)
    {
        char **null_ptr = NULL;
        return null_ptr;
    }

    char **route = (char **)malloc(sizeof(char *) * counting_edges);
    for (int i = 0; i < counting_edges; i++)
    {
        route[i] = (char *)malloc(MAX_LEN);
    }

    strcpy(route[0], (gr->adj_list)[dest_loc]->station);

    Vnode *route_tracer = (gr->adj_list)[dest_loc]->prev;

    int iterator = 1;

    while (strcmp(route_tracer->station, start) != 0)
    {
        strcpy(route[iterator], route_tracer->station);
        iterator++;
        route_tracer = route_tracer->prev;
    }

    strcpy(route[iterator], route_tracer->station);

    return route;
}

void add(Graph *gr, char *station)
{
    // check if station already in graph
    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp((gr->adj_list)[i]->station, station) == 0)
        {
            return;
        }
    }

    // add station to graph
    gr->adj_list = realloc(gr->adj_list, sizeof(Vnode) * (gr->count + 1));

    Vnode *new = (Vnode *)malloc(sizeof(Vnode));
    strcpy(new->station, station);
    new->edges = NULL;
    new->cost = -1;
    new->visited = 0;
    new->prev = NULL;

    gr->adj_list[gr->count] = new;
    gr->count++;
}

void update(Graph *gr, char *start, char *dest, int weight)
{
    if (weight == 0)
    {
        // remove edge
        // looking for start
        for (int i = 0; i < gr->count; i++)
        {
            if (strcmp((gr->adj_list)[i]->station, start) == 0)
            {
                // dest is first edge?...
                if (strcmp(gr->adj_list[i]->edges->vertex, dest) == 0)
                {
                    Enode *del = gr->adj_list[i]->edges;
                    gr->adj_list[i]->edges = gr->adj_list[i]->edges->next;
                    free(del);
                    return;
                }

                // looking for dest
                Enode *curr = (gr->adj_list)[i]->edges;
                Enode *prev = NULL;

                while (curr != NULL)
                {
                    if (strcmp(curr->vertex, dest) == 0)
                    {
                        // remove edge
                        prev->next = curr->next;
                        free(curr);
                        return;
                    }

                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
    else
    {
        // check if start not already in graph
        // check if dest not already in graph
        int start_in_graph = 0;
        int dest_in_graph = 0;

        for (int i = 0; i < gr->count; i++)
        {
            if (strcmp((gr->adj_list)[i]->station, start) == 0)
            {
                start_in_graph = 1;
            }

            if (strcmp((gr->adj_list)[i]->station, dest) == 0)
            {
                dest_in_graph = 1;
            }
        }

        if (!start_in_graph)
        {
            // add start to graph
            add(gr, start);
        }

        if (!dest_in_graph)
        {
            // add dest to graph
            add(gr, dest);
        }

        // if we JUST added one or both of the nodes...
        if ((!start_in_graph) || (!dest_in_graph))
        {
            // locate start node
            int start_idx = -1;

            for (int i = 0; i < gr->count; i++)
            {
                if (strcmp((gr->adj_list)[i]->station, start) == 0)
                {
                    start_idx = i;
                }
            }

            // if start does not have any edges yet...
            if ((gr->adj_list)[start_idx]->edges == NULL)
            {
                // create new edge
                Enode *new_edge = (Enode *)malloc(sizeof(Enode));
                strcpy(new_edge->vertex, dest);
                new_edge->weight = weight;
                new_edge->next = NULL;

                (gr->adj_list)[start_idx]->edges = new_edge;

                return;
            }

            // locate end of neighbour list for start node
            Enode *temp = (gr->adj_list)[start_idx]->edges;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            // create new edge
            Enode *new_edge = (Enode *)malloc(sizeof(Enode));
            strcpy(new_edge->vertex, dest);
            new_edge->weight = weight;
            new_edge->next = NULL;

            // connect to end of neighbour list
            temp->next = new_edge;
        }
        // start and dest were already in adj_list before we got here
        else
        {
            // locate start node
            int start_idx = -1;

            for (int i = 0; i < gr->count; i++)
            {
                if (strcmp((gr->adj_list)[i]->station, start) == 0)
                {
                    start_idx = i;
                }
            }

            // if start has no edges yet...
            if ((gr->adj_list)[start_idx]->edges == NULL)
            {
                Enode *new_edge = (Enode *)malloc(sizeof(Enode));
                strcpy(new_edge->vertex, dest);
                new_edge->next = NULL;
                new_edge->weight = weight;

                (gr->adj_list)[start_idx]->edges = new_edge;
            }

            // check if edge in neighbours list for start
            Enode *prev = NULL;
            Enode *temp = (gr->adj_list)[start_idx]->edges;

            while (temp != NULL)
            {
                if (strcmp(temp->vertex, dest) == 0)
                {
                    temp->weight = weight;
                    return;
                }

                prev = temp;
                temp = temp->next;
            }

            // edge is not in neighbours list for start,
            // so we will add it
            Enode *new_edge = (Enode *)malloc(sizeof(Enode));
            strcpy(new_edge->vertex, dest);
            new_edge->next = NULL;
            new_edge->weight = weight;

            prev->next = new_edge;
        }
    }
}

void disrupt(Graph *gr, char *station)
{
    // printf("%s is being purged\n", station);

    // make sure station is actually in graph
    int station_loc = -1;

    for (int i = 0; i < gr->count; i++)
    {
        if (strcmp((gr->adj_list)[i]->station, station) == 0)
        {
            station_loc = i;
        }
    }

    if (station_loc == -1)
    {
        return;
    }

    // remove edges with station
    for (int i = 0; i < gr->count; i++)
    {
        // printf("\tlooking at edges from: %s\n", (gr->adj_list)[i]->station);

        if ((gr->adj_list)[i]->edges == NULL)
        {
            continue;
        }

        // check if first edge needs to be removed
        if (strcmp((gr->adj_list)[i]->edges->vertex, station) == 0)
        {
            Enode *del = (gr->adj_list)[i]->edges;
            (gr->adj_list)[i]->edges = (gr->adj_list)[i]->edges->next;
            free(del);
            continue;
        }

        // remove edge
        int to_exit = 0;
        Enode *prev = NULL;
        Enode *temp = (gr->adj_list)[i]->edges;

        while (temp != NULL)
        {
            if (strcmp(temp->vertex, station) == 0)
            {
                prev->next = temp->next;

                free(temp);
                to_exit = 1;
            }

            if (to_exit)
            {
                break;
            }

            prev = temp;
            temp = temp->next;
        }
    }

    // printf("removing the station itself: %s\n", (gr->adj_list)[station_loc]->station);

    // remove edges coming out of the node being purged
    if ((gr->adj_list)[station_loc]->edges != NULL)
    {
        Enode *this = (gr->adj_list)[station_loc]->edges;
        Enode *that = NULL;

        while (this != NULL)
        {
            that = this->next;
            free(this);
            this = that;
        }
    }

    // remove the node itself by making new, shorter, adj list

    /*
    there is an issue here with free()s
    */

    Vnode **new_adj = (Vnode **)malloc((gr->count - 1) * sizeof(Vnode *));

    int marker = 0;

    for (int i = 0; i < gr->count; i++)
    {
        if (i != station_loc)
        {
            new_adj[marker] = (gr->adj_list)[i];
            marker++;
        }
    }

    free((gr->adj_list)[station_loc]);
    free(gr->adj_list);

    gr->adj_list = new_adj;
    gr->count--;

    if (gr->count == 0)
    {
        free(new_adj);
        gr->adj_list = NULL;
    }
}