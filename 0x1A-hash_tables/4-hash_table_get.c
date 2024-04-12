#include "hash_tables.h"
/**
 * hash_table_get - retrieve the value associated with a key in a hash table.
 * @ht: A pointer to the hash table.
 * @key: the key to get the value of.
 * Return: the value associated with the element, or NULL.
 */

char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int index;
	hash_node_t *node;

	if (!ht || !key || *key == '\0')
		return (NULL);
	index = key_index((const unsigned char *)key, ht->size);

	if (index >= ht->size)
		return (NULL);
	node = ht->array[index];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			return (node->value);
		}
		node = node->next;
	}
	return (NULL);
}
