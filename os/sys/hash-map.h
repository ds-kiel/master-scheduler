/**
 * \file
 *         Simple fixed Hash map
 * \author
 *         Oliver Harms <harms@chalmers.se>
 * 
 * inspired by http://www.kaushikbaruah.com/posts/data-structure-in-c-hashmap/
 * and https://stackoverflow.com/questions/24203858/how-can-i-implement-a-fixed-size-hashmap
 *
 */
#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "contiki.h"

#ifdef HASH_MAP_CONF_SIZE
#define HASH_MAP_SIZE HASH_MAP_CONF_SIZE
#else
#define HASH_MAP_SIZE 8
#endif

typedef struct hash_node_t hash_node_t;
struct __attribute__((packed)) hash_node_t{
  uint16_t key;
  uint16_t val;
  hash_node_t *next;
};

typedef struct __attribute__((packed)) hash_table_t{
  uint8_t number_entries;
  hash_node_t list[HASH_MAP_SIZE];
} hash_table_t;

void hash_map_clear_table(hash_table_t *table);

//uint8_t hash_code(uint8_t key);

uint8_t hash_map_insert(hash_table_t *table, uint16_t key, uint16_t val);

uint16_t hash_map_lookup(hash_table_t *table, uint16_t key);

#endif /* HASH_MAP_H */