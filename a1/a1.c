#include "a1.h"

/**
	Add your functions to this file.
	Make sure to review a1.h.
	Do NOT include a main() function in this file
	when you submit.
*/

Restaurant *initialize_restaurant(char *name)
{
	Restaurant *new = (Restaurant *)malloc(sizeof(Restaurant));

	new->name = (char *)malloc(strlen(name) + 1);
	strcpy(new->name, name);

	new->menu = load_menu(MENU_FNAME);

	new->num_completed_orders = 0;
	new->num_pending_orders = 0;

	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;

	new->pending_orders = q;

	return new;
}

Menu *load_menu(char *fname)
{
	Menu *new = (Menu *)malloc(sizeof(Menu));

	int num_lines = 0;

	FILE *fp = fopen(fname, "r");

	char line[ITEM_CODE_LENGTH + MAX_ITEM_NAME_LENGTH + 10 + 3];

	while (fgets(line, sizeof(line), fp))
	{
		int contains_dollar = 0;
		for (int i = 0; i <= strlen(line) - 1; i++)
		{
			if (line[i] == '$')
			{
				contains_dollar = 1;
			}
		}

		if (!contains_dollar)
		{
			continue;
		}

		(num_lines)++;
	}

	fclose(fp);

	new->item_codes = (char **)malloc(num_lines * sizeof(char *));
	new->item_names = (char **)malloc(num_lines * sizeof(char *));

	for (int i = 1; i <= num_lines; i++)
	{
		(new->item_codes[i - 1]) = (char *)malloc(sizeof(char) * ITEM_CODE_LENGTH);
		(new->item_names[i - 1]) = (char *)malloc(sizeof(char) * MAX_ITEM_NAME_LENGTH);
	}

	double *prices = (double *)malloc(sizeof(double) * num_lines);

	int counter = 0;

	FILE *file = fopen(fname, "r");

	char *tok;
	char *ptr;
	double ret;
	int contains_dollar = 0;

	while (fgets(line, sizeof(line), file))
	{
		contains_dollar = 0;
		for (int i = 0; i <= strlen(line) - 1; i++)
		{
			if (line[i] == '$')
			{
				contains_dollar = 1;
			}
		}

		if (!contains_dollar)
		{
			continue;
		}

		// clear leading and trailing whitespace
		int head = 0;
		while (line[head] == '\r' || line[head] == '\t' || line[head] == ' ')
		{
			head++;
		}

		int tail = strlen(line) - 1;
		while (line[tail] == '\r' || line[tail] == '\t' || line[tail] == ' ')
		{
			tail--;
		}

		char *trimmed = (char *)malloc(sizeof(char) * (tail - head + 2));

		for (int i = head; i <= tail; i++)
		{
			trimmed[i - head] = line[i];
		}

		// printf("%s\n", trimmed);

		char *copy = (char *)malloc(sizeof(char) * (strlen(trimmed) + 1));
		strcpy(copy, trimmed);
		tok = strtok(copy, MENU_DELIM);

		// tok = strtok(trimmed, MENU_DELIM);
		strcpy(new->item_codes[counter], tok);

		tok = strtok(NULL, MENU_DELIM);
		strcpy(new->item_names[counter], tok);

		tok = strtok(NULL, "\n");
		tok++;
		tok[strlen(tok) - 1] = '\0';

		ret = strtod(tok, &ptr);
		prices[counter] = ret;

		counter++;

		free(trimmed);
		free(copy);
	}

	fclose(file);

	new->item_cost_per_unit = prices;
	new->num_items = num_lines;

	return new;
}

Order *build_order(char *items, char *quantities)
{
	Order *new = (Order *)malloc(sizeof(Order));

	new->num_items = (int)strlen(items) / (ITEM_CODE_LENGTH - 1);
	new->item_quantities = (int *)malloc((new->num_items) * sizeof(int));
	new->item_codes = (char **)malloc((new->num_items) * sizeof(char *));

	for (int i = 0; i < (new->num_items); i++)
	{
		(new->item_codes)[i] = (char *)malloc((ITEM_CODE_LENGTH) * sizeof(char));
		(new->item_codes)[i][(ITEM_CODE_LENGTH) * sizeof(char) - 1] = '\0';
	}

	char *ptr = NULL;
	char *token = NULL;

	char *copy = (char *)malloc(sizeof(char) * (strlen(quantities) + 1));
	strcpy(copy, quantities);
	token = strtok(copy, MENU_DELIM);

	int counter = 0;
	int flag = 0;

	while (token != NULL)
	{
		(new->item_quantities)[counter] = strtod(token, &ptr);
		token = strtok(NULL, MENU_DELIM);

		for (int i = 0; i < ITEM_CODE_LENGTH - 1; i++)
		{
			(new->item_codes)[counter][i] = items[flag + i];
		}

		counter++;
		flag += (ITEM_CODE_LENGTH - 1);
	}

	free(copy);

	return new;
}

