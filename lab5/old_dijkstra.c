char **plan_route(Graph *gr, char *start, char *dest)
{
    reset_gr(gr);

    // PRIORITY QUEUE AS DYNAMIC STRING ARRAY
    char **q = (char **)malloc(sizeof(char *));
    q[0] = (char *)malloc(MAX_LEN);
    strcpy(q[0], start);
    int q_size = 1;

    int head_in_list = 0;

    // find head in adj_list
    for (int i = 0; i < gr->count; i++)
    {
        // change cost
        if (strcmp((gr->adj_list)[i]->station, q[0]) == 0)
        {
            head_in_list = 1;
            (gr->adj_list)[i]->cost = 0;
        }
    }

    // if head not in list, don't even bother
    if (!head_in_list)
    {
        // free queue
        free(q[0]);
        free(q);

        char **null_ptr = NULL;
        return null_ptr;
    }

    while (q_size > 0)
    {
        // curr = next in queue
        char *curr = q[0];

        // for (int i = 0; i < q_size; i++)
        // {
        //     printf("%s\n", q[i]);
        // }

        // printf("\n");

        // pop from queue
        for (int i = 0; i < q_size - 1; i++)
        {
            q[i] = q[i + 1];
        }

        q = realloc(q, sizeof(q[0]) * (q_size - 1));

        q_size--;

        int a = sizeof(q[0]);

        // check if curr has already been visited
        int curr_already_processed = 0;

        for (int i = 0; i < gr->count; i++)
        {
            if (strcmp((gr->adj_list)[i]->station, curr) == 0)
            {
                // if curr was already visited...
                if ((gr->adj_list)[i]->visited)
                {
                    curr_already_processed = 1;
                    break;
                }

                (gr->adj_list)[i]->visited = 1;
                break;
            }
        }

        if (curr_already_processed)
        {
            continue;
        }

        // printf("here\n");

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

                // append to queue
                q = realloc(q, a * (q_size + 1));
                q[q_size] = (char *)malloc(MAX_LEN);
                strcpy(q[q_size], (gr->adj_list)[neighbour_loc]->station);
                q_size++;
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