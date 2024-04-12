#include "hash_tables.h"
/**
 * key_index - produce the index of a certain key
 * @key: the certain key
 * @size: size of the hash_table array
 * Return: index of the key
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int index;

	index = hash_djb2(key) % size;
	return (index);
}
