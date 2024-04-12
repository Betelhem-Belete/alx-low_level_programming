#include "hash_tables.h"

/**
 * create_node - create node.
 * @key: key of the node.
 * @value: value of the node.
 * Return: pointer to the new node or NULL in failure.
 */

hash_node_t *create_node(const char *key, const char *value)
{
	hash_node_t *node = malloc(sizeof(hash_node_t));

	if (!node)
		return (NULL);
	node->key = strdup(key);
	if (!(node->key))
	{
		free(node);
		return (NULL);
	}
	node->value = strdup(value);
	if (!(node->value))
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	return (node);
}

/**
 * hash_table_set - add or update an element in a hash table.
 * @ht: A pointer to the hash table.
 * @key: the key to add - cannot be an empty string.
 * @value: the value associated with key.
 *
 * Return: 1 if it succeeded, 0 otherwise.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	hash_node_t *new_node, *existed_node;

	if (!ht || !key || !value || *key == '\0')
		return (0);
	index = key_index((const unsigned char *)key, ht->size);
	/* if index has node with the same key update the value of this node */
	if (ht->array[index])
	{
		existed_node = ht->array[index];
		while (existed_node)
		{
			if (existed_node && strcmp(existed_node->key, key) == 0)
			{
				free(existed_node->value);
				existed_node->value = strdup(value);
				return (1);
			}
			existed_node = existed_node->next;
		}
		/* if (exixted_node->key != key) at the same index, it's collision */
		/* In case of collision, new node added at the beginning of the list*/
		new_node = create_node(key, value);
		if (!new_node)
			return (0);
		new_node->next = ht->array[index];
		ht->array[index] = new_node;
		return (1);
	}
	/* if index has no node insert it */
	else
	{
		new_node = create_node(key, value);
		ht->array[index] = new_node;
		return (1);
	}
}
