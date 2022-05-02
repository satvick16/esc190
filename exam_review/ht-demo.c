/* hash_table_ignore_collisions.c from LEC0101 modified to
 *	store grocery store items and their prices.
 *	The hash function uses the ASCII value of the first char
 *	of the item name and takes the modulus with the current number of buckets.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 100
#define ALPHA 0.5
#define PRINT_DEBUG 1 // Set to 0 if you want less information to be printed out

typedef struct Cargo
{
	char item[NAME_LEN]; // hash based on item name (first letter)
	double price;
} Cargo;

typedef struct HashTable
{
	int num_buckets;
	int num_filled_buckets;
	Cargo **buckets; // replace upon collision
} HashTable;

//==================================================================
//
//		FUNCTIONS TO PRINT/DISPLAY THE HASH TABLE AND DATA
//
//==================================================================
void print_cargo(Cargo *cargo)
{
	fprintf(stdout, "%s %.2lf\n", cargo->item, cargo->price);
} // print price to two decimal places

void print_hash_table(HashTable *ht)
{
	fprintf(stdout, "====== HASH TABLE WITH %d BUCKETS ======\n", ht->num_buckets);
	for (int i = 0; i < ht->num_buckets; i++)
	{
		fprintf(stdout, "BUCKET INDEX: %d\t CARGO: ", i);
		if (ht->buckets[i] == NULL)
		{
			fprintf(stdout, "\n");
		}
		else
		{
			print_cargo(ht->buckets[i]);
		}
	}
	fprintf(stdout, "========================================\n");
}

//==================================================================
//
//		FUNCTION TO CREATE CARGO
//
//==================================================================

Cargo *make_cargo(char *item, double price)
{
	Cargo *c = (Cargo *)malloc(sizeof(Cargo));
	strcpy(c->item, item);
	c->price = price;
	return c;
}

//==================================================================
//
//		HASH TABLE UTILITIES
//
//==================================================================

HashTable *initialize_hash_table(int starting_size)
{
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	ht->buckets = (Cargo **)calloc(starting_size, sizeof(Cargo *));
	ht->num_buckets = starting_size;
	ht->num_filled_buckets = 0;
	return ht;
}

float get_load_factor(HashTable *ht)
{
	/**
	Calculate the load factor of the hash table, alpha
	*/
	return ((float)ht->num_filled_buckets) / ((float)ht->num_buckets);
}

int hash(HashTable *ht, char *item)
{
	/**
	Modulo hash function - uses first letter of the item name
	*/
	return item[0] % ht->num_buckets;
}

Cargo *insert(HashTable *ht, Cargo *c)
{
	/**
	Insert "helper", not meant to be used as interface with the
	hash table.

	In the case of a collision, the original cargo is removed and replaced
	with the new cargo. The original cargo is returned.
	*/
	Cargo *tmp = NULL;
	int i = hash(ht, c->item);

	if (PRINT_DEBUG)
	{
		fprintf(stdout, "Now inserting record for: ");
		print_cargo(c);
		fprintf(stdout, "Attempting insert at bucket index %d ...\n", i);
	}

	if (ht->buckets[i] != NULL)
	{
		tmp = ht->buckets[i]; // hold onto the item to be removed
		if (PRINT_DEBUG)
		{
			fprintf(stdout, "Collision found! Removing record for: ");
			print_cargo(tmp);
		}
	}
	else
	{
		ht->num_filled_buckets++;
	}
	ht->buckets[i] = c; // add item to bucket i

	return tmp; // return the removed item
}

