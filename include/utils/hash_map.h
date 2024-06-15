#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BUCKET_SIZE 16

typedef struct HashValue HashValue;

struct HashValue {
    int id;
    void* value;
    HashValue* next;
};

typedef struct HashMap {
    HashValue* buckets[MAX_BUCKET_SIZE];
} HashMap;

/**
 * @brief Hash function for an int identifier. 
 * 
 * @param id the id to hash
 * @return int The hashmap bucket index 
 */
int     hash_fn(int id);

/**
 * @brief Finds an object in the hasmap
 * 
 * @param id ID of the object to find
 * @param map Hashmap to search into
 * @return void* object pointer, NULL if not found.
 */
void*   hash_map_find(  int id, 
                        HashMap* map);

/**
 * @brief Inserts an object in the hashmap
 * 
 * @param id ID of the object to insert
 * @param value Pointer to the object to insert
 * @param map HashMap to insert object into
 * @return true Successful insert.
 * @return false Insert failed.
 */
bool   hash_map_insert( int id, 
                        void* value, 
                        HashMap* map);

/**
 * @brief Removes an item from the HashMap.
 * 
 * @param id ID of the object to remove.
 * @param map HashMap to remove the object from.
 * @param deallocate Flag, set to deallocate the object referenced in the HashMap.
 * @return true Removal successful.
 * @return false Removal failed.
 */
bool    hash_map_remove(int id, 
                        HashMap* map,
                        bool deallocate);

void    free_hash_map(  HashMap* map);

#endif