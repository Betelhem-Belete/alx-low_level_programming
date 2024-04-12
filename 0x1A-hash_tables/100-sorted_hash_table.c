#include "hash_tables.h"
#include "helper.h"

/**
 * shash_table_create - create a hash table and return a pointer to it
 * @size: size of the hash table
 * Return: a pointer to the hash table or NULL
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *shash_table;

	shash_table = malloc(sizeof(shash_table_t));
	if (!shash_table)
		return (NULL);
	shash_table->array = malloc(sizeof(shash_node_t *) * size);
	if (!shash_table->array)
	{
		free(shash_table);
		return (NULL);
	}
	shash_table->size = size;
	shash_table->shead = shash_table->stail = NULL;
	return (shash_table);
}

/**
 * shash_table_set - adds an element to the hash table
 * @ht: the hash table
 * @key: the key of the node
 * @value: value of the node
 * Return: 1 if it succeeded, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *node, *cur_node;
	int index;

	if (ht == NULL || ht->array == NULL || ht->size == 0 ||
			key == NULL || strlen(key) == 0 || value == NULL)
		return (0);
	index = key_index((const unsigned char *)key, ht->size);
	cur_node = ht->array[index];
	while (cur_node)
	{
		if (strcmp(cur_node->key, key) == 0)
		{
			free(cur_node->value);
			cur_node->value = strdup(value);
			return (1);
		}
		cur_node = cur_node->next;
	}
	node = create_node(key, value);
	if (!node)
		return (0);
	node->next = ht->array[index];
	ht->array[index] = node;
	sorted_list(ht, node);
	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: the hash table
 * @key: key to retrieve the value associated with
 * Return: the value of the key
 */

char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *cur_node;
	int index;

	if (!ht || !key)
		return (NULL);
	index = key_index((const unsigned char *)key, ht->size);
	cur_node = ht->array[index];
	while (cur_node)
	{
		if (strcmp(cur_node->key, key) == 0)
			return (cur_node->value);
		cur_node = cur_node->next;
	}
	return (NULL);
}

/**
 * shash_table_delete - delete the hash table
 * @ht: the hash table
 */

void shash_table_delete(shash_table_t *ht)
{
	unsigned long int i;
	shash_node_t *cur, *temp;

	if (!ht)
		return;
	for (i = 0; i < (ht->size); i++)
	{
		if (ht->array[i] != NULL)
		{
			cur = ht->array[i];
			while (cur)
			{
				temp = cur->next;
				free(cur->key);
				free(cur->value);
				free(cur);
				cur = temp;
			}
		}
	}
	free(ht->array);
	free(ht);
}