void enqueue_order(Order *order, Restaurant *restaurant)
{
	QueueNode *new_node;
	new_node->order = order;
	new_node->next = NULL;

	restaurant->pending_orders->tail->next = new_node;
	restaurant->num_pending_orders++;
	restaurant->pending_orders->tail = new_node;
}

Order *dequeue_order(Restaurant *restaurant)
{
	Order *ret = restaurant->pending_orders->head->order;
	QueueNode *new_head = restaurant->pending_orders->head->next;

	clear_order(&(restaurant->pending_orders->head->order));

	restaurant->pending_orders->head = new_head;
	restaurant->num_pending_orders--;
	restaurant->num_completed_orders--;

	return ret;
}

double get_item_cost(char *item_code, Menu *menu)
{
	int val = 0;

	for (int i = 0; i < menu->num_items; i++)
	{
		if ((menu->item_codes)[i] == item_code)
		{
			val = i;
		}
	}

	return (menu->item_cost_per_unit)[val];
}

double get_order_subtotal(Order *order, Menu *menu)
{
	double total = 0;
	double cost = 0;

	for (int i = 0; i < order->num_items; i++)
	{
		cost = get_item_cost(order->item_codes[i], menu);
		total += cost * order->item_quantities[i];
	}

	return total;
}

double get_order_total(Order *order, Menu *menu)
{
	double subtotal = get_order_subtotal(order, menu);
	return ((TAX_RATE / 100.0) + 1) * subtotal;
}

int get_num_completed_orders(Restaurant *restaurant)
{
	return restaurant->num_completed_orders;
}

int get_num_pending_orders(Restaurant *restaurant)
{
	return restaurant->num_pending_orders;
}

void clear_order(Order **order)
{
	for (int i = 0; i < (*order)->num_items; i++)
	{
		free(((*order)->item_codes)[i]);
	}

	free((*order)->item_codes);
	free((*order)->item_quantities);

	free(*order);
	*order = NULL;
}

void clear_menu(Menu **menu)
{
	Menu *temp = *menu;

	for (int i = 0; i < (*menu)->num_items; i++)
	{
		free(((temp)->item_codes)[i]);
		free(((temp)->item_names)[i]);
	}

	free((temp)->item_codes);
	free((temp)->item_names);

	free((temp)->item_cost_per_unit);

	free(temp);
	*menu = NULL;
}

void close_restaurant(Restaurant **restaurant)
{
	free((*restaurant)->name);
	clear_menu(&((*restaurant)->menu));

	QueueNode *curr = (*restaurant)->pending_orders->head;
	QueueNode *temp = NULL;

	while (curr != NULL)
	{
		clear_order(&(curr->order));
		temp = curr;
		curr = curr->next;
		free(temp);
	}

	free((*restaurant)->pending_orders);

	free(*restaurant);
	*restaurant = NULL;
}

void print_menu(Menu *menu)
{
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++)
	{
		fprintf(stdout, "(%s) %s: %.2f\n",
				menu->item_codes[i],
				menu->item_names[i],
				menu->item_cost_per_unit[i]);
	}
}

void print_order(Order *order)
{
	for (int i = 0; i < order->num_items; i++)
	{
		fprintf(
			stdout,
			"%d x (%s)\n",
			order->item_quantities[i],
			order->item_codes[i]);
	}
}

void print_receipt(Order *order, Menu *menu)
{
	for (int i = 0; i < order->num_items; i++)
	{
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout,
			"%d x (%s)\n @$%.2f ea \t %.2f\n",
			order->item_quantities[i],
			order->item_codes[i],
			item_cost,
			item_cost * order->item_quantities[i]);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);

	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}