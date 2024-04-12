#ifndef HELPER_H
#define HELPER_H

#include "hash_tables.h"
/**
 * create_node - create a new node
 * @key: key of the new node
 * @value: value of the new node
 * Return: new node or NULL
 */
shash_node_t *create_node(const char *key, const char *value)
{
	shash_node_t *node = (shash_node_t *)malloc(sizeof(shash_node_t));

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
	node->next = NULL;
	return (node);
}
/**
 * sorted_list - create the sorted linked list of the hash table
 * @ht: the hash table
 * @node: node to insert
 */
void sorted_list(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *tmp;

	if (!ht->shead && !ht->stail)
	{
		ht->shead = ht->stail = node;
		node->sprev = node->snext = NULL;
		return;
	}
	tmp = ht->shead;
	if (strcmp(node->key, ht->shead->key) < 0)
	{
		node->snext = ht->shead;
		ht->shead->sprev = node;
		ht->shead = node;
		node->sprev = NULL;
		return;
	}
	while (tmp)
	{
		if (strcmp(node->key, tmp->key) < 0)
		{
			node->snext = tmp;
			tmp->sprev->snext = node;
			node->sprev = tmp->sprev;
			tmp->sprev = node;
			return;
		}
		tmp = tmp->snext;
	}
	ht->stail->snext = node;
	node->sprev = ht->stail;
	ht->stail = node;
	ht->stail->snext = NULL;
}

/**
 * shash_table_print - print the hash table
 * @ht: the hash table
 */

void shash_table_print(const shash_table_t *ht)
{
	int flag = 0;
	shash_node_t *cur_node;

	if (!ht)
		return;
	printf("{");
	cur_node = ht->shead;
	while (cur_node)
	{
		if (flag)
			printf(", ");
		printf("'%s': '%s'", cur_node->key, cur_node->value);
		flag = 1;
		cur_node = cur_node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - print the hash table in reversed order
 * @ht: the hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	int flag = 0;
	shash_node_t *cur_node;

	if (!ht)
		return;
	printf("{");
	cur_node = ht->stail;
	while (cur_node)
	{
		if (flag)
			printf(", ");
		printf("'%s': '%s'", cur_node->key, cur_node->value);
		flag = 1;
		cur_node = cur_node->sprev;
	}
	printf("}\n");
}
#endif
