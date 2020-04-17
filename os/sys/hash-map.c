/**
 * \file
 *         Simple fixed Hash map
 * \author
 *         Oliver Harms <harms@chalmers.se>
 *
 */
#include "contiki.h"
#include "hash-map.h"

void hash_map_clear_table(hash_table_t *table){
  uint8_t pos;
  hash_node_t *node;
  table->number_entries = 0;
  for (pos = 0; pos < HASH_MAP_SIZE; ++pos){
    node = &(table->list[pos]);
    node->key = 0;
    node->val = 0;
    node->next = NULL;
  }
}

static uint8_t hash_code(uint8_t key){
  return (key % HASH_MAP_SIZE);
}

uint8_t hash_map_insert(hash_table_t *table, uint16_t key, uint16_t val){
  uint8_t pos = hash_code(key);
  hash_node_t *node = &(table->list[pos]);
  if (node->key == 0){
    node->key = key;
    node->val = val;
    ++(table->number_entries);
    return 1;
  }
  hash_node_t *prev_node;
  do {
    if (node->key == key){
      node->val = val;
      return 1;
    }
    prev_node = node;
    node = node->next;
  } while (node);
  if (table->number_entries >= HASH_MAP_SIZE){
    return 0;
  }
  uint8_t pos2;
  for (pos2 = pos; pos2 < HASH_MAP_SIZE; ++pos2){
    if (table->list[pos2].key == 0){
      node = &(table->list[pos2]);
      node->key = key;
      node->val = val;
      prev_node->next = node;
      ++(table->number_entries);
      return 1;
    }
  }
  for (pos2 = 0; pos2 < pos; ++pos2){
    if (table->list[pos2].key == 0){
      node = &(table->list[pos2]);
      node->key = key;
      node->val = val;
      prev_node->next = node;
      ++(table->number_entries);
      return 1;
    }
  }
  return 0;
}

uint16_t hash_map_lookup(hash_table_t *table, uint16_t key){
  uint8_t pos = hash_code(key);
  hash_node_t *node = &(table->list[pos]);
  while (node){
    if (node->key == key){
      return node->val;
    }
    node = node->next;
  }
  return 0;
}