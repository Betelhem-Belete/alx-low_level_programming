#include "hash_tables.h"

/**
 * hash_table_print - prints a hash table.
 * @ht: pointer to the hash table.
 *
 * Return: void.
 */
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int i;
	int flag = 0;
	hash_node_t *node;

	if (ht == NULL)
		return;

	printf("{");
	for (i = 0; i < ht->size; i++)
	{

		if (ht->array[i])
		{
			node = ht->array[i];

			while (node)
			{
				if (flag)
					printf(", ");
				printf("'%s': '%s'", node->key, node->value);
				node = node->next;
				flag = 1;
			}
		}
	}
	printf("}\n");
}