void resize(HashTable *ht)
{
	/**
	Resizes the hash table in-place such that it has double the number
	of buckets. Re-hashes every key and moves every pre-existing
	cargo in the table.
	*/

	// new bucket count should be double
	int new_size = ht->num_buckets * 2;
	int old_size = ht->num_buckets;

	Cargo *c;

	ht->buckets = realloc(ht->buckets, sizeof(Cargo **) * new_size);
	for (int i = old_size; i < new_size; i++)
	{
		ht->buckets[i] = NULL;
	} // remember realloc() doesn't initialize the expanded memory!
	ht->num_buckets = new_size;
	ht->num_filled_buckets = 0;

	for (int i = 0; i < old_size; i++)
	{
		c = ht->buckets[i];
		if (c != NULL)
		{
			ht->buckets[i] = NULL;
			Cargo *swapped = insert(ht, c);
			// using modulo arithmetic, one can show that there is no risk
			// of collisions in the resize inserts for the modulo hash
		}
	}
}

Cargo *insert_with_resize(HashTable *ht, Cargo *c)
{
	/**
	Insert maintaining load factor alpha with in-place resize.

	In the case of a collision, the original cargo is removed and replaced
	with the new cargo. The original cargo is returned.
	*/
	fprintf(stdout, "Hash table current load factor: %0.2f\n", get_load_factor(ht));
	if (get_load_factor(ht) >= ALPHA)
	{
		if (PRINT_DEBUG)
		{
			fprintf(stdout, "Load factor %0.2f exceeds alpha %0.2f. Resizing...\n", get_load_factor(ht), ALPHA);
			fprintf(stdout, "Original # buckets: %d\n", ht->num_buckets);
		}
		resize(ht);
		if (PRINT_DEBUG)
		{
			fprintf(stdout, "Resize complete.\n");
			fprintf(stdout, "New # buckets: %d\n", ht->num_buckets);
		}
	}
	Cargo *tmp = insert(ht, c);
	return tmp; // return item removed during the collision, or null
}

Cargo *delete_key(HashTable *ht, char *item)
{
	/**
	Remove the key, if it exists, from the hash table.
	Note that this function should not free any memory
	associated with the Cargo.
	*/
	int i = hash(ht, item);
	Cargo *tmp = NULL;

	tmp = ht->buckets[i];  // hold onto the item to return later
	ht->buckets[i] = NULL; // clear the bucket
	return tmp;
}

Cargo *lookup(HashTable *ht, char *item)
{
	/**
	Return the Cargo, if it exists, associated with item name
	*/
	if (PRINT_DEBUG)
	{
		fprintf(stdout, "Now looking for item: %s\n", item);
	}
	Cargo *result = NULL;
	int i = hash(ht, item);
	if (ht->buckets[i] != NULL && strcmp(ht->buckets[i]->item, item) == 0)
	{
		result = ht->buckets[i];
		if (PRINT_DEBUG)
		{
			fprintf(stdout, ".. Item found: ");
			print_cargo(result);
		}
	}
	else if (PRINT_DEBUG)
	{
		fprintf(stdout, ".. Item NOT found.\n");
	}
	return result;
}

void destroy(HashTable **ht)
{
	/**
	Free all memory allocated for the hash table to allow
	program termination.
	*/
	for (int i = 0; i < (*ht)->num_buckets; i++)
	{
		free((*ht)->buckets[i]);
		(*ht)->buckets[i] = NULL;
	}
	free((*ht)->buckets);
	free((*ht));
	*ht = NULL;
}

int main()
{
	HashTable *ht = initialize_hash_table(1);
	Cargo *c;
	Cargo *r;

	c = make_cargo("Banana", 0.67);
	r = insert_with_resize(ht, c);
	print_hash_table(ht);
	free(r);

	c = make_cargo("Apple", 2.99);
	r = insert_with_resize(ht, c);
	print_hash_table(ht);
	free(r);

	c = make_cargo("Cat", 150.00);
	r = insert_with_resize(ht, c);
	print_hash_table(ht);
	free(r);

	c = make_cargo("Banana", 0.47); // collision - reduce the price of bananas
	r = insert_with_resize(ht, c);
	print_hash_table(ht);
	free(r);

	c = make_cargo("Banana", 0.97); // collision - make bananas more expensive
	r = insert_with_resize(ht, c);
	print_hash_table(ht);
	free(r);

	lookup(ht, "Banana");
	lookup(ht, "Apple");
	lookup(ht, "Cat");

	destroy(&ht);
}